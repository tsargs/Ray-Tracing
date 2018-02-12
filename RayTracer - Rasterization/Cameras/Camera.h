#ifndef CAMERA
#define CAMERA

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 02/05/15.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

//#include "World.h"
#include "Point3D.h"
#include "Vector3D.h"
#include "Constants.h"
#include <iostream>

class World;

class Camera
{
	public:
		
		Point3D eyePos;
		Point3D lookAtPos;
		Vector3D up;
		float roll;

		Vector3D u, v, w;

		World* worldPtr;

		//Constructors

		Camera(void);										//Default Constructor
		
		//Destructor

		~Camera(void);

		//Member Functions

		virtual void RenderScene();
		void SetupOrthonormalBase();
		Point3D Rotate(const Point3D& point, const Point3D& pointOnAxis, const float& roll, const Vector3D& axisVector);
};

inline void Camera::SetupOrthonormalBase()
{
	w = (eyePos - lookAtPos).UnitVector();
	//std::cout << "x: " << w.x << ", y: " << w.y << ", z: " << w.z << "\n";
	if(roll != 0)
		up = (Rotate(eyePos+up, eyePos, roll, w)-eyePos).UnitVector();

	u = (up^w).UnitVector();
	v = (w^u).UnitVector();
	std::cout << "Orthonormal base for camera has been setup\n";
}

#endif
