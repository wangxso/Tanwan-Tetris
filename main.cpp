#include <graphics.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include<bits/stdc++.h>
#include<windows.h>
#include <mmsystem.h>

#pragma comment(lib, "WINMM.LIB")
#define SCRW 680
#define SCRH 640
int DELAY = 50   ; //延时时间
/*******************************
    项目名称:
    俄罗斯方块
    创建日期:
    2018/6/10 12:09:32
    最后修改:
    2018/06/10 12:09:32
    <创建工程>
    2018/06/12 13:14:23
    <实现方块下落预览>
    2018/06/14 20:21:11
    <实现旋转与加速>
    2018/06/19 17:13:20
    <增加排行存档功能>
    2018/06/19 18:29:03
    <增加菜单鼠标键盘操作>
    2018/06/20 09:36:05
    <增加模式选择>
    2018/06/21 08:19:20
    <修复无法重复游戏>
    2018/06/21 09:29:00
    <增加排行榜id功能>
    2018/06/22 09:10:30
    <美化界面>
    2018/06/23 10:01:22
    <修改排行榜界面>
    <添加背景音乐>
    2018/06/24 08:26:30
    <修改部分文字颜色不一致>
    2018/06/24 10:20:22
    <优化排行榜显示>
    2018/06/24 11:35:44
    <增加排行榜删除选项>(去除)

******************************/
/********************************结构体区****************************/
typedef struct AdATA
{
    int score;
    char timeinfo[100];
    char id[100];
} ADATA;
typedef struct ablock_s //块的结构体
{
    int x;              //旋转中心坐标
    int y;
    int xy[4][2];       //每一块的坐标
    color_t color;
} ablock;
/***********************************************/
/***********************变量区*******************************/
mouse_msg msg;
bool Mouse_Up;
bool Mouse_Down;
bool Mouse_Left;
bool Mouse_Right;
int zt[10][21];     //每个方格状态0未填充1已填充str[100];
int live=1;         //块是否还活着
int Mouse_X, Mouse_Y;
long score,xh;      //分数和消行
char scores[50];    //分数显示字符串
char xhs[50];       //消行显示字符串
ADATA data[1000];
PIMAGE raw;
PIMAGE img,mode,ranklist,bk,bk1;
int pow_score = 1;
bool flag = true;
/**********************************************************/

/***********************函数区域***************************/
ADATA getTime();
int menu();
int showlist();
int Judge_down(ablock* block);
int Judge_left(ablock* block);
int mousepos(int *x, int *y);
int Judge_right(ablock* block);
int saveGame(int steps,char *timetext);
void loadImg();
void del_img();
void initgame();
void mode_seltct();
void clearone(int i);
void init_mouseseg();
void draw_play_place();//绘制游戏区域
void Double_PlayGame();//双人游戏
void delete_ranklist_one();
void rotate_(ablock* block);//旋转
void updatezt(ablock* block);
void drawblock(ablock* block);//画方块
void movew(ablock* block,int where);
void Get_point(ablock* block,int x,int y,int n);//获取旋转中心
/*************************************************************/

/************************实现区****************************/
void draw_play_place()
{
    ege::setcolor(WHITE);
    ege::setbkmode(TRANSPARENT);
    ege::xyprintf(500,350,"游戏中");
    ege::xyprintf(500,450,"按方向键移动");
    ege::xyprintf(500,500,"按空格键暂停");
    ege::setbkmode(OPAQUE);
    ege::setfillcolor(BLACK);
    ege::bar(140,142,340,540);
    setfillcolor(EGERGB(255,0,0));
    setcolor(EGERGB(80,80,80));



    for(int i=140+20; i<540; i=i+20)
        //画方格
    {
        line(140,i,340,i);
    }

    for(int i=140+20; i<340; i=i+20)
    {
        line(i,140,i,540);
    }
    setcolor(EGERGB(180,180,180));
    //外边框颜色

    rectangle(140,140,140+200+1,140+400+1);

}
void PutOut()
//输出信息
{
    ege::setbkmode(TRANSPARENT);
    sprintf(scores,"得分: %ld",score*100*pow_score);
    sprintf(xhs,"消除行数: %ld",xh);
    ege::setcolor(WHITE);
    ege::xyprintf(0,20,"操作提示:");
    ege::xyprintf(0,40,"↑↓←→键进行操作");
    ege::xyprintf(0,60,"↑→,←↑进行变换旋转");
    ege::xyprintf(0,80,"按esc键退出");
    ege::setbkmode(OPAQUE);
    outtextxy(500,250,scores);
    outtextxy(500,280,xhs);

}

void playGame()
{
    //for(; ege::is_run(); ege::delay_fps(60))
    //{
    // ege::cleardevice();
    //ege::PIMAGE bk;
    //bk = ege::newimage();
    //ege::getimage(bk,"\\bk1.jpg");
    ege::setbkmode(TRANSPARENT);
    ege::putimage(0,0,bk);


    draw_play_place();
    //绘制游戏区域


    ADATA one;
    //ege::cleardevice();
    PutOut();


    ablock testbl;
    ablock nextbl;
    //下一个方块
    int rk1=1+rand()%7;
    //随机产生1到7
    for(int x=0; x<10; x++)
        zt[x][20]=1;
    for(int n=0;; Sleep(10),n++)
        //主循环
    {
        one = getTime();
        //ege::outtextxy(0,0,one.timeinfo);
        //PutOut();
        if(live==1)
        {
            live=0;
            testbl.x=241+10-20;
            //生成两个块当前的和下一个
            testbl.y=161+10-20;
            nextbl.x=500+10;
            //预览生成坐标
            nextbl.y=100+10;
            Get_point(&testbl,testbl.x,testbl.y,rk1);
            rk1=1+rand()%7;
            Get_point(&nextbl,nextbl.x,nextbl.y,rk1);
            drawblock(&testbl);
            setfillcolor(BLACK);
            //预览处颜色
            bar(400,50,600,150);
            ege::setcolor(WHITE);
            ege::rectangle(400,50,600,150);
            drawblock(&nextbl);
            PutOut();

        }
        int k=kbmsg();
        //按键处理
        key_msg whatfx;

        PutOut();
        if(k)
        {
            whatfx=getkey();
            if (whatfx.msg == key_msg_down)
            {
                if(whatfx.key==VK_SPACE)
                {
                    //e::setbkmode(TRANSPARENT);
                    setfillcolor(BLACK);
                    bar(500,350,500+100,380);
                    xyprintf(500,350,"已暂停");
                    getch();
                    getch();
                    bar(500,350,500+100,380);
                    xyprintf(500,350,"游戏中");
                    PutOut();
                    //ege::setbkmode()
                }
                color_t temp=testbl.color;
                //清除当前块，因为要改变形状
                testbl.color=BLACK;
                drawblock(&testbl);
                testbl.color=temp;

                if(whatfx.key==VK_LEFT&&(Judge_left(&testbl)!=1)&&testbl.xy[0][0]>=161&&testbl.xy[1][0]>=161&&testbl.xy[2][0]>=161&&testbl.xy[3][0]>=161)
                    movew(&testbl,3);
                if(whatfx.key==VK_RIGHT&&(Judge_right(&testbl)!=1)&&testbl.xy[0][0]<=301&&testbl.xy[1][0]<=301&&testbl.xy[2][0]<=301&&testbl.xy[3][0]<=301)
                    movew(&testbl,4);
                if(whatfx.key==VK_DOWN)
                {
                    n=DELAY;
                }
                if(whatfx.key==VK_UP)
                {
                    rotate_(&testbl);
                }
                if(whatfx.key == VK_ESCAPE )
                {
                    //live = 0;
                    if(score>0)
                    {
                        saveGame(score,one.timeinfo);
                    }
                    menu();
                }
                drawblock(&testbl);
                //绘制旋转后的块
            }
        }
        if(n==DELAY)
            //处理自由下落
        {
            n=0;
            if(Judge_down(&testbl)==1)
                //是否已经碰撞
            {
                updatezt(&testbl);
                //碰撞，更新方格状态
                //game over判定
                if(testbl.xy[0][1]<141||testbl.xy[1][1]<141||testbl.xy[2][1]<141||testbl.xy[3][1]<141)
                {
                    xyprintf(500,350,"GAME OVER !");
                    saveGame(score,one.timeinfo);
                    getch();
                    ege::cleardevice();
                    menu();
                    return ;
                }
                live=1;
                continue;
            }
            color_t temp=testbl.color;
            //清除当前块整体下移后显示
            testbl.color=BLACK;
            //下落后变为黑色
            PutOut();
            drawblock(&testbl);
            testbl.color=temp;
            movew(&testbl,1);
            drawblock(&testbl);
        }
    }
    ege::setcolor(WHITE);
    PutOut();
    // }

}
int main()
{
    srand((unsigned)time(NULL));
    setinitmode(0);
    initgraph(SCRW,SCRH);
    setcaption("贪玩俄罗斯方块v2.4");
    mciSendString(TEXT("open bgm.mp3 alias mysong"), NULL,0,NULL);
    mciSendString(TEXT("open bgm1.mp3 alias song1"),NULL,0,NULL);
    mciSendString(TEXT("open bgm2.mp3 alias song2"),NULL,0,NULL);
    loadImg();
    menu();
    getch();
    del_img();
    closegraph();
    mciSendString(TEXT("close mysong"), NULL, 0, NULL);
    //关闭音乐
    return 0;
}
//根据旋转中心和类型（n,共七种）生成一个块
void Get_point(ablock* block,int x,int y,int n)
{
    x-=10;
    y-=10;
    switch(n)
    {
    case 1:
        //L
        block->xy[0][0]=x-20;
        block->xy[0][1]=y-20;
        block->xy[1][0]=x-20;
        block->xy[1][1]=y;
        block->xy[2][0]=x;
        block->xy[2][1]=y;
        block->xy[3][0]=x+20;
        block->xy[3][1]=y;
        block->color=0xFFA500;
        break;
    case 2:
        //S
        block->xy[0][0]=x-20;
        block->xy[0][1]=y;
        block->xy[1][0]=x;
        block->xy[1][1]=y;
        block->xy[2][0]=x;
        block->xy[2][1]=y-20;
        block->xy[3][0]=x+20;
        block->xy[3][1]=y-20;
        block->color=0x00ff00;
        break;
    case 3:
        //一
        block->xy[0][0]=x-40;
        block->xy[0][1]=y-20;
        block->xy[1][0]=x-20;
        block->xy[1][1]=y-20;
        block->xy[2][0]=x;
        block->xy[2][1]=y-20;
        block->xy[3][0]=x+20;
        block->xy[3][1]=y-20;
        block->x-=10;
        block->y-=10;
        block->color=0x00ffff;
        break;
    case 4:
        //J
        block->xy[0][0]=x-20;
        block->xy[0][1]=y;
        block->xy[1][0]=x;
        block->xy[1][1]=y;
        block->xy[2][0]=x+20;
        block->xy[2][1]=y;
        block->xy[3][0]=x+20;
        block->xy[3][1]=y-20;
        block->color=0x0000ee;
        break;
    case 5:
        //田
        block->xy[0][0]=x-20;
        block->xy[0][1]=y-20;
        block->xy[1][0]=x;
        block->xy[1][1]=y-20;
        block->xy[2][0]=x-20;
        block->xy[2][1]=y;
        block->xy[3][0]=x;
        block->xy[3][1]=y;
        block->x-=10;
        block->y-=10;
        block->color=YELLOW;
        break;
    case 6:
        //T
        block->xy[0][0]=x-20;
        block->xy[0][1]=y;
        block->xy[1][0]=x;
        block->xy[1][1]=y;
        block->xy[2][0]=x;
        block->xy[2][1]=y-20;
        block->xy[3][0]=x+20;
        block->xy[3][1]=y;
        block->color=0xff00ff;
        break;
    case 7:
        //Z
        block->xy[0][0]=x-20;
        block->xy[0][1]=y-20;
        block->xy[1][0]=x;
        block->xy[1][1]=y-20;
        block->xy[2][0]=x;
        block->xy[2][1]=y;
        block->xy[3][0]=x+20;
        block->xy[3][1]=y;
        block->color=0xff0000;
        break;
    }
}
//绘制一个块
void drawblock(ablock* block)
{
    setfillcolor(block->color);
    if(block->x>400)
    {
        bar(block->xy[0][0],block->xy[0][1],block->xy[0][0]+19,block->xy[0][1]+19);
        bar(block->xy[1][0],block->xy[1][1],block->xy[1][0]+19,block->xy[1][1]+19);
        bar(block->xy[2][0],block->xy[2][1],block->xy[2][0]+19,block->xy[2][1]+19);
        bar(block->xy[3][0],block->xy[3][1],block->xy[3][0]+19,block->xy[3][1]+19);
    }
    else
        //不要超出方格
    {
        if(block->xy[0][1]>=141)
            bar(block->xy[0][0],block->xy[0][1],block->xy[0][0]+19,block->xy[0][1]+19);
        if(block->xy[1][1]>=141)
            bar(block->xy[1][0],block->xy[1][1],block->xy[1][0]+19,block->xy[1][1]+19);
        if(block->xy[2][1]>=141)
            bar(block->xy[2][0],block->xy[2][1],block->xy[2][0]+19,block->xy[2][1]+19);
        if(block->xy[3][1]>=141)
            bar(block->xy[3][0],block->xy[3][1],block->xy[3][0]+19,block->xy[3][1]+19);
    }
}
//方块移动
void movew(ablock* block,int where)
{
    switch(where)
    {
    case 1:
        //下
        block->xy[0][1]+=20;
        block->xy[1][1]+=20;
        block->xy[2][1]+=20;
        block->xy[3][1]+=20;
        block->y+=20;
        break;
    case 3:
        //左
        block->xy[0][0]-=20;
        block->xy[1][0]-=20;
        block->xy[2][0]-=20;
        block->xy[3][0]-=20;
        block->x-=20;
        break;
    case 4:
        //右
        block->xy[0][0]+=20;
        block->xy[1][0]+=20;
        block->xy[2][0]+=20;
        block->xy[3][0]+=20;
        block->x+=20;
        break;
    }
}
//清除一行
void clearone(int i)
{
    setfillcolor(BLACK);
    //消除后改变成的颜色
    for(int k=0; k<=10; k++)
    {
        bar(20*k+141,141+20*i,20*k+141+19,141+20*i+19);
    }
}
//方格状态更新
void updatezt(ablock* block)
{
    int kill=0;
    //消行个数
    for(int x=0; x<4; x++)
    {
        zt[(block->xy[x][0]-141)/20][(block->xy[x][1]-141)/20]=1;
    }
    for(int x=0; x<10; x++)
    {
        zt[x][20]=1;
    }
    for(int i=0; i<20; i++)
    {
        int j;
        for(j=0; j<10; j++)
        {
            if(zt[j][i]==0)
                break;
        }
        if(j==10)
            //一行全部被填充
        {
            clearone(i);
            xh++;
            kill++;
            for(int down=i-1; down>0; down--)
                //逐层下移
            {
                for(int k=0; k<10; k++)
                {
                    if(zt[k][down]==1)
                    {
                        color_t ys=getpixel(k*20+141+10,10+down*20+141);
                        //获取颜色
                        setfillcolor(EGERGB(0,0,0));
                        bar(k*20+141,down*20+141,k*20+141+19,down*20+141+19);
                        setfillcolor(ys);
                        //为了下移之后可以保持颜色不变,使用上一块颜色填充下一块
                        bar(k*20+141,20+down*20+141,k*20+141+19,20+down*20+141+19);
                    }
                    zt[k][down+1]=zt[k][down];
                    //下移
                }

            }

        }
    }
    if(kill==1)
        score=score+1;
    //一次消行越多，分数越高
    if(kill==2)
        score=score+3;
    if(kill==3)
        score=score+5;
    if(kill==4)
        score=score+8;
    ege::setcolor(WHITE);
    PutOut();

}
//判断下方是否有障碍
int Judge_down(ablock* block)
{
    for(int x=0; x<4; x++)
    {
        if(zt[(block->xy[x][0]-141)/20][(block->xy[x][1]-141)/20+1]==1)
            return 1;
    }
    return 0;
}
//判断左方是否有障碍
int Judge_left(ablock *block)
{
    for(int x=0; x<4; x++)
    {
        if(zt[(block->xy[x][0]-141)/20-1][(block->xy[x][1]-141)/20]==1)
            return 1;
    }
    return 0;
}
//判断右方是否有障碍
int Judge_right(ablock *block)
{
    for(int x=0; x<4; x++)
    {
        if(zt[(block->xy[x][0]-141)/20+1][(block->xy[x][1]-141)/20]==1)
            return 1;
    }
    return 0;
}
//旋转
void rotate_(ablock* block)
{
    int x1=block->x,y1=block->y;

    for(int i=0; i<4; i++)
        //如果旋转之后导致重叠或超出方格,则不旋转
    {
        if((x1-(block->xy[i][1]-y1)-20>321)||(x1-(block->xy[i][1]-y1)-20<141))
            return;
        if(zt[((x1-(block->xy[i][1]-y1)-20)-141)/20][(y1+block->xy[i][0]-x1-141)/20]==1)
            return;
    }
    for(int i=0; i<4; i++)
    {
        int temp_xz=block->xy[i][0];
        //顺时针旋转90度的坐标处理
        block->xy[i][0]=x1-((block->xy[i][1])-y1)-20;
        block->xy[i][1]=y1+(temp_xz)-x1;
    }

}
//游戏初始化，gameover之后调用的
void initgame()
{
    for(int x=0; x<10; x++)
        //超出方格的一行置一,为了统一判断是否碰撞
    {
        zt[x][20]=1;
    }
    for(int i=0; i<20; i++)
        //状态 分数 消行数清零，清除整个方格
    {
        int j;
        for(j=0; j<10; j++)
        {
            zt[j][i]=0;
        }
        clearone(i);
    }
    live = 1;
    score=0;
    xh=0;
    DELAY = 50;
}
ADATA getTime()
//获取系统时间
{
    ADATA one;
    time_t rawtime;
    struct tm *ptminfo;
    time(&rawtime);
    ptminfo = localtime(&rawtime);
    sprintf(one.timeinfo,"%02d-%02d-%02d %02d:%02d:%02d",
            ptminfo->tm_year+1900,ptminfo->tm_mon+1,ptminfo->tm_mday,
            ptminfo->tm_hour,ptminfo->tm_min,ptminfo->tm_sec);
    return one;
}
int length = 0;
int saveGame(int steps,char *timetext)//存储游戏
{
    //打开文件
    char str[100];
    ege::inputbox_getline("排行榜输入框","请输入你的id(回车结束)：",str,sizeof(str)/sizeof(*str));
    int i=0;
    FILE *fp;
    fp = fopen("gamefile.txt","r");
    if(fp==NULL)
    {
        ege::outtextxy(100,20,"error");
        exit(0);
    }
    //读出文件中的数据，存放在数组Adata中

    //不足10条，大于10条时候
    while(!feof(fp) && i < 10)
    {
        fread(&data[i],sizeof(ADATA),1,fp);
        i++;
    }
    length = --i;
    ADATA one;
    one.score = steps*100*pow_score;
    strcpy(one.timeinfo,timetext);
    strcpy(one.id,str);
    //插入有序数组
    for(i = length-1; i >= 0 && one.score > data[i].score; i--)
    {
        data[i+1] = data[i];
        data[i] = one;
    }
    //关闭文件
    fclose(fp);
    //再打开文件
    fp = fopen("gamefile.txt","w+");
    //将新的数组存入电脑
    for(int i=0; i<length+1; i++)
    {
        fwrite(&data[i],sizeof(ADATA),1,fp);
    }
    //关闭文件
    fclose(fp);


}
int showlist()
//显示排行榜
{
    ege::cleardevice();
    ege::putimage_transparent(NULL,ranklist,BLACK,0,0);
    char recoder[100];
    int i=0;
    int z=0;
    FILE *fp;
    fp = fopen("gamefile.txt","r");
    while(!feof(fp) && i < 10)
    {
        fread(&data[i],sizeof(ADATA),1,fp);
        i++;
    }
    ege::setbkmode(TRANSPARENT);
    ege::setcolor(BLACK);
    ege::rectangle(115,180,555,520);
    ege::rectangle(115,180,172,520);
    ege::rectangle(115,180,172+73,520);
    ege::rectangle(115,180,172+73+88,520);
    for(int i=0; i<10; i++)
    {
        ege::line(115,215+z,555,215+z);
        z+=30;
    }

    ege::setcolor(RED);
    ege::outtextxy(120,190,"名次");
    ege::outtextxy(200,190,"得分");
    ege::outtextxy(270,190,"id");
    ege::outtextxy(390,190,"保存时间");
    for(int j=0; j<10; j++)
    {
        char sc[100];
        //设置显示字为透明
        ege::setfont(0,10,"黑体");
        //文字颜色为黑色
        sprintf(recoder,"%d",j+1);
        sprintf(sc,"%d",data[j].score);

        if(j+1==10)
            ege::outtextxy(130,j*30+220,recoder);
        else
            ege::outtextxy(135,j*30+220,recoder);

        ege::outtextxy(175,j*30+220,sc);
        ege::outtextxy(260,j*30+220,data[j].id);
        ege::outtextxy(350,j*30+220,data[j].timeinfo);

    }

    fclose(fp);

    for(; ege::is_run(); ege::delay_fps(60))
    {
        int x,y;
        ege::mousepos(&x,&y);
        while(ege::mousemsg())
        {
            msg = ege::getmouse();
        }
        if(x > 490 && x < 640 && y > 570 && y < 680)
        {
            if(msg.is_down())
            {
                ege::setcolor(WHITE);
                ege::setbkmode(OPAQUE);
                //delete_ranklist_one();
                menu();
            }
        }

    }

    cleardevice();
}
int menu()
//初始进入界面
{
    //PlaySound(TEXT("//a.wav"), NULL, SND_FILENAME | SND_ASYNC |SND_LOOP );
    mciSendString(TEXT("play mysong repeat"), NULL, 0, NULL);//打开音乐
    //mciSendString(TEXT("close mysong"), NULL, 0, NULL);
    initgame();
    for(; ege::is_run(); ege::delay_fps(60))
    {
        ege::cleardevice();
        ege::putimage(0,0,img);
        int x,y;
        char pos[100];
        ege::mousepos(&x,&y);
        //sprintf(pos,"X:%d Y:%d",x,y);
        //ege::outtextxy(0,0,pos);
        ege::outtextxy(600,620,"关闭音乐");
        ege::outtextxy(600,580,"开启音乐");
        while(ege::mousemsg())
        {
            msg = ege::getmouse();
        }
        if(x>600&&x<680&&y>620&&y<640)
        {
            if(msg.is_down())
            {
                mciSendString(TEXT("close mysong"), NULL, 0, NULL);
                mciSendString(TEXT("close song1"), NULL, 0, NULL);
                mciSendString(TEXT("close song2"), NULL, 0, NULL);
            }

        }
        if(x>600&&x<680&&y>580&&y<620)
        {
            if(msg.is_down())
            {
                mciSendString(TEXT("open bgm.mp3 alias mysong"), NULL, 0,NULL);
                mciSendString(TEXT("open bgm1.mp3 alias song1"), NULL, 0,NULL);
                mciSendString(TEXT("open bgm2.mp3 alias song2"), NULL, 0,NULL);
                mciSendString(TEXT("play mysong repeat"),NULL,0,NULL);
            }
        }


        if(x>=249 && y>=327 && x<=472 && y<=380)
        {
            if(msg.is_down()&& flag==true )
            {
                flag = false;
                mode_seltct();
            }

        }
        if(x>=251 && x<=430 && y>=484 && y<=528 && msg.is_down())
        {
            showlist();
        }
        if(x>0 && x<=190 && y>=576 && y<640)
        {
            if(msg.is_down())
            {
                exit(0);
            }
        }
    }
}
void mode_seltct()
//模式选择
{
    int x,y;
    for(; ege::is_run(); ege::delay_fps(60))
    {
        ege::cleardevice();
        ege::putimage(0,0,mode);
        ege::mousepos(&x,&y);
        //ege::setbkmode(TRANSPARENT);
        Mouse_Down = false;
        while(ege::mousemsg())
        {
            msg = ege::getmouse();
        }
        if(x > 200 && x < 435 && y > 240 && y < 307 )
            //简单模式
        {

            ege::putimage(100,230,raw);
            if(msg.is_down())
            {
                pow_score = 1;
                DELAY = 40;
                playGame();
            }
        }
        if(x>215&&y>360&&x<430&&y<425 && flag == false)
            //一般模式
        {

            flag = true;
            ege::putimage(100,340,raw);

            if(msg.is_down())
            {
                mciSendString(TEXT("close mysong"),NULL,0,NULL);
                mciSendString(TEXT("play song1 repeat"),NULL,0,NULL);
                pow_score = 2;
                DELAY = 20;
                playGame();
            }
        }
        if(x>220&&y>480&&x<431&&y<540)
            //困难模式
        {
            ege::putimage(100,450,raw);
            if(msg.is_down())
            {
                mciSendString(TEXT("close mysong"),NULL,0,NULL);
                mciSendString(TEXT("play song2 repeat"),NULL,0,NULL);
                pow_score = 4;
                DELAY = 10;
                playGame();
            }

        }
        if(x>488&&y>585&&x<640&&y<680)
            //返回按钮
        {
            if(msg.is_down())
            {
                menu();
            }
        }
    }
}
void loadImg()
{
    img = ege::newimage();
    bk = ege::newimage();
    bk1 = ege::newimage();
    raw = ege::newimage();
    ranklist = ege::newimage();
    mode = ege::newimage();
    ege::getimage(img,"\\bk.jpg");
    ege::getimage(bk,"\\bk1.jpg");
    ege::getimage(ranklist,"\\rank.jpg");
    ege::getimage(raw,"\\raw.jpg");
    ege::getimage(mode,"\\mode.jpg");
}
void del_img()
{
    ege::delimage(img);
    ege::delimage(bk);
    ege::delimage(bk1);
    ege::delimage(raw);
    ege::delimage(ranklist);
    ege::delimage(mode);
}
