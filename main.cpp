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
int DELAY = 50   ; //��ʱʱ��
/*******************************
    ��Ŀ����:
    ����˹����
    ��������:
    2018/6/10 12:09:32
    ����޸�:
    2018/06/10 12:09:32
    <��������>
    2018/06/12 13:14:23
    <ʵ�ַ�������Ԥ��>
    2018/06/14 20:21:11
    <ʵ����ת�����>
    2018/06/19 17:13:20
    <�������д浵����>
    2018/06/19 18:29:03
    <���Ӳ˵������̲���>
    2018/06/20 09:36:05
    <����ģʽѡ��>
    2018/06/21 08:19:20
    <�޸��޷��ظ���Ϸ>
    2018/06/21 09:29:00
    <�������а�id����>
    2018/06/22 09:10:30
    <��������>
    2018/06/23 10:01:22
    <�޸����а����>
    <��ӱ�������>
    2018/06/24 08:26:30
    <�޸Ĳ���������ɫ��һ��>
    2018/06/24 10:20:22
    <�Ż����а���ʾ>
    2018/06/24 11:35:44
    <�������а�ɾ��ѡ��>(ȥ��)

******************************/
/********************************�ṹ����****************************/
typedef struct AdATA
{
    int score;
    char timeinfo[100];
    char id[100];
} ADATA;
typedef struct ablock_s //��Ľṹ��
{
    int x;              //��ת��������
    int y;
    int xy[4][2];       //ÿһ�������
    color_t color;
} ablock;
/***********************************************/
/***********************������*******************************/
mouse_msg msg;
bool Mouse_Up;
bool Mouse_Down;
bool Mouse_Left;
bool Mouse_Right;
int zt[10][21];     //ÿ������״̬0δ���1�����str[100];
int live=1;         //���Ƿ񻹻���
int Mouse_X, Mouse_Y;
long score,xh;      //����������
char scores[50];    //������ʾ�ַ���
char xhs[50];       //������ʾ�ַ���
ADATA data[1000];
PIMAGE raw;
PIMAGE img,mode,ranklist,bk,bk1;
int pow_score = 1;
bool flag = true;
/**********************************************************/

/***********************��������***************************/
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
void draw_play_place();//������Ϸ����
void Double_PlayGame();//˫����Ϸ
void delete_ranklist_one();
void rotate_(ablock* block);//��ת
void updatezt(ablock* block);
void drawblock(ablock* block);//������
void movew(ablock* block,int where);
void Get_point(ablock* block,int x,int y,int n);//��ȡ��ת����
/*************************************************************/

/************************ʵ����****************************/
void draw_play_place()
{
    ege::setcolor(WHITE);
    ege::setbkmode(TRANSPARENT);
    ege::xyprintf(500,350,"��Ϸ��");
    ege::xyprintf(500,450,"��������ƶ�");
    ege::xyprintf(500,500,"���ո����ͣ");
    ege::setbkmode(OPAQUE);
    ege::setfillcolor(BLACK);
    ege::bar(140,142,340,540);
    setfillcolor(EGERGB(255,0,0));
    setcolor(EGERGB(80,80,80));



    for(int i=140+20; i<540; i=i+20)
        //������
    {
        line(140,i,340,i);
    }

    for(int i=140+20; i<340; i=i+20)
    {
        line(i,140,i,540);
    }
    setcolor(EGERGB(180,180,180));
    //��߿���ɫ

    rectangle(140,140,140+200+1,140+400+1);

}
void PutOut()
//�����Ϣ
{
    ege::setbkmode(TRANSPARENT);
    sprintf(scores,"�÷�: %ld",score*100*pow_score);
    sprintf(xhs,"��������: %ld",xh);
    ege::setcolor(WHITE);
    ege::xyprintf(0,20,"������ʾ:");
    ege::xyprintf(0,40,"�������������в���");
    ege::xyprintf(0,60,"����,�������б任��ת");
    ege::xyprintf(0,80,"��esc���˳�");
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
    //������Ϸ����


    ADATA one;
    //ege::cleardevice();
    PutOut();


    ablock testbl;
    ablock nextbl;
    //��һ������
    int rk1=1+rand()%7;
    //�������1��7
    for(int x=0; x<10; x++)
        zt[x][20]=1;
    for(int n=0;; Sleep(10),n++)
        //��ѭ��
    {
        one = getTime();
        //ege::outtextxy(0,0,one.timeinfo);
        //PutOut();
        if(live==1)
        {
            live=0;
            testbl.x=241+10-20;
            //���������鵱ǰ�ĺ���һ��
            testbl.y=161+10-20;
            nextbl.x=500+10;
            //Ԥ����������
            nextbl.y=100+10;
            Get_point(&testbl,testbl.x,testbl.y,rk1);
            rk1=1+rand()%7;
            Get_point(&nextbl,nextbl.x,nextbl.y,rk1);
            drawblock(&testbl);
            setfillcolor(BLACK);
            //Ԥ������ɫ
            bar(400,50,600,150);
            ege::setcolor(WHITE);
            ege::rectangle(400,50,600,150);
            drawblock(&nextbl);
            PutOut();

        }
        int k=kbmsg();
        //��������
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
                    xyprintf(500,350,"����ͣ");
                    getch();
                    getch();
                    bar(500,350,500+100,380);
                    xyprintf(500,350,"��Ϸ��");
                    PutOut();
                    //ege::setbkmode()
                }
                color_t temp=testbl.color;
                //�����ǰ�飬��ΪҪ�ı���״
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
                //������ת��Ŀ�
            }
        }
        if(n==DELAY)
            //������������
        {
            n=0;
            if(Judge_down(&testbl)==1)
                //�Ƿ��Ѿ���ײ
            {
                updatezt(&testbl);
                //��ײ�����·���״̬
                //game over�ж�
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
            //�����ǰ���������ƺ���ʾ
            testbl.color=BLACK;
            //������Ϊ��ɫ
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
    setcaption("̰�����˹����v2.4");
    mciSendString(TEXT("open bgm.mp3 alias mysong"), NULL,0,NULL);
    mciSendString(TEXT("open bgm1.mp3 alias song1"),NULL,0,NULL);
    mciSendString(TEXT("open bgm2.mp3 alias song2"),NULL,0,NULL);
    loadImg();
    menu();
    getch();
    del_img();
    closegraph();
    mciSendString(TEXT("close mysong"), NULL, 0, NULL);
    //�ر�����
    return 0;
}
//������ת���ĺ����ͣ�n,�����֣�����һ����
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
        //һ
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
        //��
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
//����һ����
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
        //��Ҫ��������
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
//�����ƶ�
void movew(ablock* block,int where)
{
    switch(where)
    {
    case 1:
        //��
        block->xy[0][1]+=20;
        block->xy[1][1]+=20;
        block->xy[2][1]+=20;
        block->xy[3][1]+=20;
        block->y+=20;
        break;
    case 3:
        //��
        block->xy[0][0]-=20;
        block->xy[1][0]-=20;
        block->xy[2][0]-=20;
        block->xy[3][0]-=20;
        block->x-=20;
        break;
    case 4:
        //��
        block->xy[0][0]+=20;
        block->xy[1][0]+=20;
        block->xy[2][0]+=20;
        block->xy[3][0]+=20;
        block->x+=20;
        break;
    }
}
//���һ��
void clearone(int i)
{
    setfillcolor(BLACK);
    //������ı�ɵ���ɫ
    for(int k=0; k<=10; k++)
    {
        bar(20*k+141,141+20*i,20*k+141+19,141+20*i+19);
    }
}
//����״̬����
void updatezt(ablock* block)
{
    int kill=0;
    //���и���
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
            //һ��ȫ�������
        {
            clearone(i);
            xh++;
            kill++;
            for(int down=i-1; down>0; down--)
                //�������
            {
                for(int k=0; k<10; k++)
                {
                    if(zt[k][down]==1)
                    {
                        color_t ys=getpixel(k*20+141+10,10+down*20+141);
                        //��ȡ��ɫ
                        setfillcolor(EGERGB(0,0,0));
                        bar(k*20+141,down*20+141,k*20+141+19,down*20+141+19);
                        setfillcolor(ys);
                        //Ϊ������֮����Ա�����ɫ����,ʹ����һ����ɫ�����һ��
                        bar(k*20+141,20+down*20+141,k*20+141+19,20+down*20+141+19);
                    }
                    zt[k][down+1]=zt[k][down];
                    //����
                }

            }

        }
    }
    if(kill==1)
        score=score+1;
    //һ������Խ�࣬����Խ��
    if(kill==2)
        score=score+3;
    if(kill==3)
        score=score+5;
    if(kill==4)
        score=score+8;
    ege::setcolor(WHITE);
    PutOut();

}
//�ж��·��Ƿ����ϰ�
int Judge_down(ablock* block)
{
    for(int x=0; x<4; x++)
    {
        if(zt[(block->xy[x][0]-141)/20][(block->xy[x][1]-141)/20+1]==1)
            return 1;
    }
    return 0;
}
//�ж����Ƿ����ϰ�
int Judge_left(ablock *block)
{
    for(int x=0; x<4; x++)
    {
        if(zt[(block->xy[x][0]-141)/20-1][(block->xy[x][1]-141)/20]==1)
            return 1;
    }
    return 0;
}
//�ж��ҷ��Ƿ����ϰ�
int Judge_right(ablock *block)
{
    for(int x=0; x<4; x++)
    {
        if(zt[(block->xy[x][0]-141)/20+1][(block->xy[x][1]-141)/20]==1)
            return 1;
    }
    return 0;
}
//��ת
void rotate_(ablock* block)
{
    int x1=block->x,y1=block->y;

    for(int i=0; i<4; i++)
        //�����ת֮�����ص��򳬳�����,����ת
    {
        if((x1-(block->xy[i][1]-y1)-20>321)||(x1-(block->xy[i][1]-y1)-20<141))
            return;
        if(zt[((x1-(block->xy[i][1]-y1)-20)-141)/20][(y1+block->xy[i][0]-x1-141)/20]==1)
            return;
    }
    for(int i=0; i<4; i++)
    {
        int temp_xz=block->xy[i][0];
        //˳ʱ����ת90�ȵ����괦��
        block->xy[i][0]=x1-((block->xy[i][1])-y1)-20;
        block->xy[i][1]=y1+(temp_xz)-x1;
    }

}
//��Ϸ��ʼ����gameover֮����õ�
void initgame()
{
    for(int x=0; x<10; x++)
        //���������һ����һ,Ϊ��ͳһ�ж��Ƿ���ײ
    {
        zt[x][20]=1;
    }
    for(int i=0; i<20; i++)
        //״̬ ���� ���������㣬�����������
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
//��ȡϵͳʱ��
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
int saveGame(int steps,char *timetext)//�洢��Ϸ
{
    //���ļ�
    char str[100];
    ege::inputbox_getline("���а������","���������id(�س�����)��",str,sizeof(str)/sizeof(*str));
    int i=0;
    FILE *fp;
    fp = fopen("gamefile.txt","r");
    if(fp==NULL)
    {
        ege::outtextxy(100,20,"error");
        exit(0);
    }
    //�����ļ��е����ݣ����������Adata��

    //����10��������10��ʱ��
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
    //������������
    for(i = length-1; i >= 0 && one.score > data[i].score; i--)
    {
        data[i+1] = data[i];
        data[i] = one;
    }
    //�ر��ļ�
    fclose(fp);
    //�ٴ��ļ�
    fp = fopen("gamefile.txt","w+");
    //���µ�����������
    for(int i=0; i<length+1; i++)
    {
        fwrite(&data[i],sizeof(ADATA),1,fp);
    }
    //�ر��ļ�
    fclose(fp);


}
int showlist()
//��ʾ���а�
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
    ege::outtextxy(120,190,"����");
    ege::outtextxy(200,190,"�÷�");
    ege::outtextxy(270,190,"id");
    ege::outtextxy(390,190,"����ʱ��");
    for(int j=0; j<10; j++)
    {
        char sc[100];
        //������ʾ��Ϊ͸��
        ege::setfont(0,10,"����");
        //������ɫΪ��ɫ
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
//��ʼ�������
{
    //PlaySound(TEXT("//a.wav"), NULL, SND_FILENAME | SND_ASYNC |SND_LOOP );
    mciSendString(TEXT("play mysong repeat"), NULL, 0, NULL);//������
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
        ege::outtextxy(600,620,"�ر�����");
        ege::outtextxy(600,580,"��������");
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
//ģʽѡ��
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
            //��ģʽ
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
            //һ��ģʽ
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
            //����ģʽ
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
            //���ذ�ť
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
