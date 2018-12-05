/*
 * File: IAS-CommonLib/src/commonlib/geometry/Angle.cpp
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
#include "Angle.h"

namespace IAS {
namespace Geometry {

const Float Angle::NO_WRAP = -999.0;
const Float Angle::WRAP_360 = 360.0;
const Float Angle::WRAP_180 = 180.0;
const Float Angle::WRAP_PLUS_MINUS_180 = -180.0;
const Float Angle::WRAP_PLUS_MINUS_90 = -90.0;

Angle::Angle(Float fAngle, Float fWrap):
	fWrap(fWrap){
	set(fAngle);
}

Angle::Angle(const Angle& other){
	fWrap=other.fWrap;
	set(fAngle);
}

Angle& Angle::operator=(const Angle& other){
	fWrap=other.fWrap;
	set(other.fAngle);
	return *this;

}
Angle& Angle::operator=(const Float& fAngle){
	set(fAngle);
	return *this;
}

void Angle::set(const Float& fAngle){
	//TODO (LL) Wrap
	this->fAngle=fAngle;
}


}
}
