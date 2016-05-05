/*
 * File: IAS-CommonLib/src/commonlib/geometry/Point2D.h
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
#ifndef _IAS_Geometry_Point2D_H_
#define _IAS_Geometry_Point2D_H_

#include "../types.h"

#include <iostream>

/*************************************************************************/
/** The Angle class.
 */

namespace IAS {
namespace Geometry {

/** The class. */
 class Point2D {
public:
	Point2D(Float fX=0.0, Float fY=0.0);

	Point2D(const Point2D& other);
	Point2D& operator=(const Point2D& other);

	void getValues(Float &fX, Float& fY) const;

	inline const Float& x() const {return fX;};
	inline const Float& y() const {return fY;};

	friend std::ostream& operator<<(std::ostream& outs, const Point2D& aPoint2D);

protected:
	Float   fX;
	Float   fY;
};




}
}

#endif /* POINT2D_H_ */
