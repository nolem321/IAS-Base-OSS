/*
 * File: IAS-QSystemLib/src/qs/lang/tools/regexp/RegExpMatch.h
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
#ifndef _IAS_QS_Lang_Tools_RegExp_RegExpMatch_H_
#define _IAS_QS_Lang_Tools_RegExp_RegExpMatch_H_

#include <commonlib/commonlib.h>

#include <dm/datamodel.h>
#include <dm/tools/Setter.h>

#include <regex>

#ifdef __GNUC__
#define ias_regex_ns ::std
#else
#define ias_regex_ns ::std::tr1
#endif

namespace IAS {
namespace QS {
namespace Lang {
namespace Tools {
namespace RegExp {

/*************************************************************************/
/** The RegExpMatch class.
 *
 */
class RegExpMatch {
public:

	virtual ~RegExpMatch() throw();

	bool match(const String& strValue, DM::DataObjectPtr& dm)const;

	void addXPath(unsigned int id, const String& strXPath);

protected:
	RegExpMatch(const String& strRegExp, const DM::Type* pType);

	const DM::Type* pType;
	ias_regex_ns::regex   expression;

	class SetterEntry {
		public:

			unsigned int getId()const {return id;};
			DM::Tools::Setter* getSetter()const {return ptrSetter;};

			virtual ~SetterEntry(){};

		protected:
			SetterEntry(unsigned int id, DM::Tools::Setter* pSetter):
				ptrSetter(pSetter),
				id(id){};

			IAS_DFT_FACTORY<DM::Tools::Setter>::PtrHolder ptrSetter;
			unsigned int id;

		friend class Factory<SetterEntry>;
	};

	typedef PtrVector<SetterEntry> SettersVector;
	SettersVector                  tabSetters;

	String strRegExp;

	friend class Factory<RegExpMatch>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_QS_Lang_Tools_RegExp_RegExpMatch_H_ */
