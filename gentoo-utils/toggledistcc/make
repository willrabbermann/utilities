#!/bin/sh
# (null) - build with default options, no debug data.
# clean - remove $bin
# debug - make with debug options
# install - install to /usr/local/sbin/
# binutils - copy $bin to /mnt/nfs/block0/backup/important/binutils/$bin

bin="toggledistcc"

if [[ $1 == "clean" ]]; then
    make_cmd="rm -f $bin"
elif [[ $1 == "debug" ]]; then
    make_cmd="gcc -Wall -pedantic -g3 toggledistcc.c -o $bin"
elif [[ $1 == "install" ]]; then
    if [[ -f $bin ]]; then
       cp -v $bin /usr/local/sbin/$bin
    else
        echo "Run \"make\" first."
    fi
elif [[ $1 == "binutils" ]]; then
    cp -v $bin /mnt/nfs/block0/backup/important/binutils/$bin
elif [[ -z $1 ]]; then
    make_cmd="gcc -Wall -pedantic -O2 toggledistcc.c -o $bin"
fi

echo $make_cmd

$($make_cmd)
