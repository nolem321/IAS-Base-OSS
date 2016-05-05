/*
 * File: IAS-QSystemLib/src/ds/api.h
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
#ifndef _IAS_DS_API_API_H_
#define _IAS_DS_API_API_H_

//TODO (M) interface versioning and check on module load.

#include "api/exception/Exception.h"
#include "api/exception/RuntimeException.h"
#include "api/exception/ConstraintViolationException.h"

#include "api/Environment.h"
#include "api/Connection.h"
#include "api/Session.h"

#include "api/StatementSelect.h"
#include "api/StatementInsert.h"
#include "api/StatementCall.h"
#include "api/StatementDelete.h"
#include "api/StatementUpdate.h"

#endif /* API_H_ */
