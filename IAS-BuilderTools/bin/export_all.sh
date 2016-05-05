#!/bin/bash
 
script_dir=$(dirname $(readlink -f ${0}))


function help(){
echo >&2
echo "Usage: ">&2
echo $(basename ${0}) [options] maketargets... >&2
echo "Options: ">&2
echo "  -h               This help.">&2
echo "  -f <projectlist> File containing ordered project names.">&2
echo "  -s <svnurl>      SVN URL.">&2
exit
}

projects_file=$script_dir/../projects.txt

while getopts ":s:" opt; do
  case $opt in
    s)
      export svn_repo=$OPTARG
      ;;
    f)
      projects_file=$OPTARG
      ;;
    j)
      make_j=-j8
      ;; 
    \?)
      echo "Invalid option: -$OPTARG" >&2
      help
      ;;
    :)
      echo "Option -$OPTARG requires an argument." >&2
      help
      ;;
  esac
done


if [[ ! -f $projects_file ]] ; then
  echo >&2
  echo "Cannot read the list of projects from: " $projects_file >&2
  help
fi


cat $projects_file | while read f
do
echo '************************************************************************'
echo '****' Project: $f
echo '************************************************************************'

echo svn export ${svn_repo}/${f}
svn export ${svn_repo}/${f}

done

echo
echo All done !!!
echo


