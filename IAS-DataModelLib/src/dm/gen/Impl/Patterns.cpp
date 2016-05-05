/*
 * File: IAS-DataModelLib/src/dm/gen/Impl/Patterns.cpp
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
#include "../../../dm/gen/Impl/Patterns.h"
#include <commonlib/commonlib.h>


namespace IAS {
namespace DM {
namespace Gen {
namespace Impl {

/*************************************************************************/
Patterns::Patterns(){
	IAS_TRACER;

/*************************************************************************/

	ptrFilePreamble=IAS_DFT_FACTORY<Template>::Create(
"/*\n"
" * Generated file.\n"
" * \n"
" */\n"
);

	ptrUsingNamespaceIAS =IAS_DFT_FACTORY<Template>::Create( "using namespace IAS;\n");
/*************************************************************************/
    ptrHeader_ifndef =IAS_DFT_FACTORY<Template>::Create( "#ifndef IAS_DM_AG_Impl_${file}\n#define IAS_DM_AG_Impl_${file}\n");
    ptrHeader_endif  =IAS_DFT_FACTORY<Template>::Create( "#endif\n");
    ptrHeader_include_local =IAS_DFT_FACTORY<Template>::Create( "#include \"${file}\" \n");
    ptrHeader_include_local_h =IAS_DFT_FACTORY<Template>::Create( "#include \"${file}.h\" \n");
    ptrHeader_include_global =IAS_DFT_FACTORY<Template>::Create( "#include <${file}> \n");
    ptrHeader_include_commonlib =IAS_DFT_FACTORY<Template>::Create("#include <commonlib/commonlib.h> \n");
    ptrHeader_include_dm =IAS_DFT_FACTORY<Template>::Create( "#include \"dm/datamodel.h\" \n");
    ptrHeader_include_dmgen = IAS_DFT_FACTORY<Template>::Create(
    		"#include \"dm/gen/DataObjectList.h\" \n"
    		"#include \"dm/Impl/MemoryManager.h\" \n"
    	);
    ptrHeader_include_globalImplDataFactory = IAS_DFT_FACTORY<Template>::Create(
    		"#include <dm/gen/DataFactory.h> \n"
    		"#include \"Impl/DataFactory.h\" \n"
    );

    ptrHeader_include_impl =IAS_DFT_FACTORY<Template>::Create( "#include <Impl/${path}/${filebase}.h>\n");
    ptrHeader_include_implBulitIn =IAS_DFT_FACTORY<Template>::Create( "#include <dm/Impl/default/${filebase}.h> \n");

    ptrHeader_include_defaultTypes = IAS_DFT_FACTORY<Template>::Create(
    	"#include \"dm/default/String.h\" \n"
    	"#include \"dm/default/Integer.h\" \n"
    	"#include \"dm/default/Float.h\" \n"
    	"#include \"dm/default/Boolean.h\" \n"
		"#include \"dm/default/Date.h\" \n"
    	"#include \"dm/default/Time.h\" \n"
    	"#include \"dm/default/DateTime.h\" \n"
    );

    ptrHeader_include_defaultTypesImpl = IAS_DFT_FACTORY<Template>::Create(
    	"#include \"dm/Impl/default/String.h\" \n"
    	"#include \"dm/Impl/default/Integer.h\" \n"
    	"#include \"dm/Impl/default/Float.h\" \n"
    	"#include \"dm/Impl/default/Boolean.h\" \n"
    	"#include \"dm/Impl/default/Time.h\" \n"
    	"#include \"dm/Impl/default/Date.h\" \n"
    	"#include \"dm/Impl/default/DateTime.h\" \n"
		"#include \"dm/Impl/exception/IllegalCastException.h\"\n"
    );

/*************************************************************************/
    ptrNamespace_start =IAS_DFT_FACTORY<Template>::Create( "namespace ${ns} {\n");
    ptrNamespace_end =IAS_DFT_FACTORY<Template>::Create( "} /* ${ns} */\n");
    ptrNamespace_prefix =IAS_DFT_FACTORY<Template>::Create( "::${ns}");
/*************************************************************************/
    ptrGlobals_header_incImpl =IAS_DFT_FACTORY<Template>::Create(
    		"#include \"dm/Impl/DataFactory.h\" \n"
    		"#include \"dm/Impl/MemoryManager.h\" \n"
    		);
/*************************************************************************/
/*               G L O B A L     D A T A   F A C T O R Y                 */
/*************************************************************************/
    ptrGlobals_header =IAS_DFT_FACTORY<Template>::Create(
    "\n"
    "class GlobalDataFactory;\n"
    "\n"
    "	class DataFactoryBase  {\n"
    "		public:\n"
    "\n"
    "			static const std::string& URICommonJDM;\n"
    "\n"
    "			virtual DM::DataObject* create(const ::IAS::String& strURI, const ::IAS::String& strType)=0;\n"
    "\n"
    "		protected:\n"
    "\n"
    "			void init(const std::string& strNS);\n"
    "			GlobalDataFactory* pGlobalDataFactory;\n"
    "	};\n"
    "\n"
    "\n"
    "	class GlobalDataFactory : "
    "   public IAS::InstanceFeatureWithFactory< IAS::DM::Impl::ModelAllocator<GlobalDataFactory>, GlobalDataFactory >,\n"
    "	public ::IAS::DM::Impl::DataFactory{\n"
    "		public:\n"
    "\n"
    "			void addGeneratedFactory(const ::IAS::String& strURI, DataFactoryBase* pDataFactoryBase);\n"
    "			virtual DM::DataObject* create(const ::IAS::String& strURI, const ::IAS::String& strType);\n"
    "\n"
    "           void defineAll();\n"
    "\n"
    "		protected:\n"
    "			std::map< ::IAS::String, DataFactoryBase*> hmGeneratedFactories;\n"
    "	};\n"
    "\n"
    );
/*************************************************************************/
    ptrGlobalImplDataFactory_header = IAS_DFT_FACTORY<Template>::Create(
"class DataFactoryInitalizer_${uniq} :\n"
"   public IAS::InstanceFeatureWithFactory< IAS::DM::Impl::ModelAllocator<DataFactoryInitalizer_${uniq}>, DataFactoryInitalizer_${uniq} >{\n"
"public:\n"
"\n"
"	virtual ~DataFactoryInitalizer_${uniq}() throw();\n"
"\n"
"protected:\n"
"	DataFactoryInitalizer_${uniq}();\n"
"   friend class IAS::Factory< DataFactoryInitalizer_${uniq} >;\n"
"\n"
"};\n"
"\n"
);

/*************************************************************************/
    ptrGlobalImplDataFactory_implPart01 = IAS_DFT_FACTORY<Template>::Create(
"static void initialize_${uniq}(::IAS::DM::Gen::DataFactory* pDataFactory){\n"
"	IAS_TRACER;\n"
"\n"
);

/*************************************************************************/
    ptrGlobalImplDataFactory_implPart02 = IAS_DFT_FACTORY<Template>::Create(
"\n"
"}\n"
"\n"
"DataFactoryInitalizer_${uniq}::DataFactoryInitalizer_${uniq}(){\n"
"	IAS_TRACER;\n"
"   IAS::DM::Gen::DataFactory::GetInstance()->initializeWith(&initialize_${uniq});\n"
"}\n"
"\n"
"DataFactoryInitalizer_${uniq}::~DataFactoryInitalizer_${uniq}() throw(){\n"
"	IAS_TRACER;\n"
"}\n\n"
"extern \"C\" { void ias_dm_init(){ DataFactoryInitalizer_${uniq}::GetInstance(); } }\n"
);
/*************************************************************************/
    ptrGlobalImplDataFactory_implDeclare = IAS_DFT_FACTORY<Template>::Create(
"\n"
"	pDataFactory->declareBuiltInTypeTmpOveride(\n"
"       IAS::InstanceFeatureWithFactory< IAS::DM::Impl::ModelAllocator< ${typens}::Ext::${type}Type >, ${typens}::Ext::${type}Type >\n"
" 				::GetInstance());\n"
);
/*************************************************************************/
    ptrGlobalImplDataFactory_implDefine = IAS_DFT_FACTORY<Template>::Create(
"\n"
"       IAS::InstanceFeatureWithFactory< IAS::DM::Impl::ModelAllocator< ${typens}::Ext::${type}Type >, ${typens}::Ext::${type}Type >\n"
" 				::GetInstance()->defineProperties(pDataFactory);\n"
"\n"
);

    /*************************************************************************/
    /*                 D E C L A R A T O N S                                 */
    /*************************************************************************/

    ptrDeclaration_typeDeclarations = IAS_DFT_FACTORY<Template>::Create(
"	class ${type};\n"
"namespace Ext{\n"
"	class ${type}List;\n"
"	class ${type}Type;\n"
"}\n"
);

    /*************************************************************************/
    /*            I N T E R F A C E  D A T A   F A C T O R Y                 */
    /*************************************************************************/

    ptrInterfaceDataFactory_headerPart01 = IAS_DFT_FACTORY<Template>::Create(
"/*************************************************************************/\n"
"class DataFactory :\n"
"   public IAS::InstanceFeatureWithFactory< IAS::DM::Impl::ModelAllocator<DataFactory>, DataFactory >{\n"
"	public:\n"
"\n"
);
/*************************************************************************/
    ptrInterfaceDataFactory_headerTypeMethods = IAS_DFT_FACTORY<Template>::Create(
"	Ext::${type}Type* get${type}Type()const;\n"
"	${type}*     create${type}()const;\n"
"	${type}*     create${type}(${setType} aValue)const;\n"
"\n"
);
/*************************************************************************/
    ptrInterfaceDataFactory_headerPart02 = IAS_DFT_FACTORY<Template>::Create(
"\n"
"	virtual ~DataFactory() throw();\n"
"\n"
"	::IAS::DM::DataFactory *getContaingDataFactory();\n"
"\n"
"protected:\n"
"	DataFactory();\n"
"   friend class IAS::Factory< DataFactory >;\n"
"\n"
"};\n"
"\n"
"\n"
);
/*************************************************************************/
    ptrInterfaceDataFactory_sourceTypeMethods = IAS_DFT_FACTORY<Template>::Create(
"Ext::${type}Type* DataFactory::get${type}Type()const{\n"
"	return \n"
"		IAS::InstanceFeatureWithFactory< \n"
"         IAS::DM::Impl::ModelAllocator< ::${stdns}::${typens}::Ext::${type}Type >, \n"
"                     ::${stdns}::${typens}::Ext::${type}Type >::GetInstance();\n"
"}\n"

"${type}* DataFactory::create${type}()const{\n"
"	return \n"
"		IAS::InstanceFeatureWithFactory< \n"
"                   IAS::DM::Impl::ModelAllocator< ::${stdns}::${typens}::Ext::${type}Type >, \n"
"                     ::${stdns}::${typens}::Ext::${type}Type >::GetInstance()->create${type}();\n"
"}\n"

"${type}* DataFactory::create${type}(${setType} aValue)const{\n"
"	return \n"
"		IAS::InstanceFeatureWithFactory< \n"
"                   IAS::DM::Impl::ModelAllocator< ::${stdns}::${typens}::Ext::${type}Type >, \n"
"                     ::${stdns}::${typens}::Ext::${type}Type >::GetInstance()->create${type}(aValue);\n"
"}\n"
);
/*************************************************************************/
	ptrInterfaceDataFactory_sourcePart01 = IAS_DFT_FACTORY<Template>::Create(
"::IAS::DM::DataFactory *DataFactory::getContaingDataFactory(){\n"
"	return ::IAS::DM::Gen::DataFactory::GetInstance();\n"
"}\n"
"DataFactory::DataFactory(){"
"::IAS::DM::AG::Impl::DataFactoryInitalizer_${uniq}::GetInstance();}\n"
"DataFactory::~DataFactory()throw(){}\n"
"\n"
);

    /*************************************************************************/
    /*           I N T E R F A C E     T Y P E                               */
    /*************************************************************************/

	ptrInterfaceType_headerPart01 = IAS_DFT_FACTORY<Template>::Create(
"class ${type} : public virtual ::IAS::DM::DataObject {\n"
"public:\n"
"\n"
);
/*************************************************************************/
	ptrInterfaceType_headerPart01withBase = IAS_DFT_FACTORY<Template>::Create(
"class ${type}: public virtual ::${basens}::${base} {\n"
"public:\n"
"\n"
);

/*************************************************************************/
	ptrInterfaceType_headerPart02a = IAS_DFT_FACTORY<Template>::Create(
"\n"
"   virtual ${type}* duplicate${type}() const = 0;"
"};\n"
"namespace Ext{\n"
"typedef ::IAS::DM::Impl::DataAllocator< ::${typens}::${type} >::RefCountingPtr ${type}Ptr;\n"
"class ${type}List {\n"
"	public:\n"
);
ptrInterfaceType_headerPart02DataObject = IAS_DFT_FACTORY<Template>::Create(
"	virtual void add(::${typens}::${type}* pValue) = 0;\n"
"	virtual int size() const = 0;\n"
"	virtual ::${typens}::${type}* at(int iIdx) = 0;\n"
"	virtual const ::${typens}::${type}* at(int iIdx) const = 0;\n"
);
ptrInterfaceType_headerPart02SimpleType = IAS_DFT_FACTORY<Template>::Create(
"	virtual void add(${setType} pValue) = 0;\n"
"	virtual ${retType} at(int iIdx) = 0;\n"
"	virtual const ${retType} at(int iIdx) const = 0;\n"
"	virtual int size() const = 0;\n"
"	virtual void addDataObject(::${typens}::${type}* pValue) = 0;\n"
"	virtual ::${typens}::${type}* getDataObject(int iIdx) = 0;\n"
);
ptrInterfaceType_headerPart02Type = IAS_DFT_FACTORY<Template>::Create(
"};\n"
"/*************************************************************************/\n"
"class ${type}Type : public virtual ::IAS::DM::Type {\n"
"	public:\n"
"\n"
);
/*************************************************************************/
ptrInterfaceType_headerPart02TypeWithBase = IAS_DFT_FACTORY<Template>::Create(
"};\n"
"/*************************************************************************/\n"
"class ${type}Type : public virtual ::${basens}::Ext::${base}Type {\n"
"	public:\n"
"\n"
);
/*************************************************************************/

	ptrInterfaceType_headerPart03 = IAS_DFT_FACTORY<Template>::Create(
"};\n"
"};\n"
"\n"
);
/*************************************************************************/
	ptrInterfaceType_headerChecker = IAS_DFT_FACTORY<Template>::Create(
	"	virtual bool ${checker}()const =0;\n"
);
/*************************************************************************/
	ptrInterfaceType_headerGetter = IAS_DFT_FACTORY<Template>::Create(
	"	virtual ${retType} ${getter}() =0;\n"
	"	virtual const ${retType} ${getter}()const =0;\n"
);
/*************************************************************************/
	ptrInterfaceType_headerGetterMany = IAS_DFT_FACTORY<Template>::Create(
	"	virtual ${retList}List& ${getter}List() =0;\n"
	"	virtual const ${retList}List& ${getter}List() const =0;\n"
);
/*************************************************************************/
	ptrInterfaceType_headerSetter = IAS_DFT_FACTORY<Template>::Create(
	"	virtual void ${setter}(${setType} aValue)=0;\n"
);
/*************************************************************************/
	ptrInterfaceType_headerCreator = IAS_DFT_FACTORY<Template>::Create(
	"	virtual ${retType} ${creator}()=0;\n"
);
/*************************************************************************/
	ptrInterfaceType_headerUnsetter= IAS_DFT_FACTORY<Template>::Create(
	"	virtual void un${setter}()=0;\n"
);

/*************************************************************************/
ptrInterfaceType_headerCreateType = IAS_DFT_FACTORY<Template>::Create(
"	virtual ::${typens}::${type}* create${type}() const=0;\n"
"	virtual ::${typens}::${type}* create${type}(${setType} aValue) const=0;\n"
"	virtual ::${typens}::${type}* cast(::IAS::DM::DataObject* pDataObject) const=0;\n"
"	virtual const ::${typens}::${type}* cast(const ::IAS::DM::DataObject* pDataObject) const=0;\n"

);
/*************************************************************************/
	ptrInterfaceType_headerGetProperty = IAS_DFT_FACTORY<Template>::Create(
	"	virtual const ::IAS::DM::Property* get${property}Property() const=0;\n"
	);


    /*************************************************************************/
    /*           I M P L E M E N T A T I O N     T Y P E                     */
    /*************************************************************************/

	ptrImplType_includeSuperclasses = IAS_DFT_FACTORY<Template>::Create(
"#include <dm/Impl/DataObject${class}.h>\n"
"#include <dm/Impl/Type${class}.h>\n"
"#include <dm/Impl/MemoryManager.h>\n"
"\n"
);
/*************************************************************************/
	ptrImplType_headerPart01 = IAS_DFT_FACTORY<Template>::Create(
"class ${type}Type;\n"
"\n"
"class ${type}:\n"
);
/*************************************************************************/
	ptrImplType_headerPart02 = IAS_DFT_FACTORY<Template>::Create(
"	public ::IAS::DM::Impl::DataObjectComplex,\n"
);
/*************************************************************************/
	ptrImplType_headerPart02withBase = IAS_DFT_FACTORY<Template>::Create(
"	public ::${stdns}::${basens}::${base},\n"
);
/*************************************************************************/
	ptrImplType_headerPart02withBaseBuiltIn = IAS_DFT_FACTORY<Template>::Create(
"	public ::IAS::DM::Impl::Default::${base},\n"
);
/*************************************************************************/
	ptrImplType_headerPart03 = IAS_DFT_FACTORY<Template>::Create(
"	public virtual ::${typens}::${type}{\n"
"\n"
"public:\n"
"\n"
"	virtual ~${type}() throw();\n"
"\n"
"   virtual ::${typens}::${type}* duplicate${type}() const;"
"\n"
);
/*************************************************************************/
	ptrImplType_headerPtrList = IAS_DFT_FACTORY<Template>::Create(
	"::IAS::DM::Impl::DataAllocator< ${retList}List >::PtrHolder ptr${property}List;\n"
);
/*************************************************************************/
	ptrImplType_headerPart04a = IAS_DFT_FACTORY<Template>::Create(
"\n"
"protected:\n"
"	${type}(const ::IAS::DM::Impl::Type* pType);\n"
"	friend class ::IAS::Factory<${type}>;\n"
"};\n"
"\n"
"namespace Ext{\n"
"\n"
"typedef ::IAS::DM::Impl::DataAllocator< ${type} >::RefCountingPtr ${type}Ptr;\n"
"\n"
"class ${type}List :"
" public ::${typens}::Ext::${type}List, \n"
" public ::IAS::DM::Gen::DataObjectListProxy {\n"
"	public:\n"
"   ${type}List(::IAS::DM::DataObjectList& refList) throw();\n"
"   virtual ~${type}List();\n"
);
/*************************************************************************/
	ptrImplType_headerPart04DataObject = IAS_DFT_FACTORY<Template>::Create(
"	virtual void add(::${typens}::${type}* pValue);\n"
"	virtual int size() const ;\n"
"	virtual ::${typens}::${type}* at(int iIdx);\n"
"	virtual const ::${typens}::${type}* at(int iIdx)const;\n"
);
/*************************************************************************/
	ptrImplType_headerPart04SimpleType = IAS_DFT_FACTORY<Template>::Create(
"	virtual void add(${setType} pValue);\n"
"	virtual int size() const ;\n"
"	virtual ${retType} at(int iIdx);\n"
"	virtual const ${retType} at(int iIdx) const;\n"
"	virtual void addDataObject(::${typens}::${type}* pValue);\n"
"	virtual ::${typens}::${type}* getDataObject(int iIdx);\n"
);
/*************************************************************************/
	ptrImplType_headerPart04Type = IAS_DFT_FACTORY<Template>::Create(
"};\n"
"\n"
"class ${type}Type :\n"
"	public ::IAS::DM::Impl::Type${typeclass},\n"
"	public virtual ::${typens}::Ext::${type}Type,\n"
);
/*************************************************************************/
	ptrImplType_headerPart04TypeWithBase = IAS_DFT_FACTORY<Template>::Create(
"};\n"
"\n"
"class ${type}Type :\n"
"	public ::${stdns}::${basens}::Ext::${base}Type,\n"
"	public virtual ::${typens}::Ext::${type}Type,\n"
);
/*************************************************************************/
ptrImplType_headerPart04TypeWithBaseBuildIn = IAS_DFT_FACTORY<Template>::Create(
"};\n"
"\n"
"class ${type}Type :\n"
"	public ::IAS::DM::Impl::Default::Ext::${base}Type,\n"
"	public virtual ::${typens}::Ext::${type}Type,\n"
);
/*************************************************************************/
	ptrImplType_headerPart04TypeBody = IAS_DFT_FACTORY<Template>::Create(
"	public	IAS::InstanceFeatureWithFactory<  IAS::DM::Impl::ModelAllocator< ${type}Type >, ${type}Type > {\n"
"public:\n"
"\n"
"	virtual ~${type}Type() throw();\n"
"\n"
"	virtual ::${typens}::${type}* create${type}() const;\n"
"	virtual ::${typens}::${type}* create${type}(${setType}) const;\n"
"\n"
"	virtual ::${typens}::${type}* cast(::IAS::DM::DataObject* pDataObject) const;\n"
"	virtual const ::${typens}::${type}* cast(const ::IAS::DM::DataObject* pDataObject) const;\n"
"\n"
"	static ::${typens}::${type}* FromDataObject(::IAS::DM::DataObject* pDataObject);\n"
"	static const ::${typens}::${type}* FromDataObject(const ::IAS::DM::DataObject* pDataObject);\n"
"\n"
);
/*************************************************************************/
	ptrImplType_headerPart05 = IAS_DFT_FACTORY<Template>::Create(
"\n"
"\n"
" void defineProperties(::IAS::DM::DataFactory* pDataFactory);\n"
"protected:\n"
"	${type}Type();\n"
"	${type}Type(const ::IAS::String& strURI,const ::IAS::String& strName,const ::IAS::DM::Type *pBaseType);\n"
"\n"
"	virtual ::IAS::DM::Impl::DataObject* createDataObjectImpl() const;\n"
"\n"
"\n"
"	${typens}::${type}* create${type}Impl() const;\n"
"\n"
);
/*************************************************************************/
	ptrImplType_headerPart06 = IAS_DFT_FACTORY<Template>::Create(
"   friend class IAS::Factory< ${type}Type >; \n"
"};\n"
"};\n"
"\n"
);
/*************************************************************************/
	ptrImplType_headerChecker = IAS_DFT_FACTORY<Template>::Create(
	"	virtual bool ${checker}() const ;\n"
);
/*************************************************************************/
	ptrImplType_headerGetter = IAS_DFT_FACTORY<Template>::Create(
	"	virtual ${retType} ${getter}() ;\n"
	"	virtual const ${retType} ${getter}() const ;\n"
);
/*************************************************************************/
	ptrImplType_headerGetterMany = IAS_DFT_FACTORY<Template>::Create(
	"	virtual ${retList}List& ${getter}List() ;\n"
	"	virtual const ${retList}List& ${getter}List() const ;\n"
);
/*************************************************************************/
	ptrImplType_headerSetter = IAS_DFT_FACTORY<Template>::Create(
	"	virtual void ${setter}(${setType} aValue);\n"
);
/*************************************************************************/
	ptrImplType_headerCreator = IAS_DFT_FACTORY<Template>::Create(
	"	virtual ${retType} ${creator}();\n"
);
/*************************************************************************/
	ptrImplType_headerUnsetter = IAS_DFT_FACTORY<Template>::Create(
	"	virtual void un${setter}();\n"
);

/*************************************************************************/
ptrImplType_headerGetProperty = IAS_DFT_FACTORY<Template>::Create(
"	virtual const ::IAS::DM::Property* get${property}Property() const;\n"
);
/*************************************************************************/
ptrImplType_headerPropertyMember = IAS_DFT_FACTORY<Template>::Create(
"	const ::IAS::DM::Property* p${property}Property;\n"
);

    /*************************************************************************/
    /*      I M P L E M E N T A T I O N   T Y P E      S O U R C E           */
    /*************************************************************************/


ptrImplType_sourceChecker = IAS_DFT_FACTORY<Template>::Create(
"bool ${type}::${checker}() const {\n"
"	return isSet(dynamic_cast<const Ext::${type}Type*>(pType)->get${property}Property());\n"
"}\n"
);

ptrImplType_sourceGetter = IAS_DFT_FACTORY<Template>::Create(
"${retType} ${type}::${getter}() {\n"
"	return ${cast}get${dmMethod}( dynamic_cast<const Ext::${type}Type*>(pType)->get${property}Property());\n"
"}\n"
"const ${retType} ${type}::${getter}() const {\n"
"	return ${cast}get${dmMethod}(dynamic_cast<const Ext::${type}Type*>(pType)->get${property}Property());\n"
"}\n"

	);
/*************************************************************************/
	ptrImplType_sourceGetterMany = IAS_DFT_FACTORY<Template>::Create(
"${retType}List& ${type}::${getter}List() {\n"
"	return *ptr${property}List;\n"
"}\n"
"const ${retType}List& ${type}::${getter}List() const {\n"
"return const_cast<${type}*>(this)->${getter}List();"
"}\n"
	);
/*************************************************************************/
	ptrImplType_sourceGetterDM = IAS_DFT_FACTORY<Template>::Create(
"${retType} ${type}::${getter}() {\n"
"return ${propertyNS}::Ext::${propertyType}Type::FromDataObject((DM::DataObject*)"
"get${dmMethod}(dynamic_cast<const Ext::${type}Type*>(pType)->get${property}Property()));\n"
"}\n"
"const ${retType} ${type}::${getter}() const {\n"
"return ${propertyNS}::Ext::${propertyType}Type::FromDataObject((DM::DataObject*)"
"get${dmMethod}(dynamic_cast<const Ext::${type}Type*>(pType)->get${property}Property()));\n"
"}\n"

);
/*************************************************************************/
ptrImplType_sourceSetter = IAS_DFT_FACTORY<Template>::Create(
"void ${type}::${setter}(${setType} aValue){\n"
"	set${dmMethod}(dynamic_cast<const Ext::${type}Type*>(pType)->get${property}Property(),aValue);\n"
"}\n"
);
/*************************************************************************/
ptrImplType_sourceCreator = IAS_DFT_FACTORY<Template>::Create(
"${retType} ${type}::${creator}(){\n"
"return ${propertyNS}::Ext::${propertyType}Type::FromDataObject("
"	createDataObject(dynamic_cast<const Ext::${type}Type*>(pType)->get${property}Property()));\n"
"}\n"

);
/*************************************************************************/
ptrImplType_sourceUnsetter = IAS_DFT_FACTORY<Template>::Create(
"void ${type}::un${setter}(){\n"
"	unset(dynamic_cast<const Ext::${type}Type*>(pType)->get${property}Property());\n"
"}\n"
);
/*************************************************************************/
	ptrImplType_sourcePart01 = IAS_DFT_FACTORY<Template>::Create(
"::${typens}::${type}* ${type}::duplicate${type}() const{\n"
"   return Ext::${type}Type::FromDataObject(duplicate());\n"
"}\n"
"${type}::~${type}() throw(){}\n"
"${type}::${type}(const ::IAS::DM::Impl::Type* pType):\n"
);
/*************************************************************************/
ptrImplType_sourcePart02 = IAS_DFT_FACTORY<Template>::Create(
"	::IAS::DM::Impl::DataObject${class}(pType){\n"
);
/*************************************************************************/
ptrImplType_sourcePart02withBase = IAS_DFT_FACTORY<Template>::Create(
"	Impl::${basens}::${base}(pType){\n"
);
/*************************************************************************/
ptrImplType_sourcePart02withBaseBulitIn = IAS_DFT_FACTORY<Template>::Create(
"	::IAS::DM::Impl::Default::${base}(pType){\n"
);
/*************************************************************************/
ptrImplType_sourceConstructorManyInit = IAS_DFT_FACTORY<Template>::Create(
"    ptr${property}List=::IAS::DM::Impl::DataAllocator< ${propertyNS}::Ext::${propertyType}List >::Create< ::IAS::DM::DataObjectList& >(\n"
"     this->DataObject::getList(\n"
"		IAS::InstanceFeatureWithFactory< \n"
"         IAS::DM::Impl::ModelAllocator< ::${stdns}::${typens}::Ext::${type}Type >, \n"
"         ::${stdns}::${typens}::Ext::${type}Type >::GetInstance()->get${property}Property()) \n"
"      );\n"
);
/*************************************************************************/
	ptrImplType_sourcePart03a = IAS_DFT_FACTORY<Template>::Create(
"\n}\n"
"namespace Ext{\n"
"${type}List::${type}List(::IAS::DM::DataObjectList& refList) throw():\n"
"	::IAS::DM::Gen::DataObjectListProxy(refList){};\n"
"${type}List::~${type}List(){}\n"
);
/*************************************************************************/
	ptrImplType_sourcePart03DataObject = IAS_DFT_FACTORY<Template>::Create(
"void ${type}List::add(::${typens}::${type}* pValue){\n"
"	refDataObjectList.add(pValue);\n"
"}\n"
"int ${type}List::size()const{\n"
"	return refDataObjectList.size();\n"
"}\n"
"::${typens}::${type}* ${type}List::at(int iIdx){\n"
"	return Ext::${type}Type::FromDataObject(refDataObjectList.at(iIdx));\n"
"}\n"
"const ::${typens}::${type}* ${type}List::at(int iIdx)const{\n"
"	return Ext::${type}Type::FromDataObject(refDataObjectList.at(iIdx));\n"
"}\n"

);
/*************************************************************************/
	ptrImplType_sourcePart03SimpleType = IAS_DFT_FACTORY<Template>::Create(
"void ${type}List::add(${setType} aValue){\n"
"	refDataObjectList.add(\n"
"		IAS::InstanceFeatureWithFactory< \n"
"                   IAS::DM::Impl::ModelAllocator< ::${stdns}::${typens}::Ext::${type}Type >, \n"
"                     ::${stdns}::${typens}::Ext::${type}Type >::GetInstance()->create${type}(aValue));\n"
"}\n"
"${retType} ${type}List::at(int iIdx){\n"
"	return refDataObjectList.at(iIdx)->to${class}();\n"
"}\n"
"const ${retType} ${type}List::at(int iIdx)const{\n"
"	return refDataObjectList.at(iIdx)->to${class}();\n"
"}\n"
"int ${type}List::size()const{\n"
"	return refDataObjectList.size();\n"
"}\n"
"void ${type}List::addDataObject(::${typens}::${type}* pValue){\n"
"	refDataObjectList.add(pValue);\n"
"}\n"
"::${typens}::${type}* ${type}List::getDataObject(int iIdx){\n"
"	return Ext::${type}Type::FromDataObject(refDataObjectList.at(iIdx));\n"
"}\n"
);
	ptrImplType_sourcePart03b = IAS_DFT_FACTORY<Template>::Create(
"${type}Type::~${type}Type() throw(){\n"
"}\n"
"\n"
);
/*************************************************************************/
	ptrImplType_sourceDefineType = IAS_DFT_FACTORY<Template>::Create(
"${type}Type::${type}Type() : \n"
"	::IAS::DM::Impl::Type${typeclass}(\"${uri}\",\"${type}\",NULL){};\n"
"\n"
"${type}Type::${type}Type(const ::IAS::String& strURI, const ::IAS::String& strName, const ::IAS::DM::Type    *pBaseType) : \n"
"	::IAS::DM::Impl::Type${typeclass}(strURI,strName,pBaseType ? pBaseType : (::IAS::DM::Type*) "
"		IAS::InstanceFeatureWithFactory< \n"
"                   IAS::DM::Impl::ModelAllocator< ::${stdns}::${typens}::Ext::${type}Type >, \n"
"                     ::${stdns}::${typens}::Ext::${type}Type >::GetInstance()){};\n"
"\n"
);
/*************************************************************************/
	ptrImplType_sourceDefineTypeWithBase = IAS_DFT_FACTORY<Template>::Create(
"${type}Type::${type}Type() : \n"
"	::${stdns}::${basens}::Ext::${base}Type(\"${uri}\",\"${type}\",NULL){};\n"
"\n"
"${type}Type::${type}Type(const ::IAS::String& strURI, const ::IAS::String& strName, const ::IAS::DM::Type    *pBaseType) : \n"
"	::${stdns}::${basens}::Ext::${base}Type(strURI,strName,pBaseType ? pBaseType : (::IAS::DM::Type*)"
"		IAS::InstanceFeatureWithFactory< \n"
"                   IAS::DM::Impl::ModelAllocator< ::${stdns}::${typens}::Ext::${type}Type >, \n"
"                     ::${stdns}::${typens}::Ext::${type}Type >::GetInstance()){};\n"
"\n"
);
/*************************************************************************/
	ptrImplType_sourceDefineTypeWithBuildIn = IAS_DFT_FACTORY<Template>::Create(
"${type}Type::${type}Type() : \n"
"		::IAS::DM::Impl::Default::Ext::${base}Type(\"${uri}\",\"${type}\",NULL){};\n"
"\n"
"${type}Type::${type}Type(const ::IAS::String& strURI, const ::IAS::String& strName, const ::IAS::DM::Type    *pBaseType) : \n"
"		::IAS::DM::Impl::Default::Ext::${base}Type(strURI,strName,pBaseType ? pBaseType :  (::IAS::DM::Type*)"
"		IAS::InstanceFeatureWithFactory< \n"
"                   IAS::DM::Impl::ModelAllocator< ::${stdns}::${typens}::Ext::${type}Type >, \n"
"                     ::${stdns}::${typens}::Ext::${type}Type >::GetInstance()){};\n"
);
/*************************************************************************/
	ptrImplType_sourcePart04 = IAS_DFT_FACTORY<Template>::Create(
"void ${type}Type::defineProperties(::IAS::DM::DataFactory* pDataFactory){\n"
"\n"
);
	/*************************************************************************/
ptrImplType_sourceDefineProperty = IAS_DFT_FACTORY<Template>::Create(
"	{\n"
"		const ::IAS::DM::Type* pPropType=pDataFactory->getType(\"${propertyuri}\",\"${propertytype}\");\n"
"		p${propertySymbol}Property = defineProperty(\"${property}\",pPropType,${multi},${xmlattr});\n"
"	}\n"
);
/*************************************************************************/
ptrImplType_sourceInheritProperty = IAS_DFT_FACTORY<Template>::Create(
"	{\n"
"		p${propertySymbol}Property = asComplexType()->getProperties().getProperty(\"${property}\");\n"
"	}\n"
);
/*************************************************************************/
	ptrImplType_sourcePart05 = IAS_DFT_FACTORY<Template>::Create(
"}\n"
"\n"
"::IAS::DM::Impl::DataObject* ${type}Type::createDataObjectImpl() const{\n"
"	return create${type}Impl();\n"
"}\n"
"\n"
"${typens}::${type}* ${type}Type::create${type}Impl() const{\n"
"	IAS_TRACER;\n"
"   return ::IAS::DM::Impl::DataAllocator< ${typens}::${type}>::Create(this);\n"
"}\n"
"\n"
"::${typens}::${type}* ${type}Type::create${type}() const{\n"
"	IAS_TRACER;\n"
"	return create${type}Impl();\n"
"}\n"
"\n"
"::${typens}::${type}* ${type}Type::create${type}(${setType} aValue) const{\n"
"	IAS_TRACER;\n"
"	::IAS::DM::Impl::DataAllocator< ${typens}::${type}>::PtrHolder ptrTmp(create${type}Impl());\n"
"	ptrTmp->set${setter}(aValue);\n"
"	return ptrTmp.pass();\n"
"}\n"
"::${typens}::${type}* ${type}Type::FromDataObject(::IAS::DM::DataObject* pDataObject){\n"
"	return dynamic_cast< ${typens}::${type}* >(pDataObject);\n"
"}\n"
"const ::${typens}::${type}* ${type}Type::FromDataObject(const ::IAS::DM::DataObject* pDataObject){\n"
"	return dynamic_cast< const ${typens}::${type}* >(pDataObject);\n"
"}\n"
"\n"
"::${typens}::${type}* ${type}Type::cast(::IAS::DM::DataObject* pDataObject) const{\n"
"	return const_cast< ::${typens}::${type}*>(cast(static_cast<const ::IAS::DM::DataObject*>(pDataObject)));\n"
"}\n"
"\n"
"const ::${typens}::${type}* ${type}Type::cast(const ::IAS::DM::DataObject* pDataObject) const{\n"
"	IAS_TRACER; \n"
"	IAS_CHECK_IF_NULL(pDataObject);\n"
"	if(pDataObject->getType()->isAssignableTo(this)){\n"
"		return FromDataObject(pDataObject);\n"
"	}\n"
"	IAS_THROW(::IAS::DM::Impl::IllegalCastException(pDataObject->getType(), this));\n"
"}\n"
"\n"
);
/*************************************************************************/
	ptrImplType_sourceGetProperty = IAS_DFT_FACTORY<Template>::Create(
"const ::IAS::DM::Property* ${type}Type::get${property}Property() const {\n"
"	return p${property}Property;\n"
"};\n"
"\n"
);
/*************************************************************************/
	ptrImplType_sourcePart06 = IAS_DFT_FACTORY<Template>::Create(
"}\n"
);

}

/*************************************************************************/
void Patterns::addInclude(OutputFile* pOutputFile, const String& strFileToInclude) const{

	IAS_TRACER;

	Template::Arguments mapArgsInclude;
	mapArgsInclude.add("file",strFileToInclude);
	ptrHeader_include_local->evaluate(mapArgsInclude, pOutputFile->getStreamRef());

}
/*************************************************************************/
void Patterns::addGlobalInclude(OutputFile* pOutputFile, const String& strFileToInclude) const{

	IAS_TRACER;

	Template::Arguments mapArgsInclude;
	mapArgsInclude.add("file",strFileToInclude);
	ptrHeader_include_global->evaluate(mapArgsInclude, pOutputFile->getStreamRef());

}
/*************************************************************************/
}
}
}
}
