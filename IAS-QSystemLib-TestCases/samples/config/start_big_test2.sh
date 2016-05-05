#!/bin/bash

ias_qs_distributor -s sample&

threads=4

export IAS_DBG_GLOBAL="-stacktrace,+error,-memory,-info,-trace,-system,-profile"

DATADIR=~/Workspaces/IAS-Revised/IAS-LangLib-TestCases/data/input
LANGDIR=~/Workspaces/IAS-Revised/IAS-LangLib-TestCases/data/input

#badprograms=com::examples::big::starterBad01,com::examples::big::starterBad02,com::examples::big::starterBad03,com::examples::big::starterBad04
#badprograms=com::examples::big::starterBad01,com::examples::big::starterBad02,com::examples::big::starterBad03
badprograms=com::examples::big::starterBad01


ias_qs_processor -T1 -i 'shm://sample/Q.KICK?mode=input?timeout=60000' -o shm://sample/T.KICK -l exe:com::examples::big::starterOK 2>/tmp/starter.log &
ias_qs_processor -T1 -i 'shm://sample/Q.LOAD?mode=input?timeout=60000' -o shm://sample/T.TEST -l exe:com::examples::big::loader 2>/tmp/loader.log &
export IAS_REGION=Y
    
      
for i in {1..5}
 do

  ias_qs_processor -T${threads} -i shm://sample/Q.A.${i}'?mode=input?timeout=60000' -o shm://sample/Q.B.${i} -l match:com::examples::big::progA,${badprograms} 2>/tmp/progA.${i}.log &
  ias_qs_processor -T${threads} -i shm://sample/Q.B.${i}'?mode=input?timeout=60000' -o shm://sample/Q.STOP   -l match:com::examples::big::progB 2>/tmp/progB.${i}.log &

#	for j in {1..`echo ${threads}`}
#	 do 	    
#		ias_qs_processor -T1 -i shm://sample/Q.A.${i}'?mode=input?timeout=60000' -o shm://sample/Q.B.${i} -l match:com::examples::big::progA,${badprograms} 2>/tmp/progA.${i}.log &
#		ias_qs_processor -T1 -i shm://sample/Q.B.${i}'?mode=input?timeout=60000' -o shm://sample/Q.STOP   -l match:com::examples::big::progB 2>/tmp/progB.${i}.log &
#	 done
	 

done

ias_qs_processor -T1 -i file:${DATADIR}/timeinfo.xml -o shm://sample/Q.KICK -l fwd 2>/tmp/kicker.log
echo Started: `ps -ef|grep ias_qs_processor|wc -l`

