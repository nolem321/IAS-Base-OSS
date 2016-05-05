/*
 * File: IAS-QSystemLib/src/qs/lang/tools/regexp/RegExpMatchContainer.h
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
#ifndef _IAS_QS_Lang_Tools_RegExp_RegExpMatchContainer_H_
#define _IAS_QS_Lang_Tools_RegExp_RegExpMatchContainer_H_

#include <commonlib/commonlib.h>
#include <dm/datamodel.h>

namespace IAS {
namespace QS {
namespace Lang {
namespace Tools {
namespace RegExp {

class RegExpMatch;
/*************************************************************************/
/** The RegExpMatchContainer class.
 *
 */
class RegExpMatchContainer {
public:

	virtual ~RegExpMatchContainer() throw();

	bool match(const String& strValue, DM::DataObjectPtr& dm)const;

protected:
	RegExpMatchContainer(const String& strSpec, const DM::DataFactory* pDataFactory);

	void addMatch(RegExpMatch* pMatch);

	void parse(const String& strSpec, const DM::DataFactory* pDataFactory);

	typedef PtrVector<RegExpMatch> MatchVector;
	MatchVector                    tabMatches;


	friend class Factory<RegExpMatchContainer>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_QS_Lang_Tools_RegExp_RegExpMatchContainer_H_ */
