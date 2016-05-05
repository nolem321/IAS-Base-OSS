/*
 * File: IAS-CommonLib/src/commonlib/geometry/Vector2D.cpp
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
#include "Vector2D.h"

namespace IAS {
namespace Geometry {

Vector2D::Vector2D(const Float fDeltaX, const Float fDeltaY):
	fDeltaX(fDeltaX),
	fDeltaY(fDeltaY){};

Vector2D::Vector2D(const Point2D& aStartPoint, const Point2D& aEndPoint){
	Float fX1,fX2, fY1, fY2;

	aStartPoint.getValues(fX1,fY1);
	aEndPoint.getValues(fX2,fY2);

	fDeltaX=fX2-fX1;
	fDeltaY=fY2-fY1;
}

void Vector2D::getValues(Float& fDeltaX, Float& fDeltaY){
	fDeltaX=this->fDeltaX;
	fDeltaY=this->fDeltaY;
}

}
}
