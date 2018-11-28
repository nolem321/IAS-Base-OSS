/*
 * File: IAS-QSystemLib/src/ds/Impl/Session.h
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
#ifndef _IAS_DS_Impl_Session_H_
#define _IAS_DS_Impl_Session_H_

#include <ds/api/Session.h>
#include <qs/fmt/FmtFactory.h>

#include "Environment.h"

namespace IAS {
namespace DS {
namespace Impl {
class Connection;

/*************************************************************************/
/** The Session class.
 *
 */
class Session :
		public virtual API::Session{

public:

	virtual ~Session() throw();

	QS::Fmt::Formatter* getFormatter()const{
		return pFormatter;
	}

	const Connection* getConnection()const{
		return pConnection;
	}

  virtual const API::SQLTricks* getSQLTricks()const;

	DS::API::Environment::ObjectMode getObjectMode()const;

protected:
	Session(Connection* pConnection);

	QS::Fmt::Formatter* pFormatter;
	const Connection* pConnection;

	DS::API::Environment::ObjectMode iObjectMode;

	DS::API::Environment::ObjectMode parseObjectMode(const String& strValue);
private:

  class ObjectModeNamesMap : public HashMapWithStringKey<DS::API::Environment::ObjectMode>{
  public:
	  ObjectModeNamesMap();
  };

  static const ObjectModeNamesMap hmObjectModeNames;

};

/*************************************************************************/
}
}
}

#endif /* _IAS_DS_Impl_Session_H_ */
