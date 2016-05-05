/*
 * File: IAS-QSystemExe/src/parameters/ProcessorParameters.cpp
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
#include "ProcessorParameters.h"

#include <commonlib/commonlib.h>

#include <org/invenireaude/qsystem/workers/DataFactory.h>

using namespace ::org::invenireaude::qsystem::workers;


namespace IAS {
namespace QS {
namespace Parameters {

/*************************************************************************/
ProcessorParameters::ProcessorParameters(int argc, char* argv[]){
	IAS_TRACER;

	::IAS::QS::Parameters::ProgramParameters::init(argc,argv,"hs:i:o:l:f:N:O:T:d:m:t:c:C:E:P:");

}
/*************************************************************************/
const String ProcessorParameters::C_DefaultMode("processor");
const String ProcessorParameters::C_strEmpty("");
/*************************************************************************/
bool ProcessorParameters::hasModeSpecs()const{
	return hmIndicators.count('m');
}
/*************************************************************************/
const String& ProcessorParameters::getModeSpecs()const{

	if(!hmIndicators.count('m'))
		return C_DefaultMode;

	return hmValues.find('m')->second;
}
/*************************************************************************/
bool ProcessorParameters::hasInputSpecs()const{
	return hmIndicators.count('i');
}
/*************************************************************************/
const String& ProcessorParameters::getInputSpecs()const{

	if(!hmIndicators.count('i'))
		IAS_THROW(ConfigException("Missing -i option."));

	return hmValues.find('i')->second;
}
/*************************************************************************/
bool ProcessorParameters::hasOutputSpecs()const{
	return hmIndicators.count('o');
}
/*************************************************************************/
const String& ProcessorParameters::getOutputSpecs()const{

	if(!hmIndicators.count('o'))
		IAS_THROW(ConfigException("Missing -o option."));

	return hmValues.find('o')->second;
}
/*************************************************************************/
bool ProcessorParameters::hasLogicSpecs()const{
	return hmIndicators.count('l');
}
/*************************************************************************/
const String& ProcessorParameters::getLogicSpecs()const{

	if(!hmIndicators.count('l'))
		IAS_THROW(ConfigException("Missing -l option."));

	return hmValues.find('l')->second;
}
/*************************************************************************/
bool ProcessorParameters::hasDataSourceSpecs()const{
	return hmIndicators.count('d');
}
/*************************************************************************/
const String& ProcessorParameters::getDataSourceSpecs()const{

	if(hmIndicators.count('d')){
		return hmValues.find('d')->second;
	}else{
		return C_strEmpty;
	}
}
/*************************************************************************/
bool ProcessorParameters::hasTXMSpecs()const{
	return hmIndicators.count('t');
}
/*************************************************************************/
const String& ProcessorParameters::getTXMSpecs()const{

	static const String strEmpty;

	if(hmIndicators.count('t')){
		return hmValues.find('t')->second;
	}else{
		return strEmpty;
	}
}
/*************************************************************************/
bool ProcessorParameters::hasCacheSpecs()const{
	return hmIndicators.count('c');
}
/*************************************************************************/
const String& ProcessorParameters::getCacheSpecs()const{

	static const String strEmpty;

	if(hmIndicators.count('c')){
		return hmValues.find('c')->second;
	}else{
		return strEmpty;
	}
}
/*************************************************************************/
bool ProcessorParameters::hasEventCounterSpecs()const{
	return hmIndicators.count('E');
}
/*************************************************************************/
const String& ProcessorParameters::getEventCounterSpecs()const{

	static const String strEmpty;

	if(hmIndicators.count('E')){
		return hmValues.find('E')->second;
	}else{
		return strEmpty;
	}
}
/*************************************************************************/
bool ProcessorParameters::hasStatsPublishersSpecs()const{
	return hmIndicators.count('P');
}
/*************************************************************************/
const String& ProcessorParameters::getStatsPublishersSpecs()const{

	static const String strEmpty;

	if(hmIndicators.count('P')){
		return hmValues.find('P')->second;
	}else{
		return strEmpty;
	}
}
/*************************************************************************/
bool ProcessorParameters::hasFullConfig()const{
	return hmIndicators.count('f');
}
/*************************************************************************/
const String& ProcessorParameters::getFullConfig()const{

	static const String strEmpty;

	if(hmIndicators.count('f')){
		return hmValues.find('f')->second;
	}else{
		return strEmpty;
	}
}
/*************************************************************************/
unsigned int ProcessorParameters::getNumMessages()const{

	if(hmIndicators.count('N'))
		return TypeTools::StringToInt(hmValues.find('N')->second);
	else
		return C_MaxMessages;
}
/*************************************************************************/
unsigned int ProcessorParameters::getOffset()const{

	if(hmIndicators.count('O'))
		return TypeTools::StringToInt(hmValues.find('O')->second);
	else
		return 0;
}
/*************************************************************************/
unsigned int ProcessorParameters::getNumThreads()const{

	if(hmIndicators.count('T'))
		return TypeTools::StringToInt(hmValues.find('T')->second);
	else
		return 1;
}
/*************************************************************************/
unsigned int ProcessorParameters::getCommitCount()const{

	if(hmIndicators.count('C'))
		return TypeTools::StringToInt(hmValues.find('C')->second);
	else
		return 1;
}
/*************************************************************************/
const StringList& ProcessorParameters::getLogicParameters()const{
	IAS_TRACER;

	return this->lstParameters;
}
/*************************************************************************/
ProcessorParameters::~ProcessorParameters() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void ProcessorParameters::printCmdDesc(std::ostream& os) const{
	IAS_TRACER;

	os<<" [-options] [arguments ...]"<<std::endl;

}
/*************************************************************************/
void ProcessorParameters::printArgsDesc(std::ostream& os) const{
	IAS_TRACER;

	os<<"\t-s <name>  \t System name."<<std::endl;
	os<<"\t-i <url or file>   \t Input specification or a file name."<<std::endl;
	os<<"\t-o <url or file>   \t Output specification or a file name."<<std::endl;
	os<<"\t-l <url or file>   \t Logic specification file name or a mode name optionally followed by '!'."<<std::endl;
	os<<"\t-d <url or file>   \t Datasource specification or a file name."<<std::endl;
	os<<"\t-t <url or file>   \t XA Transaction manager specification or a file name."<<std::endl;
	os<<"\t-c <url or file>   \t Cache specification or a file name."<<std::endl;
	os<<"\t-E <file>          \t Event Counters specification file name."<<std::endl;
	os<<"\t-P <name,url,file> \t One of: 'console', 'memory', QSystem Output url or a specification file."<<std::endl;
	os<<"\t-f <file>   \t Full configuration in a single file."<<std::endl;
	os<<"\t-m <name>  \t Mode type: processor (default) or server."<<std::endl;
	os<<"\t-O <number>\t Offset - number of messages to skip."<<std::endl;
	os<<"\t-N <number>\t Number of messages to process."<<std::endl;
	os<<"\t-T <number>\t Number of threads to start."<<std::endl;
	os<<"\t-C <number>\t Commit count."<<std::endl;

	os<<"\nValid logic names are:\n"<<std::endl;
	os<<"\t fwd      - Forwarder."<<std::endl;
	os<<"\t exe      - Execute the specified program(s)."<<std::endl;
	os<<"\t match    - Execute programs which signature match the input data."<<std::endl;
	os<<"\t attr     - Execute program selected by the message meta attribute."<<std::endl;
	os<<"\t extern   - External module."<<std::endl;
	os<<"\t js       - External module for JavaScript."<<std::endl;
	os<<"\t grab     - Message extractor."<<std::endl;
	os<<"\t proxy    - Synchronous proxy."<<std::endl;
	os<<"\t aproxy   - Asynchronous proxy."<<std::endl;
	os<<"\t mp | message_preview - Message preview."<<std::endl;
	os<<"\t sp | stats_producer  - Statistics producer."<<std::endl;
	os<<" When the logic name is followed by an exclamation mark '!' the message content will NOT be parsed."<<std::endl;

	os<<"\nExamples:"<<std::endl;
	os<<"\t ias_qs_processor -i file:/tmp/customer.json -o file:stdout_fmt?format=XML -l fwd"<<std::endl;
	os<<std::endl;
	os<<"\t ias_qs_processor -T1 -i 'shm://sample/Q.INPUT?mode=input?timeout=60000' -o 'dir:/tmp/test_${ID}_${TS}?format=XML' -l exe:com::examples::test"<<std::endl;

}
/*************************************************************************/
}
}
}
