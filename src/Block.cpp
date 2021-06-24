//
// Created by Dell on 2021/6/24.
//

#include "Block.h"
using namespace std;



Block::Block() {
    cerr << "fuck" << endl;
    BlockID = 0;
    Blocktype = 0;
    x = 0;
    y = 0;
    z = 0;
    faceing_x = 0;
    faceing_y = 0;
    faceing_z = 1;
    for (int i = 0; i < 6; i++)
        textureID[i] = 0;
    block_toward = 0;
    block_toward_mode = 0;
}

Block::Block(int ID,int type,int set_x, int set_y, int set_z) {
    BlockID = ID;
    Blocktype = type;
    x = set_x;
    y = set_y;
    z = set_z;
    faceing_x = 0;
    faceing_y = 0;
    faceing_z = 1;
    for (int i = 0; i < 6; i++)
        textureID[i] = 0;
    block_toward = 0;
    block_toward_mode = 0;
}

//方块格式与数据
void Block::set_Block(const int data[], int set_x, int set_y, int set_z,int set_size) {

    BlockID = data[0];
    if (BlockID)
    {
        block_toward = data[1];
        block_toward_mode = 0;

        Blocktype = data[2];

        x = set_x;
        y = set_y;
        z = set_z;

        faceing_x = 0;
        faceing_y = 0;
        faceing_z = 1;

        draw = data[3];
        for (int ii = 4; ii < 10; ii++)
            drawface[ii-4]= data[ii];

        if (set_size)
        {
            if (x <= set_size)//左
                faceing_x = -1;
            else if (x >= set_size * 2 - 1)
                faceing_x = 1;

            if (y <= set_size)//前
                faceing_y = -1;
            else if (y >= set_size * 2 - 1)
                faceing_y = 1;
        }

        //初始化
        init_Block(BlockID, Blocktype);
    }
}

//方块数据初始化（最好通过读入文件实现，参数包括材质，碰撞体积，反光）
void Block::init_Block(int ID, int type) {

    BlockID = ID;
    Blocktype = type;

    for (int i = 0; i < 6; i++)
        textureID[i] = 0;

    //初始化光照材质
    block_ambient[0] = 0.5; block_ambient[1] = 0.5; block_ambient[2] = 0.5; block_ambient[3] = 1.0;// 环境颜色
    block_diffuse[0] = 0.8; block_diffuse[1] = 0.8; block_diffuse[2] = 0.8; block_diffuse[3] = 1.0;//散射颜色
    block_specluar[0] = 0.2; block_specluar[1] = 0.2; block_specluar[2] = 0.2; block_specluar[3] = 1.0;//镜面颜色
    block_shininess[0] = 0.0;//镜面指数
    block_emission[0] = 0; block_emission[1] = 0; block_emission[2] = 0; block_emission[3] = 1.0;//发射颜色

    if (Blocktype == 0)
    {
        //导入材质
        switch (BlockID) {
            case -1: {
                for (int i = 0; i < 6; i++)
                    textureID[i] = 20;
            }break;//基岩
            case 1: {
                for (int i = 0; i < 6; i++)
                    textureID[i] = 16;
            } break;//石头
            case 2: {
                for (int i = 0; i < 6; i++)
                    textureID[i] = 1;
            } break;//泥土
            case 3: {
                textureID[0] = 2;
                textureID[1] = 1;
                textureID[2] = 3;
                textureID[3] = 3;
                textureID[4] = 3;
                textureID[5] = 3;

                if (faceing_x)
                {
                    if (faceing_x == 1)
                        textureID[5] = textureID[0];
                    else
                        textureID[4] = textureID[0];
                }
                if (faceing_y)
                {
                    if (faceing_y == 1)
                        textureID[3] = textureID[0];
                    else
                        textureID[2] = textureID[0];
                }
            } break;//草地
            case 4: {
                textureID[0] = 18;
                textureID[1] = 1;
                textureID[2] = 19;
                textureID[3] = 19;
                textureID[4] = 19;
                textureID[5] = 19;

                if (faceing_x)
                {
                    if (faceing_x == 1)
                        textureID[5] = textureID[0];
                    else
                        textureID[4] = textureID[0];
                }
                if (faceing_y)
                {
                    if (faceing_y == 1)
                        textureID[3] = textureID[0];
                    else
                        textureID[2] = textureID[0];
                }
            } break;//干草地
            case 5: {
                textureID[0] = 5;
                textureID[1] = 1;
                textureID[2] = 4;
                textureID[3] = 4;
                textureID[4] = 4;
                textureID[5] = 4;

                if (faceing_x)
                {
                    if (faceing_x == 1)
                        textureID[5] = textureID[0];
                    else
                        textureID[4] = textureID[0];
                }
                if (faceing_y)
                {
                    if (faceing_y == 1)
                        textureID[3] = textureID[0];
                    else
                        textureID[2] = textureID[0];
                }
            } break;//雪地
            case 6: {
                for (int i = 0; i < 6; i++)
                    textureID[i] = 5;
            } break;//雪
            case 7: {
                for (int i = 0; i < 6; i++)
                    textureID[i] = 6;
            } break;//圆石
            case 8: {
                for (int i = 0; i < 6; i++)
                    textureID[i] = 7;
            } break;//沙
            case 9: {
                for (int i = 0; i < 6; i++)
                    textureID[i] = 8;

                block_shininess[0] = 5.0;

            } break;//冰
            case 10: {
                for (int i = 0; i < 6; i++)
                    textureID[i] = 24;
                block_shininess[0] = 20.0;//镜面指数
                block_specluar[0] = 0.8;
                block_specluar[1] = 0.8;
                block_specluar[2] = 0.8;
                block_specluar[3] = 1.0;//发射颜色
            } break;//黏土
            case 11: {
                textureID[0] = 22;
                textureID[1] = 23;
                textureID[2] = 21;
                textureID[3] = 21;
                textureID[4] = 21;
                textureID[5] = 21;
            } break;//仙人掌
            case 12: {
                textureID[0] = 12;
                textureID[1] = 12;
                textureID[2] = 11;
                textureID[3] = 11;
                textureID[4] = 11;
                textureID[5] = 11;

                block_toward_mode = 3;
            } break;//橡木
            case 13: {
                for (int i = 0; i < 6; i++)
                    textureID[i] = 13;
            } break;//橡木木板
            case 14: {
                textureID[0] = 13;
                textureID[1] = 13;
                textureID[2] = 14;
                textureID[3] = 14;
                textureID[4] = 14;
                textureID[5] = 14;
            } break;//书架
            case 15: {
                textureID[0] = 16;
                textureID[1] = 16;
                textureID[2] = 15;
                textureID[3] = 15;
                textureID[4] = 15;
                textureID[5] = 15;
            } break;//煤矿
            case 16: {
                textureID[0] = 27;
                textureID[1] = 13;
                textureID[2] = 25;
                textureID[3] = 25;
                textureID[4] = 26;
                textureID[5] = 26;

                block_toward_mode = 2;
            } break;//工作台
            case 17: {
                textureID[0] = 30;
                textureID[1] = 30;
                textureID[2] = 28;
                textureID[3] = 29;
                textureID[4] = 29;
                textureID[5] = 29;

                block_toward_mode = 2;
            } break;//熔炉
            case 18: {
                for (int i = 0; i < 6; i++)
                    textureID[i] = 32;
                block_emission[0] = 0.8;
                block_emission[1] = 0.8;
                block_emission[2] = 0.3;
                block_emission[3] = 1.0;
            }break;//灯
            case 19: {
                for (int i = 0; i < 6; i++)
                    textureID[i] = 42;
                block_shininess[0] = 200.0;//镜面指数
                block_specluar[0] = 0.8;
                block_specluar[1] = 0.8;
                block_specluar[2] = 0.8;
                block_specluar[3] = 1.0;//发射颜色
            }break;//金块
            case 20: {
                for (int i = 0; i < 6; i++)
                    textureID[i] = 44;
                block_emission[0] = 0.9;
                block_emission[1] = 0.9;
                block_emission[2] = 0.9;
                block_emission[3] = 1.0;
            }break;//海晶灯
            default:break;
        };
    }
    else if (Blocktype == 1)//半砖
    {
        switch (BlockID) {
            case 1: {
            }break;
        }
    }
    else if (Blocktype == 2)//实体
    {
        switch (BlockID) {
            case 1: {}break;
        }
    }
    else if (Blocktype == 3)//透明方块
    {
        switch (BlockID) {
            case 1: {
                for (int i = 0; i < 6; i++)
                    textureID[i] = 10;
            } break;//玻璃
            case 2: {
                for (int i = 0; i < 6; i++)
                    textureID[i] = 31;
            } break;//叶子
        }
    }
    else if (Blocktype == 4)//透明无碰撞
    {

        switch (BlockID) {
            case 1: {
                for (int i = 0; i < 6; i++)
                    textureID[i] = 33;
                block_emission[0] = 0.4;
                block_emission[1] = 0.4;
                block_emission[2] = 0.15;
                block_emission[3] = 1.0;
            }break;//火把
            case 2: {
                for (int i = 0; i < 6; i++)
                    textureID[i] = 17;
            }break;//藤蔓
            case 3: {
                for (int i = 0; i < 6; i++)
                    textureID[i] = 35;
            }break;//铁轨
            case 4: {
                for (int i = 0; i < 6; i++)
                    textureID[i] = 37;
            }break;//铃兰
            case 5: {
                for (int i = 0; i < 6; i++)
                    textureID[i] = 38;
            }break;//蒲公英
            case 6: {
                for (int i = 0; i < 6; i++)
                    textureID[i] = 39;
            }break;//玫瑰
            case 7: {
                for (int i = 0; i < 6; i++)
                    textureID[i] = 36;
            }break;//绣球花
            case 8: {
                for (int i = 0; i < 6; i++)
                    textureID[i] = 40;
            }break;//灌木
            case 9: {
                for (int i = 0; i < 6; i++)
                    textureID[i] = 41;
            }break;//草
        }
    }
    else if (Blocktype == 5)//水体
    {
        switch (BlockID) {
            case 1: {
                for (int i = 0; i < 6; i++)
                    textureID[i] = 9;

                block_shininess[0] = 20.0;
                block_specluar[0] = 1;
                block_specluar[1] = 1;
                block_specluar[2] = 1;
                block_specluar[3] = 1.0;
            }break;//水
        }
    }
}

//方块绘制
void Block::draw_Block() {
    if (BlockID && draw) {
        glPushMatrix();
        glTranslated(x, y, z);
        if (block_toward_mode)//如果有朝向属性(实现)
        {
            int warp[6];
            for (int i = 0; i < 6; i++)
                warp[i]=drawface[i];

            if (block_toward_mode==3)
            {
                switch (block_toward)
                {
                    case 0:
                    case 1:break;
                    case 2:
                    case 3: {
                        drawface[0] = warp[2];
                        drawface[1] = warp[3];
                        drawface[2] = warp[1];
                        drawface[3] = warp[0];
                        drawface[4] = warp[4];
                        drawface[5] = warp[5];

                        glRotatef(90, 1, 0, 0);
                    }break;
                    case 4:
                    case 5: {
                        drawface[0] = warp[5];
                        drawface[1] = warp[4];
                        drawface[2] = warp[2];
                        drawface[3] = warp[3];
                        drawface[4] = warp[0];
                        drawface[5] = warp[1];

                        glRotatef(90, 0, 1, 0);
                    }break;
                    default:break;
                }
            }

            if (block_toward_mode == 2)
            {
                switch (block_toward)
                {
                    case 0:
                    case 1:
                    case 2:
                    case 3: break;
                    case 4:
                    case 5: {
                        drawface[0] = warp[0];
                        drawface[1] = warp[1];
                        drawface[2] = warp[5];
                        drawface[3] = warp[4];
                        drawface[4] = warp[2];
                        drawface[5] = warp[3];

                        glRotatef(90, 0, 0, 1);
                    }break;
                    default:break;
                }
            }
        }

        switch (Blocktype)
        {
            case 0: {
                glColor3f(1, 1, 1);

                glEnable(GL_CULL_FACE);//优化，只绘制面向部分
                glCullFace(GL_FRONT);

                glEnable(GL_TEXTURE_2D);
                glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);//指定绘制模式 MODULATE

                glMaterialfv(GL_FRONT, GL_AMBIENT, block_ambient);//环境颜色
                glMaterialfv(GL_FRONT, GL_DIFFUSE, block_diffuse);//散射颜色
                glMaterialfv(GL_FRONT, GL_SPECULAR, block_specluar);//镜面颜色
                glMaterialfv(GL_FRONT, GL_SHININESS, block_shininess);//镜面指数
                glMaterialfv(GL_FRONT, GL_EMISSION, block_emission);//发射颜色

                amount = 4;
                size = 0.25;

                //上 0 z+
                if (drawface[0]) {
                    glBindTexture(GL_TEXTURE_2D, texname[textureID[0]]);//指定绘制材质
                    for (int i = 0; i < amount; i++)
                        for (int j = 0; j < amount; j++)
                        {
                            glBegin(GL_QUADS);
                            glNormal3f(0.0f, 0.0f, 1.0f);
                            glTexCoord2f((i + 1) * size, (j + 1) * size);       glVertex3f(-0.5 + (i + 1) * size, -0.5 + (j + 1) * size, 0.5);
                            glTexCoord2f((i + 1) * size, j * size);       glVertex3f(-0.5 + (i + 1) * size, -0.5 + j * size, 0.5);
                            glTexCoord2f(i * size, j * size);       glVertex3f(-0.5 + i * size, -0.5 + j * size, 0.5);
                            glTexCoord2f(i * size, (j + 1) * size);       glVertex3f(-0.5 + i * size, -0.5 + (j + 1) * size, 0.5);
                            glEnd();
                        }
                }

                //下 1 z-
                if (drawface[1]) {
                    glBindTexture(GL_TEXTURE_2D, texname[textureID[1]]);//指定绘制材质
                    glBegin(GL_QUADS);
                    glNormal3f(0.0f, 0.0f, -1.0f);
                    glTexCoord2f(1, 1); glVertex3f(0.5, 0.5, -0.5);
                    glTexCoord2f(0, 1); glVertex3f(-0.5, 0.5, -0.5);
                    glTexCoord2f(0, 0); glVertex3f(-0.5, -0.5, -0.5);
                    glTexCoord2f(1, 0); glVertex3f(0.5, -0.5, -0.5);
                    glEnd();
                }

                //前 2 y-
                if (drawface[2]) {
                    glBindTexture(GL_TEXTURE_2D, texname[textureID[2]]);//指定绘制材质
                    glBegin(GL_QUADS);
                    glNormal3f(0.0f, -1.0f, 0.0f);
                    glTexCoord2f(0, 0); glVertex3f(0.5, -0.5, 0.5);
                    glTexCoord2f(0, 1); glVertex3f(0.5, -0.5, -0.5);
                    glTexCoord2f(1, 1); glVertex3f(-0.5, -0.5, -0.5);
                    glTexCoord2f(1, 0); glVertex3f(-0.5, -0.5, 0.5);
                    glEnd();
                }

                //后 3 y+
                if (drawface[3]) {
                    glBindTexture(GL_TEXTURE_2D, texname[textureID[3]]);//指定绘制材质
                    glBegin(GL_QUADS);
                    glNormal3f(0.0f, 1.0f, 0.0f);
                    glTexCoord2f(0, 0); glVertex3f(0.5, 0.5, 0.5);
                    glTexCoord2f(1, 0); glVertex3f(-0.5, 0.5, 0.5);
                    glTexCoord2f(1, 1); glVertex3f(-0.5, 0.5, -0.5);
                    glTexCoord2f(0, 1); glVertex3f(0.5, 0.5, -0.5);
                    glEnd();
                }

                //左 4 x-
                if (drawface[4]) {
                    glBindTexture(GL_TEXTURE_2D, texname[textureID[4]]);//指定绘制材质
                    glBegin(GL_QUADS);
                    glNormal3f(-1.0f, 0.0f, 0.0f);
                    glTexCoord2f(0, 0); glVertex3f(-0.5, 0.5, 0.5);
                    glTexCoord2f(1, 0); glVertex3f(-0.5, -0.5, 0.5);
                    glTexCoord2f(1, 1); glVertex3f(-0.5, -0.5, -0.5);
                    glTexCoord2f(0, 1); glVertex3f(-0.5, 0.5, -0.5);
                    glEnd();
                }

                //右 5 x+
                if (drawface[5]) {
                    glBindTexture(GL_TEXTURE_2D, texname[textureID[5]]);//指定绘制材质
                    glBegin(GL_QUADS);
                    glNormal3f(1.0f, 0.0f, 0.0f);
                    glTexCoord2f(0, 0); glVertex3f(0.5, 0.5, 0.5);
                    glTexCoord2f(0, 1); glVertex3f(0.5, 0.5, -0.5);
                    glTexCoord2f(1, 1); glVertex3f(0.5, -0.5, -0.5);
                    glTexCoord2f(1, 0); glVertex3f(0.5, -0.5, 0.5);
                    glEnd();
                }

                //new 不太对劲
                /*
                            //上 0 z+
                if (drawface[0]) {
                    glBindTexture(GL_TEXTURE_2D, texname[textureID[0]]);//指定绘制材质
                    for (int i = 0; i < amount; i++)
                        for (int j = 0; j < amount; j++)
                        {
                            glBegin(GL_QUADS);
                            glNormal3f(0.0f, 0.0f, 1.0f);
                            glTexCoord2f((i + 1) * size, (j + 1) * size);       glVertex3f(-0.5 + (i + 1) * size, -0.5 + (j + 1) * size, 0.5);
                            glTexCoord2f((i + 1) * size, j * size);       glVertex3f(-0.5 + (i + 1) * size, -0.5 + j * size, 0.5);
                            glTexCoord2f(i * size, j * size);       glVertex3f(-0.5 + i * size, -0.5 + j * size, 0.5);
                            glTexCoord2f(i * size, (j + 1) * size);       glVertex3f(-0.5 + i * size, -0.5 + (j + 1) * size, 0.5);
                            glEnd();
                        }
                }

                //down z-
                if (drawface[1]) {
                    glBindTexture(GL_TEXTURE_2D, texname[textureID[1]]);//指定绘制材质
                    glPushMatrix();
                    glRotatef(180, 1, 0, 0);
                    for (int i = 0; i < amount; i++)
                        for (int j = 0; j < amount; j++)
                        {
                            glBegin(GL_QUADS);
                            glNormal3f(0.0f, 0.0f, 1.0f);
                            glTexCoord2f((i + 1) * size, (j + 1) * size);       glVertex3f(-0.5 + (i + 1) * size, -0.5 + (j + 1) * size, 0.5);
                            glTexCoord2f((i + 1) * size, j * size);       glVertex3f(-0.5 + (i + 1) * size, -0.5 + j * size, 0.5);
                            glTexCoord2f(i * size, j * size);       glVertex3f(-0.5 + i * size, -0.5 + j * size, 0.5);
                            glTexCoord2f(i * size, (j + 1) * size);       glVertex3f(-0.5 + i * size, -0.5 + (j + 1) * size, 0.5);
                            glEnd();
                        }
                    glPopMatrix();
                }

                //前 2 y-
                if (drawface[2]) {
                    glBindTexture(GL_TEXTURE_2D, texname[textureID[2]]);//指定绘制材质
                    glPushMatrix();
                    glRotatef(90, 1, 0, 0);
                    glRotatef(180, 0, 0, 1);
                    for (int i = 0; i < amount; i++)
                        for (int j = 0; j < amount; j++)
                        {
                            glBegin(GL_QUADS);
                            glNormal3f(0.0f, 0.0f, 1.0f);
                            glTexCoord2f((i + 1) * size, (j + 1) * size);       glVertex3f(-0.5 + (i + 1) * size, -0.5 + (j + 1) * size, 0.5);
                            glTexCoord2f((i + 1) * size, j * size);       glVertex3f(-0.5 + (i + 1) * size, -0.5 + j * size, 0.5);
                            glTexCoord2f(i * size, j * size);       glVertex3f(-0.5 + i * size, -0.5 + j * size, 0.5);
                            glTexCoord2f(i * size, (j + 1) * size);       glVertex3f(-0.5 + i * size, -0.5 + (j + 1) * size, 0.5);
                            glEnd();
                        }
                    glPopMatrix();
                }

                //后 3 y+
                if (drawface[3]) {
                    glBindTexture(GL_TEXTURE_2D, texname[textureID[3]]);//指定绘制材质
                    glPushMatrix();
                    glRotatef(-90, 1, 0, 0);
                    glRotatef(0, 0, 0, 1);
                    for (int i = 0; i < amount; i++)
                        for (int j = 0; j < amount; j++)
                        {
                            glBegin(GL_QUADS);
                            glNormal3f(0.0f, 0.0f, 1.0f);
                            glTexCoord2f((i + 1) * size, (j + 1) * size);       glVertex3f(-0.5 + (i + 1) * size, -0.5 + (j + 1) * size, 0.5);
                            glTexCoord2f((i + 1) * size, j * size);       glVertex3f(-0.5 + (i + 1) * size, -0.5 + j * size, 0.5);
                            glTexCoord2f(i * size, j * size);       glVertex3f(-0.5 + i * size, -0.5 + j * size, 0.5);
                            glTexCoord2f(i * size, (j + 1) * size);       glVertex3f(-0.5 + i * size, -0.5 + (j + 1) * size, 0.5);
                            glEnd();
                        }
                    glPopMatrix();
                }

                //左 4 x-
                if (drawface[4]) {
                    glBindTexture(GL_TEXTURE_2D, texname[textureID[4]]);//指定绘制材质
                    glPushMatrix();
                    glRotatef(-90, 0, 1, 0);
                    glRotatef(90, 0, 0, 1);
                    for (int i = 0; i < amount; i++)
                        for (int j = 0; j < amount; j++)
                        {
                            glBegin(GL_QUADS);
                            glNormal3f(0.0f, 0.0f, 1.0f);
                            glTexCoord2f((i + 1) * size, (j + 1) * size);       glVertex3f(-0.5 + (i + 1) * size, -0.5 + (j + 1) * size, 0.5);
                            glTexCoord2f((i + 1) * size, j * size);       glVertex3f(-0.5 + (i + 1) * size, -0.5 + j * size, 0.5);
                            glTexCoord2f(i * size, j * size);       glVertex3f(-0.5 + i * size, -0.5 + j * size, 0.5);
                            glTexCoord2f(i * size, (j + 1) * size);       glVertex3f(-0.5 + i * size, -0.5 + (j + 1) * size, 0.5);
                            glEnd();
                        }
                    glPopMatrix();
                }

                //右 5 x+
                if (drawface[4]) {
                    glBindTexture(GL_TEXTURE_2D, texname[textureID[4]]);//指定绘制材质
                    glPushMatrix();
                    glRotatef(90, 0, 1, 0);
                    glRotatef(-90, 0, 0, 1);
                    for (int i = 0; i < amount; i++)
                        for (int j = 0; j < amount; j++)
                        {
                            glBegin(GL_QUADS);
                            glNormal3f(0.0f, 0.0f, 1.0f);
                            glTexCoord2f((i + 1) * size, (j + 1) * size);       glVertex3f(-0.5 + (i + 1) * size, -0.5 + (j + 1) * size, 0.5);
                            glTexCoord2f((i + 1) * size, j * size);       glVertex3f(-0.5 + (i + 1) * size, -0.5 + j * size, 0.5);
                            glTexCoord2f(i * size, j * size);       glVertex3f(-0.5 + i * size, -0.5 + j * size, 0.5);
                            glTexCoord2f(i * size, (j + 1) * size);       glVertex3f(-0.5 + i * size, -0.5 + (j + 1) * size, 0.5);
                            glEnd();
                        }
                    glPopMatrix();
                }
                */

                //old 性能好，效果差
                /*
                //上 0 z+
                if (drawface[0]) {
                    glBindTexture(GL_TEXTURE_2D, texname[textureID[0]]);//指定绘制材质
                    glBegin(GL_QUADS);
                    glNormal3f(0.0f, 0.0f, 1.0f);
                    glTexCoord2f(1, 1); glVertex3f(0.5, 0.5, 0.5);
                    glTexCoord2f(1, 0); glVertex3f(0.5, -0.5, 0.5);
                    glTexCoord2f(0, 0); glVertex3f(-0.5, -0.5, 0.5);
                    glTexCoord2f(0, 1); glVertex3f(-0.5, 0.5, 0.5);
                    glEnd();
                }
                //下 1 z-
                if (drawface[1]) {
                    glBindTexture(GL_TEXTURE_2D, texname[textureID[1]]);//指定绘制材质
                    glBegin(GL_QUADS);
                    glNormal3f(0.0f, 0.0f, -1.0f);
                    glTexCoord2f(1, 1); glVertex3f(0.5, 0.5, -0.5);
                    glTexCoord2f(0, 1); glVertex3f(-0.5, 0.5, -0.5);
                    glTexCoord2f(0, 0); glVertex3f(-0.5, -0.5, -0.5);
                    glTexCoord2f(1, 0); glVertex3f(0.5, -0.5, -0.5);
                    glEnd();
                }

                //前 2 y-
                if (drawface[2]) {
                    glBindTexture(GL_TEXTURE_2D, texname[textureID[2]]);//指定绘制材质
                    glBegin(GL_QUADS);
                    glNormal3f(0.0f, -1.0f, 0.0f);
                    glTexCoord2f(0, 0); glVertex3f(0.5, -0.5, 0.5);
                    glTexCoord2f(0, 1); glVertex3f(0.5, -0.5, -0.5);
                    glTexCoord2f(1, 1); glVertex3f(-0.5, -0.5, -0.5);
                    glTexCoord2f(1, 0); glVertex3f(-0.5, -0.5, 0.5);
                    glEnd();
                }

                //后 3 y+
                if (drawface[3]) {
                    glBindTexture(GL_TEXTURE_2D, texname[textureID[3]]);//指定绘制材质
                    glBegin(GL_QUADS);
                    glNormal3f(0.0f, 1.0f, 0.0f);
                    glTexCoord2f(0, 0); glVertex3f(0.5, 0.5, 0.5);
                    glTexCoord2f(1, 0); glVertex3f(-0.5, 0.5, 0.5);
                    glTexCoord2f(1, 1); glVertex3f(-0.5, 0.5, -0.5);
                    glTexCoord2f(0, 1); glVertex3f(0.5, 0.5, -0.5);
                    glEnd();
                }

                //左 4 x-
                if (drawface[4]) {
                    glBindTexture(GL_TEXTURE_2D, texname[textureID[4]]);//指定绘制材质
                    glBegin(GL_QUADS);
                    glNormal3f(-1.0f, 0.0f, 0.0f);
                    glTexCoord2f(0, 0); glVertex3f(-0.5, 0.5, 0.5);
                    glTexCoord2f(1, 0); glVertex3f(-0.5, -0.5, 0.5);
                    glTexCoord2f(1, 1); glVertex3f(-0.5, -0.5, -0.5);
                    glTexCoord2f(0, 1); glVertex3f(-0.5, 0.5, -0.5);
                    glEnd();
                }

                //右 5 x+
                if (drawface[5]) {
                    glBindTexture(GL_TEXTURE_2D, texname[textureID[5]]);//指定绘制材质
                    glBegin(GL_QUADS);
                    glNormal3f(1.0f, 0.0f, 0.0f);
                    glTexCoord2f(0, 0); glVertex3f(0.5, 0.5, 0.5);
                    glTexCoord2f(0, 1); glVertex3f(0.5, 0.5, -0.5);
                    glTexCoord2f(1, 1); glVertex3f(0.5, -0.5, -0.5);
                    glTexCoord2f(1, 0); glVertex3f(0.5, -0.5, 0.5);
                    glEnd();
                }
                */

                glDisable(GL_TEXTURE_2D);
                glDisable(GL_CULL_FACE);
            }break;
            case 1: {
                glColor3f(1, 1, 1);

                glEnable(GL_CULL_FACE);//优化，只绘制面向部分
                glCullFace(GL_FRONT);

                glEnable(GL_TEXTURE_2D);
                glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);//指定绘制模式 MODULATE

                glMaterialfv(GL_FRONT, GL_AMBIENT, block_ambient);//环境颜色
                glMaterialfv(GL_FRONT, GL_DIFFUSE, block_diffuse);//散射颜色
                glMaterialfv(GL_FRONT, GL_SPECULAR, block_specluar);//镜面颜色
                glMaterialfv(GL_FRONT, GL_SHININESS, block_shininess);//镜面指数
                glMaterialfv(GL_FRONT, GL_EMISSION, block_emission);//发射颜色


                //上 0 z+
                if (drawface[0]) {
                    glBindTexture(GL_TEXTURE_2D, texname[textureID[0]]);//指定绘制材质
                    glBegin(GL_QUADS);
                    glNormal3f(0.0f, 0.0f, 1.0f);
                    glTexCoord2f(1, 1); glVertex3f(0.5, 0.5, 0.5);
                    glTexCoord2f(1, 0); glVertex3f(0.5, -0.5, 0.5);
                    glTexCoord2f(0, 0); glVertex3f(-0.5, -0.5, 0.5);
                    glTexCoord2f(0, 1); glVertex3f(-0.5, 0.5, 0.5);
                    glEnd();
                }

                //下 1 z-
                if (drawface[1]) {
                    glBindTexture(GL_TEXTURE_2D, texname[textureID[1]]);//指定绘制材质
                    glBegin(GL_QUADS);
                    glNormal3f(0.0f, 0.0f, -1.0f);
                    glTexCoord2f(1, 1); glVertex3f(0.5, 0.5, -0.5);
                    glTexCoord2f(0, 1); glVertex3f(-0.5, 0.5, -0.5);
                    glTexCoord2f(0, 0); glVertex3f(-0.5, -0.5, -0.5);
                    glTexCoord2f(1, 0); glVertex3f(0.5, -0.5, -0.5);
                    glEnd();
                }


                //前 2 y-
                if (drawface[2]) {
                    glBindTexture(GL_TEXTURE_2D, texname[textureID[2]]);//指定绘制材质
                    glBegin(GL_QUADS);
                    glNormal3f(0.0f, -1.0f, 0.0f);
                    glTexCoord2f(0, 0); glVertex3f(0.5, -0.5, 0.5);
                    glTexCoord2f(0, 1); glVertex3f(0.5, -0.5, -0.5);
                    glTexCoord2f(1, 1); glVertex3f(-0.5, -0.5, -0.5);
                    glTexCoord2f(1, 0); glVertex3f(-0.5, -0.5, 0.5);
                    glEnd();
                }

                //后 3 y+
                if (drawface[3]) {
                    glBindTexture(GL_TEXTURE_2D, texname[textureID[3]]);//指定绘制材质
                    glBegin(GL_QUADS);
                    glNormal3f(0.0f, 1.0f, 0.0f);
                    glTexCoord2f(0, 0); glVertex3f(0.5, 0.5, 0.5);
                    glTexCoord2f(1, 0); glVertex3f(-0.5, 0.5, 0.5);
                    glTexCoord2f(1, 1); glVertex3f(-0.5, 0.5, -0.5);
                    glTexCoord2f(0, 1); glVertex3f(0.5, 0.5, -0.5);
                    glEnd();
                }

                //左 4 x-
                if (drawface[4]) {
                    glBindTexture(GL_TEXTURE_2D, texname[textureID[4]]);//指定绘制材质
                    glBegin(GL_QUADS);
                    glNormal3f(-1.0f, 0.0f, 0.0f);
                    glTexCoord2f(0, 0); glVertex3f(-0.5, 0.5, 0.5);
                    glTexCoord2f(1, 0); glVertex3f(-0.5, -0.5, 0.5);
                    glTexCoord2f(1, 1); glVertex3f(-0.5, -0.5, -0.5);
                    glTexCoord2f(0, 1); glVertex3f(-0.5, 0.5, -0.5);
                    glEnd();
                }

                //右 5 x+
                if (drawface[5]) {
                    glBindTexture(GL_TEXTURE_2D, texname[textureID[5]]);//指定绘制材质
                    glBegin(GL_QUADS);
                    glNormal3f(1.0f, 0.0f, 0.0f);
                    glTexCoord2f(0, 0); glVertex3f(0.5, 0.5, 0.5);
                    glTexCoord2f(0, 1); glVertex3f(0.5, 0.5, -0.5);
                    glTexCoord2f(1, 1); glVertex3f(0.5, -0.5, -0.5);
                    glTexCoord2f(1, 0); glVertex3f(0.5, -0.5, 0.5);
                    glEnd();
                }

                glDisable(GL_TEXTURE_2D);
                glDisable(GL_CULL_FACE);
            }break;
            case 2: {}break;
            case 3: {
                glColor3f(1, 1, 1);

                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                glEnable(GL_TEXTURE_2D);
                glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);//指定绘制模式 MODULATE

                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, block_ambient);//环境颜色
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, block_diffuse);//散射颜色
                glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, block_specluar);//镜面颜色
                glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, block_shininess);//镜面指数
                glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, block_emission);//发射颜色

                glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);


                //上 0 z+
                if (drawface[0]) {
                    glBindTexture(GL_TEXTURE_2D, texname[textureID[0]]);//指定绘制材质
                    glBegin(GL_QUADS);
                    glNormal3f(0.0f, 0.0f, 1.0f);
                    glTexCoord2f(1, 1); glVertex3f(0.5, 0.5, 0.5);
                    glTexCoord2f(1, 0); glVertex3f(0.5, -0.5, 0.5);
                    glTexCoord2f(0, 0); glVertex3f(-0.5, -0.5, 0.5);
                    glTexCoord2f(0, 1); glVertex3f(-0.5, 0.5, 0.5);
                    glEnd();
                }

                //下 1 z-
                if (drawface[1]) {
                    glBindTexture(GL_TEXTURE_2D, texname[textureID[1]]);//指定绘制材质
                    glBegin(GL_QUADS);
                    glNormal3f(0.0f, 0.0f, -1.0f);
                    glTexCoord2f(1, 1); glVertex3f(0.5, 0.5, -0.5);
                    glTexCoord2f(0, 1); glVertex3f(-0.5, 0.5, -0.5);
                    glTexCoord2f(0, 0); glVertex3f(-0.5, -0.5, -0.5);
                    glTexCoord2f(1, 0); glVertex3f(0.5, -0.5, -0.5);
                    glEnd();
                }


                //前 2 y-
                if (drawface[2]) {
                    glBindTexture(GL_TEXTURE_2D, texname[textureID[2]]);//指定绘制材质
                    glBegin(GL_QUADS);
                    glNormal3f(0.0f, -1.0f, 0.0f);
                    glTexCoord2f(0, 0); glVertex3f(0.5, -0.5, 0.5);
                    glTexCoord2f(0, 1); glVertex3f(0.5, -0.5, -0.5);
                    glTexCoord2f(1, 1); glVertex3f(-0.5, -0.5, -0.5);
                    glTexCoord2f(1, 0); glVertex3f(-0.5, -0.5, 0.5);
                    glEnd();
                }

                //后 3 y+
                if (drawface[3]) {
                    glBindTexture(GL_TEXTURE_2D, texname[textureID[3]]);//指定绘制材质
                    glBegin(GL_QUADS);
                    glNormal3f(0.0f, 1.0f, 0.0f);
                    glTexCoord2f(0, 0); glVertex3f(0.5, 0.5, 0.5);
                    glTexCoord2f(1, 0); glVertex3f(-0.5, 0.5, 0.5);
                    glTexCoord2f(1, 1); glVertex3f(-0.5, 0.5, -0.5);
                    glTexCoord2f(0, 1); glVertex3f(0.5, 0.5, -0.5);
                    glEnd();
                }

                //左 4 x-
                if (drawface[4]) {
                    glBindTexture(GL_TEXTURE_2D, texname[textureID[4]]);//指定绘制材质
                    glBegin(GL_QUADS);
                    glNormal3f(-1.0f, 0.0f, 0.0f);
                    glTexCoord2f(0, 0); glVertex3f(-0.5, 0.5, 0.5);
                    glTexCoord2f(1, 0); glVertex3f(-0.5, -0.5, 0.5);
                    glTexCoord2f(1, 1); glVertex3f(-0.5, -0.5, -0.5);
                    glTexCoord2f(0, 1); glVertex3f(-0.5, 0.5, -0.5);
                    glEnd();
                }

                //右 5 x+
                if (drawface[5]) {
                    glBindTexture(GL_TEXTURE_2D, texname[textureID[5]]);//指定绘制材质
                    glBegin(GL_QUADS);
                    glNormal3f(1.0f, 0.0f, 0.0f);
                    glTexCoord2f(0, 0); glVertex3f(0.5, 0.5, 0.5);
                    glTexCoord2f(0, 1); glVertex3f(0.5, 0.5, -0.5);
                    glTexCoord2f(1, 1); glVertex3f(0.5, -0.5, -0.5);
                    glTexCoord2f(1, 0); glVertex3f(0.5, -0.5, 0.5);
                    glEnd();
                }

                glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
                glDisable(GL_TEXTURE_2D);
                glDisable(GL_BLEND);
            }break;
            case 4: {
                glColor3f(1, 1, 1);

                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                glEnable(GL_TEXTURE_2D);
                glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);//指定绘制模式 MODULATE

                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, block_ambient);//环境颜色
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, block_diffuse);//散射颜色
                glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, block_specluar);//镜面颜色
                glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, block_shininess);//镜面指数
                glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, block_emission);//发射颜色

                glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

                switch (BlockID)
                {
                    case 1: {
                        glEnable(GL_CULL_FACE);//优化，只绘制面向部分
                        glCullFace(GL_FRONT);

                        //上 0 z+
                        glBindTexture(GL_TEXTURE_2D, texname[textureID[0]]);//指定绘制材质
                        glBegin(GL_QUADS);
                        glNormal3f(0.0f, 0.0f, 1.0f);
                        glTexCoord2f(0.5625, 0.5); glVertex3f(0.05, 0.05, 0.125);
                        glTexCoord2f(0.5625, 0.375); glVertex3f(0.05, -0.05, 0.125);
                        glTexCoord2f(0.4375, 0.375); glVertex3f(-0.05, -0.05, 0.125);
                        glTexCoord2f(0.4375, 0.5); glVertex3f(-0.05, 0.05, 0.125);
                        glEnd();

                        //前 2 y-
                        glBindTexture(GL_TEXTURE_2D, texname[textureID[2]]);//指定绘制材质
                        glBegin(GL_QUADS);
                        glNormal3f(0.0f, -1.0f, 0.0f);
                        glTexCoord2f(0.4375, 0.375); glVertex3f(0.05, -0.05, 0.125);
                        glTexCoord2f(0.4375, 1); glVertex3f(0.05, -0.05, -0.5);
                        glTexCoord2f(0.5625, 1); glVertex3f(-0.05, -0.05, -0.5);
                        glTexCoord2f(0.5625, 0.375); glVertex3f(-0.05, -0.05, 0.125);
                        glEnd();

                        //后 3 y+
                        glBindTexture(GL_TEXTURE_2D, texname[textureID[3]]);//指定绘制材质
                        glBegin(GL_QUADS);
                        glNormal3f(0.0f, 1.0f, 0.0f);
                        glTexCoord2f(0.4375, 0.375); glVertex3f(0.05, 0.05, 0.125);
                        glTexCoord2f(0.5625, 0.375); glVertex3f(-0.05, 0.05, 0.125);
                        glTexCoord2f(0.5625, 1); glVertex3f(-0.05, 0.05, -0.5);
                        glTexCoord2f(0.4375, 1); glVertex3f(0.05, 0.05, -0.5);
                        glEnd();

                        //左 4 x-
                        glBindTexture(GL_TEXTURE_2D, texname[textureID[4]]);//指定绘制材质
                        glBegin(GL_QUADS);
                        glNormal3f(-1.0f, 0.0f, 0.0f);
                        glTexCoord2f(0.4375, 0.375); glVertex3f(-0.05, 0.05, 0.125);
                        glTexCoord2f(0.5625, 0.375); glVertex3f(-0.05, -0.05, 0.125);
                        glTexCoord2f(0.5625, 1); glVertex3f(-0.05, -0.05, -0.5);
                        glTexCoord2f(0.4375, 1); glVertex3f(-0.05, 0.05, -0.5);
                        glEnd();

                        //右 5 x+
                        glBindTexture(GL_TEXTURE_2D, texname[textureID[5]]);//指定绘制材质
                        glBegin(GL_QUADS);
                        glNormal3f(1.0f, 0.0f, 0.0f);
                        glTexCoord2f(0.4375, 0.375); glVertex3f(0.05, 0.05, 0.125);
                        glTexCoord2f(0.4375, 1); glVertex3f(0.05, 0.05, -0.5);
                        glTexCoord2f(0.5625, 1); glVertex3f(0.05, -0.05, -0.5);
                        glTexCoord2f(0.5625, 0.375); glVertex3f(0.05, -0.05, 0.125);
                        glEnd();

                        glDisable(GL_CULL_FACE);
                    }break;
                    case 2: {

                        switch (block_toward)
                        {
                            case 1: {
                                glBindTexture(GL_TEXTURE_2D, texname[textureID[0]]);//指定绘制材质
                                glBegin(GL_QUADS);
                                glNormal3f(0.0f, 0.0f, -1.0f);
                                glTexCoord2f(1, 1); glVertex3f(0.5, 0.5, 0.49609375);
                                glTexCoord2f(1, 0); glVertex3f(0.5, -0.5, 0.49609375);
                                glTexCoord2f(0, 0); glVertex3f(-0.5, -0.5, 0.49609375);
                                glTexCoord2f(0, 1); glVertex3f(-0.5, 0.5, 0.49609375);
                                glEnd();
                            }break;
                            case 0: {
                                glBindTexture(GL_TEXTURE_2D, texname[textureID[1]]);//指定绘制材质
                                glBegin(GL_QUADS);
                                glNormal3f(0.0f, 0.0f, 1.0f);
                                glTexCoord2f(1, 1); glVertex3f(0.5, 0.5, -0.49609375);
                                glTexCoord2f(0, 1); glVertex3f(-0.5, 0.5, -0.49609375);
                                glTexCoord2f(0, 0); glVertex3f(-0.5, -0.5, -0.49609375);
                                glTexCoord2f(1, 0); glVertex3f(0.5, -0.5, -0.49609375);
                                glEnd();
                            }break;
                            case 3: {
                                glBindTexture(GL_TEXTURE_2D, texname[textureID[2]]);//指定绘制材质
                                glBegin(GL_QUADS);
                                glNormal3f(0.0f, 1.0f, 0.0f);
                                glTexCoord2f(0, 0); glVertex3f(0.5, -0.49609375, 0.5);
                                glTexCoord2f(0, 1); glVertex3f(0.5, -0.49609375, -0.5);
                                glTexCoord2f(1, 1); glVertex3f(-0.5, -0.49609375, -0.5);
                                glTexCoord2f(1, 0); glVertex3f(-0.5, -0.49609375, 0.5);
                                glEnd();
                            }break;
                            case 2: {
                                glBindTexture(GL_TEXTURE_2D, texname[textureID[3]]);//指定绘制材质
                                glBegin(GL_QUADS);
                                glNormal3f(0.0f, -1.0f, 0.0f);
                                glTexCoord2f(0, 0); glVertex3f(0.5, 0.49609375, 0.5);
                                glTexCoord2f(1, 0); glVertex3f(-0.5, 0.49609375, 0.5);
                                glTexCoord2f(1, 1); glVertex3f(-0.5, 0.49609375, -0.5);
                                glTexCoord2f(0, 1); glVertex3f(0.5, 0.49609375, -0.5);
                                glEnd();
                            }break;
                            case 5: {
                                glBindTexture(GL_TEXTURE_2D, texname[textureID[4]]);//指定绘制材质
                                glBegin(GL_QUADS);
                                glNormal3f(1.0f, 0.0f, 0.0f);
                                glTexCoord2f(0, 0); glVertex3f(-0.49609375, 0.5, 0.5);
                                glTexCoord2f(1, 0); glVertex3f(-0.49609375, -0.5, 0.5);
                                glTexCoord2f(1, 1); glVertex3f(-0.49609375, -0.5, -0.5);
                                glTexCoord2f(0, 1); glVertex3f(-0.49609375, 0.5, -0.5);
                                glEnd();
                            }break;
                            case 4: {
                                glBindTexture(GL_TEXTURE_2D, texname[textureID[5]]);//指定绘制材质
                                glBegin(GL_QUADS);
                                glNormal3f(-1.0f, 0.0f, 0.0f);
                                glTexCoord2f(0, 0); glVertex3f(0.49609375, 0.5, 0.5);
                                glTexCoord2f(0, 1); glVertex3f(0.49609375, 0.5, -0.5);
                                glTexCoord2f(1, 1); glVertex3f(0.49609375, -0.5, -0.5);
                                glTexCoord2f(1, 0); glVertex3f(0.49609375, -0.5, 0.5);
                                glEnd();
                            }break;
                            default:break;
                        }

                    }break;
                    case 3: {

                        switch (block_toward)
                        {
                            case 0:case 1:
                            case 2:case 3:break;
                            case 4: case 5:glRotatef(90, 0, 0, 1); break;
                            default:break;
                        }

                        glBindTexture(GL_TEXTURE_2D, texname[textureID[1]]);//指定绘制材质
                        glBegin(GL_QUADS);
                        glNormal3f(0.0f, 0.0f, 1.0f);
                        glTexCoord2f(1, 1); glVertex3f(0.5, 0.5, -0.49609375);
                        glTexCoord2f(0, 1); glVertex3f(-0.5, 0.5, -0.49609375);
                        glTexCoord2f(0, 0); glVertex3f(-0.5, -0.5, -0.49609375);
                        glTexCoord2f(1, 0); glVertex3f(0.5, -0.5, -0.49609375);
                        glEnd();

                    }break;
                    case 4:case 5:case 6:case 7:case 8:case 9: {

                        glBindTexture(GL_TEXTURE_2D, texname[textureID[0]]);//指定绘制材质
                        glBegin(GL_QUADS);
                        glNormal3f(1.0f, 1.0f, 0.0f);
                        glTexCoord2f(1, 1); glVertex3f(0.35, -0.35, -0.5);
                        glTexCoord2f(0, 1); glVertex3f(-0.35, 0.35, -0.5);
                        glTexCoord2f(0, 0); glVertex3f(-0.35, 0.35, +0.5);
                        glTexCoord2f(1, 0); glVertex3f(0.35, -0.35, +0.5);
                        glEnd();

                        glBindTexture(GL_TEXTURE_2D, texname[textureID[0]]);//指定绘制材质
                        glBegin(GL_QUADS);
                        glNormal3f(-1.0f, 1.0f, 0.0f);
                        glTexCoord2f(1, 1); glVertex3f(0.35, 0.35, -0.5);
                        glTexCoord2f(0, 1); glVertex3f(-0.35, -0.35, -0.5);
                        glTexCoord2f(0, 0); glVertex3f(-0.35, -0.35, +0.5);
                        glTexCoord2f(1, 0); glVertex3f(0.35,  0.35, +0.5);
                        glEnd();

                    }break;
                    default:break;
                }

                glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

                glDisable(GL_TEXTURE_2D);
                glDisable(GL_BLEND);
            }break;
            case 5: {
                glColor3f(1, 1, 1);

                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                glEnable(GL_TEXTURE_2D);
                glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);//指定绘制模式 MODULATE

                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, block_ambient);//环境颜色
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, block_diffuse);//散射颜色
                glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, block_specluar);//镜面颜色
                glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, block_shininess);//镜面指数
                glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, block_emission);//发射颜色

                glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

                amount = 16;
                size = 0.0625;

                //上 0 z+
                if (drawface[0]) {
                    glBindTexture(GL_TEXTURE_2D, texname[textureID[0]]);//指定绘制材质
                    for (int i = 0; i < amount; i++)
                        for (int j = 0; j < amount; j++)
                        {
                            glBegin(GL_QUADS);
                            glNormal3f(0.0f, 0.0f, 1.0f);
                            glTexCoord2f((i + 1) * size, (j + 1) * size);       glVertex3f(-0.5 + (i + 1) * size, -0.5 + (j + 1) * size, 0.5);
                            glTexCoord2f((i + 1) * size, j * size);       glVertex3f(-0.5 + (i + 1) * size, -0.5 + j * size, 0.5);
                            glTexCoord2f(i * size, j * size);       glVertex3f(-0.5 + i * size, -0.5 + j * size, 0.5);
                            glTexCoord2f(i * size, (j + 1) * size);       glVertex3f(-0.5 + i * size, -0.5 + (j + 1) * size, 0.5);
                            glEnd();
                        }
                }

                //下 1 z-
                if (drawface[1]) {
                    glBindTexture(GL_TEXTURE_2D, texname[textureID[1]]);//指定绘制材质
                    glBegin(GL_QUADS);
                    glNormal3f(0.0f, 0.0f, -1.0f);
                    glTexCoord2f(1, 1); glVertex3f(0.5, 0.5, -0.499);
                    glTexCoord2f(0, 1); glVertex3f(-0.5, 0.5, -0.499);
                    glTexCoord2f(0, 0); glVertex3f(-0.5, -0.5, -0.499);
                    glTexCoord2f(1, 0); glVertex3f(0.5, -0.5, -0.499);
                    glEnd();
                }
                //前 2 y-
                if (drawface[2]) {
                    glBindTexture(GL_TEXTURE_2D, texname[textureID[2]]);//指定绘制材质
                    glBegin(GL_QUADS);
                    glNormal3f(0.0f, -1.0f, 0.0f);
                    glTexCoord2f(0, 0); glVertex3f(0.5, -0.499, 0.5);
                    glTexCoord2f(0, 1); glVertex3f(0.5, -0.499, -0.5);
                    glTexCoord2f(1, 1); glVertex3f(-0.5, -0.499, -0.5);
                    glTexCoord2f(1, 0); glVertex3f(-0.5, -0.499, 0.5);
                    glEnd();
                }

                //后 3 y+
                if (drawface[3]) {
                    glBindTexture(GL_TEXTURE_2D, texname[textureID[3]]);//指定绘制材质
                    glBegin(GL_QUADS);
                    glNormal3f(0.0f, 1.0f, 0.0f);
                    glTexCoord2f(0, 0); glVertex3f(0.5, 0.499, 0.5);
                    glTexCoord2f(1, 0); glVertex3f(-0.5, 0.499, 0.5);
                    glTexCoord2f(1, 1); glVertex3f(-0.5, 0.499, -0.5);
                    glTexCoord2f(0, 1); glVertex3f(0.5, 0.499, -0.5);
                    glEnd();
                }

                //左 4 x-
                if (drawface[4]) {
                    glBindTexture(GL_TEXTURE_2D, texname[textureID[4]]);//指定绘制材质
                    glBegin(GL_QUADS);
                    glNormal3f(-1.0f, 0.0f, 0.0f);
                    glTexCoord2f(0, 0); glVertex3f(-0.499, 0.5, 0.5);
                    glTexCoord2f(1, 0); glVertex3f(-0.499, -0.5, 0.5);
                    glTexCoord2f(1, 1); glVertex3f(-0.499, -0.5, -0.5);
                    glTexCoord2f(0, 1); glVertex3f(-0.499, 0.5, -0.5);
                    glEnd();
                }

                //右 5 x+
                if (drawface[5]) {
                    glBindTexture(GL_TEXTURE_2D, texname[textureID[5]]);//指定绘制材质
                    glBegin(GL_QUADS);
                    glNormal3f(1.0f, 0.0f, 0.0f);
                    glTexCoord2f(0, 0); glVertex3f(0.499, 0.5, 0.5);
                    glTexCoord2f(0, 1); glVertex3f(0.499, 0.5, -0.5);
                    glTexCoord2f(1, 1); glVertex3f(0.499, -0.5, -0.5);
                    glTexCoord2f(1, 0); glVertex3f(0.499, -0.5, 0.5);
                    glEnd();
                }

                glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

                glDisable(GL_TEXTURE_2D);
                glDisable(GL_BLEND);
            }break;
        }

        glPopMatrix();
    }
}

void Block::draw_Block_edit() {
    if ((BlockID) && draw) {
        glPushMatrix();
        glTranslated(x, y, z);

        if (drawface[0]) {
            glPushName(0);
            glBegin(GL_QUADS);//上 0
            glNormal3f(0.0f, 0.0f, 1.0f);
            glVertex3f(0.5, 0.5, 0.5);
            glVertex3f(-0.5, 0.5, 0.5);
            glVertex3f(-0.5, -0.5, 0.5);
            glVertex3f(0.5, -0.5, 0.5);
            glEnd();
            glPopName();
        }


        if (drawface[1]) {
            glPushName(1);
            glBegin(GL_QUADS);//下 1
            glNormal3f(0.0f, 0.0f, -1.0f);
            glVertex3f(0.5, 0.5, -0.5);
            glVertex3f(-0.5, 0.5, -0.5);
            glVertex3f(-0.5, -0.5, -0.5);
            glVertex3f(0.5, -0.5, -0.5);
            glEnd();
            glPopName();
        }

        if (drawface[2]) {
            glPushName(2);
            glBegin(GL_QUADS);//前 2
            glNormal3f(0.0f, -1.0f, 0.0f);
            glVertex3f(0.5, -0.5, 0.5);
            glVertex3f(-0.5, -0.5, 0.5);
            glVertex3f(-0.5, -0.5, -0.5);
            glVertex3f(0.5, -0.5, -0.5);
            glEnd();
            glPopName();
        }

        if (drawface[3]) {
            glPushName(3);
            glBegin(GL_QUADS);//后 3
            glNormal3f(0.0f, 1.0f, 0.0f);
            glVertex3f(0.5, 0.5, 0.5);
            glVertex3f(-0.5, 0.5, 0.5);
            glVertex3f(-0.5, 0.5, -0.5);
            glVertex3f(0.5, 0.5, -0.5);
            glEnd();
            glPopName();
        }

        if (drawface[4]) {
            glPushName(4);
            glBegin(GL_QUADS);//左 4
            glNormal3f(-1.0f, 0.0f, 0.0f);
            glVertex3f(-0.5, 0.5, 0.5);
            glVertex3f(-0.5, -0.5, 0.5);
            glVertex3f(-0.5, -0.5, -0.5);
            glVertex3f(-0.5, 0.5, -0.5);
            glEnd();
            glPopName();
        }

        if (drawface[5]) {
            glPushName(5);
            glBegin(GL_QUADS);//右 5
            glNormal3f(1.0f, 0.0f, 0.0f);
            glVertex3f(0.5, 0.5, 0.5);
            glVertex3f(0.5, -0.5, 0.5);
            glVertex3f(0.5, -0.5, -0.5);
            glVertex3f(0.5, 0.5, -0.5);
            glEnd();
            glPopName();
        }

        glPopMatrix();
    }
}


void Block::draw_skybox(float set_color[4])
{

    float sky_size = 100;

    glDisable(GL_LIGHTING);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //sky
    if (1)
    {
        glColor4f(set_color[0] * 0.5, set_color[1] * 0.7, set_color[2] * 1, 1);
        glPushMatrix();

        //上 0 z+
        glBegin(GL_QUADS);
        glVertex3f(sky_size, sky_size, sky_size);
        glVertex3f(sky_size, -sky_size, sky_size);
        glVertex3f(-sky_size, -sky_size, sky_size);
        glVertex3f(-sky_size, sky_size, sky_size);
        glEnd();

        //下 1 z-
        glBegin(GL_QUADS);
        glVertex3f(sky_size, sky_size, -sky_size);
        glVertex3f(-sky_size, sky_size, -sky_size);
        glVertex3f(-sky_size, -sky_size, -sky_size);
        glVertex3f(sky_size, -sky_size, -sky_size);
        glEnd();

        //前 2 y-
        glBegin(GL_QUADS);
        glVertex3f(sky_size, -sky_size, sky_size);
        glVertex3f(sky_size, -sky_size, -sky_size);
        glTexCoord2f(0.4, 1); glVertex3f(-sky_size, -sky_size, -sky_size);
        glTexCoord2f(0.4, 0.8); glVertex3f(-sky_size, -sky_size, sky_size);
        glEnd();

        //后 3 y+
        glBegin(GL_QUADS);
        glVertex3f(sky_size, sky_size, sky_size);
        glVertex3f(-sky_size, sky_size, sky_size);
        glVertex3f(-sky_size, sky_size, -sky_size);
        glVertex3f(sky_size, sky_size, -sky_size);
        glEnd();

        //左 4 x-
        glBegin(GL_QUADS);
        glVertex3f(-sky_size, sky_size, sky_size);
        glVertex3f(-sky_size, -sky_size, sky_size);
        glVertex3f(-sky_size, -sky_size, -sky_size);
        glVertex3f(-sky_size, sky_size, -sky_size);
        glEnd();

        //右 5 x+
        glBegin(GL_QUADS);
        glVertex3f(sky_size, sky_size, sky_size);
        glVertex3f(sky_size, sky_size, -sky_size);
        glVertex3f(sky_size, -sky_size, -sky_size);
        glVertex3f(sky_size, -sky_size, sky_size);
        glEnd();

        glPopMatrix();
    }

    //cloud
    if (1) {
        sky_size--;
        glColor4f(set_color[0] * 1, set_color[1] * 1, set_color[2] * 1, 0.5);
        glEnable(GL_TEXTURE_2D);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);//指定绘制模式 MODULATE

        glPushMatrix();
        //上 0 z+
        glBindTexture(GL_TEXTURE_2D, texname[34]);//指定绘制材质
        glBegin(GL_QUADS);
        glNormal3f(0.0f, 0.0f, 1.0f);
        glTexCoord2f(0.2, 0.4); glVertex3f(sky_size, sky_size, sky_size);
        glTexCoord2f(0.2, 0.2); glVertex3f(sky_size, -sky_size, sky_size);
        glTexCoord2f(0, 0.2); glVertex3f(-sky_size, -sky_size, sky_size);
        glTexCoord2f(0, 0.4); glVertex3f(-sky_size, sky_size, sky_size);
        glEnd();

        //下 1 z-
        glBegin(GL_QUADS);
        glNormal3f(0.0f, 0.0f, -1.0f);
        glTexCoord2f(0.6, 0.4); glVertex3f(sky_size, sky_size, -sky_size);
        glTexCoord2f(0.4, 0.4); glVertex3f(-sky_size, sky_size, -sky_size);
        glTexCoord2f(0.4, 0.2); glVertex3f(-sky_size, -sky_size, -sky_size);
        glTexCoord2f(0.6, 0.2); glVertex3f(sky_size, -sky_size, -sky_size);
        glEnd();

        //前 2 y-
        glBegin(GL_QUADS);
        glNormal3f(0.0f, -1.0f, 0.0f);
        glTexCoord2f(0.2, 0.8); glVertex3f(sky_size, -sky_size, sky_size);
        glTexCoord2f(0.2, 1); glVertex3f(sky_size, -sky_size, -sky_size);
        glTexCoord2f(0.4, 1); glVertex3f(-sky_size, -sky_size, -sky_size);
        glTexCoord2f(0.4, 0.8); glVertex3f(-sky_size, -sky_size, sky_size);
        glEnd();

        //后 3 y+
        glBegin(GL_QUADS);
        glNormal3f(0.0f, 1.0f, 0.0f);
        glTexCoord2f(0.2, 0.4); glVertex3f(sky_size, sky_size, sky_size);
        glTexCoord2f(0.4, 0.4); glVertex3f(-sky_size, sky_size, sky_size);
        glTexCoord2f(0.4, 0.6); glVertex3f(-sky_size, sky_size, -sky_size);
        glTexCoord2f(0.2, 0.6); glVertex3f(sky_size, sky_size, -sky_size);
        glEnd();

        //左 4 x-
        glBegin(GL_QUADS);
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glTexCoord2f(0.2, 0.6); glVertex3f(-sky_size, sky_size, sky_size);
        glTexCoord2f(0.4, 0.6); glVertex3f(-sky_size, -sky_size, sky_size);
        glTexCoord2f(0.4, 0.8); glVertex3f(-sky_size, -sky_size, -sky_size);
        glTexCoord2f(0.2, 0.8); glVertex3f(-sky_size, sky_size, -sky_size);
        glEnd();

        //右 5 x+
        glBegin(GL_QUADS);
        glNormal3f(1.0f, 0.0f, 0.0f);
        glTexCoord2f(0.2, 0.2); glVertex3f(sky_size, sky_size, sky_size);
        glTexCoord2f(0.2, 0.4); glVertex3f(sky_size, sky_size, -sky_size);
        glTexCoord2f(0.4, 0.4); glVertex3f(sky_size, -sky_size, -sky_size);
        glTexCoord2f(0.4, 0.2); glVertex3f(sky_size, -sky_size, sky_size);
        glEnd();

        glPopMatrix();
    }

    //star
    if (set_color[0] < 0.2)
    {
        sky_size--;
        glColor4f(1, 1, 1, (0.2 - set_color[0]) * 2);
        glEnable(GL_TEXTURE_2D);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);//指定绘制模式 MODULATE

        glPushMatrix();
        //上 0 z+
        glBindTexture(GL_TEXTURE_2D, texname[43]);//指定绘制材质
        glBegin(GL_QUADS);
        glNormal3f(0.0f, 0.0f, 1.0f);
        glTexCoord2f(1, 1); glVertex3f(sky_size, sky_size, sky_size);
        glTexCoord2f(1, 0); glVertex3f(sky_size, -sky_size, sky_size);
        glTexCoord2f(0, 0); glVertex3f(-sky_size, -sky_size, sky_size);
        glTexCoord2f(0, 1); glVertex3f(-sky_size, sky_size, sky_size);
        glEnd();

        //下 1 z-
        glBegin(GL_QUADS);
        glNormal3f(0.0f, 0.0f, -1.0f);
        glTexCoord2f(1, 1); glVertex3f(sky_size, sky_size, -sky_size);
        glTexCoord2f(0, 1); glVertex3f(-sky_size, sky_size, -sky_size);
        glTexCoord2f(0, 0); glVertex3f(-sky_size, -sky_size, -sky_size);
        glTexCoord2f(1, 0); glVertex3f(sky_size, -sky_size, -sky_size);
        glEnd();

        //前 2 y-
        glBegin(GL_QUADS);
        glNormal3f(0.0f, -1.0f, 0.0f);
        glTexCoord2f(0, 0); glVertex3f(sky_size, -sky_size, sky_size);
        glTexCoord2f(0, 1); glVertex3f(sky_size, -sky_size, -sky_size);
        glTexCoord2f(1, 1); glVertex3f(-sky_size, -sky_size, -sky_size);
        glTexCoord2f(1, 0); glVertex3f(-sky_size, -sky_size, sky_size);
        glEnd();

        //后 3 y+
        glBegin(GL_QUADS);
        glNormal3f(0.0f, 1.0f, 0.0f);
        glTexCoord2f(0, 0); glVertex3f(sky_size, sky_size, sky_size);
        glTexCoord2f(1, 0); glVertex3f(-sky_size, sky_size, sky_size);
        glTexCoord2f(1, 1); glVertex3f(-sky_size, sky_size, -sky_size);
        glTexCoord2f(0, 1); glVertex3f(sky_size, sky_size, -sky_size);
        glEnd();

        //左 4 x-
        glBegin(GL_QUADS);
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glTexCoord2f(0, 0); glVertex3f(-sky_size, sky_size, sky_size);
        glTexCoord2f(1, 0); glVertex3f(-sky_size, -sky_size, sky_size);
        glTexCoord2f(1, 1); glVertex3f(-sky_size, -sky_size, -sky_size);
        glTexCoord2f(0, 1); glVertex3f(-sky_size, sky_size, -sky_size);
        glEnd();

        //右 5 x+
        glBegin(GL_QUADS);
        glNormal3f(1.0f, 0.0f, 0.0f);
        glTexCoord2f(0, 0); glVertex3f(sky_size, sky_size, sky_size);
        glTexCoord2f(0, 1); glVertex3f(sky_size, sky_size, -sky_size);
        glTexCoord2f(1, 1); glVertex3f(sky_size, -sky_size, -sky_size);
        glTexCoord2f(1, 0); glVertex3f(sky_size, -sky_size, sky_size);
        glEnd();

        glPopMatrix();
    }

    glDisable(GL_TEXTURE_2D);

    glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);

}

void Block::draw_waterbox()
{
    glColor4f(0.5, 0.5, 0.5, 0.5);

    glDisable(GL_LIGHTING);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);//指定绘制模式 MODULATE

    glPushMatrix();
    glScalef(0.3, 0.3, 0.3);

    //上 0 z+
    glBindTexture(GL_TEXTURE_2D, texname[9]);//指定绘制材质
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(1, 1); glVertex3f(0.5, 0.5, 0.5);
    glTexCoord2f(1, 0); glVertex3f(0.5, -0.5, 0.5);
    glTexCoord2f(0, 0); glVertex3f(-0.5, -0.5, 0.5);
    glTexCoord2f(0, 1); glVertex3f(-0.5, 0.5, 0.5);
    glEnd();


    //下 1 z-
    glBindTexture(GL_TEXTURE_2D, texname[9]);//指定绘制材质
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(1, 1); glVertex3f(0.5, 0.5, -0.5);
    glTexCoord2f(0, 1); glVertex3f(-0.5, 0.5, -0.5);
    glTexCoord2f(0, 0); glVertex3f(-0.5, -0.5, -0.5);
    glTexCoord2f(1, 0); glVertex3f(0.5, -0.5, -0.5);
    glEnd();



    //前 2 y-

    glBindTexture(GL_TEXTURE_2D, texname[9]);//指定绘制材质
    glBegin(GL_QUADS);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(0, 0); glVertex3f(0.5, -0.5, 0.5);
    glTexCoord2f(0, 1); glVertex3f(0.5, -0.5, -0.5);
    glTexCoord2f(1, 1); glVertex3f(-0.5, -0.5, -0.5);
    glTexCoord2f(1, 0); glVertex3f(-0.5, -0.5, 0.5);
    glEnd();


    //后 3 y+

    glBindTexture(GL_TEXTURE_2D, texname[9]);//指定绘制材质
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0, 0); glVertex3f(0.5, 0.5, 0.5);
    glTexCoord2f(1, 0); glVertex3f(-0.5, 0.5, 0.5);
    glTexCoord2f(1, 1); glVertex3f(-0.5, 0.5, -0.5);
    glTexCoord2f(0, 1); glVertex3f(0.5, 0.5, -0.5);
    glEnd();


    //左 4 x-

    glBindTexture(GL_TEXTURE_2D, texname[9]);//指定绘制材质
    glBegin(GL_QUADS);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0, 0); glVertex3f(-0.5, 0.5, 0.5);
    glTexCoord2f(1, 0); glVertex3f(-0.5, -0.5, 0.5);
    glTexCoord2f(1, 1); glVertex3f(-0.5, -0.5, -0.5);
    glTexCoord2f(0, 1); glVertex3f(-0.5, 0.5, -0.5);
    glEnd();

    //右 5 x+
    glBindTexture(GL_TEXTURE_2D, texname[9]);//指定绘制材质
    glBegin(GL_QUADS);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(0, 0); glVertex3f(0.5, 0.5, 0.5);
    glTexCoord2f(0, 1); glVertex3f(0.5, 0.5, -0.5);
    glTexCoord2f(1, 1); glVertex3f(0.5, -0.5, -0.5);
    glTexCoord2f(1, 0); glVertex3f(0.5, -0.5, 0.5);
    glEnd();

    glPopMatrix();
    glEnable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
}

//材质加载
void texture_load(void)
{
    int texture_number, texture_ID;//总文件数
    string texture_filename;
    const char* tex_filename;
    ifstream input;
    input.open("./materials/texture/texture.txt");
    input >> texture_number;
    glGenTextures(50, texname);
    for (int i = 0; i < texture_number; i++)
    {
        input >> texture_ID >> texture_filename;
        cout << texture_ID << " " << texture_filename << endl;
        tex_filename = texture_filename.c_str();
        glBindTexture(GL_TEXTURE_2D, texname[texture_ID]);
        // 为当前绑定的纹理对象设置环绕、过滤方式
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//GL_NEAREST,GL_LINEAR
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        // 加载并生成纹理
        int width, height, nrChannels;
        Image * image = new Image();
        image->loadf(tex_filename, &width, &height, &nrChannels, 0);
        unsigned char* data = image->getData();
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
    }
}