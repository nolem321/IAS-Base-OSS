/*
 * File: IAS-LangLib/src/lang/model/ExternalProgramNode.cpp
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
#include "ExternalProgramNode.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "dec/ParametersNode.h"

namespace IAS {
namespace Lang {
namespace Model {


/*************************************************************************/
ExternalProgramNode::ExternalProgramNode(Dec::QualifiedNameNode*        pQualifiedNameNode,
										 const String&                  strExternalDefinition,
		  	  	  	  	  	  	  	  	 Dec::ParametersNode*           pParametersNode,
		  	  	  	  	  	  	  	  	 const StringList&          lstParameters):
 ProgramNode(pQualifiedNameNode,pParametersNode,true),
 lstParameters(lstParameters){
IAS_TRACER;

	init(strExternalDefinition);
}
/*************************************************************************/
ExternalProgramNode::ExternalProgramNode(Dec::QualifiedNameNode*        pQualifiedNameNode,
										const String&                   strExternalDefinition,
		  	  	  	  	  	  	  	  	 Dec::ParametersNode*           pParametersNode,
		  	  	  	  	  	  	  	  	 Dec::DeclarationNode*          pResultDeclartionNode,
		  	  	  	  	  	  	  	  	 const StringList&          lstParameters):
ProgramNode(pQualifiedNameNode,pParametersNode,true),
lstParameters(lstParameters){

	IAS_TRACER;

	init(strExternalDefinition);
	addResultDeclarationNode(pResultDeclartionNode);
}
/*************************************************************************/
ExternalProgramNode::~ExternalProgramNode() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void ExternalProgramNode::init(const String& strExternalDefinition){

	IAS_TRACER;

	StringList lstTmp;

	TypeTools::Tokenize(strExternalDefinition,lstTmp,':');

	StringList::const_iterator it=lstTmp.begin();

	switch(lstTmp.size()){
		case 2:
			strLibrary=*it++;
			strSymbol=*it;
			break;

		case 3:
			strLibrary=*it++;
			strModule=*it++;
			strSymbol=*it;
			break;
		default:

			IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isError(),"["<<strExternalDefinition<<"], no. tokens = "<<lstTmp.size());
			IAS_THROW(BadUsageException("Invalid external program specification."));
	}

}
/*************************************************************************/
}
}
}
