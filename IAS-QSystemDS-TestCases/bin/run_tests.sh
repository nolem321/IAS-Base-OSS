#!/bin/bash

_script_dir=$(dirname $(readlink -f ${0}))

_test_dir=${_script_dir}/../specs
_work_dir=/tmp/test
_db_dir=${_script_dir}/../db

function help {
     echo
     echo "Dumps table:"
     echo `basename $0` "<parameters>"
     echo "Parameters:"
     echo "  -t <testname>   Testcase name."
     echo "  -d <database>   Database."
     echo "  -c Copy answer to specification."
     echo
     echo $*
     echo
     exit 1
}

_copy=NO

while getopts ht:d:c opt
do
  case $opt in
    h)
          help 0
    ;;
    d)
      _db=$OPTARG
    ;;
    t)
      _test=$OPTARG
    ;;
    c)
      _copy=YES
    ;;
    *)
      help Invalid option.
     ;;
  esac
done

if [ -z ${_test} ] ; then
help Missing testcase.
fi

if [ -z ${_db} ] ; then
help Missing db.
fi

_dburl=${_db_dir}/${_db}/ds.*

_in_dir=${_test_dir}/${_test}
_out_dir=${_work_dir}/${_test}

if [ ! -d ${_in_dir} ] ; then
help ${_in_dir} doesn\'t exists. Missing test case \?
fi


shift `expr $OPTIND - 1`
##################################################################
. ${_script_dir}/setenv.sh
##################################################################
export IAS_LANG_SRC_DIRS=${IAS_LANG_SRC_DIRS}:${_in_dir}:${_script_dir}/../lang
#echo ${IAS_LANG_SRC_DIRS}

#export IAS_QS_REGISTRY=${_script_dir}/../db/registry.xml

mkdir -p ${_out_dir}
rm -f ${_out_dir}/*

${_db_dir}/${_db}/bin/reset.sh 2>/dev/null >/dev/null
#${_db_dir}/${_db}/bin/reset.sh

if [ -f ${_db_dir}/${_db}/txm.xml ] ; then
_xa="-t ${_db_dir}/${_db}/txm.xml"
fi

_input_file=$(echo ${_in_dir}/input.*)
export IAS_DBG_PRT_LOC=Y

#export IAS_DBG_GLOBAL=+info,-details,+error,+stacktrace,+throw,+data
export IAS_DBG_GLOBAL=+info,-details,+error,+stacktrace,+throw,+data,+system
export IAS_DBG_LANG=+info,-details,+error,+stacktrace,+throw
#export IAS_DBG_GLOBAL=-info,-details,+error,+stacktrace,+throw,-data,+system


ias_qs_processor -i file:${_input_file} \
                 -o file:${_out_dir}/output \
                 -l exe main \
                 -d ${_dburl} \
                  ${_xa} \
                  > ${_out_dir}/out.txt \
                  2> ${_out_dir}/err.txt

###############################
if [ ${_copy} == YES ]
then
echo cp ${_out_dir}/output ${_in_dir}/output
cp ${_out_dir}/output ${_in_dir}/output
fi
###############################

diff ${_in_dir}/output ${_out_dir}/output 2> ${_out_dir}/output.diff 1>&2
if [ $? == 0 ]
then
_result=OK
else
_result=Failure
fi


printf " %20s %10s - %s \n" ${_test} ${_db} ${_result}


