//
//  random.c
//  myproject
//
//  Created by chrystal_zl on 16/5/31.
//  Copyright © 2016年 chrystal_zl. All rights reserved.
//

#define _CRT_SECURE_NO_DEPRECATE 1

#include "pso.h"
#include "influence.h"
#include "random.h"
#include "node.h"
#include "param.h"
#include <stdio.h>
#include "string.h"
#include <math.h>
#include <time.h>
#include <stdlib.h>


double randd()
{return (double)rand()/RAND_MAX;}//生成0，1之间的随机数

int randi(int k)
{return (int)(randd()*k+0.5);}

double randg()
{
    double r = (double)rand()/RAND_MAX;
    if(r>=0.8)
        r = r-UPPER_INFL;
    return r;
}   //生成0，0.8之间的随机初始阈值
double ddntime;

double random_uniform(double a, double b)      // Uniform Distribution
{
    double y;
    y = (double)rand()/(RAND_MAX);
    return (a+(b-a)*y);
}

int check_threshold( double th )
{
    double y;
    
    y = (double)rand()/(RAND_MAX);
    
    if( y < th )
        return 1;
    else
        return 0;
}

int* select_rand(int *id_set)  //选取随机数
{
    int arr[NumNodes];
    int i;
    int r;
    int temp;
    id_set = (int*) calloc( NumOri_Nodes, sizeof(id_set) );
    srand((unsigned)time(NULL));
    for(i=0;i<NumNodes;i++) arr[i]=i+1;//将数组赋值1~NumNodes
    for(i=0;i<NumNodes;i++)
    {
        r=Rand(0,NumNodes-1);
        temp=arr[i];
        arr[i]=arr[r];
        arr[r]=temp;
    }//数组乱序
    for(i=1;i<=NumOri_Nodes;i++)
    {
        id_set[i-1]=arr[i-1];
        //printf("id_select[%d] is %3d\n",i-1,id_set[i-1]);
    }
    return id_set;
}

double generate_weight()
{
    double y;
    y = (double)( rand()%UPPER_WEIGHT + 1 );
    return y;
}

int Rand(int X,int Y)     //生成x到y之间的随机数
{
    int temp;
    if(X>Y)
    {
        temp=X;
        X=Y;
        Y=temp;
    }
    return rand()%(Y-X+1)+X;
    
}


double getSecs( )    //得到总的cpu时间
{
    /* Get total CPU time in seconds. */
    clock_t t;
    
    t = clock();
    
    //return ( ((double) t)/CLK_TCK );
    return ( ((double) t)/2.0 );
    
}

void present( double v, int *xv )
{
    FILE *file;
    int i;
    char filename[2048]="";
    char temp[30];
    
    // network
    sprintf( temp, "N%d_", NumNodes);
    strcat( filename, temp );
    sprintf( temp, "p%.3f_", CONNECT_PARAM);
    strcat( filename, temp );
    
    // problem
    sprintf( temp, "k%d_", TARGET_NUM);
    strcat( filename, temp );
    
    // algorithm
    sprintf( temp, "STY%d_", SOLVE_TYPE);
    strcat( filename, temp );
    sprintf( temp, "w%d_", DISSIMTYPE);
    strcat( filename, temp );
    sprintf( temp, "r%d", TOPK);
    strcat( filename, temp );
    
    sprintf( temp, ".txt");
    strcat( filename, temp );
    
    
    
    file = fopen(filename, "w");
    
    fprintf(file, "The optimal value is:  %f\n\n", v);
    fprintf(file, "A=[");
    
    for(i=0; i<NumNodes; i++)
        if( xv[i] == 1 )
            fprintf(file, "%d, ", i+1);
    fprintf(file, "]\n\n");
    
    fprintf(file, "time=%.3fs", ddntime);
    
    fclose(file);
}

