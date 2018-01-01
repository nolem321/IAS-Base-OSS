/*
 * File: IAS-CommonLib/src/commonlib/net/ssl/Environment.cpp
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
#include "Environment.h"

#include <openssl/err.h>

#include <commonlib/tools/EnvTools.h>

#include "SSLException.h"
#include <signal.h>

namespace IAS {
namespace Net {
namespace SSL {

/* This array will store all of the mutexes available to OpenSSL. */
static pthread_mutex_t *mutex_buf=NULL;

static void locking_function(int mode, int n, const char * file, int line)
{
    if (mode & CRYPTO_LOCK)
    	pthread_mutex_lock(mutex_buf+n);
    else
    	pthread_mutex_unlock(mutex_buf+n);
}

static unsigned long id_function(void)
{
    return ((unsigned long)pthread_self());
}

int thread_setup(void)
{
    int i;

    mutex_buf = (pthread_mutex_t*) malloc(CRYPTO_num_locks() * sizeof(pthread_mutex_t));
    if (!mutex_buf)
        return 0;
    for (i = 0;  i < CRYPTO_num_locks(  );  i++)
    	pthread_mutex_init(mutex_buf+i,NULL);
    CRYPTO_set_id_callback(id_function);
    CRYPTO_set_locking_callback(locking_function);
    return 1;
}

int thread_cleanup(void)
{
    int i;
    if (!mutex_buf)
        return 0;
    CRYPTO_set_id_callback(NULL);
    CRYPTO_set_locking_callback(NULL);
    for (i = 0;  i < CRYPTO_num_locks(  );  i++)
    	pthread_mutex_destroy(mutex_buf+i);
    free(mutex_buf);
    mutex_buf = NULL;
    return 1;
}
/*************************************************************************/
Environment::Environment():bio_err(0),ciphers(0){
	IAS_TRACER;
	thread_setup();
	initialize();
}
/*************************************************************************/
Environment::~Environment() throw(){
	IAS_TRACER;
	thread_cleanup();
}
/*************************************************************************/
void Environment::printErrors(){
	ERR_print_errors(bio_err);
}
/*************************************************************************/
void Environment::initialize() {
	IAS_TRACER;

	if (!bio_err) {
		/* Global system initialization*/

	    OpenSSL_add_all_algorithms();
	    ERR_load_BIO_strings();
	    ERR_load_crypto_strings();

		SSL_library_init();
		SSL_load_error_strings();

		/* An error write context */
		bio_err = BIO_new_fp(stderr, BIO_NOCLOSE);
	}

	//TODO signal(SIGPIPE, SIG_IGN).
	//This should make send to return EPIPE error. Otherwise you can
	// send MSG_NOSIGNAL flag to the send call.
	//signal(SIGPIPE, 0);

    /* Set our cipher list */
    //if(ciphers){
    //  SSL_CTX_set_cipher_list(ctx,ciphers);
   // }

}

}
}
}
