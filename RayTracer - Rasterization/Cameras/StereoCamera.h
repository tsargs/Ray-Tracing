#ifndef STEREOCAMERA
#define STEREOCAMERA

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 04/25/16.
//  Copyright © 2016 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Camera.h"
#include "World.h"

class PinHole;

class StereoCamera:public Camera
{
	public:
		
		PinHole *leftCamera;
		PinHole *rightCamera;
		float separationAngle;
		int imageInterval;  // Number of pixels between left and right image
		float d;		// Distance of view-plane from eye

		double lookAtDist;
		double halfCameraDist;

		//Constructors
		StereoCamera(void);										//Default Constructor
		StereoCamera(World* worldPointer, const Point3D& eyePosition, const Point3D& lookAtPosition, const Vector3D& upVector, const float& distance, const float& betaVal, const int& imageIntervalVal);

		//Destructor

		~StereoCamera(void);

		//Member Functions

		void RenderScene(void);
		void InitializeCameras(void);
};

#endif
