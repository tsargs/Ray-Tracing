#ifndef AMBIENTWITHOCCLUDER
#define AMBIENTWITHOCCLUDER

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 04/16/16.
//  Copyright © 2016 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Light.h"
#include "World.h"

class AmbientWithOccluder:public Light
{
	public:

		RGBColor color;
		float intensity;

		float baseShadeFactor;
		Vector3D u, v, w;
		Vector3D up = Vector3D(0.0072, 1, 0.0034);
		Sampler *localSampler;

		//Constructors
		AmbientWithOccluder(void);										//Default Constructor
		AmbientWithOccluder(const RGBColor& colorObj, const float& iVal, const float& baseShade, Sampler *samplerPtr);
		void SetupOrthonormalBase(Vector3D normalVector);

		//Destructor

		~AmbientWithOccluder(void);

		//Member Functions

		//Returns direction of incoming light at the hit point
		Vector3D GetLightDirection(ShadeRecord &sr);

		//Returns incoming radiance at hitpoint
		RGBColor IncomingRadiance(ShadeRecord &sr);
		bool IsPointInShadow(const ShadeRecord& sr, const Vector3D& lightDirection) const;
};

#endif
