#########################################################################
ARTIFACT=IASQSystemMod-LMDB
ARTIFACT_ALT_NAMES+=dsmod_lmdb.so
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
-include Makefile.depend
