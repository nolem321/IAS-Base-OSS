/*
 * File: IAS-DataModelLib-TestCases/src/tc/dm/CustomerXSD.cpp
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
#include "../dm/CustomerXSD.h"
#include <commonlib/commonlib.h>

#include <dm/Impl/DataFactory.h>

extern "C"{
	extern void xmlMemoryDump();
}

namespace IAS {
namespace TC {
namespace DM {

/*************************************************************************/
CustomerXSD::CustomerXSD(TestSuite* pTestSuite) throw():theTestRunner(this){
	IAS_TRACER;
	std::cout<<"CustomerXSD, creation:\n";
	init(pTestSuite);
}

/*************************************************************************/
CustomerXSD::~CustomerXSD() throw(){
	IAS_TRACER;
	std::cout<<"CustomerXSD, clean up:\n";
}

/*************************************************************************/
void CustomerXSD::caseALL(){
	IAS_TRACER;


	IAS_DFT_FACTORY< XML::XSDHelper >::PtrHolder ptrXSDHelper(IAS_DFT_FACTORY< XML::XSDHelper >::Create(ptrDataFactory.getPointer()));

	ptrXSDHelper->defineTypesFromFile("testdata/customer.xsd");

	//sleep(5);
	//std::cout<<"--------before waiting----------\n";
	//ptrXSDHelper->defineTypesFromFile("/home/albert/Workspaces/REB2-SVN-Galileo/REB-Catalog-XSD/xsd/operations.xsd");
	//std::cout<<"--------defined----------\n";
	//sleep(5);
	//std::cout<<"--------waiting----------\n";
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
	ptrCustomer->setDataObject("address",ptrForeignAddress);
	ptrCustomer->createDataObject("mailingAddress");


	//inspect(ptrCustomer,std::cout,"Root");

	ptrCustomer->createDataObject("age");
	//ptrCustomer->setString("address[1]/street","Sezamowa");
	//ptrCustomer->setString("address[1]/block","102");
	//ptrCustomer->getDataObject("address[0]")->setString("block","202");

	//DataObject *pTmp = ptrCustomer->getList("address").at(2);
	//pTmp->setString("street","Longview");

	//ptrCustomer->setString("address[2]/block","7");

	//inspect(ptrCustomer,std::cout,"Root");

	IAS_DFT_FACTORY< XML::XMLHelper >::PtrHolder ptrXMLHelper(IAS_DFT_FACTORY< XML::XMLHelper >::Create(ptrDataFactory.getPointer()));

	String strOutput;
	ptrXMLHelper->save(strOutput,ptrCustomer,"","");
	std::cout<<strOutput;


	return;

	IAS_DFT_FACTORY< XML::XMLDocument >::PtrHolder ptrDoc(ptrXMLHelper->readString(strOutput));

	DataObjectPtr ptrDataObject(ptrDoc->getRootObject());
	ptrXMLHelper->save(strOutput,ptrDataObject,"","");
	std::cout<<strOutput;
	ptrDataObject->setString("header/postingTimestamp/value","TEST");
	ptrXMLHelper->save(strOutput,ptrDataObject,"","");
	std::cout<<strOutput;

	std::cout<<"---------------------\n";
	std::cout<<"---------------------\n";

	Timestamp t(true);

	return;

	/*
	std::cout<<t.toString()<<"\n";

	for(int i=0;i<10000;i++){
		PtrHolder<XML::XMLDocument> ptrDoc(ptrXMLHelper->readString(strOutput));
	}
	t.setCurrent();
	std::cout<<t.toString()<<"\n";

	for(int i=0;i<10000;i++){
		ptrXMLHelper->save(strOutput,ptrDataObject,"","");
	}
	t.setCurrent();
	std::cout<<t.toString()<<"\n";


	std::cout<<"---------------------\n";
*/

}

/*************************************************************************/
void CustomerXSD::inspect(DataObject *pDataObject, std::ostream& os, String strIndent){
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
void CustomerXSD::init(TestSuite* pTestSuite) {
	IAS_TRACER;

	ptrDataFactory = IAS_DFT_FACTORY< ::IAS::DM::Impl::DataFactory >::Create();

	theTestRunner.addCase("ALL",&::IAS::TC::DM::CustomerXSD::caseALL);
	::IAS::TestUnit::init("CustomerXSD",&theTestRunner, pTestSuite);
}
/*************************************************************************/
}
}
}
