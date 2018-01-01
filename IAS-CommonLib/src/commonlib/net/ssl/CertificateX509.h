/*
 * File: IAS-CommonLib/src/commonlib/net/ssl/CertificateX509.h
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
#ifndef _IAS_Net_SSL_CertificateX509_H_
#define _IAS_Net_SSL_CertificateX509_H_

#include <commonlib/misc/InstanceFeature.h>

#include <openssl/ssl.h>

namespace IAS {
namespace Net {
namespace SSL {

/*************************************************************************/
/** The CertificateX509 class.
 *
 */
class CertificateX509 {
public:

	virtual ~CertificateX509() throw();

	X509 *getCertificateX509()const{
		return x509;
	}

	String getBase64EncodedContent();

	typedef std::map<String,String> NamesMap;

	String getIssuerName()const;
	String getSubjectName()const;

	void getSubject(NamesMap& hmNames)const;

	String getSubjectField(const String& strID)const;

	inline String getSubjectCN()const{ return getSubjectField(NID_commonName);};
	inline String getSubjectON()const{ return getSubjectField(NID_organizationName);};
	inline String getSubjectLN()const{ return getSubjectField(NID_localityName);};

protected:

	CertificateX509(X509* x509);
	CertificateX509(const String& strFileName);

	X509 *x509;

	String getSubjectField(int nid)const;

	friend class Factory<CertificateX509>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_Net_SSL_CertificateX509_H_ */
