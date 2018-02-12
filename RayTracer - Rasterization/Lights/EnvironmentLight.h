#ifndef ENVIRONMENTLIGHT
#define ENVIRONMENTLIGHT

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 05/02/16.
//  Copyright © 2016 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Light.h"
#include "World.h"

class EnvironmentLight:public Light
{
	public:

		Sampler *localSampler;
		Material *localMaterial;

		Vector3D lightDirection;
		Vector3D u, v, w;
		Vector3D up = Vector3D(0.0072, 1, 0.0034);
		

		//Constructors
		EnvironmentLight(void);										//Default Constructor
		EnvironmentLight(Sampler *samplerPtr, Material *materialPtr, const bool& shadowState);

		//Destructor

		~EnvironmentLight(void);

		//Member Functions

		//Returns direction of incoming light at the hit point
		Vector3D GetLightDirection(ShadeRecord &sr);

		//Returns incoming radiance at hitpoint
		RGBColor IncomingRadiance(ShadeRecord &sr);

		bool IsPointInShadow(const ShadeRecord& sr, const Vector3D& lightDirection) const;

		void SetupOrthonormalBase(Vector3D normalVector);
};

#endif
