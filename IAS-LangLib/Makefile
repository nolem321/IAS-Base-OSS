
#########################################################################
ARTIFACT=IASLangLib
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
all : makedirs $(TARGET)
#########################################################################
-include Makefile.depend
#########################################################################
src/lang/script/parser/AutoGenParser.cpp: src/lang/script/parser/AutoGenParser.yy
	echo bison for $@
	bison -v -o $@ $<
#########################################################################
src/lang/script/parser/AutoGenParser.hpp: src/lang/script/parser/AutoGenParser.yy
	echo bison for $@
	bison -v -o $@ $<

#########################################################################
ifdef LD_LIBRARY_PATH
LD_LIBRARY_PATH:=../IAS-CommonLib/out/lib:$(LD_LIBRARY_PATH)
else
LD_LIBRARY_PATH:=../IAS-CommonLib/out/lib
endif
LD_LIBRARY_PATH:=../IAS-DataModelLib/out/lib:$(LD_LIBRARY_PATH)
IAS_DBG_GLOBAL=+errors,-info,-throw,+stacktrace
IAS_DBG_DM=+errors,-info

IAS_XSD_FILES=xsd/builtin.xsd
SPACE=
SPACE+=
IAS_XSD_FILES_COMMA=$(subst $(SPACE),:,${IAS_XSD_FILES})

dm : ${IAS_XSD_FILES}
	@rm -rf src/org
	@rm -rf src/Impl
	@echo Generating DataModel from: ${IAS_XSD_FILES}
	@../IAS-DataModelLib-CodeGen/out/bin/ias_dm_codegen -s -x ${IAS_XSD_FILES_COMMA} -d src	
	@rm -rf src/src

