#ifndef SPOTLIGHT
#define SPOTLIGHT

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 02/26/15.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Light.h"
#include "World.h"

class SpotLight:public Light
{
	public:

		RGBColor color;
		float intensity;
		Point3D position;
		Point3D lookAtPosition;
		Vector3D direction;

		//Constructors
		SpotLight(void);										//Default Constructor
		SpotLight(const RGBColor& colorObj, const float& iVal, const Point3D pointObj, const Point3D& lookAtPos, const bool& shadowState);

		//Destructor

		~SpotLight(void);

		//Member Functions

		//Returns direction of incoming light at the hit point
		Vector3D GetLightDirection(ShadeRecord &sr);

		//Returns incoming radiance at hitpoint
		RGBColor IncomingRadiance(ShadeRecord &sr);
		bool IsPointInShadow(const ShadeRecord& sr, const Vector3D& lightDirection) const;
};

#endif
