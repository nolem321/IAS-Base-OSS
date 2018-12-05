#!/bin/bash

function help {
     echo
     echo "Dumps table:"
     echo `basename $0` "<parameters>"
     echo "Parameters:"
     echo "  -t <table> Table name."
     echo
     echo $*
     echo
     exit 1
}

while getopts ht: opt
do
  case $opt in
    h)
          help 0
    ;;
    t)
      _table=$OPTARG
    ;;
    *)
      help Invalid option.
     ;;
  esac
done

if [ -z ${_table} ] ; then
help Missing table name.
fi

shift `expr $OPTIND - 1`
##################################################################

psql ${IAS_TEST_DS_POSTGRESQL_DB} <<EOF

   SELECT * FROM ${_table};

EOF
