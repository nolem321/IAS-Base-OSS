/*
 * File: IAS-DataModelLib/src/dm/gen/CppCodeGenerator.cpp
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
#include "../../dm/gen/CppCodeGenerator.h"
#include <commonlib/commonlib.h>

#include "../../dm/gen/Impl/CppCodeGeneratorLogic.h"
#include "../../dm/Impl/DataFactory.h"

namespace IAS {
namespace DM {
namespace Gen {
/*************************************************************************/
CppCodeGenerator::CppCodeGenerator() throw(){
	IAS_TRACER;
	ptrDataFactory = IAS_DFT_FACTORY< ::IAS::DM::Impl::DataFactory >::Create();
	ptrXSDHelper = IAS_DFT_FACTORY<XML::XSDHelper>::Create(ptrDataFactory.getPointer());
}
/*************************************************************************/
CppCodeGenerator::~CppCodeGenerator() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void CppCodeGenerator::loadModel(const String& strModelFile){
	IAS_TRACER;

	ptrXSDHelper->defineTypesFromFile(strModelFile);

}
/*************************************************************************/
void CppCodeGenerator::setNamespaces(const StringList& lstNamespaces){
	IAS_TRACER;
	this->lstNamespaces=lstNamespaces;
}
/*************************************************************************/
void CppCodeGenerator::generateCode(const String& strBaseDir, bool bSingleDataObjectFile){
	IAS_TRACER;

	IAS_DFT_FACTORY<Gen::Impl::CppCodeGeneratorLogic>::PtrHolder ptrLogic;
	ptrLogic = IAS_DFT_FACTORY<Gen::Impl::CppCodeGeneratorLogic>::Create(ptrDataFactory.getPointer(),strBaseDir);

	ptrLogic->setSingleDataObjectFile(bSingleDataObjectFile);
	ptrLogic->generate(lstNamespaces);
}
/*************************************************************************/
}
}
}
