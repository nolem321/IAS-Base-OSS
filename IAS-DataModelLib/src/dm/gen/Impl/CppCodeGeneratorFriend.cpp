/*
 * File: IAS-DataModelLib/src/dm/gen/Impl/CppCodeGeneratorFriend.cpp
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
#include "../../../dm/gen/Impl/CppCodeGeneratorFriend.h"
#include <commonlib/commonlib.h>
#include "../../../dm/gen/Impl/Helpers.h"

namespace IAS {
namespace DM {
namespace Gen {
namespace Impl {

/*************************************************************************/
CppCodeGeneratorFriend::CppCodeGeneratorFriend(CppCodeGeneratorLogic* pParent):
		pParent(pParent){
	IAS_TRACER;
}
/*************************************************************************/
CppCodeGeneratorFriend::~CppCodeGeneratorFriend()throw(){}
/*************************************************************************/
bool CppCodeGeneratorFriend::hasDataObjectMethods(const DM::Type* pType) const{
	IAS_TRACER;
	return !pType->isDataObjectType() && pType->getTypeEnum() != DM::Type::AnyType;
}
/*************************************************************************/
void CppCodeGeneratorFriend::beginStandardNamespaces(OutputFile* pFile) const{
	IAS_TRACER;

	pParent->printNamespace(pFile->getStreamRef(),
							pParent->patterns.ptrNamespace_start,
							pParent->lstStandardNamespaces);

}
/*************************************************************************/
void CppCodeGeneratorFriend::endStandardNamespaces(OutputFile* pFile) const{
	IAS_TRACER;

	pParent->printNamespace(pFile->getStreamRef(),
							pParent->patterns.ptrNamespace_end,
							pParent->lstStandardNamespaces,true);

}
/*************************************************************************/
void CppCodeGeneratorFriend::beginTypeNamespaces(OutputFile* pFile,
											     const StringList& strNSParts) const{
	IAS_TRACER;

	pParent->printNamespace(pFile->getStreamRef(),
							pParent->patterns.ptrNamespace_start,
							strNSParts);

}
/*************************************************************************/
void CppCodeGeneratorFriend::endTypeNamespaces(OutputFile* pFile,
											   const StringList& strNSParts) const{
	IAS_TRACER;

	pParent->printNamespace(pFile->getStreamRef(),
							pParent->patterns.ptrNamespace_end,
							strNSParts,true);

}
/*************************************************************************/
bool CppCodeGeneratorFriend::isGeneratedType(const DM::Type* pType) const{
	IAS_TRACER;
	return getNSMap().count(pType->getURI()) > 0;
}
/*************************************************************************/
String CppCodeGeneratorFriend::computeDataObjectType(const Type* pType, bool bPointer) const{
	IAS_TRACER;
	String strResult;

	strResult+="::";
	strResult+=Helpers::URIToPrefix(pType->getURI());
	strResult+="::";
	strResult+=pType->getName();

	if(bPointer)
		strResult+="*";
	return strResult;
}
/*************************************************************************/
String CppCodeGeneratorFriend::computeReturnType(const Type* pType) const{
	IAS_TRACER;

	IAS_CHECK_IF_VALID(pType);


	switch(pType->getTypeEnum()){

		case Type::BooleanType: 			return "bool";
		case Type::IntegerType: 			return "int";
		case Type::FloatType:   			return "::IAS::Float";
		case Type::TextType:		        return "::IAS::String";

		case Type::TimeType:				return "::IAS::Time";
		case Type::DateType:				return "::IAS::Date";
		case Type::DateTimeType:			return "::IAS::DateTime";


		case Type::AnyType:                 return "::IAS::DM::DataObjectPtr";

		case Type::DataObjectType:			return computeDataObjectType(pType,true);
		default:

			StringStream ssInfo;
			ssInfo<<"unknown or unsupported dm::Type::Types["<<pType->getName();
			ssInfo<<":"<<pType->getTypeEnum()<<"]";
			IAS_THROW(InternalException(ssInfo.str()));
	}

}
/*************************************************************************/
String CppCodeGeneratorFriend::computeReturnListType(const Type* pType) const{
	IAS_TRACER;

	IAS_CHECK_IF_VALID(pType);

	if(pType->getURI().compare(DataFactory::BuildInTypesNamespace) == 0)
		switch(pType->getTypeEnum()){

			case Type::BooleanType: 			return "::IAS::DM::Default::Ext::Boolean";
			case Type::IntegerType: 			return "::IAS::DM::Default::Ext::Integer";
			case Type::FloatType:   			return "::IAS::DM::Default::Ext::Float";
			case Type::TextType:		        return "::IAS::DM::Default::Ext::String";
			case Type::DateType:    	        return "::IAS::DM::Default::Ext::Date";
			case Type::TimeType: 	            return "::IAS::DM::Default::Ext::Time";
			case Type::DateTimeType:            return "::IAS::DM::Default::Ext::DateTime";
			case Type::AnyType:                 return "::IAS::DM::DataObjectPtr";
			case Type::DataObjectType:			return computeDataObjectType(pType,false);

		default:

			StringStream ssInfo;
			ssInfo<<"unknown or unsupported dm::Type::Types["<<pType->getName();
			ssInfo<<":"<<pType->getTypeEnum()<<":";
			IAS_THROW(InternalException(ssInfo.str()));
	}

	String strResult;

	strResult+="::";
	strResult+=Helpers::URIToPrefix(pType->getURI());
	strResult+="::Ext::";
	strResult+=pType->getName();

	return strResult;
}

/*************************************************************************/
String CppCodeGeneratorFriend::computeSetterType(const Type* pType) const{
	IAS_TRACER;
	IAS_CHECK_IF_VALID(pType);

	switch(pType->getTypeEnum()){

			case Type::BooleanType: 			return "bool";
			case Type::IntegerType: 			return "int";
			case Type::FloatType:   			return "::IAS::Float";
			case Type::TextType:		        return "const ::IAS::String&";

			case Type::DateType:	 	        return "const ::IAS::Date&";
			case Type::TimeType:	    	    return "const ::IAS::Time&";
			case Type::DateTimeType:	        return "const ::IAS::DateTime&";

			case Type::AnyType:                 return "::IAS::DM::DataObjectPtr";
			case Type::DataObjectType:			return computeDataObjectType(pType,true);

			default:

				StringStream ssInfo;
				ssInfo<<"unknown or unsupported dm::Type::Types["<<pType->getName();
				ssInfo<<":"<<pType->getTypeEnum()<<":";
				IAS_THROW(InternalException(ssInfo.str()));
		}

}
/*************************************************************************/
String CppCodeGeneratorFriend::computeDMSetterMethod(const Type* pType) const{
	IAS_TRACER;

	IAS_CHECK_IF_VALID(pType);
	String strResult;

	//if(pType->getURI().compare(DataFactory::BuildInTypesNamespace))

	switch(pType->getTypeEnum()){

		case Type::BooleanType:
			return "Boolean";

		case Type::IntegerType:
			return "Integer";

		case Type::FloatType:
			return "Float";

		case Type::TextType:
			return "String";

		case Type::DateType:
			return "Date";

		case Type::TimeType:
			return "Time";

		case Type::DateTimeType:
			return "DateTime";

		case Type::AnyType:
		case Type::DataObjectType:
			return "DataObject";

		default:

			StringStream ssInfo;
			ssInfo<<"unknown or unsupported dm::Type::Types["<<pType->getName();
			ssInfo<<":"<<pType->getTypeEnum()<<":";
			IAS_THROW(InternalException(ssInfo.str()));
	}

}
/*************************************************************************/
String CppCodeGeneratorFriend::computeImplClass(const Type* pType) const{
	IAS_TRACER;

	IAS_CHECK_IF_VALID(pType);
	String strResult;


	switch(pType->getTypeEnum()){

		case Type::BooleanType:		return "Boolean";
		case Type::IntegerType:		return "Integer";
		case Type::FloatType:      	return "Float";
		case Type::TextType:	 	return "String";

		case Type::DateType:		return "Date";
		case Type::TimeType:		return "Time";
		case Type::DateTimeType:	return "DateTime";

		case Type::DataObjectType:	return "Complex";

		default:

			StringStream ssInfo;
			ssInfo<<"unknown or unsupported dm::Type::Types["<<pType->getName();
			ssInfo<<":"<<pType->getTypeEnum()<<":";
			IAS_THROW(InternalException(ssInfo.str()));
	}

}
/*************************************************************************/
unsigned int CppCodeGeneratorFriend::getStartingProperty(const DM::Type* pType) const{
	IAS_TRACER;

	if(pType->isRootType())
		return 0;

	return pType->getBaseType()->asComplexType()->getProperties().getSize();
}
/*************************************************************************/
}
}
}
}
