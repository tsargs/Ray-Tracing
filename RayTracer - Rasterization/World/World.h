#ifndef WORLD
#define WORLD

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 12/30/15.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "ViewPlane.h"
#include "Sphere.h"
#include "DomeSphere.h"
#include "Plane.h"
#include "Cube.h"
#include "Rectangle.h"
#include "Quadric.h"
#include "Triangle.h"
#include "Disk.h"
#include "OpenCylinder.h"
#include "CompoundObject.h"
#include "FlatMeshTriangle.h"
#include "Grid.h"
#include "ShadeRecord.h"
#include "Project01Tracer.h"		//Tracer for Project01
#include "WhittedTracer.h"
#include "PathTracer.h"
#include "Orthographic.h"
#include "PinHole.h"
#include "DOFCamera.h"
#include "StereoCamera.h"

#include "Ambient.h"
#include "AmbientWithOccluder.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "SpotLight.h"
#include "SphericalAreaLight.h"
#include "EnvironmentLight.h"
#include "Matte.h"
#include "Phong.h"
#include "Reflective.h"
#include "GlossyReflective.h"
#include "Transparent.h"
#include "Translucent.h"
#include "Emissive.h"
#include "SVMatte.h"
#include "SVReflective.h"
#include "SVTransparent.h"
#include "SVTransparentEta.h"
#include "Image.h"
#include "CubicNoise.h"
#include "PlainTexture.h"
#include "ImageTexture.h"
#include "FBMTexture.h"
#include "TurbulenceTexture.h"
#include "SphericalMapping.h"
#include "LightProbeMapping.h"
#include "RectangularMapping.h"
#include "FunctionMapping.h"
#include "ProjectionMapping.h"
#include "SolidTexMapping.h"

#include "PaintCamera.h"

#include <vector>

class Tracer;
class Camera;
class Phong;
//class ShadeRecord;

using namespace std;

class World
{
	public:
		
		ViewPlane viewPlane;
		std::vector<GeometricObject*> objectsInScene;
		Tracer* tracerPtr;
		RGBColor bgColor;

		unsigned char *pixmap;
		Camera* cameraPtr;

		//Animation
		int frameCount;

		//Animation 01
		Sphere *movingSphere;

		//Animation 01
		float normalizedFrameVal;

		Light *ambientLightPtr;
		std::vector<Light*> lights;

		int reflectionDepth;
				
		//Constructors

		World(void);												//Default Constructor
		
		//Destructor

		~World(void);

		//Member Functions
		World operator= (const World& worldObj);

		void BuildWorldProject01(void);
		void BuildWorldProject02(void);
		void BuildWorldProject03(void);
		void BuildWorldProject04(void);
		void BuildWorldProject05(void);
		void BuildWorldProject06(void);
		void BuildWorldProject08(void);
		void BuildWorldProject08WithNormalMap(void);
		void BuildWorldTest(void);
		void BuildGridTest(void);
		void BuildWorldWithBunny(void);
		void BuildWorldWithTetrahedron(void);
		void BuildWorldWithCube(void);
		void BuildReflectiveBunny(void);
		void BuildReflectiveTetrahedron(void);
		void BuildNormalMapTest(void);
		void BuildWorldEnvironmentMap(void);
		void BuildWorldProject09(void);
		void BuildTransparentBunny(void);
		void BuildTransparentRectangle(void);
		void BuildTransparentRectangleSVEta(void);
		void BuildDOFTest(void);
		void BuildAmbientOcclusionTest(void);
		void BuildAreaLightTest(void);
		void BuildBunnyWithAreaLight(void);
		void BuildGlossyMaterial(void);
		void BuildTranslucentTest(void);
		void BuildEnvironmentLightTest(void);
		void BuildAmbientOcclusionWithSphere(void);
		void BuildCausticTest(void);
		void ConstructFrame(unsigned char* pixMapFromMain);

		void BuildAnimation01(void);
		void RenderAnimation01(unsigned char* pixMapFromMain);
		void BuildAnimation02(void);
		void RenderAnimation02(unsigned char* pixMapFromMain);
		void BuildAnimation03(void);
		void RenderAnimation03(unsigned char* pixMapFromMain);
		void BuildAnimation04(void);
		void RenderAnimation04(unsigned char* pixMapFromMain);
		char* itoa(int Value, int Base);

		void AddObjectToWorld(GeometricObject* objectPtr);
		void AddLightToWorld(Light* lightPtr);
		ShadeRecord MultipleObjectsHitFunction(const Ray& ray);
};


inline void World::AddObjectToWorld(GeometricObject* objectPtr)
{
	objectsInScene.push_back(objectPtr);
	cout << "called\n";
}

#endif
