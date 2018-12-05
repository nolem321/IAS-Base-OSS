/*
 * File: IAS-QSystemMod-LMDB/src/ds/Impl/LMDB/ResultSetOutput.h
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
#ifndef _IAS_DS_Impl_LMDB_ResultSetOutput_H_
#define _IAS_DS_Impl_LMDB_ResultSetOutput_H_

#include <commonlib/commonlib.h>
#include <ds/api/IResultSetOutput.h>

#include "Statement.h"
#include <lmdb.h>

namespace IAS {
namespace DS {
namespace Impl {
namespace LMDB {
class Session;
/*************************************************************************/
/** The ResultSetOutput class.
 *
 */
class ResultSetOutput :
		public virtual DS::API::IResultSetOutput {
public:

	virtual ~ResultSetOutput() throw();

	virtual void addResultSetOutput(DM::Tools::Setter* pSetter, bool bOptional);
	virtual void bindResultSetOutputs();

	virtual bool next();
	virtual void fetch(int iIdx, DM::DataObjectPtr& dm);

	virtual void close();

protected:
	ResultSetOutput(Statement& statement);

	typedef std::vector<bool>         OptionalTable;
	OptionalTable						          tabOptional;

	typedef std::vector<DM::Tools::Setter*>     SettersTable;
	SettersTable						                    tabSetters;

	Statement& statement;

  void fetchValue(MDB_val& value, DM::Tools::Setter* pSetter, DM::DataObjectPtr& dm);

  int  iKeyIdx;
  int  iDataIdx;

	MDB_cursor *cursor;

  MDB_val values[2];

	bool bHasData;
  bool bReadAll;

};
/*************************************************************************/
}
}
}
}

#endif /* _IAS_DS_Impl_LMDB_ResultSetOutput_H_ */
