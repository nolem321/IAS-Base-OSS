#########################################################################
ARTIFACT=IASQSystemMod-SPS
ARTIFACT_ALT_NAMES+=qsmod_sps.so
#########################################################################
DEP_PROJECTS+=IAS-CommonLib
DEP_PROJECTS+=IAS-DataModelLib
DEP_PROJECTS+=IAS-LangLib
DEP_PROJECTS+=IAS-QSystemLib
#########################################################################
include Makefile.FILES
#########################################################################
include ../IAS-BuilderTools/Makefile
#########################################################################
-include $(CPPDEPS)
#########################################################################
-include Makefile.$(IAS_PLATFORM)
all : makedirs $(TARGET) links
#########################################################################
LD_LIBRARY_PATH:=../IAS-CommonLib/out/lib:$(LD_LIBRARY_PATH)
LD_LIBRARY_PATH:=../IAS-DataModelLib/out/lib:$(LD_LIBRARY_PATH)
IAS_DBG_GLOBAL=+errors,-info
IAS_DBG_DM=+errors,-info

dm : xsd/qsystem.workers.sps.xsd
	@rm -rf src/org
	@rm -rf src/Impl
	@echo Generating DataModel from: xsd/qsystem.workers.sps.xsd
	@../IAS-DataModelLib-CodeGen/out/bin/ias_dm_codegen -s -x xsd/qsystem.workers.sps.xsd -d src -n 'http://www.invenireaude.org/qsystem/workers/sps'
	#rmdir src/src/Impl
	#rmdir src/src
#########################################################################
-include Makefile.depend
