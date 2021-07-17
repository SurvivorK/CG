//
// Created by Dell on 2021/6/24.
//

#include "Image.h"
#define STB_IMAGE_IMPLEMENTATION   // use of stb functions once and for all
#include "stb_image.h"

void Image::loadf(const char* filename, int* width, int* height, int* nrChannels, int req_comp) {
    _imgData = stbi_load(filename, width, height, nrChannels, 0);
}
Image::~Image()
{
    if ( _imgData )
        stbi_image_free(_imgData);
}
