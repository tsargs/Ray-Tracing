#ifndef MESHTRIANGLE
#define MESHTRIANGLE

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 03/27/16.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "GeometricObject.h"
#include "Mesh.h"

class MeshTriangle:public GeometricObject
{
	public:
		
		Mesh *meshPtr;
		int i0, i1, i2;
		Vector3D normal;

		BBox bBox;

		//Constructors

		MeshTriangle(void);												//Default Constructor
		
		//Destructor

		~MeshTriangle(void);

		//Member Functions

		virtual bool hit(const Ray& ray, double& tMin, ShadeRecord& sr) const;					//Hit function which checks for ray intersections
		bool ShadowHit(const Ray& ray, double& tMin) const;
		void ComputeNormal(const bool& inverseNormal);
		void UpdateBoundingBox(void);
		BBox GetBoundingBox(void);
};

#endif
