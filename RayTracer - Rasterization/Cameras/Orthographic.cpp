// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 02/05/15.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Orthographic.h"

//Default Constructor
Orthographic::Orthographic(void)
{
	
}

Orthographic::Orthographic(World* worldPointer)
{
	worldPtr = worldPointer;
}

//Destructor
Orthographic::~Orthographic(void)
{

}

void Orthographic::RenderScene(void)
{
	std::cout << "Orthographic::RenderScene";
	World world = *worldPtr;
	ViewPlane viewPlane = worldPtr->viewPlane;
	Tracer *tracerPtr = worldPtr->tracerPtr;
	Ray ray;
	double rayX;
	double rayY;
	RGBColor currentPixelColor;

	ray.rayDirection = Vector3D(0, 0, 1);

	Sampler *sampler = viewPlane.samplerPtr;

	Point2D samplePoint;

	for (int i = 0; i < viewPlane.height; i++)
	{
		for (int j = 0; j < viewPlane.width; j++)
		{
			currentPixelColor = black;
			for (int k = 0; k < viewPlane.samplesPerPixel; k++)
			{
				samplePoint = sampler->FetchSample();
				//std::cout << "samplePoint: " << samplePoint.x << ", " << samplePoint.y << "\n";
				rayY = (i * viewPlane.pixelSize) + samplePoint.y - (viewPlane.pixelSize * viewPlane.height * 0.5);
				rayX = (j * viewPlane.pixelSize) + samplePoint.x - (viewPlane.pixelSize * viewPlane.width * 0.5);

				//rayY = viewPlane.pixelSize * (i - (viewPlane.height * 0.5) + 0.5);
				//rayX = viewPlane.pixelSize * (j - (viewPlane.width * 0.5) + 0.5);

				ray.origin = Point3D(rayX, rayY, -100);
				currentPixelColor += tracerPtr->TraceRay(ray);
				//std::cout << "currentPixelColor: " << currentPixelColor.r << ", " << currentPixelColor.g << "\n";
			}

			int index = ((i * viewPlane.width) + j) * 3;
			world.pixmap[index] = (currentPixelColor.r * 255) / viewPlane.samplesPerPixel;
			world.pixmap[++index] = (currentPixelColor.g * 255) / viewPlane.samplesPerPixel;
			world.pixmap[++index] = (currentPixelColor.b * 255) / viewPlane.samplesPerPixel;

			//if (currentPixelColor.r == 1)
			//{
			//	std::cout << "i: " << i << "  j: " << j << "\n";
			//	//std::cout << currentPixelColor.r << currentPixelColor.g << currentPixelColor.b << "\n";
			//}
		}
	}



	std::cout << "End of pixels\n";
}
