#ifndef NORMAL
#define NORMAL

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 01/15/16.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

class Normal
{
	public:
		double x, y, z;

		//Constructors

		Normal(void);										//Default Constructor
		Normal(double xVal, double yVal, double zVal);
		Normal(const Normal& normal);						//Copy constructor
		
		//Destructor

		~Normal(void);

		//Member Functions

		Normal& UnitVector(void);							//Returns unit vector

		Normal& operator=(const Normal& normal);			//Assignment Operator
};

#endif
