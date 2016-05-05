/*
 * File: IAS-CommonLib/src/commonlib/net/ssl/CertificateX509.cpp
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
#include <commonlib/logger/logger.h>
#include <commonlib/memory/memory.h>
#include "CertificateX509.h"
#include "SSLException.h"
#include <commonlib/exception/ItemNotFoundException.h>

namespace IAS {
namespace Net {
namespace SSL {

/***********************************************************************/
CertificateX509::CertificateX509(X509* x509):x509(x509){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(x509);
}
/*************************************************************************/
String CertificateX509::getIssuerName()const{
	IAS_TRACER;

	char sBuffer[4096];
	X509_NAME* name=X509_get_issuer_name(this->x509);

	X509_NAME_oneline(name,sBuffer,4096);

	return String(sBuffer);
}
/*************************************************************************/
String CertificateX509::getSubjectName()const{
	IAS_TRACER;

	char sBuffer[4096];
	X509_NAME* name=X509_get_subject_name(this->x509);
	X509_NAME_oneline(name,sBuffer,4096);

	return String(sBuffer);
}
/*************************************************************************/
void CertificateX509::getSubject(NamesMap& hmNames)const{
	IAS_TRACER;

	 X509_NAME* name=X509_get_subject_name(this->x509);

	 hmNames.clear();
	 char sBuffer[32];
	 for (int iIdx = 0; iIdx < X509_NAME_entry_count(name); iIdx++){
		 X509_NAME_ENTRY *e = X509_NAME_get_entry(name, iIdx);
		 if(e){
			 OBJ_obj2txt(sBuffer,32,e->object,0);

			 hmNames[sBuffer]=String((char*)ASN1_STRING_data(e->value));
		 }
	  }

}
/*************************************************************************/
String CertificateX509::getSubjectField(const String& strID)const{
	IAS_TRACER;

	 int nid = OBJ_txt2nid(strID.c_str());

	 if(nid == NID_undef)
		 IAS_THROW(ItemNotFoundException()<<"SSL NID: "<<strID);

	 return getSubjectField(nid);
}
/*************************************************************************/
String CertificateX509::getSubjectField(int nid)const{
	IAS_TRACER;

	 X509_NAME* name=X509_get_subject_name(this->x509);

	 if(!name)
		 IAS_THROW(ItemNotFoundException()<<"SSL subject when looking for: "<<nid);

	 int idx = X509_NAME_get_index_by_NID(name, nid, -1);

	 if(idx == -1)
		IAS_THROW(ItemNotFoundException()<<"SSL X509_NAME_get_index_by_NID for: "<<nid);

	 X509_NAME_ENTRY *entry = X509_NAME_get_entry(name, idx);

	 if(!entry)
		 IAS_THROW(ItemNotFoundException()<<"SSL X509_NAME_get_entry for: "<<nid);

	  ASN1_STRING *data = X509_NAME_ENTRY_get_data(entry);

	  if(!data)
		  return String("");

	  return String((char*)ASN1_STRING_data(data));
}
/*************************************************************************/
CertificateX509::~CertificateX509() throw(){
	IAS_TRACER;
	X509_free(this->x509);
}
/*************************************************************************/


}
}
}
