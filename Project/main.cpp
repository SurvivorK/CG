#include "header.h"
#include "Block.h"
#include "Entity.h"
#include "Worlds.h"
using namespace std;

//控制符
bool bPersp = true;          //投影透视-p
bool bWire = false;           //线框模式-o
bool btest = false;            //调试模式
bool bbuilt = false;           //建筑/放置模式
bool blocked = false;          //lock on
int camera_mode = 1;               //相机模式：1-旁观，2-第一人称，3-第二人称
bool left_button = false;
bool middle_button = false;
bool right_button = false;

//窗口大小
int wHeight = 0;
int wWidth = 0;
GLfloat whRatio;//长宽比

//鼠标控制
float lastX = 0;                   //鼠标位置x
float lastY = 0;                   //鼠标位置y
float yaw = 90, pitch = 0;        //俯仰角与其rad形式
float yawr, pitchr;
float click_time=0;                 //点击时间

//键盘控制
bool moved1 = false;
bool moved2 = false;
bool key_down = true;//为了防止跳跳兽出现
bool w_down = false;
bool a_down = false;
bool s_down = false;
bool d_down = false;
bool space_down = false;
bool space_and_shift_down = false;

//相机模式
int max_camera_mode = 4;

//camera_mode = 1
float distance1= 30;               //相距离原点距离
int cycle = 1;
float sensitivity1_1 = 0.5;         //灵敏度（用于鼠标左键控制）
float sensitivity1_2 = 0.003;         //灵敏度（用于鼠标右键控制）
float sensitivity1_3 =0.1;         //灵敏度（用于鼠标中键控制）

//camera_mode = 2/3/4
float sensitivity2 = 0.005;         //灵敏度（用于鼠标控制）
float sensitivity2_2 = 0.5;         //灵敏度（用于键盘控制）

//camera_mode = 4
int worldsize;
int old_face;
int up[3] = { 0,0,0 };
float temp;
float yaw_fix=0;
float playerdata[10];
bool changeface = false;
bool changeview = false;

//光照参数
bool time_on = true;//时间开关
bool reflect_on = true;//变化主光源
int light_num = 0;
float light_list[8][10];
GLfloat light0_color[4] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_color[3][4] = {1.0, 1.0, 1.0, 1.0,
                             0.9, 0.9, 0.9, 1.0,
                             0.8, 0.8, 0.3, 1.0 };
GLfloat linght_enviroment[] = { 0.4, 0.4, 0.4, 1.0 };
float light_postion[8][4];


//视点
float player[4] = { 0 , 0 , 30 , 0 };     //位置
float eye[] = { 0, 0, 30 };         //相机位置
float center[] = { 0, 0, 0 };     //看向位置

//存储选择数据
#define BUFSIZE 512
GLuint selectBuf[BUFSIZE];
bool selected = false;          //确认是否已选中方块
int Current_blockID = 0;        //目前放置方块（如何显示？表示？）
int Current_type = 0;
int max_ID[6] = { 20,0,0,2,9,1 };
int select_blockpramma[5] = { 0,0,0,0,0 };//目前选中方块数据 面,x,y,z,选中面

//constant
const float pi = 3.14;
const float radtrans = pi / 180;

//世界，人物，方块
int a2[10] = { 12,0,0,1,1,1,1,1,1,1 };
World b1(1);
Block a1(2,0,0,0,0);

//场景绘制
void Draw_Scene()
{
    glMatrixMode(GL_MODELVIEW);

    a1.draw_skybox(light0_color);
    b1.draw_World(camera_mode);

    glFlush();
}

//选择模式场景绘制
void Draw_Scene_edit()
{
    glMatrixMode(GL_MODELVIEW);
    //lEnable(GL_CULL_FACE);//这里优化会出错
    glCullFace(GL_FRONT);

    glInitNames();
    glPushName(0);
    glPopName();

    //a1.draw_Block_edit();
    b1.draw_World_edit(camera_mode);

    glDisable(GL_CULL_FACE);
    glFlush();
}

//导入光照列表
void re_lihgtdata()
{
    light_num = b1.re_draw_world_lightlist(light_list);

    for (int i = 0; i <= light_num; i++)
    {
        switch ((int)light_list[i][0])
        {
            case 0: {
                light_postion[i][0] = light_list[i][1] - worldsize * 1.5 + 0.5;
                light_postion[i][1] = light_list[i][3]+ worldsize / 2 - 0.5;;
                light_postion[i][2] = -light_list[i][2] + worldsize * 1.5 - 0.5;
                light_postion[i][3] = light_list[i][4];
            }break;
            case 1: {
                //glRotatef(180, 1, 0, 0);
                light_postion[i][0] = light_list[i][1] - worldsize * 1.5 + 0.5;
                light_postion[i][1] = -light_list[i][3] - worldsize / 2 + 0.5;
                light_postion[i][2] = light_list[i][2] - worldsize * 1.5 + 0.5;
                light_postion[i][3] = light_list[i][4];
            }break;
            case 2: {
                //glRotatef(90, 1, 0, 0);
                light_postion[i][0] = light_list[i][1] - worldsize * 1.5 + 0.5;
                light_postion[i][1] = light_list[i][2] - worldsize * 1.5 + 0.5;
                light_postion[i][2] = light_list[i][3] + worldsize / 2 - 0.5;
                light_postion[i][3] = light_list[i][4];
            }break;
            case 3: {
                //glRotatef(180, 0, 0, 1);
                //glRotatef(90, 1, 0, 0);
                light_postion[i][0] = -light_list[i][1] + worldsize * 1.5 - 0.5;
                light_postion[i][1] = light_list[i][2] - worldsize * 1.5 + 0.5;
                light_postion[i][2] = -light_list[i][3] - worldsize / 2 + 0.5;
                light_postion[i][3] = light_list[i][4];
            }break;
            case 4: {
                //glRotatef(270, 0, 0, 1);
                //glRotatef(90, 1, 0, 0);
                light_postion[i][0] = -light_list[i][3] - worldsize / 2 + 0.5;
                light_postion[i][1] = light_list[i][2] - worldsize * 1.5 + 0.5;
                light_postion[i][2] = light_list[i][1] - worldsize * 1.5 + 0.5;
                light_postion[i][3] = light_list[i][4];
            }break;
            case 5: {
                //glRotatef(90, 0, 0, 1);
                //glRotatef(90, 1, 0, 0);
                light_postion[i][0] = light_list[i][3] + worldsize / 2 - 0.5;
                light_postion[i][1] = light_list[i][2] - worldsize * 1.5 + 0.5;
                light_postion[i][2] = -light_list[i][1] + worldsize * 1.5 - 0.5;
                light_postion[i][3] = light_list[i][4];
            }break;
            default: {
                light_postion[i][0] = light_list[i][1];
                light_postion[i][1] = light_list[i][2];
                light_postion[i][2] = light_list[i][3];
                light_postion[i][3] = light_list[i][4];
            }; break;
        }
    }
}
//导入世界
void world_load(int ID)
{
    bool newworld = true;
    int current_i = 0;

    int world_number, world_ID[10];
    string world_name[10], world_place[10];
    ifstream input;
    input.open("./materials/data/worldtitle.txt");
    input >> world_number;

    for (int i = 0; i < world_number; i++)
    {
        input >> world_ID[i] >> world_name[i] >> world_place[i];
        if (ID == world_ID[i])
        {
            newworld = false;
            current_i = i;
        }
    }

    input.close();

    //加载
    if (newworld && (world_number < 10))
    {
        //new
        cout << "GENERATING NEW WORLD?  Y/N" << endl;
        char c;
        cin >> c;

        if (c == 'Y')
        {
            int set_worldsize;
            string set_worldname;

            cout << "INPUTWORLD SIZE" << endl;
            cin >> set_worldsize;
            cout << "INPUT WORLD NAME" << endl;
            cin >> set_worldname;

            b1.change_worldID(ID);
            b1.change_worldsize(set_worldsize);
            b1.init_World();

            worldsize = b1.re_worldsize();
            re_lihgtdata();
            world_number++;

            ofstream output;
            output.open("./data/worldtitle.txt");
            output << world_number << endl;

            for (int i = 0; i < world_number-1; i++)
            {
                output << world_ID[i] << " " << world_name[i] << " " << world_place[i] << endl;
            }
            output << ID << " " << set_worldname << " " << "./data/world" << ID << ".txt" << endl;

            output.close();

            b1.output_worlddata();

        }
    }
    else
    {
        cout << "LOADING WORLD " << world_name[current_i]<<" ? Y/N/D"<< endl;
        char c;
        cin >> c;

        if (c == 'Y')
        {
            //input old worlds
            b1.change_worldID(ID);
            b1.input_worlddata();
            worldsize = b1.re_worldsize();
            re_lihgtdata();
        }
        else if (c == 'D')
        {
            world_number--;

            ofstream output;
            output.open("./data/worldtitle.txt");
            output << world_number << endl;

            for (int i = 0; i < world_number + 1; i++)
            {
                if (world_ID[i] == ID) continue;
                output << world_ID[i] << " " << world_name[i] << " " << world_place[i] << endl;
            }

            output.close();

        }

    }
}

//读取选择，选出最近的物体
void processHits(GLint hits, GLuint buffer[])
{
    unsigned int i, j;
    GLuint names, * ptr, minZ, * ptrNames, numberOfNames;

    ptr = (GLuint*)buffer;
    ptrNames = NULL;
    minZ = 0xffffffff;

    for (i = 0; i < hits; i++) {
        names = *ptr;
        ptr++;
        if (*ptr < minZ) {
            numberOfNames = names;
            minZ = *ptr;
            ptrNames = ptr + 2;
        }

        ptr += names + 2;
    }

    //返回最近的点击的名称
    ptr = ptrNames;
    //cout << "number of names =" << numberOfNames << endl;
    for (j = 0; j < numberOfNames; j++, ptr++) {
        select_blockpramma[j] = *ptr;
        cout << select_blockpramma[j] << " ";
    }
    cout << endl;
    selected = true;
}

//选择函数，输入鼠标坐标x,y
void select(int x, int y)
{
    //cout << "select" << endl;
    selected = false;
    int hits;
    GLint viewport[4];

    //设置储存返回数据位置，进入选择模式
    glSelectBuffer(BUFSIZE, selectBuf);

    //进入选择模式
    glRenderMode(GL_SELECT);

    //保存投影矩阵
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    glGetIntegerv(GL_VIEWPORT, viewport);
    gluPickMatrix(x, viewport[3] - y, 1, 1, viewport);
    gluPerspective(45.0, whRatio, 1, 1000);

    Draw_Scene_edit();

    glMatrixMode(GL_PROJECTION);

    // 恢复原始投影矩
    glPopMatrix();

    // 返回常规模式，得到选中物体的数目
    hits = glRenderMode(GL_RENDER);
    //cout << "hits=" << hits << endl;

    // 如果点击发生
    if (hits != 0)
        processHits(hits, selectBuf);

}

//窗口变换
void updateView(int height, int width)
{
    glViewport(0, 0, width, height);						// Reset The Current Viewport

    glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
    glLoadIdentity();									// Reset The Projection Matrix

    whRatio = (GLfloat)width / (GLfloat)height;

    if (bPersp) {
        gluPerspective(45.0, whRatio, 0.1, 1000);             //投影,视角45度。
    }
    else {
        whRatio *= 3;
        glOrtho(-whRatio, whRatio, -3, 3, -100, 100);                //正投影
    }

    glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
}

//窗口适应
void reshape(int width, int height)
{
    if (height == 0)										// Prevent A Divide By Zero By
    {
        height = 1;										// Making Height Equal One
    }

    wHeight = height;
    wWidth = width;

    updateView(wHeight, wWidth);
}

//重绘函数
void redraw()
{
    //键盘操作初始化....说白了就是支持几个键一起按下去
    moved1 = false;
    moved2 = false;

    //水中？
    if ((camera_mode == 3) || (camera_mode == 4))
    {
        if (b1.re_worlddata(round(playerdata[0]), round(playerdata[1]), round(playerdata[2]), round(playerdata[3]), 2) == 5)//in water function
        {
            b1.player.re_Player_positon(playerdata);
            b1.player.inwater = true;
            key_down = true;
        }
    }

    //运动
    if (((camera_mode == 2) || (camera_mode == 3) || (camera_mode == 4)))
    {
        if (a_down) {
            moved2 = true;
            if (camera_mode == 2)
            {
                player[0] += sensitivity2_2 * sin(yawr);
                player[2] -= sensitivity2_2 * cos(yawr);
                eye[0] = player[0];
                eye[2] = player[2];
                center[0] = eye[0] + 5 * cos(yawr);
                center[2] = eye[2] + 5 * sin(yawr);
            }
            else if (camera_mode == 3)
            {
                b1.player.Player_move(yaw_fix, 2);
            }
            else if (camera_mode == 4)
            {
                b1.player.Player_move(yaw, 2);
            }
        }
        if (d_down)
        {
            moved2 = true;
            if (camera_mode == 2)
            {
                player[0] -= sensitivity2_2 * sin(yawr);
                player[2] += sensitivity2_2 * cos(yawr);
                eye[0] = player[0];
                eye[2] = player[2];
                center[0] = eye[0] + 5 * cos(yawr);
                center[2] = eye[2] + 5 * sin(yawr);
            }
            else if (camera_mode == 3)
            {
                b1.player.Player_move(yaw_fix, 3);
            }
            else if (camera_mode == 4)
            {
                b1.player.Player_move(yaw, 3);
            }
        }
        if (w_down)
        {
            moved1 = true;
            if (camera_mode == 2)
            {
                player[0] += sensitivity2_2 * cos(yawr);
                player[2] += sensitivity2_2 * sin(yawr);
                eye[0] = player[0];
                eye[2] = player[2];
                center[0] = eye[0] + 5 * cos(yawr);
                center[2] = eye[2] + 5 * sin(yawr);
            }
            else if (camera_mode == 3)
            {
                b1.player.Player_move(yaw_fix, 0);
            }
            else if (camera_mode == 4)
            {
                b1.player.Player_move(yaw, 0);
            }
        }
        if (s_down)
        {
            moved1 = true;
            if (camera_mode == 2)
            {
                player[0] -= sensitivity2_2 * cos(yawr);
                player[2] -= sensitivity2_2 * sin(yawr);
                eye[0] = player[0];
                eye[2] = player[2];
                center[0] = eye[0] + 5 * cos(yawr);
                center[2] = eye[2] + 5 * sin(yawr);
            }
            else if (camera_mode == 3)
            {
                b1.player.Player_move(yaw_fix, 1);
            }
            else if (camera_mode == 4)
            {
                b1.player.Player_move(yaw, 1);
            }
        }
        if (space_down)
        {
            if (camera_mode == 2)
            {
                if (space_and_shift_down)
                {
                    player[1] -= sensitivity2_2;
                    eye[1] = player[1];
                    center[1] = eye[1] + 5 * sin(pitchr);
                }
                else
                {
                    player[1] += sensitivity2_2;
                    eye[1] = player[1];
                    center[1] = eye[1] + 5 * sin(pitchr);
                }
            }
            else if ((camera_mode == 3)  && (key_down == true))
            {
                b1.player.Player_move(yaw_fix, 4);
                key_down = false;
            }
            else if ((camera_mode == 4) && (key_down == true))
            {
                b1.player.Player_move(yaw, 4);
                key_down = false;
            }
        }
    }

    if (moved1 == false)
    {
        if (camera_mode == 3)
        {
            b1.player.Player_move(yaw_fix, -1);//更新玩家速度
        }
        else if (camera_mode == 4)
        {
            b1.player.Player_move(yaw, -1);//更新玩家速度
        }
    }
    if (moved2 == false)
    {
        if (camera_mode == 3)
        {
            b1.player.Player_move(yaw_fix, -2);//更新玩家速度
        }
        else if (camera_mode == 4)
        {
            b1.player.Player_move(yaw, -2);//更新玩家速度
        }
    }

    if (camera_mode == 3)
    {
        b1.player.Player_move(yaw_fix, -3);//更新玩家速度
    }
    else if (camera_mode == 4)
    {
        b1.player.Player_move(yaw, -3);//更新玩家速度
    }

    //优化面切换
    if ((camera_mode == 3) || (camera_mode == 4))
    {
        b1.crash_dect();
        b1.player.re_Player_positon(playerdata);

        if (old_face != (int)playerdata[0])
        {
            changeface = true;
            if (camera_mode == 3)
                switch (old_face)
                {
                    case 0: {
                        switch ((int)playerdata[0])
                        {
                            case 2:break;
                            case 3:break;
                            case 4:yaw_fix += -90; break;
                            case 5:yaw_fix += -90; break;
                        }
                    }break;
                    case 1: {
                        switch ((int)playerdata[0])
                        {
                            case 2:break;
                            case 3:break;
                            case 4:yaw_fix += 90; break;
                            case 5:yaw_fix += 90; break;
                        }
                    }break;
                    case 2: {
                        switch ((int)playerdata[0])
                        {
                            case 0:break;
                            case 1:break;
                            case 4:break;
                            case 5:yaw_fix += -180; break;
                        }
                    }break;
                    case 3: {
                        switch ((int)playerdata[0])
                        {
                            case 0:break;
                            case 1:break;
                            case 4:yaw_fix += -180; break;
                            case 5:break;
                        }
                    }break;;
                    case 4: {
                        switch ((int)playerdata[0])
                        {
                            case 2:break;
                            case 3:yaw_fix += 180; break;
                            case 0:yaw_fix += 90; break;
                            case 1:yaw_fix += -90; break;
                        }
                    }break;
                    case 5: {
                        switch ((int)playerdata[0])
                        {
                            case 2:yaw_fix += 180; break;
                            case 3:break;
                            case 0:yaw_fix += 90; break;
                            case 1:yaw_fix += -90; break;
                        }
                    }break;
                }
            else if (camera_mode == 4)
            {
                switch (old_face)
                {
                    case 0: {
                        switch ((int)playerdata[0])
                        {
                            case 2:break;
                            case 3:break;
                            case 4:yaw += -90; break;
                            case 5:yaw += -90; break;
                        }
                    }break;
                    case 1: {
                        switch ((int)playerdata[0])
                        {
                            case 2:break;
                            case 3:break;
                            case 4:yaw += 90; break;
                            case 5:yaw += 90; break;
                        }
                    }break;
                    case 2: {
                        switch ((int)playerdata[0])
                        {
                            case 0:break;
                            case 1:break;
                            case 4:break;
                            case 5:yaw += -180; break;
                        }
                    }break;
                    case 3: {
                        switch ((int)playerdata[0])
                        {
                            case 0:break;
                            case 1:break;
                            case 4:yaw += -180; break;
                            case 5:break;
                        }
                    }break;;
                    case 4: {
                        switch ((int)playerdata[0])
                        {
                            case 2:break;
                            case 3:yaw += 180; break;
                            case 0:yaw += 90; break;
                            case 1:yaw += -90; break;
                        }
                    }break;
                    case 5: {
                        switch ((int)playerdata[0])
                        {
                            case 2:yaw += 180; break;
                            case 3:break;
                            case 0:yaw += 90; break;
                            case 1:yaw += -90; break;
                        }
                    }break;
                }
                yawr = yaw * radtrans;
            }
        }

        old_face = (int)playerdata[0];
    }

    if (changeface)
    {
        pitch = pitch + 90;
        if (pitch > 89)
            pitch = 89;

        changeface = false;
        changeview = true;
    }

    if (changeview)
    {
        cout << pitch << endl;
        pitch -= 1;
        if (pitch < 0)
        {
            pitch = 0;
            changeview = false;
        }
        pitchr = pitch * radtrans;
    }


    // 重设Modelview Matrix，初始化
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //视角设置
    if (camera_mode == 4)
    {
        up[0] = 0;
        up[1] = 0;
        up[2] = 0;

        switch ((int)playerdata[0])
        {
            case 0: {

                up[1] = 1;

                eye[0] = playerdata[1] - worldsize * 1.5 + 0.5;
                eye[1] = playerdata[3] + worldsize / 2 - 0.5;
                eye[2] = -playerdata[2] + worldsize * 1.5 - 0.5;

                center[0] = eye[0] + 5 * cos(yawr * 1);
                center[1] = eye[1] + 5 * sin(pitchr * 1);
                center[2] = eye[2] + 5 * sin(yawr * 1);
            }break;
            case 1: {
                //glRotatef(180, 1, 0, 0);

                up[1] = -1;

                eye[0] = playerdata[1] - worldsize * 1.5 + 0.5;
                eye[1] = -playerdata[3] - worldsize / 2 + 0.5;
                eye[2] = playerdata[2] - worldsize * 1.5 + 0.5;

                center[0] = eye[0] + 5 * cos(yawr * -1);
                center[1] = eye[1] + 5 * sin(pitchr * -1);
                center[2] = eye[2] + 5 * sin(yawr * -1);
            }break;
            case 2: {
                //glRotatef(90, 1, 0, 0);

                up[2] = 1;

                eye[0] = playerdata[1] - worldsize * 1.5 + 0.5;
                eye[1] = playerdata[2] - worldsize * 1.5 + 0.5;
                eye[2] = playerdata[3] + worldsize / 2 - 0.5;

                center[0] = eye[0] + 5 * cos(yawr * -1);
                center[1] = eye[1] + 5 * sin(yawr * -1);
                center[2] = eye[2] + 5 * sin(pitchr * 1);

            }break;
            case 3: {
                //glRotatef(180, 0, 0, 1);
                //glRotatef(90, 1, 0, 0);

                up[2] = -1;

                eye[0] = -playerdata[1] + worldsize * 1.5 - 0.5;
                eye[1] = playerdata[2] - worldsize * 1.5 + 0.5;
                eye[2] = -playerdata[3] - worldsize / 2 + 0.5;

                center[0] = eye[0] + 5 * cos(yawr * 1);
                center[1] = eye[1] + 5 * sin(yawr * 1);
                center[2] = eye[2] + 5 * sin(pitchr * -1);
            }break;
            case 4: {
                //glRotatef(270, 0, 0, 1);
                //glRotatef(90, 1, 0, 0);

                up[0] = -1;

                eye[0] = -playerdata[3] - worldsize / 2 + 0.5;
                eye[1] = playerdata[2] - worldsize * 1.5 + 0.5;
                eye[2] = playerdata[1] - worldsize * 1.5 + 0.5;

                center[0] = eye[0] + 5 * sin(pitchr * -1);
                center[1] = eye[1] + 5 * sin(yawr * -1);
                center[2] = eye[2] + 5 * cos(yawr * -1);
            }break;
            case 5: {
                //glRotatef(90, 0, 0, 1);
                //glRotatef(90, 1, 0, 0);

                up[0] = 1;

                eye[0] = playerdata[3] + worldsize / 2 - 0.5;
                eye[1] = playerdata[2] - worldsize * 1.5 + 0.5;
                eye[2] = -playerdata[1] + worldsize * 1.5 - 0.5;

                center[0] = eye[0] + 5 * sin(pitchr * 1);
                center[1] = eye[1] + 5 * sin(yawr * 1);
                center[2] = eye[2] + 5 * cos(yawr * 1);
            }break;
            default:break;
        }

        gluLookAt(eye[0], eye[1], eye[2],
                  center[0], center[1], center[2],
                  up[0], up[1], up[2]);

    }
    else
    {
        gluLookAt(eye[0], eye[1], eye[2],
                  center[0], center[1], center[2],
                  0, cycle, 0);			// 场景（0，0，0）的视点中心 (0,5,50)，Y轴向上
    }


    //绘制模式设置（线框/模型）
    if (bWire) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    //显示模式设置（开启深度，开启光照）
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);

    if (time_on)
    {
        float light_yawr = (b1.re_worldtime() / 100.0) * (3.14 / 180);

        light_postion[0][0] = 5 * cos(light_yawr);
        light_postion[0][1] = 4 * cos(light_yawr);
        light_postion[0][2] = 3 * sin(light_yawr);
    }

    if (reflect_on)
    {
        float cos_light = (light_postion[0][0] * eye[0] + light_postion[0][1] * eye[1] + light_postion[0][2] * eye[2]) / ((sqrt(light_postion[0][0] * light_postion[0][0] + light_postion[0][1] * light_postion[0][1] + light_postion[0][2] * light_postion[0][2])) * (sqrt(eye[0] * eye[0] + eye[1] * eye[1] + eye[2] * eye[2])));

        if (cos_light > 0.5)
        {
            light0_color[0] = 1;
            light0_color[1] = 1;
            light0_color[2] = 1;
            light0_color[3] = 1;
        }
        else if (cos_light < -0.5)
        {
            light0_color[0] = 0;
            light0_color[1] = 0;
            light0_color[2] = 0;
            light0_color[3] = 1;
        }
        else if (cos_light>=0)
        {
            light0_color[0] = 0.9 + cos_light * 0.2;
            light0_color[1] = 0.2 + cos_light * 1.6;
            light0_color[2] = 0 + cos_light * 2;
            light0_color[3] = 1;
        }
        else if (cos_light < 0)
        {
            light0_color[0] = 0.9 + cos_light * 1.8;
            light0_color[1] = 0.2 + cos_light * 0.4;
            light0_color[2] = 0;
            light0_color[3] = 1;
        }
    }

    switch (light_num)
    {
        case 7: {
            glLightfv(GL_LIGHT7, GL_POSITION, light_postion[7]);
            glLightfv(GL_LIGHT7, GL_DIFFUSE, light_color[(int)light_list[7][5]]);
            glLightfv(GL_LIGHT7, GL_SPECULAR, light_color[(int)light_list[7][6]]);
            glLightf(GL_LIGHT7, GL_CONSTANT_ATTENUATION, light_list[7][7]);
            glLightf(GL_LIGHT7, GL_LINEAR_ATTENUATION, light_list[7][8]);
            glLightf(GL_LIGHT7, GL_QUADRATIC_ATTENUATION, light_list[7][9]);
            glEnable(GL_LIGHT7);
        }
        case 6: {
            glLightfv(GL_LIGHT6, GL_POSITION, light_postion[6]);
            glLightfv(GL_LIGHT6, GL_DIFFUSE, light_color[(int)light_list[6][5]]);
            glLightfv(GL_LIGHT6, GL_SPECULAR, light_color[(int)light_list[6][6]]);
            glLightf(GL_LIGHT6, GL_CONSTANT_ATTENUATION, light_list[6][7]);
            glLightf(GL_LIGHT6, GL_LINEAR_ATTENUATION, light_list[6][8]);
            glLightf(GL_LIGHT6, GL_QUADRATIC_ATTENUATION, light_list[6][9]);
            glEnable(GL_LIGHT6);
        }
        case 5: {
            glLightfv(GL_LIGHT5, GL_POSITION, light_postion[5]);
            glLightfv(GL_LIGHT5, GL_DIFFUSE, light_color[(int)light_list[5][5]]);
            glLightfv(GL_LIGHT5, GL_SPECULAR, light_color[(int)light_list[5][6]]);
            glLightf(GL_LIGHT5, GL_CONSTANT_ATTENUATION, light_list[5][7]);
            glLightf(GL_LIGHT5, GL_LINEAR_ATTENUATION, light_list[5][8]);
            glLightf(GL_LIGHT5, GL_QUADRATIC_ATTENUATION, light_list[5][9]);
            glEnable(GL_LIGHT5);
        }
        case 4: {
            glLightfv(GL_LIGHT4, GL_POSITION, light_postion[4]);
            glLightfv(GL_LIGHT4, GL_DIFFUSE, light_color[(int)light_list[4][5]]);
            glLightfv(GL_LIGHT4, GL_SPECULAR, light_color[(int)light_list[4][6]]);
            glLightf(GL_LIGHT4, GL_CONSTANT_ATTENUATION, light_list[4][7]);
            glLightf(GL_LIGHT4, GL_LINEAR_ATTENUATION, light_list[4][8]);
            glLightf(GL_LIGHT4, GL_QUADRATIC_ATTENUATION, light_list[4][9]);
            glEnable(GL_LIGHT4);
        }
        case 3: {
            glLightfv(GL_LIGHT3, GL_POSITION, light_postion[3]);
            glLightfv(GL_LIGHT3, GL_DIFFUSE, light_color[(int)light_list[3][5]]);
            glLightfv(GL_LIGHT3, GL_SPECULAR, light_color[(int)light_list[3][6]]);
            glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, light_list[3][7]);
            glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, light_list[3][8]);
            glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, light_list[3][9]);
            glEnable(GL_LIGHT3);
        }
        case 2: {
            glLightfv(GL_LIGHT2, GL_POSITION, light_postion[2]);
            glLightfv(GL_LIGHT2, GL_DIFFUSE, light_color[(int)light_list[2][5]]);
            glLightfv(GL_LIGHT2, GL_SPECULAR, light_color[(int)light_list[2][6]]);
            glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, light_list[2][7]);
            glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, light_list[2][8]);
            glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, light_list[2][9]);
            glEnable(GL_LIGHT2);
        }
        case 1: {
            glLightfv(GL_LIGHT1, GL_POSITION, light_postion[1]);
            glLightfv(GL_LIGHT1, GL_DIFFUSE, light_color[(int)light_list[1][5]]);
            glLightfv(GL_LIGHT1, GL_SPECULAR, light_color[(int)light_list[1][6]]);
            glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, light_list[1][7]);
            glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, light_list[1][8]);
            glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, light_list[1][9]);
            glEnable(GL_LIGHT1);
        }
        case 0: {
            glLightfv(GL_LIGHT0, GL_POSITION, light_postion[0]);
            glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_color);
            glLightfv(GL_LIGHT0, GL_SPECULAR, light0_color);
            glLightModelfv(GL_LIGHT_MODEL_AMBIENT, linght_enviroment);//全局光
            glEnable(GL_LIGHT0);
        }
    }

    // 旋转y轴
    glRotatef(0, 0, 1.0f, 0);
    glRotatef(-90, 1, 0, 0);

    // Draw Scene
    Draw_Scene();

    switch (light_num)
    {
        case 7: {
            glDisable(GL_LIGHT7);
        }
        case 6: {
            glDisable(GL_LIGHT6);
        }
        case 5: {
            glDisable(GL_LIGHT5);
        }
        case 4: {
            glDisable(GL_LIGHT4);
        }
        case 3: {
            glDisable(GL_LIGHT3);
        }
        case 2: {
            glDisable(GL_LIGHT2);
        }
        case 1: {
            glDisable(GL_LIGHT1);
        }
        case 0: {
            glDisable(GL_LIGHT0);
        }break;
    }

    glDisable(GL_LIGHTING);
    glutSwapBuffers();

    b1.player.inwater = false;
}

//???
void idle()
{
    glutPostRedisplay();
}

//键盘读入
void key(unsigned char k, int x, int y)
{
    switch (k)
    {
        case 27:exit(0); break;                                         //强退

        case 'p': if (btest) { bPersp = !bPersp; updateView(wHeight, wWidth); } break;    //投影开关
        case 'o': if (btest) { bWire = !bWire; }break;                                   //线框开关

        case 'a': {
            a_down = true;
        } break;
        case 'd': {
            d_down = true;
        } break;
        case 'w': {
            w_down = true;
        }break;
        case 's': {
            s_down = true;
        }break;
        case ' ': {
            space_down = true;
            int mod = glutGetModifiers();//获取shift键信息
            if (mod == GLUT_ACTIVE_SHIFT)
                space_and_shift_down = true;
            else
                space_and_shift_down = false;
        }break;

        case'`': {
            blocked = !blocked;
            cout << "locked!";
        }break;//english mode!!
        case',': {
            Current_blockID--;
            if (Current_blockID < 0)
                Current_blockID = 0;
            cout << "current ID=" << Current_blockID << endl;
        }break;
        case '<': {
            Current_type--;
            Current_blockID = 0;
            if (Current_type < 0)
                Current_type = 0;
            cout << "current type=" << Current_type << endl;
        } break;
        case'.': {
            Current_blockID++;
            if (Current_blockID >= max_ID[Current_type])
                Current_blockID = max_ID[Current_type];
            cout << "current ID=" << Current_blockID << endl;
        } break;
        case '>': {
            Current_type++;
            Current_blockID = 0;
            if (Current_type >= 5)
                Current_type = 5;
            cout << "current type=" << Current_type << endl;
        } break;

        case'L': {
            cout << "LOADING NEW WORLD...." << endl;
            cout << "please input world ID" << endl;
            int ID;
            cin >> ID;
            world_load(ID);
        }; break;
        default:break;
    }
}

//键盘弹起
void keyup(unsigned char k, int x, int y)
{
    switch (k)
    {
        case 'a': {
            a_down = false;
        } break;
        case 'd': {
            d_down = false;
        } break;
        case 'w': {
            w_down = false;
        }break;
        case 's': {
            s_down = false;
        }break;
        case ' ': {
            space_down = false;
            key_down = true;
        }break;
    }
}

//特殊按键
void specialkey(int k, int x, int y)
{
    switch (k)
    {
        case GLUT_KEY_F1: {
            b1.output_worlddata();
            cout << "world save" << endl;
        } break;
        case GLUT_KEY_F2: {
            b1.input_worlddata();
            cout << "world load" << endl;
        }break;
        case GLUT_KEY_F3: {
            bbuilt = !bbuilt; 	cout << "edit mode change" << endl;
            Current_blockID = 0;
            Current_type = 0;
            if (bbuilt == false)
            {
                b1.draw_world_test();
                selected = false;
            }
        } break;    //开关建筑
        case GLUT_KEY_F4: {
            camera_mode++;
            cycle = 1;

            if (camera_mode > max_camera_mode)
                camera_mode = 1;
            cout << "camera mode change " << camera_mode << endl;

            if (camera_mode == 1)
            {
                center[0] = 0;
                center[1] = 0;
                center[2] = 0;

                eye[0] = 0;
                eye[1] = 0;
                eye[2] = 30;

                distance1 = 30;

                yaw = 90;
                pitch = 0;

                yawr = yaw * radtrans;
                pitchr = pitch * radtrans;
            }
            else if (camera_mode == 2)
            {
                center[0] = 0;
                center[1] = 0;
                center[2] = 0;

                eye[0] = 0;
                eye[1] = 0;
                eye[2] = 30;

                yaw = -90;
                pitch = 0;

                yawr = yaw * radtrans;
                pitchr = pitch * radtrans;
            }
            else if (camera_mode == 3)
            {
                center[0] = 0;
                center[1] = 0;
                center[2] = 0;

                eye[0] = 0;
                eye[1] = 0;
                eye[2] = 30;

                distance1 = 30;

                yaw = 90;
                pitch = 0;

                yawr = yaw * radtrans;
                pitchr = pitch * radtrans;
            }
            else if (camera_mode == 4)
            {
                center[0] = 0;
                center[1] = 0;
                center[2] = 0;

                eye[0] = 0;
                eye[1] = 0;
                eye[2] = 30;

                yaw = 0;
                pitch = 0;

                yawr = yaw * radtrans;
                pitchr = pitch * radtrans;
            }

        } break; //视角

        case GLUT_KEY_F10: {
            btest = !btest;
            cout << "test mode change" << endl;
        }break;            //开关调试

        default:break;
    }
}

//鼠标操作（点击）
void mouseclick(int button, int state, int x, int y)
{
    if ( button == GLUT_LEFT_BUTTON )
        if (state == GLUT_DOWN)
        {
            left_button = true;
            lastX = x;
            lastY = y;
            if ( bbuilt)
            {
                select(lastX, lastY);
                if (selected)
                {
                    b1.change_worlddata(0, select_blockpramma[0],0,select_blockpramma[1], select_blockpramma[2], select_blockpramma[3],0);
                    re_lihgtdata();
                }

            }
        }
        else
        {
            left_button = false;
        }
    if ( button == GLUT_RIGHT_BUTTON )
        if (state == GLUT_DOWN)
        {
            right_button = true;
            lastX = x;
            lastY = y;
            if (bbuilt)
            {
                selected = false;
                select(lastX, lastY);
                if (selected)
                {
                    b1.add_worlddata(Current_blockID, select_blockpramma[0], Current_type,select_blockpramma[1], select_blockpramma[2], select_blockpramma[3], select_blockpramma[4]);
                    re_lihgtdata();
                }
            }
        }
        else
        {
            right_button = false;
        }
    if ( button == GLUT_MIDDLE_BUTTON )
        if (state == GLUT_DOWN)
        {
            middle_button = true;
            lastX = x;
            lastY = y;

            if (camera_mode == 1)
            {
                for (int i = 0; i < 3; i++)
                    center[i] = 0;
            }
        }
        else
        {
            middle_button = false;
        }
}

//鼠标操作点击+平移回调
void mousemovent(int x, int y)
{
    float xoffset,yoffset;
    if (!blocked) {
        if (!selected)
        {
            if ((camera_mode == 1)||(camera_mode == 3))
            {
                if (middle_button)
                {
                    yoffset = y - lastY;
                    lastY = y;

                    yoffset *= sensitivity1_3;

                    distance1 += yoffset;

                    if (distance1 <= 1.5)                      //限制
                        distance1 = 1.5;
                    else if (distance1 >= 40)
                        distance1 = 40;

                    eye[0] = cos(yawr) * cos(pitchr) * distance1 + center[0];
                    eye[1] = sin(pitchr) * distance1 + center[1];
                    eye[2] = sin(yawr) * cos(pitchr) * distance1 + center[2];

                }
                else if (left_button)
                {
                    xoffset = x - lastX;
                    yoffset = y - lastY;
                    lastX = x;
                    lastY = y;

                    xoffset *= sensitivity1_1;
                    yoffset *= sensitivity1_1;

                    yaw += xoffset * cycle;
                    pitch += yoffset * cycle;

                    if (pitch > 90.0f)
                    {
                        pitch = 90.0f;
                        yaw = yaw - 180.0f;
                        cycle = -cycle;
                    }
                    if (pitch < -90.0f)
                    {
                        pitch = -90.0f;
                        yaw = yaw - 180.0f;
                        cycle = -cycle;
                    }

                    if (yaw >= 180.0f)
                        yaw -= 360.0f;
                    if (yaw < -180.0f)
                        yaw += 360.0f;

                    yawr = yaw * radtrans;
                    pitchr = pitch * radtrans;

                    eye[0] = cos(yawr) * cos(pitchr) * distance1 + center[0];
                    eye[1] = sin(pitchr) * distance1 + center[1];
                    eye[2] = sin(yawr) * cos(pitchr) * distance1 + center[2];

                }
                else if (right_button)
                {
                    xoffset = x - lastX;
                    yoffset = y - lastY;
                    lastX = x;
                    lastY = y;

                    xoffset *= sensitivity1_2 * distance1;
                    yoffset *= sensitivity1_2 * distance1;

                    center[0] += (yoffset * sin(pitchr) * cos(yawr) - xoffset * sin(yawr)) * cycle;
                    center[1] += yoffset * cos(pitchr) * cycle;
                    center[2] += (-yoffset * sin(pitchr) * sin(yawr) + xoffset * cos(yawr)) * cycle;

                    eye[0] = cos(yawr) * cos(pitchr) * distance1 + center[0];
                    eye[1] = sin(pitchr) * distance1 + center[1];
                    eye[2] = sin(yawr) * cos(pitchr) * distance1 + center[2];

                }

            }
        }
    }
}

//鼠标操作平移回调
void passivemousemovent(int x, int y)
{
    float xoffset, yoffset;
    if (!blocked) {
        if (camera_mode == 2)
        {
            xoffset = lastX - x;
            yoffset = lastY - y;
            lastX = x;
            lastY = y;

            xoffset *= sensitivity1_1;
            yoffset *= sensitivity1_1;

            yaw -= xoffset;
            pitch += yoffset;

            if (pitch >= 85.0f)
            {
                pitch = 85.0f;
            }
            if (pitch <= -85.0f)
            {
                pitch = -85.0f;
            }

            if (yaw >= 180.0f)
                yaw -= 360.0f;
            if (yaw < -180.0f)
                yaw += 360.0f;

            yawr = yaw * radtrans;
            pitchr = pitch * radtrans;

            center[0] = eye[0] + 5 * cos(yawr);
            center[1] = eye[1] + 5 * sin(pitchr);
            center[2] = eye[2] + 5 * sin(yawr);

        }
        else if (camera_mode == 4)
        {
            xoffset = lastX - x;
            yoffset = lastY - y;
            lastX = x;
            lastY = y;

            xoffset *= sensitivity1_1;
            yoffset *= sensitivity1_1;

            yaw -= xoffset;
            pitch += yoffset;

            if (pitch >= 89.0f)
            {
                pitch = 89.0f;
            }
            if (pitch <= -89.0f)
            {
                pitch = -89.0f;
            }

            if (yaw >= 180.0f)
                yaw -= 360.0f;
            if (yaw < -180.0f)
                yaw += 360.0f;

            yawr = yaw * radtrans;
            pitchr = pitch * radtrans;

        }
    }
}

//主程序
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(480, 480);
    int windowHandle = glutCreateWindow("kitty's cubeworld");
    glClearColor(0.5, 0.8, 1.0, 0.0);//	背景色

    cout << "STARTING..." << endl;
    texture_load();
    world_load(1);

    glutDisplayFunc(redraw);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(key);
    glutKeyboardUpFunc(keyup);
    glutSpecialFunc(specialkey);
    glutMouseFunc(mouseclick);
    glutMotionFunc(mousemovent);
    glutPassiveMotionFunc(passivemousemovent);
    glutIdleFunc(idle);

    glutMainLoop();
    return 0;
}

