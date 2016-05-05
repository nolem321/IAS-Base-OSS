#!/bin/bash

function sedsource (){

sedfile.sh "${1}" ${2}.h
sedfile.sh "${1}" ${2}.cpp
}

for i in Boolean Float Integer DateTime Date Time
do

cp String.h ${i}.h
cp String.cpp ${i}.cpp

sedsource "/URI/ s/::IAS::String/__STRING__/g" ${i}
sedsource "s/String/${i}/g" ${i}
sedsource "/URI/ s/__STRING__/::IAS::String/g" ${i}
done

sedsource "s/::IAS::Boolean/bool/g" Boolean
sedsource "s/::IAS::Integer/int/g" Integer

sedsource "s/bool\&/bool/g" Boolean
sedsource "s/int\&/int/g" Integer
sedsource "s/Float\&/Float/g" Float

