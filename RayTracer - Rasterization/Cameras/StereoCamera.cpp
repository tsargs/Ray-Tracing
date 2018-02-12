// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 04/25/16.
//  Copyright © 2016 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "StereoCamera.h"

//Default Constructor
StereoCamera::StereoCamera(void)
{
	
}

StereoCamera::StereoCamera(World* worldPointer, const Point3D& eyePosition, const Point3D& lookAtPosition, const Vector3D& upVector, const float& distance, const float& betaVal, const int& imageIntervalVal)
{
	worldPtr = worldPointer;
	eyePos = eyePosition;
	lookAtPos = lookAtPosition;
	up = upVector;
	d = distance;
	separationAngle = betaVal;
	imageInterval = imageIntervalVal;
	SetupOrthonormalBase();

	lookAtDist = lookAtPos.Distance(eyePos);
	halfCameraDist = tan(0.5 * separationAngle * (pi / 180)) * lookAtDist;
	InitializeCameras();
}

//Destructor
StereoCamera::~StereoCamera(void)
{

}

void StereoCamera::InitializeCameras(void)
{
	Point3D eyePosition;
	Point3D lookAtPosition;
	Vector3D upVector(0, 1, 0);
	float viewPlaneDistance = d;
	float rollAngle = 0;

	eyePosition = eyePos - (u * halfCameraDist);
	lookAtPosition = lookAtPos - (u * halfCameraDist);

	leftCamera = new PinHole(worldPtr, eyePosition, lookAtPosition, upVector, viewPlaneDistance, rollAngle);
	leftCamera->halfCameraDist = halfCameraDist;
	leftCamera->rightCameraOffset = 0;
	leftCamera->imageInterval = imageInterval;
	leftCamera->widthMultiplicand = 2;

	eyePosition = eyePos + (u * halfCameraDist);
	lookAtPosition = lookAtPos + (u * halfCameraDist);

	rightCamera = new PinHole(worldPtr, eyePosition, lookAtPosition, upVector, viewPlaneDistance, rollAngle);
	rightCamera->halfCameraDist = -halfCameraDist;
	rightCamera->rightCameraOffset = worldPtr->viewPlane.width + imageInterval;
	rightCamera->imageInterval = imageInterval;
	rightCamera->widthMultiplicand = 2;
}

void StereoCamera::RenderScene(void)
{
	std::cout << "StereoCamera::RenderScene";
	leftCamera->RenderScene();
	rightCamera->RenderScene();
	std::cout << "End of pixels\n";
}
