/*
 * File: IAS-LangLib/src/lang/interpreter/proc/exception/ProcessorLinkedException.h
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
/* ChangeLog:
 *
 */

#ifndef _IAS_AS_Lang_Interpreter_Proc_Exception_ProcessorLinkedException_H_
#define _IAS_AS_Lang_Interpreter_Proc_Exception_ProcessorLinkedException_H_


#include <commonlib/commonlib.h>

#include "ProcessorException.h"
#include <lang/tools/parser/SourceLocation.h>
#include <lang/model/Node.h>

namespace IAS {
namespace Lang {
namespace Interpreter{
namespace Proc {

/*************************************************************************/
/** The class. */
 class ProcessorLinkedException : public ProcessorException {

public:

	ProcessorLinkedException(::IAS::Exception& e,
							 const Tools::Parser::SourceLocation& sourceLocation,
							 const Model::Node *pNode);

	virtual ~ProcessorLinkedException() throw();

	const Tools::Parser::SourceLocation&  getSourceLocation(){
		return sourceLocation;
	}

    const Model::Node* getNode(){
			return pNode;
		}

	virtual const char*  getName();

protected:

	const Model::Node *pNode;
	Tools::Parser::SourceLocation sourceLocation;
};
/*************************************************************************/

}
}
}
}

#endif /*_IAS_AS_Lang_Exception_ProcessorLinkedException_H_*/
