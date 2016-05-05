/*
 * File: IAS-CommonLib-TestCases/src/testcases/TCTime.cpp
 * 
 * Copyright (C) 2015, Albert Krzymowski
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "commonlib/commonlib.h"

#include "TCTime.h"

#include <iomanip>
#include <unistd.h>

namespace IAS{
namespace TCT{

/*************************************************************************/
TCTime::TCTime(TestSuite* pTestSuite):theTestRunner(this){
	IAS_TRACER;
	init(pTestSuite);
}
/*************************************************************************/
TCTime::~TCTime() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void TCTime::init(TestSuite* pTestSuite){	
	IAS_TRACER;

	theTestRunner.addCase("Time",&::IAS::TCT::TCTime::caseTime);
	theTestRunner.addCase("Date",&::IAS::TCT::TCTime::caseDate);
	theTestRunner.addCase("Sample",&::IAS::TCT::TCTime::caseTimesample);
	theTestRunner.addCase("TSSimple",&::IAS::TCT::TCTime::caseTimestampConversionsSimple);
	theTestRunner.addCase("TSZones",&::IAS::TCT::TCTime::caseTimestampConversionsZones);

	TestUnit::init("TCTime",&theTestRunner,pTestSuite);
}

/*************************************************************************/
void TCTime::caseTimesample(){
	IAS_TRACER;

	IAS::TimeSample ts(true);

	sleep(1);
	long iResult;

	if( (iResult=(ts.getSample() - 1000000)) > 5000)
		IAS_THROW(InternalException(TypeTools::IntToString(iResult)+"TimeSample - suspicious difference."));
	ts.start();

	sleep(1);
	if( (iResult=(ts.getSample() - 1000000)) > 5000)
		IAS_THROW(InternalException(TypeTools::IntToString(iResult)+"TimeSample - suspicious difference."));

}
/*************************************************************************/
void TCTime::testTimestampConversion(const String& strInput,
			 	 	 	 	 	     const String& strFormat){
	IAS_TRACER;

	Timestamp ts;

	ts.fromString(strInput,strFormat);
	String strOutput(ts.toString(strFormat));

	if(true)
		std::cout<<strFormat<<" : "<<strInput<<":"<<strOutput<<std::endl;

	if(strInput.compare(strOutput))
		IAS_THROW(InternalException(String("Conversion error:")+strInput+":"+strOutput+":"+strFormat));

}
/*************************************************************************/
void TCTime::testTimestampConversion(const String& strInput,
 	 	  	  	  	  	  	  	  	 const String& strIFormat,
 	 	  	  	  	  	  	  	  	 const String& strOutput,
 	 	  	  	  	  	  	  	  	 const String& strOFormat){
	IAS_TRACER;

	Timestamp ts;

	ts.fromString(strInput,strIFormat);
	String strTmp(ts.toString(strOFormat));

	if(true){
		unsigned short iYear;
		unsigned short iMon;
		unsigned short iDay;
		unsigned short iHour;
		unsigned short iMin;
		unsigned short iSec;
		unsigned int ifSec;
		ts.getDateTime(iYear,iMon,iDay,iHour,iMin,iSec,ifSec);
		std::cout<<strTmp<<","<<iYear<<std::endl;
	}
	if(strTmp.compare(strOutput))
		IAS_THROW(InternalException(String("Conversion error (2) :")+strInput+":"+strTmp+":"+strOFormat));

}
/*************************************************************************/
void TCTime::caseTimestampConversionsSimple(){
	IAS_TRACER;

	tzset();

	testTimestampConversion("20110102","%Y%m%d");
	testTimestampConversion("20111224","%Y%m%d");
	testTimestampConversion("2011/06/24","%Y/%m/%d");

	testTimestampConversion("10:11:12","%H:%M:%S");
	testTimestampConversion("2011-06-24T10","%Y-%m-%dT%H");
	testTimestampConversion("2011-06-24T10:11","%Y-%m-%dT%H:%M");
	testTimestampConversion("2011-06-24T10:11:12","%Y-%m-%dT%H:%M:%S");

	testTimestampConversion("2014-09-19T11:51:35.851","%Y-%m-%dT%H:%M:%S%F");

	testTimestampConversion("2011-03-24T10:11:12","%Y-%m-%dT%H:%M:%S",
			                "2011 Mar 24 10:11:12","%Y %b %d %H:%M:%S");

	testTimestampConversion("2011 Mar 24 10:11:12","%Y %b %d %H:%M:%S",
			                "2011-03-24T10:11:12","%Y-%m-%dT%H:%M:%S");

}
/*************************************************************************/
void TCTime::caseTimestampConversionsZones(){
	IAS_TRACER;

	StringStream ssTmp;
	ssTmp<<"2011-06-24T10:11:12";
	ssTmp<<(timezone < 0 ? "-" : "+");
	ssTmp<<std::setfill('0');
	ssTmp<<std::setw(2)<<abs(timezone/3600);
	String strTmp(ssTmp.str());
	std::cout<<strTmp<<std::endl;
	testTimestampConversion(strTmp,"%Y-%m-%dT%H:%M:%S%Z");

	testTimestampConversion("2011-06-24T10:11:12","%Y-%m-%dT%H:%M:%S",strTmp,"%Y-%m-%dT%H:%M:%S%Z");
	testTimestampConversion("2011-06-24T10:11:12","%Y-%m-%dT%H:%M:%S%Z",strTmp,"%Y-%m-%dT%H:%M:%S%Z");
	testTimestampConversion(strTmp,"%Y-%m-%dT%H:%M:%S%Z",strTmp,"%Y-%m-%dT%H:%M:%S%Z");

}
/*************************************************************************/
void TCTime::caseDate(){
	IAS_TRACER;


	Date d1("2011-01-12");
	Date d2("2011-01-12");
	Date d3("2011-02-23");

	if(! (d1 == d2))
		IAS_THROW(InternalException(String("Date comparison error 1.")));

	if(d1 != d2)
		IAS_THROW(InternalException(String("Date comparison error 2.")));

	if(d1 == d3)
		IAS_THROW(InternalException(String("Date comparison error 3.")+d1.toString()+d3.toString()));

	if(! (d1 != d3))
		IAS_THROW(InternalException(String("Date comparison error 4.")));

	Timestamp tsTmp(d1);

	if(! (d1 == tsTmp))
		IAS_THROW(InternalException(String("Date comparison error 5.")));


}
/*************************************************************************/
void TCTime::caseTime(){

	IAS_TRACER;

	Time t1("11:22:33");
	Time t2("11:22:33");
	Time t3("22:11:33");

	if(! (t1 == t2))
		IAS_THROW(InternalException(String("Time comparison error 1.")));

	if(t1 != t2)
		IAS_THROW(InternalException(String("Time comparison error 2.")));

	if(t1 == t3)
		IAS_THROW(InternalException(String("Time comparison error 3.")));

	if(! (t1 != t3))
		IAS_THROW(InternalException(String("Time comparison error 4.")));

	Timestamp tsTmp(t1);

	if(! (t1 == tsTmp))
		IAS_THROW(InternalException(String("Time comparison error 5.")));


	t1.setTime(22,11,33);

	if(t1 != t3)
		IAS_THROW(InternalException(String("Time comparison error 6.")));

	t1.fromTimeString("22:11:33");

	if(t1 != t3)
		IAS_THROW(InternalException(String("Time comparison error 7.")));


}
/*************************************************************************/
} /* namespace TCT */
} /* namespace IAS */
