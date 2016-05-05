/*
 * File: IAS-QSystemLib/src/qs/Impl/net/sync/BlockIOWrapperFactory.cpp
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
#include "BlockIOWrapperFactory.h"
#include<qs/log/LogLevel.h>


namespace IAS {
namespace QS {
namespace Net {
namespace Sync{

/*************************************************************************/
BlockIOWrapperFactory::BlockIOWrapperFactory(const ::org::invenireaude::qsystem::workers::Connection* dmConnection):
		dmConnection(dmConnection->duplicateConnection()){}
/*************************************************************************/
BlockIOWrapperFactory::~BlockIOWrapperFactory(){
	IAS_TRACER;
}
/*************************************************************************/
const ::org::invenireaude::qsystem::workers::Connection* BlockIOWrapperFactory::getConnection()const{
	return dmConnection;
};
/*************************************************************************/
BlockIOWrapper::BlockIOWrapper(IAS::Net::FileHandle* pFileHandle):
		ptrFileHandle(pFileHandle){

	setPeer(pFileHandle->getPeer());
}
/*************************************************************************/
IAS::Net::IBlockIO *BlockIOWrapper::getBlockIO()const{
	return ptrFileHandle;
};
/*************************************************************************/
IAS::Net::FileHandle *BlockIOWrapper::getFileHandle()const{
	return ptrFileHandle;
};
/*************************************************************************/
const String& BlockIOWrapper::getPeer()const{
	return strPeer;
};
/*************************************************************************/
void BlockIOWrapper::setPeer(const String& strPeer){
	IAS_TRACER;

	IAS_LOG(QS::LogLevel::INSTANCE.isInfo(),"Peer: "<<strPeer);

	this->strPeer=strPeer;
}
/*************************************************************************/
}
}
}
}
