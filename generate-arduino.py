#!/usr/bin/env python
from os import path

def filenameNotIn(fnlist):
	def closure(fn, full):
		return not fn in fnlist
	return closure

def filenameDoesNotContain(text):
	def closure(fn, full):
		return text not in fn
	return closure

def filenameDoesNotBeginWith(text):
	def closure(fn, full):
		return fn[0:len(text)] != text
	return closure

def fileDoesNotInclude(substrings):
	def closure(fn, full):
		with open(full, 'rb') as f:
			data = f.read()
			for substring in substrings:
				if substring in data:
					return False
			return True
		return False #couldn't open or something went wrong.
	return closure

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
	filenameDoesNotBeginWith(path.join('stl','debug')),
	filenameDoesNotBeginWith(path.join('using','h')),
	fileDoesNotInclude([
		'Please remove it', #workaround headers for sun
		'pollution', # old namespace-polluting headers
	])
]

sources = [
#	'stlport_prefix.h',
#	'aligned_buffer.h',
#	'locale.cpp',
#	'ios.cpp'
]

def allFiltersInList(filterList):
	def closure(fn, full):
		for n, f in enumerate(filterList):
			if not f(fn, full):
				#print(fn, "Failed", n)
				return False
		return True
	return closure


def extractPathInfo(primaryRoot, inputRoot):
	def closure(fn):
		full = path.join(inputRoot, fn)
		rel = path.relpath(full, primaryRoot)
		return full, rel
	return closure

def buildCopyListFromRoot(rootDir, filterFunc):
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
	with open(fn, 'ab') as f:
		return

def main(rootpath, dest):
	from os import path
	headerRoot = path.join(rootpath, 'stlport')
	srcRoot = path.join(rootpath, 'src')

	files = buildCopyListFromRoot(headerRoot, allFiltersInList(headerFilters))
	files.extend([
		{
			'full_source' : path.join(srcRoot, fn),
			'old_root' : srcRoot,
			'rel_name' : fn
		}
		for fn in sources ])
	doCopy(files, dest)
	touchFile(path.join(dest, 'stlport.h'))


if __name__ == '__main__':
	import sys
	from os import makedirs, error
	if hasattr(sys.modules['__main__'], '__file__'):
		myself = path.abspath(sys.modules['__main__'].__file__)
		rootpath = path.dirname(myself)
		if len(sys.argv) > 1:
			dest = path.dirname(sys.argv[1])
		else:
			dest = path.join(rootpath, 'Arduino', 'stlport')
		try:
			makedirs(dest)
		except error:
			pass
		main(rootpath, dest)

