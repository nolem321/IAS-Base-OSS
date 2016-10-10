/*
 * File: IAS-QSystemLib/src/qs/fmt/SOAPFormatter.h
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
#ifndef _IAS_QS_Fmt_SOAPFormatter_H_
#define _IAS_QS_Fmt_SOAPFormatter_H_

#include <commonlib/commonlib.h>
#include <dm/datamodel.h>
#include <dm/json/JSONHelper.h>

#include <qs/fmt/Formatter.h>
#include <qs/fmt/XMLFormatter.h>

#include <org/invenireaude/qsystem/workers/Context.h>

namespace IAS {
namespace QS {
namespace Fmt {

/*************************************************************************/
/** The SOAPFormatter class.
 *
 */
class SOAPFormatter : public Formatter {
public:

	virtual ~SOAPFormatter() throw();

	virtual void write(const DM::DataObject* dmData,
							std::ostream&       ostream,
						    QS::API::Attributes *pAttributes=NULL);

	virtual void read( DM::DataObjectPtr& dmData,
						   std::istream&       istream,
						   QS::API::Attributes *pAttributes=NULL);

protected:

	SOAPFormatter(const DM::DataFactory* pDataFactory, const String& strNS);

	const String& strNS;

	const DM::DataFactory* pDataFactory;

	TimeSamplesResults tsrParsing;
	TimeSamplesResults tsrSerialization;

	friend class Factory<SOAPFormatter>;
};

/*************************************************************************/
class SOAPFormatterV1 : public SOAPFormatter{
  protected:
	SOAPFormatterV1(const DM::DataFactory* pDataFactory);
	friend class Factory<SOAPFormatterV1>;
};
/*************************************************************************/
class SOAPFormatterV12 : public SOAPFormatter{
  protected:
	SOAPFormatterV12(const DM::DataFactory* pDataFactory);

	void getSOAPContent(std::istream& istream, StringStream& ostream);

	virtual void read( DM::DataObjectPtr& dmData,
						   std::istream&       istream,
						   QS::API::Attributes *pAttributes=NULL);

	friend class Factory<SOAPFormatterV12>;
};
/*************************************************************************/

}
}
}

/*************************************************************************/
extern "C"{
void* _ias_qs_fmt_SOAP(const ::IAS::DM::DataFactory* pDataFactory);
void* _ias_qs_fmt_SOAP12(const ::IAS::DM::DataFactory* pDataFactory);
}
/*************************************************************************/
#endif /* _IAS_QS_Fmt_SOAPFormatter_H_ */
