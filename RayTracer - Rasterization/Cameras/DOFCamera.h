#ifndef DOFCAMERA
#define DOFCAMERA

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 04/15/16.
//  Copyright © 2016 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Camera.h"
#include "World.h"

class DOFCamera:public Camera
{
	public:
		
		float d;		// Distance of view-plane from eye
		float focalPlaneDistance;
		float lensRadius;
		Sampler *localSampler;

		float fDistByD;

		//Constructors
		DOFCamera(void);										//Default Constructor
		DOFCamera(World* worldPointer, const Point3D& eyePosition, const Point3D& lookAtPosition, const Vector3D& upVector, const float& distance, const float& focalPlaneDist, const float& lens_Radius, const float& rollAngle, Sampler *samplerPtr);

		//Destructor

		~DOFCamera(void);

		//Member Functions

		void RenderScene();
};

#endif
