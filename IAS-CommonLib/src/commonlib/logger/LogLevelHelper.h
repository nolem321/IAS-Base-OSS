/*
 * File: IAS-CommonLib/src/commonlib/logger/LogLevelHelper.h
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
/* IAS_COPYRIGHT */

/* ChangeLog:
 * 
 */

#ifndef _IAS_LogLevelHelper_H_
#define _IAS_LogLevelHelper_H_

namespace IAS{


/*************************************************************************/
/** The LogLevelHelper class.
 */


class LogLevelHelper{ 
	
	public:		
				
		static void ReadSettings(LogLevelBase   *ptrLogLevel, const char *sSettings);
		static void SetDefaults(LogLevelBase   *ptrLogLevel);
		
	protected:
		
	static void ReadWordSettings(LogLevelBase   *ptrLogLevel, const char *sWord);
};


}/* namespace IAS */

#endif /*LOGGER_H_*/

