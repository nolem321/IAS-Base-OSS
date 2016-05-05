/*
 * File: IAS-CommonLib/src/commonlib/callbacks/CallbacksRegister.h
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

#ifndef IAS_CALLBACKSREGISTER_H_
#define IAS_CALLBACKSREGISTER_H_

#include "TypeInfoProxy.h"

/*
 *
 */

namespace IAS {

/*************************************************************************/
/** The template for a call back register.
 * One can add call back functions indexed with class type.
 *
 */

template<class E, class H>
class CallbackRegister {
public:

  typedef std::map<TypeInfoProxy, H *> CallbackMap;
  CallbackMap hmCallbacks;


  ~CallbackRegister(){
	  for(typename CallbackMap::iterator it=hmCallbacks.begin();
		  it != hmCallbacks.end();
		  it++){
			  try{ IAS_DFT_FACTORY<H>::Free(it->second); }catch(...){};
	  };
  }

  template <typename T>
  void registerCallback(H *h) {
    hmCallbacks[&typeid(T)] = h;
  }

  H* getCallback(E* o) {
	  IAS_TRACER;
	  if(hmCallbacks.count(&typeid(*o)) == 0)
		  IAS_THROW(InternalException(String("getCallback")+=typeid(*o).name()));
	  return hmCallbacks[&typeid(*o)];
  }

};



}


#define IAS_TYPEID_CHECK(t, e) \
{ if(typeid(*e) != typeid(t)){            \
	  String strInfo("Type mismatch:");     \
	  strInfo+=typeid(*e).name();            \
      strInfo+=", expected: ";               \
	  strInfo+=typeid(t).name();             \
	  IAS_THROW(InternalException(strInfo));}}     \

#define IAS_DYNAMICCAST(t, e)	(dynamic_cast<t*>(e))
#define IAS_DYNAMICCAST_CONST(t, e)	(dynamic_cast<const t*>(e))

#endif /* CALLBACKSREGISTER_H_ */
