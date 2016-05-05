/*
 * File: IAS-QSystemLib/src/qs/api/Attributes.h
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
#ifndef _IAS_QS_API_Attributes_H_
#define _IAS_QS_API_Attributes_H_

#include <commonlib/commonlib.h>

namespace IAS {
namespace QS {
namespace API {

/*************************************************************************/
/** The Attributes class.
 *
 */
class Attributes {
public:

	void setValue(const String& strName, const String& strValue);
	const String& getValue(const String& strName)const;
	bool          isSet(const String& strName)const;

	void unset(const String& strName);

	typedef HashMapWithStringKey<String> ValuesMap;

	typedef ValuesMap::iterator iterator;
	typedef ValuesMap::const_iterator const_iterator;

	inline iterator begin(){ return hmValues.begin(); };
	inline const_iterator begin()const { return hmValues.begin(); };

	inline iterator end(){ return hmValues.end(); };
	inline const_iterator end()const { return hmValues.end(); };

	inline Attributes& operator=(const Attributes& other){

		for(const_iterator it=other.begin(); it != other.end(); it++)
			setValue(it->first,it->second);

		return *this;
	}

	inline void setMID(const String& strValue){
		setValue(CA_MID,strValue);
	}

	inline const String& getMID()const{
		return getValue(CA_MID);
	}

	inline void setCID(const String& strValue){
		setValue(CA_CID,strValue);
	}

	inline const String& getCID()const{
		return getValue(CA_CID);
	}


	inline void setFormat(const String& strValue){
		setValue(CA_Format,strValue);
	}

	inline const String& getFormat()const{
		return getValue(CA_Format);
	}


	inline void setReplyTo(const String& strValue){
		setValue(CA_ReplyTo,strValue);
	}

	inline const String& getReplyTo()const{
		return getValue(CA_ReplyTo);
	}

	inline void setPersistance(bool bValue){
		String strValue(bValue ? "1" : "0");
		setValue(CA_Persistance,strValue);
	}

	inline bool getPersistance()const{
		return isSet(CA_Persistance) && getValue(CA_Persistance).compare("1")==0;
	}

	inline void setExpiration(int iValue){

		if(iValue == CA_Unlimited_Expiration){
			hmValues.erase(CA_Expiration);
		}else{
			StringStream ssValue;
			ssValue<<iValue;
			setValue(CA_Expiration,ssValue.str());
		}

	}

	inline int getExpiration()const{
		if(!isSet(CA_Expiration))
			return CA_Unlimited_Expiration;

		return TypeTools::StringToInt(getValue(CA_Expiration));
	}

	inline void setPriority(int iValue){
		StringStream ssValue;
		ssValue<<iValue;
		setValue(CA_Priority,ssValue.str());
	}

	inline int getPriority()const{
		return TypeTools::StringToInt(getValue(CA_Priority));
	}

	static const String& CA_MID;
	static const String& CA_CID;
	static const String& CA_Format;
	static const String& CA_ReplyTo;
	static const String& CA_Persistance;
	static const String& CA_Expiration;
	static const String& CA_Priority;

	static const int CA_Unlimited_Expiration = -1;

protected:

	ValuesMap							  hmValues;

};

/*************************************************************************/
}
}
}

#endif /* _IAS_QS_API_Attributes_H_ */
