/*
 * File: Template.h
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


#ifndef _IAS_QS_Tools_Template_H_
#define _IAS_QS_Tools_Template_H_

#include <commonlib/commonlib.h>
#include <dm/datamodel.h>

namespace IAS {

namespace Lang {
namespace Interpreter{
class ProgramLoader;
}
}

namespace QS {
namespace Tools {

/*************************************************************************/
/** The Template class.
 *
 */
class Template : public IAS::Template{
public:

	virtual ~Template() throw();

	class Arguments : public IAS::Template::Arguments{

		public:

		Arguments(const DM::DataObject* dmData, IAS::Lang::Interpreter::ProgramLoader *pProgramLoader=NULL, Arguments* pParentArguments = NULL, size_t iIdx = 0);
		virtual ~Arguments()throw();

		virtual bool getImpl(const String& strKey, String& strValue);
		virtual Template::Arguments* createNestedImpl(const String& strKey);
		virtual size_t getNestedCount(const String& strKey);

		protected:

			IAS::Lang::Interpreter::ProgramLoader *pProgramLoader;

			const DM::DataObject* dmData;
			size_t iIdx;

			void parseFunctionCall(const String& strValue, String& strFunction, String& strArgument);
			void callFunction(const String strFunction, const DM::DataObject* dmData, String& strValue);
	};

	protected:

	   Template(const String& strPattern);

	friend class Factory<Template>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_QS_Tools_Template_H_ */
