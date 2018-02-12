// =============================================================================
//
//  Created by Shyam Prathish Sargunam on 03/06/16.
//  Copyright © 2015 Shyam Prathish Sargunam. All rights reserved.
//
// =============================================================================

#include "ImageTexture.h"

//Default Constructor
ImageTexture::ImageTexture(void) : imagePtr(nullptr), mappingPtr(nullptr)
{
}

ImageTexture::ImageTexture(Image* imagePointer, Mapping* mappingPointer) : imagePtr(imagePointer), mappingPtr(mappingPointer)
{
}

//Destructor
ImageTexture::~ImageTexture(void)
{

}

RGBColor ImageTexture::GetColor(const ShadeRecord& sr) const
{
	return mappingPtr->MapToImage(sr, imagePtr);
}


