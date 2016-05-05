=======================
= SOURCE DISTRIBUTION
=======================

Compilation:
------------------

 Read the instructions:
   http://invenireaude.com/content/articles/faq/compilation.html
 
 and use the:
 
   ./IAS-BuilderTools/bin/build_all.sh
       
 or just try:

1. Set IAS_PLATFORM to proper Makefile.____ sufix
	export IAS_PLATFORM=Linux-64bitO3
	export IAS_DEST_DIR=install_destination_directory (default is /usr/local)
	
2. Invoke:
	 gmake clean
	 gmake sdo
	 gmake all
     sudo gmake install

