/*
 * File: IAS-QSystemExe/src/parameters/ChangeParameters.cpp
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
#include "ChangeParameters.h"
#include "ParameterException.h"

#include <commonlib/commonlib.h>

#include <iomanip>

#include <org/invenireaude/qsystem/DataFactory.h>
#include <org/invenireaude/qsystem/SystemChange.h>

using namespace ::org::invenireaude::qsystem;

namespace IAS {
namespace QS {
namespace Parameters {

/*************************************************************************/
ChangeParameters::ChangeParameters(int argc, char* argv[]){
	IAS_TRACER;

	::IAS::QS::Parameters::ProgramParameters::init(argc,argv,"hs:a:f:d");

}
/*************************************************************************/
const String& ChangeParameters::getSystemName()const{

	IAS_TRACER;

	if(!hmIndicators.count('s') || !hmValues.count('s') )
			IAS_THROW(ConfigException("Missing -s option."));

	return hmValues.find('s')->second;
}
/*************************************************************************/
ChangeParameters::~ChangeParameters() throw(){
	IAS_TRACER;
}
/*************************************************************************/
::org::invenireaude::qsystem::Ext::SystemChangePtr ChangeParameters::readFromFile(const String& strFileName){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Reading:"<<strFileName);

	IAS_DFT_FACTORY<DM::XML::XMLHelper>::PtrHolder
		ptrXMLHelper (IAS_DFT_FACTORY<DM::XML::XMLHelper>::Create(
					DataFactory::GetInstance()->getContaingDataFactory()));

	IAS_DFT_FACTORY<DM::XML::XMLDocument>::PtrHolder ptrDoc(ptrXMLHelper->readFile(strFileName));
	return DataFactory::GetInstance()->getSystemChangeType()->cast(ptrDoc->getRootObject());

}
/*************************************************************************/
static inline void _setXPath(DM::DataObject* dm, const String& strXPath, const String& strValue){
	IAS_TRACER;

	String strNewXPath(strXPath);

	while(strNewXPath.find('/')!=String::npos){

		String strProperty(strNewXPath.substr(0,strNewXPath.find('/')));

		if(!dm->isSet(strProperty))
			dm->createDataObject(strProperty);

		strNewXPath=strNewXPath.substr(strNewXPath.find('/')+1);
	}

	dm->setString(strXPath,strValue);
}
/*************************************************************************/
::org::invenireaude::qsystem::Ext::SystemChangePtr ChangeParameters::createFromCmdLine(const String& strAction,
		ParametersList& lstArguments){
	IAS_TRACER;

	Ext::SystemChangePtr dmResult;

	String strTypeName=String("Action")+strAction;
	String strURI(DataFactory::GetInstance()->getSystemChangeType()->getURI());

	Ext::ActionPtr dmAction;
	try{
		 dmAction = DataFactory::GetInstance()->getActionType()->cast(
				 DataFactory::GetInstance()->getContaingDataFactory()->getType(strURI,strTypeName)->createDataObject());
	}catch(Exception& e){
		throw ParameterException(strAction+" - action not found."+e.toString());
	}

	for(ParametersList::const_iterator it=lstArguments.begin();
		it != lstArguments.end(); it++){

		String strName;
		String strValue;
		TypeTools::ChopArguments(*it,strName, strValue);

		try{
			_setXPath(dmAction,strName,strValue);
		}catch(Exception& e){
			throw ParameterException(strName+" - attribute not found."+e.toString());
		}
	}
	dmResult=DataFactory::GetInstance()->getSystemChangeType()->createSystemChange();
	dmResult->setActions(dmAction);
	return dmResult;
}
/*************************************************************************/
::org::invenireaude::qsystem::Ext::ActionList& ChangeParameters::getActions(){
	IAS_TRACER;

	if(!dmSystemChange){
		if(hmIndicators.count('f') && hmIndicators.count('a'))
			IAS_THROW(ParameterException("Cannot specify both -f and -a"));

		if(!hmIndicators.count('f') && !hmIndicators.count('a'))
			IAS_THROW(ParameterException("At least one of -f or -a options required."));

		if(hmIndicators.count('f'))
			dmSystemChange=readFromFile(hmValues['f']);
		else
			dmSystemChange=createFromCmdLine(hmValues['a'],this->lstParameters);
	}

	return dmSystemChange->getActionsList();
}
/*************************************************************************/
void ChangeParameters::printCmdDesc(std::ostream& os) const{
	IAS_TRACER;

	os<<" [options] [parameter=value]* \n\n\tChanges SHM system."<<std::endl;

}
/*************************************************************************/
static void _printProperties(std::ostream& os, const DM::ComplexType* pComplex, String strPrefix){
	IAS_TRACER;

	const DM::PropertyList& lstProperties=pComplex->getProperties();

	for(int i=0;i<lstProperties.getSize();i++){

		os<<strPrefix<<std::right<<std::setw(32)<<lstProperties.getProperty(i)->getName()<<"  --->  ";

		const DM::Type *pType=lstProperties.getProperty(i)->getType();
		if(pType->isDataObjectType()){
			os<<std::endl;
			_printProperties(os,pType->asComplexType(),strPrefix+"     ");
		}else{
			os<<pType->getName()<<" : "<<pType->getURI();
			os<<std::endl;
		}
	}
}
/*************************************************************************/
void ChangeParameters::printArgsDesc(std::ostream& os) const{
	IAS_TRACER;

	os<<"\t\t-f <filename> \t actions definitions file containing: \n\t\t\t\t\t"
			<<DataFactory::GetInstance()->getSystemChangeType()->getName()<<":"
			<<DataFactory::GetInstance()->getSystemChangeType()->getURI()
			<<std::endl;
	os<<"\t or"<<std::endl;

	os<<"\t\t-a \t\t action (specify -h and -a to see action options)."<<std::endl;

	const DM::TypeList& lstTypes(DataFactory::GetInstance()->getContaingDataFactory()->getTypes());
	String strURI(DataFactory::GetInstance()->getSystemChangeType()->getURI());

	if(hmIndicators.count('a') && hmValues.count('a')){

		for(int iIdx=0;iIdx<lstTypes.getSize();iIdx++){
			const DM::Type *pType=lstTypes.at(iIdx);
			if(strURI.compare(pType->getURI())==0 &&
			   pType->getName().substr(0,6).compare("Action")==0 &&
			   hmValues.find('a')->second.compare(pType->getName().substr(6)) == 0){

				os<<"Properties for "<<hmValues.find('a')->second<<" are: "<<std::endl;
				_printProperties(os,pType->asComplexType(),"    ");

				return ;
			}
		}

	}

	os<<"\n\tAvailable actions are:"<<std::endl;
	for(int iIdx=0;iIdx<lstTypes.getSize();iIdx++){
		const DM::Type *pType=lstTypes.at(iIdx);
		if(strURI.compare(pType->getURI())==0 &&
		   pType->getName().substr(0,6).compare("Action")==0){
			os<<"\t\t"<<(pType->getName().substr(6))<<std::endl;
		}
	}

	os<<"\n\tExample:"<<std::endl;
	os<<"\t\t ias_qs_change -s sample -a CreateQueue queueDefinition/name=Q.START  queueDefinition/size=1"<<std::endl;
}
/*************************************************************************/
}
}
}
