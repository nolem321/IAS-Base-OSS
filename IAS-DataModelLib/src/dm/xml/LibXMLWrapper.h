/*
 * File: IAS-DataModelLib/src/dm/xml/LibXMLWrapper.h
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
#ifndef _IAS_DM_XML_LIBXMLWRAPPER_H_
#define _IAS_DM_XML_LIBXMLWRAPPER_H_

#include <commonlib/commonlib.h>

#include <map>

namespace IAS {
namespace DM {
namespace XML {

/*************************************************************************/
/** The class. */
 class LibXMLWrapper : public InstanceFeature<LibXMLWrapper>{
public:

	virtual ~LibXMLWrapper() throw();

	static LibXMLWrapper* Create();

	const char* getNodeName(int iNode) const;
protected:
	LibXMLWrapper();

	typedef ias_std_unordered_map<int, const char*> NodesMap;

	NodesMap hmNodes;

	friend class ::IAS::Factory<LibXMLWrapper>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_DM_XML_LIBXMLWRAPPER_H_ */
