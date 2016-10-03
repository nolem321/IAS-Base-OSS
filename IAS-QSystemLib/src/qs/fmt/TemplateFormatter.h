/*
 * File: IAS-QSystemLib/src/qs/fmt/TemplateFormatter.h
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
#ifndef _IAS_QS_Fmt_TemplateFormatter_H_
#define _IAS_QS_Fmt_TemplateFormatter_H_

#include <commonlib/commonlib.h>

#include "Formatter.h"
#include <qs/tools/Template.h>

#include <org/invenireaude/qsystem/workers/Context.h>

namespace IAS {
namespace QS {
namespace Fmt {

/*************************************************************************/
/** The TemplateFormatter class.
 *
 */
class TemplateFormatter :public Formatter {
public:

	virtual ~TemplateFormatter() throw();


	virtual void write(const DM::DataObject* dmData,
							std::ostream&       ostream,
						    QS::API::Attributes *pAttributes=NULL);

	virtual void read( DM::DataObjectPtr& dmData,
						   std::istream&       istream,
						   QS::API::Attributes *pAttributes=NULL);

	static const String& CStrAttr;

	static const String& CEnvTemplateDir;

protected:
	TemplateFormatter(const DM::DataFactory* pDataFactory);

	const DM::DataFactory* pDataFactory;

	TimeSamplesResults tsrSerialization;

	HashMapStringToPointer<Tools::Template> hmTemplates;

	const Tools::Template* getTemplate(QS::API::Attributes *pAttributes,
								const DM::DataObject* dmData);

	const Tools::Template* tryTemplate(const String& strName);

	StringList lstTemplateDirectories;

	friend class Factory<TemplateFormatter>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_QS_Fmt_TemplateFormatter_H_ */
