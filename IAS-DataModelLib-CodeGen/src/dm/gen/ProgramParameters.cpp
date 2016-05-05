/*
 * File: IAS-DataModelLib-CodeGen/src/dm/gen/ProgramParameters.cpp
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
#include "../../dm/gen/ProgramParameters.h"
#include <commonlib/commonlib.h>

namespace IAS {
namespace DM {
namespace Gen {

/*************************************************************************/
ProgramParameters::ProgramParameters(int argc, char* argv[]){
	IAS_TRACER;

	::IAS::ProgramParameters::init(argc,argv,"hx:d:sn:");

	if(hmIndicators.count('n')){
		String strValue(hmValues.find('n')->second);
		TypeTools::Tokenize(strValue,lstNamespaces,',');
	}

}
/*************************************************************************/
ProgramParameters::~ProgramParameters() throw(){
	IAS_TRACER;
}
/*************************************************************************/
const String& ProgramParameters::getXSDFile() const{
	IAS_TRACER;

	if(hmIndicators.count('x') > 0)
		return hmValues.find('x')->second;

	IAS_THROW(BadUsageException("XSD file not provided."))
}
/*************************************************************************/
const String& ProgramParameters::getOutputDir() const{
	IAS_TRACER;

	std::cerr<<"T:"<<hmValues.count('d')<<std::endl;
	if(hmIndicators.count('d')>0)
		return hmValues.find('d')->second;

	IAS_THROW(BadUsageException("Output directory not provided."))

}
/*************************************************************************/
bool  ProgramParameters::isSingleDataObjectFile() const{
	IAS_TRACER;
	return hmIndicators.count('s') > 0;
}
/*************************************************************************/
const StringList& ProgramParameters::getNamespacesToBeGenerated()const{
	return lstNamespaces;
}
/*************************************************************************/
}
}
}
