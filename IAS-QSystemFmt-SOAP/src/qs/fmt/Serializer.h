/*
 * File: IAS-QSystemLib/src/qs/fmt/Serializer.h
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
#ifndef _IAS_QS_Fmt_Serializer_H_
#define _IAS_QS_Fmt_Serializer_H_

#include <commonlib/commonlib.h>
#include <dm/datamodel.h>
#include <dm/xml/XMLSerializer.h>
#include <qs/fmt/Formatter.h>

namespace IAS {
namespace QS {
namespace Fmt {

/*************************************************************************/
/** The Serializer class.
 *
 */
class Serializer : public DM::XML::XMLSerializer {
public:

	virtual ~Serializer() throw();

	void serialize(const DM::XML::XMLDocument* pDocument);

protected:
	Serializer(DM::XML::XMLHelper* pXMLHelper,
			   DM::XML::LibXMLWriter *pWriter,
			   const String& strSOAPNS,
			   QS::API::Attributes *pAttributes=NULL);

	QS::API::Attributes *pAttributes;
	const DM::XML::XMLDocument* pDocument;

	void write_soap_envelope();
	void write_soap_header();
	void write_soap_body();

	const String& strSOAPNS;

	friend class Factory<Serializer>;
};

/*************************************************************************/
}
}
}
/*************************************************************************/
#endif /* _IAS_QS_Fmt_Serializer_H_ */
