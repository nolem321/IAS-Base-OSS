/*
 * File: IAS-LangLib/src/lang/model/Model.h
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
#ifndef _IAS_AS_Lang_Model_MODEL_H_
#define _IAS_AS_Lang_Model_MODEL_H_

#include <commonlib/commonlib.h>

#include <map>
#include <list>

#include "dec/TypeDefinitionNode.h"
#include "dec/NamespaceDeclarationNode.h"

#include <lang/tools/parser/SourceLocation.h>

namespace IAS {
namespace Lang {
namespace Model {

class ProgramNode;

/*************************************************************************/
/** The class. */
 class Model : public Tools::Parser::ISourceLocationStore {
public:

	virtual ~Model() throw();

	void addTypeDefinition(Dec::TypeDefinitionNode* pTypeDefinitionNode);
	void addNamespaceAliasDefinition(Dec::NamespaceDeclarationNode* pNamespaceDeclarationNode);

	const Dec::TypeDefinitionNode* getTypeDefinitionNode(const String& strName,
														 const String& strNamespace)const;

	bool  getNamespaceAliasDefinition(const String& strAlias,
										 String& strNamespace)const;

	void addProgram(ProgramNode* pProgramNode);

	typedef std::list<const ProgramNode*> ProgramList;
	const ProgramList& getPrograms(const String& strName)const;
	void getAllPrograms(ProgramList& refOutput)const;

	 virtual Tools::Parser::SourceLocation::SourceID registerSource(const String& strName);
	 virtual const String& resolve(Tools::Parser::SourceLocation::SourceID iID)const;

	 static void RegisterBuildInTypes();

protected:
	Model();

	typedef HashMapWithStringKey<ProgramList>        ProgramListsMap;
	typedef HashMapStringPairToPointer<Dec::TypeDefinitionNode>    TypeDefinitionListsMap;
	typedef HashMapStringToPointer<Dec::NamespaceDeclarationNode>  NamespaceDeclarationNodeMap;

	ProgramListsMap                              	  hmProgramLists;
	TypeDefinitionListsMap						 	  hmTypes;
	NamespaceDeclarationNodeMap					 	  hmNamespaceDeclarations;

	typedef IAS_DFT_FACTORY<ProgramNode>::PtrHoldersCollection ProgramNodesCollection;
	ProgramNodesCollection phcProgramNodes;


	typedef HashMapWithStringKey<Tools::Parser::SourceLocation::SourceID>        SourcesMap;
	typedef std::map<Tools::Parser::SourceLocation::SourceID,String>             SourcesByIDMap;

	SourcesMap									  hmSources;
	SourcesByIDMap								  hmSourcesByID;

	friend class ::IAS::Factory<Model>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_AS_Lang_Model_MODEL_H_ */
