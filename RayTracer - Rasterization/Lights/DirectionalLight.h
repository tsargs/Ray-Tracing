#ifndef DIRECTIONALLIGHT
#define DIRECTIONALLIGHT

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 02/21/15.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Light.h"
#include "World.h"

class DirectionalLight:public Light
{
	public:

		RGBColor color;
		float intensity;
		Point3D position;
		Vector3D direction;

		//Constructors
		DirectionalLight(void);										//Default Constructor
		DirectionalLight(const RGBColor& colorObj, const float& iVal, const Point3D pointObj, const Vector3D& directionVector, const bool& shadowState);

		//Destructor

		~DirectionalLight(void);

		//Member Functions

		//Returns direction of incoming light at the hit point
		Vector3D GetLightDirection(ShadeRecord &sr);

		//Returns incoming radiance at hitpoint
		RGBColor IncomingRadiance(ShadeRecord &sr);
		bool IsPointInShadow(const ShadeRecord& sr, const Vector3D& lightDirection) const;
};

#endif
