/*
 * File: IAS-CommonLib/src/commonlib/tools/ProgramParameters.cpp
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
#include "ProgramParameters.h"

#include "../logger/logger.h"

#include "../exception/BadUsageException.h"

#ifndef _AIX
#include <getopt.h>
#endif

namespace IAS {

/*************************************************************************/
ProgramParameters::ProgramParameters() throw(){
	IAS_TRACER;
}

/*************************************************************************/
ProgramParameters::~ProgramParameters() throw(){
	IAS_TRACER;
}
/*************************************************************************/
const ProgramParameters::ParametersList& ProgramParameters::getParameters() const{
	IAS_TRACER;
	return lstParameters;
}
/*************************************************************************/
const String& ProgramParameters::getExeName() const{
	return strExeName;
}
/*************************************************************************/
void ProgramParameters::init(int argc, char* argv[], const String& strArgSpec){
	IAS_TRACER;

	int c;

	while( (c = getopt(argc,argv, strArgSpec.c_str() )) != -1 )
	 switch(c){

		case ':':
			IAS_THROW(BadUsageException("Missing option value."));
			break;

		case '?':
			IAS_THROW(BadUsageException("Unexpected program argument."));
			break;

		default:

			hmIndicators[c]=true;

			if(optarg != NULL){
				hmValues[c]=optarg;
				IAS_LOG(IAS::LogLevel::INSTANCE.isInfo(),"["<<c<<"]="<<optarg);
			}else{
				IAS_LOG(IAS::LogLevel::INSTANCE.isInfo(),"["<<c<<"]");
			}
	}

	for(int iIdx = optind; iIdx<argc; iIdx++)
		lstParameters.push_back(String(argv[iIdx]));

	strExeName=argv[0];
	String::size_type iPos = strExeName.find_last_of('/');
	if(iPos != String::npos)
		strExeName = strExeName.substr(iPos+1);

}
/*************************************************************************/
}
