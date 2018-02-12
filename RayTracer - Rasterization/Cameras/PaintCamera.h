#ifndef PAINTCAMERA
#define PAINTCAMERA

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 04/25/16.
//  Copyright © 2016 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Camera.h"
#include "World.h"

class PaintCamera:public Camera
{
	public:
		
		float d;		// Distance of view-plane from eye

		Point3D newLookAtPos;
		Texture *imageTexture;

		//For stereoscopic images
		double halfCameraDist;
		int rightCameraOffset;
		int imageInterval;
		int widthMultiplicand;

		//Constructors
		PaintCamera(void);										//Default Constructor
		PaintCamera(World* worldPointer, const Point3D& eyePosition, const Point3D& lookAtPosition, const Vector3D& upVector, const float& distance, Texture *texPtr);

		//Destructor

		~PaintCamera(void);

		//Member Functions

		void RenderScene();
		void SetupNewOrthonormalBase(const float& x, const float& y);
};

#endif
