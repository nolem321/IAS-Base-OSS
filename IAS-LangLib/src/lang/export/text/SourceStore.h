/*
 * File: IAS-LangLib/src/lang/interpreter/json/SourceStore.h
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
#ifndef _IAS_Lang_Export_Text_SourceStore_H_
#define _IAS_Lang_Export_Text_SourceStore_H_

#include <commonlib/commonlib.h>
#include <dm/datamodel.h>

namespace IAS {
namespace Lang {
namespace Model {
namespace Dec{
class TypeDefinitionNode;
}
class Model;
class ProgramNode;
}

namespace Export {
namespace Exe{
class Program;
namespace Expr{
class ExprList;
}
}
namespace Extern{
class ModuleStore;
}

namespace Text {
/*************************************************************************/
/** The SourceStore class.
 *
 */
class SourceStore {
public:

	virtual ~SourceStore() throw();


	String exportSource(const ::IAS::Lang::Model::ProgramNode* pProgramNode);
	String exportDeclaration(const ::IAS::Lang::Model::ProgramNode* pProgramNode);

  String getExportedNamespace(const String& strNamespace)const;

	void build(const Model::ProgramNode* pProgramNode);

	void buildSources();

	typedef std::list<const DM::Type*> TypeList;

	const ::IAS::Lang::Model::ProgramNode* findMatch(const String&   strName,
				   	   	   	   	   	   	      	   	 const TypeList& lstParameters)const;


protected:

	SourceStore(const ::IAS::Lang::Model::Model* pModel, const DM::DataFactory *pDataFactory);

	const ::IAS::Lang::Model::Model* pModel;
	const DM::DataFactory *pDataFactory;

	struct Entry{
		String strDeclaration;
		String strSource;
	};

	typedef HashMap< const ::IAS::Lang::Model::ProgramNode*,
						Entry >  ExportSourceMap;

	ExportSourceMap hmExportSources;

	bool matchParameteres(const ::IAS::Lang::Model::ProgramNode* pProgramNode,
						  const TypeList& lstTypes)const;

	friend class ::IAS::Factory<SourceStore>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_Lang_Export_SourceStore_H_ */
