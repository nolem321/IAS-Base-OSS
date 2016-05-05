#!/bin/bash

BINDIR=$(dirname "$( readlink -f "$0" )")
TESTDIR=`echo $BINDIR| sed s/\/bin//`

export TESTINDIR=${TESTDIR}/input/$0
export TESTOUTDIR=${TESTDIR}/output/$0

echo rm -rf ${TESTOUTDIR}
mkdir -p ${TESTOUTDIR}

echo Test: $0

