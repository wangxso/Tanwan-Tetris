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
PIMAGE close,open,hell,soso;
int pow_score = 1;
bool flag = true;
/**********************************************************/

/***********************��������***************************/
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
//void draw_play_place();//������Ϸ����
void Double_PlayGame();//˫����Ϸ
void delete_ranklist_one();
void rotate_(ablock* block);//��ת
void updatezt(ablock* block);
void drawblock(ablock* block);//������
void movew(ablock* block,int where);
void Get_point(ablock* block,int x,int y,int n);//��ȡ��ת����
/*************************************************************/
int DELAY = 50   ; //��ʱʱ��


#endif // TETRIS_H_INCLUDED
