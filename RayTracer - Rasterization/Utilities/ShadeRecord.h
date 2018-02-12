#ifndef SHADERECORD
#define SHADERECORD

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 1/14/16.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "RGBColor.h"
#include "Point3D.h"
#include "Ray.h"
//#include "World.h"

class World;
class Material;

class ShadeRecord
{
	public:
		RGBColor color;
		float t;
		Point3D hitPoint;
		Vector3D localHitPoint;
		Ray ray;
		Material *materialPtr;
		World *worldPtr;
		bool objectHit;
		Vector3D normal;
		int rayDepth;

		ShadeRecord(void);

		//***********************************************************************************************************//
		//**									     ***IMPORTANT***											   **//
		//*			If new variables are added in this class, they should be added in assignment operator too		*//
		//**																									   **//
		//***********************************************************************************************************//

		~ShadeRecord(void);												//Destructor

	//Member Functions
		ShadeRecord& operator=(const ShadeRecord& sr);							//Assignment operator
};

#endif