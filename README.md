# Project with No Name

## Timeline
### 2021-06-24
1. 更新了项目结构
   1. 分类include（头文件）和src（cpp文件），main.cpp放在最外层。data、player和texture放到了materials资源文件夹下。目的是减少同一个目录下的文件夹数量
   2. 在cmake-build-debug文件夹下放了和主目录相同的materials和freeglut.dll，这是因为用CLion时exe会生成在cmake-build-debug，freeglut.dll时运行必须的动态链接库，materials是程序运行所需的材料库，两个都必不可少
2. 修改了stbi_image.h的使用，新建了一个Image类专门处理图像读取
   - 我不知道为什么原来每个文件都include 这个不会出问题，讲道理这个库只能include & define implexxxx 一次。现在这个结构肯定不会出问题
3. 修改了代码里和materials中的路径
   （为什么原来都是两个斜杠，虽然我不知道对不对但是看着很吓人qaq）

4. imgui跑在glut上好像会有奇怪的问题，我不知道能不能work
   
## Usage
你还是需要检查SysWOW里有没有glu32.dll 以及 编译器的相关文件里有没有opengl32.a
你的cmake版本应该 > 3.10
### 1. CLion
如果你有CLion，可以直接导入这个项目（我还是觉得CLion比VS好看且好用）
1. 用CLion打开这个文件夹，然后从cmakelist.txt导入项目
2. 然后就可以愉快地运行

CLion我觉得如果已经配好了工程文件还是非常好上手（这么说的话VS配好了也挺好用的，但是它怪丑的）

### 2. 没有CLion

~~没有CLion也可以跑~~

~~你在项目目录下命令行运行：~~


emmm我没有摸索出来没有CLion怎么跑 dbq

如果你真的没有CLion，可以参考一下项目架构，然后到时候我手动合并代码。（尽量模块化开发一些，多写一些类什么的，别都堆在一起了