#!/bin/bash

killall ias_qs_distributor
killall ias_qs_processor
sleep 2
killall -9 ias_qs_distributor
killall -9 ias_qs_processor
sleep 1

ias_qs_create -c ~/Workspaces/IAS-Revised/IAS-QSystemLib-TestCases/samples/config/new_big_test.qs.xml

ias_qs_change -s sample -a CreateQueue queueDefinition/name=Q.KICK   queueDefinition/size=1

ias_qs_change -s sample -a CreateTopic topicDefinition/name=T.KICK   topicDefinition/size=1
ias_qs_change -s sample -a CreateQueue queueDefinition/name=Q.START  queueDefinition/size=1
ias_qs_change -s sample -a CreateQueue queueDefinition/name=Q.LOAD   queueDefinition/size=10000
ias_qs_change -s sample -a CreateQueue queueDefinition/name=Q.STOP   queueDefinition/size=1

ias_qs_change -s sample -a CreateTopic topicDefinition/name=T.TEST  topicDefinition/size=20000

 ias_qs_change -s sample -a CreateSubscription topicName=T.KICK queueName=Q.START
 ias_qs_change -s sample -a CreateSubscription topicName=T.KICK queueName=Q.LOAD
 
for i in {1..5} 
do
 ias_qs_change -s sample -a CreateQueue queueDefinition/name=Q.A.${i} queueDefinition/size=20000
 ias_qs_change -s sample -a CreateQueue queueDefinition/name=Q.B.${i} queueDefinition/size=20000
 ias_qs_change -s sample -a CreateSubscription topicName=T.TEST queueName=Q.A.${i}
  
done

ias_qs_status -s sample 2>&1|grep -B 3 -A 30 Topic
