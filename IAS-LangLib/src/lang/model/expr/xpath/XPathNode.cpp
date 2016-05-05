/*
 * File: IAS-LangLib/src/lang/model/expr/xpath/XPathNode.cpp
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
#include "XPathNode.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "../ExprNode.h"

namespace IAS {
namespace Lang {
namespace Model {
namespace Expr {
namespace XPath {


/*************************************************************************/
XPathNode::Element::Element(String strName){
	IAS_TRACER;
	this->strName=strName;
	bIsMulti=false;
}
/*************************************************************************/
XPathNode::Element::Element(String strName, ExprNode* pExprNode){
	IAS_TRACER;
	this->strName=strName;
	ptrExprNode=pExprNode;
	bIsMulti=true;
}
/*************************************************************************/
XPathNode::XPathNode(){
	IAS_TRACER;

}
/*************************************************************************/
XPathNode::~XPathNode() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void XPathNode::addSingleElement(const String& strName){
	IAS_TRACER;

	addElement(IAS_DFT_FACTORY<Element>::Create(strName));
}
/*************************************************************************/
void XPathNode::addMultiElement(const String& strName,
									ExprNode* pExprNode){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pExprNode);
	addElement(IAS_DFT_FACTORY<Element>::Create(strName,pExprNode));
}
/*************************************************************************/
void XPathNode::addElement(XPathNode::Element *pElement){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pElement);

	phcElements.addPointer(pElement);
	lstElements.push_back(pElement);
}
/*************************************************************************/
}
}
}
}
}
