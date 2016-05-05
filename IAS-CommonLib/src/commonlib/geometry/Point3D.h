/*
 * File: IAS-CommonLib/src/commonlib/geometry/Point3D.h
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
#ifndef _IAS_Geometry_Point3D_H_
#define _IAS_Geometry_Point3D_H_

#include "../types.h"

/*
 *
 */
namespace IAS {
namespace Geometry {

/*************************************************************************/
/** The Angle class.
 */

 class Point3D {
public:
	Point3D();
	Point3D(Float fX=0.0, Float fY=0.0, Float fZ=0.0);

	Point3D(const Point3D& other);
	Point3D& operator=(const Point3D& other);

	void getValues(Float &fX, Float& fY, Float& fZ) const;

	inline Float& x(){return fX;};
	inline Float& y(){return fY;};
	inline Float& z(){return fZ;};

protected:
	Float   fX;
	Float   fY;
	Float   fZ;
};

}

}

#endif /* POINT3D_H_ */
