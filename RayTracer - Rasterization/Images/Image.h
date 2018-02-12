#ifndef IMAGE
#define IMAGE

// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 03/06/15.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <cassert>
#include <sstream>
#include <string>

#include <string.h>

#include "RGBColor.h"

using namespace std;

class Image
{
	public:
		std::vector<RGBColor> pixmap;
		int width, height;
		int maxColor;

		//Constructors
		Image(void);										//Default Constructor

		//Destructor

		~Image(void);

		//Member Functions

		//Reads PPM File
		void ReadPPMFile(char* filename);
		void WritePPMFile(char* fileOne, unsigned char* localPixMap, const int& width, const int& height);
		void WritePPMFile(char* fileOne, char* fileTwo);
};

#endif
