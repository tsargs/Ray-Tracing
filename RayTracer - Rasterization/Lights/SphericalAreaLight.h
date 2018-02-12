#ifndef SPHERICALAREALIGHT
#define SPHERICALAREALIGHT

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 04/17/16.
//  Copyright © 2016 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Light.h"
#include "World.h"

class SphericalAreaLight:public Light
{
	public:

		RGBColor color;
		float intensity;
		Point3D position;
		float radius;

		//Constructors
		SphericalAreaLight(void);										//Default Constructor
		SphericalAreaLight(const RGBColor& colorObj, const float& iVal, const Point3D pointObj, const float& rVal, const bool& shadowState);

		//Destructor

		~SphericalAreaLight(void);

		//Member Functions

		//Returns direction of incoming light at the hit point
		Vector3D GetLightDirection(ShadeRecord &sr);

		//Returns incoming radiance at hitpoint
		RGBColor IncomingRadiance(ShadeRecord &sr);

		bool IsPointInShadow(const ShadeRecord& sr, const Vector3D& lightDirection) const;
};

#endif
