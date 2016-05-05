/*
 * File: IAS-DataModelLib-TestCases/src/tc/dm/CustomerJSON.cpp
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
#include "../dm/CustomerJSON.h"
#include <commonlib/commonlib.h>

#include <dm/Impl/DataFactory.h>
#include <dm/json/JSONHelper.h>

namespace IAS {
namespace TC {
namespace DM {

/*************************************************************************/
CustomerJSON::CustomerJSON(TestSuite* pTestSuite) throw():theTestRunner(this){
	IAS_TRACER;
	std::cout<<"CustomerJSON, creation:\n";
	init(pTestSuite);
}

/*************************************************************************/
CustomerJSON::~CustomerJSON() throw(){
	IAS_TRACER;
	std::cout<<"CustomerJSON, clean up:\n";
}

/*************************************************************************/
void CustomerJSON::caseALL(){
	IAS_TRACER;

	IAS_DFT_FACTORY< XML::XSDHelper >::PtrHolder ptrXSDHelper(IAS_DFT_FACTORY< XML::XSDHelper >::Create(ptrDataFactory.getPointer()));

	ptrXSDHelper->defineTypesFromFile("testdata/customer.xsd");
	//ptrJSONHelper->defineTypesFromFile("/home/albert/Workspaces/REB2-SVN-Galileo/REB-Catalog-JSON/JSON/operations.JSON");

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

	std::cout<<"============== ORIGINAL ================= "<<std::endl;
	inspect(ptrCustomer,std::cout,"Root");
	std::cout<<"============== ORIGINAL ================= "<<std::endl;

	IAS_DFT_FACTORY< JSON::JSONHelper >::PtrHolder ptrJSONHelper(IAS_DFT_FACTORY< JSON::JSONHelper >::Create(ptrDataFactory.getPointer()));

	StringStream ssOutput;
	ptrJSONHelper->save(ssOutput,ptrCustomer);
	std::cout<<"============== JSON ================= "<<std::endl;
	std::cout<<ssOutput.str();
	std::cout<<"============== JSON ================= "<<std::endl;

	IAS::DM::DataObjectPtr dmNew(ptrJSONHelper->load(ssOutput));

	std::cout<<"============== NEW ================= "<<std::endl;
	inspect(dmNew,std::cout,"Saved");
	std::cout<<"============== NEW ================= "<<std::endl;

}

/*************************************************************************/
void CustomerJSON::inspect(DataObject *pDataObject, std::ostream& os, String strIndent){
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
void CustomerJSON::init(TestSuite* pTestSuite) {
	IAS_TRACER;

	ptrDataFactory = IAS_DFT_FACTORY< ::IAS::DM::Impl::DataFactory >::Create();

	theTestRunner.addCase("ALL",&::IAS::TC::DM::CustomerJSON::caseALL);
	::IAS::TestUnit::init("CustomerJSON",&theTestRunner, pTestSuite);
}
/*************************************************************************/
}
}
}
