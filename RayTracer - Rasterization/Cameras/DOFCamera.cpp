// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 04/15/16.
//  Copyright © 2016 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "DOFCamera.h"

//Default Constructor
DOFCamera::DOFCamera(void)
{
	
}

DOFCamera::DOFCamera(World* worldPointer, const Point3D& eyePosition, const Point3D& lookAtPosition, const Vector3D& upVector, const float& distance, const float& focalPlaneDist, const float& lens_Radius, const float& rollAngle, Sampler *samplerPtr)
{
	worldPtr = worldPointer;
	eyePos = eyePosition;
	lookAtPos = lookAtPosition;
	up = upVector;
	d = distance;
	roll = rollAngle;
	SetupOrthonormalBase();

	focalPlaneDistance = focalPlaneDist;
	fDistByD = focalPlaneDistance / d;
	lensRadius = lens_Radius;
	localSampler = samplerPtr;
	localSampler->MapSamplesToCircle();
}

//Destructor
DOFCamera::~DOFCamera(void)
{

}

void DOFCamera::RenderScene(void)
{
	std::cout << "DOFCamera::RenderScene";
	World world = *worldPtr;
	ViewPlane viewPlane = worldPtr->viewPlane;
	Tracer *tracerPtr = worldPtr->tracerPtr;
	Ray ray;
	double rayX;
	double rayY;
	RGBColor currentPixelColor;

	Sampler *sampler = viewPlane.samplerPtr;
	//localSampler->MapSamplesToCircle();

	Point2D samplePoint;
	Point2D lensPoint;
	Point3D fHitPoint;  //Intersection point on focal plane

	for (int i = 0; i < viewPlane.height; i++)
	{
		for (int j = 0; j < viewPlane.width; j++)
		{
			currentPixelColor = black;
			for (int k = 0; k < viewPlane.samplesPerPixel; k++)
			{
				samplePoint = sampler->FetchSample();
				lensPoint = localSampler->FetchCircularSample() * lensRadius;
				
				rayY = (i * viewPlane.pixelSize) + samplePoint.y - (viewPlane.pixelSize * viewPlane.height * 0.5);
				rayX = (j * viewPlane.pixelSize) + samplePoint.x - (viewPlane.pixelSize * viewPlane.width * 0.5);

				fHitPoint.x = rayX*fDistByD;
				fHitPoint.y = rayY*fDistByD;
				fHitPoint.z = -focalPlaneDistance;

				ray.origin = Point3D(eyePos.x, eyePos.y, eyePos.z) + u*lensPoint.x + v*lensPoint.y;
				ray.rayDirection = Vector3D(u*(fHitPoint.x - lensPoint.x) + v*(fHitPoint.y - lensPoint.y) - w*focalPlaneDistance).UnitVector();

				currentPixelColor += tracerPtr->TraceRay(ray, 0);
			}

			int index = ((i * viewPlane.width) + j) * 3;
			world.pixmap[index] = (currentPixelColor.r * 255) / viewPlane.samplesPerPixel;
			world.pixmap[++index] = (currentPixelColor.g * 255) / viewPlane.samplesPerPixel;
			world.pixmap[++index] = (currentPixelColor.b * 255) / viewPlane.samplesPerPixel;
		}
	}
	std::cout << "End of pixels\n";
}
