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
	filenameDoesNotBeginWith(path.join('using','h')),
	fileDoesNotInclude([
		'Please remove it', #workaround headers for sun
		'pollution', # old namespace-polluting headers
	])
]

sources = [
	'stlport_prefix.h',
	'aligned_buffer.h',
	'acquire_release.h',
	'locale.cpp',
	'ios.cpp',
	'c_locale.h',
	'c_locale.c',
	'locale_impl.cpp',
	'locale_impl.h',
	'c_locale_dummy/c_locale_dummy.c',
	'num_get.cpp',
	'num_get_float.cpp',
	'num_put.cpp',
	'num_put_float.cpp',
	'locale_catalog.cpp',
	'collate.cpp',
	'codecvt.cpp',
	'allocators.cpp',
	'lock_free_slist.h',
	'messages.cpp',
	'monetary.cpp',
	'message_facets.h',
	'numpunct.cpp',
	'dll_main.cpp',
	'facets_byname.cpp',
	'ctype.cpp',
	'iostream.cpp'
]

flatten_sources = [

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
	files.extend([
		{
			'full_source' : path.join(srcRoot, fn),
			'old_root' : srcRoot,
			'rel_name' : path.basename(fn)
		}
		for fn in flatten_sources ])
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

