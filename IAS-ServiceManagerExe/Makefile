#########################################################################
ARTIFACTS=
#########################################################################
DEP_PROJECTS+=IAS-CommonLib
DEP_PROJECTS+=IAS-DataModelLib
DEP_PROJECTS+=IAS-ServiceManagerLib
#########################################################################
include Makefile.FILES
#########################################################################
include ../IAS-BuilderTools/Makefile
#########################################################################
-include $(CPPDEPS)
#########################################################################
-include Makefile.$(IAS_PLATFORM)
LD_LIBRARY_PATH:=../IAS-CommonLib/out/lib
LD_LIBRARY_PATH:=../IAS-DataModelLib/out/lib:$(LD_LIBRARY_PATH):/usr/local/lib

all : makedirs $(CPPEXES) 

#########################################################################
-include Makefile.depend
