#!/bin/bash
set -e

devbranch=STLport-5.2-avr
installbranch=STLport-5.2-arduino-installed
builddir=build/lib

basedir=$(cd $(dirname 0) && pwd)
TMPDIR=$(mktemp -d)

trap EXIT "rm -rf $TMPDIR"

git clone $basedir $tmpdir/repo
(
	cd $tmpdir/repo
	git checkout -b $devbranch origin/$devbranch
	make -C $builddir SKETCHBOOK=$tmpdir install-arduino
	git checkout -b $installbranch origin/$installbranch
	git merge --no-ff --no-commit $devbranch || true
	git rm rf *
	mv $tmpdir/libraries/stlport/* .
	git add .
	git commit -m "Generated installed version for Arduino"
	git push origin $installbranch
)
