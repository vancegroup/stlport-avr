#!/usr/bin/env python
from os import path

def filenameNotIn(fnlist):
	'''
	Predicate-creation function for "argument not in given list"
	(Returns a closure for use as a predicate.)
	'''
	def closure(fn, full):
		return not fn in fnlist
	return closure

def filenameDoesNotContain(text):
	'''
	Predicate-creation function for "argument does not contain the given text"
	(Returns a closure for use as a predicate.)
	'''
	def closure(fn, full):
		return text not in fn
	return closure

def filenameDoesNotBeginWith(text):
	'''
	Predicate-creation function for "argument does not begin with the given text"
	(Returns a closure for use as a predicate.)
	'''
	def closure(fn, full):
		return fn[0:len(text)] != text
	return closure

def fileDoesNotInclude(substrings):
	'''
	Predicate-creation function for "file named by argument does not contain
	any of the text in the given list."
	(Returns a closure for use as a predicate.)
	'''
	def closure(fn, full):
		with open(full, 'rb') as f:
			data = f.read()
			for substring in substrings:
				if substring in data:
					return False
			return True
		return False #couldn't open or something went wrong.
	return closure

def allFiltersInList(filterList):
	'''
	Predicate-creation function for 'argument passes all predicates in given list'.
	That is, the predicate is the AND of all supplied predicates.
	(Returns a closure for use as a predicate.)
	'''
	def closure(fn, full):
		for n, f in enumerate(filterList):
			if not f(fn, full):
				return False
		return True
	return closure


# List of filters (predicates) that a header seen while walking must pass
# before being added to the file copy list.
headerFilters = [
	filenameNotIn([
		# Deprecated
		'iomanip.h',
		'ios.h',
		'iostream.h',
		'istream.h',
		'ostream.h',
		'streambuf.h',
		'strstream',
		'strstream.h',
		'typeinfo.h',

		# Unavailable features
		'pthread_alloc',
		'pthread.h',
		'fstream',
		'fstream.h',
	]),
	filenameDoesNotBeginWith('wince'),
	filenameDoesNotBeginWith(path.join('using','h')),
	fileDoesNotInclude([
		'Please remove it', #workaround headers for sun
		'pollution', # old namespace-polluting headers
	])
]

# List of files to be copied from the src/ directory into the destination
# directory, with structure under src/ intact.
sources = [
#	'stlport_prefix.h',
#	'aligned_buffer.h',
#	'locale.cpp',
#	'ios.cpp'
]

# List of files to be copied relative to the STLport root directory, directly
# into the destination root (directory structure flattened)
flatten_files = [
]



def extractPathInfo(primaryRoot, inputRoot):
	'''
	Function to return a closure for mapping a filename relative to an input root
	to the full path to that file (joining inputRoot and fn) and the relative
	path of the full file with respect to the primary root.

	Honestly, for this one, the code is easier to read/understand than the comment.

	Needed because os.walk tells us a filename and the directory it's in,
	and we want the full path and the path relative to some root, which is
	potentially higher than the file's direct parent directory.

	Made to be called to create the function argument for map()
	'''
	def closure(fn):
		full = path.join(inputRoot, fn)
		rel = path.relpath(full, primaryRoot)
		return full, rel
	return closure

def buildCopyListFromRoot(rootDir, filterFunc):
	'''
	Walks a directory tree from a given directory, and adds dictionaries
	for each file (to be copied eventually) that passes the filter function.

	Used to walk the header tree, for just the "good stuff."
	'''
	from os import walk

	return [
		{
			'full_source' : full,
			'old_root' : rootDir,
			'rel_name' : rel
		}
		for root, dirs, files in walk(rootDir)
		for full, rel in map(extractPathInfo(rootDir, root), files)
		if filterFunc(rel, full)
	]

def doCopy(copyList, newRoot):
	'''
	Given a list of files, represented as dictionaries with at least
	'full_source' (a source path) and 'rel_name' (a destination-relative
	desired post-copy name) keys, copy them into the given new root directory,
	making any necessary directories.
	'''
	from os import path, makedirs
	from shutil import copy2
	for entry in copyList:
		dest = path.join(newRoot, entry['rel_name'])
		destDir = path.dirname(dest)
		if not path.exists(destDir):
			makedirs(destDir)
		print(entry['full_source'], dest)
		copy2(entry['full_source'], dest)


def touchFile(fn):
	'''
	Just open a file (for append) to ensure it exists. In theory, like
	the unix touch command.
	'''
	with open(fn, 'ab') as f:
		return

def main(rootpath, dest):
	'''
	The main body of the Arduino library tree generator.
	Takes the root directory of STLport and the full destination directory
	as parameters.

	Through a mix of filtered file-system walking (headers) and explicit
	specification (source files and extra files), build up a list of
	dictionaries with info about files, which is then passed to doCopy.
	'''

	from os import path
	headerRoot = path.join(rootpath, 'stlport')
	srcRoot = path.join(rootpath, 'src')
	# Generate the initial file list by walking the header tree, filtering as we go.
	files = buildCopyListFromRoot(headerRoot, allFiltersInList(headerFilters))

	# Extend that list with specified source files from src/
	files.extend([
		{
			'full_source' : path.join(srcRoot, fn),
			'old_root' : srcRoot,
			'rel_name' : fn
		}
		for fn in sources ])

	# Extend that list with specified "other" files from arbitrary
	# locations in the source tree, all of which will be copied to the
	# destination root rather than preserving an original directory layout.
	files.extend([
		{
			'full_source' : path.join(rootpath, fn),
			'old_root' : rootpath,
			'rel_name' : path.basename(fn)
		}
		for fn in flatten_files ])

	# Perform the copies of the files in our list to the destination.
	doCopy(files, dest)

	# Create the Arduino-needed dummy header file with touch.
	# TODO: This essentially implies/requires that the destination directory
	# is named 'stlport' - make this more flexible?
	touchFile(path.join(dest, 'stlport.h'))


# Do the thing when run from the command line.
if __name__ == '__main__':
	import sys
	from os import makedirs, error
	# Find out where this source file is, so we know the STLport root dir.
	if hasattr(sys.modules['__main__'], '__file__'):
		myself = path.abspath(sys.modules['__main__'].__file__)
		rootpath = path.dirname(myself)

		# A passed argument is assumed to be a destination directory
		if len(sys.argv) > 1:
			dest = path.dirname(sys.argv[1])
		else:
			# No argument: defaults to build/Arduino/stlport in the STLport tree
			dest = path.join(rootpath, 'build', 'Arduino', 'stlport')

		# Ensure the destination directory exists.
		try:
			makedirs(dest)
		except error:
			pass

		# Now, call the main install method.
		main(rootpath, dest)

