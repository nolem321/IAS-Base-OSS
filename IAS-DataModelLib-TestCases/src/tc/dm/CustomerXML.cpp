/*
 * File: IAS-DataModelLib-TestCases/src/tc/dm/CustomerXML.cpp
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
#include "../dm/CustomerXML.h"
#include <commonlib/commonlib.h>

#include <dm/Impl/DataFactory.h>

namespace IAS {
namespace TC {
namespace DM {

/*************************************************************************/
CustomerXML::CustomerXML(TestSuite* pTestSuite) throw():theTestRunner(this){
	IAS_TRACER;
	std::cout<<"CustomerXML, creation:\n";
	init(pTestSuite);
}

/*************************************************************************/
CustomerXML::~CustomerXML() throw(){
	IAS_TRACER;
	std::cout<<"CustomerXML, clean up:\n";
}

/*************************************************************************/
void CustomerXML::caseALL(){
	IAS_TRACER;

	IAS_DFT_FACTORY< XML::XSDHelper >::PtrHolder ptrXSDHelper(IAS_DFT_FACTORY< XML::XSDHelper >::Create(ptrDataFactory.getPointer()));

	ptrXSDHelper->defineTypesFromFile("testdata/customer.xsd");
	//ptrXMLHelper->defineTypesFromFile("/home/albert/Workspaces/REB2-SVN-Galileo/REB-Catalog-XML/XML/operations.XML");

	Type* pCustomerType = ptrDataFactory->getType("http://www.examples.org/akc","Customer");

	DataObjectPtr ptrCustomer(pCustomerType->createDataObject());

	ptrCustomer->createDataObject("firstname");
	ptrCustomer->setDataObject("lastname",ptrDataFactory->getDefaultType(Type::TextType)->createDataObject());
	ptrCustomer->setString("middlename","Mr.");
	ptrCustomer->createDataObject("age");
	ptrCustomer->setString("age","10");
	ptrCustomer->createDataObject("address");
	ptrCustomer->createDataObject("address");
	ptrCustomer->createDataObject("address");

	const Type* pTypeF = ptrDataFactory->getType("http://www.examples.org/akcf","Address");

	DataObjectPtr ptrForeignAddress(pTypeF->createDataObject());
	ptrForeignAddress->setString("country","Laponia");
	//ptrCustomer->setDataObject("address",ptrForeignAddress.pass());
	ptrCustomer->createDataObject("mailingAddress");

	//inspect(ptrCustomer,std::cout,"Root");

	ptrCustomer->createDataObject("age");
	ptrCustomer->setString("address[1]/street","Sezamowa");
	ptrCustomer->setString("address[1]/block","102");
	ptrCustomer->getDataObject("address[0]")->setString("block","202");

	//DataObject *pTmp = ptrCustomer->getList("address").at(2);
	//pTmp->setString("street","Longview");

	ptrCustomer->setDateTime("birth",DateTime(true));
	ptrCustomer->setDateTime("address[2]/street",ptrCustomer->getDateTime("birth"));
	ptrCustomer->setString("address[2]/block","7");

	inspect(ptrCustomer,std::cout,"Root");

	IAS_DFT_FACTORY< XML::XMLHelper >::PtrHolder ptrXMLHelper(IAS_DFT_FACTORY< XML::XMLHelper >::Create(ptrDataFactory.getPointer()));

	//ptrXMLHelper->save(strOutput,ptrCustomer,"a","http://www.examples.org/akc");
	StringStream ssTmp;
	ptrXMLHelper->save(ssTmp,ptrCustomer,"a","http://www.examples.org/akc");
	//std::cout<<XML::XMLHelper::Stringify(ptrDataFactory,ptrCustomer);

	String strOutput(ssTmp.str());
	std::cout<<strOutput;

	IAS_DFT_FACTORY< XML::XMLDocument >::PtrHolder ptrDoc(
			ptrXMLHelper->readStream(ssTmp));

	inspect(ptrDoc->getRootObject(),std::cout,"Saved");

	std::cout<<XML::XMLHelper::Stringify(ptrDataFactory,ptrDoc->getRootObject())<<std::endl;
}

/*************************************************************************/
void CustomerXML::inspect(DataObject *pDataObject, std::ostream& os, String strIndent){
	IAS_TRACER;

	const Type* pType = pDataObject->getType();
	os<<strIndent<<"=";
	switch(pType->getTypeEnum()){

		case Type::BooleanType:
		case Type::TextType:
		case Type::IntegerType:
			os<<'"'<<pDataObject->toString()<<'"';
			os<<" of [";
			os<<pType->getURI()<<":"<<pType->getName();
			os<<"]";
			break;

		case Type::DataObjectType:
			os<<"\n";
			const PropertyList &lstProperties = pType->asComplexType()->getProperties();
			for(int i=0; i<lstProperties.getSize(); i++){
				String strNewIndent(strIndent);
				strNewIndent+=".";
				strNewIndent+=lstProperties.getProperty(i)->getName();

				if(! lstProperties.getProperty(i)->isMulti()){
					try{
						inspect(pDataObject->getDataObject(lstProperties.getProperty(i)),os,strNewIndent);
					}catch(RuntimeException& e){
						os<<strNewIndent<<" not set \n";
					}
				}else{

					DataObjectList& list = pDataObject->getList(lstProperties.getProperty(i));

					os<<strNewIndent<<".size="<<list.size()<<"\n";

					for(int j=0; j<list.size(); j++){
						StringStream ssNewIndentWithIdx;
						ssNewIndentWithIdx<<strNewIndent<<"["<<j<<"]";
						inspect(list.at(j),os,ssNewIndentWithIdx.str());
					}


				}

			}
			break;
	}

	os<<"\n";
}
/*************************************************************************/
void CustomerXML::init(TestSuite* pTestSuite) {
	IAS_TRACER;

	ptrDataFactory = IAS_DFT_FACTORY< ::IAS::DM::Impl::DataFactory >::Create();

	theTestRunner.addCase("ALL",&::IAS::TC::DM::CustomerXML::caseALL);
	::IAS::TestUnit::init("CustomerXML",&theTestRunner, pTestSuite);
}
/*************************************************************************/
}
}
}
