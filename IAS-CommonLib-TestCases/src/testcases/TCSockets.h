/*
 * File: IAS-CommonLib-TestCases/src/testcases/TCSockets.h
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
#ifndef TCSockets_H_
#define TCSockets_H_

#include "commonlib/testcase/TestUnit.h"
#include "commonlib/net/FileHandle.h"
#include "commonlib/net/BlockIO.h"

namespace IAS{
namespace TCT{

class TCSockets: public TestUnit{

public:
	TCSockets(TestSuite* pTestSuite);
	virtual ~TCSockets()  throw ();
	
	virtual void init(TestSuite* pTestSuite);

	void case01();
	void case02();
	void case03();
	void case04();

	struct SyncServer : public Thread, Runnable{

		SyncServer();

		virtual void run();
		virtual void serve(Net::IBlockIO* pBlockIO);

		Net::Server server;

	};

	struct SyncServerSSL : public SyncServer{
		virtual void run();
	};

	struct SyncClient {

		SyncClient();

		virtual void run();
		virtual void serve(Net::IBlockIO* pBlockIO);

		Net::Client client;

		StringStream ssInput;
	};

	struct SyncClientSSL : public SyncClient{
		virtual void run();
	};


	struct AsyncClient : public Thread, Runnable {

		AsyncClient();
		virtual void run();
		virtual void serve(Net::IBlockIO* pBlockIO);

		Net::Client client;
		StringStream ssException;
	};

	struct AsyncClientSSL : public AsyncClient{
		virtual void run();
	};

	/*struct Worker04 : public Thread, Runnable{

			Worker04(Net::EventMonitor*  pEventMonitor);
			virtual void run();

			Net::EventMonitor*  pEventMonitor;

			String strResult;
		};

*/

	friend class ::IAS::Factory<TCSockets>;
	::IAS::TestRunner<TCSockets> theTestRunner;
};


} /* namespace TCT */
} /* namespace IAS */


#endif /*TCSockets_H_*/
