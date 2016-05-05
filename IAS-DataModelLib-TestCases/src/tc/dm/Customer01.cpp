/*
 * File: IAS-DataModelLib-TestCases/src/tc/dm/Customer01.cpp
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
#include "../dm/Customer01.h"
#include <commonlib/commonlib.h>

#include <dm/Impl/DataFactory.h>


namespace IAS {
namespace TC {
namespace DM {

/*************************************************************************/
Customer01::Customer01(TestSuite* pTestSuite) throw():theTestRunner(this){
	IAS_TRACER;
	std::cout<<"Customer01, creation:\n";
	init(pTestSuite);
}

/*************************************************************************/
Customer01::~Customer01() throw(){
	IAS_TRACER;
	std::cout<<"Customer01, clean up:\n";
}

/*************************************************************************/
void Customer01::init(TestSuite* pTestSuite) {
	IAS_TRACER;

	ptrDataFactory = IAS_DFT_FACTORY< ::IAS::DM::Impl::DataFactory >::Create();

	theTestRunner.addCase("ALL",&::IAS::TC::DM::Customer01::caseALL);
	::IAS::TestUnit::init("Customer01",&theTestRunner, pTestSuite);
}
/*************************************************************************/
void Customer01::caseALL(){
	IAS_TRACER;

	Type *pAddressType = ptrDataFactory->defineType("ABC","Address");
	ComplexType *pAddressComplexType =  pAddressType->asComplexType();

	pAddressComplexType->defineProperty("street",ptrDataFactory->getDefaultType(Type::TextType));
	pAddressComplexType->defineProperty("block",ptrDataFactory->getDefaultType(Type::IntegerType));
	pAddressComplexType->defineProperty("city",ptrDataFactory->getDefaultType(Type::TextType));

	Type *pCustomerType = ptrDataFactory->defineType("ABC","Customer");
	ComplexType *pCustomerComplexType =  pCustomerType->asComplexType();

	pCustomerComplexType->defineProperty("firstname",ptrDataFactory->getDefaultType(Type::TextType));
	pCustomerComplexType->defineProperty("midname",ptrDataFactory->getDefaultType(Type::TextType));
	pCustomerComplexType->defineProperty("lastname",ptrDataFactory->getDefaultType(Type::TextType));
	pCustomerComplexType->defineProperty("age",ptrDataFactory->getDefaultType(Type::IntegerType));
	pCustomerComplexType->defineProperty("address",pAddressType);
	pCustomerComplexType->defineProperty("otherAddresses",pAddressType,true);


	DataObjectPtr ptrCustomer(pCustomerType->createDataObject());
	ptrCustomer->createDataObject("firstname");
	ptrCustomer->setDataObject("lastname",ptrDataFactory->getDefaultType(Type::TextType)->createDataObject("abc"));
	DataObjectPtr ptrMidName = ptrDataFactory->getDefaultType(Type::TextType)->createDataObject(String("Jr"));
	ptrCustomer->setDataObject("midname",ptrMidName);
	ptrCustomer->createDataObject("age");
	std::cerr<<"info 1\n";
	ptrCustomer->setString("age","10");
	ptrCustomer->setDataObject("address",pAddressType->createDataObject());
	ptrCustomer->setDataObject("otherAddresses",pAddressType->createDataObject());
	ptrCustomer->setDataObject("otherAddresses",pAddressType->createDataObject());
	ptrCustomer->setDataObject("otherAddresses",pAddressType->createDataObject());
	ptrCustomer->setDataObject("otherAddresses",pAddressType->createDataObject());

	std::cout<<"Inspect 2 ===================================================\n";

	inspect(ptrCustomer,std::cout,"Root");

	ptrCustomer->createDataObject("age");
	ptrCustomer->createDataObject("age");
	ptrCustomer->setString("address/street","Sezamowa");
	ptrCustomer->setString("address/block","102");
	ptrCustomer->setString("address/block","103");
	ptrCustomer->getDataObject("address")->setString("block","202");

	DataObject *pTmp = ptrCustomer->getList(pCustomerComplexType->getProperties().getProperty("otherAddresses")).at(1);
	DataObjectList& lst = ptrCustomer->getList(pCustomerComplexType->getProperties().getProperty("otherAddresses"));
	lst.add(pAddressType->createDataObject());
	pTmp->setString("block","666");

	ptrCustomer->setString("otherAddresses[2]/block","7");
	ptrCustomer->setString("otherAddresses[3]/block","333");
	ptrCustomer->setString("otherAddresses[4]/block","444");
	ptrCustomer->setString("otherAddresses[3]/city","c333");
	ptrCustomer->setString("otherAddresses[4]/city","c444");

	ptrCustomer->setString("otherAddresses[0]/block","9");
	std::cout<<"Inspect 2 ===================================================\n";
	inspect(ptrCustomer,std::cout,"Root");
	std::cout<<"Copy ===================================================\n";
	//DataObjectPtr ptrCustomerCopy(ptrCustomer->duplicate());
	//inspect(ptrCustomerCopy,std::cout,"Copy");
}

/*************************************************************************/
void Customer01::inspect(DataObject *pDataObject, std::ostream& os, String strIndent){
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
						if(pDataObject->isSet(lstProperties.getProperty(i)))
							inspect(pDataObject->getDataObject(lstProperties.getProperty(i)),os,strNewIndent);
						else
							os<<strNewIndent<<"=_EMPTY_\n";

					}catch(RuntimeException& e){
						os<<strNewIndent<<"exception:"<<e.toString()<<"\n";
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
}
}
}
