/*
 * File: IAS-QSystemMod-PostgreSQL/src/ds/Impl/PostgreSQL/ValueConverter.cpp
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
#include "ValueConverter.h"
#include "exception/PostgreSQLException.h"

#include "log/LogLevel.h"
#include "Session.h"
#include "Connection.h"

#include <qs/fmt/FmtFactory.h>

namespace IAS{
namespace DS{
namespace Impl{
namespace PostgreSQL{

/*************************************************************************/
void ValueConverter::ConvertToPostgreSQL(Statement& statement,
                                         const DM::Tools::Setter *pSetter,
                                         const DM::DataObjectPtr &dm,
                                         StringStream &ssValue){

  IAS_TRACER;


	DM::DataObjectPtr dmValue(pSetter->getValue(dm));
  DM::Type::Types iTypeEnum = pSetter->getTargetTypeEnum();

  switch (iTypeEnum){

  case DM::Type::TextType:
    ssValue << dmValue->toString();
    break;

  case DM::Type::DataObjectType:
  case DM::Type::AnyType:
    statement.getSession()->getFormatter()->write(dmValue, ssValue);
    break;

  case DM::Type::BooleanType:
    ssValue << dmValue->toInteger();
    break;

  case DM::Type::IntegerType:
    ssValue << dmValue->toInteger();
    break;

  case DM::Type::FloatType:
    ssValue << dmValue->toFloat();
    break;

  case DM::Type::TimeType:
    ssValue << dmValue->toTime().Timestamp::toString(Connection::CDFmtTime);
    break;

  case DM::Type::DateTimeType:
    ssValue << dmValue->toDateTime().Timestamp::toString(Connection::CDFmtDateTime);
    break;

  case DM::Type::DateType:
    ssValue << dmValue->toDate().Timestamp::toString(Connection::CDFmtDate);
    break;

  default:
    ssValue << dmValue->toString();

  }
}
/*************************************************************************/
void ValueConverter::ConvertFromPostgreSQL(Statement& statement, DM::Tools::Setter *pSetter, DM::DataObjectPtr &dm, const char *sValue){

  DM::Type::Types iTypeEnum = pSetter->getTargetTypeEnum();

  switch (iTypeEnum){

  case DM::Type::TextType:
    pSetter->setString(dm, sValue);
    break;

  case DM::Type::DataObjectType:
  case DM::Type::AnyType:

    {
        DM::DataObjectPtr dmValue;
  		  StringStream ssValue(sValue);
			  statement.getSession()->getFormatter()->read(dmValue,ssValue);
			  pSetter->setDataObject(dm,dmValue);
    }

    break;

  case DM::Type::BooleanType:
    pSetter->setInteger(dm, TypeTools::StringToInt(sValue));
    break;

  case DM::Type::IntegerType:
    pSetter->setInteger(dm, TypeTools::StringToInt(sValue));
    break;

  case DM::Type::FloatType:
     pSetter->setFloat(dm, TypeTools::StringToFloat(sValue));
    break;

  case DM::Type::TimeType:
    {
      Timestamp ts;
      ts.fromString(sValue, Connection::CDFmtTime);
      pSetter->setTime(dm, ts);
      break;
    }

  case DM::Type::DateTimeType:
    {
      Timestamp ts;
      ts.fromString(sValue, Connection::CDFmtDateTime);
      pSetter->setDateTime(dm, ts);
      break;
    }

  case DM::Type::DateType:
    {
      Timestamp ts;
      ts.fromString(sValue, Connection::CDFmtDate);
      pSetter->setDate(dm, ts);
      break;
    }


  default:
    pSetter->setString(dm, sValue);

  }

}
/*************************************************************************/
}
}
}
}
