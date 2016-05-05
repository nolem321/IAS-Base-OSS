/*
 * File: IAS-CommonLib/src/commonlib/geometry/Vector3D.cpp
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
#include "Vector3D.h"

namespace IAS {
namespace Geometry {

Vector3D::Vector3D(const Float fDeltaX, const Float fDeltaY, const Float fDeltaZ):
	fDeltaX(fDeltaX),
	fDeltaY(fDeltaY),
	fDeltaZ(fDeltaZ)
	{};

Vector3D::Vector3D(const Point3D& aStartPoint, const Point3D& aEndPoint){
	Float fX1,fX2, fY1, fY2, fZ1, fZ2;

	aStartPoint.getValues(fX1,fY1,fZ1);
	aEndPoint.getValues(fX2,fY2,fZ2);

	fDeltaX=fX2-fX1;
	fDeltaY=fY2-fY1;
	fDeltaZ=fZ2-fZ1;

}

void Vector3D::getValues(Float& fDeltaX, Float& fDeltaY, Float& fDeltaZ){
	fDeltaX=this->fDeltaX;
	fDeltaY=this->fDeltaY;
	fDeltaZ=this->fDeltaZ;
}


}
}
