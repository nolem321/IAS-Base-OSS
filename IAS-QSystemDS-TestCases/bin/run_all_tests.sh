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
     echo "  -t <testnames>   Testcase names (comma separated)."
     echo "  -d <databases>   Databases(comma separated)."
     echo "  -c Copy answer to specification."
     echo
     echo $*
     echo
     exit 1
}

_dbs=$( (cd ${_db_dir}; echo *) )

while getopts ht:d:c opt
do
  case $opt in
    h)
         help 0
    ;;
    d)
      _dbs=$( echo $OPTARG|tr , " ")
    ;;
    t)
      _parmcases=$( echo $OPTARG|tr , " ")
    ;;
    c)
      _copy="-c"
    ;;

    *)
      help Invalid option.
     ;;
  esac
done

for d in ${_dbs}
do

if [ -z "${_parmcases}" ]; then
  echo Test cases from : ${d}/valid_test_cases.txt
  _cases=$(cat ${_db_dir}/${d}/valid_test_cases.txt)
else
  _cases=${_parmcases}
fi

if [ -z "${_cases}" ]; then
echo "No test cases for: " ${d}
else
 for c in ${_cases}
  do
    ${_script_dir}/run_tests.sh -t ${c} -d ${d} ${_copy}
  done
fi

done