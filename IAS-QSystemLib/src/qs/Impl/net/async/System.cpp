/*
 * File: IAS-QSystemLib/src/qs/Impl/net/async/System.cpp
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
#include "System.h"

#include "Connection.h"
#include "Engine.h"
#include "ssl/Engine.h"
namespace IAS {
namespace QS {
namespace Net {
namespace Async {

/*************************************************************************/
System::System(){
	IAS_TRACER;
}

/*************************************************************************/
System::~System() throw(){
	IAS_TRACER;
}
/*************************************************************************/
API::Connection* System::createConnection(const ::org::invenireaude::qsystem::workers::Connection* dmConnection){
	IAS_TRACER;

	URI uri;
	API::Environment::BuildURI(uri,dmConnection);

	String key(uri.getURIString());

	if(hmEngineMap.count(key) == 0)
		hmEngineMap[key]=dmConnection->isSetSsl() ?
				IAS_DFT_FACTORY<SSL::Engine>::Create(dmConnection,this) :
				IAS_DFT_FACTORY<Engine>::Create(dmConnection,this);

	Engine *pEngine=hmEngineMap.at(key);

	return IAS_DFT_FACTORY<Connection>::Create(this,pEngine);

}
/*************************************************************************/
}
}
}
}
