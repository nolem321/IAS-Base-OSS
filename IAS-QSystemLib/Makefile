#########################################################################
ARTIFACT=IASQSystemLib
#########################################################################
DEP_PROJECTS+=IAS-CommonLib
DEP_PROJECTS+=IAS-DataModelLib
DEP_PROJECTS+=IAS-LangLib
#########################################################################
LANG_FILES+=cache.y
LANG_FILES+=dict.y
LANG_FILES+=execute.y
LANG_FILES+=fmt.y
LANG_FILES+=qs.y
LANG_FILES+=storage.y
LANG_FILES+=template.y
LANG_FILES+=typeinfo.y
#########################################################################
include Makefile.FILES
#########################################################################
include ../IAS-BuilderTools/Makefile
#########################################################################
-include $(CPPDEPS)
#########################################################################
-include Makefile.$(IAS_PLATFORM)
all : makedirs $(TARGET)
#########################################################################
ifdef LD_LIBRARY_PATH
LD_LIBRARY_PATH:=../IAS-CommonLib/out/lib:$(LD_LIBRARY_PATH)
else
LD_LIBRARY_PATH:=../IAS-CommonLib/out/lib
endif
LD_LIBRARY_PATH:=../IAS-DataModelLib/out/lib:$(LD_LIBRARY_PATH)
IAS_DBG_GLOBAL=+errors,-info,-throw,+stacktrace
IAS_DBG_DM=+errors,-info

IAS_XSD_FILES=xsd/qsystem.xsd
IAS_XSD_FILES+=xsd/qsystem.typeinfo.xsd
IAS_XSD_FILES+=xsd/qsystem.stats.xsd
IAS_XSD_FILES+=xsd/qsystem.service.xsd
IAS_XSD_FILES+=xsd/qsystem.workers.spec.xsd

IAS_XSD_NS=http://www.invenireaude.org/qsystem

SPACE=
SPACE+=
IAS_XSD_FILES_COMMA=$(subst $(SPACE),:,${IAS_XSD_FILES})

dm : ${IAS_XSD_FILES}
	@rm -rf src/org
	@rm -rf src/Impl
	@echo Generating DataModel from: ${IAS_XSD_FILES}
	@../IAS-DataModelLib-CodeGen/out/bin/ias_dm_codegen -s -x ${IAS_XSD_FILES_COMMA} -n ${IAS_XSD_NS} -d src
	@rm -rf src/src

#########################################################################
-include Makefile.depend
