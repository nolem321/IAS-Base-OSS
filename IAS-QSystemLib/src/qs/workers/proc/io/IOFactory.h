/*
 * File: IAS-QSystemLib/src/qs/workers/proc/io/IOFactory.h
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
#ifndef _IAS_QS_Workers_Proc_IOFactory_H_
#define _IAS_QS_Workers_Proc_IOFactory_H_

#include <commonlib/commonlib.h>

#include <dm/datamodel.h>

#include <org/invenireaude/qsystem/workers/Connection.h>
#include <org/invenireaude/qsystem/workers/io/OutputSpecification.h>
#include <org/invenireaude/qsystem/workers/io/InputSpecification.h>


namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace WCM {
class WorkContextManager;
}
namespace IO {

class Input;
class Output;
class IOManager;

/*************************************************************************/
/** The IOFactory class.
 *
 */
class IOFactory {

public:

	virtual ~IOFactory()throw();

	void createInput(const String& strName);
	void createOutput(const String& strName);
	void createController(const String& strName);


	static ::org::invenireaude::qsystem::workers::io::Ext::InputSpecificationPtr
	   InputSpecsToDM(const String& strSpecs);

	static ::org::invenireaude::qsystem::workers::io::Ext::OutputSpecificationPtr
	   OutputSpecsToDM(const String& strSpecs);

	IOFactory(const ::org::invenireaude::qsystem::workers::io::InputSpecification*  dmInputSpecification,
			  const ::org::invenireaude::qsystem::workers::io::OutputSpecification* dmOutputSpecification,
		   	  IOManager* pIOManager,
			  WCM::WorkContextManager* pWorkContextManager);

	static void UpdateConnection(const URI& uri, org::invenireaude::qsystem::workers::Connection *pConnection);
	static void	UpdateAttributes(const URI& uri,::org::invenireaude::qsystem::workers::Ext::AttributeUpdateList& lstAttrUpdates);

protected:

	typedef HashMapWithStringKey<const DM::DataObject*> ParametersMap;

	ParametersMap  hmInputs;
	ParametersMap  hmOutputs;
	ParametersMap  hmControllers;

	IOManager* pIOManager;
	WCM::WorkContextManager* pWorkContextManager;

	void create(const DM::DataObject* dmParameters);
	void create(const ::org::invenireaude::qsystem::workers::io::Input* dmParameters);
	void create(const ::org::invenireaude::qsystem::workers::io::Output* dmParameters);

};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_QS_Workers_Proc_IOFactory_H_ */
