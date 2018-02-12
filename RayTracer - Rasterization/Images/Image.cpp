// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 03/06/15.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "Image.h"

//Default Constructor
Image::Image(void)
{
	
}


//Destructor
Image::~Image(void)
{

}

void readComments(ifstream &fileStream)
{
	string clean;
	while (fileStream.peek() == '#')
	{
		getline(fileStream, clean);
	}
}

void Image::ReadPPMFile(char* filename) 
{
	ifstream inputFile(filename, ios::binary);
	if (!inputFile)
	{
		cout << "Invalid file. Exiting execution\n";
		exit(0);
	}
	else
	{
		readComments(inputFile);

		//Validating Magic Number
		string singleLine;
		getline(inputFile, singleLine);

		if (singleLine != "P6")
		{
			cout << "The file is not in ppm format. Inappropriate magic number\n";
			inputFile.close();
			exit(-1);
		}

		readComments(inputFile);

		//get width and height
		getline(inputFile, singleLine);
		istringstream(singleLine) >> width >> height;

		readComments(inputFile);

		getline(inputFile, singleLine);
		maxColor = atoi(singleLine.c_str());
		if (maxColor > 255)
		{
			cout << "Color value exceeds 255\n";
			inputFile.close();
			exit(-1);
		}

		pixmap.resize(width*height);

		readComments(inputFile);

		int data = 0;

		//read bytes for pixel map
		for (int y = height - 1; y >= 0; y--)
		{
			for (int x = 0; x < width; x++)
			{
				int i = y * width + x;
				char rgbValue[3];
				inputFile.read(rgbValue, sizeof rgbValue);

				unsigned char urgbValue[3];
				
				urgbValue[0] = rgbValue[0];
				urgbValue[1] = rgbValue[1];
				urgbValue[2] = rgbValue[2];

				RGBColor tempColor;

				tempColor.r = (urgbValue[0]);
				tempColor.g = (urgbValue[1]);
				tempColor.b = (urgbValue[2]);
				
				tempColor.r /= 255;
				tempColor.g /= 255;
				tempColor.b /= 255;

				pixmap[i] = tempColor;
			}
		}
		inputFile.close();
	}
}

void Image::WritePPMFile(char* fileName, unsigned char* localPixMap, const int& width, const int& height)
{
	ofstream outFile(fileName, ios::binary);

	if (outFile.is_open())
	{
		outFile << "P6\n";
		outFile << width << " " << height << "\n";
		outFile << 255 << "\n";

		for (int y = height - 1; y >= 0; y--)
		{
			for (int x = 0; x < width; x++)
			{
				int i = (y * width + x)*3;

				outFile << localPixMap[i];
				outFile << localPixMap[++i];
				outFile << localPixMap[++i];
			}
		}
		outFile.close();
	}
}

void Image::WritePPMFile(char* fileOne, char* fileTwo)
{
	ReadPPMFile(fileOne);

	ofstream outFile(fileTwo, ios::binary);

	if (outFile.is_open())
	{
		outFile << "P6\n";
		outFile << width << " " << height << "\n";
		outFile << maxColor << "\n";

		for (int y = height - 1; y >= 0; y--)
		{
			for (int x = 0; x < width; x++)
			{
				int i = y * width + x;
				/*if(y == 100)
					std::cout << "red: " << (unsigned char)(pixmap[i].r * 255)<< "\n";
				*/

				//outFile << (char)(pixmap[i].r * 255);
				//outFile << (char)(pixmap[i].g * 255);
				//outFile << (char)(pixmap[i].b * 255);

				unsigned char temp[3];
				temp[0] = (pixmap[i].r * 255);
				temp[1] = (pixmap[i].g * 255);
				temp[2] = (pixmap[i].b * 255);
				
				outFile << (char)temp[0];
				outFile << (char)temp[1];
				outFile << (char)temp[2];
			}
		}
		outFile.close();
	}
}