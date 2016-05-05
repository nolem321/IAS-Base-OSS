#!/bin/bash

#xterm -e "ias_qs_distributor -s sample; date; sleep 30" &
ias_qs_distributor -s sample&
threads=4

export IAS_DBG_GLOBAL="-stacktrace,+error,-memory,-info,-trace,-system,-memorytrace,-profile"
#export IAS_DBG_GLOBAL="-stacktrace,+error,-memory,-info,-trace,-system,-memorytrace,-profile"

DATADIR=~/Workspaces/IAS-Revised/IAS-LangLib-TestCases/data/input
LANGDIR=~/Workspaces/IAS-Revised/IAS-LangLib-TestCases/data/input

#badprograms=com::examples::big::starterBad01,com::examples::big::starterBad02,com::examples::big::starterBad03,com::examples::big::starterBad04
#badprograms=com::examples::big::starterBad01,com::examples::big::starterBad02,com::examples::big::starterBad03
badprograms=com::examples::big::starterBad01

ias_qs_processor -T1 -i 'shm://sample/Q.KICK?mode=input?timeout=15000' -o shm://sample/T.KICK -l exe:com::examples::big::starterOK &
ias_qs_processor -T1 -i 'shm://sample/Q.LOAD?mode=input?timeout=15000' -o shm://sample/T.TEST -l exe:com::examples::big::loader &
    
for i in {1..5}
 do
  ias_qs_processor -T${threads} -i shm://sample/Q.A.${i}'?mode=input?timeout=10000' -o shm://sample/Q.B.${i} -l match:com::examples::big::progA,${badprograms}&
  ias_qs_processor -T${threads} -i shm://sample/Q.B.${i}'?mode=input?timeout=10000' -o shm://sample/Q.STOP   -l match:com::examples::big::progB&
done
 

ias_qs_processor -T1 -i file:${DATADIR}/timeinfo.xml -o shm://sample/Q.KICK -l fwd&

