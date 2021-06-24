//
// Created by Dell on 2021/6/24.
//

#ifndef PROJECT_ENTITY_H
#define PROJECT_ENTITY_H

#include "header.h"

class Entity
{
public:
    Entity();
    void set_Entity(int set_face, int set_x, int set_y, int set_z);
    void draw_Entity(void);
    void Playertexture_load(void);
private:
    int face = 0, x = 0, y = 0, z = 0;
    float yaw = 0, pitch = 0 ;
};


#endif //PROJECT_ENTITY_H
