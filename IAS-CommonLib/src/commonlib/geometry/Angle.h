/*
 * File: IAS-CommonLib/src/commonlib/geometry/Angle.h
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
#ifndef ANGLE_H_
#define ANGLE_H_

#include "../types.h"
/*
 *
 */
namespace IAS {
namespace Geometry {

/*************************************************************************/
/** The Angle class.
 */

class Angle {
public:

	static const Float NO_WRAP ;
	static const Float WRAP_360;
	static const Float WRAP_180;
	static const Float WRAP_PLUS_MINUS_180 ;
	static const Float WRAP_PLUS_MINUS_90;

	Angle(Float fAngle=0.0, Float fWrap=360.0);
	Angle(const Angle& other);

	Angle& operator=(const Angle& other);
	Angle& operator=(const Float& fAngle);
	void set(const Float& fAngle);

	inline operator Float() const{return fAngle;};
	inline Float angle()const{return fAngle;};

protected:
	Float fAngle;
	Float fWrap;
};


}
}

#endif /* ANGLE_H_ */
