//
// Created by Dell on 2021/6/24.
//

#ifndef PROJECT_PLAYER_H
#define PROJECT_PLAYER_H


#include "header.h"

class Player
{
public:
    Player();
    Player(int set_face, int set_x, int set_y, int set_z);
    bool inwater = false;
    void set_Player(int set_face, float set_x, float set_y, float set_z, float set_yaw, float set_pitch);
    void set_Player_pos(int set_face, float set_x, float set_y, float set_z);
    void Player_move(float set_yaw, int key);
    void Player_move_re(int x_re, int y_re, int z_re);
    void re_Player_positon(float pos[]);
    void draw_Player(void);
    void draw_Player_edit(void);//这个简单画个大方块1*1就可
private:
    int face = 0;
    float x = 0, y = 0, z = 0;//....
    const float pi = 3.14;
    const float radtrans = pi / 180;
    float yaw = 0, pitch = 0;//目前视角
    float yawr = 0, pitchr = 0;
    float body_yaw = 0;//身体角
    float speed_x = 0, speed_y = 0, speed_z = 0;//速度
    float speed_1_x = 0, speed_1_y = 0, speed_2_x = 0, speed_2_y = 0;
    float speed_add = 0.0025;
    float speed_max = 0.025;
    float res_x = 0.0015, res_y = 0.0015, res_z = 0.010;//阻尼
    int player_textureID[5][6];//头、身体，腿，尾巴，耳朵
    GLfloat player_ambient[4] = { 0.2,0.2,0.2,1.0 };// 环境颜色
    GLfloat player_diffuse[4] = { 0.2,0.2,0.2,1.0 };//散射颜色
    GLfloat player_specluar[4] = { 0.2,0.2,0.2,1.0 };//镜面颜色
    GLfloat player_shininess[1] = { 0.0 };//镜面指数
    GLfloat player_emission[4] = { 0.2,0.2,0.2,1.0 };//发射颜色
};

static GLuint player_texname[50];
void Playertexture_load(void);


#endif //PROJECT_PLAYER_H
