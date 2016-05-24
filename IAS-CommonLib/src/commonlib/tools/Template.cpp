/*
 * File: IAS-CommonLib/src/commonlib/tools/Template.cpp
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
#include "Template.h"
#include "../exception/ProcessorException.h"
#include "../exception/ItemNotFoundException.h"

#include "../memory/memory.h"
#include "../logger/logger.h"


namespace IAS {

/*************************************************************************/
Template::Arguments::Arguments(){};
/*************************************************************************/
void Template::Arguments::add(const String& strKey, const String& strValue){
	IAS_TRACER;

	hmValues[strKey]=strValue;
}
/*************************************************************************/
const String& Template::Arguments::get(const String& strKey) const{
	IAS_TRACER;

	ValuesMap::const_iterator it=hmValues.find(strKey);

	if(it == hmValues.end()) {
		IAS_THROW(ItemNotFoundException(strKey));
	}

	return it->second;
}
/*************************************************************************/
Template::ChildArguments::ChildArguments(const Arguments& parent):parent(parent){};
/*************************************************************************/
const String& Template::ChildArguments::get(const String& strKey) const{
	IAS_TRACER;

	ValuesMap::const_iterator it=hmValues.find(strKey);

	if(it == hmValues.end()) {
		return parent.get(strKey);
	}

	return it->second;

}
/*************************************************************************/
Template::Template(const String& strTemplateText){

	IAS_TRACER;
	this->strTemplateText=strTemplateText;

	buildKeysList();
}
/*************************************************************************/
Template::~Template() throw(){
	IAS_TRACER;
}
/*************************************************************************/
bool Template::hasKey(const String& strKey) const{
	IAS_TRACER;

	std::vector<String>::const_iterator it = lstKeys.begin();
	while(it != lstKeys.end()){

		if(strKey.compare(*it) == 0)
			return true;
		it++;
	}

	return false;
}
/*************************************************************************/
void Template::evaluate(const Arguments& args, std::ostream& os)const{

	State iState = ST_Outside;
	String strKey;

	for(int iIdx=0; iIdx<strTemplateText.length(); iIdx++){

		char c=strTemplateText[iIdx];

		switch(c){

			case '$':
				switch(iState){
					case ST_Outside:
						iState=ST_Special;
						break;
					case ST_Special:
						iState=ST_Outside;
						os<<'$';
						break;
					case ST_Template:
						IAS_THROW(ProcessorException("$ within Template."));
						break;
					default:
						IAS_THROW(InternalException("Template::buildKeysList::iState"));
				}
				break;


				case '{':
					switch(iState){
						case ST_Outside:
							os<<c;
							break;
						case ST_Special:
							iState=ST_Template;
							strKey="";
							break;
						case ST_Template:
							IAS_THROW(ProcessorException("{ within Template."));
							break;
						default:
							IAS_THROW(InternalException("Template::buildKeysList::iState"));
					}
					break;

					case '}':
						switch(iState){
							case ST_Outside:
								os<<c;
								break;
							case ST_Special:
								iState=ST_Outside;
								os<<'$'<<c;
								iState=ST_Outside;
								break;
							case ST_Template:
								os<<args.get(strKey);
								iState=ST_Outside;
								break;
							default:
								IAS_THROW(InternalException("Template::buildKeysList::iState"));
					}
					break;

					default:
						switch(iState){
							case ST_Outside:
								os<<c;
							break;
							case ST_Special:
							break;
							case ST_Template:
								strKey+=c;
							break;
							default:
								IAS_THROW(InternalException("Template::buildKeysList::iState"));
							}
			}/* SWITCH (c) */

		}/* FOR */

	if(iState == ST_Special)
		os<<'$';

	if(iState == ST_Template)
			os<<"${"<<strKey;


	os.flush();
}
/*************************************************************************/
void Template::buildKeysList(){
	IAS_TRACER;

	State iState = ST_Outside;
	String strKey;

	int iLine = 1;
	int iPos  = 0;

	for(int iIdx=0; iIdx<strTemplateText.length(); iIdx++){

		char c=strTemplateText[iIdx];

		iPos++;

		switch(c){

			case '$':
				switch(iState){
					case ST_Outside:
						iState=ST_Special;
						break;
					case ST_Special:
						iState=ST_Special;
						break;
					case ST_Template:
						IAS_THROW(ProcessorException("$ within Template.",iPos,iLine));
						break;
					default:
						IAS_THROW(InternalException("Template::buildKeysList::iState"));
				}
				break;


				case '{':
					switch(iState){
						case ST_Outside:
							break;
						case ST_Special:
							iState=ST_Template;
							strKey="";
							break;
						case ST_Template:
							IAS_THROW(ProcessorException("{ within Template.",iPos,iLine));
							break;
						default:
							IAS_THROW(InternalException("Template::buildKeysList::iState"));
					}
					break;

					case '}':
						switch(iState){
							case ST_Outside:
								break;
							case ST_Special:
								iState=ST_Outside;
								break;
							case ST_Template:
								lstKeys.push_back(strKey);
								iState=ST_Outside;
								break;
							default:
								IAS_THROW(InternalException("Template::buildKeysList::iState"));
					}
					break;

					case '\n':

						switch(iState){
							case ST_Special:
								iState=ST_Outside;
							case ST_Outside:
								iLine++;
								iPos=0;
								break;
							case ST_Template:
								IAS_THROW(ProcessorException("'\n' within Template.",iPos,iLine));
								break;
							default:
								IAS_THROW(InternalException("Template::buildKeysList::iState"));
					}

					default:
						if(iState == ST_Template)
							strKey+=c;

		}/* SWITCH (c) */

		}/* FOR */

}

/*************************************************************************/
}

