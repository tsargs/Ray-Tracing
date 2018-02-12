#ifndef PROJECTIONMAPPING
#define PROJECTIONMAPPING

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 03/20/16.
//  Copyright © 2016 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Mapping.h"
#include "Constants.h"

class ProjectionMapping:public Mapping
{
	public:

		Point3D projectionCenter;
		float distance;

		Vector3D n0, n1, n2;
		
		//Constructors
		ProjectionMapping(void);										//Default Constructor


		//Destructor

		~ProjectionMapping(void);

		//Member Functions
		void ComputeNormals(void);

		//Pure virtual function to get the color at particular hit point
		RGBColor MapToImage(const ShadeRecord& sr, Image* imagePtr) const;
};

#endif
