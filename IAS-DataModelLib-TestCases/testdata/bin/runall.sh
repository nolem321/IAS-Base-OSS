#!/bin/bash

export BINDIR=$(dirname "$( readlink -f "$0" )")
export TESTDIR=`echo $BINDIR| sed s/\/bin//`

. ${BINDIR}/setenv.sh

cd $TESTDIR/input

for i in * 
do
( ${BINDIR}/runtestcase.sh $i )
done

