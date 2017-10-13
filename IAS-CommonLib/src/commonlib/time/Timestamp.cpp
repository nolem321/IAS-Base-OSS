/*
 * File: IAS-CommonLib/src/commonlib/time/Timestamp.cpp
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
#include "Timestamp.h"

#include <commonlib/commonlib.h>

#include <iomanip>
#include <langinfo.h>

namespace IAS {

struct Locale{

	Locale();

	 std::vector<std::string>             tabMonths;
	 std::vector<std::string>             tabDays;

	 ias_std_unordered_map<std::string,int>  hmMonths;
	 ias_std_unordered_map<std::string,int>  hmDays;

};

Locale TheLocale;

const String& Timestamp::CDftDateTimeFormat("%Y-%m-%dT%H:%M:%S%F%Z");
const String& Timestamp::CDftTimeFormat("%H:%M:%S");
const String& Timestamp::CDftDateFormat("%Y-%m-%d");
/*************************************************************************/
Locale::Locale(){

	tabMonths.push_back(::nl_langinfo(ABMON_1));
	tabMonths.push_back(::nl_langinfo(ABMON_2));
	tabMonths.push_back(::nl_langinfo(ABMON_3));
	tabMonths.push_back(::nl_langinfo(ABMON_4));
	tabMonths.push_back(::nl_langinfo(ABMON_5));
	tabMonths.push_back(::nl_langinfo(ABMON_6));
	tabMonths.push_back(::nl_langinfo(ABMON_7));
	tabMonths.push_back(::nl_langinfo(ABMON_8));
	tabMonths.push_back(::nl_langinfo(ABMON_9));
	tabMonths.push_back(::nl_langinfo(ABMON_10));
	tabMonths.push_back(::nl_langinfo(ABMON_11));
	tabMonths.push_back(::nl_langinfo(ABMON_12));

	int iIdx=0;
	for( std::vector<std::string>::const_iterator it=tabMonths.begin();
			it != tabMonths.end(); it++){
		hmMonths[*it]=iIdx++;
	}

	tabDays.push_back(::nl_langinfo(ABDAY_1));
	tabDays.push_back(::nl_langinfo(ABDAY_2));
	tabDays.push_back(::nl_langinfo(ABDAY_3));
	tabDays.push_back(::nl_langinfo(ABDAY_4));
	tabDays.push_back(::nl_langinfo(ABDAY_5));
	tabDays.push_back(::nl_langinfo(ABDAY_6));
	tabDays.push_back(::nl_langinfo(ABDAY_7));

	for( std::vector<std::string>::const_iterator it=tabDays.begin();
			it != tabDays.end(); it++){
		hmDays[*it]=iIdx++;
	}

}
/*************************************************************************/
Timestamp::Timestamp(bool bCurrentSystemDate) {

	if (bCurrentSystemDate)
		readSystemTimestamp();
	else
		theValue.tv_sec = theValue.tv_usec = 0;
}
/*************************************************************************/
Timestamp::Timestamp(const Timestamp& other) :
		theValue(other.theValue) {
}
/*************************************************************************/
Timestamp::Timestamp(const String& strValue) {
		fromDateTimeString(strValue);
}
/*************************************************************************/
Timestamp::~Timestamp() throw () {
}
/*************************************************************************/
void Timestamp::readSystemTimestamp() {
	gettimeofday(&theValue, NULL);
}
/*************************************************************************/
void Timestamp::assign(const Timestamp& other) {
	theValue = other.theValue;
}
/*************************************************************************/
void Timestamp::setDate( short iYear,  short iMonth,
		 short iDay) {
	IAS_TRACER;

	struct tm tmpTime;
	memset(&tmpTime,0,sizeof(struct tm));
	localtime_r(&theValue.tv_sec,&tmpTime);

	tmpTime.tm_year=iYear-1900;
	tmpTime.tm_mon=iMonth-1;
	tmpTime.tm_mday=iDay;

	tmpTime.tm_isdst=-1;
	theValue.tv_sec=mktime(&tmpTime);
}
/*************************************************************************/
void Timestamp::setTime( short iHour,  short iMin,
		 short iSec,  int iUSec) {
	IAS_TRACER;

	struct tm tmpTime;
	memset(&tmpTime,0,sizeof(struct tm));
	localtime_r(&theValue.tv_sec,&tmpTime);

	tmpTime.tm_hour=iHour;
	tmpTime.tm_min=iMin;
	tmpTime.tm_sec=iSec;

	tmpTime.tm_isdst=-1;
	theValue.tv_sec=mktime(&tmpTime);

	theValue.tv_usec=iUSec;
}
/*************************************************************************/
void Timestamp::setDateTime( short iYear,  short iMonth,  short iDay,
							 short iHour,  short iMin, short iSec,  int iUSec) {
	IAS_TRACER;

	struct tm tmpTime;
	memset(&tmpTime,0,sizeof(struct tm));
	localtime_r(&theValue.tv_sec,&tmpTime);

	tmpTime.tm_year=iYear-1900;
	tmpTime.tm_mon=iMonth-1;
	tmpTime.tm_mday=iDay;

	tmpTime.tm_hour=iHour;
	tmpTime.tm_min=iMin;
	tmpTime.tm_sec=iSec;

	tmpTime.tm_isdst=-1;
	theValue.tv_sec=mktime(&tmpTime);

	theValue.tv_usec=iUSec;
}
/*************************************************************************/
void Timestamp::getDate( short &iYear,  short &iMonth,
		 short &iDay) const {
	IAS_TRACER;

	struct tm tmpTime;
	memset(&tmpTime,0,sizeof(struct tm));
	localtime_r(&theValue.tv_sec,&tmpTime);

	iYear=tmpTime.tm_year+1900;
	iMonth=tmpTime.tm_mon+1;
	iDay=tmpTime.tm_mday;

}
/*************************************************************************/
void Timestamp::getTime( short &iHour,  short &iMin, short &iSec,  int& iUSec) const {
	IAS_TRACER;

	struct tm tmpTime;
	memset(&tmpTime,0,sizeof(struct tm));
	localtime_r(&theValue.tv_sec,&tmpTime);

	iHour=tmpTime.tm_hour;
	iMin=tmpTime.tm_min;
	iSec=tmpTime.tm_sec;
	iUSec=theValue.tv_usec;
}
/*************************************************************************/
void Timestamp::getDateTime( short &iYear,  short &iMonth,	 short &iDay,
							 short &iHour,  short &iMin,  short &iSec,  int& iUSec) const {
	IAS_TRACER;

	struct tm tmpTime;
	memset(&tmpTime,0,sizeof(struct tm));
	localtime_r(&theValue.tv_sec,&tmpTime);

	iYear=tmpTime.tm_year+1900;
	iMonth=tmpTime.tm_mon+1;
	iDay=tmpTime.tm_mday;

	iHour=tmpTime.tm_hour;
	iMin=tmpTime.tm_min;
	iSec=tmpTime.tm_sec;
	iUSec=theValue.tv_usec;

}
/*************************************************************************/
String Timestamp::toString() const {
	IAS_TRACER;
	return toDateTimeString();
}
/*************************************************************************/
String Timestamp::toDateTimeString() const {
	IAS_TRACER;
	return toString("%Y-%m-%dT%H:%M:%S%F"/*//TODO (L) timestamp zones CDftDateTimeFormat*/);
}
/*************************************************************************/
String Timestamp::toTimeString() const {
	IAS_TRACER;
	return toString(CDftTimeFormat);
}
/*************************************************************************/
String Timestamp::toDateString() const {
	IAS_TRACER;
	return toString(CDftDateFormat);
}
/*************************************************************************/
String Timestamp::toString(const String& strFormat) const {
	IAS_TRACER;

	StringStream ssValue;
	ssValue<<std::setfill('0');
	struct tm tmpTime;

	memset(&tmpTime,0,sizeof(struct tm));
	localtime_r(&theValue.tv_sec,&tmpTime);

	tmpTime.tm_year+=1900;
	tmpTime.tm_mon+=1;

	bool bReplacement=false;

	for(String::const_iterator it=strFormat.begin();
			it != strFormat.end();
			it++) {

		if(!bReplacement) {

			if(*it == '%') {
				bReplacement=true;
			} else {
				ssValue<<*it;
			}

		} else {
			bReplacement=false;
			switch(*it) {
				case '%': ssValue<<'%'; break;
				case 'y': ssValue<<std::setw(2)<<(tmpTime.tm_year%100); break;
				case 'Y': ssValue<<std::setw(4)<<(tmpTime.tm_year); break;
				case 'm': ssValue<<std::setw(2)<<(tmpTime.tm_mon); break;
				case 'b': ssValue<<(TheLocale.tabMonths[tmpTime.tm_mon-1]); break;
				case 'a': ssValue<<(TheLocale.tabDays[tmpTime.tm_wday-1]); break;
				case 'd': ssValue<<std::setw(2)<<(tmpTime.tm_mday); break;
				case 'H': ssValue<<std::setw(2)<<(tmpTime.tm_hour); break;
				case 'M': ssValue<<std::setw(2)<<(tmpTime.tm_min); break;
				case 'S': ssValue<<std::setw(2)<<(tmpTime.tm_sec); break;
				case 'f': ssValue<<std::setw(CFPrec)<<(theValue.tv_usec/CFRound);break;
				case 'F':
				if(theValue.tv_usec/CFRound > 0)
				ssValue<<"."<<std::setw(CFPrec)<<(theValue.tv_usec/CFRound);
				break;
				case 'u': ssValue<<std::setw(UFPrec)<<(theValue.tv_usec);break;
				case 'U':
				if(theValue.tv_usec > 0)
				ssValue<<"."<<std::setw(UFPrec)<<(theValue.tv_usec);
				break;

				case 'z': ssValue<<(timezone < 0 ? "-" : "+")<<std::setw(2)<<abs(timezone/3600); break;
				case 'Z': if(timezone!=0)ssValue<<(timezone < 0 ? "-" : "+")<<std::setw(2)<<abs(timezone/3600); break;

				default:
				IAS_THROW(BadUsageException(String("Invalid timestamp format:")+strFormat));
			}
		}

	}

	return ssValue.str();
}
/*************************************************************************/
void Timestamp::fromString(const String& strValue) {
	IAS_TRACER;
	fromDateTimeString(strValue);
}
/*************************************************************************/
void Timestamp::fromDateTimeString(const String& strValue) {
	IAS_TRACER;
	fromString(strValue,CDftDateTimeFormat);
}
/*************************************************************************/
void Timestamp::fromDateString(const String& strValue) {
	IAS_TRACER;
	fromString(strValue,CDftDateFormat);
}
/*************************************************************************/
void Timestamp::fromTimeString(const String& strValue) {
	IAS_TRACER;
	fromString(strValue,CDftTimeFormat);
}
/*************************************************************************/
void Timestamp::fromString(const String& strValue, const String& strFormat) {
	IAS_TRACER;
	fromString(strValue,strFormat,false);
}
/*************************************************************************/
void Timestamp::fromString(const String& strValue, const String& strFormat, bool toLocalTime) {
	IAS_TRACER;

	StringStream ssValue(strValue);

	short iZone=0;

	struct tm tmpTime;
	memset(&tmpTime,0,sizeof(struct tm));
	tmpTime.tm_mday=1;
	tmpTime.tm_year=70;
	bool bReplacement=false;
	short iMSec = 0;

	for(String::const_iterator it=strFormat.begin();
			it != strFormat.end();
			it++) {

		if(!bReplacement) {

			if(*it == '%') {
				bReplacement=true;
			} else {

				if(*it != ssValue.get())
				//TODO (M) parse error exception ?
				IAS_THROW(BadUsageException(String("Error in timestamp string(1):")+strFormat+"/"+strValue));
			}

		} else {
			bReplacement=false;

			try {
				switch(*it) {

					case '%': if(ssValue.get() != '%') IAS_THROW(BadUsageException(String("Error in timestamp string(2):")+strFormat+"/"+strValue)); break;

					case 'b':
						tmpTime.tm_mon=readAbbreviatedMonth(ssValue);
						break;

					case 'y':
						tmpTime.tm_year=readNumber(ssValue,2)+2000;
						tmpTime.tm_year-=1900;
						break;

					case 'Y':
						tmpTime.tm_year=readNumber(ssValue,4);
						tmpTime.tm_year-=1900;
					break;

					case 'm':
						tmpTime.tm_mon=readNumber(ssValue,2) - 1;
					break;

					case 'd': tmpTime.tm_mday=readNumber(ssValue,2); break;
					case 'H': tmpTime.tm_hour=readNumber(ssValue,2); break;
					case 'M': tmpTime.tm_min=readNumber(ssValue,2); break;
					case 'S': tmpTime.tm_sec=readNumber(ssValue,2); break;

					case 'f': iMSec=readUSec(ssValue,false);break;
					case 'F': iMSec=readUSec(ssValue,true);break;
					case 'z': iZone=readZone(ssValue,false); break;
					case 'Z': iZone=readZone(ssValue,true); break;

					default:
					IAS_THROW(BadUsageException(String("Invalid timestamp format:")+strFormat));
				}} catch(Exception& e) {
				IAS_THROW(BadUsageException(String("Timestamp parse error(3):")+strFormat+"/"+strValue+e.getInfo()));
			}

		}
	}

	//TODO (L) Time zones

	tmpTime.tm_isdst=-1;


	if (toLocalTime) {
		theValue.tv_sec = Timestamp::gmtToLocal(&tmpTime);
	} else {
		theValue.tv_sec=mktime(&tmpTime);
	}

	theValue.tv_usec=CFRound*iMSec;
}
/*************************************************************************/
short Timestamp::readNumber(std::istream& is, int iLimitDigits) {
	IAS_TRACER;

	short iDigits=0;
	char c;
	short iValue=0;

	while(!is.eof() && (iLimitDigits == 0 || iDigits < iLimitDigits )&& isdigit(c=is.get())) {
		iDigits++;
		iValue=iValue*10 + c - '0';
	}

	if(iLimitDigits > 0 && iDigits != iLimitDigits) {
		StringStream ssMessage;
		ssMessage<<"Bad number of digits:"<<iDigits<<" expected: "<<iLimitDigits<<", eof: "<<is.eof()<<" c="<<c;
		IAS_THROW(BadUsageException(ssMessage.str()));
	}

	if(iDigits != iLimitDigits && !isdigit(c))
	is.unget();

	return iValue;
}
/*************************************************************************/
short Timestamp::readUSec(std::istream& is, bool bOptionalDecimal) {
	IAS_TRACER;

	char c=is.get();

	if(c != '.') {

		if(bOptionalDecimal) {
			is.unget();
			return 0;
		} else {
			IAS_THROW(BadUsageException("Parse error in a timestamp string, decimal point expected."));
		}
	}

	int iDigits=0;
	short iValue=0;

	while( !is.eof() && isdigit(c=is.get()) ) {
		iValue=iValue*10+(c-'0');
		iDigits++;
	}

	if(!isdigit(c))
		is.unget();

	if(iDigits == 0)
		IAS_THROW(BadUsageException("Parse error in a timestamp string, empty fraction."));

	while(iDigits++ < CFPrec)
		iValue*=10;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(), iValue <<"/"<<"000")
	return iValue;
}
/*************************************************************************/
short Timestamp::readZone(std::istream& is, bool bOptionalDecimal) {
	IAS_TRACER;

	short iSign=0;
	short iHours=0;
	short iMinutes=0;

	char c=is.get();

	if(!is.eof()) {

		if(bOptionalDecimal)
		return 0;

		IAS_THROW(BadUsageException("Parse error in a timestamp string, \'+/-\' in zone expected."));
	}

	switch(c) {

		case '+': iSign=1; break;
		case '-': iSign=-1; break;
		case 'Z': return 0;
		default:
		if(bOptionalDecimal) {
			is.unget();
			return 0;
		} else {
			IAS_THROW(BadUsageException("Parse error in a timestamp string, \'+/-/Z\' in zone expected."));
		}
	}

	iHours=readNumber(is,2);

	if(!is.eof()) {

		if((c=is.get()) == ':') {
			iMinutes=readNumber(is,2);
		} else {
			is.unget();
		}

	}

	return iSign*60*iHours+iMinutes;
}
/*************************************************************************/
short Timestamp::readAbbreviatedMonth(std::istream& is) {
	IAS_TRACER;
	std::string strValue;
	char c;
	while( !is.eof() && isalpha(c=is.get()) ) {
		strValue+=c;
	}

	if(!is.eof())
		is.unget();

	if(TheLocale.hmMonths.count(strValue) == 0)
		IAS_THROW(BadUsageException("Parse error in a timestamp string, uknown month abbreviated."));

	return TheLocale.hmMonths.find(strValue)->second;
}
/*************************************************************************/
void Timestamp::toPosixTime(time_t& aValue) const {
	IAS_TRACER;
	aValue=theValue.tv_sec;
}
/*************************************************************************/
void Timestamp::toPosixTime(struct tm& aValue) const {
	IAS_TRACER;
	localtime_r(&theValue.tv_sec, &aValue);
}
/*************************************************************************/
void Timestamp::fromPosixTime(time_t aValue) {
	IAS_TRACER;
	theValue.tv_usec=0;
	theValue.tv_sec=aValue;
}
/*************************************************************************/
void Timestamp::fromPosixTime(struct tm& aValue) {
	IAS_TRACER;
	theValue.tv_sec=mktime(&aValue);
	theValue.tv_usec=0;
}
/*************************************************************************/
Timestamp& Timestamp::operator+=(const Timestamp& other) {
	IAS_TRACER;

	theValue.tv_sec+=other.theValue.tv_sec;
	theValue.tv_usec+=other.theValue.tv_usec;

	if(theValue.tv_usec > 1000000) {
		theValue.tv_sec++;
		theValue.tv_usec-=1000000;
	}

	return *this;
}
/*************************************************************************/
Timestamp& Timestamp::operator-=(const Timestamp& other) {
	IAS_TRACER;

	theValue.tv_sec-=other.theValue.tv_sec;
	theValue.tv_usec-=other.theValue.tv_usec;

	if(theValue.tv_usec < 0) {
		theValue.tv_sec--;
		theValue.tv_usec+=1000000;
	}

	return *this;
}
/*************************************************************************/
Timestamp operator+(const Timestamp& left, const Timestamp& right) {
	IAS_TRACER;
	Timestamp tsResult(left);
	tsResult += right;
	return tsResult;
}
/*************************************************************************/
Timestamp operator-(const Timestamp& left, const Timestamp& right) {
	IAS_TRACER;
	Timestamp tsResult(left);
	tsResult -= right;
	return tsResult;
}
/*************************************************************************/
bool operator==(const Timestamp& left, const Timestamp& right) {
	IAS_TRACER;

	return left.theValue.tv_sec == right.theValue.tv_sec &&
			left.theValue.tv_usec == right.theValue.tv_usec ;

}
/*************************************************************************/
bool operator!=(const Timestamp& left, const Timestamp& right) {
	IAS_TRACER;
	return ! (left == right);
}
/*************************************************************************/
bool operator<=(const Timestamp& left, const Timestamp& right) {
	IAS_TRACER;

	return (left.theValue.tv_sec <= right.theValue.tv_sec) ||
			(left.theValue.tv_sec == right.theValue.tv_sec &&
			 left.theValue.tv_usec <= right.theValue.tv_usec );

}
/*************************************************************************/
bool operator<(const Timestamp& left, const Timestamp& right) {
	IAS_TRACER;

	return (left.theValue.tv_sec < right.theValue.tv_sec) ||
			(left.theValue.tv_sec == right.theValue.tv_sec &&
			 left.theValue.tv_usec < right.theValue.tv_usec );

}
/*************************************************************************/
bool operator>=(const Timestamp& left, const Timestamp& right) {
	IAS_TRACER;

	return (left.theValue.tv_sec >= right.theValue.tv_sec) ||
			(left.theValue.tv_sec == right.theValue.tv_sec &&
			 left.theValue.tv_usec >= right.theValue.tv_usec );

}

/*************************************************************************/
bool operator>(const Timestamp& left, const Timestamp& right) {
	IAS_TRACER;

	return (left.theValue.tv_sec > right.theValue.tv_sec) ||
			(left.theValue.tv_sec == right.theValue.tv_sec &&
			 left.theValue.tv_usec > right.theValue.tv_usec );

}
/*************************************************************************/
time_t Timestamp::gmtToLocal(struct tm* timeinfo){
	 IAS_TRACER;

    timeinfo->tm_isdst = -1; // let the system figure this out for us
    time_t t = mktime(timeinfo) - timezone;

    if (daylight != 0 && timeinfo->tm_isdst != 0) {
        t += 3600;
    }

    return t;
}
}
