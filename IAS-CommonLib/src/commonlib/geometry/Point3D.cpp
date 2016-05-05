/*
 * File: IAS-CommonLib/src/commonlib/geometry/Point3D.cpp
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
#include "Point3D.h"

namespace IAS {
namespace Geometry {

Point3D::Point3D(Float fX, Float fY, Float fZ):
	fX(fX),
	fY(fY),
	fZ(fZ)
	{};

Point3D::Point3D(const Point3D& other){
	this->fX=other.fX;
	this->fY=other.fY;
}

Point3D& Point3D::operator=(const Point3D& other){
	this->fX=other.fX;
	this->fY=other.fY;
}


void Point3D::getValues(Float &fX, Float& fY, Float& fZ)const{
	fX=this->fX;
	fY=this->fY;
	fZ=this->fZ;
}


}
}
