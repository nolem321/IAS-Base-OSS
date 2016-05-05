/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/xpath/XPathAccessor.cpp
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
#include "XPathAccessor.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <lang/interpreter/exe/exception/NullObjectReferenceException.h>
#include <lang/interpreter/exe/exception/PropertyNotSetException.h>


#include "../../Context.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Expr {
namespace XPath {
/*************************************************************************/
XPathAccessor::Element::Element(String strName):
	pProperty(NULL){
	IAS_TRACER;
	this->strName=strName;
	bIsMulti=false;
}
/*************************************************************************/
XPathAccessor::Element::Element(String strName, Expr* pExpr){
	IAS_TRACER;
	this->strName=strName;
	ptrExpr=pExpr;
	bIsMulti=true;
	pProperty=NULL;
}
/*************************************************************************/
void XPathAccessor::Element::setProperty(const DM::Property *pProperty){
	IAS_TRACER;
	IAS_CHECK_IF_VALID(pProperty);
	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isDetailedInfo(),(void*)(this)<<":"<<(void*)pProperty);
	this->pProperty=pProperty;
}
/*************************************************************************/
const DM::Property *XPathAccessor::Element::getProperty() const {
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pProperty);
	return pProperty;
}
/*************************************************************************/
XPathAccessor::XPathAccessor():
	pValueProperty(NULL),
	bArrayExp(false){
	IAS_TRACER;
}
/*************************************************************************/
XPathAccessor::~XPathAccessor() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void XPathAccessor::addSingleElement(const String& strName){
	IAS_TRACER;

	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isDetailedInfo(),((void*)this)<<" add: "<<strName);

	addElement(IAS_DFT_FACTORY<Element>::Create(strName));
}
/*************************************************************************/
void XPathAccessor::addMultiElement(const String& strName,
									Expr* pExpr){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pExpr);
	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isDetailedInfo(),((void*)this)<<" add: "<<strName);
	addElement(IAS_DFT_FACTORY<Element>::Create(strName,pExpr));
}
/*************************************************************************/
void XPathAccessor::addElement(XPathAccessor::Element *pElement){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pElement);

	phcElements.addPointer(pElement);
	lstElements.push_back(pElement);
}
/*************************************************************************/
const DM::Property  *XPathAccessor::getValueProperty() const{
	IAS_TRACER;
	IAS_CHECK_IF_VALID(pValueProperty);
	return pValueProperty;
}
/*************************************************************************/
void XPathAccessor::computeProperties(const DM::ComplexType *pComplexType){


	IAS_CHECK_IF_VALID(pComplexType);


	for(ElementList::const_iterator it = lstElements.begin();
		it != lstElements.end();
		it++){

		pValueProperty = pComplexType->getProperties().getProperty((*it)->getName());

		IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isDetailedInfo(),((*it)->getName())<<((void*)this)<<" in "<<pValueProperty->getType()->getName());

		if(it + 1 != lstElements.end())
			pComplexType=pValueProperty->getType()->asComplexType();
		else{
			bArrayExp= (!(*it)->isMulti()) && pValueProperty->isMulti();
		}

		(*it)->setProperty(pValueProperty);
	}


	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isDetailedInfo(),"Array? : "<<bArrayExp);

}
/*************************************************************************/
DM::DataObject* XPathAccessor::getTargetObject(DM::DataObject* pParent, Context *pCtx) const{
	IAS_TRACER;

	IAS_CHECK_IF_VALID(pParent);
	DM::DataObject* pResult = pParent;

	for(ElementList::const_iterator it = lstElements.begin();
		it != lstElements.end();
		it++){

			IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isDetailedInfo(),(*it)->getName());

			if((*it)->isMulti()){
				int iIdx = (*it)->getMultiExpr()->evaluateInt(pCtx);
				DM::DataObjectList& lstValues = pResult->getList((*it)->getProperty());
				pResult = lstValues.at(iIdx);
			}else{

				try{
					pResult = pResult->getDataObject((*it)->getProperty());
				}catch(DM::RuntimeException& e){
					IAS_THROW(PropertyNotSetException((*it)->getProperty()->getName()));
				}

			}

			if(!pResult)
				IAS_THROW(NullObjectReferenceException((*it)->getProperty()->getName()));
	}

	return pResult;
}

/*************************************************************************/
ExprResultSetter XPathAccessor::getTargetObjectSetter(DM::DataObject* pParent, Context *pCtx) const{
	IAS_TRACER;

	IAS_CHECK_IF_VALID(pParent);
	DM::DataObjectPtr pResult = pParent;

	ElementList::const_iterator it = lstElements.begin();

	while(it + 1 != lstElements.end()){

			IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isDetailedInfo(),(*it)->getName());

			if((*it)->isMulti()){
				int iIdx = (*it)->getMultiExpr()->evaluateInt(pCtx);
				DM::DataObjectList& lstValues = pResult->getList((*it)->getProperty());
				pResult = lstValues.at(iIdx);
			}else{
				if(pResult->isSet((*it)->getProperty()))
					pResult = pResult->getDataObject((*it)->getProperty());
				else
					pResult = pResult->createDataObject((*it)->getProperty());
			}

		it++;
	}

	if( (*it)->isMulti() ){
		return ExprResultSetter(pResult,pValueProperty, (*it)->getMultiExpr()->evaluateInt(pCtx));
	}else{
		return ExprResultSetter(pResult,pValueProperty);
	}
}
/*************************************************************************/
DM::DataObjectList& XPathAccessor::getTargetObjectList(DM::DataObject* pParent, Context *pCtx) const{
	IAS_TRACER;

	IAS_CHECK_IF_VALID(pParent);
	DM::DataObject* pResult = pParent;

	for(ElementList::const_iterator it = lstElements.begin();
		it + 1!= lstElements.end();
		it++){

			IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isDetailedInfo(),(*it)->getName());

			if((*it)->isMulti()){
				int iIdx = (*it)->getMultiExpr()->evaluateInt(pCtx);
				DM::DataObjectList& lstValues = pResult->getList((*it)->getProperty());
				pResult = lstValues.at(iIdx);
			}else{
				pResult = pResult->getDataObject((*it)->getProperty());
			}
	}

	return pResult->getList(pValueProperty);
}

/*************************************************************************/
void XPathAccessor::deleteDataObject(DM::DataObject* pParent, Context *pCtx)const{
	IAS_TRACER;

	IAS_CHECK_IF_VALID(pParent);
	DM::DataObject* pResult = pParent;

	ElementList::const_iterator it = lstElements.begin();

	while(it + 1 != lstElements.end()) {

		IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isDetailedInfo(),(*it)->getName());

		if ((*it)->isMulti()) {
			int iIdx = (*it)->getMultiExpr()->evaluateInt(pCtx);
			DM::DataObjectList& lstValues = pResult->getList((*it)->getProperty());
			pResult = lstValues.at(iIdx);
		} else {
			pResult = pResult->getDataObject((*it)->getProperty());
		}
		it++;
	}

	if((*it)->isMulti()){
		int iIdx = (*it)->getMultiExpr()->evaluateInt(pCtx);
		pResult->getList((*it)->getProperty()).remove(iIdx);
	}else{
		pResult->unset((*it)->getProperty());
	}

}
/*************************************************************************/
bool XPathAccessor::isSet(DM::DataObject* pParent, Context *pCtx)const{
	IAS_TRACER;

	IAS_CHECK_IF_VALID(pParent);
	DM::DataObject* pResult = pParent;

	ElementList::const_iterator it = lstElements.begin();

	while(it + 1 != lstElements.end()) {

		IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isDetailedInfo(),(*it)->getName());

		if ((*it)->isMulti()) {
			int iIdx = (*it)->getMultiExpr()->evaluateInt(pCtx);
			DM::DataObjectList& lstValues = pResult->getList((*it)->getProperty());
			pResult = lstValues.at(iIdx);
		} else {

			if(! pResult->isSet((*it)->getProperty()))
				return false;

			pResult = pResult->getDataObject((*it)->getProperty());
		}
		it++;
	}

	if((*it)->isMulti()){
		int iIdx = (*it)->getMultiExpr()->evaluateInt(pCtx);
		return pResult->getList((*it)->getProperty()).size() > iIdx;
	}else{
		return pResult->isSet((*it)->getProperty());
	}

}
/*************************************************************************/
bool XPathAccessor::isNull(DM::DataObject* pParent, Context *pCtx)const{
	IAS_TRACER;

	IAS_CHECK_IF_VALID(pParent);
	DM::DataObject* pResult = pParent;

	ElementList::const_iterator it = lstElements.begin();

	while(it + 1 != lstElements.end()) {

		IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isDetailedInfo(),(*it)->getName());

		if ((*it)->isMulti()) {
			int iIdx = (*it)->getMultiExpr()->evaluateInt(pCtx);
			DM::DataObjectList& lstValues = pResult->getList((*it)->getProperty());
			pResult = lstValues.at(iIdx);
		} else {

			if(! pResult->isSet((*it)->getProperty()))
				return false;

			pResult = pResult->getDataObject((*it)->getProperty());
		}
		it++;
	}

	if((*it)->isMulti()){
		int iIdx = (*it)->getMultiExpr()->evaluateInt(pCtx);

		const DM::DataObjectList& lstDataObjects(pResult->getList((*it)->getProperty()));

		if(lstDataObjects.size() <= iIdx)
			return false;

		return lstDataObjects.at(iIdx) == NULL;
	}else{

		if(!pResult->isSet((*it)->getProperty()))
			return false;

		return pResult->getDataObject((*it)->getProperty()) == NULL;

	}

}
/*************************************************************************/
}
}
}
}
}
}
