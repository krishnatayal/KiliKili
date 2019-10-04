#!/bin/bash

usage()
{
	echo "./make_submission.sh <roll number>"
	exit 1
}

#################################################

#Check for mandatory arg
if [ $# -ne 1 ]; then
	echo "Error: Invalid args"
	usage
fi

#Files will be first copied to tmp
dir=/tmp/$1

#delete already existing dir
if [ -d $dir ]; then
	rm -rf $dir
fi

mkdir $dir

#Copy all the dirs to destination
homedir="/home/baahubali/"
if [ -d $homedir/KiliKili ]; then
	cp -r $homedir/KiliKili $dir/
fi
if [ -d $homedir/KiliKili_B3 ]; then
	cp -r $homedir/KiliKili_B4 $dir/
fi
if [ -d $homedir/KiliKili_B4 ]; then
	cp -r $homedir/KiliKili_B3 $dir/
fi
if [ -d $homedir/KiliKili_B5 ]; then
	cp -r $homedir/KiliKili_B5 $dir/
fi

#make tar and copy to home dir
cd /tmp/
tarfile="${1}.tar"
tar -cf $tarfile ${1}
cp $tarfile $homedir

#delete tmp files
rm -f $tarfile
rm -rf $dir
