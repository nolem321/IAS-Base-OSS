/*
 * File: IAS-CommonLib/src/commonlib/geometry/Vector2D.h
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
#ifndef _IAS_Geometry_Vector2D_H_
#define _IAS_Geometry_Vector2D_H_

#include "../types.h"
#include "Point2D.h"

/*************************************************************************/
/** The Angle class.
 */

namespace IAS {
namespace Geometry {

/** The class. */
 class Vector2D {
public:
	Vector2D(const Float fDeltaX, const Float fDeltaY);
	Vector2D(const Point2D& aStartPoint, const Point2D& aEndPoint);

	void getValues(Float& fDeltaX, Float& fDeltaY);

protected:
	Float fDeltaX;
	Float fDeltaY;
};

}

}

#endif /* VECTOR2D_H_ */
