//
//  pso.c
//  myproject
//
//  Created by chrystal_zl on 16/5/19.
//  Copyright © 2016年 chrystal_zl. All rights reserved.
//

#include "pso.h"
#include "random.h"
#include "node.h"
#include "param.h"
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>


double price_discount[N];//商家选择的折扣
double x[N][dim];//选择的初始节点
double p[N][dim+1];//粒子群

double price_v[N];//折扣的速度
double v[N][dim];//节点的速度
double v_all[N][dim+1];

double price_y[N];//折扣的适应值
double y[N][dim];//节点的适应值
double y_all[N][dim+1];

double price_pbest[N];//折扣的局部最优
double pbest[N][dim];//节点的局部最优
double pbest_all[N][dim+1];

double price_gbest;//折扣的全局最优
double gbest[dim];//节点的全局最优
double gbest_all[dim+1];

void cal_fitness()//适应值函数
{
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<dim+1;j++)
            y_all[i][j]=p[i][j]*sin(10*PI*p[i][j])+2;
    }
}

double MAX(double a,double b)
{
    double max;
    if(a>b) max=a;
    else max=b;
    return max;
}

void init()
{
    //随机生成*price_discount *price_v和**x **v中各个值
    for(int i=0;i<N;i++)
    {
        price_discount[i]=randd();
        price_v[i]=randd()*Vmax;

        for(int j=0;j<dim;j++)
        {
            x[i][j]=randd();
            
            v[i][j]=randd()*Vmax;
        }
    }
    
    //把*price_discount和**x合并为**p
    {for(int m=0;m<N;m++)
        p[m][0]=price_discount[m];
        for(int f=0;f<N;f++)
            for(int k=0;k<dim;k++)
                p[f][k+1]=x[f][k];
    }
    
    //把*price_v和**v合并为**v_all
    {for(int m=0;m<N;m++)
        v_all[m][0]=price_v[m];
        for(int f=0;f<N;f++)
            for(int k=0;k<dim;k++)
                v_all[f][k+1]=v[f][k];
    }
    /*-----end-----初始化位置和速度-----end-----*/
    
    cal_fitness();
    /*-----end-----初始化适应值-----end-----*/
    
    for(int i=0;i<N;i++)
        for(int j=0;j<dim+1;j++)
        {pbest_all[i][j]=y_all[i][j];
            printf("initial pbest_all[%d][%d] is %f\n",i,j,pbest_all[i][j]);
        }
    printf("\n");
    /*-----end-----初始化局部最优-----end-----*/
    
    for(int j=0;j<dim+1;j++)
        gbest_all[j] = y_all[0][j];
    for(int i=0;i<N;i++)
        for(int j=0;j<dim+1;j++)
            gbest_all[j]=MAX(gbest_all[j],y_all[i][j]);
    for(int j=0;j<dim+1;j++)
        printf("initial gbest_all[%d] is %f\n",j,gbest_all[j]);
    printf("\n");
    /*-----end-----初始化全局最优-----end-----*/
}

void pso()
{
    int i,g;
    double w;
    for(g=0;g<G;g++)//进行G轮迭代
    {
        w=w2+(w1-w2)*(G-g)/G;
        for(i=0;i<N;i++)
        {
            for(int j=0;j<dim+1;j++)
            {v_all[i][j]=w*v_all[i][j]+c1*randd()*(pbest_all[i][j]-p[i][j])+c2*randd()*(gbest_all[j]-p[i][j]);
                //if(v_all[i][j]>Vmax)
                //v_all[i][j]=Vmax;
                p[i][j]+=v_all[i][j];
                /*if(p[i][j]<-1)
                 p[i][j]=-1;
                 if(p[i][j]>2)
                 p[i][j]=2;//++++++++++++这里可以设置x的范围，进一步思考!!!!!!
                 */
            }
        }//更新一次v_all和p
        cal_fitness();

        for(i=0;i<N;i++)
        {
            for(int k=0;k<dim+1;k++)
            {pbest_all[i][k]=MAX(pbest_all[i][k],y_all[i][k]);
                printf("update round %d of pbest_all[%d][%d] is %f\n",g+1,i,k,pbest_all[i][k]);
                gbest_all[k]=MAX(gbest_all[k],pbest_all[i][k]);
            }
        }
        printf("\n");
        for(int k=0;k<dim+1;k++)
            printf("update round %d of gbest_all[%d] is %f\n",g+1,k,gbest_all[k]);
        printf("\n");
    }
}
