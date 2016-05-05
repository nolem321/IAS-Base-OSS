/*
 * File: IAS-LangLib/src/lang/model/ExternalProgramNode.h
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
#ifndef _IAS_AS_Lang_Model_ExternalProgramNode_H_
#define _IAS_AS_Lang_Model_ExternalProgramNode_H_

#include <commonlib/commonlib.h>
#include "ProgramNode.h"

namespace IAS {
namespace Lang {
namespace Model {

/*************************************************************************/
/** The class. */
 class ExternalProgramNode : public ProgramNode {

 public:

	virtual ~ExternalProgramNode() throw();

	const String& getLibrary()const { return strLibrary; };
	const String& getModule()const { return strModule; };
	const String& getSymbol()const { return strSymbol; };

	const StringList& getParameters()const { return lstParameters; };

protected:
	ExternalProgramNode(Dec::QualifiedNameNode*    pQualifiedNameNode,
			   	   	    const String&              strExternalDefinition,
			   	   	    Dec::ParametersNode*       pParametersNode,
			   	   	    const StringList&          lstParamters);

	ExternalProgramNode(Dec::QualifiedNameNode*    pQualifiedNameNode,
				   	   	const String&              strExternalDefinition,
				   	   	Dec::ParametersNode*       pParametersNode,
				   	    Dec::DeclarationNode*      pResultDeclartionNode,
				   	    const StringList&          lstParameters);

	String strLibrary;
	String strModule;
	String strSymbol;

	StringList lstParameters;

	void init(const String& strExternalDefinition);

	friend class ::IAS::Factory<ExternalProgramNode>;
};

/*************************************************************************/
}
}
}


#endif /* _IAS_AS_Lang_Model_ExternalProgramNode_H_ */
