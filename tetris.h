#ifndef TETRIS_H_INCLUDED
#define TETRIS_H_INCLUDED

#include <graphics.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include<bits/stdc++.h>
#include<windows.h>
#include <mmsystem.h>
#include<windows.h>
#pragma comment(lib, "WINMM.LIB")
#define SCRW 680
#define SCRH 640
#include <iostream>
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
PIMAGE close,open,hell,soso;
int pow_score = 1;
bool flag = true;
/**********************************************************/

/***********************函数区域***************************/
ADATA getTime();
DWORD WINAPI playGame(LPVOID pM);
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
void open_Music();
void close_Music();
void mode_seltct();
void clearone(int i);
void clear_Music();
void init_mouseseg();
//void draw_play_place();//绘制游戏区域
void Double_PlayGame();//双人游戏
void delete_ranklist_one();
void rotate_(ablock* block);//旋转
void updatezt(ablock* block);
void drawblock(ablock* block);//画方块
void movew(ablock* block,int where);
void Get_point(ablock* block,int x,int y,int n);//获取旋转中心
/*************************************************************/
int DELAY = 50   ; //延时时间


#endif // TETRIS_H_INCLUDED
