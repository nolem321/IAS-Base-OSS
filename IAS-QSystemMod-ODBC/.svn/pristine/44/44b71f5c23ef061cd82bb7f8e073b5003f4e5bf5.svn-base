/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-DB2/src/ds/Impl/DB2/Output.h 
 *
 * Licensed under the Invenire Aude Commercial License (the "License");
 * you may not use this file except in compliance with the License. 
 * You may find the license terms and conditions in the LICENSE.txt file.
 * or at http://www.invenireaude.com/licenses/license.txt
 * 
 * This file and any derived form, including but not limited to object
 * executable, represents the Confidential Materials.
 * 
 */
#ifndef _IAS_DS_Impl_DB2_Output_H_
#define _IAS_DS_Impl_DB2_Output_H_

#include <commonlib/commonlib.h>
#include <ds/api/IOutput.h>

#include "Statement.h"
#include "Input.h"
namespace IAS {
namespace DS {
namespace Impl {
namespace DB2 {
class Session;
/*************************************************************************/
/** The Output class.
 *
 */
class Output :
		public Input,
		public virtual DS::API::IOutput {
public:

	virtual ~Output() throw();

	virtual void addOutput(const String& strTag, DM::Tools::Setter *pSetter);
	virtual void addInputOutput(const String& strTag, DM::Tools::Setter *pSetter);

	virtual void feedInputs(DM::DataObjectPtr& dm);

	virtual void fetch( DM::DataObjectPtr& dm);

protected:
	Output(Statement& statement);

	Holder::Base::Table			   			     tabOutputHolders;
	Holder::Base::Table			   			     tabInputOutputHolders;
};
/*************************************************************************/
}
}
}
}

#endif /* _IAS_DS_Impl_DB2_Output_H_ */
