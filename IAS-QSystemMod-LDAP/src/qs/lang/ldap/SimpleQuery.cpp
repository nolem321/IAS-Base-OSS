/*
 * File: IAS-QSystemMod-SysMon/src/qs/lang/ldap/SimpleQuery.cpp
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
#include "SimpleQuery.h"

#include <lang/model/dec/ResultDeclarationNode.h>
#include <lang/interpreter/exe/exception/InterpreterProgramException.h>

#include <org/invenireaude/lang/mod/ldap/QueryResult.h>
#include <org/invenireaude/lang/mod/ldap/DataFactory.h>

#include <tools/ldap/Environment.h>


using namespace ::IAS::Lang::Interpreter;
using namespace ::org::invenireaude::lang::mod::ldap;

namespace IAS {
namespace QS  {
namespace Lang {
namespace LDAP  {

/*************************************************************************/
SimpleQuery::SimpleQuery(const DM::Type* pType, const StringList& lstParamaters, const ::IAS::Lang::Interpreter::Extern::ModuleProxy* pModuleProxy){
	IAS_TRACER;

	static Mutex mutex;
	Mutex::Locker locker(mutex);

	if(lstParamaters.size() != 1)
		IAS_THROW(BadUsageException("Connection name expected: in LDAP::SimpleQuery"));

	strConnection = *(lstParamaters.begin());

	IAS::Tools::LDAP::Environment::GetInstance()->lookup(strConnection);

}
/*************************************************************************/
SimpleQuery::~SimpleQuery() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void SimpleQuery::executeExternal(Exe::Context *pCtx) const{
	IAS_TRACER;

	DM::DataObject* pParameters = pCtx->getBlockVariables(0);

	const String strSearchBase = pParameters->getString("strSearchBase");
	const String strQuery = pParameters->getString("strQuery");

	IAS::Tools::LDAP::EntryList lstResult;
	IAS::Tools::LDAP::Environment::GetInstance()->lookup(strConnection)->query(strSearchBase, strQuery, lstResult);

	DM::DataObjectList& lstDMResult(pParameters->getList(IAS::Lang::Model::Dec::ResultDeclarationNode::CStrResultVariable));

	for (IAS::Tools::LDAP::EntryList::const_iterator it = lstResult.begin(); it != lstResult.end(); ++it) {
		Ext::QueryResultPtr dmQueryResult(DataFactory::GetInstance()->createQueryResult());
		const DM::PropertyList& lstProperties(dmQueryResult->getType()->asComplexType()->getProperties());

		for (IAS::Tools::LDAP::Entry::const_iterator itAttr = it->begin(); itAttr != it->end(); ++itAttr) {

			// FIXME: only first value of attribute returned now, it->second.size() >= 1 ?
			String strName = itAttr->first;
			String strValue = itAttr->second.front();

			try {
				dmQueryResult->setString(lstProperties.getProperty(strName), strValue);
			} catch(ItemNotFoundException& e) {
				IAS_LOG(LogLevel::INSTANCE.isInfo(), "Missing property: "<<strName);
			}
		}

		lstDMResult.add(dmQueryResult);
	}
}
/*************************************************************************/
Extern::Statement* SimpleQuery::Create(const DM::Type* pType, const StringList& lstParamaters, const ::IAS::Lang::Interpreter::Extern::ModuleProxy* pModuleProxy){
	IAS_TRACER;
	return IAS_DFT_FACTORY<SimpleQuery>::Create(pType, lstParamaters, pModuleProxy);
}
/*************************************************************************/
}
}
}
}
