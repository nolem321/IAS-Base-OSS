/*
 * File: IAS-CommonLib/src/commonlib/configfile/PropertiesProviderFromFile.h
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
/* IAS_COPYRIGHT */

/* ChangeLog:
 *
 */

#ifndef PROPERTIESPROVIDERFROMFILE_H_
#define PROPERTIESPROVIDERFROMFILE_H_

#include "PropertiesProvider.h"
#include "../memory/ma/Factory.h"
#include <fstream>

namespace IAS{

/*************************************************************************/
/** The properties provider for a file.
 */
class PropertiesProviderFromFile : public PropertiesProvider
{
public:
	virtual ~PropertiesProviderFromFile();
	
	
	virtual void getNextProperty(String& strName, String& strValue);
	virtual void reset();

	PropertiesProviderFromFile(const char* sFileName);

protected:
	PropertiesProviderFromFile();
	virtual void openFile(const char* sFileName);
	
private:
	std::ifstream isFile;
	int			  iLineNo;
    String        strFileName;

    friend class ::IAS::Factory<PropertiesProviderFromFile>;
};

}

#endif /*PROPERTIESPROVIDERFROMFILE_H_*/
