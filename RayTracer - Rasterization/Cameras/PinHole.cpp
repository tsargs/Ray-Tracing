// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 02/05/15.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "PinHole.h"

//Default Constructor
PinHole::PinHole(void)
{
	
}

PinHole::PinHole(World* worldPointer, const Point3D& eyePosition, const Point3D& lookAtPosition, const Vector3D& upVector, const float& distance, const float& rollAngle)
{
	worldPtr = worldPointer;
	eyePos = eyePosition;
	lookAtPos = lookAtPosition;
	up = upVector;
	d = distance;
	roll = rollAngle;
	SetupOrthonormalBase();
}

//Destructor
PinHole::~PinHole(void)
{

}

void PinHole::RenderScene(void)
{
	std::cout << "PinHole::RenderScene";
	World world = *worldPtr;
	ViewPlane viewPlane = worldPtr->viewPlane;
	Tracer *tracerPtr = worldPtr->tracerPtr;
	Ray ray;
	double rayX;
	double rayY;
	RGBColor currentPixelColor;

	Sampler *sampler = viewPlane.samplerPtr;

	Point2D samplePoint;

	ray.origin = Point3D(eyePos.x, eyePos.y, eyePos.z);

	for (int i = 0; i < viewPlane.height; i++)
	{
		for (int j = 0; j < viewPlane.width; j++)
		{
			currentPixelColor = black;
			for (int k = 0; k < viewPlane.samplesPerPixel; k++)
			{
				samplePoint = sampler->FetchSample();

				rayY = (i * viewPlane.pixelSize) + samplePoint.y - (viewPlane.pixelSize * viewPlane.height * 0.5);
				rayX = ((j * viewPlane.pixelSize) + samplePoint.x - (viewPlane.pixelSize * viewPlane.width * 0.5));

				ray.rayDirection = Vector3D(u*rayX + v*rayY - w*d).UnitVector(); // negative sign for w*d is because w is pointing the opposite direction
				currentPixelColor += tracerPtr->TraceRay(ray, 0);
			}

			int index = ((i * (viewPlane.width)) + (j)) * 3;
			world.pixmap[index] = (currentPixelColor.r * 255) / viewPlane.samplesPerPixel;
			world.pixmap[++index] = (currentPixelColor.g * 255) / viewPlane.samplesPerPixel;
			world.pixmap[++index] = (currentPixelColor.b * 255) / viewPlane.samplesPerPixel;
		}
	}
	std::cout << "End of pixels\n";
}
