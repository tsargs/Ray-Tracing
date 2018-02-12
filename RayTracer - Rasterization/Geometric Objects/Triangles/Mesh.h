#ifndef MESH
#define MESH

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 03/27/16.
//  Copyright © 2016 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Point3D.h"
#include "Vector3D.h"

#include <vector>

using namespace std;

class Mesh
{
	public:

	vector <Point3D> vertices;
	int vertexCount;

	vector <int> indices;
	vector <Vector3D> normals;

	vector <vector <int>> facesShared;	//2-dimensional vector array

	vector<float> u;
	vector<float> v;

	int triangleCount;

	//Constructors
	Mesh(void);										//Default Constructor

	~Mesh(void);									//Destructor
};

#endif