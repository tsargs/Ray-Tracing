#ifndef GRID
#define GRID

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 03/27/16.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "CompoundObject.h"
#include "Mesh.h"
#include "FlatMeshTriangle.h"

#include "ply.h"

class Grid:public CompoundObject
{
	public:
		
		int nx, ny, nz;		//Number of cells in x,y and z direction
		std::vector<GeometricObject*> cells;
		BBox boundingBox;

		Mesh *meshPtr;

		//Constructors

		Grid(void);												//Default Constructor
		
		//Destructor

		~Grid(void);

		//Member Functions

		bool hit(const Ray& ray, double& tMin, ShadeRecord& sr) const;					//Hit function which checks for ray intersections
		bool ShadowHit(const Ray& ray, double& tMin) const;

		void ReadFlatTriangles(char* fileName);
		void ReadSmoothTriangles(char* fileName);
		void ReadPLYTriangles(char* fileName, int type);

		BBox GetBoundingBox(void);
		void ConstructCells(void);

		Point3D GetMinPoint(void);
		Point3D GetMaxPoint(void);

		float ClampValue(float value, float minVal, float maxVal) const;
};

inline float Grid::ClampValue(float value, float minVal, float maxVal) const
{
	return value > minVal ? ((value < maxVal) ? value : maxVal) : minVal;
}

#endif
