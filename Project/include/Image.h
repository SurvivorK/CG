//
// Created by Dell on 2021/6/24.
//

#ifndef PROJECT_IMAGE_H
#define PROJECT_IMAGE_H


#ifndef _IMAGE_H_
#define _IMAGE_H_

class Image {
public:
    Image() : _imgData() {}
    virtual ~Image();

    void loadf(const char* filename, int* width, int* height, int *nrChannels, int req_comp = 0);
    unsigned char* getData() const { return _imgData; }
protected:
    unsigned char* _imgData;
};
#endif


#endif //PROJECT_IMAGE_H
