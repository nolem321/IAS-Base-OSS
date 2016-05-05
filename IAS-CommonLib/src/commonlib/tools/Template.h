/*
 * File: IAS-CommonLib/src/commonlib/tools/Template.h
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
#ifndef _IAS_Tmplate_H_
#define _IAS_Template_H_

#include <commonlib/types.h>
#include <ostream>

#include <map>
#include <vector>

namespace IAS {
/*************************************************************************/
class Template {
public:

	class Arguments {

		public:
			Arguments();

			void add(const String& strKey, const String& Value);
			virtual const String& get(const String& strKey) const;

		protected:

			typedef std::map<String, String> ValuesMap;
			ValuesMap hmValues;
	};

	class ChildArguments : public Arguments{

		public:

			ChildArguments(const Arguments& parent);

			virtual const String& get(const String& strKey) const;

		protected:
			const Arguments& parent;
	};


	virtual ~Template() throw();

	bool hasKey(const String& strKey) const;
	void evaluate(const Arguments& args, std::ostream& os)const;

protected:
	enum State{
		ST_Outside = 0,
		ST_Special = 1,
		ST_Template = 2
	};

	Template(const String& strTemplateText);

	std::vector<String> lstKeys;
	String strTemplateText;

	void buildKeysList();

	friend class ::IAS::Factory<Template>;
};

/*************************************************************************/
}
#endif /* _IAS_SDOWrap_Cpp_TEMPLATE_H_ */
