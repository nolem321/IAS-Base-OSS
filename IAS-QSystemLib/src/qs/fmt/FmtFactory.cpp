/*
 * File: IAS-QSystemLib/src/qs/fmt/FmtFactory.cpp
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
#include "FmtFactory.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "XMLFormatter.h"
#include "JSONFormatter.h"
#include "JSONPureFormatter.h"
#include "URLEncodeFormatter.h"
#include "StringFormatter.h"
#include "RawFormatter.h"
#include "TemplateFormatter.h"
#include "DelimitedFormatter.h"

using namespace ::org::invenireaude::qsystem;

namespace IAS {
namespace QS {
namespace Fmt {
/*************************************************************************/
FmtFactory::FmtFactory(const DM::DataFactory* pDataFactory):pDataFactory(pDataFactory){
	IAS_TRACER;

	IAS_CHECK_IF_NULL(pDataFactory);

	hmFormatters["XML"]=IAS_DFT_FACTORY<XMLFormatter>::Create(pDataFactory);
	hmFormatters["JSON"]=IAS_DFT_FACTORY<JSONFormatter>::Create(pDataFactory);
	hmFormatters["JSONPure"]=IAS_DFT_FACTORY<JSONPureFormatter>::Create(pDataFactory);
	hmFormatters["URLEnc"]=IAS_DFT_FACTORY<URLEncodeFormatter>::Create(pDataFactory);
	hmFormatters["String"]=IAS_DFT_FACTORY<StringFormatter>::Create(pDataFactory);
	hmFormatters["Raw"]=IAS_DFT_FACTORY<RawFormatter>::Create(pDataFactory);
	hmFormatters["Template"]=IAS_DFT_FACTORY<TemplateFormatter>::Create(pDataFactory);
	hmFormatters["DEL"]=IAS_DFT_FACTORY<DelimitedFormatter>::Create(pDataFactory);
}
/*************************************************************************/
FmtFactory::~FmtFactory(){
	IAS_TRACER;
	hmFormatters.clear();
	hmLibraries.clear();
}
/*************************************************************************/
Formatter* FmtFactory::getFormatter(const String& strSpecs)const{
	IAS_TRACER;

	FmtFactory* this_m=const_cast<FmtFactory*>(this);

	Mutex::Locker locker(this_m->theMutex);

	if(hmFormatters.count(strSpecs) == 0){

		try{
		String strTmp=String("qsfmt_")+strSpecs+".so";

		this_m->hmLibraries[strSpecs]=IAS_DFT_FACTORY<SYS::DynamicLibrary>::Create(strTmp);

		void *p=this_m->hmLibraries.at(strSpecs)->getSymbol(String("_ias_qs_fmt_")+strSpecs);

		this_m->hmFormatters[strSpecs]=(*(ExternalFormatterFactoryPtr)p)(pDataFactory);
		}catch(Exception& e){
			IAS_THROW(BadUsageException(String("Unknown formatter or dynamic library cannot be loaded: ")+strSpecs + ":" +  e.getName() + " " + e.getInfo()));
		}
	}

	if(hmFormatters.count(strSpecs) == 0)
		IAS_THROW(ItemNotFoundException(strSpecs+" - formatter not found"));

	return const_cast<FormatterMap&>(hmFormatters).at(strSpecs);
}
/*************************************************************************/
}
}
}
