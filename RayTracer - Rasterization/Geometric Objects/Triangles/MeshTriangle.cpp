// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 03/27/16.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "MeshTriangle.h"

//Default Constructor
MeshTriangle::MeshTriangle(void)
{

}

//Destructor
MeshTriangle::~MeshTriangle(void)
{

}

void MeshTriangle::UpdateBoundingBox(void)
{
	Point3D v0 = meshPtr->vertices[i0];
	Point3D v1 = meshPtr->vertices[i1];
	Point3D v2 = meshPtr->vertices[i2];

	Point3D tempPoint, minPoint, maxPoint;

	double x0 = kMaxValue, y0 = kMaxValue, z0 = kMaxValue;

	for (int i = 0; i < 3; i++)
	{
		if (i == 0)
			tempPoint = v0;
		if (i == 1)
			tempPoint = v1;
		if (i == 2)
			tempPoint = v2;

		x0 = (x0 > tempPoint.x) ? tempPoint.x : x0;
		y0 = (y0 > tempPoint.y) ? tempPoint.y : y0;
		z0 = (z0 > tempPoint.z) ? tempPoint.z : z0;
	}

	x0 -= kEpsilon;
	y0 -= kEpsilon;
	z0 -= kEpsilon;

	minPoint = Point3D(x0, y0, z0);

	double x1 = -kMaxValue, y1 = -kMaxValue, z1 = -kMaxValue;

	for (int i = 0; i < 3; i++)
	{
		if (i == 0)
			tempPoint = v0;
		if (i == 1)
			tempPoint = v1;
		if (i == 2)
			tempPoint = v2;

		x1 = (x1 < tempPoint.x) ? tempPoint.x : x1;
		y1 = (y1 < tempPoint.y) ? tempPoint.y : y1;
		z1 = (z1 < tempPoint.z) ? tempPoint.z : z1;
	}

	x1 += kEpsilon;
	y1 += kEpsilon;
	z1 += kEpsilon;

	maxPoint = Point3D(x1, y1, z1);

	bBox.minPoint = minPoint;
	bBox.maxPoint = maxPoint;
}

BBox MeshTriangle::GetBoundingBox(void)
{
	return bBox;
}

void MeshTriangle::ComputeNormal(const bool& inverseNormal)
{
	Point3D v0 = Point3D(meshPtr->vertices[i0]);
	Point3D v1 = Point3D(meshPtr->vertices[i1]);
	Point3D v2 = Point3D(meshPtr->vertices[i2]);

	normal = ((v1 - v0) ^ (v2 - v0)).UnitVector();

	if (inverseNormal)
		normal = -normal;
}

bool MeshTriangle::hit(const Ray & ray, double & tMin, ShadeRecord& sr) const
{
	return false;
}

bool MeshTriangle::ShadowHit(const Ray& ray, double& tMin) const
{
	Point3D v0 = Point3D(meshPtr->vertices[i0]);
	Point3D v1 = Point3D(meshPtr->vertices[i1]);
	Point3D v2 = Point3D(meshPtr->vertices[i2]);

	double a = v0.x - v1.x, b = v0.x - v2.x, c = ray.rayDirection.x, d = v0.x - ray.origin.x;
	double e = v0.y - v1.y, f = v0.y - v2.y, g = ray.rayDirection.y, h = v0.y - ray.origin.y;
	double i = v0.z - v1.z, j = v0.z - v2.z, k = ray.rayDirection.z, l = v0.z - ray.origin.z;

	double m = f*k - g*j, n = g*i - e*k, o = e*j - f*i;

	double denominator = a*m + b*n + c*o;
	double invDenominator = 1.0 / denominator;

	double p = g*l - h*k, q = h*j - f*l;
	double r = h*k - g*l, s = e*l - h*i;
	double t = f*l - h*j, u = h*i - e*l;

	double beta = (d*m + b*p + c*q) * invDenominator;

	if (beta < 0.0)
		return false;

	double gamma = (a*r + d*n + c*s) * invDenominator;

	if (gamma < 0.0 || beta + gamma > 1.0)
		return false;

	double tVal = (a*t + b*u + d*o) * invDenominator;

	if (tVal < kEpsilon)
		return false;

	tMin = tVal;

	return true;
}