/*
 * File: IAS-QSystemMod-LMDB/src/ds/Impl/LMDB/Input.cpp
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
#include "Input.h"
#include "exception/LMDBException.h"

#include <sqlite3.h>
#include "log/LogLevel.h"
#include "Session.h"

#include <qs/fmt/FmtFactory.h>

#include <lmdb.h>

namespace IAS {
namespace DS {
namespace Impl {
namespace LMDB {

/*************************************************************************/
Input::Input(Statement& statement):statement(statement){
	IAS_TRACER;
}
/*************************************************************************/
Input::~Input() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Input::addInput(const String& strTag, DM::Tools::Setter *pSetter){
	IAS_TRACER;

  if (elementKey.strTag.empty()) {
    elementKey.strTag = strTag;
    elementKey.pSetter = pSetter;
    return;
  }

  if (elementValue.strTag.empty()) {
    elementValue.strTag = strTag;
    elementValue.pSetter = pSetter;
  }
}
/*************************************************************************/
void Input::feedInputs(DM::DataObjectPtr& dm){
	IAS_TRACER;

  if (!elementKey.strTag.empty())
    feedInput(elementKey, dm);

  if (!elementValue.strTag.empty())
    feedInput(elementValue, dm);
}
/*************************************************************************/
void Input::feedInput(Element& e, DM::DataObjectPtr& dm){

	  if(!e.pSetter->isSet(dm)){

        e.mv.mv_size = 0;
        e.mv.mv_data = 0;

		}else{

			DM::DataObjectPtr dmValue(e.pSetter->getValue(dm));

			if(e.pSetter->getTargetTypeEnum() == DM::Type::DataObjectType ||
			   e.pSetter->getTargetTypeEnum() == DM::Type::AnyType) {
				QS::Fmt::Formatter *pFormatter=statement.getSession()->getFormatter();
				StringStream ssValue;
        pFormatter->write(dmValue,ssValue);
        e.strValue = ssValue.str();
			}else{
				e.strValue=dmValue->toString();
			}

    }

    e.mv.mv_size = e.strValue.length();
    e.mv.mv_data = (void*) e.strValue.c_str();

    IAS_LOG(LogLevel::INSTANCE.isData(),"mv:      "<<e.strTag);
    IAS_LOG(LogLevel::INSTANCE.isData(),"value:   "<<e.strValue);
    IAS_LOG(LogLevel::INSTANCE.isData(),"mv_size: "<<e.mv.mv_size);
    IAS_LOG(LogLevel::INSTANCE.isData(),"mv_data: "<<e.mv.mv_data);
}
/*************************************************************************/
}
}
}
}
