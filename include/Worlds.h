//
// Created by Dell on 2021/6/24.
//

#ifndef PROJECT_WORLDS_H
#define PROJECT_WORLDS_H

#include"Block.h"
#include"Player.h"
#include"Entity.h"

class World
{
public:
    World();
    World(int size);
    Player player;
    void modify_pram(int pram[]);
    void modify_playerpram(float pram[]);
    void change_worldID(int set_ID);
    void change_worldsize(int number);
    void change_worlddata(int ID, int face,int type,int x, int y, int z, int toward);
    void add_worlddata(int ID, int face, int type,int x, int y, int z, int toward);
    void init_World();
    int block_crash_dect(float face, float x, float y, float z);
    void crash_dect();
    void draw_face(int set_face);
    void draw_World(int mode);
    void draw_World_edit(int mode);
    void output_worlddata();
    void input_worlddata();
    void draw_world_test();
    void draw_world_singletest(int face,int x,int y,int z);
    int draw_world_rules(int face1, int x1, int y1, int z1, int face2, int x2, int y2, int z2);
    void draw_world_lightlist();
    void draw_world_singlelightlist(int face, int x, int y, int z, int act);
    int re_draw_world_lightlist(float set_light_list[8][10]);
    int re_worlddata(int face, int x, int y, int z, int data);
    int re_worldsize();
    int re_worldtime();
private:
    int worldID;
    char worldname[20];
    int worldsize;
    int worlddata[6][75][75][25][10] = {0};//存放世界数据:6-面；50,50，25-x，y，z;2-方块数据，目前为0-ID，1-facing,2-type(0,normal;1,unbreakable;2-half;3-entity),3-是否draw,4~9-各面绘制0,1,2,3,4,5
    /*
      这在里稍微说一下以防后来者迷糊了，总之这个数据结构比你们想象的要复杂,worlddata存放对应位置的方块ID
      我考虑过一些用于遍历立方体内部空间的方案而且要求每个面储存内容大体相近，最后得出结论放在这
      0,5对应顶面与底面，只用于储存worldsize + 1~worldsize * 2 - 2，worldsize + 1~worldsize * 2 - 2，worldsize区域的内容
      1,2,3,4对应四个侧面，储存0~worldsize * 2 - 2，0~worldsize * 3 - 1，worldsize区间内容，顺带一提这样刚好构成一个大立方体

      关于type，0-方块，1-半砖，2-实体，3-透明方块，4-透明无碰撞，5-水/流体；
      绘制顺序，1，0，2, 5, 4, 3；

      可能优化--根据距离玩家远近生成绘制列表。
     */
    int draw_type_list[6] = {0,1,2,5,3,4};
    int light_num = 0;
    float light_list[8][10];//face,x,y,z,0，diffuse,specular,0,1,2次衰减因子;
    float playerdata[10];
    int time = 0;
};


#endif //PROJECT_WORLDS_H
