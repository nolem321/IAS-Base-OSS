=======================
= BINARY DISTRIBUTION
=======================

 INSTALLATION:
   Copy the shared libraries and symbolic links to the target directory:
   
	cp -ar Linux-64bit-O3/* your_ias_libraries_directory
	
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
	 gmake all
     gmake install

