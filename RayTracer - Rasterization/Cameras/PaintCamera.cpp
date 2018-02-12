// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 04/25/16.
//  Copyright © 2016 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "PaintCamera.h"

//Default Constructor
PaintCamera::PaintCamera(void)
{
	
}

PaintCamera::PaintCamera(World* worldPointer, const Point3D& eyePosition, const Point3D& lookAtPosition, const Vector3D& upVector, const float& distance, Texture *texPtr)
{
	worldPtr = worldPointer;
	eyePos = eyePosition;
	lookAtPos = lookAtPosition;
	up = upVector;
	d = distance;
	imageTexture = texPtr;
}

//Destructor
PaintCamera::~PaintCamera(void)
{

}

void PaintCamera::RenderScene(void)
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
			SetupNewOrthonormalBase((float)j/viewPlane.width, (float)i/viewPlane.height);
			for (int k = 0; k < viewPlane.samplesPerPixel; k++)
			{
				samplePoint = sampler->FetchSample();

				rayY = (i * viewPlane.pixelSize) + samplePoint.y - (viewPlane.pixelSize * viewPlane.height * 0.5);
				rayX = ((j * viewPlane.pixelSize) + samplePoint.x - (viewPlane.pixelSize * viewPlane.width * 0.5)) + halfCameraDist;

				ray.rayDirection = Vector3D(u*rayX + v*rayY - w*d).UnitVector(); // negative sign for w*d is because w is pointing the opposite direction
				currentPixelColor += tracerPtr->TraceRay(ray, 0);
			}

			int index = ((i * viewPlane.width) + (j+rightCameraOffset)) * 3;
			world.pixmap[index] = (currentPixelColor.r * 255) / viewPlane.samplesPerPixel;
			world.pixmap[++index] = (currentPixelColor.g * 255) / viewPlane.samplesPerPixel;
			world.pixmap[++index] = (currentPixelColor.b * 255) / viewPlane.samplesPerPixel;
		}
	}
	std::cout << "End of pixels\n";
}

void PaintCamera::SetupNewOrthonormalBase(const float& x, const float& y)
{
	ShadeRecord localSR;
	localSR.localHitPoint = Vector3D(x, y, 0);
	RGBColor texColor = imageTexture->GetColor(localSR);
	double nx = (texColor.r - 0.5) * 2;
	double ny = (texColor.g - 0.5) * 2;
	double nz = (texColor.b - 0.5) * 2;
	
	Vector3D posOffset(nx, ny, nz);
	//localSR.localHitPoint.PrintValues();
	//posOffset.PrintValues();
	newLookAtPos = lookAtPos + (posOffset * 50 * worldPtr->normalizedFrameVal);

	//lookAtPos.PrintValues();
	//newLookAtPos.PrintValues();
	
	w = (eyePos - newLookAtPos).UnitVector();

	u = (up^w).UnitVector();
	v = (w^u).UnitVector();
}