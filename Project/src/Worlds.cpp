//
// Created by Dell on 2021/6/24.
//

#include "Worlds.h"
using namespace std;


World::World()
{
    worldID = 1;
    worldsize = 10;
    player.set_Player(0,0,0,0,0,0);
}


World::World(int ID)
{
    worldID = ID;
}

//标准化坐标(解决六个面边界时的问题)---type 3 朝向只改了0,1
void World::modify_pram(int pram[])
{
    int temp;
    switch (pram[0])
    {
        case 0: {
            //0-2 inerface
            if ((pram[1] < (worldsize * 2 - 1)) && (pram[2] < (worldsize + 1)))
            {
                pram[0] = 2;
                pram[1] = pram[1];
                temp = pram[2];
                pram[2] = worldsize * 2 - 1 + pram[3];
                pram[3] = worldsize - temp;
                pram[4] = 0;
                return;
            }
            //0-3 inerface
            if ((pram[1] >= (worldsize + 1)) && (pram[2] >= (worldsize * 2 - 1)))
            {
                pram[0] = 3;
                pram[1] = worldsize * 3 - 1 - pram[1];
                temp = pram[2];
                pram[2] = worldsize * 2 - 1 + pram[3];
                pram[3] = temp - worldsize * 2 + 1;
                pram[4] = 0;
                return;
            }
            //0-4 inerface
            if ((pram[1] < (worldsize + 1)) && (pram[2] >= (worldsize + 1)))
            {
                pram[0] = 4;
                temp = pram[1];
                pram[1] = worldsize * 3 - 1 - pram[2];
                pram[2] = worldsize * 2 - 1 + pram[3];
                pram[3] = worldsize - temp;
                pram[4] = 0;
                return;
            }
            //0-5 inerface
            if ((pram[1] >= (worldsize * 2 - 1)) && (pram[2] < (worldsize * 2 - 1)))
            {
                pram[0] = 5;
                temp = pram[1];
                pram[1] = pram[2];
                pram[2] = worldsize * 2 - 1 + pram[3];
                pram[3] = temp - worldsize * 2 + 1;
                pram[4] = 0;
                return;
            }
        } break;
        case 1: {
            //1-3 inerface
            if ((pram[1] >= (worldsize + 1)) && (pram[2] < (worldsize + 1)))
            {
                pram[0] = 3;
                pram[1] = worldsize * 3 - 1 - pram[1];
                temp = pram[2];
                pram[2] = worldsize - pram[3];
                pram[3] = worldsize - temp;
                pram[4] = 0;
                return;
            }
            //1-2 inerface
            if ((pram[1] < (worldsize * 2 - 1)) && (pram[2] >= (worldsize * 2 - 1)))
            {
                pram[0] = 2;
                pram[1] = pram[1];
                temp = pram[2];
                pram[2] = worldsize - pram[3];
                pram[3] = temp - worldsize * 2 + 1;
                pram[4] = 0;
                return;
            }
            //1-5 inerface
            if ((pram[1] >= (worldsize * 2 - 1)) && (pram[2] >= (worldsize + 1)))
            {
                pram[0] = 5;
                temp = pram[1];
                pram[1] = worldsize * 3 - 1 - pram[2];
                pram[2] = worldsize - pram[3];
                pram[3] = temp - worldsize * 2 + 1;;
                pram[4] = 0;
                return;
            }
            //1-4 inerface
            if ((pram[1] < (worldsize + 1)) && (pram[2] < (worldsize * 2 - 1)))
            {
                pram[0] = 4;
                temp = pram[1];
                pram[1] = pram[2];
                pram[2] = worldsize - pram[3];
                pram[3] = worldsize - temp;
                pram[4] = 0;
                return;
            }
        } break;
        case 2: {
            if ((pram[1] < (worldsize + 1)) && (pram[3] < 0))
            {
                pram[0] = 4;
                temp = pram[3];
                pram[3] = worldsize - pram[1];
                pram[1] = worldsize * 2 + temp - 1;
                pram[2] = pram[2];
                pram[4] = 4;
                return;
            }
            if ((pram[2] < (worldsize + 1)) && (pram[3] < 0))
            {
                pram[0] = 1;
                temp = pram[3];
                pram[1] = pram[1];
                pram[3] = worldsize - pram[2];
                pram[2] = worldsize * 2 + temp - 1;
                pram[4] = 2;
                return;
            }
            if ((pram[2] >= (worldsize * 2 - 1)) && (pram[3] < 0))
            {
                pram[0] = 0;
                pram[1] = pram[1];
                temp = pram[3];
                pram[3] = pram[2] - (worldsize * 2 - 1);
                pram[2] = worldsize - temp;
                pram[4] = 3;
                return;
            }
            if (pram[1] >= (worldsize * 2 - 1))
            {
                pram[0] = 5;
                temp = pram[1];
                pram[1] = worldsize - pram[3];
                pram[2] = pram[2];
                pram[3] = temp - worldsize * 2 + 1;
                pram[4] = 0;
                return;
            }
        } break;
        case 3: {
            if ((pram[1] < (worldsize + 1)) && (pram[3] < 0))
            {
                pram[0] = 5;
                temp = pram[3];
                pram[3] = worldsize - pram[1];
                pram[1] = worldsize * 2 + temp - 1;
                pram[2] = pram[2];
                pram[4] = 4;
                return;
            }
            if ((pram[2] < (worldsize + 1)) && (pram[3] < 0))
            {
                pram[0] = 1;
                temp = pram[3];
                pram[3] = worldsize - pram[2];
                pram[1] = (worldsize * 3 - 1) - pram[1];
                pram[2] = worldsize - temp;
                pram[4] = 3;
                return;
            }
            if ((pram[2] >= (worldsize * 2 - 1)) && (pram[3] < 0))
            {
                pram[0] = 0;
                temp = pram[3];
                pram[3] = pram[2] - (worldsize * 2 - 1);
                pram[2] = worldsize * 2 + temp - 1;
                pram[1] = (worldsize * 3 - 1) - pram[1];
                pram[4] = 2;
                return;
            }
            if (pram[1] >= (worldsize * 2 - 1))
            {
                pram[0] = 4;
                temp = pram[1];
                pram[1] = worldsize - pram[3];
                pram[2] = pram[2];
                pram[3] = temp - worldsize * 2 + 1;
                pram[4] = 0;
                return;
            }
        }break;
        case 4: {
            if ((pram[1] < (worldsize + 1)) && (pram[3] < 0))
            {
                pram[0] = 3;
                temp = pram[3];
                pram[3] = worldsize - pram[1];
                pram[1] = worldsize * 2 + temp - 1;
                pram[2] = pram[2];
                pram[4] = 4;
                return;
            }
            if ((pram[2] < (worldsize + 1)) && (pram[3] < 0))
            {
                pram[0] = 1;
                temp = pram[3];
                pram[3] = worldsize - pram[2];
                pram[2] = pram[1];
                pram[1] = worldsize - temp;
                pram[4] = 5;
                return;
            }
            if ((pram[2] >= (worldsize * 2 - 1)) && (pram[3] < 0))
            {
                pram[0] = 0;
                temp = pram[3];
                pram[3] = pram[2] - (worldsize * 2 - 1);
                pram[2] = (worldsize * 3 - 1) - pram[1];
                pram[1] = worldsize - temp;
                pram[4] = 5;
                return;
            }
            if (pram[1] >= (worldsize * 2 - 1))
            {
                pram[0] = 2;
                temp = pram[1];
                pram[1] = worldsize - pram[3];
                pram[2] = pram[2];
                pram[3] = temp - worldsize * 2 + 1;
                pram[4] = 0;
                return;
            }
        }break;
        case 5: {
            if ((pram[1] < (worldsize + 1)) && (pram[3] < 0))
            {
                pram[0] = 2;
                temp = pram[3];
                pram[3] = worldsize - pram[1];
                pram[1] = worldsize * 2 + temp - 1;
                pram[2] = pram[2];
                pram[4] = 4;
                return;
            }
            if ((pram[2] < (worldsize + 1)) && (pram[3] < 0))
            {
                pram[0] = 1;
                temp = pram[3];
                pram[3] = worldsize - pram[2];
                pram[2] = (worldsize * 3 - 1) - pram[1];
                pram[1] = worldsize * 2 + temp - 1;;
                pram[4] = 4;
                return;
            }
            if ((pram[2] >= (worldsize * 2 - 1)) && (pram[3] < 0))
            {
                pram[0] = 0;
                temp = pram[3];
                pram[3] = pram[2] - (worldsize * 2 - 1);
                pram[2] = pram[1];
                pram[1] = worldsize * 2 + temp - 1;;
                pram[4] = 4;
                return;
            }
            if (pram[1] >= (worldsize * 2 - 1))
            {
                pram[0] = 3;
                temp = pram[1];
                pram[1] = worldsize - pram[3];
                pram[2] = pram[2];
                pram[3] = temp - worldsize * 2 + 1;
                pram[4] = 0;
                return;
            }
        } break;
        default:break;
    }
}

//标准化玩家坐标(解决六个面边界时的问题)
void World::modify_playerpram(float pram[])
{
    float temp;
    switch ((int)pram[0])
    {
        case 0: {
            //0-2 inerface
            if ((pram[1] < (worldsize * 2 - 1)) && (pram[2] < (worldsize + 1)))
            {
                pram[0] = 2;
                pram[1] = pram[1];
                temp = pram[2];
                pram[2] = worldsize * 2 - 1 + pram[3];
                pram[3] = worldsize - temp;
                return;
            }
            //0-3 inerface
            if ((pram[1] >= (worldsize + 1)) && (pram[2] >= (worldsize * 2 - 1)))
            {
                pram[0] = 3;
                pram[1] = worldsize * 3 - 1 - pram[1];
                temp = pram[2];
                pram[2] = worldsize * 2 - 1 + pram[3];
                pram[3] = temp - worldsize * 2 + 1;
                return;
            }
            //0-4 inerface
            if ((pram[1] < (worldsize + 1)) && (pram[2] >= (worldsize + 1)))
            {
                pram[0] = 4;
                temp = pram[1];
                pram[1] = worldsize * 3 - 1 - pram[2];
                pram[2] = worldsize * 2 - 1 + pram[3];
                pram[3] = worldsize - temp;
                return;
            }
            //0-5 inerface
            if ((pram[1] >= (worldsize * 2 - 1)) && (pram[2] < (worldsize * 2 - 1)))
            {
                pram[0] = 5;
                temp = pram[1];
                pram[1] = pram[2];
                pram[2] = worldsize * 2 - 1 + pram[3];
                pram[3] = temp - worldsize * 2 + 1;
                return;
            }
        } break;
        case 1: {
            //1-3 inerface
            if ((pram[1] >= (worldsize + 1)) && (pram[2] < (worldsize + 1)))
            {
                pram[0] = 3;
                pram[1] = worldsize * 3 - 1 - pram[1];
                temp = pram[2];
                pram[2] = worldsize - pram[3];
                pram[3] = worldsize - temp;
                return;
            }
            //1-2 inerface
            if ((pram[1] < (worldsize * 2 - 1)) && (pram[2] >= (worldsize * 2 - 1)))
            {
                pram[0] = 2;
                pram[1] = pram[1];
                temp = pram[2];
                pram[2] = worldsize - pram[3];
                pram[3] = temp - worldsize * 2 + 1;
                return;
            }
            //1-5 inerface
            if ((pram[1] >= (worldsize * 2 - 1)) && (pram[2] >= (worldsize + 1)))
            {
                pram[0] = 5;
                temp = pram[1];
                pram[1] = worldsize * 3 - 1 - pram[2];
                pram[2] = worldsize - pram[3];
                pram[3] = temp - worldsize * 2 + 1;;
                return;
            }
            //1-4 inerface
            if ((pram[1] < (worldsize + 1)) && (pram[2] < (worldsize * 2 - 1)))
            {
                pram[0] = 4;
                temp = pram[1];
                pram[1] = pram[2];
                pram[2] = worldsize - pram[3];
                pram[3] = worldsize - temp;
                return;
            }
        } break;
        case 2: {
            if ((pram[1] < (worldsize + 1)) && (pram[3] < 0))
            {
                pram[0] = 4;
                temp = pram[3];
                pram[3] = worldsize - pram[1];
                pram[1] = worldsize * 2 + temp - 1;
                pram[2] = pram[2];
                return;
            }
            if ((pram[2] < (worldsize + 1)) && (pram[3] < 0))
            {
                pram[0] = 1;
                temp = pram[3];
                pram[1] = pram[1];
                pram[3] = worldsize - pram[2];
                pram[2] = worldsize * 2 + temp - 1;
                return;
            }
            if ((pram[2] >= (worldsize * 2 - 1)) && (pram[3] < 0))
            {
                pram[0] = 0;
                pram[1] = pram[1];
                temp = pram[3];
                pram[3] = pram[2] - (worldsize * 2 - 1);
                pram[2] = worldsize - temp;
                return;
            }
            if (pram[1] >= (worldsize * 2 - 1))
            {
                pram[0] = 5;
                temp = pram[1];
                pram[1] = worldsize - pram[3];
                pram[2] = pram[2];
                pram[3] = temp - worldsize * 2 + 1;
                return;
            }
        } break;
        case 3: {
            if ((pram[1] < (worldsize + 1)) && (pram[3] < 0))
            {
                pram[0] = 5;
                temp = pram[3];
                pram[3] = worldsize - pram[1];
                pram[1] = worldsize * 2 + temp - 1;
                pram[2] = pram[2];
                return;
            }
            if ((pram[2] < (worldsize + 1)) && (pram[3] < 0))
            {
                pram[0] = 1;
                temp = pram[3];
                pram[3] = worldsize - pram[2];
                pram[1] = (worldsize * 3 - 1) - pram[1];
                pram[2] = worldsize - temp;
                return;
            }
            if ((pram[2] >= (worldsize * 2 - 1)) && (pram[3] < 0))
            {
                pram[0] = 0;
                temp = pram[3];
                pram[3] = pram[2] - (worldsize * 2 - 1);
                pram[2] = worldsize * 2 + temp - 1;
                pram[1] = (worldsize * 3 - 1) - pram[1];
                return;
            }
            if (pram[1] >= (worldsize * 2 - 1))
            {
                pram[0] = 4;
                temp = pram[1];
                pram[1] = worldsize - pram[3];
                pram[2] = pram[2];
                pram[3] = temp - worldsize * 2 + 1;
                return;
            }
        } break;
        case 4: {
            if ((pram[1] < (worldsize + 1)) && (pram[3] < 0))
            {
                pram[0] = 3;
                temp = pram[3];
                pram[3] = worldsize - pram[1];
                pram[1] = worldsize * 2 + temp - 1;
                pram[2] = pram[2];
                return;
            }
            if ((pram[2] < (worldsize + 1)) && (pram[3] < 0))
            {
                pram[0] = 1;
                temp = pram[3];
                pram[3] = worldsize - pram[2];
                pram[2] = pram[1];
                pram[1] = worldsize - temp;
                return;
            }
            if ((pram[2] >= (worldsize * 2 - 1)) && (pram[3] < 0))
            {
                pram[0] = 0;
                temp = pram[3];
                pram[3] = pram[2] - (worldsize * 2 - 1);
                pram[2] = (worldsize * 3 - 1) - pram[1];
                pram[1] = worldsize - temp;
                return;
            }
            if (pram[1] >= (worldsize * 2 - 1))
            {
                pram[0] = 2;
                temp = pram[1];
                pram[1] = worldsize - pram[3];
                pram[2] = pram[2];
                pram[3] = temp - worldsize * 2 + 1;
                return;
            }
        } break;
        case 5: {
            if ((pram[1] < (worldsize + 1)) && (pram[3] < 0))
            {
                pram[0] = 2;
                temp = pram[3];
                pram[3] = worldsize - pram[1];
                pram[1] = worldsize * 2 + temp - 1;
                pram[2] = pram[2];
                return;
            }
            if ((pram[2] < (worldsize + 1)) && (pram[3] < 0))
            {
                pram[0] = 1;
                temp = pram[3];
                pram[3] = worldsize - pram[2];
                pram[2] = (worldsize * 3 - 1) - pram[1];
                pram[1] = worldsize * 2 + temp - 1;;
                return;
            }
            if ((pram[2] >= (worldsize * 2 - 1)) && (pram[3] < 0))
            {
                pram[0] = 0;
                temp = pram[3];
                pram[3] = pram[2] - (worldsize * 2 - 1);
                pram[2] = pram[1];
                pram[1] = worldsize * 2 + temp - 1;;
                return;
            }
            if (pram[1] >= (worldsize * 2 - 1))
            {
                pram[0] = 3;
                temp = pram[1];
                pram[1] = worldsize - pram[3];
                pram[2] = pram[2];
                pram[3] = temp - worldsize * 2 + 1;
                return;
            }
        } break;
        default:break;
    }
}

void World::change_worldID(int set_ID)
{
    worldID = set_ID;
}

//世界大小
void World::change_worldsize(int number) {
    if (number % 2 == 1)
        number++;
    worldsize = number;
    if (worldsize <= 4)
        worldsize = 4;
    else if (worldsize >= 25)
        worldsize = 24;

    init_World();
}

//改变存档方块
void World::change_worlddata(int ID, int face, int type, int x, int y, int z, int toward)
{
    if ((ID == 0) && (worlddata[face][x][y][z][0] != -1))
    {
        draw_world_singlelightlist(face, x, y, z, -1);

        worlddata[face][x][y][z][0] = ID;
        worlddata[face][x][y][z][1] = toward;
        worlddata[face][x][y][z][2] = 0;

        draw_world_test();//emmm...优化
    }
    else if ((ID != 0) && (worlddata[face][x][y][z][0] == 0))
    {
        worlddata[face][x][y][z][0] = ID;
        worlddata[face][x][y][z][1] = toward;
        worlddata[face][x][y][z][2] = type;

        draw_world_singletest(face,x,y,z);//emmm...优化
        draw_world_singlelightlist(face, x, y, z, 1);
    }
}

//放置方块(输入点击方块位置)
void World::add_worlddata(int ID, int face, int type, int x, int y, int z, int toward)
{
    //实际坐标
    int actual[5];
    actual[0] = face;
    actual[1] = x;
    actual[2] = y;
    actual[3] = z;
    actual[4] = toward;

    switch (toward)
    {
        case 0:actual[3]++; break;
        case 1:actual[3]--; break;
        case 2:actual[2]--; break;
        case 3:actual[2]++; break;
        case 4:actual[1]--; break;
        case 5:actual[1]++; break;
        default:break;
    }

    modify_pram(actual);

    change_worlddata(ID, actual[0], type, actual[1], actual[2], actual[3], actual[4]);
}

//初始化世界数据
void World::init_World()
{

    for (int h = 0; h < 6; h++)//面
        for (int i = 0; i < 3 * worldsize; i++)
            for (int j = 0; j < 3 * worldsize; j++)
                for (int k = 0; k < worldsize; k++)
                    for (int l = 0;l < 10 ; l++)
                        worlddata[h][i][j][k][l] = 0;


    for (int h = 0; h < 6; h++)
        for (int i = worldsize; i < worldsize * 2; i++)
            for (int j = worldsize; j < worldsize * 2; j++)
            {
                worlddata[h][i][j][0][0] = -1;//设为1无法摧毁
                worlddata[h][i][j][1][0] = 2;
                worlddata[h][i][j][2][0] = 3;
            }


    player.set_Player(0, worldsize+4, worldsize+4, 4, 0, 0);
    draw_world_test();
}

//方块碰撞检测，碰撞返回1
int World::block_crash_dect(float face, float x, float y, float z)
{
    float collison_size = 0.25;//玩家碰撞体积
    int temp_ID = 0;
    int temp_type = 0;

    temp_ID=re_worlddata((int)(face)/*face*/, (int)round(x)/*x*/, (int)round(y)/*y*/, (int)round(z)/*z*/, 0);
    temp_type= re_worlddata((int)(face)/*face*/, (int)round(x)/*x*/, (int)round(y)/*y*/, (int)round(z)/*z*/, 2);

    if (temp_ID == 0)
        return 0;

    if (temp_type < 4)
        return 1;

    return 0;
}

//碰撞检测
void World::crash_dect()
{
    int re_x = 1, re_y = 1, re_z = 1;
    float collison_size = 0.25;//玩家碰撞体积

    //回调玩家速度位置信息
    player.re_Player_positon(playerdata);

    //先判断x,y平面（未考虑衔接，待改写）
    if ((playerdata[7] > 0) && block_crash_dect(playerdata[0]/*face*/, playerdata[1] + playerdata[7] + collison_size/*x*/, playerdata[2]/*y*/, playerdata[3]/*z*/))
    {
        player.set_Player_pos((int)playerdata[0], round(playerdata[1] + playerdata[7] + collison_size) - 0.501 - collison_size, playerdata[2], playerdata[3]);
        re_x = -1;
    }
    else if ((playerdata[7] < 0) && block_crash_dect(playerdata[0]/*face*/, playerdata[1] + playerdata[7] - collison_size/*x*/, playerdata[2]/*y*/, playerdata[3]/*z*/))
    {
        player.set_Player_pos((int)playerdata[0], round(playerdata[1] + playerdata[7] - collison_size) + 0.501 + collison_size, playerdata[2], playerdata[3]);
        re_x = -1;
    }

    if ((playerdata[8] > 0) && block_crash_dect(playerdata[0]/*face*/, playerdata[1]/*x*/, playerdata[2] + playerdata[8] + collison_size/*y*/, playerdata[3]/*z*/))
    {
        player.set_Player_pos((int)playerdata[0], playerdata[1], round(playerdata[2] + playerdata[8] + collison_size) - 0.501 - collison_size, playerdata[3]);
        re_y = -1;
    }
    else if ((playerdata[8] < 0) && block_crash_dect(playerdata[0]/*face*/, playerdata[1]/*x*/, playerdata[2] + playerdata[8] - collison_size/*y*/, playerdata[3]/*z*/))
    {
        player.set_Player_pos((int)playerdata[0], playerdata[1], round(playerdata[2] + playerdata[8] - collison_size) + 0.501 + collison_size, playerdata[3]);
        re_y = -1;
    }


    if (((int)playerdata[8] >= 0) && (playerdata[7] > 0) && block_crash_dect(playerdata[0]/*face*/, playerdata[1] + playerdata[7] + collison_size/*x*/, playerdata[2] + collison_size/*y*/, playerdata[3]/*z*/))
        re_x = -1;
    else if (((int)playerdata[8] <= 0) && (playerdata[7] > 0) && block_crash_dect(playerdata[0]/*face*/, playerdata[1] + playerdata[7] + collison_size/*x*/, playerdata[2] - collison_size/*y*/, playerdata[3]/*z*/))
        re_x = -1;

    if (((int)playerdata[8] >= 0) && (playerdata[7] < 0) && block_crash_dect(playerdata[0]/*face*/, playerdata[1] + playerdata[7] - collison_size/*x*/, playerdata[2] + collison_size/*y*/, playerdata[3]/*z*/))
        re_x = -1;
    else if (((int)playerdata[8] <= 0) && (playerdata[7] < 0) && block_crash_dect(playerdata[0]/*face*/, playerdata[1] + playerdata[7] - collison_size/*x*/, playerdata[2] - collison_size/*y*/, playerdata[3]/*z*/))
        re_x = -1;

    if ((playerdata[8] > 0) && ((int)playerdata[7] >= 0) && block_crash_dect(playerdata[0]/*face*/, playerdata[1] + collison_size/*x*/, playerdata[2] + playerdata[8] + collison_size/*y*/, playerdata[3]/*z*/))
        re_y = -1;
    else if ((playerdata[8] > 0) && ((int)playerdata[7] <= 0) && block_crash_dect(playerdata[0]/*face*/, playerdata[1] - collison_size/*x*/, playerdata[2] + playerdata[8] + collison_size/*y*/, playerdata[3]/*z*/))
        re_y = -1;

    if ((playerdata[8] < 0) && ((int)playerdata[7] >= 0) && block_crash_dect(playerdata[0]/*face*/, playerdata[1] + collison_size/*x*/, playerdata[2] + playerdata[8] - collison_size/*y*/, playerdata[3]/*z*/))
        re_y = -1;
    else if ((playerdata[8] < 0) && ((int)playerdata[7] <= 0) && block_crash_dect(playerdata[0]/*face*/, playerdata[1] - collison_size/*x*/, playerdata[2] + playerdata[8] - collison_size/*y*/, playerdata[3]/*z*/))
        re_y = -1;


    //这里是z平面的
    if ((playerdata[9] > 0) && block_crash_dect(playerdata[0]/*face*/, playerdata[1]/*x*/, playerdata[2]/*y*/, playerdata[3] + playerdata[9] + collison_size/*z*/))
    {
        player.set_Player_pos((int)playerdata[0], playerdata[1], playerdata[2], round(playerdata[3] + playerdata[9] + collison_size) - 0.5 - collison_size);
        re_z = -1;
    }
    else if ((playerdata[9] < 0) && block_crash_dect(playerdata[0]/*face*/, playerdata[1]/*x*/, playerdata[2]/*y*/, playerdata[3] + playerdata[9] - collison_size/*z*/))
    {
        player.set_Player_pos((int)playerdata[0], playerdata[1], playerdata[2], round(playerdata[3] + playerdata[9] - collison_size) + 0.5 + collison_size);
        re_z = -1;
    }

    //emm...gravity...
    if ((playerdata[9] == 0) && !block_crash_dect(playerdata[0]/*face*/, playerdata[1]/*x*/, playerdata[2]/*y*/, playerdata[3] - 0.001 - collison_size/*z*/) && !block_crash_dect(playerdata[0]/*face*/, playerdata[1]/*x*/, playerdata[2] - collison_size/*y*/, playerdata[3] - 0.001 - collison_size/*z*/) && !block_crash_dect(playerdata[0]/*face*/, playerdata[1]/*x*/, playerdata[2] + collison_size/*y*/, playerdata[3] - 0.001 - collison_size/*z*/) && !block_crash_dect(playerdata[0]/*face*/, playerdata[1] - collison_size/*x*/, playerdata[2]/*y*/, playerdata[3] - 0.001 - collison_size/*z*/) && !block_crash_dect(playerdata[0]/*face*/, playerdata[1] + collison_size/*x*/, playerdata[2] /*y*/, playerdata[3] - 0.001 - collison_size/*z*/))
        re_z = -2;


    //操作
    player.Player_move_re(re_x, re_y, re_z);

    //位置校正
    player.re_Player_positon(playerdata);
    if (playerdata[3] + collison_size < 0)
    {
        player.Player_move_re(-1, -1, -1);
        modify_playerpram(playerdata);
        player.set_Player(playerdata[0], playerdata[1], playerdata[2], playerdata[3], playerdata[4], playerdata[5]);
    }
}

//绘制在对应面所需变换
void World::draw_face(int set_face)
{
    switch (set_face)
    {
        case 0: {
            glTranslatef(-worldsize * 1.5 + 0.5, -worldsize * 1.5 + 0.5, worldsize / 2 - 0.5);
        }break;
        case 1: {
            glRotatef(180, 1, 0, 0);
            glTranslatef(-worldsize * 1.5 + 0.5, -worldsize * 1.5 + 0.5, worldsize / 2 - 0.5);
        }break;
        case 2: {
            glRotatef(90, 1, 0, 0);
            glTranslatef(-worldsize * 1.5 + 0.5, -worldsize * 1.5 + 0.5, worldsize / 2 - 0.5);
        }break;
        case 3: {
            glRotatef(180, 0, 0, 1);
            glRotatef(90, 1, 0, 0);
            glTranslatef(-worldsize * 1.5 + 0.5, -worldsize * 1.5 + 0.5, worldsize / 2 - 0.5);
        }break;
        case 4: {
            glRotatef(270, 0, 0, 1);
            glRotatef(90, 1, 0, 0);
            glTranslatef(-worldsize * 1.5 + 0.5, -worldsize * 1.5 + 0.5, worldsize / 2 - 0.5);
        }break;
        case 5: {
            glRotatef(90, 0, 0, 1);
            glRotatef(90, 1, 0, 0);
            glTranslatef(-worldsize * 1.5 + 0.5, -worldsize * 1.5 + 0.5, worldsize / 2 - 0.5);
        }break;
        default:break;
    }
}

//实现绘制世界
void World::draw_World(int mode)//绘制
{
    time += 1;
    if (time > 36000)
        time = 0;

    //人物绘制
    glPushMatrix();
    draw_face((int)playerdata[0]);
    crash_dect();
    player.draw_Player();
    glPopMatrix();

    //方块绘制
    Block a(0,0, 0, 0, 0);

    for (int h = 0; h < 6; h++)
    {
        glPushMatrix();//顶 0
        glTranslatef(-worldsize * 1.5 + 0.5, -worldsize * 1.5 + 0.5, worldsize / 2 - 0.5);
        for (int i = worldsize + 1; i < worldsize * 2 - 1; i++)
            for (int j = worldsize + 1; j < worldsize * 2 - 1; j++)
                for (int k = 0; k < worldsize; k++)
                {
                    if (worlddata[0][i][j][k][2]== draw_type_list[h])
                    {
                        a.set_Block(worlddata[0][i][j][k], i, j, k, worldsize);
                        a.draw_Block();
                    }
                }
        glPopMatrix();

        glPushMatrix();//前 2
        glRotatef(90, 1, 0, 0);
        glTranslatef(-worldsize * 1.5 + 0.5, -worldsize * 1.5 + 0.5, worldsize / 2 - 0.5);
        for (int i = 0; i < worldsize * 2 - 1; i++)
            for (int j = 0; j < worldsize * 3; j++)
                for (int k = 0; k < worldsize; k++)
                {
                    if (worlddata[2][i][j][k][2] == draw_type_list[h])
                    {
                        a.set_Block(worlddata[2][i][j][k], i, j, k, worldsize);
                        a.draw_Block();
                    }
                }
        glPopMatrix();

        glPushMatrix();//右 5（面对）
        glRotatef(90, 0, 0, 1);
        glRotatef(90, 1, 0, 0);
        glTranslatef(-worldsize * 1.5 + 0.5, -worldsize * 1.5 + 0.5, worldsize / 2 - 0.5);
        for (int i = 0; i < worldsize * 2 - 1; i++)
            for (int j = 0; j < worldsize * 3; j++)
                for (int k = 0; k < worldsize; k++)
                {
                    if (worlddata[5][i][j][k][2] == draw_type_list[h])
                    {
                        a.set_Block(worlddata[5][i][j][k], i, j, k, worldsize);
                        a.draw_Block();
                    }
                }
        glPopMatrix();

        glPushMatrix();//后3
        glRotatef(180, 0, 0, 1);
        glRotatef(90, 1, 0, 0);
        glTranslatef(-worldsize * 1.5 + 0.5, -worldsize * 1.5 + 0.5, worldsize / 2 - 0.5);
        for (int i = 0; i < worldsize * 2 - 1; i++)
            for (int j = 0; j < worldsize * 3; j++)
                for (int k = 0; k < worldsize; k++)
                {
                    if (worlddata[3][i][j][k][2] == draw_type_list[h])
                    {
                        a.set_Block(worlddata[3][i][j][k], i, j, k, worldsize);
                        a.draw_Block();
                    }
                }
        glPopMatrix();

        glPushMatrix();//左 4
        glRotatef(270, 0, 0, 1);
        glRotatef(90, 1, 0, 0);
        glTranslatef(-worldsize * 1.5 + 0.5, -worldsize * 1.5 + 0.5, worldsize / 2 - 0.5);
        for (int i = 0; i < worldsize * 2 - 1; i++)
            for (int j = 0; j < worldsize * 3; j++)
                for (int k = 0; k < worldsize; k++)
                {
                    if (worlddata[4][i][j][k][2] == draw_type_list[h])
                    {
                        a.set_Block(worlddata[4][i][j][k], i, j, k, worldsize);
                        a.draw_Block();
                    }
                }
        glPopMatrix();

        glPushMatrix();//底 1
        glRotatef(180, 1, 0, 0);
        glTranslatef(-worldsize * 1.5 + 0.5, -worldsize * 1.5 + 0.5, worldsize / 2 - 0.5);
        for (int i = worldsize + 1; i < worldsize * 2 - 1; i++)
            for (int j = worldsize + 1; j < worldsize * 2 - 1; j++)
                for (int k = 0; k < worldsize; k++)
                {
                    if (worlddata[1][i][j][k][2] == draw_type_list[h])
                    {
                        a.set_Block(worlddata[1][i][j][k], i, j, k, worldsize);
                        a.draw_Block();
                    }
                }
        glPopMatrix();
    }

    if (player.inwater && (mode == 4))
    {
        player.re_Player_positon(playerdata);
        glPushMatrix();
        draw_face((int)playerdata[0]);
        glPushMatrix();
        glTranslatef(playerdata[1], playerdata[2], playerdata[3]);
        a.draw_waterbox();
        glPopMatrix();
        glPopMatrix();
    }

}

//编辑模式
void World::draw_World_edit(int mode)//绘制
{
    Block a(0,0, 0, 0, 0);

    if (mode != 4)
    {
        glPushMatrix();
        draw_face((int)playerdata[0]);
        player.draw_Player_edit();
        glPopMatrix();
    }

    glPushMatrix();//顶 0
    glTranslatef(-worldsize * 1.5 + 0.5, -worldsize * 1.5 + 0.5, worldsize / 2 - 0.5);
    for (int i = worldsize + 1; i < worldsize * 2 - 1; i++)
        for (int j = worldsize + 1; j < worldsize * 2 - 1; j++)
            for (int k = 0; k < worldsize; k++)
            {
                glPushName(0);
                glPushName(i);
                glPushName(j);
                glPushName(k);
                a.set_Block(worlddata[0][i][j][k], i, j, k, worldsize);
                a.draw_Block_edit();
                glPopName();
                glPopName();
                glPopName();
                glPopName();
            }
    glPopMatrix();


    glPushMatrix();//前 2
    glRotatef(90, 1, 0, 0);
    glTranslatef(-worldsize * 1.5 + 0.5, -worldsize * 1.5 + 0.5, worldsize / 2 - 0.5);
    for (int i = 0; i < worldsize * 2 - 1; i++)
        for (int j = 0; j < worldsize * 3; j++)
            for (int k = 0; k < worldsize; k++)
            {
                glPushName(2);
                glPushName(i);
                glPushName(j);
                glPushName(k);
                a.set_Block(worlddata[2][i][j][k], i, j, k, worldsize);
                a.draw_Block_edit();
                glPopName();
                glPopName();
                glPopName();
                glPopName();
            }
    glPopMatrix();
    glPopName();


    glPushMatrix();//右 5（面对）
    glRotatef(90, 0, 0, 1);
    glRotatef(90, 1, 0, 0);
    glTranslatef(-worldsize * 1.5 + 0.5, -worldsize * 1.5 + 0.5, worldsize / 2 - 0.5);
    for (int i = 0; i < worldsize * 2 - 1; i++)
        for (int j = 0; j < worldsize * 3; j++)
            for (int k = 0; k < worldsize; k++)
            {
                glPushName(5);
                glPushName(i);
                glPushName(j);
                glPushName(k);
                a.set_Block(worlddata[5][i][j][k], i, j, k, worldsize);
                a.draw_Block_edit();
                glPopName();
                glPopName();
                glPopName();
                glPopName();
            }
    glPopMatrix();
    glPopName();


    glPushMatrix();//后3
    glRotatef(180, 0, 0, 1);
    glRotatef(90, 1, 0, 0);
    glTranslatef(-worldsize * 1.5 + 0.5, -worldsize * 1.5 + 0.5, worldsize / 2 - 0.5);
    for (int i = 0; i < worldsize * 2 - 1; i++)
        for (int j = 0; j < worldsize * 3; j++)
            for (int k = 0; k < worldsize; k++)
            {
                glPushName(3);
                glPushName(i);
                glPushName(j);
                glPushName(k);
                a.set_Block(worlddata[3][i][j][k], i, j, k, worldsize);
                a.draw_Block_edit();
                glPopName();
                glPopName();
                glPopName();
                glPopName();
            }
    glPopMatrix();
    glPopName();


    glPushMatrix();//左 4
    glRotatef(270, 0, 0, 1);
    glRotatef(90, 1, 0, 0);
    glTranslatef(-worldsize * 1.5 + 0.5, -worldsize * 1.5 + 0.5, worldsize / 2 - 0.5);
    for (int i = 0; i < worldsize * 2 - 1; i++)
        for (int j = 0; j < worldsize * 3; j++)
            for (int k = 0; k < worldsize; k++)
            {
                glPushName(4);
                glPushName(i);
                glPushName(j);
                glPushName(k);
                a.set_Block(worlddata[4][i][j][k], i, j, k, worldsize);
                a.draw_Block_edit();
                glPopName();
                glPopName();
                glPopName();
                glPopName();
            }
    glPopMatrix();
    glPopName();


    glPushMatrix();//底 1
    glRotatef(180, 1, 0, 0);
    glTranslatef(-worldsize * 1.5 + 0.5, -worldsize * 1.5 + 0.5, worldsize / 2 - 0.5);
    for (int i = worldsize + 1; i < worldsize * 2 - 1; i++)
        for (int j = worldsize + 1; j < worldsize * 2 - 1; j++)
            for (int k = 0; k < worldsize; k++)
            {
                glPushName(1);
                glPushName(i);
                glPushName(j);
                glPushName(k);
                a.set_Block(worlddata[1][i][j][k], i, j, k, worldsize);
                a.draw_Block_edit();
                glPopName();
                glPopName();
                glPopName();
                glPopName();
            }
    glPopMatrix();
    glPopName();

}

//数据储存
void World::output_worlddata()
{
    int world_number,world_ID;
    string world_name, world_place;
    const char* world_dataplace;
    ifstream input;
    input.open("./materials/data/worldtitle.txt");
    input >> world_number;

    for (int i=0; i < world_number; i++)
    {
        input >> world_ID >> world_name >> world_place;
        if (worldID == world_ID) break;
    }

    ofstream output;
    world_dataplace = world_place.c_str();
    output.open(world_dataplace);

    output << worldID << " " << worldsize <<" "<<time<<endl;

    player.re_Player_positon(playerdata);
    output << playerdata[0] << " " << playerdata[1] << " " << playerdata[2] << " " << playerdata[3] << " "<<endl;

    for (int h = 0; h < 6; h++)
    {
        for (int i = 0; i < 3 * worldsize; i++)
        {
            for (int j = 0; j < 3 * worldsize; j++)
            {
                for (int k = 0; k < worldsize; k++)
                {
                    for (int l = 0; l < 3 ; l++)//目前一个方块有3个数据
                        output<<worlddata[h][i][j][k][l]<<" ";
                    output << "  ";
                }
                output <<endl;
            }
            output << endl;
            output << endl;
        }
        output << endl;
        output << endl;
        output << endl;
    }

    input.close();
    output.close();

}

//数据读取
void World::input_worlddata()
{
    int world_number, world_ID;
    string world_name, world_place;
    const char* world_dataplace;
    ifstream input;
    input.open("./materials/data/worldtitle.txt");
    input >> world_number;

    for (int i = 0; i < world_number; i++)
    {
        input >> world_ID >> world_name >> world_place;
        if (worldID == world_ID) break;
    }

    ifstream iutputdata;
    world_dataplace = world_place.c_str();
    iutputdata.open(world_dataplace);

    iutputdata >> worldID >> worldsize>>time;

    iutputdata >> playerdata[0] >> playerdata[1] >> playerdata[2] >> playerdata[3];
    player.set_Player(playerdata[0], playerdata[1], playerdata[2], playerdata[3], 0, 0);
    player.Player_move_re(-1, -1, -1);

    for (int h = 0; h < 6; h++)
    {
        for (int i = 0; i < 3 * worldsize; i++)
        {
            for (int j = 0; j < 3 * worldsize; j++)
            {
                for (int k = 0; k < worldsize; k++)
                {
                    for (int l = 0; l < 3; l++)//目前一个方块只有3个数据
                        iutputdata >> worlddata[h][i][j][k][l];
                }
            }
        }
    }

    input.close();
    iutputdata.close();

    draw_world_test();
    draw_world_lightlist();
}

//优化，减少绘制数目
void World::draw_world_test()
{
    for (int h = 0; h < 6; h++)
    {
        for (int i = 0; i < 3 * worldsize; i++)
        {
            for (int j = 0; j < 3 * worldsize; j++)
            {
                for (int k = 0; k < worldsize; k++)
                {
                    //简单来说，上面的上面有方块就不画了，方块是否绘制看六面和是否为0，int 默认初始为 0
                    draw_world_singletest(h, i, j, k);
                }
            }
        }
    }
}

//单方块测试
void World::draw_world_singletest(int face, int x, int y, int z)
{
    //old简单来说，上面的上面有方块就不画了，方块是否绘制看六面和是否为0，int 默认初始为 0
    /*
    if (worlddata[face][x][y][z][0])
    {
        worlddata[face][x][y][z][3] = 0;
        for (int ii = 4; ii < 10; ii++)
            worlddata[face][x][y][z][ii] = 0;

        //face0-[4]
        if ((z + 1) < worldsize)
            if (worlddata[face][x][y][z + 1][0] == 0)
                worlddata[face][x][y][z][4] = 1;
        if ((z + 1) >= worldsize)
            worlddata[face][x][y][z][4] = 1;

        //face1-[5]
        if ((z - 1) >= 0)
        {
            if (worlddata[face][x][y][z - 1][0] == 0)
                worlddata[face][x][y][z][5] = 1;
        }

        //face2-[6]
        if ((y - 1) >= 0)
            if (worlddata[face][x][y - 1][z][0] == 0)
                worlddata[face][x][y][z][6] = 1;

        //face3-[7]
        if ((y + 1) < (worldsize * 2))
            if (worlddata[face][x][y + 1][z][0] == 0)
                worlddata[face][x][y][z][7] = 1;

        //face4-[8]
        if ((x - 1) >= 0)
            if (worlddata[face][x - 1][y][z][0] == 0)
                worlddata[face][x][y][z][8] = 1;

        //face5-[9]
        if ((x + 1) < (worldsize * 1.5 - 1))
            if (worlddata[face][x + 1][y][z][0] == 0)
                worlddata[face][x][y][z][9] = 1;

        for (int ii = 4; ii < 10; ii++)
            worlddata[face][x][y][z][3] += worlddata[face][x][y][z][ii];

    }
    */

    //new
    int temp[5];//临时存放
    temp[0] = face;
    temp[1] = x;
    temp[2] = y;
    temp[3] = z;
    temp[4] = 0;

    if (worlddata[face][x][y][z][0])//先有方块！
    {
        //初始化，默认所有面不显示
        worlddata[face][x][y][z][3] = 0;
        for (int ii = 4; ii < 10; ii++)
            worlddata[face][x][y][z][ii] = 0;

        //0面-[4]，无争议，最为简单
        if ((z + 1) < worldsize)//若上方无方块显示此面
        {
            if ((worlddata[face][x][y][z + 1][0] == 0) || draw_world_rules(face, x, y, z + 1, face, x, y, z))
                worlddata[face][x][y][z][4] = 1;
        }
        else//最顶上当然得显示
            worlddata[face][x][y][z][4] = 1;

        //1面-[5]
        if ((z - 1) >= 0) //若下方无方块显示此面
        {
            if ((worlddata[face][x][y][z - 1][0] == 0) || draw_world_rules(face, x, y, z - 1, face, x, y, z))
                worlddata[face][x][y][z][5] = 1;
        }
        else if ((x >= (worldsize  + 1)) && (x <= (worldsize * 2 - 2)) && (y >= (worldsize  + 1)) && (y <= (worldsize * 2 - 2))) //若面心最底层不显示此面
        {
            worlddata[face][x][y][z][5] = 0;
        }
        else //不为面心最底层，调用pram标准化,检测下方方块。
        {
            temp[0] = face;
            temp[1] = x;
            temp[2] = y;
            temp[3] = z - 1;
            temp[4] = 0;

            modify_pram(temp);
            if ((worlddata[temp[0]][temp[1]][temp[2]][temp[3]][0] == 0) || draw_world_rules(temp[0],temp[1],temp[2],temp[3],face,x,y,z))
                worlddata[face][x][y][z][5] = 1;

        }

        //2-5面分类讨论
        if (face > 1)
        {
            //2面-[6]
            if ((y - 1) >= 0)
            {
                if ((worlddata[face][x][y - 1][z][0] == 0) || draw_world_rules(face, x, y - 1, z, face, x, y, z))
                    worlddata[face][x][y][z][6] = 1;
            }
            else
                worlddata[face][x][y][z][6] = 1;

            //3面-[7]
            if ((y + 1) < worldsize * 3)
            {
                if ((worlddata[face][x][y + 1][z][0] == 0) || draw_world_rules(face, x, y + 1, z, face, x, y, z))
                    worlddata[face][x][y][z][7] = 1;
            }
            else
                worlddata[face][x][y][z][7] = 1;

            //4面-[8]
            if ((x - 1) >= 0)
            {
                if ((worlddata[face][x - 1][y][z][0] == 0) || draw_world_rules(face, x - 1, y, z, face, x, y, z))
                    worlddata[face][x][y][z][8] = 1;
            }
            else
                worlddata[face][x][y][z][8] = 1;

            //5面-[9]
            if ((x + 1) <= (worldsize * 2 - 2))
            {
                if ((worlddata[face][x + 1][y][z][0] == 0) || draw_world_rules(face, x + 1, y, z, face, x, y, z))
                    worlddata[face][x][y][z][9] = 1;
            }
            else
            {
                temp[0] = face;
                temp[1] = x + 1;
                temp[2] = y;
                temp[3] = z;
                temp[4] = 0;

                modify_pram(temp);
                if ((worlddata[temp[0]][temp[1]][temp[2]][temp[3]][0] == 0) || draw_world_rules(temp[0], temp[1], temp[2], temp[3], face, x, y, z))
                    worlddata[face][x][y][z][9] = 1;

            }
        }
        else {
            //2面-[6]
            if ((y - 1) >= (worldsize + 1))
            {
                if ((worlddata[face][x][y - 1][z][0] == 0) || draw_world_rules(face, x, y - 1, z, face, x, y, z))
                    worlddata[face][x][y][z][6] = 1;
            }
            else
            {
                temp[0] = face;
                temp[1] = x;
                temp[2] = y - 1;
                temp[3] = z;
                temp[4] = 0;

                modify_pram(temp);
                if ((worlddata[temp[0]][temp[1]][temp[2]][temp[3]][0] == 0) || draw_world_rules(temp[0], temp[1], temp[2], temp[3], face, x, y, z))
                    worlddata[face][x][y][z][6] = 1;

            }

            //3面-[7]
            if ((y + 1) <= (worldsize * 2 - 2))
            {
                if ((worlddata[face][x][y + 1][z][0] == 0) || draw_world_rules(face, x, y + 1, z, face, x, y, z))
                    worlddata[face][x][y][z][7] = 1;
            }
            else
            {
                temp[0] = face;
                temp[1] = x;
                temp[2] = y + 1;
                temp[3] = z;
                temp[4] = 0;

                modify_pram(temp);
                if ((worlddata[temp[0]][temp[1]][temp[2]][temp[3]][0] == 0) || draw_world_rules(temp[0], temp[1], temp[2], temp[3], face, x, y, z))
                    worlddata[face][x][y][z][7] = 1;

            }

            //4面-[8]
            if ((x - 1) >= (worldsize + 1))
            {
                if ((worlddata[face][x - 1][y][z][0] == 0) || draw_world_rules(face, x - 1, y, z, face, x, y, z))
                    worlddata[face][x][y][z][8] = 1;
            }
            else
            {
                temp[0] = face;
                temp[1] = x - 1;
                temp[2] = y;
                temp[3] = z;
                temp[4] = 0;

                modify_pram(temp);
                if ((worlddata[temp[0]][temp[1]][temp[2]][temp[3]][0] == 0) || draw_world_rules(temp[0], temp[1], temp[2], temp[3], face, x, y, z))
                    worlddata[face][x][y][z][8] = 1;

            }

            //5面-[9]
            if ((x + 1) <= (worldsize * 2 - 2))
            {
                if ((worlddata[face][x + 1][y][z][0] == 0) || draw_world_rules(face, x + 1, y, z, face, x, y, z))
                    worlddata[face][x][y][z][9] = 1;
            }
            else
            {
                temp[0] = face;
                temp[1] = x + 1;
                temp[2] = y;
                temp[3] = z;
                temp[4] = 0;

                modify_pram(temp);
                if ((worlddata[temp[0]][temp[1]][temp[2]][temp[3]][0] == 0) || draw_world_rules(temp[0], temp[1], temp[2], temp[3], face, x, y, z))
                    worlddata[face][x][y][z][9] = 1;

            }
        }

        //老规矩对吧，方块是否显示由六个面决定
        for (int ii = 4; ii < 10; ii++)
            worlddata[face][x][y][z][3] += worlddata[face][x][y][z][ii];
    }
}

//绘制规则
int World::draw_world_rules(int face1, int x1, int y1, int z1, int face2, int x2, int y2, int z2)//后or2为绘制方块，返回1绘制。
{
    //流体绘制规则，不画与实体方块界面
    if (worlddata[face2][x2][y2][z2][2] == 5)
    {
        if (worlddata[face1][x1][y1][z1][2] == 0)
            return 0;
    }

    //透明非完全方块规则，（实际上这里drawface无用，只有draw总合生效），如被实体方块包围则不画物体
    if (worlddata[face2][x2][y2][z2][2] == 4)
    {
        if (worlddata[face1][x1][y1][z1][2] == 0)
            return 0;
    }

        //透明方块


        //普通规则
    else if (worlddata[face1][x1][y1][z1][2] != worlddata[face2][x2][y2][z2][2])
        return 1;

    return 0;
}

//光照列表
void World::draw_world_lightlist()
{
    light_num = 0;
    light_list[light_num][0] = -1;
    light_list[light_num][1] = 5;
    light_list[light_num][2] = 4;
    light_list[light_num][3] = 3;

    for (int h = 0; h < 6; h++)//面
        for (int i = 0; i < 3 * worldsize; i++)
            for (int j = 0; j < 3 * worldsize; j++)
                for (int k = 0; k < worldsize; k++)
                {
                    draw_world_singlelightlist(h, i, j, k, 1);
                    if (light_num==7)
                        return;
                }

}

//单方块列表操作
void World::draw_world_singlelightlist(int face, int x, int y, int z,int act)
{
    if (act > 0)//加入
    {
        if ((worlddata[face][x][y][z][0] == 18) && (worlddata[face][x][y][z][2] == 0))
        {

            light_num++;
            if (light_num > 7)
            {
                light_num--;
                return;
            }

            light_list[light_num][0] = face;
            light_list[light_num][1] = x;
            light_list[light_num][2] = y;
            light_list[light_num][3] = z;
            light_list[light_num][4] = 1;
            light_list[light_num][5] = 2;
            light_list[light_num][6] = 2;
            light_list[light_num][7] = 1;
            light_list[light_num][8] = 0;
            light_list[light_num][9] = 0.125;
        }
        if ((worlddata[face][x][y][z][0] == 1) && (worlddata[face][x][y][z][2] == 4))
        {

            light_num++;
            if (light_num > 7)
            {
                light_num--;
                return;
            }

            light_list[light_num][0] = face;
            light_list[light_num][1] = x;
            light_list[light_num][2] = y;
            light_list[light_num][3] = z;
            light_list[light_num][4] = 1;
            light_list[light_num][5] = 2;
            light_list[light_num][6] = 2;
            light_list[light_num][7] = 2;
            light_list[light_num][8] = 0;
            light_list[light_num][9] = 1;
        }
        if ((worlddata[face][x][y][z][0] == 20) && (worlddata[face][x][y][z][2] == 0))
        {
            light_num++;
            if (light_num > 7)
            {
                light_num--;
                return;
            }

            light_list[light_num][0] = face;
            light_list[light_num][1] = x;
            light_list[light_num][2] = y;
            light_list[light_num][3] = z;
            light_list[light_num][4] = 1;
            light_list[light_num][5] = 1;
            light_list[light_num][6] = 1;
            light_list[light_num][7] = 1;
            light_list[light_num][8] = 0;
            light_list[light_num][9] = 0.125;
        }
    }
    else if (act < 0)//删除
    {
        if (((worlddata[face][x][y][z][0] == 1) && (worlddata[face][x][y][z][2] == 4)) || ((worlddata[face][x][y][z][0] == 18) && (worlddata[face][x][y][z][2] == 0))|| ((worlddata[face][x][y][z][0] == 20) && (worlddata[face][x][y][z][2] == 0)))
        {
            int del_num;

            for (int i = 1; i <= light_num; i++)
                if ((face == light_list[i][0]) && (x == light_list[i][1]) && (y == light_list[i][2]) && (z == light_list[i][3]))
                {
                    del_num = i;
                    break;
                }

            for (int i = del_num; i < light_num; i++)
                for (int j = 0; j < 10; j++)
                    light_list[i][j] = light_list[i + 1][j];

            light_num--;
        }
    }
}

//光照列表回调
int World::re_draw_world_lightlist(float set_light_list[8][10])
{
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 10; j++)
            set_light_list[i][j] = light_list[i][j];

    return light_num;
}

//回调给定位置的方块参数
int World::re_worlddata(int face, int x, int y, int z, int data)
{
    int parm[5];

    parm[0] = face;
    parm[1] = x;
    parm[2] = y;
    parm[3] = z;
    parm[4] = 0;

    modify_pram(parm);
    return worlddata[parm[0]][parm[1]][parm[2]][parm[3]][data];
}

//回调世界大小
int World::re_worldsize()
{
    return worldsize;
}

int World::re_worldtime()
{
    return time;
}








