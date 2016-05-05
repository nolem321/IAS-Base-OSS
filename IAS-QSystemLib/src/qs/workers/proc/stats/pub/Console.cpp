/*
 * File: Console.cpp
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

#include "Console.h"
#include <iomanip>

#include <org/invenireaude/qsystem/workers/stats/LogicSample.h>
#include <org/invenireaude/qsystem/workers/stats/LogicSamplesSet.h>
#include <org/invenireaude/qsystem/stats/Sample.h>

#include <qs/workers/proc/wcm/WorkContextManager.h>
#include <qs/workers/proc/GlobalContext.h>
#include "../PublisherStore.h"

using namespace ::org::invenireaude::qsystem::workers;
using namespace ::org::invenireaude;

using namespace std;

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Stats {
namespace Pub {

/*************************************************************************/
Console::Console(){
	IAS_TRACER;
}
/*************************************************************************/
Console::~Console() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Console::publish(stats::LogicSamplesSet* dmLogicSamplesSet,
					  WCM::WorkContextManager* pWorkContextManager)const{
	IAS_TRACER;

	clearConsole();

	unsigned int iMsgLeft;
	unsigned int iMsgTotal;

	pWorkContextManager->getGlobalContext()->getProgress(iMsgLeft, iMsgTotal);

	unsigned int iProgress =  iMsgTotal - iMsgLeft;
	unsigned int iProgressPct= iMsgTotal > 0 ? 100*(iMsgTotal - iMsgLeft) / iMsgTotal : 0;

	DateTime ts(true);

	cout<<        "Invenire Aude, QSystem Data Processor \n";
	cout<<        "+--------------------------------------------------------------------------------------------------+\n";
	cout<<        "| "<< ts.toTimeString() <<" | Progress: ";
	for(int iIdx=0;iIdx<100;iIdx+=2)
		cout<< (iIdx < iProgressPct ? '=' : (iIdx < iProgressPct + 2 ? '>' : ' '));
	cout<<        "|  Done: "<<setw(8)<<iProgress<<"("<<setw(3)<<iProgressPct<<"%) |\n";
	cout<<        "+------------------+------------------+------------------------------------------------------------+\n";
	cout<<        "|     Case Name    |                  |\n";
	cout<<        "+------------------+------------------+------------------------------------------------------------+\n";

	const stats::Ext::LogicSampleList &lstSamples(dmLogicSamplesSet->getLogicSampleList());

	for(int iIdx=0; iIdx < lstSamples.size(); iIdx++){

		const stats::LogicSample *dmLogicSample = lstSamples.at(iIdx);

		const qsystem::stats::Sample *dmSuccess = dmLogicSample->getSuccess();
		const qsystem::stats::Sample *dmFailure = dmLogicSample->getFailure();

		unsigned int iNumSuccess = dmSuccess->getNum();

		cout<<"|"<< left  << setw(18)<< dmLogicSample->getName();
		    //<<"|"<< right << setw(3) << (*it)->getNumInstances()

		{
			unsigned int iNum = dmSuccess->getNum();
			unsigned int iMin = dmSuccess->getMin();
			unsigned int iMax = dmSuccess->getMax();
			unsigned int iAvg = dmSuccess->getAvg();

			cout<<"|"<< right << setw(8) << iNum
			<<" "<< right << setw(8) << iAvg
			<<"|"<< right << setw(8) << iMin
			<<" "<< right << setw(8) << iMax;
		}

		{
			unsigned int iNum = dmFailure->getNum();
			unsigned int iMin = dmFailure->getMin();
			unsigned int iMax = dmFailure->getMax();
			unsigned int iAvg = dmFailure->getAvg();

			cout<<"|"<< right << setw(8) << iNum
			<<" "<< right << setw(8) << iAvg
			<<"|"<< right << setw(8) << iMin
			<<" "<< right << setw(8) << iMax;
		}
		cout<<"|\n";
	}

	cout<<        "+------------------+-----------------+-----------------------------------------------------------+\n";
	cout.flush();
}
/*************************************************************************/
void Console::clearConsole()const{
	IAS_TRACER;

		/*
		 * It is a bitter truth, that on systems/terminals that this does not work
		 * termcap and ncurses will mess the screen, too. So let us leave this as it is.
		 */
	cout<<"\e[2J\e[H";
	cout.flush();
}
/*************************************************************************/

}
}
}
}
}
}
