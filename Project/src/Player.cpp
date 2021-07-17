//
// Created by Dell on 2021/6/24.
//

#include "Player.h"

using namespace std;



Player::Player()
{
    face = 0;
    x = 0;
    y = 0;
    z = 0;
    yaw = 0;
    pitch = 0;
    speed_x = 0;
    speed_y = 0;
    speed_z = 0;
}


Player::Player(int set_face, int set_x, int set_y, int set_z)
{
    face = set_face;
    x = set_x;
    y = set_y;
    z = set_z;
    yaw = 0;
    pitch = 0;
    speed_x = 0;
    speed_y = 0;
    speed_z = 0;
}


void Player::set_Player(int set_face, float set_x, float set_y, float set_z, float set_yaw, float set_pitch)
{
    face = set_face;
    x = set_x;
    y = set_y;
    z = set_z;
    yaw = set_yaw;
    pitch = set_pitch;
    yawr = yaw * radtrans;
    pitchr = pitch * radtrans;
}

void Player::set_Player_pos(int set_face, float set_x, float set_y, float set_z)
{
    face = set_face;
    x = set_x;
    y = set_y;
    z = set_z;
}

//玩家移动通过三步实现——1.键盘输入，move函数计算输入后位置(注意输入的为弧度)；2.position回调玩家位置；3.collision判断(架构，player存在world里，a.b.player_move)4.move_re执行移动
void Player::Player_move(float set_yaw,int key)
{
    switch (face)
    {
        case 0:case 1:case 2:case 4:  yaw = -set_yaw; break;
        case 3:case 5:yaw = -set_yaw+180; break;
        case 6:yaw = set_yaw;  break;
    }

    yawr = yaw * radtrans;

    //根据输入改变速度
    switch (key)
    {
        case 0: {

            speed_1_x += speed_add * cos(yawr);
            speed_1_y += speed_add * sin(yawr);

            /*
            if (speed_x > speed_max)
                speed_x = speed_max;
            else if (speed_x < (-speed_max))
                speed_x = -speed_max;
            if (speed_y > speed_max)
                speed_y = speed_max;
            else if (speed_y < (-speed_max))
                speed_y = -speed_max;
             */

            if (speed_1_x * speed_1_x + speed_1_y * speed_1_y > speed_max * speed_max)
            {
                speed_1_x = speed_max * cos(yawr);
                speed_1_y = speed_max * sin(yawr);
            }

        }break;//w
        case 1: {
            speed_1_x -= speed_add * cos(yawr);
            speed_1_y -= speed_add * sin(yawr);

            if (speed_1_x * speed_1_x + speed_1_y * speed_1_y > speed_max * speed_max)
            {
                speed_1_x = -speed_max * cos(yawr);
                speed_1_y = -speed_max * sin(yawr);
            }

        }break;//s
        case 3: {
            speed_2_x += speed_add * sin(yawr);
            speed_2_y -= speed_add * cos(yawr);

            if (speed_2_x * speed_2_x + speed_2_y * speed_2_y > speed_max * speed_max * 0.25)
            {
                speed_2_x = speed_max * sin(yawr) * 0.5;
                speed_2_y = -speed_max * cos(yawr) * 0.5;
            }

        }break;//a
        case 2: {
            speed_2_x -= speed_add * sin(yawr);
            speed_2_y += speed_add * cos(yawr);

            if (speed_2_x * speed_2_x + speed_2_y * speed_2_y > speed_max * speed_max * 0.25)
            {
                speed_2_x = -speed_max * sin(yawr) * 0.5;
                speed_2_y = speed_max * cos(yawr) * 0.5;
            }

        }break;//d
        case 4: {
            if (inwater)
            {
                speed_z += speed_max;
                if (speed_z > speed_max * 5)
                    speed_z = speed_max * 5;
            }
            else if (speed_z == 0)
                speed_z += speed_max * 5;
        }break;//space——jump
        case -1: {
            if (speed_1_x > 0) {

                speed_1_x -= res_x;

                if (speed_1_x < 0)
                    speed_1_x = 0;

            }
            if (speed_1_y > 0) {

                speed_1_y -= res_y;

                if (speed_1_y < 0)
                    speed_1_y = 0;

            }

            if (speed_1_x < 0) {

                speed_1_x += res_x;

                if (speed_1_x > 0)
                    speed_1_x = 0;

            }
            if (speed_1_y < 0) {

                speed_1_y += res_y;

                if (speed_1_y > 0)
                    speed_1_y = 0;

            }
        }break;//无操作减速
        case -2: {
            if (speed_2_x > 0) {

                speed_2_x -= res_x;

                if (speed_2_x < 0)
                    speed_2_x = 0;

            }
            if (speed_2_y > 0) {

                speed_2_y -= res_y;

                if (speed_2_y < 0)
                    speed_2_y = 0;

            }

            if (speed_2_x < 0) {

                speed_2_x += res_x;

                if (speed_2_x > 0)
                    speed_2_x = 0;

            }
            if (speed_2_y < 0) {

                speed_2_y += res_y;

                if (speed_2_y > 0)
                    speed_2_y = 0;

            }

        }break;//无操作减速
        default: {	//重力——牛顿默默爬回棺材板??牛顿气哭.jpg
            if (speed_z != 0)
            {
                if (inwater)
                {
                    speed_z -= 0.005;
                }
                else
                    speed_z -= res_z;
            }
        }break;
    }

    speed_x = speed_1_x + speed_2_x;
    speed_y = speed_1_y + speed_2_y;

}

//位移控制，1执行，-1回退;
void Player::Player_move_re(int x_re, int y_re, int z_re)
{
    if (x_re)
    {
        if (x_re == 1) {
            x += speed_x;
        }
        else if (x_re == -1) {
            speed_x = 0;
            speed_1_x = 0;
            speed_2_x = 0;
        }
    }

    if (y_re)
    {
        if (y_re == 1) {
            y += speed_y;
        }
        else if (x_re == -1) {
            speed_y = 0;
            speed_1_y = 0;
            speed_2_y = 0;
        }
    }

    if (z_re)
    {
        if (z_re == 1) {
            z += speed_z;
        }
        else if (z_re == -1) {
            speed_z = 0;
        }
        else if (z_re == -2)
        {
            speed_z -= res_z;
            z += speed_z;
        }
    }
}

//回调玩家位置
void Player::re_Player_positon(float pos[])
{
    pos[0]=face;
    pos[1] = x;
    pos[2] = y;
    pos[3] = z;
    pos[5] = yaw;
    pos[6] = pitch;
    pos[7] = speed_x;
    pos[8] = speed_y;
    pos[9] = speed_z;

}

//绘制
void Player::draw_Player(void)
{
    glColor3f(1, 1, 1);

    glEnable(GL_CULL_FACE);//优化，只绘制面向部分
    glCullFace(GL_FRONT);

    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);//指定绘制模式

    glMaterialfv(GL_FRONT, GL_AMBIENT, player_ambient);//环境颜色
    glMaterialfv(GL_FRONT, GL_DIFFUSE, player_diffuse);//散射颜色
    glMaterialfv(GL_FRONT, GL_SPECULAR, player_specluar);//镜面颜色
    glMaterialfv(GL_FRONT, GL_SHININESS, player_shininess);//镜面指数
    glMaterialfv(GL_FRONT, GL_EMISSION, player_emission);//发射颜色


    glBindTexture(GL_TEXTURE_2D, player_texname[player_textureID[0][0]]);//指定绘制材质


    glPushMatrix();
    glTranslated(x, y, z);
    glRotatef(yaw, 0, 0, 1);

    glRotatef(90, 1, 0, 0);
    glutSolidTeapot(0.5);

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_CULL_FACE);

}

//编辑绘制模式，将人物以方块数据写入world中
void Player::draw_Player_edit(void)
{
    glPushMatrix();
    glTranslated(round(x), round(y), round(z));

    glPushName(face);
    glPushName((int)round(x));
    glPushName((int)round(y));
    glPushName((int)round(z));

    glPushName(0);
    glBegin(GL_QUADS);//上 0
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glEnd();
    glPopName();

    glPushName(1);
    glBegin(GL_QUADS);//下 1
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, -0.5);
    glEnd();
    glPopName();

    glPushName(2);
    glBegin(GL_QUADS);//前 2
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, -0.5);
    glEnd();
    glPopName();

    glPushName(3);
    glBegin(GL_QUADS);//后 3
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glEnd();
    glPopName();

    glPushName(4);
    glBegin(GL_QUADS);//左 4
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glEnd();
    glPopName();

    glPushName(5);
    glBegin(GL_QUADS);//右 5
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glEnd();
    glPopName();

    glPopName();
    glPopName();
    glPopName();
    glPopName();

    glPopMatrix();

}

//材质载入
void Playertexture_load(void)
{
    int texture_number, texture_ID;//总文件数
    string texture_filename;
    const char* tex_filename;
    ifstream input;
    input.open("./materials/texture/texture.txt");
    input >> texture_number;
    glGenTextures(50, player_texname);
    for (int i = 0; i < texture_number; i++)
    {
        input >> texture_ID >> texture_filename;
        cout << texture_ID << " " << texture_filename << endl;
        tex_filename = texture_filename.c_str();
        glBindTexture(GL_TEXTURE_2D, player_texname[texture_ID]);
        // 为当前绑定的纹理对象设置环绕、过滤方式
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // 加载并生成纹理
        int width, height, nrChannels;
        Image* image = new Image();
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