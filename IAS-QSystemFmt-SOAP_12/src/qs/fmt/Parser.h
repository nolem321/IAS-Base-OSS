/*
 * File: IAS-QSystemLib/src/qs/fmt/Parser.h
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
#ifndef _IAS_QS_Fmt_Parser_H_
#define _IAS_QS_Fmt_Parser_H_

#include <commonlib/commonlib.h>
#include <dm/datamodel.h>
#include <dm/xml/XMLParser.h>
#include <qs/fmt/Formatter.h>

namespace IAS {
namespace QS {
namespace Fmt {

/*************************************************************************/
/** The Parser class.
 *
 */
class Parser : public DM::XML::XMLParser {
public:

	virtual ~Parser() throw();

	DM::XML::XMLDocument* parse();


protected:
	Parser(DM::XML::XMLHelper* pXMLHelper, DM::XML::LibXMLLexer *pLibXMLLexer, QS::API::Attributes *pAttributes=NULL);

	QS::API::Attributes *pAttributes;

	void parse_soap_envelope();
	void parse_soap_header();
	void parse_soap_body();

	friend class Factory<Parser>;
};

/*************************************************************************/
}
}
}
/*************************************************************************/
#endif /* _IAS_QS_Fmt_Parser_H_ */
