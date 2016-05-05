/*
 * File: IAS-CommonLib/src/commonlib/geometry/Vector3D.h
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
#ifndef _IAS_Geometry_Vector3D_H_
#define _IAS_Geometry_Vector3D_H_

#include "../types.h"
#include "Point3D.h"

/*************************************************************************/
/** The Vector3D class.
 */

namespace IAS {
namespace Geometry {

/** The class. */
 class Vector3D {
public:
    Vector3D(const Float fDeltaX, const Float fDeltaY, const Float fDeltaZ);
	Vector3D(const Point3D& aStartPoint, const Point3D& aEndPoint);

	void getValues(Float& fDeltaX, Float& fDeltaY, Float& fDeltaZ);

protected:
	Float fDeltaX;
	Float fDeltaY;
	Float fDeltaZ;
};

}
}

#endif /* VECTORY3D_H_ */
