#! /bin/sh -

printf "%s\n" "Adding baremusl headers ..."
if [ -d ./baremusl ] && [ -d ./baremusl/include ] ; then
	#TODO: add logic to mkdir
	if [ -d /usr/include ] && [ -d /usr/include/sys ] ; then
		cp -vfp ./baremusl/include/sys/*.h /usr/include/sys/ ;
	fi ;
fi ;
