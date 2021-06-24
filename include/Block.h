//
// Created by Dell on 2021/6/24.
//

#ifndef PROJECT_BLOCK_H
#define PROJECT_BLOCK_H


#include "header.h"

class Block
{
public:
    Block();
    Block(int ID, int type,int set_x, int set_y, int set_z);
    void set_Block(const int data[],int set_x, int set_y, int set_z, int set_size);
    void init_Block(int ID, int type);
    void draw_Block();
    void draw_Block_edit();
    void draw_skybox(float set_color[4]);
    void draw_waterbox();
private:
    int BlockID;
    int Blocktype;
    int x,y,z;
    int faceing_x, faceing_y, faceing_z;
    int block_toward=0;
    int block_toward_mode=0;
    int textureID[6];
    GLfloat block_ambient[4] = { 0.2,0.2,0.2,1.0 };// 环境颜色
    GLfloat block_diffuse[4] = { 0.2,0.2,0.2,1.0 };//散射颜色
    GLfloat block_specluar[4] = { 0.2,0.2,0.2,1.0 };//镜面颜色
    GLfloat block_shininess[1] = { 0.0 };//镜面指数
    GLfloat block_emission[4] = { 0.2,0.2,0.2,1.0 };//发射颜色
    int draw = 1;//是否绘制
    int drawface[6] = { 1,1,1,1,1,1 };//各面是否绘制
    int amount = 4;
    float size = 0.25;
};

static GLuint texname[50];
void texture_load(void);


#endif //PROJECT_BLOCK_H
