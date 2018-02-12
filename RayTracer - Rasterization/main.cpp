// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 12/30/15.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include <iostream>
#include <World.h>
#include <GL/glut.h>

int width, height;
unsigned char *pixmap;

static void windowResize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, (w / 2), 0, (h / 2), 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
static void windowDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glRasterPos2i(0, 0);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, pixmap);
	glFlush();
}
static void processMouse(int button, int state, int x, int y)
{
	if (state == GLUT_UP)
		exit(0);               // Exit on mouse click.
}
static void init(void)
{
	glClearColor(0, 0, 0, 1); // Set background color.
}

void DisplayProgress()
{
	glutPostRedisplay();
}

int main(void)
{
	width = 500;
	height = 400;
	pixmap = new unsigned char[width * height * 3];

	//Animation
	/*
	World world;
	std::cout << "------->	RAY TRACER - Animation	<-------\n";
	//world.BuildAnimation01();
	//world.RenderAnimation01(pixmap);
	//world.BuildAnimation02();
	//world.RenderAnimation02(pixmap);
	//world.BuildAnimation03();
	//world.RenderAnimation03(pixmap);
	world.BuildAnimation04();
	world.RenderAnimation04(pixmap);
	*/

	World world;
	std::cout << "------->	RAY TRACER	<-------\n";
	//world.BuildWorldProject01();
	//world.BuildWorldProject02();
	//world.BuildWorldProject03();
	//world.BuildWorldProject04();
	//world.BuildWorldProject05();
	//world.BuildWorldTest();
	//world.BuildGridTest();
	//world.BuildWorldWithBunny();
	//world.BuildWorldWithTetrahedron();
	//world.BuildWorldWithCube();
	//world.BuildWorldProject08();
	//world.BuildReflectiveBunny();
	//world.BuildReflectiveTetrahedron();
	//world.BuildNormalMapTest();
	//world.BuildWorldProject08WithNormalMap();
	//world.BuildWorldEnvironmentMap();
	//world.BuildWorldProject09();
	//world.BuildTransparentBunny();
	//world.BuildTransparentRectangle();
	//world.BuildTransparentRectangleSVEta();
	//world.BuildDOFTest();
	//world.BuildAmbientOcclusionTest();
	//world.BuildAreaLightTest();
	//world.BuildBunnyWithAreaLight();
	//world.BuildGlossyMaterial();
	//world.BuildTranslucentTest();
	//world.BuildEnvironmentLightTest();
	world.BuildAmbientOcclusionWithSphere();
	//world.BuildCausticTest();
	world.ConstructFrame(pixmap);

	//pixmap = world.pixmap;

	char fakeParam[] = "fake";
	char *fakeargv[] = { fakeParam, NULL };
	int fakeargc = 1;

	glutInit(&fakeargc, fakeargv);

	glutInitWindowPosition(100, 100); // Where the window will display on-screen.
	glutInitWindowSize(width, height);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutCreateWindow("Shyam Prathish - Image Synthesis");
	init();
	glutReshapeFunc(windowResize);
	glutDisplayFunc(windowDisplay);
	glutMouseFunc(processMouse);
	glutMainLoop();

	glutIdleFunc(DisplayProgress);

	glutIdleFunc(NULL);

	//std::cin.clear();
	//std::cin.ignore(1000, '\n');
	return 0;

}


