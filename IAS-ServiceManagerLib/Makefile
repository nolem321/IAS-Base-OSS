#########################################################################
ARTIFACT=IASServiceManagerLib
#########################################################################
DEP_PROJECTS+=IAS-CommonLib
DEP_PROJECTS+=IAS-DataModelLib
#########################################################################
include Makefile.FILES
#########################################################################
include ../IAS-BuilderTools/Makefile
#########################################################################
-include $(CPPDEPS)
#########################################################################
-include Makefile.$(IAS_PLATFORM)
ifdef LD_LIBRARY_PATH
LD_LIBRARY_PATH:=../IAS-CommonLib/out/lib:$(LD_LIBRARY_PATH)
else
LD_LIBRARY_PATH:=../IAS-CommonLib/out/lib
endif
LD_LIBRARY_PATH:=../IAS-DataModelLib/out/lib:$(LD_LIBRARY_PATH):/usr/local/lib:
IAS_DBG_GLOBAL=+errors,-info
IAS_DBG_DM=+errors,-info

all : makedirs $(TARGET) 

dm : xsd/smcfg.xsd xsd/smapi.xsd
	@rm -rf src/Impl src/org src/Impl
	@echo Generating DataModel from: xsd/smapi.xsd
	@(../IAS-DataModelLib-CodeGen/out/bin/ias_dm_codegen -s -x xsd/smapi.xsd -d src)
	rmdir src/src/Impl
	rmdir src/src
	
#########################################################################
-include Makefile.depend
