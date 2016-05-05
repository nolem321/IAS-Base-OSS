g++ -pg  `find out/obj -name *.o` -o out/bin/ias_dm_tests `find ../IAS-CommonLib/out/obj -name *.o`  `find ../IAS-SDOLib/out/obj -name *.o` `find ../IAS-SDOTuscany/out/obj -name *.o` -lxml2 -lpthread
ls -l out/bin/ias_dm_tests 
