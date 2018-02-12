// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 03/27/16.
//  Copyright © 2016 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Grid.h"

//Default Constructor
Grid::Grid(void)
{
}

//Destructor
Grid::~Grid(void)
{

}

BBox Grid::GetBoundingBox(void)
{
	return boundingBox;
}

void Grid::ReadFlatTriangles(char* fileName)
{
	ReadPLYTriangles(fileName, 0);
}

void Grid::ReadSmoothTriangles(char* fileName)
{

}

void Grid::ReadPLYTriangles(char* fileName, int triangleType)
{
	meshPtr = new Mesh();

	typedef struct Vertex
	{
		float x, y, z;
	}Vertex;

	typedef struct Face
	{
		unsigned char vertexCount;
		int *vertices;
	}Face;

	PlyProperty vertexProperty[] = {
										{ "x", PLY_FLOAT, PLY_FLOAT, offsetof(Vertex, x), 0, 0, 0, 0 },
										{ "y", PLY_FLOAT, PLY_FLOAT, offsetof(Vertex, y), 0, 0, 0, 0 },
										{ "z", PLY_FLOAT, PLY_FLOAT, offsetof(Vertex, z), 0, 0, 0, 0 }
									};

	PlyProperty faceProperty[] = {
									{ "vertex_indices", PLY_INT, PLY_INT, offsetof(Face, vertices), 1, PLY_UCHAR, PLY_UCHAR, offsetof(Face, vertexCount) }
								};

	int elementCount;
	char** elementList;
	int fileType;
	float version;

	PlyFile *plyFile = ply_open_for_reading(fileName, &elementCount, &elementList, &fileType, &version);

	for (int i = 0; i < elementCount; i++)
	{
		char* elementName = elementList[i];

		int eachElementCount;
		int propertyCount;
		PlyProperty **propertyList = ply_get_element_description(plyFile, elementName, &eachElementCount, &propertyCount);

		std::cout << "Element: " << elementName << ", Count: " << eachElementCount << ", PropertiesCount: " << propertyCount << "\n";

		if (equal_strings(elementName, "vertex"))
		{
			meshPtr->vertexCount = eachElementCount;
			meshPtr->vertices.reserve(eachElementCount);

			meshPtr->facesShared.reserve(eachElementCount);	//The faces shared by each vertex
			vector<int> listOfFaces;	//Empty integer array
			for (int j = 0; j < 0; j++)
			{
				meshPtr->facesShared.push_back(listOfFaces);
			}

			ply_get_property(plyFile, elementName, &vertexProperty[0]);
			ply_get_property(plyFile, elementName, &vertexProperty[1]);
			ply_get_property(plyFile, elementName, &vertexProperty[2]);

			Vertex *vertex;
			for (int j = 0; j < eachElementCount; j++)
			{
				vertex = new Vertex();
				ply_get_element(plyFile, (void *)vertex);
				meshPtr->vertices.push_back(Point3D(vertex->x, vertex->y, vertex->z));
				delete vertex;
			}
		}

		if (equal_strings(elementName, "face"))
		{
			std::cout << "Here0\n";
			meshPtr->triangleCount = eachElementCount;
			objects.reserve(eachElementCount);

			ply_get_property(plyFile, elementName, &faceProperty[0]);

			Face *face;
			for (int j = 0; j < eachElementCount; j++)
			{
				face = new Face();
				ply_get_element(plyFile, (void *)face);

				if (triangleType == 0) //Flat mesh triangle
				{
					FlatMeshTriangle* triangle = new FlatMeshTriangle();
					triangle->i0 = face->vertices[0];
					triangle->i1 = face->vertices[1];
					triangle->i2 = face->vertices[2];
					triangle->meshPtr = meshPtr;
					triangle->ComputeNormal(false);
					triangle->UpdateBoundingBox();
					objects.push_back(triangle);
				}
				delete face;
			}
			

			if(triangleType == 0)
				meshPtr->facesShared.erase(meshPtr->facesShared.begin(), meshPtr->facesShared.end());	
		}
	}
	ply_close(plyFile);
}

//Definition of Hit function declared in the base class Geometric Object
bool Grid::hit(const Ray& ray, double& t, ShadeRecord& sr) const
{
	double t0, t1;

	double txMin, txMax; // upper and lower intersection point(x axis)
	double tyMin, tyMax; // upper and lower intersection point(y axis)
	double tzMin, tzMax; // upper and lower intersection point(z axis)

	double a = 1.0 / ray.rayDirection.x;
	double b = 1.0 / ray.rayDirection.y;
	double c = 1.0 / ray.rayDirection.z;

	Point3D minPoint = boundingBox.minPoint;
	Point3D maxPoint = boundingBox.maxPoint;

	if (a >= 0)
	{
		txMin = (minPoint.x - ray.origin.x) * a;
		txMax = (maxPoint.x - ray.origin.x) * a;
	}
	else
	{
		txMin = (maxPoint.x - ray.origin.x) * a;
		txMax = (minPoint.x - ray.origin.x) * a;
	}

	if (b >= 0)
	{
		tyMin = (minPoint.y - ray.origin.y) * b;
		tyMax = (maxPoint.y - ray.origin.y) * b;
	}
	else
	{
		tyMin = (maxPoint.y - ray.origin.y) * b;
		tyMax = (minPoint.y - ray.origin.y) * b;
	}

	if (c >= 0)
	{
		tzMin = (minPoint.z - ray.origin.z) * c;
		tzMax = (maxPoint.z - ray.origin.z) * c;
	}
	else
	{
		tzMin = (maxPoint.z - ray.origin.z) * c;
		tzMax = (minPoint.z - ray.origin.z) * c;
	}

	//Point of entry for the ray
	//Largest of tMin values

	t0 = (txMin > tyMin) ? txMin : tyMin;
	t0 = (tzMin > t0) ? tzMin : t0;

	//Point of exit for the ray
	//Smallest of tMax values
	t1 = (txMax < tyMax) ? txMax : tyMax;
	t1 = (tzMax < t1) ? tzMax : t1;

	if (t0 > t1)
		return false;

	Point3D p0 = boundingBox.minPoint;
	Point3D p1 = boundingBox.maxPoint;
	int ix, iy, iz;

	if (boundingBox.Inside(ray.origin))
	{
		ix = (ray.origin.x - p0.x) / (p1.x - p0.x) * nx;
		ix = ClampValue(ix, 0, nx - 1);

		iy = (ray.origin.y - p0.y) / (p1.y - p0.y) * ny;
		iy = ClampValue(iy, 0, ny - 1);

		iz = (ray.origin.z - p0.z) / (p1.z - p0.z) * nz;
		iz = ClampValue(iz, 0, nz - 1);
	}
	else
	{
		Point3D hitPoint = ray.origin + (ray.rayDirection * t0);

		ix = (hitPoint.x - p0.x) / (p1.x - p0.x) * nx;
		ix = ClampValue(ix, 0, nx - 1);

		iy = (hitPoint.y - p0.y) / (p1.y - p0.y) * ny;
		iy = ClampValue(iy, 0, ny - 1);

		iz = (hitPoint.z - p0.z) / (p1.z - p0.z) * nz;
		iz = ClampValue(iz, 0, nz - 1);
	}

	double dtx = (txMax - txMin) / nx;
	double dty = (tyMax - tyMin) / ny;
	double dtz = (tzMax - tzMin) / nz;

	double txNext, tyNext, tzNext;
	int ixStep, iyStep, izStep;
	int ixEnd, iyEnd, izEnd;

	if (ray.rayDirection.x > 0)
	{
		txNext = txMin + (ix + 1) * dtx;
		ixStep = 1;
		ixEnd = nx;
	}
	else if (ray.rayDirection.x == 0.0)
	{
		txNext = kMaxValue;
		ixStep = -1;
		ixEnd = -1;
	}
	else 
	{
		txNext = txMin + (nx - ix) * dtx;
		ixStep = -1;
		ixEnd = -1;
	}

	if (ray.rayDirection.y > 0)
	{
		tyNext = tyMin + (iy + 1) * dty;
		iyStep = 1;
		iyEnd = ny;
	}
	else if (ray.rayDirection.y == 0.0)
	{
		tyNext = kMaxValue;
		iyStep = -1;
		iyEnd = -1;
	}
	else
	{
		tyNext = tyMin + (ny - iy) * dty;
		iyStep = -1;
		iyEnd = -1;
	}


	if (ray.rayDirection.z > 0)
	{
		tzNext = tzMin + (iz + 1) * dtz;
		izStep = 1;
		izEnd = nz;
	}
	else if (ray.rayDirection.z == 0.0)
	{
		tzNext = kMaxValue;
		izStep = -1;
		izEnd = -1;
	}
	else
	{
		tzNext = tzMin + (nz - iz) * dtz;
		izStep = -1;
		izEnd = -1;
	}

	while (true)
	{
		int index = ix + (nx*iy) + (nx*ny*iz);
		GeometricObject *object = cells[index];

		if (txNext < tyNext && txNext < tzNext)
		{
			if (object != nullptr && object->hit(ray, t, sr) == true && t < txNext)
			{
				materialPtr = object->materialPtr;
				return true;
			}

			txNext += dtx;
			ix += ixStep;

			if (ix == ixEnd)
				return false;
		}
		else if(tyNext < tzNext)
		{
			if (object != nullptr && object->hit(ray, t, sr) == true && t < tyNext)
			{
				materialPtr = object->materialPtr;
				return true;
			}

			tyNext += dty;
			iy += iyStep;

			if (iy == iyEnd)
				return false;
		}
		else
		{
			if (object != nullptr && object->hit(ray, t, sr) == true && t < tzNext)
			{
				materialPtr = object->materialPtr;
				return true;
			}

			tzNext += dtz;
			iz += izStep;

			if (iz == izEnd)
				return false;
		}

	}
}

bool Grid::ShadowHit(const Ray& ray, double& t) const
{
	double t0, t1;

	double txMin, txMax; // upper and lower intersection point(x axis)
	double tyMin, tyMax; // upper and lower intersection point(y axis)
	double tzMin, tzMax; // upper and lower intersection point(z axis)

	double a = 1.0 / ray.rayDirection.x;
	double b = 1.0 / ray.rayDirection.y;
	double c = 1.0 / ray.rayDirection.z;

	Point3D minPoint = boundingBox.minPoint;
	Point3D maxPoint = boundingBox.maxPoint;

	if (a >= 0)
	{
		txMin = (minPoint.x - ray.origin.x) * a;
		txMax = (maxPoint.x - ray.origin.x) * a;
	}
	else
	{
		txMin = (maxPoint.x - ray.origin.x) * a;
		txMax = (minPoint.x - ray.origin.x) * a;
	}

	if (b >= 0)
	{
		tyMin = (minPoint.y - ray.origin.y) * b;
		tyMax = (maxPoint.y - ray.origin.y) * b;
	}
	else
	{
		tyMin = (maxPoint.y - ray.origin.y) * b;
		tyMax = (minPoint.y - ray.origin.y) * b;
	}

	if (c >= 0)
	{
		tzMin = (minPoint.z - ray.origin.z) * c;
		tzMax = (maxPoint.z - ray.origin.z) * c;
	}
	else
	{
		tzMin = (maxPoint.z - ray.origin.z) * c;
		tzMax = (minPoint.z - ray.origin.z) * c;
	}

	//Point of entry for the ray
	//Largest of tMin values

	t0 = (txMin > tyMin) ? txMin : tyMin;
	t0 = (tzMin > t0) ? tzMin : t0;

	//Point of exit for the ray
	//Smallest of tMax values
	t1 = (txMax < tyMax) ? txMax : tyMax;
	t1 = (tzMax < t1) ? tzMax : t1;

	if (t0 > t1)
		return false;

	Point3D p0 = boundingBox.minPoint;
	Point3D p1 = boundingBox.maxPoint;
	int ix, iy, iz;

	if (boundingBox.Inside(ray.origin))
	{
		ix = (ray.origin.x - p0.x) / (p1.x - p0.x) * nx;
		ix = ClampValue(ix, 0, nx - 1);

		iy = (ray.origin.y - p0.y) / (p1.y - p0.y) * ny;
		iy = ClampValue(iy, 0, ny - 1);

		iz = (ray.origin.z - p0.z) / (p1.z - p0.z) * nz;
		iz = ClampValue(iz, 0, nz - 1);
	}
	else
	{
		Point3D hitPoint = ray.origin + (ray.rayDirection * t0);

		ix = (hitPoint.x - p0.x) / (p1.x - p0.x) * nx;
		ix = ClampValue(ix, 0, nx - 1);

		iy = (hitPoint.y - p0.y) / (p1.y - p0.y) * ny;
		iy = ClampValue(iy, 0, ny - 1);

		iz = (hitPoint.z - p0.z) / (p1.z - p0.z) * nz;
		iz = ClampValue(iz, 0, nz - 1);
	}

	double dtx = (txMax - txMin) / nx;
	double dty = (tyMax - tyMin) / ny;
	double dtz = (tzMax - tzMin) / nz;

	double txNext, tyNext, tzNext;
	int ixStep, iyStep, izStep;
	int ixEnd, iyEnd, izEnd;

	if (ray.rayDirection.x > 0)
	{
		txNext = txMin + (ix + 1) * dtx;
		ixStep = 1;
		ixEnd = nx;
	}
	else if (ray.rayDirection.x == 0.0)
	{
		txNext = kMaxValue;
		ixStep = -1;
		ixEnd = -1;
	}
	else
	{
		txNext = txMin + (nx - ix) * dtx;
		ixStep = -1;
		ixEnd = -1;
	}

	if (ray.rayDirection.y > 0)
	{
		tyNext = tyMin + (iy + 1) * dty;
		iyStep = 1;
		iyEnd = ny;
	}
	else if (ray.rayDirection.y == 0.0)
	{
		tyNext = kMaxValue;
		iyStep = -1;
		iyEnd = -1;
	}
	else
	{
		tyNext = tyMin + (ny - iy) * dty;
		iyStep = -1;
		iyEnd = -1;
	}


	if (ray.rayDirection.z > 0)
	{
		tzNext = tzMin + (iz + 1) * dtz;
		izStep = 1;
		izEnd = nz;
	}
	else if (ray.rayDirection.z == 0.0)
	{
		tzNext = kMaxValue;
		izStep = -1;
		izEnd = -1;
	}
	else
	{
		tzNext = tzMin + (nz - iz) * dtz;
		izStep = -1;
		izEnd = -1;
	}

	while (true)
	{
		int index = ix + (nx*iy) + (nx*ny*iz);
		GeometricObject *object = cells[index];

		if (txNext < tyNext && txNext < tzNext)
		{
			if (object != nullptr && object->ShadowHit(ray, t) == true && t < txNext)
			{
				return true;
			}

			txNext += dtx;
			ix += ixStep;

			if (ix == ixEnd)
				return false;
		}
		else if (tyNext < tzNext)
		{
			if (object != nullptr && object->ShadowHit(ray, t) == true && t < tyNext)
			{
				materialPtr = object->materialPtr;
				return true;
			}

			tyNext += dty;
			iy += iyStep;

			if (iy == iyEnd)
				return false;
		}
		else
		{
			if (object != nullptr && object->ShadowHit(ray, t) == true && t < tzNext)
			{
				materialPtr = object->materialPtr;
				return true;
			}

			tzNext += dtz;
			iz += izStep;

			if (iz == izEnd)
				return false;
		}

	}
}

void Grid::ConstructCells(void)
{
	int objectCount = objects.size();
	float m = 2;

	Point3D p0 = GetMinPoint();
	Point3D p1 = GetMaxPoint();

	boundingBox.minPoint = p0;
	boundingBox.maxPoint = p1;

	float wx = p1.x - p0.x, wy = p1.y - p0.y, wz = p1.z - p0.z;
	float s = cbrt(wx*wy*wz / objectCount);

	nx = ((m*wx) / s) + 1;
	ny = ((m*wy) / s) + 1;
	nz = ((m*wz) / s) + 1;

	int cellCount = nx*ny*nz;

	cells.reserve(cellCount);
	std::vector<int> objCountPerCell;

	objCountPerCell.reserve(cellCount);

	for (int i = 0; i < cellCount; i++)
	{
		cells.push_back(nullptr);
		objCountPerCell.push_back(0);
	}
	
	for (int i = 0; i < objectCount; i++)
	{
		Point3D minPoint = objects[i]->GetBoundingBox().minPoint;
		Point3D maxPoint = objects[i]->GetBoundingBox().maxPoint;

		int ixMin = (minPoint.x - p0.x) / (p1.x - p0.x) * nx;
		ixMin = ClampValue(ixMin, 0, nx - 1);

		int ixMax = (maxPoint.x - p0.x) / (p1.x - p0.x) * nx;
		ixMax = ClampValue(ixMax, 0, nx - 1);

		int iyMin = (minPoint.y - p0.y) / (p1.y - p0.y) * ny;
		iyMin = ClampValue(iyMin, 0, ny - 1);

		int iyMax = (maxPoint.y - p0.y) / (p1.y - p0.y) * ny;
		iyMax = ClampValue(iyMax, 0, ny - 1);

		int izMin = (minPoint.z - p0.z) / (p1.z - p0.z) * nz;
		izMin = ClampValue(izMin, 0, nz - 1);

		int izMax = (maxPoint.z - p0.z) / (p1.z - p0.z) * nz;
		izMax = ClampValue(izMax, 0, nz - 1);

		for (int ix = ixMin; ix <= ixMax; ix++)
		{
			for (int iy = iyMin; iy <= iyMax; iy++)
			{
				for (int iz = izMin; iz <= izMax; iz++)
				{
					int index = ix + (nx*iy) + (nx*ny*iz);

					if (objCountPerCell[index] == 0)
					{
						cells[index] = objects[i];
					}
					else if (objCountPerCell[index] == 1)
					{
						CompoundObject *compound = new CompoundObject();
						compound->AddObject(cells[index]);
						compound->AddObject(objects[i]);

						cells[index] = compound;
					}
					else
					{
						cells[index]->AddObject(objects[i]);
					}

					objCountPerCell[index]++;
				}
			}
		}
	}

	objects.erase(objects.begin(), objects.end());
	objCountPerCell.erase(objCountPerCell.begin(), objCountPerCell.end());
}

Point3D Grid::GetMinPoint(void)
{
	int objectCount = objects.size();
	double x = kMaxValue, y = kMaxValue, z = kMaxValue;

	for (int i = 0; i < objectCount; i++)
	{
		Point3D tempPoint = objects[i]->GetBoundingBox().minPoint;
		x = (x > tempPoint.x) ? tempPoint.x : x;
		y = (y > tempPoint.y) ? tempPoint.y : y;
		z = (z > tempPoint.z) ? tempPoint.z : z;
	}

	x -= kEpsilon;
	y -= kEpsilon;
	z -= kEpsilon;

	return Point3D(x, y, z);
}

Point3D Grid::GetMaxPoint(void)
{
	int objectCount = objects.size();
	double x = -kMaxValue, y = -kMaxValue, z = -kMaxValue;

	for (int i = 0; i < objectCount; i++)
	{
		Point3D tempPoint = objects[i]->GetBoundingBox().maxPoint;
		x = (x < tempPoint.x) ? tempPoint.x : x;
		y = (y < tempPoint.y) ? tempPoint.y : y;
		z = (z < tempPoint.z) ? tempPoint.z : z;
	}

	x += kEpsilon;
	y += kEpsilon;
	z += kEpsilon;

	return Point3D(x, y, z);
}