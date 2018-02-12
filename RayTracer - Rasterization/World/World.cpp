// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 12/30/15.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "World.h"

//Default Constructor
World::World(void) 
{

}


//Destructor
World::~World(void)
{

}

World World::operator= (const World& w)
{
	viewPlane = w.viewPlane;
	objectsInScene = w.objectsInScene;
	tracerPtr = w.tracerPtr;
	bgColor = w.bgColor;

	pixmap = w.pixmap;
	cameraPtr = w.cameraPtr;

	ambientLightPtr = w.ambientLightPtr;
	lights = w.lights;

	return *this;
}

void World::AddLightToWorld(Light* lightPtr)
{
	lights.push_back(lightPtr);
}

//BuildWorld Function
void World::BuildWorldProject01(void)
{
	//ViewPlane
	viewPlane.SetResolution(600, 600, 0.5);
	viewPlane.SetSampler(0, 1);

	//Camera
	cameraPtr = new Orthographic(this);

	//Tracer
	tracerPtr = new Project01Tracer(this);

	//Background Color
	bgColor = white;
	
	//Objects
	Sphere *spherePtr = new Sphere;

	spherePtr->SetCenter(0, 0, 0);
	spherePtr->SetRadius(50);
	spherePtr->SetColor(1,0,0);
	AddObjectToWorld(spherePtr);

	spherePtr = new Sphere;
	spherePtr->SetCenter(50, 100, -90);
	spherePtr->SetRadius(100);
	spherePtr->SetColor(0, 0, 1);
	AddObjectToWorld(spherePtr);

	Plane *planePtr = new Plane;
	planePtr->SetPoint(Point3D(0,0,100));
	planePtr->SetNormal(-0.5,-1,0.1);
	planePtr->SetColor(0,1,0);
	AddObjectToWorld(planePtr);

	Cube* cubePtr = new Cube(Point3D(-20, -110, 0), Point3D(-95, -60, 120));
	cubePtr->SetColor(0, 0.6, 0.5);
	AddObjectToWorld(cubePtr);

	std::cout << "BuildWorldProject01";
}


void World::BuildWorldProject02(void)
{
	//ViewPlane
	viewPlane.SetResolution(800, 450, 0.5);
	viewPlane.SetSampler(1, 16);

	//Camera
	Point3D eyePosition(400, 260, -500);
	Point3D lookAtPosition(80, 40, -60);
	Vector3D upVector(0, 1, 0);
	float viewPlaneDistance = 500;
	float rollAngle = -10; //-25; // Negative sign for clock-wise rotation

	cameraPtr = new PinHole(this, eyePosition, lookAtPosition, upVector, viewPlaneDistance, rollAngle);

	//Tracer
	tracerPtr = new Project01Tracer(this);

	//Background Color
	bgColor = white;

	//Objects

	//Floor Plane
	Plane *planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(0, 1, 0);
	planePtr->SetColor(0.86, 0.86, 0.86);
	AddObjectToWorld(planePtr);

	//Wall one
	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(1, 0, 0);
	planePtr->SetColor(0.99, 0.96, 0.9);
	AddObjectToWorld(planePtr);

	//Wall two
	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(0, 0, 1);
	planePtr->SetColor(1, 0.93, 0.83);
	AddObjectToWorld(planePtr);

	
	Sphere *spherePtr = new Sphere;

	spherePtr->SetCenter(80, 30, -170);
	spherePtr->SetRadius(30);
	spherePtr->SetColor(1, 0.5, 0.31);
	AddObjectToWorld(spherePtr);

	spherePtr = new Sphere;
	spherePtr->SetCenter(40, 40, -90);
	spherePtr->SetRadius(40);
	spherePtr->SetColor(0.25, 0.41, 0.88);
	AddObjectToWorld(spherePtr);

	
	Cube* cubePtr = new Cube(Point3D(80, 0, -120), Point3D(140, 120, -50));
	cubePtr->SetColor(0, 0.6, 0.5);
	AddObjectToWorld(cubePtr);

	
	Quadric *quadricPtr = new Quadric(1, 1, 1, 0, -1);
	quadricPtr->SetCenter(160, 50, -60);
	quadricPtr->SetEyePosAndPCE(eyePosition);
	quadricPtr->SetSParameter(17, 50, 17);
	Vector3D n0 = Vector3D(1, 0, 0);
	Vector3D n1 = Vector3D(0, 0.6, -0.8);
	Vector3D n2 = Vector3D(0, 0.8, 0.6);
	quadricPtr->SetNormalVectors(n0, n1, n2);
	quadricPtr->SetColor(0.54, 0.27, 0.07);
	AddObjectToWorld(quadricPtr);


	std::cout << "BuildWorldProject02";
}

void World::BuildWorldProject03(void)
{
	Matte *mattePtr;
	Sphere *spherePtr;
	Phong *phongPtr;

	//ViewPlane
	viewPlane.SetResolution(600, 450, 0.5);
	viewPlane.SetSampler(1, 16);
	
	//Camera
	Point3D eyePosition(200, 280, -500);
	Point3D lookAtPosition(80, 90, -100);
	Vector3D upVector(0, 1, 0);
	float viewPlaneDistance = 400;
	float rollAngle = 0;// -10; //-25; // Negative sign for clock-wise rotation

	cameraPtr = new PinHole(this, eyePosition, lookAtPosition, upVector, viewPlaneDistance, rollAngle);

	//Tracer
	tracerPtr = new Project01Tracer(this);

	//Background Color
	bgColor = white;

	ambientLightPtr = new Ambient(white, 1);

	//PointLight *pointLight = new PointLight(white, 3, Point3D(160, 200, -200), false);
	//AddLightToWorld(pointLight);

	//DirectionalLight *directionalLight = new DirectionalLight(white, 3, Point3D(100, 200, -100), Vector3D(1,-1,0), false);
	//AddLightToWorld(directionalLight);

	SpotLight *spotLight = new SpotLight(white, 3, Point3D(175, 250, -225), Point3D(0,30,0), false);// Vector3D(0, -1, 0));// Vector3D(-0.577, -0.577, 0.577));
	AddLightToWorld(spotLight);

	//Objects
	/*
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.2, RGBColor(1, 0.5, 0.31));
	mattePtr->SetDiffuseBRDF(0.65, RGBColor(1, 0.5, 0.31));
	
	spherePtr = new Sphere;
	spherePtr->materialPtr = mattePtr;
	spherePtr->SetCenter(80, 30, -170);
	spherePtr->SetRadius(30);
	//spherePtr->SetColor(1, 0.5, 0.31);
	AddObjectToWorld(spherePtr);
	*/

	phongPtr = new Phong(viewPlane.samplerPtr);
	phongPtr->SetAmbientBRDF(0.4, RGBColor(0.9, 0.79, 0.43));
	phongPtr->SetDiffuseBRDF(0.3, RGBColor(0.84, 0.47, 0.29));
	phongPtr->SetSpecularBRDF(0.4, RGBColor(1, 1, 1), 100);
	phongPtr->SetRimColor(RGBColor(0.84, 0.47, 0.29));

	spherePtr = new Sphere;
	spherePtr->materialPtr = phongPtr;
	spherePtr->SetCenter(80, 130, -90);
	spherePtr->SetRadius(30);
	//spherePtr->SetColor(1, 0.5, 0.31);
	AddObjectToWorld(spherePtr);

	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.23, 0.09, 0.09));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.8, 0.53, 0.23));
	
	spherePtr = new Sphere;
	spherePtr->SetCenter(80, 40, -90);
	spherePtr->SetRadius(40);
	spherePtr->materialPtr = mattePtr;
	//spherePtr->SetColor(0.25, 0.41, 0.88);
	AddObjectToWorld(spherePtr);
	

	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	//Floor Plane
	Plane *planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(0, 1, 0);
	planePtr->materialPtr = mattePtr;
	//planePtr->SetColor(0.86, 0.86, 0.86);
	AddObjectToWorld(planePtr);

	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	//Wall one
	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(1, 0, 0);
	planePtr->materialPtr = mattePtr;
	//planePtr->SetColor(0.99, 0.96, 0.9);
	AddObjectToWorld(planePtr);

	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	//Wall two
	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(0, 0, -1);
	planePtr->materialPtr = mattePtr;
	//planePtr->SetColor(1, 0.93, 0.83);
	AddObjectToWorld(planePtr);

	std::cout << "BuildWorldProject03";
}

void World::BuildWorldProject04(void)
{

	Matte *mattePtr;
	Sphere *spherePtr;
	Phong *phongPtr;

	//ViewPlane
	viewPlane.SetResolution(600, 450, 0.5);
	viewPlane.SetSampler(1, 16);

	//Camera
	Point3D eyePosition(120, 280, -500);
	Point3D lookAtPosition(160, 90, -100);
	Vector3D upVector(0, 1, 0);
	float viewPlaneDistance = 500;
	float rollAngle = 0;// -10; //-25; // Negative sign for clock-wise rotation

	cameraPtr = new PinHole(this, eyePosition, lookAtPosition, upVector, viewPlaneDistance, rollAngle);

	//Tracer
	tracerPtr = new WhittedTracer(this);

	//Background Color
	bgColor = white;

	//Objects
	phongPtr = new Phong(viewPlane.samplerPtr);
	phongPtr->SetAmbientBRDF(0.4, RGBColor(0.9, 0.79, 0.43));
	phongPtr->SetDiffuseBRDF(0.3, RGBColor(0.84, 0.47, 0.29));
	phongPtr->SetSpecularBRDF(0.4, RGBColor(1, 1, 1), 100);
	//phongPtr->SetRimColor(RGBColor(0.84, 0.47, 0.29));

	spherePtr = new Sphere;
	spherePtr->materialPtr = phongPtr;
	spherePtr->SetCenter(160, 130, -90);
	spherePtr->SetRadius(30);
	//spherePtr->SetColor(1, 0.5, 0.31);
	AddObjectToWorld(spherePtr);

	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.23, 0.09, 0.09));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.8, 0.53, 0.23));

	spherePtr = new Sphere;
	spherePtr->SetCenter(160, 40, -90);
	spherePtr->SetRadius(40);
	spherePtr->materialPtr = mattePtr;
	//spherePtr->SetColor(0.25, 0.41, 0.88);
	AddObjectToWorld(spherePtr);

	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	//Floor Plane
	Plane *planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(0, 1, 0);
	planePtr->materialPtr = mattePtr;
	//planePtr->SetColor(0.86, 0.86, 0.86);
	AddObjectToWorld(planePtr);

	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	//Wall one
	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(1, 0, 0);
	planePtr->materialPtr = mattePtr;
	//planePtr->SetColor(0.99, 0.96, 0.9);
	AddObjectToWorld(planePtr);

	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	//Wall two
	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(0, 0, -1);
	planePtr->materialPtr = mattePtr;
	//planePtr->SetColor(1, 0.93, 0.83);
	AddObjectToWorld(planePtr);


	ambientLightPtr = new Ambient(white, 1);

	
	PointLight *pointLight = new PointLight(white, 3, Point3D(80, 200, -200), true);
	AddLightToWorld(pointLight);

	//SpotLight *spotLight = new SpotLight(white, 3, Point3D(175, 250, -225), Point3D(0,30,0), true);// Vector3D(0, -1, 0));// Vector3D(-0.577, -0.577, 0.577));
	//AddLightToWorld(spotLight);

	//DirectionalLight *directionalLight = new DirectionalLight(white, 3, Point3D(900, 200, -100), Vector3D(-1,-1,0), true);
	//AddLightToWorld(directionalLight);

	std::cout << "\nBuildWorldProject04\n";
}

void World::BuildWorldProject05(void)
{
	Sphere *spherePtr;
	Plane *planePtr;
	Rectangle *rectanglePtr;

	Matte *mattePtr;
	Phong *phongPtr;

	SVMatte *svMattePtr;

	Image *imagePtr;
	Texture *texturePtr;
	Mapping *mappingPtr;

	//ViewPlane
	viewPlane.SetResolution(600, 450, 0.5);
	viewPlane.SetSampler(1, 16);

	//Camera
	Point3D eyePosition(120, 280, -500);
	Point3D lookAtPosition(160, 90, -100);
	Vector3D upVector(0, 1, 0);
	float viewPlaneDistance = 500;
	float rollAngle = 0;// -10; //-25; // Negative sign for clock-wise rotation

	cameraPtr = new PinHole(this, eyePosition, lookAtPosition, upVector, viewPlaneDistance, rollAngle);

	//Tracer
	tracerPtr = new WhittedTracer(this);

	//Background Color
	bgColor = white;

	//Objects
	imagePtr = new Image();
	imagePtr->ReadPPMFile("EarthLowRes.ppm");
	//imagePtr->ReadPPMFile("cube.ppm");

	mappingPtr = new SphericalMapping();
	//mappingPtr = new FunctionMapping();

	//texturePtr = new PlainTexture(RGBColor(0.8, 0.53, 0.23));
	texturePtr = new ImageTexture(imagePtr, mappingPtr);

	svMattePtr = new SVMatte(viewPlane.samplerPtr);
	svMattePtr->SetAmbientBRDF(0.4, texturePtr);
	svMattePtr->SetDiffuseBRDF(0.6, texturePtr);

	spherePtr = new Sphere;
	spherePtr->SetCenter(160, 40, -90);
	spherePtr->SetRadius(40);
	spherePtr->materialPtr = svMattePtr;
	//spherePtr->SetColor(0.25, 0.41, 0.88);
	AddObjectToWorld(spherePtr);

	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.1, 0.1, 0.1));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.46));

	//Floor Plane
	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(0, 1, 0);
	planePtr->materialPtr = mattePtr;
	//planePtr->SetColor(0.86, 0.86, 0.86);
	AddObjectToWorld(planePtr);

	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	//Wall one
	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(1, 0, 0);
	planePtr->materialPtr = mattePtr;
	//planePtr->SetColor(0.99, 0.96, 0.9);
	AddObjectToWorld(planePtr);

	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	//Wall two
	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(0, 0, -1);
	planePtr->materialPtr = mattePtr;
	//planePtr->SetColor(1, 0.93, 0.83);
	AddObjectToWorld(planePtr);

	imagePtr = new Image();
	imagePtr->ReadPPMFile("CountryScene.ppm");

	mappingPtr = new RectangularMapping();
	texturePtr = new ImageTexture(imagePtr, mappingPtr);

	svMattePtr = new SVMatte(viewPlane.samplerPtr);
	svMattePtr->SetAmbientBRDF(0.4, texturePtr);
	svMattePtr->SetDiffuseBRDF(0.6, texturePtr);

	rectanglePtr = new Rectangle(Point3D(190,60,-4), Vector3D(-130,0,0), Vector3D(0,70,0));
	rectanglePtr->materialPtr = svMattePtr;
	AddObjectToWorld(rectanglePtr);

	ambientLightPtr = new Ambient(white, 1);

	PointLight *pointLight = new PointLight(white, 3, Point3D(80, 200, -200), true);
	AddLightToWorld(pointLight);

	//SpotLight *spotLight = new SpotLight(white, 3, Point3D(175, 250, -225), Point3D(0,30,0), true);// Vector3D(0, -1, 0));// Vector3D(-0.577, -0.577, 0.577));
	//AddLightToWorld(spotLight);

	//DirectionalLight *directionalLight = new DirectionalLight(white, 3, Point3D(900, 200, -100), Vector3D(-1,-1,0), true);
	//AddLightToWorld(directionalLight);

	std::cout << "\nBuildWorldProject05\n";
}

void World::BuildWorldProject06(void)
{
	cout << "InvRandMax: " << inverseRandMax << "\n";

	Sphere *spherePtr;
	Plane *planePtr;
	Rectangle *rectanglePtr;

	Matte *mattePtr;
	Phong *phongPtr;

	SVMatte *svMattePtr;

	Image *imagePtr;
	Texture *texturePtr;
	Mapping *mappingPtr;
	LatticeNoise* noisePtr;

	//ViewPlane
	viewPlane.SetResolution(600, 450, 0.5);
	viewPlane.SetSampler(1, 16);

	//Camera
	Point3D eyePosition(120, 280, -500);
	//Point3D lookAtPosition(160, 90, -100);
	Point3D lookAtPosition(200, 40, 0);
	Vector3D upVector(0, 1, 0);
	float viewPlaneDistance = 500;
	float rollAngle = 0;// -10; //-25; // Negative sign for clock-wise rotation

	cameraPtr = new PinHole(this, eyePosition, lookAtPosition, upVector, viewPlaneDistance, rollAngle);

	//Tracer
	tracerPtr = new Project01Tracer(this);

	//Background Color
	bgColor = white;

	//Objects
	noisePtr = new CubicNoise();
	noisePtr->SetGainLacunarity(0.5, 8);
	noisePtr->SetNumberOfOctaves(6);
	
	
	FBMTexture *fbmTexturePtr = new FBMTexture(noisePtr);
	fbmTexturePtr->SetColor(RGBColor(0.85,0.9,0.34));
	fbmTexturePtr->SetMinMaxValues(-0.1, 1.1);
	
	texturePtr = fbmTexturePtr;
	
	
	/*
	TurbulenceTexture *turbTexturePtr = new TurbulenceTexture(noisePtr);
	turbTexturePtr->SetColor(red);
	turbTexturePtr->SetMinMaxValues(0, 1);

	texturePtr = turbTexturePtr;
	*/

	svMattePtr = new SVMatte(viewPlane.samplerPtr);
	svMattePtr->SetAmbientBRDF(0.4, texturePtr);
	svMattePtr->SetDiffuseBRDF(0.6, texturePtr);

	spherePtr = new Sphere;
	spherePtr->SetCenter(160, 40, -90);
	spherePtr->SetRadius(40);
	spherePtr->materialPtr = svMattePtr;
	//spherePtr->SetColor(0.25, 0.41, 0.88);
	AddObjectToWorld(spherePtr);

	imagePtr = new Image();
	imagePtr->ReadPPMFile("CountryScene.ppm");

	mappingPtr = new SolidTexMapping();

	texturePtr = new ImageTexture(imagePtr, mappingPtr);

	svMattePtr = new SVMatte(viewPlane.samplerPtr);
	svMattePtr->SetAmbientBRDF(0.4, texturePtr);
	svMattePtr->SetDiffuseBRDF(0.6, texturePtr);

	spherePtr = new Sphere;
	spherePtr->SetCenter(260, 40, -90);
	spherePtr->SetRadius(40);
	spherePtr->materialPtr = svMattePtr;
	//spherePtr->SetColor(0.25, 0.41, 0.88);
	//AddObjectToWorld(spherePtr);

	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.1, 0.1, 0.1));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.46));

	//Floor Plane
	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(0, 1, 0);
	planePtr->materialPtr = mattePtr;
	//planePtr->SetColor(0.86, 0.86, 0.86);
	AddObjectToWorld(planePtr);

	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	//Wall one
	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(1, 0, 0);
	planePtr->materialPtr = mattePtr;
	//planePtr->SetColor(0.99, 0.96, 0.9);
	AddObjectToWorld(planePtr);

	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	//Wall two

	imagePtr = new Image();
	imagePtr->ReadPPMFile("CountryScene.ppm");

	mappingPtr = new ProjectionMapping();
	texturePtr = new ImageTexture(imagePtr, mappingPtr);

	svMattePtr = new SVMatte(viewPlane.samplerPtr);
	svMattePtr->SetAmbientBRDF(0.4, texturePtr);
	svMattePtr->SetDiffuseBRDF(0.6, texturePtr);

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(0, 0, -1);
	planePtr->materialPtr = svMattePtr;
	//planePtr->SetColor(1, 0.93, 0.83);
	AddObjectToWorld(planePtr);

	imagePtr = new Image();
	imagePtr->ReadPPMFile("CountryScene.ppm");

	mappingPtr = new RectangularMapping();
	texturePtr = new ImageTexture(imagePtr, mappingPtr);

	svMattePtr = new SVMatte(viewPlane.samplerPtr);
	svMattePtr->SetAmbientBRDF(0.4, texturePtr);
	svMattePtr->SetDiffuseBRDF(0.6, texturePtr);

	rectanglePtr = new Rectangle(Point3D(190, 60, -4), Vector3D(-130, 0, 0), Vector3D(0, 70, 0));
	rectanglePtr->materialPtr = svMattePtr;
	//AddObjectToWorld(rectanglePtr);

	ambientLightPtr = new Ambient(white, 1);

	PointLight *pointLight = new PointLight(white, 3, Point3D(80, 200, -200), true);
	AddLightToWorld(pointLight);

	//SpotLight *spotLight = new SpotLight(white, 3, Point3D(175, 250, -225), Point3D(0,30,0), true);// Vector3D(0, -1, 0));// Vector3D(-0.577, -0.577, 0.577));
	//AddLightToWorld(spotLight);

	//DirectionalLight *directionalLight = new DirectionalLight(white, 3, Point3D(900, 200, -100), Vector3D(-1,-1,0), true);
	//AddLightToWorld(directionalLight);

	std::cout << "\nBuildWorldTest\n";
}

void World::BuildWorldTest(void)
{
	cout << "InvRandMax: " << inverseRandMax << "\n";

	Sphere *spherePtr;
	Plane *planePtr;
	Rectangle *rectanglePtr;

	Matte *mattePtr;
	Phong *phongPtr;

	SVMatte *svMattePtr;

	Image *imagePtr;
	Texture *texturePtr;
	Mapping *mappingPtr;
	LatticeNoise* noisePtr;

	//ViewPlane
	viewPlane.SetResolution(600, 450, 0.5);
	viewPlane.SetSampler(1, 4);

	//Camera
	Point3D eyePosition(120, 280, -500);
	//Point3D lookAtPosition(160, 90, -100);
	Point3D lookAtPosition(50, 40, 0);
	Vector3D upVector(0, 1, 0);
	float viewPlaneDistance = 500;
	float rollAngle = 0;// -10; //-25; // Negative sign for clock-wise rotation

	cameraPtr = new PinHole(this, eyePosition, lookAtPosition, upVector, viewPlaneDistance, rollAngle);

	//Tracer
	tracerPtr = new Project01Tracer(this);

	//Background Color
	bgColor = white;

	//Objects
	noisePtr = new CubicNoise();
	noisePtr->SetGainLacunarity(0.5, 8);
	noisePtr->SetNumberOfOctaves(6);


	FBMTexture *fbmTexturePtr = new FBMTexture(noisePtr);
	fbmTexturePtr->SetColor(RGBColor(0.85, 0.9, 0.34));
	fbmTexturePtr->SetMinMaxValues(-0.1, 1.1);

	texturePtr = fbmTexturePtr;

	svMattePtr = new SVMatte(viewPlane.samplerPtr);
	svMattePtr->SetAmbientBRDF(0.4, texturePtr);
	svMattePtr->SetDiffuseBRDF(0.6, texturePtr);

	spherePtr = new Sphere;
	spherePtr->SetCenter(160, 40, -90);
	spherePtr->SetRadius(40);
	spherePtr->materialPtr = svMattePtr;
	//spherePtr->SetColor(0.25, 0.41, 0.88);
	//AddObjectToWorld(spherePtr);

	imagePtr = new Image();
	imagePtr->ReadPPMFile("CountryScene.ppm");

	mappingPtr = new SolidTexMapping();

	texturePtr = new ImageTexture(imagePtr, mappingPtr);

	svMattePtr = new SVMatte(viewPlane.samplerPtr);
	svMattePtr->SetAmbientBRDF(0.4, texturePtr);
	svMattePtr->SetDiffuseBRDF(0.6, texturePtr);

	spherePtr = new Sphere;
	spherePtr->SetCenter(260, 40, -90);
	spherePtr->SetRadius(40);
	spherePtr->materialPtr = svMattePtr;
	//spherePtr->SetColor(0.25, 0.41, 0.88);
	//AddObjectToWorld(spherePtr);

	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.23, 0.09, 0.09));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.8, 0.53, 0.23));

	Cube* cubePtr = new Cube(Point3D(10, 0, -120), Point3D(100, 60, 0));
	cubePtr->materialPtr = mattePtr;
	AddObjectToWorld(cubePtr);

	// yellow triangle

	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.25, RGBColor(1, 1, 0));
	mattePtr->SetDiffuseBRDF(0.75, RGBColor(1, 1, 0));
	

	Triangle* triangle = new Triangle(Point3D(80, 65, -110), Point3D(50, 100, -130), Point3D(70, 100, -60));
	triangle->materialPtr = mattePtr;
	AddObjectToWorld(triangle);

	// dark green triangle

	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.25, RGBColor(0.0, 0.5, 0.41));
	mattePtr->SetDiffuseBRDF(0.75, RGBColor(0.0, 0.5, 0.41));

	triangle = new Triangle(Point3D(80, 100, -130), Point3D(50, 65, -115), Point3D(30, 80, -50));
	triangle->materialPtr = mattePtr;
	AddObjectToWorld(triangle);

	//Compound Object - Cylinder

	CompoundObject *compoundObject = new CompoundObject();

	// Red disk

	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.25, RGBColor(1.0, 0.0, 0.0));
	mattePtr->SetDiffuseBRDF(0.75, RGBColor(1.0, 0.0, 0.0));

	Vector3D tempNormal = Vector3D(0, 1, 0);// .UnitVector();
	Disk *disk= new Disk(Point3D(0, 140, 0), 30, tempNormal);
	disk->materialPtr = mattePtr;
	compoundObject->AddObject(disk);
	//AddObjectToWorld(disk);

	// OpenCylinder
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.25, RGBColor(1.0, 1.0, 0.5));
	mattePtr->SetDiffuseBRDF(0.75, RGBColor(1.0, 1.0, 0.5));

	OpenCylinder *openCylinder = new OpenCylinder(30, 80, 140);
	openCylinder->materialPtr = mattePtr;
	compoundObject->AddObject(openCylinder);
	//AddObjectToWorld(openCylinder);
	compoundObject->SetMaterial(mattePtr);
	AddObjectToWorld(compoundObject);

	//Floor Plane
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.1, 0.1, 0.1));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.46));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(0, 1, 0);
	planePtr->materialPtr = mattePtr;
	//planePtr->SetColor(0.86, 0.86, 0.86);
	AddObjectToWorld(planePtr);


	//Wall one
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(1, 0, 0);
	planePtr->materialPtr = mattePtr;
	//planePtr->SetColor(0.99, 0.96, 0.9);
	AddObjectToWorld(planePtr);

	//Wall two
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	imagePtr = new Image();
	imagePtr->ReadPPMFile("CountryScene.ppm");

	mappingPtr = new ProjectionMapping();
	texturePtr = new ImageTexture(imagePtr, mappingPtr);

	svMattePtr = new SVMatte(viewPlane.samplerPtr);
	svMattePtr->SetAmbientBRDF(0.4, texturePtr);
	svMattePtr->SetDiffuseBRDF(0.6, texturePtr);

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(0, 0, -1);
	planePtr->materialPtr = svMattePtr;
	//planePtr->SetColor(1, 0.93, 0.83);
	AddObjectToWorld(planePtr);

	imagePtr = new Image();
	imagePtr->ReadPPMFile("CountryScene.ppm");

	mappingPtr = new RectangularMapping();
	texturePtr = new ImageTexture(imagePtr, mappingPtr);

	svMattePtr = new SVMatte(viewPlane.samplerPtr);
	svMattePtr->SetAmbientBRDF(0.4, texturePtr);
	svMattePtr->SetDiffuseBRDF(0.6, texturePtr);

	rectanglePtr = new Rectangle(Point3D(190, 60, -4), Vector3D(-130, 0, 0), Vector3D(0, 70, 0));
	rectanglePtr->materialPtr = svMattePtr;
	//AddObjectToWorld(rectanglePtr);

	ambientLightPtr = new Ambient(white, 1);

	PointLight *pointLight = new PointLight(white, 3, Point3D(80, 200, -200), true);
	AddLightToWorld(pointLight);

	//SpotLight *spotLight = new SpotLight(white, 3, Point3D(175, 250, -225), Point3D(0,30,0), true);// Vector3D(0, -1, 0));// Vector3D(-0.577, -0.577, 0.577));
	//AddLightToWorld(spotLight);

	//DirectionalLight *directionalLight = new DirectionalLight(white, 3, Point3D(900, 200, -100), Vector3D(-1,-1,0), true);
	//AddLightToWorld(directionalLight);

	std::cout << "\nBuildWorldTest\n";
}

void World::BuildGridTest(void)
{

	Sphere *spherePtr;

	Matte *mattePtr;

	//ViewPlane
	viewPlane.SetResolution(400, 400, 1);
	viewPlane.SetSampler(1, 4);

	//Camera
	Point3D eyePosition(10, 15, 30);
	//Point3D lookAtPosition(160, 90, -100);
	Point3D lookAtPosition(0, 0, 0);
	Vector3D upVector(0, 1, 0);
	float viewPlaneDistance = 4600;
	float rollAngle = 0;// -10; //-25; // Negative sign for clock-wise rotation

	cameraPtr = new PinHole(this, eyePosition, lookAtPosition, upVector, viewPlaneDistance, rollAngle);

	//Tracer
	tracerPtr = new Project01Tracer(this);

	//Background Color
	bgColor = black;

	int num_spheres = 1000;		

	float volume = 0.1 / num_spheres;
	float radius = pow(0.75 * volume / 3.14159, 0.333333);

	srand(15);

	Grid *grid = new Grid;

	//Objects

	for (int j = 0; j < num_spheres; j++)
	{
		mattePtr = new Matte(viewPlane.samplerPtr);
		mattePtr->SetAmbientBRDF(0.4, RGBColor((float)rand()* inverseRandMax, (float)rand()* inverseRandMax, (float)rand()* inverseRandMax));
		mattePtr->SetDiffuseBRDF(0.6, RGBColor((float)rand()* inverseRandMax, (float)rand()* inverseRandMax, (float)rand()* inverseRandMax));

		spherePtr = new Sphere();
		spherePtr->SetCenter(1 - 2 * ((float)rand()* inverseRandMax), 1 - 2 * ((float)rand()* inverseRandMax), 1 - 2 * ((float)rand()* inverseRandMax));
		spherePtr->SetRadius(radius);
		spherePtr->SetBoundingBox();
		spherePtr->materialPtr = mattePtr;
		grid->AddObject(spherePtr);
	}

	grid->ConstructCells();
	AddObjectToWorld(grid);
	
	ambientLightPtr = new Ambient(white, 1);

	//PointLight *pointLight = new PointLight(white, 3, Point3D(80, 200, -200), true);
	//AddLightToWorld(pointLight);

	//SpotLight *spotLight = new SpotLight(white, 3, Point3D(175, 250, -225), Point3D(0,30,0), true);// Vector3D(0, -1, 0));// Vector3D(-0.577, -0.577, 0.577));
	//AddLightToWorld(spotLight);

	DirectionalLight *directionalLight = new DirectionalLight(white, 3, Point3D(900, 200, -100), Vector3D(-1,-1,0), true);
	AddLightToWorld(directionalLight);

	std::cout << "\nBuildGridTest\n";
}

void World::BuildWorldWithBunny(void)
{

	Sphere *spherePtr;

	Matte *mattePtr;

	//ViewPlane
	viewPlane.SetResolution(600, 600, 0.5);
	viewPlane.SetSampler(1, 16);

	//Camera
	Point3D eyePosition(0, 1.2, 0.7);
	//Point3D lookAtPosition(160, 90, -100);
	Point3D lookAtPosition(0, 0.03, 0);
	Vector3D upVector(0, 1, 0.25);
	float viewPlaneDistance = 1200;
	float rollAngle = 0;// -10; //-25; // Negative sign for clock-wise rotation

	cameraPtr = new PinHole(this, eyePosition, lookAtPosition, upVector, viewPlaneDistance, rollAngle);

	//Tracer
	tracerPtr = new Project01Tracer(this);

	//Background Color
	bgColor = black;

	//Objects

	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0, 0.2, 0.5));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0, 0.5, 1));

	Grid *grid = new Grid;
	grid->ReadFlatTriangles("bun_zipper.ply");
	//grid->ReadFlatTriangles("dragonStandRight_48");
	//grid->ReadFlatTriangles("TwoTriangles.ply");
	//grid->ReadFlatTriangles("pyramid.ply");
	grid->SetMaterial(mattePtr);
	grid->ConstructCells();
	AddObjectToWorld(grid);

	//Plane
	//Floor Plane
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.1, 0.1, 0.1));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.46));

	Plane *planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0.03, 0));
	planePtr->SetNormal(0, 1, 0);
	planePtr->materialPtr = mattePtr;
	//planePtr->SetColor(0.86, 0.86, 0.86);
	AddObjectToWorld(planePtr);


	//Wall one
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0.1, 0, 0));
	planePtr->SetNormal(-1, 0, 0);
	planePtr->materialPtr = mattePtr;
	//planePtr->SetColor(0.99, 0.96, 0.9);
	AddObjectToWorld(planePtr);

	//Wall two
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, -0.06));
	planePtr->SetNormal(0, 0, 1);
	planePtr->materialPtr = mattePtr;
	//planePtr->SetColor(1, 0.93, 0.83);
	AddObjectToWorld(planePtr);

	ambientLightPtr = new Ambient(white, 1);

	PointLight *pointLight = new PointLight(white, 3, Point3D(-1, 5, 0.6), true);
	AddLightToWorld(pointLight);

	//SpotLight *spotLight = new SpotLight(white, 3, Point3D(175, 250, -225), Point3D(0,30,0), true);// Vector3D(0, -1, 0));// Vector3D(-0.577, -0.577, 0.577));
	//AddLightToWorld(spotLight);

	//DirectionalLight *directionalLight = new DirectionalLight(white, 3, Point3D(900, 200, -100), Vector3D(-0.75, -1, +0.15), true);
	//AddLightToWorld(directionalLight);

	std::cout << "\nBuildGridTest\n";
}

void World::BuildWorldWithTetrahedron(void)
{
	Sphere *spherePtr;

	Matte *mattePtr;

	//ViewPlane
	viewPlane.SetResolution(600, 600, 0.5);
	viewPlane.SetSampler(1, 16);

	//Camera
	Point3D eyePosition(100, 50, 30);
	//Point3D lookAtPosition(160, 90, -100);
	Point3D lookAtPosition(0, 5, 8);
	Vector3D upVector(0, 1, 0.25);
	float viewPlaneDistance = 1000;
	float rollAngle = 0;// -10; //-25; // Negative sign for clock-wise rotation

	cameraPtr = new PinHole(this, eyePosition, lookAtPosition, upVector, viewPlaneDistance, rollAngle);

	//Tracer
	tracerPtr = new Project01Tracer(this);

	//Background Color
	bgColor = black;

	//Objects

	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.1, 0.5, 1));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.1, 0.5, 1));

	Grid *grid = new Grid;
	//grid->ReadFlatTriangles("bun_zipper.ply");
	grid->ReadFlatTriangles("pyramid.ply");
	//grid->ReadFlatTriangles("TwoTriangles.ply");
	//grid->ReadFlatTriangles("pyramid.ply");
	grid->SetMaterial(mattePtr);
	grid->ConstructCells();
	AddObjectToWorld(grid);

	//Plane
	//Floor Plane
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.1, 0.1, 0.1));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.46));

	Plane *planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 5, 0));
	planePtr->SetNormal(0, 1, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Wall one
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0.1, 0, 0));
	planePtr->SetNormal(1, 0, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Wall two
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, -0.06));
	planePtr->SetNormal(0, 0, 1);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	ambientLightPtr = new Ambient(white, 1);

	PointLight *pointLight = new PointLight(white, 3, Point3D(80, 70, 30), true);
	AddLightToWorld(pointLight);

	//SpotLight *spotLight = new SpotLight(white, 3, Point3D(175, 250, -225), Point3D(0,30,0), true);// Vector3D(0, -1, 0));// Vector3D(-0.577, -0.577, 0.577));
	//AddLightToWorld(spotLight);

	//DirectionalLight *directionalLight = new DirectionalLight(white, 3, Point3D(900, 200, -100), Vector3D(-0.75, -1, +0.15), true);
	//AddLightToWorld(directionalLight);

	std::cout << "\nBuildGridTest\n";
}

void World::BuildWorldWithCube(void)
{
	Sphere *spherePtr;

	Matte *mattePtr;

	//ViewPlane
	viewPlane.SetResolution(600, 600, 0.5);
	viewPlane.SetSampler(1, 1);

	//Camera
	Point3D eyePosition(5, 5, 5);
	//Point3D lookAtPosition(160, 90, -100);
	Point3D lookAtPosition(0, 0, 0);
	Vector3D upVector(0, 1, 0.25);
	float viewPlaneDistance = 1000;
	float rollAngle = 0;// -10; //-25; // Negative sign for clock-wise rotation

	cameraPtr = new PinHole(this, eyePosition, lookAtPosition, upVector, viewPlaneDistance, rollAngle);

	//Tracer
	tracerPtr = new Project01Tracer(this);

	//Background Color
	bgColor = black;

	//Objects

	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.7, 0.3, 0));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(1, 1, 0));

	Grid *grid = new Grid;
	//grid->ReadFlatTriangles("bun_zipper.ply");
	grid->ReadFlatTriangles("Cube.ply");
	//grid->ReadFlatTriangles("TwoTriangles.ply");
	//grid->ReadFlatTriangles("pyramid.ply");
	grid->SetMaterial(mattePtr);
	grid->ConstructCells();
	AddObjectToWorld(grid);

	//Plane
	//Floor Plane
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.1, 0.1, 0.1));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.46));

	Plane *planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, -2, 0));
	planePtr->SetNormal(0, 1, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);


	//Wall one
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(-2, 0, 0));
	planePtr->SetNormal(1, 0, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Wall two
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, -2));
	planePtr->SetNormal(0, 0, 1);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	ambientLightPtr = new Ambient(white, 1);

	PointLight *pointLight = new PointLight(white, 3, Point3D(8, 10, 5), true);
	AddLightToWorld(pointLight);

	//SpotLight *spotLight = new SpotLight(white, 3, Point3D(175, 250, -225), Point3D(0,30,0), true);// Vector3D(0, -1, 0));// Vector3D(-0.577, -0.577, 0.577));
	//AddLightToWorld(spotLight);

	//DirectionalLight *directionalLight = new DirectionalLight(white, 3, Point3D(900, 200, -100), Vector3D(-0.75, -1, +0.15), true);
	//AddLightToWorld(directionalLight);

	std::cout << "\nBuildGridTest\n";
}

void World::BuildWorldProject08(void)
{
	Sphere *spherePtr;
	Plane *planePtr;
	Rectangle *rectanglePtr;

	Matte *mattePtr;
	Phong *phongPtr;
	Reflective *reflectivePtr;

	SVMatte *svMattePtr;

	Image *imagePtr;
	Texture *texturePtr;
	Mapping *mappingPtr;
	LatticeNoise* noisePtr;

	Grid* grid = new Grid();

	//ViewPlane
	viewPlane.SetResolution(600, 600, 0.5);
	viewPlane.SetSampler(1, 1);

	//Camera
	Point3D eyePosition(120, 280, -500);
	//Point3D lookAtPosition(160, 90, -100);
	Point3D lookAtPosition(50, 40, 0);
	Vector3D upVector(0, 1, 0);
	float viewPlaneDistance = 500;
	float rollAngle = 0;// -10; //-25; // Negative sign for clock-wise rotation

	cameraPtr = new PinHole(this, eyePosition, lookAtPosition, upVector, viewPlaneDistance, rollAngle);

	//Tracer
	tracerPtr = new WhittedTracer(this);
	//tracerPtr = new Project01Tracer(this);
	reflectionDepth = 5;

	//Background Color
	bgColor = white;

	//Objects

	imagePtr = new Image();
	imagePtr->ReadPPMFile("uffizi.ppm");

	mappingPtr = new LightProbeMapping();

	texturePtr = new ImageTexture(imagePtr, mappingPtr);

	svMattePtr = new SVMatte(viewPlane.samplerPtr);
	svMattePtr->SetAmbientBRDF(0.4, texturePtr);
	svMattePtr->SetDiffuseBRDF(0.6, texturePtr);

	spherePtr = new Sphere;
	spherePtr->SetCenter(50, 130, -90);
	spherePtr->SetRadius(40);
	spherePtr->materialPtr = svMattePtr;
	spherePtr->SetBoundingBox();
	grid->AddObject(spherePtr);

	reflectivePtr = new Reflective(viewPlane.samplerPtr);
	reflectivePtr->SetAmbientBRDF(0, RGBColor(1, 0.09, 0.09));
	reflectivePtr->SetDiffuseBRDF(0, RGBColor(0, 1, 0.23));
	reflectivePtr->SetSpecularBRDF(0, RGBColor(1, 1, 1), 10000);
	reflectivePtr->SetPerfectSpecularBRDF(1, RGBColor(1.0,1.0,1.0));

	Cube* cubePtr = new Cube(Point3D(20, 20, -10), Point3D(400, 180, 0));
	cubePtr->materialPtr = reflectivePtr;
	AddObjectToWorld(cubePtr);

	//Sphere
	noisePtr = new CubicNoise();
	noisePtr->SetGainLacunarity(0.5, 8);
	noisePtr->SetNumberOfOctaves(6);

	FBMTexture *fbmTexturePtr = new FBMTexture(noisePtr);
	fbmTexturePtr->SetColor(RGBColor(0.85, 0.9, 0.34));
	fbmTexturePtr->SetMinMaxValues(-0.1, 1.1);

	texturePtr = fbmTexturePtr;

	svMattePtr = new SVMatte(viewPlane.samplerPtr);
	svMattePtr->SetAmbientBRDF(0.4, texturePtr);
	svMattePtr->SetDiffuseBRDF(0.6, texturePtr);

	spherePtr = new Sphere;
	spherePtr->SetCenter(160, 40, -90);
	spherePtr->SetRadius(40);
	spherePtr->materialPtr = svMattePtr;
	spherePtr->SetBoundingBox();
	//AddObjectToWorld(spherePtr);
	grid->AddObject(spherePtr);

	//Reflective Sphere
	reflectivePtr = new Reflective(viewPlane.samplerPtr);
	reflectivePtr->SetAmbientBRDF(0, RGBColor(0, 0.09, 0.9));
	reflectivePtr->SetDiffuseBRDF(0, RGBColor(0.1, 0.2, 1));
	reflectivePtr->SetSpecularBRDF(0, RGBColor(1, 1, 1), 10000);
	reflectivePtr->SetPerfectSpecularBRDF(1, RGBColor(1.0, 1.0, 1.0));

	spherePtr = new Sphere;
	spherePtr->SetCenter(80, 40, -90);
	spherePtr->SetRadius(40);
	spherePtr->materialPtr = reflectivePtr;
	spherePtr->SetBoundingBox();
	//AddObjectToWorld(spherePtr);
	grid->AddObject(spherePtr);

	//Phong Cube

	phongPtr = new Phong(viewPlane.samplerPtr);
	phongPtr->SetAmbientBRDF(0.2, RGBColor(0, 0.79, 0.8));
	phongPtr->SetDiffuseBRDF(0.6, RGBColor(0, 0.47, 1));
	phongPtr->SetSpecularBRDF(0.4, RGBColor(1, 1, 1), 100);

	cubePtr = new Cube(Point3D(20, 20, -400), Point3D(60, 80, -250));
	cubePtr->materialPtr = phongPtr;
	AddObjectToWorld(cubePtr);

	//Compound Object - Cylinder

	CompoundObject *compoundObject = new CompoundObject();

	// OpenCylinder
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.25, RGBColor(1.0, 1.0, 0.5));
	mattePtr->SetDiffuseBRDF(0.75, RGBColor(1.0, 1.0, 0.5));

	OpenCylinder *openCylinder = new OpenCylinder(30, 80, 140);
	openCylinder->materialPtr = mattePtr;
	compoundObject->AddObject(openCylinder);
	AddObjectToWorld(openCylinder);

	//Floor Plane
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.1, 0.1, 0.1));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.46));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(0, 1, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Ceiling Plane
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.1, 0.1, 0.1));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.46));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 300, 0));
	planePtr->SetNormal(0, -1, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Wall one
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(1, 0, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Wall two
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(0, 0, -1);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Wall three
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, -700));
	planePtr->SetNormal(0, 0, 1);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Wall four
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(400, 0, 0));
	planePtr->SetNormal(-1, 0, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	grid->ConstructCells();
	AddObjectToWorld(grid);

	ambientLightPtr = new Ambient(white, 1);

	PointLight *pointLight = new PointLight(white, 3, Point3D(80, 200, -200), true);
	AddLightToWorld(pointLight);

	//SpotLight *spotLight = new SpotLight(white, 3, Point3D(175, 250, -225), Point3D(0,30,0), true);// Vector3D(0, -1, 0));// Vector3D(-0.577, -0.577, 0.577));
	//AddLightToWorld(spotLight);

	//DirectionalLight *directionalLight = new DirectionalLight(white, 3, Point3D(900, 200, -100), Vector3D(-1,-1,0), true);
	//AddLightToWorld(directionalLight);

	std::cout << "\nBuildWorldTest\n";
}

void World::BuildWorldProject08WithNormalMap(void)
{
	Sphere *spherePtr;
	Plane *planePtr;
	Rectangle *rectanglePtr;

	Matte *mattePtr;
	Phong *phongPtr;
	Reflective *reflectivePtr;

	SVMatte *svMattePtr;
	SVReflective *svReflectivePtr;

	Image *imagePtr;
	Texture *texturePtr;
	Mapping *mappingPtr;
	LatticeNoise* noisePtr;

	Grid* grid = new Grid();

	//ViewPlane
	viewPlane.SetResolution(600, 600, 0.5);
	viewPlane.SetSampler(1, 16);

	//Camera
	Point3D eyePosition(120, 280, -500);
	//Point3D lookAtPosition(160, 90, -100);
	Point3D lookAtPosition(50, 40, 0);
	Vector3D upVector(0, 1, 0);
	float viewPlaneDistance = 500;
	float rollAngle = 0;// -10; //-25; // Negative sign for clock-wise rotation

	cameraPtr = new PinHole(this, eyePosition, lookAtPosition, upVector, viewPlaneDistance, rollAngle);

	//Tracer
	tracerPtr = new WhittedTracer(this);
	//tracerPtr = new Project01Tracer(this);
	reflectionDepth = 5;

	//Background Color
	bgColor = white;

	//Objects

	/*
	imagePtr = new Image();
	imagePtr->ReadPPMFile("uffizi.ppm");

	mappingPtr = new LightProbeMapping();

	texturePtr = new ImageTexture(imagePtr, mappingPtr);

	svMattePtr = new SVMatte(viewPlane.samplerPtr);
	svMattePtr->SetAmbientBRDF(0.4, texturePtr);
	svMattePtr->SetDiffuseBRDF(0.6, texturePtr);

	spherePtr = new Sphere;
	spherePtr->SetCenter(50, 130, -90);
	spherePtr->SetRadius(40);
	spherePtr->materialPtr = svMattePtr;
	spherePtr->SetBoundingBox();
	grid->AddObject(spherePtr);
	*/

	//Reflective Sphere
	imagePtr = new Image();
	imagePtr->ReadPPMFile("GreenAndYellow.ppm");

	mappingPtr = new SphericalMapping();

	texturePtr = new ImageTexture(imagePtr, mappingPtr);

	Image *normalMapPtr = new Image();
	normalMapPtr->ReadPPMFile("BricksNormal.ppm");
	//normalMapPtr->ReadPPMFile("CheckerNormal.ppm");

	Texture *normalMapTexPtr = new ImageTexture(normalMapPtr, mappingPtr);

	svReflectivePtr = new SVReflective(viewPlane.samplerPtr);
	svReflectivePtr->SetAmbientBRDF(0, texturePtr);
	svReflectivePtr->SetDiffuseBRDF(0, texturePtr);
	svReflectivePtr->SetSpecularBRDF(0, RGBColor(1, 1, 1), 10000);
	svReflectivePtr->SetPerfectSpecularBRDF(1, RGBColor(1.0, 1.0, 1.0));
	svReflectivePtr->SetNormalMap(normalMapTexPtr);

	spherePtr = new Sphere;
	spherePtr->SetCenter(80, 100, -90);
	spherePtr->SetRadius(40);
	spherePtr->materialPtr = svReflectivePtr;
	spherePtr->SetBoundingBox();
	//AddObjectToWorld(spherePtr);
	grid->AddObject(spherePtr);

	//Phong Cube

	phongPtr = new Phong(viewPlane.samplerPtr);
	phongPtr->SetAmbientBRDF(0.2, RGBColor(0, 0.79, 0.8));
	phongPtr->SetDiffuseBRDF(0.6, RGBColor(0, 0.47, 1));
	phongPtr->SetSpecularBRDF(0.4, RGBColor(1, 1, 1), 100);

	Cube *cubePtr = new Cube(Point3D(20, 20, -400), Point3D(60, 80, -250));
	cubePtr->materialPtr = phongPtr;
	AddObjectToWorld(cubePtr);

	//Compound Object - Cylinder

	CompoundObject *compoundObject = new CompoundObject();

	// OpenCylinder
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.25, RGBColor(1.0, 1.0, 0.5));
	mattePtr->SetDiffuseBRDF(0.75, RGBColor(1.0, 1.0, 0.5));

	OpenCylinder *openCylinder = new OpenCylinder(30, 80, 140);
	openCylinder->materialPtr = mattePtr;
	compoundObject->AddObject(openCylinder);
	AddObjectToWorld(openCylinder);

	//Floor Plane
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.1, 0.1, 0.1));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.46));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(0, 1, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Ceiling Plane
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.1, 0.1, 0.1));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.46));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 300, 0));
	planePtr->SetNormal(0, -1, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Wall one
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(1, 0, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Wall two
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(0, 0, -1);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Wall three
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, -700));
	planePtr->SetNormal(0, 0, 1);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Wall four
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(400, 0, 0));
	planePtr->SetNormal(-1, 0, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	grid->ConstructCells();
	AddObjectToWorld(grid);

	ambientLightPtr = new Ambient(white, 1);

	PointLight *pointLight = new PointLight(white, 3, Point3D(80, 200, -200), true);
	AddLightToWorld(pointLight);

	//SpotLight *spotLight = new SpotLight(white, 3, Point3D(175, 250, -225), Point3D(0,30,0), true);// Vector3D(0, -1, 0));// Vector3D(-0.577, -0.577, 0.577));
	//AddLightToWorld(spotLight);

	//DirectionalLight *directionalLight = new DirectionalLight(white, 3, Point3D(900, 200, -100), Vector3D(-1,-1,0), true);
	//AddLightToWorld(directionalLight);

	std::cout << "\nBuildWorldTest\n";
}

void World::BuildReflectiveBunny(void)
{
	Sphere *spherePtr;

	Matte *mattePtr;

	SVMatte *svMattePtr;

	Image *imagePtr;
	Texture *texturePtr;
	Mapping *mappingPtr;

	//ViewPlane
	viewPlane.SetResolution(600, 600, 0.5);
	viewPlane.SetSampler(1, 16);

	reflectionDepth = 1;

	//Camera
	Point3D eyePosition(0, 1.2, 0.7);
	//Point3D lookAtPosition(160, 90, -100);
	Point3D lookAtPosition(0, 0.03, 0);
	Vector3D upVector(0, 1, 0.25);
	float viewPlaneDistance = 1200;
	float rollAngle = 0;// -10; //-25; // Negative sign for clock-wise rotation

	cameraPtr = new PinHole(this, eyePosition, lookAtPosition, upVector, viewPlaneDistance, rollAngle);

	//Tracer
	tracerPtr = new WhittedTracer(this);

	//Background Color
	bgColor = black;

	//Objects

	Reflective* reflectivePtr = new Reflective(viewPlane.samplerPtr);
	reflectivePtr->SetAmbientBRDF(0.0, RGBColor(0, 0.2, 0.5));
	reflectivePtr->SetDiffuseBRDF(0.0, RGBColor(0, 0.5, 1));
	reflectivePtr->SetSpecularBRDF(0, RGBColor(1, 1, 1), 10000);
	reflectivePtr->SetPerfectSpecularBRDF(1, RGBColor(1, 1, 1.0));

	Grid *grid = new Grid;
	grid->ReadFlatTriangles("bun_zipper.ply");
	//grid->ReadFlatTriangles("dragonStandRight_48");
	//grid->ReadFlatTriangles("TwoTriangles.ply");
	//grid->ReadFlatTriangles("pyramid.ply");

	spherePtr = new Sphere;
	spherePtr->SetCenter(0, 0, 0);
	spherePtr->SetRadius(0.1);
	spherePtr->materialPtr = reflectivePtr;
	spherePtr->SetBoundingBox();
	//AddObjectToWorld(spherePtr);
	//grid->AddObject(spherePtr);


	grid->SetMaterial(reflectivePtr);
	grid->ConstructCells();
	AddObjectToWorld(grid);

	//Plane
	//Floor Plane
	imagePtr = new Image();
	imagePtr->ReadPPMFile("BrownRamp.ppm");

	mappingPtr = new RectangularMapping();
	texturePtr = new ImageTexture(imagePtr, mappingPtr);

	svMattePtr = new SVMatte(viewPlane.samplerPtr);
	svMattePtr->SetAmbientBRDF(0.4, texturePtr);
	svMattePtr->SetDiffuseBRDF(0.6, texturePtr);

	Plane *planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0.03, 0));
	planePtr->SetNormal(0, 1, 0);
	planePtr->materialPtr = svMattePtr;
	//planePtr->SetColor(0.86, 0.86, 0.86);
	AddObjectToWorld(planePtr);

	//Ceiling Plane
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.5, 0.5, 0.5));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(1.0, 1.0, 1.0));


	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 1.2, 0));
	planePtr->SetNormal(0, -1, 0);
	planePtr->materialPtr = mattePtr;
	//planePtr->SetColor(0.86, 0.86, 0.86);
	AddObjectToWorld(planePtr);

	//Wall one
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.5, 0.5, 0.5));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(1.0, 1.0, 1.0));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0.1, 0, 0));
	planePtr->SetNormal(-1, 0, 0);
	planePtr->materialPtr = mattePtr;
	//planePtr->SetColor(0.99, 0.96, 0.9);
	AddObjectToWorld(planePtr);

	//Wall two
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.5, 0.5, 0.5));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.5, 1.0, 0.5));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, -0.1));
	planePtr->SetNormal(0, 0, 1);
	planePtr->materialPtr = mattePtr;
	//planePtr->SetColor(1, 0.93, 0.83);
	AddObjectToWorld(planePtr);

	//Wall Three
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.5, 0.5, 0.5));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.5, 0.5, 1.0));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(-0.22, 0, 0));
	planePtr->SetNormal(1, 0, 0);
	planePtr->materialPtr = mattePtr;
	//planePtr->SetColor(0.99, 0.96, 0.9);
	AddObjectToWorld(planePtr);

	//Wall Four
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.2, 0.2, 0.2));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.5, 1.0, 0.5));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, -2));
	planePtr->SetNormal(0, 0, -1);
	planePtr->materialPtr = mattePtr;
	//planePtr->SetColor(1, 0.93, 0.83);
	AddObjectToWorld(planePtr);

	ambientLightPtr = new Ambient(white, 1);

	PointLight *pointLight = new PointLight(white, 3, Point3D(-0.03, 0.6, 0), true);
	AddLightToWorld(pointLight);

	//SpotLight *spotLight = new SpotLight(white, 3, Point3D(175, 250, -225), Point3D(0,30,0), true);// Vector3D(0, -1, 0));// Vector3D(-0.577, -0.577, 0.577));
	//AddLightToWorld(spotLight);

	//DirectionalLight *directionalLight = new DirectionalLight(white, 3, Point3D(900, 200, -100), Vector3D(-0.75, -1, +0.15), true);
	//AddLightToWorld(directionalLight);

	std::cout << "\nBuildGridTest\n";
}

void World::BuildReflectiveTetrahedron(void)
{
	Sphere *spherePtr;

	Matte *mattePtr;

	//ViewPlane
	viewPlane.SetResolution(600, 600, 0.5);
	viewPlane.SetSampler(1, 16);

	reflectionDepth = 5;

	//Camera
	Point3D eyePosition(60, 40, 15);
	//Point3D lookAtPosition(160, 90, -100);
	Point3D lookAtPosition(0, 5, 8);
	Vector3D upVector(0, 1, 0.25);
	float viewPlaneDistance = 1000;
	float rollAngle = 0;// -10; //-25; // Negative sign for clock-wise rotation

	cameraPtr = new PinHole(this, eyePosition, lookAtPosition, upVector, viewPlaneDistance, rollAngle);

	//Tracer
	tracerPtr = new WhittedTracer(this);

	//Background Color
	bgColor = black;

	//Objects

	Reflective* reflectivePtr = new Reflective(viewPlane.samplerPtr);
	reflectivePtr->SetAmbientBRDF(0.0, RGBColor(0, 0.2, 0.5));
	reflectivePtr->SetDiffuseBRDF(0, RGBColor(0, 0.5, 1));
	reflectivePtr->SetSpecularBRDF(0, RGBColor(1, 1, 1), 10000);
	reflectivePtr->SetPerfectSpecularBRDF(1, RGBColor(1, 1, 1.0));

	Cube* cubePtr = new Cube(Point3D(0, 10, 2), Point3D(0.5, 40, 40));
	cubePtr->materialPtr = reflectivePtr;
	AddObjectToWorld(cubePtr);

	reflectivePtr = new Reflective(viewPlane.samplerPtr);
	reflectivePtr->SetAmbientBRDF(0.0, RGBColor(0, 0.2, 0.5));
	reflectivePtr->SetDiffuseBRDF(0.0, RGBColor(0, 0.5, 1));
	reflectivePtr->SetSpecularBRDF(0, RGBColor(1, 1, 1), 10000);
	reflectivePtr->SetPerfectSpecularBRDF(1, RGBColor(1, 1, 1.0));

	Grid *grid = new Grid;
	grid->ReadFlatTriangles("pyramid.ply");


	spherePtr = new Sphere;
	spherePtr->SetCenter(5, 5, 5);
	spherePtr->SetRadius(5);
	spherePtr->materialPtr = reflectivePtr;
	spherePtr->SetBoundingBox();
	//grid->AddObject(spherePtr);

	grid->SetMaterial(reflectivePtr);
	grid->ConstructCells();
	AddObjectToWorld(grid);

	//Plane
	//Floor Plane
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.1, 0.1, 0.1));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.46));

	Plane *planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 5, 0));
	planePtr->SetNormal(0, 1, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Ceiling Plane
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.1, 0.1, 0.1));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.46));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 100, 0));
	planePtr->SetNormal(0, -1, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Wall one
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0.1, 0, 0));
	planePtr->SetNormal(1, 0, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Wall two
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(80, 0, 0));
	planePtr->SetNormal(-1, 0, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Wall three
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.8, 0.6, 0.2));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, -0.06));
	planePtr->SetNormal(0, 0, 1);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Wall four
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.8, 0.6, 0.2));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 40));
	planePtr->SetNormal(0, 0, -1);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	ambientLightPtr = new Ambient(white, 1);

	PointLight *pointLight = new PointLight(white, 6, Point3D(40, 50, 40), true);
	AddLightToWorld(pointLight);

	//SpotLight *spotLight = new SpotLight(white, 3, Point3D(175, 250, -225), Point3D(0,30,0), true);// Vector3D(0, -1, 0));// Vector3D(-0.577, -0.577, 0.577));
	//AddLightToWorld(spotLight);

	//DirectionalLight *directionalLight = new DirectionalLight(white, 3, Point3D(900, 200, -100), Vector3D(-0.75, -1, +0.15), true);
	//AddLightToWorld(directionalLight);

	std::cout << "\nBuildGridTest\n";
}

void World::BuildNormalMapTest(void)
{
	Sphere *spherePtr;
	Plane *planePtr;
	Rectangle *rectanglePtr;

	Matte *mattePtr;
	Phong *phongPtr;

	SVMatte *svMattePtr;

	Image *imagePtr;
	Texture *texturePtr;
	Mapping *mappingPtr;

	//ViewPlane
	viewPlane.SetResolution(600, 600, 0.5);
	viewPlane.SetSampler(1, 4);

	reflectionDepth = 2;

	//Camera
	Point3D eyePosition(120, 280, -500);
	Point3D lookAtPosition(100, 90, -100);
	Vector3D upVector(0, 1, 0);
	float viewPlaneDistance = 500;
	float rollAngle = 0;// -10; //-25; // Negative sign for clock-wise rotation

	cameraPtr = new PinHole(this, eyePosition, lookAtPosition, upVector, viewPlaneDistance, rollAngle);

	//Tracer
	tracerPtr = new WhittedTracer(this);

	//Background Color
	bgColor = white;

	//Objects
	imagePtr = new Image();
	imagePtr->ReadPPMFile("GreenAndYellow.ppm");

	mappingPtr = new SphericalMapping();

	texturePtr = new ImageTexture(imagePtr, mappingPtr);

	Image *normalMapPtr = new Image();
	//normalMapPtr->ReadPPMFile("SpiralNormal.ppm");
	normalMapPtr->ReadPPMFile("CheckerNormal.ppm");

	Texture *normalMapTexPtr = new ImageTexture(normalMapPtr, mappingPtr);

	svMattePtr = new SVMatte(viewPlane.samplerPtr);
	svMattePtr->SetAmbientBRDF(0.4, texturePtr);
	svMattePtr->SetDiffuseBRDF(0.6, texturePtr);
	//svMattePtr->SetNormalMap(normalMapTexPtr);

	spherePtr = new Sphere;
	spherePtr->SetCenter(70, 40, -90);
	spherePtr->SetRadius(40);
	spherePtr->materialPtr = svMattePtr;
	AddObjectToWorld(spherePtr);

	//Mirror
	Reflective *reflectivePtr = new Reflective(viewPlane.samplerPtr);
	reflectivePtr->SetAmbientBRDF(0, RGBColor(1, 0.09, 0.09));
	reflectivePtr->SetDiffuseBRDF(0, RGBColor(0, 1, 0.23));
	reflectivePtr->SetSpecularBRDF(0, RGBColor(1, 1, 1), 10000);
	reflectivePtr->SetPerfectSpecularBRDF(1, RGBColor(1.0, 1.0, 1.0));

	Cube* cubePtr = new Cube(Point3D(20, 20, -10), Point3D(400, 180, 0));
	cubePtr->materialPtr = reflectivePtr;
	AddObjectToWorld(cubePtr);

	//Sphere
	svMattePtr = new SVMatte(viewPlane.samplerPtr);
	svMattePtr->SetAmbientBRDF(0.4, texturePtr);
	svMattePtr->SetDiffuseBRDF(0.6, texturePtr);
	svMattePtr->SetNormalMap(normalMapTexPtr);

	spherePtr = new Sphere;
	spherePtr->SetCenter(160, 40, -90);
	spherePtr->SetRadius(40);
	spherePtr->materialPtr = svMattePtr;
	AddObjectToWorld(spherePtr);

	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.1, 0.1, 0.1));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.46));

	//Floor Plane
	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(0, 1, 0);
	planePtr->materialPtr = mattePtr;
	//planePtr->SetColor(0.86, 0.86, 0.86);
	AddObjectToWorld(planePtr);

	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	//Wall one
	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(1, 0, 0);
	planePtr->materialPtr = mattePtr;
	//planePtr->SetColor(0.99, 0.96, 0.9);
	AddObjectToWorld(planePtr);

	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	//Wall two
	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(0, 0, -1);
	planePtr->materialPtr = mattePtr;
	//planePtr->SetColor(1, 0.93, 0.83);
	AddObjectToWorld(planePtr);

	ambientLightPtr = new Ambient(white, 1);

	PointLight *pointLight = new PointLight(white, 3, Point3D(80, 200, -200), true);
	AddLightToWorld(pointLight);

	//SpotLight *spotLight = new SpotLight(white, 3, Point3D(175, 250, -225), Point3D(0,30,0), true);// Vector3D(0, -1, 0));// Vector3D(-0.577, -0.577, 0.577));
	//AddLightToWorld(spotLight);

	//DirectionalLight *directionalLight = new DirectionalLight(white, 3, Point3D(900, 200, -100), Vector3D(-1,-1,0), true);
	//AddLightToWorld(directionalLight);

	std::cout << "\nBuildWorldProject05\n";
}

void World::BuildWorldEnvironmentMap(void)
{
	Sphere *spherePtr;
	Plane *planePtr;
	Rectangle *rectanglePtr;

	Matte *mattePtr;
	Phong *phongPtr;
	Reflective *reflectivePtr;

	SVMatte *svMattePtr;
	SVReflective *svReflectivePtr;

	Image *imagePtr;
	Texture *texturePtr;
	Mapping *mappingPtr;
	LatticeNoise* noisePtr;

	Grid* grid = new Grid();

	//ViewPlane
	viewPlane.SetResolution(600, 600, 0.5);
	viewPlane.SetSampler(1, 16);

	//Camera
	Point3D eyePosition(25, 25, -50);
	//Point3D lookAtPosition(160, 90, -100);
	Point3D lookAtPosition(0, 0, 0);
	Vector3D upVector(0, 1, 0);
	float viewPlaneDistance = 200;
	float rollAngle = 179;// -10; //-25; // Negative sign for clock-wise rotation

	cameraPtr = new PinHole(this, eyePosition, lookAtPosition, upVector, viewPlaneDistance, rollAngle);

	//Tracer
	tracerPtr = new WhittedTracer(this);
	//tracerPtr = new Project01Tracer(this);
	reflectionDepth = 5;

	//Background Color
	bgColor = white;

	//Objects

	imagePtr = new Image();
	imagePtr->ReadPPMFile("uffizi.ppm");

	//mappingPtr = new LightProbeMapping();
	mappingPtr = new SphericalMapping();

	texturePtr = new ImageTexture(imagePtr, mappingPtr);

	svMattePtr = new SVMatte(viewPlane.samplerPtr);
	svMattePtr->SetAmbientBRDF(0.4, texturePtr);
	svMattePtr->SetDiffuseBRDF(0.6, texturePtr);

	spherePtr = new Sphere;
	spherePtr->SetCenter(0, 0, 0);
	spherePtr->SetRadius(100);
	spherePtr->materialPtr = svMattePtr;
	spherePtr->SetBoundingBox();
	AddObjectToWorld(spherePtr);
	
	//Reflective Cube

	reflectivePtr = new Reflective(viewPlane.samplerPtr);
	reflectivePtr->SetAmbientBRDF(0.3, RGBColor(0, 0.79, 0.8));
	reflectivePtr->SetDiffuseBRDF(0.7, RGBColor(0, 0.47, 1));
	reflectivePtr->SetSpecularBRDF(0, RGBColor(1, 1, 1), 10000);
	reflectivePtr->SetPerfectSpecularBRDF(1, RGBColor(1, 1, 1));

	Cube *cubePtr = new Cube(Point3D(-10, -10, -10), Point3D(10, 15, 10));
	cubePtr->materialPtr = reflectivePtr;
	AddObjectToWorld(cubePtr);

	//Reflective Tetrahedron

	reflectivePtr = new Reflective(viewPlane.samplerPtr);
	reflectivePtr->SetAmbientBRDF(0, RGBColor(0, 0.8, 0.79));
	reflectivePtr->SetDiffuseBRDF(0, RGBColor(0, 1, 0.47));
	reflectivePtr->SetSpecularBRDF(0, RGBColor(1, 1, 1), 10000);
	reflectivePtr->SetPerfectSpecularBRDF(1, RGBColor(1, 1, 1));

	grid->ReadFlatTriangles("pyramid.ply");
	grid->SetMaterial(reflectivePtr);
	grid->ConstructCells();
	AddObjectToWorld(grid);

	//Reflective Sphere

	reflectivePtr = new Reflective(viewPlane.samplerPtr);
	reflectivePtr->SetAmbientBRDF(0.2, RGBColor(0.79, 0.8, 0.79));
	reflectivePtr->SetDiffuseBRDF(0.6, RGBColor(1, 1, 0.47));
	reflectivePtr->SetSpecularBRDF(0, RGBColor(1, 1, 1), 10000);
	reflectivePtr->SetPerfectSpecularBRDF(1, RGBColor(1, 1, 1));

	spherePtr = new Sphere;
	spherePtr->SetCenter(17.5, 0, 0);
	spherePtr->SetRadius(5);
	spherePtr->materialPtr = reflectivePtr;
	spherePtr->SetBoundingBox();
	AddObjectToWorld(spherePtr);

	ambientLightPtr = new Ambient(white, 1);

	PointLight *pointLight = new PointLight(white, 3, Point3D(20, 25, -30), true);
	AddLightToWorld(pointLight);

	//SpotLight *spotLight = new SpotLight(white, 3, Point3D(175, 250, -225), Point3D(0,30,0), true);// Vector3D(0, -1, 0));// Vector3D(-0.577, -0.577, 0.577));
	//AddLightToWorld(spotLight);

	//DirectionalLight *directionalLight = new DirectionalLight(white, 3, Point3D(900, 200, -100), Vector3D(-1,-1,0), true);
	//AddLightToWorld(directionalLight);

	std::cout << "\nBuildWorldTest\n";
}

void World::BuildWorldProject09(void)
{
	Sphere *spherePtr;
	Plane *planePtr;
	Rectangle *rectanglePtr;
	Cube *cubePtr;

	Matte *mattePtr;
	Phong *phongPtr;
	Reflective *reflectivePtr;
	Transparent *transparentPtr;

	SVMatte *svMattePtr;

	Image *imagePtr;
	Texture *texturePtr;
	Mapping *mappingPtr;
	LatticeNoise* noisePtr;

	Grid* grid = new Grid();

	//ViewPlane
	viewPlane.SetResolution(600, 600, 0.5);
	viewPlane.SetSampler(1, 4);

	//Camera
	Point3D eyePosition(120, 280, -500);
	//Point3D lookAtPosition(160, 90, -100);
	Point3D lookAtPosition(50, 40, 0);
	Vector3D upVector(0, 1, 0);
	float viewPlaneDistance = 500;
	float rollAngle = 0;// -10; //-25; // Negative sign for clock-wise rotation

	cameraPtr = new PinHole(this, eyePosition, lookAtPosition, upVector, viewPlaneDistance, rollAngle);

	//Tracer
	tracerPtr = new WhittedTracer(this);
	//tracerPtr = new Project01Tracer(this);
	reflectionDepth = 5;

	//Background Color
	bgColor = white;

	//Objects

	//Transparent cube
	transparentPtr = new Transparent();
	transparentPtr->SetAmbientBRDF(0, RGBColor(1, 0.09, 0.09));
	transparentPtr->SetDiffuseBRDF(0, RGBColor(0, 1, 0.23));
	transparentPtr->SetSpecularBRDF(0.2, RGBColor(1, 1, 1), 2000);
	transparentPtr->SetPerfectSpecularBRDF(0.1, RGBColor(1.0, 1.0, 1.0));
	transparentPtr->SetTransparentProperties(0.9, 1.003);

	cubePtr = new Cube(Point3D(50, 120, -150), Point3D(125, 160, -90));
	cubePtr->materialPtr = transparentPtr;
	AddObjectToWorld(cubePtr);

	//Phong Cube

	phongPtr = new Phong(viewPlane.samplerPtr);
	phongPtr->SetAmbientBRDF(0.2, RGBColor(0, 0.79, 0.8));
	phongPtr->SetDiffuseBRDF(0.6, RGBColor(0, 0.47, 1));
	phongPtr->SetSpecularBRDF(0.4, RGBColor(1, 1, 1), 100);

	cubePtr = new Cube(Point3D(20, 20, -400), Point3D(60, 80, -250));
	cubePtr->materialPtr = phongPtr;
	AddObjectToWorld(cubePtr);

	//Compound Object - Cylinder

	CompoundObject *compoundObject = new CompoundObject();

	// OpenCylinder
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.25, RGBColor(1.0, 1.0, 0.5));
	mattePtr->SetDiffuseBRDF(0.75, RGBColor(1.0, 1.0, 0.5));

	OpenCylinder *openCylinder = new OpenCylinder(30, 80, 140);
	openCylinder->materialPtr = mattePtr;
	compoundObject->AddObject(openCylinder);
	AddObjectToWorld(openCylinder);

	//Floor Plane
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.1, 0.1, 0.1));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.46));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(0, 1, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Ceiling Plane
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.1, 0.1, 0.1));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.46));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 300, 0));
	planePtr->SetNormal(0, -1, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Wall one
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(1, 0, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Wall two
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(0, 0, -1);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Wall three
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, -700));
	planePtr->SetNormal(0, 0, 1);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Wall four
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(400, 0, 0));
	planePtr->SetNormal(-1, 0, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	grid->ConstructCells();
	AddObjectToWorld(grid);

	ambientLightPtr = new Ambient(white, 1);

	PointLight *pointLight = new PointLight(white, 3, Point3D(200, 200, -100), true);
	AddLightToWorld(pointLight);

	pointLight = new PointLight(white, 3, Point3D(300, 290, -75), true);
	AddLightToWorld(pointLight);

	pointLight = new PointLight(white, 2, Point3D(50, 25, -75), true);
	//AddLightToWorld(pointLight);

	//SpotLight *spotLight = new SpotLight(white, 3, Point3D(175, 250, -225), Point3D(0,30,0), true);// Vector3D(0, -1, 0));// Vector3D(-0.577, -0.577, 0.577));
	//AddLightToWorld(spotLight);

	//DirectionalLight *directionalLight = new DirectionalLight(white, 3, Point3D(900, 200, -100), Vector3D(-1,-1,0), true);
	//AddLightToWorld(directionalLight);

	std::cout << "\nBuildWorldTest\n";
}

void World::BuildTransparentBunny(void)
{
	Sphere *spherePtr;

	Matte *mattePtr;

	SVMatte *svMattePtr;

	Image *imagePtr;
	Texture *texturePtr;
	Mapping *mappingPtr;

	//ViewPlane
	viewPlane.SetResolution(600, 600, 0.5);
	viewPlane.SetSampler(1, 16);

	reflectionDepth = 2;

	//Camera
	Point3D eyePosition(0, 1.2, 0.7);
	//Point3D lookAtPosition(160, 90, -100);
	Point3D lookAtPosition(-0.05, 0.03, 0);
	Vector3D upVector(0, 1, 0.25);
	float viewPlaneDistance = 1200;
	float rollAngle = 0;// -10; //-25; // Negative sign for clock-wise rotation

	cameraPtr = new PinHole(this, eyePosition, lookAtPosition, upVector, viewPlaneDistance, rollAngle);

	//Tracer
	tracerPtr = new WhittedTracer(this);

	//Background Color
	bgColor = black;

	//Objects

	Transparent *transparentPtr = new Transparent();
	transparentPtr->SetAmbientBRDF(0, RGBColor(1, 0.09, 0.09));
	transparentPtr->SetDiffuseBRDF(0, RGBColor(0, 1, 0.23));
	transparentPtr->SetSpecularBRDF(0.2, RGBColor(1, 1, 1), 2000);
	transparentPtr->SetPerfectSpecularBRDF(0.1, RGBColor(1.0, 1.0, 1.0));
	transparentPtr->SetTransparentProperties(0.9, 1);

	Grid *grid = new Grid;
	grid->ReadFlatTriangles("bun_zipper.ply");
	//grid->ReadFlatTriangles("dragonStandRight_48");
	//grid->ReadFlatTriangles("TwoTriangles.ply");
	//grid->ReadFlatTriangles("pyramid.ply");

	grid->SetMaterial(transparentPtr);
	grid->ConstructCells();
	AddObjectToWorld(grid);

	//Plane
	//Floor Plane
	imagePtr = new Image();
	imagePtr->ReadPPMFile("BrownRamp.ppm");

	mappingPtr = new RectangularMapping();
	texturePtr = new ImageTexture(imagePtr, mappingPtr);

	svMattePtr = new SVMatte(viewPlane.samplerPtr);
	svMattePtr->SetAmbientBRDF(0.4, texturePtr);
	svMattePtr->SetDiffuseBRDF(0.6, texturePtr);

	Plane *planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, -0.06, 0));
	planePtr->SetNormal(0, 1, 0);
	planePtr->materialPtr = svMattePtr;
	//planePtr->SetColor(0.86, 0.86, 0.86);
	AddObjectToWorld(planePtr);

	//Ceiling Plane
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.1, 0.1, 0.1));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.46));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 300, 0));
	planePtr->SetNormal(0, -1, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Wall one
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.5, 0.5, 0.5));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(1.0, 1.0, 1.0));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0.1, 0, 0));
	planePtr->SetNormal(-1, 0, 0);
	planePtr->materialPtr = mattePtr;
	//planePtr->SetColor(0.99, 0.96, 0.9);
	//AddObjectToWorld(planePtr);

	//Wall two
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.5, 0.5, 0.5));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.5, 1.0, 0.5));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, -0.1));
	planePtr->SetNormal(0, 0, 1);
	planePtr->materialPtr = mattePtr;
	//planePtr->SetColor(1, 0.93, 0.83);
	//AddObjectToWorld(planePtr);

	//Wall three
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, -700));
	planePtr->SetNormal(0, 0, 1);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Wall four
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(400, 0, 0));
	planePtr->SetNormal(-1, 0, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	ambientLightPtr = new Ambient(white, 1);

	PointLight *pointLight = new PointLight(white, 3, Point3D(-0.8, 0.6, 0.2), true);
	AddLightToWorld(pointLight);

	//SpotLight *spotLight = new SpotLight(white, 3, Point3D(175, 250, -225), Point3D(0,30,0), true);// Vector3D(0, -1, 0));// Vector3D(-0.577, -0.577, 0.577));
	//AddLightToWorld(spotLight);

	//DirectionalLight *directionalLight = new DirectionalLight(white, 3, Point3D(900, 200, -100), Vector3D(-0.75, -1, +0.15), true);
	//AddLightToWorld(directionalLight);

	std::cout << "\nBuildGridTest\n";
}

void World::BuildTransparentRectangle(void)
{
	Sphere *spherePtr;
	Plane *planePtr;
	Rectangle *rectanglePtr;
	Cube *cubePtr;

	Matte *mattePtr;
	Phong *phongPtr;
	Reflective *reflectivePtr;
	Transparent *transparentPtr;

	SVMatte *svMattePtr;
	SVTransparent * svTransparentPtr;

	Image *imagePtr;
	Texture *texturePtr;
	Mapping *mappingPtr;
	LatticeNoise* noisePtr;

	Grid* grid = new Grid();

	//ViewPlane
	viewPlane.SetResolution(600, 600, 0.5);
	viewPlane.SetSampler(1, 16);

	//Camera
	Point3D eyePosition(120, 280, -500);
	//Point3D lookAtPosition(160, 90, -100);
	Point3D lookAtPosition(50, 40, 0);
	Vector3D upVector(0, 1, 0);
	float viewPlaneDistance = 500;
	float rollAngle = 0;// -10; //-25; // Negative sign for clock-wise rotation

	cameraPtr = new PinHole(this, eyePosition, lookAtPosition, upVector, viewPlaneDistance, rollAngle);

	//Tracer
	tracerPtr = new WhittedTracer(this);
	//tracerPtr = new Project01Tracer(this);
	reflectionDepth = 5;

	//Background Color
	bgColor = white;

	//Objects

	//Transparent rectangle

	imagePtr = new Image();
	imagePtr->ReadPPMFile("GreenAndYellow.ppm");

	mappingPtr = new RectangularMapping();

	texturePtr = new ImageTexture(imagePtr, mappingPtr);

	Image *normalMapPtr = new Image();
	//normalMapPtr->ReadPPMFile("SpiralNormal.ppm");
	normalMapPtr->ReadPPMFile("CheckerNormal.ppm");

	Texture *normalMapTexPtr = new ImageTexture(normalMapPtr, mappingPtr);

	svTransparentPtr = new SVTransparent(viewPlane.samplerPtr);
	svTransparentPtr->SetAmbientBRDF(0, texturePtr);
	svTransparentPtr->SetDiffuseBRDF(0, texturePtr);
	svTransparentPtr->SetNormalMap(normalMapTexPtr);
	svTransparentPtr->SetSpecularBRDF(0.2, RGBColor(1, 1, 1), 2000);
	svTransparentPtr->SetPerfectSpecularBRDF(0.05, RGBColor(1.0, 1.0, 1.0));
	svTransparentPtr->SetTransparentProperties(0.95, 1.005);

	rectanglePtr = new Rectangle(Point3D(190, 75, -100), Vector3D(-160, 0, 0), Vector3D(0, 120, 0));
	rectanglePtr->materialPtr = svTransparentPtr;
	AddObjectToWorld(rectanglePtr);

	//Phong Cube

	phongPtr = new Phong(viewPlane.samplerPtr);
	phongPtr->SetAmbientBRDF(0.2, RGBColor(0, 0.79, 0.8));
	phongPtr->SetDiffuseBRDF(0.6, RGBColor(0, 0.47, 1));
	phongPtr->SetSpecularBRDF(0.4, RGBColor(1, 1, 1), 100);

	cubePtr = new Cube(Point3D(20, 20, -400), Point3D(60, 80, -250));
	cubePtr->materialPtr = phongPtr;
	AddObjectToWorld(cubePtr);

	//Compound Object - Cylinder

	CompoundObject *compoundObject = new CompoundObject();

	// OpenCylinder
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.25, RGBColor(1.0, 1.0, 0.5));
	mattePtr->SetDiffuseBRDF(0.75, RGBColor(1.0, 1.0, 0.5));

	OpenCylinder *openCylinder = new OpenCylinder(30, 80, 140);
	openCylinder->materialPtr = mattePtr;
	compoundObject->AddObject(openCylinder);
	AddObjectToWorld(openCylinder);

	//Floor Plane
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.1, 0.1, 0.1));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.46));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(0, 1, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Ceiling Plane
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.1, 0.1, 0.1));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.46));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 300, 0));
	planePtr->SetNormal(0, -1, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Wall one
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(1, 0, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Wall two
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(0, 0, -1);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Wall three
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, -700));
	planePtr->SetNormal(0, 0, 1);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Wall four
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(400, 0, 0));
	planePtr->SetNormal(-1, 0, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	grid->ConstructCells();
	AddObjectToWorld(grid);

	ambientLightPtr = new Ambient(white, 1);

	PointLight *pointLight = new PointLight(white, 3, Point3D(200, 200, -100), true);
	AddLightToWorld(pointLight);

	pointLight = new PointLight(white, 3, Point3D(300, 290, -75), true);
	AddLightToWorld(pointLight);

	pointLight = new PointLight(white, 2, Point3D(50, 25, -75), true);
	//AddLightToWorld(pointLight);

	//SpotLight *spotLight = new SpotLight(white, 3, Point3D(175, 250, -225), Point3D(0,30,0), true);// Vector3D(0, -1, 0));// Vector3D(-0.577, -0.577, 0.577));
	//AddLightToWorld(spotLight);

	//DirectionalLight *directionalLight = new DirectionalLight(white, 3, Point3D(900, 200, -100), Vector3D(-1,-1,0), true);
	//AddLightToWorld(directionalLight);

	std::cout << "\nBuildWorldTest\n";
}

void World::BuildTransparentRectangleSVEta(void)
{
	Sphere *spherePtr;
	Plane *planePtr;
	Rectangle *rectanglePtr;
	Cube *cubePtr;

	Matte *mattePtr;
	Phong *phongPtr;
	Reflective *reflectivePtr;
	Transparent *transparentPtr;

	SVMatte *svMattePtr;
	SVTransparentEta * svTransparentPtr;

	Image *imagePtr;
	Texture *texturePtr;
	Mapping *mappingPtr;
	LatticeNoise* noisePtr;

	Grid* grid = new Grid();

	//ViewPlane
	viewPlane.SetResolution(600, 600, 0.5);
	viewPlane.SetSampler(1, 16);

	//Camera
	Point3D eyePosition(120, 280, -500);
	//Point3D lookAtPosition(160, 90, -100);
	Point3D lookAtPosition(50, 40, 0);
	Vector3D upVector(0, 1, 0);
	float viewPlaneDistance = 500;
	float rollAngle = 0;// -10; //-25; // Negative sign for clock-wise rotation

	cameraPtr = new PinHole(this, eyePosition, lookAtPosition, upVector, viewPlaneDistance, rollAngle);

	//Tracer
	tracerPtr = new WhittedTracer(this);
	//tracerPtr = new Project01Tracer(this);
	reflectionDepth = 5;

	//Background Color
	bgColor = white;

	//Objects

	//Transparent rectangle

	imagePtr = new Image();
	imagePtr->ReadPPMFile("GreenAndYellow.ppm");

	mappingPtr = new RectangularMapping();

	texturePtr = new ImageTexture(imagePtr, mappingPtr);

	Image *normalMapPtr = new Image();
	//normalMapPtr->ReadPPMFile("SpiralNormal.ppm");
	normalMapPtr->ReadPPMFile("CheckerNormal.ppm");

	Texture *normalMapTexPtr = new ImageTexture(normalMapPtr, mappingPtr);

	svTransparentPtr = new SVTransparentEta(viewPlane.samplerPtr);
	svTransparentPtr->SetAmbientBRDF(0, texturePtr);
	svTransparentPtr->SetDiffuseBRDF(0, texturePtr);
	svTransparentPtr->SetNormalMap(normalMapTexPtr);
	svTransparentPtr->SetSpecularBRDF(0.2, RGBColor(1, 1, 1), 2000);
	svTransparentPtr->SetPerfectSpecularBRDF(0.05, RGBColor(1.0, 1.0, 1.0));
	svTransparentPtr->SetTransparentProperties(0.95, 1.005);

	rectanglePtr = new Rectangle(Point3D(190, 75, -100), Vector3D(-160, 0, 0), Vector3D(0, 120, 0));
	rectanglePtr->materialPtr = svTransparentPtr;
	AddObjectToWorld(rectanglePtr);

	//Phong Cube

	phongPtr = new Phong(viewPlane.samplerPtr);
	phongPtr->SetAmbientBRDF(0.2, RGBColor(0, 0.79, 0.8));
	phongPtr->SetDiffuseBRDF(0.6, RGBColor(0, 0.47, 1));
	phongPtr->SetSpecularBRDF(0.4, RGBColor(1, 1, 1), 100);

	cubePtr = new Cube(Point3D(20, 20, -400), Point3D(60, 80, -250));
	cubePtr->materialPtr = phongPtr;
	AddObjectToWorld(cubePtr);

	//Compound Object - Cylinder

	CompoundObject *compoundObject = new CompoundObject();

	// OpenCylinder
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.25, RGBColor(1.0, 1.0, 0.5));
	mattePtr->SetDiffuseBRDF(0.75, RGBColor(1.0, 1.0, 0.5));

	OpenCylinder *openCylinder = new OpenCylinder(30, 80, 140);
	openCylinder->materialPtr = mattePtr;
	compoundObject->AddObject(openCylinder);
	AddObjectToWorld(openCylinder);

	//Floor Plane
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.1, 0.1, 0.1));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.46));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(0, 1, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Ceiling Plane
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.1, 0.1, 0.1));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.46));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 300, 0));
	planePtr->SetNormal(0, -1, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Wall one
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(1, 0, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Wall two
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(0, 0, -1);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Wall three
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, -700));
	planePtr->SetNormal(0, 0, 1);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Wall four
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(400, 0, 0));
	planePtr->SetNormal(-1, 0, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	grid->ConstructCells();
	AddObjectToWorld(grid);

	ambientLightPtr = new Ambient(white, 1);

	PointLight *pointLight = new PointLight(white, 3, Point3D(200, 200, -100), true);
	AddLightToWorld(pointLight);

	pointLight = new PointLight(white, 3, Point3D(300, 290, -75), true);
	AddLightToWorld(pointLight);

	pointLight = new PointLight(white, 2, Point3D(50, 25, -75), true);
	//AddLightToWorld(pointLight);

	//SpotLight *spotLight = new SpotLight(white, 3, Point3D(175, 250, -225), Point3D(0,30,0), true);// Vector3D(0, -1, 0));// Vector3D(-0.577, -0.577, 0.577));
	//AddLightToWorld(spotLight);

	//DirectionalLight *directionalLight = new DirectionalLight(white, 3, Point3D(900, 200, -100), Vector3D(-1,-1,0), true);
	//AddLightToWorld(directionalLight);

	std::cout << "\nBuildWorldTest\n";
}

void World::BuildDOFTest(void)
{
	Sphere *spherePtr;
	Plane *planePtr;
	Rectangle *rectanglePtr;
	Cube *cubePtr;

	Matte *mattePtr;
	Phong *phongPtr;
	Reflective *reflectivePtr;
	Transparent *transparentPtr;

	SVMatte *svMattePtr;
	SVTransparentEta * svTransparentPtr;

	Image *imagePtr;
	Texture *texturePtr;
	Mapping *mappingPtr;
	LatticeNoise* noisePtr;

	Grid* grid = new Grid();

	//ViewPlane
	int samples = 100;
	viewPlane.SetResolution(600, 600, 0.5);
	viewPlane.SetSampler(1, samples);

	//Camera
	Point3D eyePosition(120, 100, -500);
	//Point3D lookAtPosition(160, 90, -100);
	Point3D lookAtPosition(100, 20, 1000);
	Vector3D upVector(0, 1, 0);
	float viewPlaneDistance = 500;
	float rollAngle = 0;// -10; //-25; // Negative sign for clock-wise rotation
	float focalPlaneDistance = 510;
	float lensRadius = 25;
	Sampler *lensSampler = new JitteredSampler(samples);

	cameraPtr = new DOFCamera(this, eyePosition, lookAtPosition, upVector, viewPlaneDistance, focalPlaneDistance, lensRadius, rollAngle, lensSampler);

	//Tracer
	tracerPtr = new WhittedTracer(this);
	//tracerPtr = new Project01Tracer(this);
	reflectionDepth = 5;

	//Background Color
	bgColor = white;

	//Objects

	//Transparent rectangle

	imagePtr = new Image();
	imagePtr->ReadPPMFile("GreenAndYellow.ppm");

	mappingPtr = new RectangularMapping();

	texturePtr = new ImageTexture(imagePtr, mappingPtr);

	Image *normalMapPtr = new Image();
	//normalMapPtr->ReadPPMFile("SpiralNormal.ppm");
	normalMapPtr->ReadPPMFile("CheckerNormal.ppm");

	Texture *normalMapTexPtr = new ImageTexture(normalMapPtr, mappingPtr);

	svTransparentPtr = new SVTransparentEta(viewPlane.samplerPtr);
	svTransparentPtr->SetAmbientBRDF(0, texturePtr);
	svTransparentPtr->SetDiffuseBRDF(0, texturePtr);
	svTransparentPtr->SetNormalMap(normalMapTexPtr);
	svTransparentPtr->SetSpecularBRDF(0.2, RGBColor(1, 1, 1), 2000);
	svTransparentPtr->SetPerfectSpecularBRDF(0.05, RGBColor(1.0, 1.0, 1.0));
	svTransparentPtr->SetTransparentProperties(0.95, 1.005);

	rectanglePtr = new Rectangle(Point3D(190, 75, -100), Vector3D(-160, 0, 0), Vector3D(0, 120, 0));
	rectanglePtr->materialPtr = svTransparentPtr;
	//AddObjectToWorld(rectanglePtr);

	//Globe
	imagePtr = new Image();
	imagePtr->ReadPPMFile("GreenAndYellow.ppm");

	mappingPtr = new SphericalMapping();

	texturePtr = new ImageTexture(imagePtr, mappingPtr);

	svMattePtr = new SVMatte(viewPlane.samplerPtr);
	svMattePtr->SetAmbientBRDF(0.4, texturePtr);
	svMattePtr->SetDiffuseBRDF(0.6, texturePtr);

	spherePtr = new Sphere;
	spherePtr->SetCenter(160, 40, 40);
	spherePtr->SetRadius(40);
	spherePtr->materialPtr = svMattePtr;
	//spherePtr->SetColor(0.25, 0.41, 0.88);
	AddObjectToWorld(spherePtr);

	//Phong Cube

	phongPtr = new Phong(viewPlane.samplerPtr);
	phongPtr->SetAmbientBRDF(0.2, RGBColor(0, 0.79, 0.8));
	phongPtr->SetDiffuseBRDF(0.6, RGBColor(0, 0.47, 1));
	phongPtr->SetSpecularBRDF(0.4, RGBColor(1, 1, 1), 100);

	cubePtr = new Cube(Point3D(20, 0, 0), Point3D(60, 60, 100));
	cubePtr->materialPtr = phongPtr;
	AddObjectToWorld(cubePtr);

	//Floor Plane
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.1, 0.1, 0.1));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.46));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(0, 1, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Ceiling Plane
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.1, 0.1, 0.1));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.46));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 300, 0));
	planePtr->SetNormal(0, -1, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Wall one
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(1, 0, 0);
	planePtr->materialPtr = mattePtr;
	//AddObjectToWorld(planePtr);

	//Wall two
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(0, 0, -1);
	planePtr->materialPtr = mattePtr;
	//AddObjectToWorld(planePtr);

	//Wall three
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, -700));
	planePtr->SetNormal(0, 0, 1);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Wall four
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(400, 0, 0));
	planePtr->SetNormal(-1, 0, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	grid->ConstructCells();
	AddObjectToWorld(grid);

	ambientLightPtr = new Ambient(white, 1);

	PointLight *pointLight = new PointLight(white, 3, Point3D(200, 200, -100), true);
	AddLightToWorld(pointLight);

	pointLight = new PointLight(white, 3, Point3D(300, 290, -75), true);
	AddLightToWorld(pointLight);

	pointLight = new PointLight(white, 2, Point3D(50, 25, -75), true);
	//AddLightToWorld(pointLight);

	//SpotLight *spotLight = new SpotLight(white, 3, Point3D(175, 250, -225), Point3D(0,30,0), true);// Vector3D(0, -1, 0));// Vector3D(-0.577, -0.577, 0.577));
	//AddLightToWorld(spotLight);

	//DirectionalLight *directionalLight = new DirectionalLight(white, 3, Point3D(900, 200, -100), Vector3D(-1,-1,0), true);
	//AddLightToWorld(directionalLight);

	std::cout << "\nBuildWorldTest\n";
}

void World::BuildAmbientOcclusionTest(void)
{
	Sphere *spherePtr;
	Plane *planePtr;
	Rectangle *rectanglePtr;
	Cube *cubePtr;

	Matte *mattePtr;
	Phong *phongPtr;
	Reflective *reflectivePtr;
	Transparent *transparentPtr;

	SVMatte *svMattePtr;
	SVTransparentEta * svTransparentPtr;

	Image *imagePtr;
	Texture *texturePtr;
	Mapping *mappingPtr;
	LatticeNoise* noisePtr;

	Grid* grid = new Grid();

	//ViewPlane
	int samples = 100;
	viewPlane.SetResolution(500, 400, 0.5);
	viewPlane.SetSampler(1, samples);

	//Camera
	Point3D eyePosition(120, 100, -500);
	//Point3D lookAtPosition(160, 90, -100);
	Point3D lookAtPosition(100, 20, 1000);
	Vector3D upVector(0, 1, 0);
	float viewPlaneDistance = 500;
	float rollAngle = 0;// -10; //-25; // Negative sign for clock-wise rotation
	
	/*
	float focalPlaneDistance = 510;
	float lensRadius = 25;
	Sampler *lensSampler = new JitteredSampler(samples);
	*/

	cameraPtr = new PinHole(this, eyePosition, lookAtPosition, upVector, viewPlaneDistance, rollAngle);

	//Tracer
	tracerPtr = new WhittedTracer(this);
	//tracerPtr = new Project01Tracer(this);
	reflectionDepth = 5;

	//Background Color
	bgColor = white;

	//Objects

	//Globe
	imagePtr = new Image();
	imagePtr->ReadPPMFile("GreenAndYellow.ppm");

	mappingPtr = new SphericalMapping();

	texturePtr = new ImageTexture(imagePtr, mappingPtr);

	svMattePtr = new SVMatte(viewPlane.samplerPtr);
	svMattePtr->SetAmbientBRDF(0.8, texturePtr);
	svMattePtr->SetDiffuseBRDF(0, texturePtr);

	spherePtr = new Sphere;
	spherePtr->SetCenter(160, 40, 40);
	spherePtr->SetRadius(40);
	spherePtr->materialPtr = svMattePtr;
	//spherePtr->SetColor(0.25, 0.41, 0.88);
	//AddObjectToWorld(spherePtr);
	
	//Matte sphere
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.8, RGBColor(1, 0, 0));
	mattePtr->SetDiffuseBRDF(0, RGBColor(0.61, 0.42, 0.46));

	spherePtr = new Sphere;
	spherePtr->SetCenter(160, 40, 40);
	spherePtr->SetRadius(40);
	spherePtr->materialPtr = mattePtr;
	AddObjectToWorld(spherePtr);

	//Phong Cube

	phongPtr = new Phong(viewPlane.samplerPtr);
	phongPtr->SetAmbientBRDF(0.8, RGBColor(0, 0.47, 0.8));
	phongPtr->SetDiffuseBRDF(0, RGBColor(0, 0.47, 1));
	phongPtr->SetSpecularBRDF(0.4, RGBColor(1, 1, 1), 100);

	cubePtr = new Cube(Point3D(20, 0, 0), Point3D(60, 60, 100));
	cubePtr->materialPtr = phongPtr;
	AddObjectToWorld(cubePtr);

	//Floor Plane
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.8, RGBColor(0.8, 0.8, 0.8));
	mattePtr->SetDiffuseBRDF(0, RGBColor(0.61, 0.42, 0.46));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(0, 1, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Ceiling Plane
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.1, 0.1, 0.1));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.46));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 300, 0));
	planePtr->SetNormal(0, -1, 0);
	planePtr->materialPtr = mattePtr;
	//AddObjectToWorld(planePtr);


	Sampler *ambientOcclusionSampler = new JitteredSampler(samples);
	ambientOcclusionSampler->MapSamplesToHemiSphere(1);
	ambientLightPtr = new AmbientWithOccluder(white, 1, 0, ambientOcclusionSampler);
	//ambientLightPtr = new Ambient(white, 1);

	PointLight *pointLight = new PointLight(white, 3, Point3D(200, 200, -100), true);
	//AddLightToWorld(pointLight);

	pointLight = new PointLight(white, 3, Point3D(300, 290, -75), true);
	//AddLightToWorld(pointLight);

	pointLight = new PointLight(white, 2, Point3D(50, 25, -75), true);
	//AddLightToWorld(pointLight);

	//SpotLight *spotLight = new SpotLight(white, 3, Point3D(175, 250, -225), Point3D(0,30,0), true);// Vector3D(0, -1, 0));// Vector3D(-0.577, -0.577, 0.577));
	//AddLightToWorld(spotLight);

	//DirectionalLight *directionalLight = new DirectionalLight(white, 3, Point3D(900, 200, -100), Vector3D(-1,-1,0), true);
	//AddLightToWorld(directionalLight);

	std::cout << "\nBuildWorldTest\n";
}

void World::BuildAreaLightTest(void)
{
	Sphere *spherePtr;
	Plane *planePtr;
	Rectangle *rectanglePtr;
	Cube *cubePtr;

	Matte *mattePtr;
	Phong *phongPtr;
	Reflective *reflectivePtr;
	Transparent *transparentPtr;

	SVMatte *svMattePtr;
	SVTransparentEta * svTransparentPtr;

	Image *imagePtr;
	Texture *texturePtr;
	Mapping *mappingPtr;
	LatticeNoise* noisePtr;

	Grid* grid = new Grid();

	//ViewPlane
	int samples = 196;
	viewPlane.SetResolution(500, 400, 0.5);
	viewPlane.SetSampler(1, samples);

	//Camera
	Point3D eyePosition(120, 100, -500);
	Point3D lookAtPosition(100, 10, 1000);
	Vector3D upVector(0, 1, 0);
	float viewPlaneDistance = 400;
	float rollAngle = 0;// -10; //-25; // Negative sign for clock-wise rotation

	cameraPtr = new PinHole(this, eyePosition, lookAtPosition, upVector, viewPlaneDistance, rollAngle);

	//Tracer
	tracerPtr = new WhittedTracer(this);
	//tracerPtr = new Project01Tracer(this);
	reflectionDepth = 5;

	//Background Color
	bgColor = white;

	//Objects

	//Globe
	imagePtr = new Image();
	imagePtr->ReadPPMFile("GreenAndYellow.ppm");

	mappingPtr = new SphericalMapping();

	texturePtr = new ImageTexture(imagePtr, mappingPtr);

	svMattePtr = new SVMatte(viewPlane.samplerPtr);
	svMattePtr->SetAmbientBRDF(0.8, texturePtr);
	svMattePtr->SetDiffuseBRDF(0, texturePtr);

	spherePtr = new Sphere;
	spherePtr->SetCenter(160, 40, 40);
	spherePtr->SetRadius(40);
	spherePtr->materialPtr = svMattePtr;
	//spherePtr->SetColor(0.25, 0.41, 0.88);
	//AddObjectToWorld(spherePtr);

	//Matte sphere
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.3, RGBColor(1, 0, 0));
	mattePtr->SetDiffuseBRDF(0.7, RGBColor(1, 0.12, 0.16));

	spherePtr = new Sphere;
	spherePtr->SetCenter(160, 40, 40);
	spherePtr->SetRadius(40);
	spherePtr->materialPtr = mattePtr;
	AddObjectToWorld(spherePtr);

	//Phong Cube

	phongPtr = new Phong(viewPlane.samplerPtr);
	phongPtr->SetAmbientBRDF(0.3, RGBColor(0, 0.47, 0.8));
	phongPtr->SetDiffuseBRDF(0.7, RGBColor(0, 0.47, 1));
	phongPtr->SetSpecularBRDF(1, RGBColor(1, 1, 1), 100);

	cubePtr = new Cube(Point3D(20, 0, 0), Point3D(60, 60, 100));
	cubePtr->materialPtr = phongPtr;
	AddObjectToWorld(cubePtr);

	//Floor Plane
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.3, RGBColor(0.8, 0.8, 0.8));
	mattePtr->SetDiffuseBRDF(0.7, RGBColor(1, 1, 1));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(0, 1, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Ceiling Plane
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.1, 0.1, 0.1));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.46));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 300, 0));
	planePtr->SetNormal(0, -1, 0);
	planePtr->materialPtr = mattePtr;
	//AddObjectToWorld(planePtr);


	Sampler *ambientOcclusionSampler = new JitteredSampler(samples);
	ambientOcclusionSampler->MapSamplesToHemiSphere(1);
	ambientLightPtr = new AmbientWithOccluder(white, 1, 0.1, ambientOcclusionSampler);
	//ambientLightPtr = new Ambient(white, 1);

	SphericalAreaLight *areaLight = new SphericalAreaLight(white, 3, Point3D(120, 100, -100), 100, true);
	AddLightToWorld(areaLight);
}

void World::BuildBunnyWithAreaLight(void)
{
	Sphere *spherePtr;
	Plane *planePtr;
	Rectangle *rectanglePtr;
	Cube *cubePtr;

	Matte *mattePtr;
	Phong *phongPtr;
	Reflective *reflectivePtr;
	Transparent *transparentPtr;

	SVMatte *svMattePtr;
	SVTransparentEta * svTransparentPtr;

	Image *imagePtr;
	Texture *texturePtr;
	Mapping *mappingPtr;
	LatticeNoise* noisePtr;

	Grid* grid = new Grid();

	//ViewPlane
	int samples = 100;
	viewPlane.SetResolution(600, 600, 0.5);
	viewPlane.SetSampler(1, samples);

	//Camera
	Point3D eyePosition(0, 1.2, 0.7);
	Point3D lookAtPosition(-0.05, 0.03, 0);
	Vector3D upVector(0, 1, 0.25);
	float viewPlaneDistance = 1200;
	float rollAngle = 0;// -10; //-25; // Negative sign for clock-wise rotation

	cameraPtr = new PinHole(this, eyePosition, lookAtPosition, upVector, viewPlaneDistance, rollAngle);

	//Tracer
	tracerPtr = new WhittedTracer(this);
	//tracerPtr = new Project01Tracer(this);
	reflectionDepth = 5;

	//Background Color
	bgColor = white;

	//Objects
	//Phong Bunny

	phongPtr = new Phong(viewPlane.samplerPtr);
	phongPtr->SetAmbientBRDF(0.3, RGBColor(0, 0.47, 0.8));
	phongPtr->SetDiffuseBRDF(0.7, RGBColor(0, 0.47, 1));
	phongPtr->SetSpecularBRDF(1, RGBColor(1, 1, 1), 100);

	grid->ReadFlatTriangles("bun_zipper.ply");

	grid->SetMaterial(phongPtr);
	grid->ConstructCells();
	AddObjectToWorld(grid);

	//Planes

	//Floor Plane
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.3, RGBColor(0.8, 0.8, 0.8));
	mattePtr->SetDiffuseBRDF(0.7, RGBColor(1, 1, 1));

	planePtr = new Plane;
	//planePtr->SetPoint(Point3D(0, -0.06, 0));
	planePtr->SetPoint(Point3D(0, 0.03, 0));
	planePtr->SetNormal(0, 1, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Ceiling Plane
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.1, 0.1, 0.1));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.46));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 300, 0));
	planePtr->SetNormal(0, -1, 0);
	planePtr->materialPtr = mattePtr;
	//AddObjectToWorld(planePtr);


	Sampler *ambientOcclusionSampler = new JitteredSampler(samples);
	ambientOcclusionSampler->MapSamplesToHemiSphere(1);
	ambientLightPtr = new AmbientWithOccluder(white, 1, 0.1, ambientOcclusionSampler);
	//ambientLightPtr = new Ambient(white, 1);

	//PointLight *pointLight = new PointLight(white, 3, Point3D(-0.03, 0.6, 0), true);
	SphericalAreaLight *areaLight = new SphericalAreaLight(white, 3, Point3D(1.2, 1, 1), 1, true);
	//Point3D(120, 100, 100)
	AddLightToWorld(areaLight);
}

void World::BuildGlossyMaterial(void)
{
	Sphere *spherePtr;
	Plane *planePtr;
	Rectangle *rectanglePtr;
	Cube *cubePtr;

	Matte *mattePtr;
	Phong *phongPtr;
	Reflective *reflectivePtr;
	Transparent *transparentPtr;
	GlossyReflective *glossyPtr;

	SVMatte *svMattePtr;
	SVTransparentEta * svTransparentPtr;

	Image *imagePtr;
	Texture *texturePtr;
	Mapping *mappingPtr;
	LatticeNoise* noisePtr;

	Grid* grid = new Grid();

	//ViewPlane
	int samples = 100;
	viewPlane.SetResolution(600, 600, 0.5);
	viewPlane.SetSampler(1, samples);

	//Camera
	Point3D eyePosition(120, 100, -500);
	Point3D lookAtPosition(100, 10, 1000);
	Vector3D upVector(0, 1, 0);
	float viewPlaneDistance = 400;
	float rollAngle = 0;// -10; //-25; // Negative sign for clock-wise rotation

	cameraPtr = new PinHole(this, eyePosition, lookAtPosition, upVector, viewPlaneDistance, rollAngle);

	//Tracer
	tracerPtr = new WhittedTracer(this);
	//tracerPtr = new Project01Tracer(this);
	reflectionDepth = 5;

	//Background Color
	bgColor = white;

	//Objects

	//Glossy Sphere
	float expVal = 1;
	Sampler *newSampler = new JitteredSampler(samples);
	newSampler->MapSamplesToHemiSphere(expVal);

	glossyPtr = new GlossyReflective(newSampler);
	glossyPtr->SetAmbientBRDF(0, RGBColor(0, 0.9, 0.09));
	glossyPtr->SetDiffuseBRDF(0, RGBColor(0, 1, 0.23));
	glossyPtr->SetSpecularBRDF(1, RGBColor(1, 1, 1), expVal);
	glossyPtr->SetPerfectSpecularBRDF(1, RGBColor(1.0, 1.0, 1.0));

	spherePtr = new Sphere;
	spherePtr->SetCenter(120, 40, 40);
	spherePtr->SetRadius(40);
	spherePtr->materialPtr = glossyPtr;
	AddObjectToWorld(spherePtr);

	//Matte sphere
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.3, RGBColor(1, 0.8, 0));
	mattePtr->SetDiffuseBRDF(0.7, RGBColor(1, 1, 0.16));

	spherePtr = new Sphere;
	spherePtr->SetCenter(160, 20, -20);
	spherePtr->SetRadius(20);
	spherePtr->materialPtr = mattePtr;
	AddObjectToWorld(spherePtr);

	//Phong Cube

	phongPtr = new Phong(viewPlane.samplerPtr);
	phongPtr->SetAmbientBRDF(0.3, RGBColor(0, 0.47, 0.8));
	phongPtr->SetDiffuseBRDF(0.7, RGBColor(0, 0.47, 1));
	phongPtr->SetSpecularBRDF(1, RGBColor(1, 1, 1), 100);

	cubePtr = new Cube(Point3D(20, 0, 0), Point3D(60, 60, 100));
	cubePtr->materialPtr = phongPtr;
	AddObjectToWorld(cubePtr);

	//Floor Plane
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.3, RGBColor(0.8, 0.8, 0.8));
	mattePtr->SetDiffuseBRDF(0.7, RGBColor(1, 1, 1));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(0, 1, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Ceiling Plane
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.1, 0.1, 0.1));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.46));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 300, 0));
	planePtr->SetNormal(0, -1, 0);
	planePtr->materialPtr = mattePtr;
	//AddObjectToWorld(planePtr);


	Sampler *ambientOcclusionSampler = new JitteredSampler(samples);
	ambientOcclusionSampler->MapSamplesToHemiSphere(1);
	ambientLightPtr = new AmbientWithOccluder(white, 1, 0.1, ambientOcclusionSampler);
	//ambientLightPtr = new Ambient(white, 1);

	SphericalAreaLight *areaLight = new SphericalAreaLight(white, 3, Point3D(120, 100, -100), 40, true);
	AddLightToWorld(areaLight);

	PointLight *pointLight = new PointLight(white, 3, Point3D(200, 200, -100), true);
	//AddLightToWorld(pointLight);
}

void World::BuildTranslucentTest(void)
{
	Sphere *spherePtr;
	Plane *planePtr;
	Rectangle *rectanglePtr;
	Cube *cubePtr;

	Matte *mattePtr;
	Phong *phongPtr;
	Reflective *reflectivePtr;
	Transparent *transparentPtr;
	Translucent * translucentPtr;
 
	SVMatte *svMattePtr;

	Image *imagePtr;
	Texture *texturePtr;
	Mapping *mappingPtr;
	LatticeNoise* noisePtr;

	Grid* grid = new Grid();

	//ViewPlane
	int samples = 100;
	viewPlane.SetResolution(600, 600, 0.5);
	viewPlane.SetSampler(1, samples);

	//Camera
	Point3D eyePosition(120, 280, -500);
	//Point3D lookAtPosition(160, 90, -100);
	Point3D lookAtPosition(80, 40, 0);
	Vector3D upVector(0, 1, 0);
	float viewPlaneDistance = 500;
	float rollAngle = 0;// -10; //-25; // Negative sign for clock-wise rotation

	cameraPtr = new PinHole(this, eyePosition, lookAtPosition, upVector, viewPlaneDistance, rollAngle);

	//Tracer
	tracerPtr = new WhittedTracer(this);
	//tracerPtr = new Project01Tracer(this);
	reflectionDepth = 5;

	//Background Color
	bgColor = white;

	//Objects

	//Transparent cube
	Sampler *newSampler = new JitteredSampler(samples);
	newSampler->MapSamplesToHemiSphere(10000);
	translucentPtr = new Translucent(newSampler);
	translucentPtr->SetAmbientBRDF(0, RGBColor(1, 0.09, 0.09));
	translucentPtr->SetDiffuseBRDF(0, RGBColor(0, 1, 0.23));
	translucentPtr->SetSpecularBRDF(0.2, RGBColor(1, 1, 1), 2000);
	translucentPtr->SetPerfectSpecularBRDF(0.05, RGBColor(1.0, 1.0, 1.0));
	translucentPtr->SetTransparentProperties(0.95, 1);

	cubePtr = new Cube(Point3D(50, 120, -150), Point3D(125, 160, -90));
	cubePtr->materialPtr = translucentPtr;
	//AddObjectToWorld(cubePtr);

	rectanglePtr = new Rectangle(Point3D(170, 100, -200), Vector3D(-110, 0, 0), Vector3D(0, 70, 0));
	rectanglePtr->materialPtr = translucentPtr;
	AddObjectToWorld(rectanglePtr);

	//Phong Sphere

	phongPtr = new Phong(viewPlane.samplerPtr);
	phongPtr->SetAmbientBRDF(0.2, RGBColor(0, 0.8, 0.2));
	phongPtr->SetDiffuseBRDF(0.6, RGBColor(0, 1, 0));
	phongPtr->SetSpecularBRDF(0.4, RGBColor(1, 1, 1), 100);

	spherePtr = new Sphere(Point3D(100, 80, -95), 60);
	spherePtr->materialPtr = phongPtr;
	AddObjectToWorld(spherePtr);

	//Phong Sphere

	phongPtr = new Phong(viewPlane.samplerPtr);
	phongPtr->SetAmbientBRDF(0.2, RGBColor(0.8, 0.24, 0));
	phongPtr->SetDiffuseBRDF(0.6, RGBColor(1, 0.47, 0));
	phongPtr->SetSpecularBRDF(0.4, RGBColor(1, 1, 1), 100);

	spherePtr = new Sphere(Point3D(150, 80, -50), 100);
	spherePtr->materialPtr = phongPtr;
	//AddObjectToWorld(spherePtr);

	//Phong Cube

	phongPtr = new Phong(viewPlane.samplerPtr);
	phongPtr->SetAmbientBRDF(0.2, RGBColor(0, 0.79, 0.8));
	phongPtr->SetDiffuseBRDF(0.6, RGBColor(0, 0.47, 1));
	phongPtr->SetSpecularBRDF(0.4, RGBColor(1, 1, 1), 100);

	cubePtr = new Cube(Point3D(20, 20, -400), Point3D(60, 80, -250));
	cubePtr->materialPtr = phongPtr;
	AddObjectToWorld(cubePtr);

	//Compound Object - Cylinder

	CompoundObject *compoundObject = new CompoundObject();

	// OpenCylinder
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.25, RGBColor(1.0, 1.0, 0.5));
	mattePtr->SetDiffuseBRDF(0.75, RGBColor(1.0, 1.0, 0.5));

	OpenCylinder *openCylinder = new OpenCylinder(30, 80, 140);
	openCylinder->materialPtr = mattePtr;
	compoundObject->AddObject(openCylinder);
	AddObjectToWorld(openCylinder);

	//Floor Plane
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.1, 0.1, 0.1));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.46));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(0, 1, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Ceiling Plane
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.1, 0.1, 0.1));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.46));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 500, 0));
	planePtr->SetNormal(0, -1, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Wall one
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(1, 0, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Wall two
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(0, 0, -1);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Wall three
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, -700));
	planePtr->SetNormal(0, 0, 1);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Wall four
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(400, 0, 0));
	planePtr->SetNormal(-1, 0, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//ambientLightPtr = new Ambient(white, 1);

	//PointLight *pointLight = new PointLight(white, 6, Point3D(200, 200, -100), true);
	//AddLightToWorld(pointLight);

	Sampler *ambientOcclusionSampler = new JitteredSampler(samples);
	ambientOcclusionSampler->MapSamplesToHemiSphere(1);
	ambientLightPtr = new AmbientWithOccluder(white, 1, 0.1, ambientOcclusionSampler);
	//ambientLightPtr = new Ambient(white, 1);

	SphericalAreaLight *areaLight = new SphericalAreaLight(white, 6, Point3D(300, 400, -300), 60, true);
	AddLightToWorld(areaLight);

	std::cout << "\nBuildWorldTest\n";
}

void World::BuildEnvironmentLightTest(void)
{
	Sphere *spherePtr;
	Plane *planePtr;
	Rectangle *rectanglePtr;
	Cube *cubePtr;

	Matte *mattePtr;
	Phong *phongPtr;
	Reflective *reflectivePtr;
	Transparent *transparentPtr;
	Emissive *emissivePtr;

	SVMatte *svMattePtr;
	SVTransparentEta * svTransparentPtr;

	Image *imagePtr;
	Texture *texturePtr;
	Mapping *mappingPtr;
	LatticeNoise* noisePtr;

	Grid* grid = new Grid();

	//ViewPlane
	int samples = 100;
	viewPlane.SetResolution(500, 400, 0.5);
	viewPlane.SetSampler(1, samples);

	//Camera
	Point3D eyePosition(400, 150, -500);
	Point3D lookAtPosition(20, 20, 250);
	Vector3D upVector(0, 1, 0);
	float viewPlaneDistance = 550;
	float rollAngle = 0;// -10; //-25; // Negative sign for clock-wise rotation

	cameraPtr = new PinHole(this, eyePosition, lookAtPosition, upVector, viewPlaneDistance, rollAngle);

	//Tracer
	tracerPtr = new PathTracer(this);
	//tracerPtr = new WhittedTracer(this);
	//tracerPtr = new Project01Tracer(this);
	reflectionDepth = 5;

	//Objects

	//Globe
	imagePtr = new Image();
	imagePtr->ReadPPMFile("GreenAndYellow.ppm");

	mappingPtr = new SphericalMapping();

	texturePtr = new ImageTexture(imagePtr, mappingPtr);

	svMattePtr = new SVMatte(viewPlane.samplerPtr);
	svMattePtr->SetAmbientBRDF(0.8, texturePtr);
	svMattePtr->SetDiffuseBRDF(0, texturePtr);

	spherePtr = new Sphere;
	spherePtr->SetCenter(160, 40, 40);
	spherePtr->SetRadius(40);
	spherePtr->materialPtr = svMattePtr;
	//spherePtr->SetColor(0.25, 0.41, 0.88);
	//AddObjectToWorld(spherePtr);

	//Matte sphere
	Sampler *materialSampler = new JitteredSampler(samples);
	mattePtr = new Matte(materialSampler);
	mattePtr->SetAmbientBRDF(0.3, RGBColor(0.15, 0.8, 0));
	mattePtr->SetDiffuseBRDF(0.7, RGBColor(0.2, 0.9, 0.3));

	spherePtr = new Sphere;
	spherePtr->SetCenter(140, 40, 40);
	spherePtr->SetRadius(40);
	spherePtr->materialPtr = mattePtr;
	AddObjectToWorld(spherePtr);

	//Matte sphere
	materialSampler = new JitteredSampler(samples);
	mattePtr = new Matte(materialSampler);
	mattePtr->SetAmbientBRDF(0.3, RGBColor(0.8, 0.1, 0.1));
	mattePtr->SetDiffuseBRDF(0.7, RGBColor(1, 0.2, 0.3));

	spherePtr = new Sphere;
	spherePtr->SetCenter(90, 20, 0);
	spherePtr->SetRadius(20);
	spherePtr->materialPtr = mattePtr;
	AddObjectToWorld(spherePtr);

	//Matte Cube
	materialSampler = new JitteredSampler(samples);
	mattePtr = new Matte(materialSampler);
	mattePtr->SetAmbientBRDF(0.3, RGBColor(0, 0.47, 0.8));
	mattePtr->SetDiffuseBRDF(0.7, RGBColor(0, 0.47, 1));

	cubePtr = new Cube(Point3D(20, 0, 0), Point3D(60, 60, 45));
	cubePtr->materialPtr = mattePtr;
	AddObjectToWorld(cubePtr);

	//Matte Cube
	materialSampler = new JitteredSampler(samples);
	mattePtr = new Matte(materialSampler);
	mattePtr->SetAmbientBRDF(0.3, RGBColor(0, 0.47, 0.8));
	mattePtr->SetDiffuseBRDF(0.7, RGBColor(1, 1, 1));

	cubePtr = new Cube(Point3D(-20, 0, 60), Point3D(220, 120, 100));
	cubePtr->materialPtr = mattePtr;
	AddObjectToWorld(cubePtr);

	//Floor Plane
	materialSampler = new JitteredSampler(samples);
	mattePtr = new Matte(materialSampler);
	mattePtr->SetAmbientBRDF(0.3, RGBColor(1, 1, 1));
	mattePtr->SetDiffuseBRDF(0.7, RGBColor(1, 1, 1));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(0, 1, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	Sampler *ambientOcclusionSampler = new JitteredSampler(samples);
	ambientOcclusionSampler->MapSamplesToHemiSphere(1);
	ambientLightPtr = new AmbientWithOccluder(white, 1, 0.1, ambientOcclusionSampler);
	//ambientLightPtr = new Ambient(white, 1);

	//Background Color
	bgColor = RGBColor(1,0,0);

	emissivePtr = new Emissive(1, RGBColor(1, 1, 1));

	DomeSphere *domespherePtr = new DomeSphere;
	domespherePtr->SetCenter(0, 0, 0);
	domespherePtr->SetRadius(1000000);
	domespherePtr->materialPtr = emissivePtr;
	AddObjectToWorld(domespherePtr);

	Sampler *envLightSampler = new JitteredSampler(samples);
	envLightSampler->MapSamplesToHemiSphere(1);
	EnvironmentLight *envLight = new EnvironmentLight(envLightSampler, emissivePtr, true);
	AddLightToWorld(envLight);

	//SphericalAreaLight *areaLight = new SphericalAreaLight(white, 3, Point3D(120, 100, -100), 100, true);
	//AddLightToWorld(areaLight);
}

void World::BuildAmbientOcclusionWithSphere(void)
{
	Sphere *spherePtr;
	Plane *planePtr;
	Rectangle *rectanglePtr;
	Cube *cubePtr;

	Matte *mattePtr;
	Phong *phongPtr;
	Reflective *reflectivePtr;
	Transparent *transparentPtr;
	Emissive *emissivePtr;

	SVMatte *svMattePtr;
	SVTransparentEta * svTransparentPtr;

	Image *imagePtr;
	Texture *texturePtr;
	Mapping *mappingPtr;
	LatticeNoise* noisePtr;

	Grid* grid = new Grid();

	//ViewPlane
	int samples = 64;
	viewPlane.SetResolution(500, 400, 0.5);
	viewPlane.SetSampler(1, samples);

	//Camera
	//Point3D eyePosition(10, 50, -150);
	Point3D eyePosition(1, 300, -1);
	Point3D lookAtPosition(0, 40, 0);
	Vector3D upVector(0, 1, 0);
	//float viewPlaneDistance = 100;
	float viewPlaneDistance = 300;
	float rollAngle = 0;// -10; //-25; // Negative sign for clock-wise rotation

	cameraPtr = new PinHole(this, eyePosition, lookAtPosition, upVector, viewPlaneDistance, rollAngle);

	//Tracer
	//tracerPtr = new PathTracer(this);
	tracerPtr = new WhittedTracer(this);
	//tracerPtr = new Project01Tracer(this);
	reflectionDepth = 5;

	//Objects


	//Matte sphere
	Sampler *materialSampler = new JitteredSampler(samples);
	mattePtr = new Matte(materialSampler);
	mattePtr->SetAmbientBRDF(1, RGBColor(1, 0.2, 0.3));
	mattePtr->SetDiffuseBRDF(0, RGBColor(1, 0.2, 0.3));

	spherePtr = new Sphere;
	spherePtr->SetCenter(0, 40, 0);
	spherePtr->SetRadius(40);
	spherePtr->materialPtr = mattePtr;
	AddObjectToWorld(spherePtr);


	//Floor Plane
	materialSampler = new JitteredSampler(samples);
	mattePtr = new Matte(materialSampler);
	mattePtr->SetAmbientBRDF(1, RGBColor(1, 1, 1));
	mattePtr->SetDiffuseBRDF(0, RGBColor(1, 1, 1));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(0, 1, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	Sampler *ambientOcclusionSampler = new JitteredSampler(samples);
	ambientOcclusionSampler->MapSamplesToHemiSphere(1);
	ambientLightPtr = new AmbientWithOccluder(white, 1, 0.1, ambientOcclusionSampler);
	//ambientLightPtr = new Ambient(white, 1);

	//Background Color
	bgColor = RGBColor(1, 0, 0);

	emissivePtr = new Emissive(1, RGBColor(1, 1, 1));

	DomeSphere *domespherePtr = new DomeSphere;
	domespherePtr->SetCenter(0, 0, 0);
	domespherePtr->SetRadius(1000);
	//domespherePtr->SetRadius(1000000);
	domespherePtr->materialPtr = emissivePtr;
	AddObjectToWorld(domespherePtr);

	Sampler *envLightSampler = new JitteredSampler(samples);
	envLightSampler->MapSamplesToHemiSphere(1);
	EnvironmentLight *envLight = new EnvironmentLight(envLightSampler, emissivePtr, true);
	//AddLightToWorld(envLight);

	//SphericalAreaLight *areaLight = new SphericalAreaLight(white, 3, Point3D(120, 100, -100), 100, true);
	//AddLightToWorld(areaLight);
}

void World::BuildCausticTest(void)
{
	Sphere *spherePtr;
	Plane *planePtr;
	Rectangle *rectanglePtr;
	Cube *cubePtr;

	Matte *mattePtr;
	Phong *phongPtr;
	Reflective *reflectivePtr;
	Transparent *transparentPtr;
	Emissive *emissivePtr;

	SVMatte *svMattePtr;
	SVTransparentEta * svTransparentPtr;

	Image *imagePtr;
	Texture *texturePtr;
	Mapping *mappingPtr;
	LatticeNoise* noisePtr;

	Grid* grid = new Grid();

	//ViewPlane
	int samples = 36;
	viewPlane.SetResolution(500, 400, 0.5);
	viewPlane.SetSampler(1, samples);

	//Camera
	Point3D eyePosition(0, 130, -300);
	Point3D lookAtPosition(0, 20, 0);
	Vector3D upVector(0, 1, 0);
	float viewPlaneDistance = 800;
	float rollAngle = 0;// -10; //-25; // Negative sign for clock-wise rotation

	cameraPtr = new PinHole(this, eyePosition, lookAtPosition, upVector, viewPlaneDistance, rollAngle);

	//Tracer
	tracerPtr = new PathTracer(this);
	//tracerPtr = new WhittedTracer(this);
	//tracerPtr = new Project01Tracer(this);
	reflectionDepth = 2;

	//Objects

	//Globe
	imagePtr = new Image();
	imagePtr->ReadPPMFile("GreenAndYellow.ppm");

	mappingPtr = new SphericalMapping();

	texturePtr = new ImageTexture(imagePtr, mappingPtr);

	svMattePtr = new SVMatte(viewPlane.samplerPtr);
	svMattePtr->SetAmbientBRDF(0.8, texturePtr);
	svMattePtr->SetDiffuseBRDF(0, texturePtr);

	spherePtr = new Sphere;
	spherePtr->SetCenter(160, 40, 40);
	spherePtr->SetRadius(40);
	spherePtr->materialPtr = svMattePtr;
	//spherePtr->SetColor(0.25, 0.41, 0.88);
	//AddObjectToWorld(spherePtr);

	//Reflective OpenCylinder

	reflectivePtr = new Reflective(viewPlane.samplerPtr);
	reflectivePtr->SetAmbientBRDF(0, RGBColor(0, 0.09, 0.9));
	reflectivePtr->SetDiffuseBRDF(0.4, RGBColor(1.0, 0.5, 0.25));
	reflectivePtr->SetSpecularBRDF(0, RGBColor(1, 1, 1), 1);
	reflectivePtr->SetPerfectSpecularBRDF(1, RGBColor(1.0, 0.5, 0.25));

	OpenCylinder *openCylinder = new OpenCylinder(30, 0, 50);
	openCylinder->materialPtr = reflectivePtr;
	AddObjectToWorld(openCylinder);

	//Matte sphere
	Sampler *materialSampler = new JitteredSampler(samples);
	mattePtr = new Matte(materialSampler);
	mattePtr->SetAmbientBRDF(0.3, RGBColor(0.15, 0.8, 0));
	mattePtr->SetDiffuseBRDF(0.7, RGBColor(0.2, 0.9, 0.3));

	spherePtr = new Sphere;
	spherePtr->SetCenter(140, 40, 40);
	spherePtr->SetRadius(40);
	spherePtr->materialPtr = mattePtr;
	//AddObjectToWorld(spherePtr);

	//Matte sphere
	materialSampler = new JitteredSampler(samples);
	mattePtr = new Matte(materialSampler);
	mattePtr->SetAmbientBRDF(0.3, RGBColor(0.8, 0.1, 0.1));
	mattePtr->SetDiffuseBRDF(0.7, RGBColor(1, 0.2, 0.3));

	spherePtr = new Sphere;
	spherePtr->SetCenter(90, 20, 0);
	spherePtr->SetRadius(20);
	spherePtr->materialPtr = mattePtr;
	//AddObjectToWorld(spherePtr);

	//Matte Cube
	materialSampler = new JitteredSampler(samples);
	mattePtr = new Matte(materialSampler);
	mattePtr->SetAmbientBRDF(0.3, RGBColor(0, 0.47, 0.8));
	mattePtr->SetDiffuseBRDF(0.7, RGBColor(1, 1, 1));

	cubePtr = new Cube(Point3D(-20, 0, 60), Point3D(220, 120, 100));
	cubePtr->materialPtr = mattePtr;
	//AddObjectToWorld(cubePtr);

	//Floor Plane
	materialSampler = new JitteredSampler(samples);
	mattePtr = new Matte(materialSampler);
	mattePtr->SetAmbientBRDF(0.3, RGBColor(1, 1, 1));
	mattePtr->SetDiffuseBRDF(0.7, RGBColor(1, 1, 1));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(0, 1, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	Sampler *ambientOcclusionSampler = new JitteredSampler(samples);
	ambientOcclusionSampler->MapSamplesToHemiSphere(1);
	ambientLightPtr = new AmbientWithOccluder(white, 1, 0.1, ambientOcclusionSampler);
	//ambientLightPtr = new Ambient(white, 1);

	//Background Color
	bgColor = RGBColor(1, 0, 0);

	emissivePtr = new Emissive(1, RGBColor(1, 1, 1));

	DomeSphere *domespherePtr = new DomeSphere;
	domespherePtr->SetCenter(0, 0, 0);
	domespherePtr->SetRadius(1000000);
	domespherePtr->materialPtr = emissivePtr;
	AddObjectToWorld(domespherePtr);

	Sampler *envLightSampler = new JitteredSampler(samples);
	envLightSampler->MapSamplesToHemiSphere(1);
	EnvironmentLight *envLight = new EnvironmentLight(envLightSampler, emissivePtr, true);
	AddLightToWorld(envLight);

	SphericalAreaLight *areaLight = new SphericalAreaLight(white, 3, Point3D(500, 100, -100), 100, true);
	//AddLightToWorld(areaLight);
}

void World::BuildAnimation01(void)
{
	Sphere *spherePtr;
	Plane *planePtr;
	Rectangle *rectanglePtr;
	Cube *cubePtr;

	Matte *mattePtr;
	Phong *phongPtr;
	Reflective *reflectivePtr;
	Transparent *transparentPtr;

	SVMatte *svMattePtr;
	SVTransparentEta * svTransparentPtr;

	Image *imagePtr;
	Texture *texturePtr;
	Mapping *mappingPtr;
	LatticeNoise* noisePtr;

	Grid* grid = new Grid();

	//ViewPlane
	int samples = 49;
	viewPlane.SetResolution(700, 500, 0.5);
	viewPlane.SetSampler(1, samples);

	//Camera
	Point3D eyePosition(120, 100, -500);
	//Point3D lookAtPosition(160, 90, -100);
	Point3D lookAtPosition(-100, 20, 1000);
	Vector3D upVector(0, 1, 0);
	float viewPlaneDistance = 300;
	float rollAngle = 0;// -10; //-25; // Negative sign for clock-wise rotation
	float focalPlaneDistance = 510;
	float lensRadius = 25;
	Sampler *lensSampler = new JitteredSampler(samples);

	cameraPtr = new DOFCamera(this, eyePosition, lookAtPosition, upVector, viewPlaneDistance, focalPlaneDistance, lensRadius, rollAngle, lensSampler);

	//Tracer
	tracerPtr = new WhittedTracer(this);
	reflectionDepth = 5;

	//Background Color
	bgColor = white;

	//Objects

	//Transparent rectangle

	imagePtr = new Image();
	imagePtr->ReadPPMFile("GreenAndYellow.ppm");

	mappingPtr = new RectangularMapping();

	texturePtr = new ImageTexture(imagePtr, mappingPtr);

	Image *normalMapPtr = new Image();
	//normalMapPtr->ReadPPMFile("SpiralNormal.ppm");
	normalMapPtr->ReadPPMFile("CheckerNormal.ppm");

	Texture *normalMapTexPtr = new ImageTexture(normalMapPtr, mappingPtr);

	svTransparentPtr = new SVTransparentEta(viewPlane.samplerPtr);
	svTransparentPtr->SetAmbientBRDF(0, texturePtr);
	svTransparentPtr->SetDiffuseBRDF(0, texturePtr);
	svTransparentPtr->SetNormalMap(normalMapTexPtr);
	svTransparentPtr->SetSpecularBRDF(0.2, RGBColor(1, 1, 1), 2000);
	svTransparentPtr->SetPerfectSpecularBRDF(0.05, RGBColor(1.0, 1.0, 1.0));
	svTransparentPtr->SetTransparentProperties(0.95, 1.005);

	rectanglePtr = new Rectangle(Point3D(190, 75, -100), Vector3D(-160, 0, 0), Vector3D(0, 120, 0));
	rectanglePtr->materialPtr = svTransparentPtr;
	//AddObjectToWorld(rectanglePtr);

	//Matte sphere
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.3, RGBColor(1, 0, 0));
	mattePtr->SetDiffuseBRDF(0.7, RGBColor(1, 0.12, 0.16));

	spherePtr = new Sphere;
	spherePtr->SetCenter(0, 70, 0);
	spherePtr->SetRadius(40);
	spherePtr->materialPtr = mattePtr;
	movingSphere = spherePtr;
	AddObjectToWorld(spherePtr);

	//Phong Cube
	phongPtr = new Phong(viewPlane.samplerPtr);
	phongPtr->SetAmbientBRDF(0.2, RGBColor(0, 0.79, 0.8));
	phongPtr->SetDiffuseBRDF(0.6, RGBColor(0, 0.47, 1));
	phongPtr->SetSpecularBRDF(0.4, RGBColor(1, 1, 1), 100);

	cubePtr = new Cube(Point3D(20, 0, 0), Point3D(60, 60, 100));
	cubePtr->materialPtr = phongPtr;
	AddObjectToWorld(cubePtr);

	//Floor Plane
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.1, 0.1, 0.1));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.46));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(0, 1, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Ceiling Plane
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.1, 0.1, 0.1));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.46));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 300, 0));
	planePtr->SetNormal(0, -1, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Wall one
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(1, 0, 0);
	planePtr->materialPtr = mattePtr;
	//AddObjectToWorld(planePtr);

	//Wall two
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(0, 0, -1);
	planePtr->materialPtr = mattePtr;
	//AddObjectToWorld(planePtr);

	//Wall three
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, -700));
	planePtr->SetNormal(0, 0, 1);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Wall four
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(400, 0, 0));
	planePtr->SetNormal(-1, 0, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	Sampler *ambientOcclusionSampler = new JitteredSampler(samples);
	ambientOcclusionSampler->MapSamplesToHemiSphere(1);
	ambientLightPtr = new AmbientWithOccluder(white, 1, 0.1, ambientOcclusionSampler);
	//ambientLightPtr = new Ambient(white, 1);

	SphericalAreaLight *areaLight = new SphericalAreaLight(white, 5, Point3D(70, 100, -50), 50, true);
	AddLightToWorld(areaLight);

	/*ambientLightPtr = new Ambient(white, 1);

	PointLight *pointLight = new PointLight(white, 3, Point3D(200, 200, -100), true);
	AddLightToWorld(pointLight);

	pointLight = new PointLight(white, 3, Point3D(300, 290, -75), true);
	AddLightToWorld(pointLight);*/

	frameCount = 36;

	std::cout << "\nBuildAnimation01\n";
}

void World::RenderAnimation01(unsigned char* pixMapFromMain)
{
	//pixmap = new unsigned char[viewPlane.width * viewPlane.height * 3];
	pixmap = pixMapFromMain;
	Image *outImage = new Image();
	
	char newFileName[12];
	char *frameNumber;

	for (int i = 0; i < frameCount; i= i+1)
	{
		std::cout << "Rendering Frame " << i << "\n";
		
		float normalizedFrame = (float) i / (frameCount);

		float theta = -(normalizedFrame * 2 * pi);

		//std::cout << "normalizedFrame: " << normalizedFrame << "\n";
		std::cout << "theta: " << (theta * 180) * invPi << "\n";

		float newX = 160 * cos(theta);
		float newY = movingSphere->center.y;
		float newZ = 160 * sin(theta);
		movingSphere->SetCenter(newX, newY, newZ);

		movingSphere->center.PrintValues();

		cameraPtr->RenderScene();

		strcpy(newFileName, "Frame");

		frameNumber = itoa(i, 10);
		strcat(newFileName, frameNumber);


		strcat(newFileName, ".ppm");

		outImage->WritePPMFile(newFileName, pixmap, viewPlane.width, viewPlane.height);
	}
}

void World::BuildAnimation02(void)
{
	Sphere *spherePtr;
	Plane *planePtr;
	Rectangle *rectanglePtr;
	Cube *cubePtr;

	Matte *mattePtr;
	Phong *phongPtr;
	Reflective *reflectivePtr;
	Transparent *transparentPtr;

	SVMatte *svMattePtr;
	SVTransparentEta * svTransparentPtr;

	Image *imagePtr;
	Texture *texturePtr;
	Mapping *mappingPtr;
	LatticeNoise* noisePtr;

	Grid* grid = new Grid();

	//ViewPlane
	int samples = 16;
	viewPlane.SetResolution(1000, 540, 0.5);
	viewPlane.SetSampler(1, samples);

	//Camera
	Point3D eyePosition(120, 95, -500);
	//Point3D lookAtPosition(160, 90, -100);
	Point3D lookAtPosition(100, -25, 1000);
	Vector3D upVector(0, 1, 0);
	float viewPlaneDistance = 700;
	float rollAngle = 0;// -10; //-25; // Negative sign for clock-wise rotation
	//float focalPlaneDistance = 510;
	//float lensRadius = 25;
	//Sampler *lensSampler = new JitteredSampler(samples);

	cameraPtr = new PinHole(this, eyePosition, lookAtPosition, upVector, viewPlaneDistance, rollAngle);
	//cameraPtr = new DOFCamera(this, eyePosition, lookAtPosition, upVector, viewPlaneDistance, focalPlaneDistance, lensRadius, rollAngle, lensSampler);

	//Tracer
	tracerPtr = new WhittedTracer(this);
	reflectionDepth = 5;

	//Background Color
	bgColor = white;

	//Objects

	//Transparent rectangle

	imagePtr = new Image();
	imagePtr->ReadPPMFile("GreenAndYellow.ppm");

	mappingPtr = new RectangularMapping();

	texturePtr = new ImageTexture(imagePtr, mappingPtr);

	Image *normalMapPtr = new Image();
	//normalMapPtr->ReadPPMFile("SpiralNormal.ppm");
	normalMapPtr->ReadPPMFile("CheckerNormal.ppm");

	Texture *normalMapTexPtr = new ImageTexture(normalMapPtr, mappingPtr);

	svTransparentPtr = new SVTransparentEta(viewPlane.samplerPtr);
	svTransparentPtr->SetAmbientBRDF(0, texturePtr);
	svTransparentPtr->SetDiffuseBRDF(0, texturePtr);
	svTransparentPtr->SetNormalMap(normalMapTexPtr);
	svTransparentPtr->SetSpecularBRDF(0.2, RGBColor(1, 1, 1), 2000);
	svTransparentPtr->SetPerfectSpecularBRDF(0.05, RGBColor(1.0, 1.0, 1.0));
	svTransparentPtr->SetTransparentProperties(0.95, 1.005);

	rectanglePtr = new Rectangle(Point3D(190, -5, -100), Vector3D(-160, 0, 0), Vector3D(0, 120, 0));
	rectanglePtr->materialPtr = svTransparentPtr;
	AddObjectToWorld(rectanglePtr);

	//Matte sphere
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.3, RGBColor(1, 0, 0));
	mattePtr->SetDiffuseBRDF(0.7, RGBColor(1, 0.12, 0.16));

	spherePtr = new Sphere;
	spherePtr->SetCenter(160, 40, 100);
	spherePtr->SetRadius(40);
	spherePtr->materialPtr = mattePtr;
	movingSphere = spherePtr;
	//AddObjectToWorld(spherePtr);

	//Compound Object - Cylinder

	CompoundObject *compoundObject = new CompoundObject();

	// OpenCylinder
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.25, RGBColor(1.0, 1.0, 0.5));
	mattePtr->SetDiffuseBRDF(0.75, RGBColor(1.0, 1.0, 0.5));

	OpenCylinder *openCylinder = new OpenCylinder(30, 0, 123);
	openCylinder->materialPtr = mattePtr;
	compoundObject->AddObject(openCylinder);
	AddObjectToWorld(openCylinder);

	//Phong Cube
	phongPtr = new Phong(viewPlane.samplerPtr);
	phongPtr->SetAmbientBRDF(0.2, RGBColor(0, 0.79, 0.8));
	phongPtr->SetDiffuseBRDF(0.6, RGBColor(0, 0.47, 1));
	phongPtr->SetSpecularBRDF(0.4, RGBColor(1, 1, 1), 100);

	cubePtr = new Cube(Point3D(50, 0, 0), Point3D(90, 60, 100));
	cubePtr->materialPtr = phongPtr;
	AddObjectToWorld(cubePtr);


	//Phong Cube
	phongPtr = new Phong(viewPlane.samplerPtr);
	phongPtr->SetAmbientBRDF(0.2, RGBColor(0, 0.9, 0.1));
	phongPtr->SetDiffuseBRDF(0.6, RGBColor(0, 1, 0.2));
	phongPtr->SetSpecularBRDF(0.4, RGBColor(1, 1, 1), 100);

	cubePtr = new Cube(Point3D(180, 0, 0), Point3D(240, 70, 70));
	cubePtr->materialPtr = phongPtr;
	AddObjectToWorld(cubePtr);

	//Floor Plane
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.1, 0.1, 0.1));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.46));

	mattePtr->SetAmbientBRDF(0.3, RGBColor(0.8, 0.8, 0.8));
	mattePtr->SetDiffuseBRDF(0.7, RGBColor(1, 1, 1));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(0, 1, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Ceiling Plane
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.1, 0.1, 0.1));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.46));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 300, 0));
	planePtr->SetNormal(0, -1, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Wall one
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(1, 0, 0);
	planePtr->materialPtr = mattePtr;
	//AddObjectToWorld(planePtr);

	//Wall two
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(0, 0, -1);
	planePtr->materialPtr = mattePtr;
	//AddObjectToWorld(planePtr);

	//Wall three
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, -700));
	planePtr->SetNormal(0, 0, 1);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Wall four
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));
	mattePtr->SetAmbientBRDF(0.3, RGBColor(0.8, 0.8, 0.8));
	mattePtr->SetDiffuseBRDF(0.7, RGBColor(1, 1, 1));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(400, 0, 0));
	planePtr->SetNormal(-1, 0, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//ambientLightPtr = new Ambient(white, 1);

	Sampler *ambientOcclusionSampler = new JitteredSampler(samples);
	ambientOcclusionSampler->MapSamplesToHemiSphere(1);
	ambientLightPtr = new AmbientWithOccluder(white, 1, 0.1, ambientOcclusionSampler);

	PointLight *pointLight = new PointLight(white, 2, Point3D(200, 200, -100), true);
	AddLightToWorld(pointLight);

	pointLight = new PointLight(white, 2, Point3D(300, 290, -75), true);
	AddLightToWorld(pointLight);

	pointLight = new PointLight(white, 2, Point3D(-200, 290, -105), true);
	AddLightToWorld(pointLight);

	frameCount = 36;

	std::cout << "\nBuildAnimation02\n";
}

void World::RenderAnimation02(unsigned char* pixMapFromMain)
{
	//pixmap = new unsigned char[viewPlane.width * viewPlane.height * 3];
	pixmap = pixMapFromMain;
	Image *outImage = new Image();

	char newFileName[12];
	char *frameNumber;

	for (int i = 13; i < frameCount; i = i + 1)
	{
		std::cout << "Rendering Frame " << i << "\n";

		normalizedFrameVal = (float)i / (frameCount);

		cameraPtr->RenderScene();

		strcpy(newFileName, "Image");

		frameNumber = itoa(i, 10);
		strcat(newFileName, frameNumber);


		strcat(newFileName, ".ppm");

		outImage->WritePPMFile(newFileName, pixmap, viewPlane.width, viewPlane.height);
	}
}

void World::BuildAnimation03(void)
{
	Sphere *spherePtr;
	Plane *planePtr;
	Rectangle *rectanglePtr;
	Cube *cubePtr;

	Matte *mattePtr;
	Phong *phongPtr;
	Reflective *reflectivePtr;
	Transparent *transparentPtr;

	SVMatte *svMattePtr;
	SVTransparentEta * svTransparentPtr;

	Image *imagePtr;
	Texture *texturePtr;
	Mapping *mappingPtr;
	LatticeNoise* noisePtr;

	Grid* grid = new Grid();

	//ViewPlane
	int samples = 9;
	viewPlane.SetResolution(500, 540, 0.5);
	viewPlane.SetSampler(1, samples);

	//Camera
	Point3D eyePosition(120, 100, -500);
	Point3D lookAtPosition(-100, 20, 1000);
	Vector3D upVector(0, 1, 0);
	float viewPlaneDistance = 300;
	float separationAngle = 5;
	float imageInterval = 5;

	cameraPtr = new StereoCamera(this, eyePosition, lookAtPosition, upVector, viewPlaneDistance, separationAngle, imageInterval);

	//Tracer
	tracerPtr = new WhittedTracer(this);
	reflectionDepth = 5;

	//Background Color
	bgColor = white;

	//Objects

	//Transparent rectangle

	imagePtr = new Image();
	imagePtr->ReadPPMFile("GreenAndYellow.ppm");

	mappingPtr = new RectangularMapping();

	texturePtr = new ImageTexture(imagePtr, mappingPtr);

	Image *normalMapPtr = new Image();
	//normalMapPtr->ReadPPMFile("SpiralNormal.ppm");
	normalMapPtr->ReadPPMFile("CheckerNormal.ppm");

	Texture *normalMapTexPtr = new ImageTexture(normalMapPtr, mappingPtr);

	svTransparentPtr = new SVTransparentEta(viewPlane.samplerPtr);
	svTransparentPtr->SetAmbientBRDF(0, texturePtr);
	svTransparentPtr->SetDiffuseBRDF(0, texturePtr);
	svTransparentPtr->SetNormalMap(normalMapTexPtr);
	svTransparentPtr->SetSpecularBRDF(0.2, RGBColor(1, 1, 1), 2000);
	svTransparentPtr->SetPerfectSpecularBRDF(0.05, RGBColor(1.0, 1.0, 1.0));
	svTransparentPtr->SetTransparentProperties(0.95, 1.005);

	rectanglePtr = new Rectangle(Point3D(190, 75, -100), Vector3D(-160, 0, 0), Vector3D(0, 120, 0));
	rectanglePtr->materialPtr = svTransparentPtr;
	//AddObjectToWorld(rectanglePtr);

	//Matte sphere
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.3, RGBColor(1, 0, 0));
	mattePtr->SetDiffuseBRDF(0.7, RGBColor(1, 0.12, 0.16));

	spherePtr = new Sphere;
	spherePtr->SetCenter(0, 70, 0);
	spherePtr->SetRadius(40);
	spherePtr->materialPtr = mattePtr;
	movingSphere = spherePtr;
	AddObjectToWorld(spherePtr);

	//Phong Cube
	phongPtr = new Phong(viewPlane.samplerPtr);
	phongPtr->SetAmbientBRDF(0.2, RGBColor(0, 0.79, 0.8));
	phongPtr->SetDiffuseBRDF(0.6, RGBColor(0, 0.47, 1));
	phongPtr->SetSpecularBRDF(0.4, RGBColor(1, 1, 1), 100);

	cubePtr = new Cube(Point3D(20, 0, 0), Point3D(60, 60, 100));
	cubePtr->materialPtr = phongPtr;
	AddObjectToWorld(cubePtr);

	//Floor Plane
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.1, 0.1, 0.1));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.46));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(0, 1, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Ceiling Plane
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.1, 0.1, 0.1));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.46));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 300, 0));
	planePtr->SetNormal(0, -1, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Wall one
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(1, 0, 0);
	planePtr->materialPtr = mattePtr;
	//AddObjectToWorld(planePtr);

	//Wall two
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(0, 0, -1);
	planePtr->materialPtr = mattePtr;
	//AddObjectToWorld(planePtr);

	//Wall three
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, -700));
	planePtr->SetNormal(0, 0, 1);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Wall four
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(400, 0, 0));
	planePtr->SetNormal(-1, 0, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	ambientLightPtr = new Ambient(white, 1);

	PointLight *pointLight = new PointLight(white, 2, Point3D(200, 200, -100), true);
	AddLightToWorld(pointLight);

	pointLight = new PointLight(white, 2, Point3D(300, 290, -75), true);
	AddLightToWorld(pointLight);

	frameCount = 36;

	std::cout << "\nBuildAnimation03\n";
}

void World::RenderAnimation03(unsigned char* pixMapFromMain)
{
	pixmap = pixMapFromMain;
	Image *outImage = new Image();

	char newFileName[12];
	char *frameNumber;

	for (int i = 0; i < frameCount; i = i + 1)
	{
		std::cout << "Rendering Frame " << i << "\n";

		normalizedFrameVal = (float)i / (frameCount);

		float normalizedFrame = (float)i / (frameCount);

		float theta = -(normalizedFrame * 2 * pi);

		//std::cout << "normalizedFrame: " << normalizedFrame << "\n";
		std::cout << "theta: " << (theta * 180) * invPi << "\n";

		float newX = 160 * cos(theta);
		float newY = movingSphere->center.y;
		float newZ = 160 * sin(theta);
		movingSphere->SetCenter(newX, newY, newZ);

		movingSphere->center.PrintValues();

		cameraPtr->RenderScene();

		strcpy(newFileName, "Stereo");

		frameNumber = itoa(i, 10);
		strcat(newFileName, frameNumber);


		strcat(newFileName, ".ppm");

		outImage->WritePPMFile(newFileName, pixmap, viewPlane.width * 2 + 5, viewPlane.height);
	}
}

void World::BuildAnimation04(void)
{
	Sphere *spherePtr;
	Plane *planePtr;
	Rectangle *rectanglePtr;
	Cube *cubePtr;

	Matte *mattePtr;
	Phong *phongPtr;
	Reflective *reflectivePtr;
	Transparent *transparentPtr;

	SVMatte *svMattePtr;
	SVTransparentEta * svTransparentPtr;

	Image *imagePtr;
	Texture *texturePtr;
	Mapping *mappingPtr;
	LatticeNoise* noisePtr;

	Grid* grid = new Grid();

	//ViewPlane
	int samples = 4;
	viewPlane.SetResolution(960, 540, 0.5);
	viewPlane.SetSampler(1, samples);

	//Camera
	Point3D eyePosition(120, 100, -500);
	Point3D lookAtPosition(-100, 20, 1000);
	Vector3D upVector(0, 1, 0);
	float viewPlaneDistance = 600;

	Image *normalMapPtr = new Image();
	normalMapPtr->ReadPPMFile("NewNormalMap.ppm");
	mappingPtr = new RectangularMapping();
	Texture *normalMapTexPtr = new ImageTexture(normalMapPtr, mappingPtr);

	cameraPtr = new PaintCamera(this, eyePosition, lookAtPosition, upVector, viewPlaneDistance, normalMapTexPtr);

	//Tracer
	tracerPtr = new WhittedTracer(this);
	reflectionDepth = 5;

	//Background Color
	bgColor = white;

	//Objects

	//Matte sphere
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.3, RGBColor(1, 0, 0));
	mattePtr->SetDiffuseBRDF(0.7, RGBColor(1, 0.12, 0.16));

	spherePtr = new Sphere;
	spherePtr->SetCenter(0, 70, 0);
	spherePtr->SetRadius(40);
	spherePtr->materialPtr = mattePtr;
	movingSphere = spherePtr;
	AddObjectToWorld(spherePtr);

	//Matte sphere
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.3, RGBColor(0.05, 0.3, 0.8));
	mattePtr->SetDiffuseBRDF(0.7, RGBColor(0.12, 0.4, 1));

	spherePtr = new Sphere;
	spherePtr->SetCenter(-45, 100, 50);
	spherePtr->SetRadius(50);
	spherePtr->materialPtr = mattePtr;
	movingSphere = spherePtr;
	AddObjectToWorld(spherePtr);

	//Matte sphere
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.3, RGBColor(0, 1, 0));
	mattePtr->SetDiffuseBRDF(0.7, RGBColor(0.12, 1, 0.16));

	spherePtr = new Sphere;
	spherePtr->SetCenter(130, 70, 50);
	spherePtr->SetRadius(50);
	spherePtr->materialPtr = mattePtr;
	movingSphere = spherePtr;
	AddObjectToWorld(spherePtr);

	//Matte sphere
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.3, RGBColor(0.7, 0.4, 0.1));
	mattePtr->SetDiffuseBRDF(0.7, RGBColor(1, 0.5, 0.16));

	spherePtr = new Sphere;
	spherePtr->SetCenter(175, 90, 85);
	spherePtr->SetRadius(40);
	spherePtr->materialPtr = mattePtr;
	movingSphere = spherePtr;
	AddObjectToWorld(spherePtr);

	//Phong Cube
	phongPtr = new Phong(viewPlane.samplerPtr);
	phongPtr->SetAmbientBRDF(0.2, RGBColor(0, 0.79, 0.8));
	phongPtr->SetDiffuseBRDF(0.6, RGBColor(0, 0.47, 1));
	phongPtr->SetSpecularBRDF(0.4, RGBColor(1, 1, 1), 100);

	cubePtr = new Cube(Point3D(20, 0, 0), Point3D(60, 60, 100));
	cubePtr->materialPtr = phongPtr;
	AddObjectToWorld(cubePtr);

	//Floor Plane
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.1, 0.1, 0.1));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.46));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(0, 1, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Ceiling Plane
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.1, 0.1, 0.1));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.46));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 300, 0));
	planePtr->SetNormal(0, -1, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Wall one
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(1, 0, 0);
	planePtr->materialPtr = mattePtr;
	//AddObjectToWorld(planePtr);

	//Wall two
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, 0));
	planePtr->SetNormal(0, 0, -1);
	planePtr->materialPtr = mattePtr;
	//AddObjectToWorld(planePtr);

	//Wall three
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(0, 0, -700));
	planePtr->SetNormal(0, 0, 1);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	//Wall four
	mattePtr = new Matte(viewPlane.samplerPtr);
	mattePtr->SetAmbientBRDF(0.4, RGBColor(0.08, 0.1, 0.08));
	mattePtr->SetDiffuseBRDF(0.6, RGBColor(0.61, 0.42, 0.26));

	planePtr = new Plane;
	planePtr->SetPoint(Point3D(400, 0, 0));
	planePtr->SetNormal(-1, 0, 0);
	planePtr->materialPtr = mattePtr;
	AddObjectToWorld(planePtr);

	ambientLightPtr = new Ambient(white, 1);

	PointLight *pointLight = new PointLight(white, 2, Point3D(200, 200, -100), true);
	AddLightToWorld(pointLight);

	pointLight = new PointLight(white, 2, Point3D(300, 290, -75), true);
	AddLightToWorld(pointLight);

	frameCount = 36;

	std::cout << "\nBuildAnimation04\n";
}

void World::RenderAnimation04(unsigned char* pixMapFromMain)
{
	pixmap = pixMapFromMain;
	Image *outImage = new Image();

	char newFileName[14];
	char *frameNumber;

	for (int i = 0; i < frameCount; i = i + 1)
	{
		std::cout << "Rendering Frame " << i << "\n";

		normalizedFrameVal = (float)i / (frameCount);

		normalizedFrameVal +=1;

		cameraPtr->RenderScene();

		strcpy(newFileName, "Painting");

		frameNumber = itoa(i, 10);
		strcat(newFileName, frameNumber);


		strcat(newFileName, ".ppm");

		outImage->WritePPMFile(newFileName, pixmap, viewPlane.width, viewPlane.height);
	}
}

char* World::itoa(int Value, int Base)

{
	int n = Value;
	int arrayLength = 1;

	while (n / Base > 0)
	{
		arrayLength++;
		n = n / Base;
	}
	char* outputArray = new char[arrayLength];
	int tempLength = arrayLength;

	int estimatedValue;
	while (tempLength > 0)
	{
		estimatedValue = Value % Base;

		if (Base == 16 && estimatedValue > 9)
		{
			estimatedValue += 55;
		}
		else
		{
			estimatedValue += 48;
		}
		outputArray[tempLength - 1] = estimatedValue;
		Value = Value / Base;
		--tempLength;
	}
	outputArray[arrayLength] = '\0';
	return outputArray;
}

void World::ConstructFrame(unsigned char* pixMapFromMain)
{
	pixmap = pixMapFromMain;
	cameraPtr->RenderScene();
}

ShadeRecord World::MultipleObjectsHitFunction(const Ray& ray)
{
	ShadeRecord sr;
	sr.worldPtr = this;
	double t;
	double tMin = kMaxValue;
	int objectCount = objectsInScene.size();
	Vector3D tempNormal;
	Point3D tempPoint;

	for (int i = 0; i < objectCount; i++)
	{
		if (objectsInScene[i]->hit(ray, t, sr) == true && t < tMin)
		{
			sr.materialPtr = objectsInScene[i]->materialPtr;
			sr.color = objectsInScene[i]->color;
			sr.objectHit = true;
			//Backup of values of object with least t - so that we can add this to the shade record eventually after all the objects are checked for intersection
			tMin = t;
			tempNormal = sr.normal;	
			tempPoint = sr.hitPoint;
		}
	}

	if (sr.objectHit == true)
	{
		sr.t = tMin;
		sr.normal = tempNormal;
		sr.hitPoint = tempPoint;
	}

	return sr;
}

