#ifndef PINHOLE
#define PINHOLE

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 02/05/15.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Camera.h"
#include "World.h"

class PinHole:public Camera
{
	public:
		
		float d;		// Distance of view-plane from eye

		//For stereoscopic images
		double halfCameraDist;
		int rightCameraOffset;
		int imageInterval;
		int widthMultiplicand;

		//Constructors
		PinHole(void);										//Default Constructor
		PinHole(World* worldPointer, const Point3D& eyePosition, const Point3D& lookAtPosition, const Vector3D& upVector, const float& distance, const float& rollAngle);

		//Destructor

		~PinHole(void);

		//Member Functions

		void RenderScene();
};

#endif
