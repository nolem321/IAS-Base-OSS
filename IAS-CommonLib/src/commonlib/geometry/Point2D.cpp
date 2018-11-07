/*
 * File: IAS-CommonLib/src/commonlib/geometry/Point2D.cpp
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
#include "Point2D.h"

namespace IAS {
namespace Geometry {

Point2D::Point2D(Float fX, Float fY):
	fX(fX),
	fY(fY)
	{};

Point2D::Point2D(const Point2D& other){
	this->fX=other.fX;
	this->fY=other.fY;
}

Point2D& Point2D::operator=(const Point2D& other){
	this->fX=other.fX;
	this->fY=other.fY;
	return *this;
}


void Point2D::getValues(Float &fX, Float& fY) const{
	fX=this->fX;
	fY=this->fY;
}

/*************************************************************************/
std::ostream& operator<<(std::ostream& outs, const Point2D& aPoint2D){
	outs<<"("<<aPoint2D.fX<<","<<aPoint2D.fY<<")";
	return outs;
}

}
}
