//
//  pso.c
//  myproject
//
//  Created by chrystal_zl on 16/5/19.
//  Copyright © 2016年 chrystal_zl. All rights reserved.
//

#include "pso.h"
#include "influence.h"
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

double y[N]; //适应值
double pbest[N]; //局部最优值
double gbest; //全局最优值

double ori_price[N]={0.6};
Node pso_node;

double* cal_fitness(double **a)//适应值函数
{
    Node node,retnode;
    node = copy_graph_nodes(ori_graph);
    retnode = node;
    a = (double**) calloc( N, sizeof(*a) );
    for(int i=0; i<N; i++)
        a[i] = (double*) calloc( dim+1, sizeof(**a) );
    
    for(int i=0;i<N;i++)
    {
        ori_price[i] = a[i][0];
        for(int j=1;j<dim+1;j++)
        {
            node->infln = a[N][j];
            node = node->next;
        }
        node = retnode;
        y[i] = influenceAll(node, 1,ori_price[i]);
    }
    return y;
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
    Node node;
    for(int i=0;i<N;i++)
    {
        node = getNodepointer(ori_graph,1);
        price_discount[i]=ori_price[0];//初始折扣赋给price_discount
        printf("price_discount[%d] is %f\t",i,price_discount[i]);
        price_v[i]=randd()*Vmax;

        for(int j=0;j<dim;j++)
        {
            x[i][j]=(double)node->infln; //初始影响状态赋给x
            printf("x[%d][%d] is %f\n",i,j,x[i][j]);
            v[i][j]=randd()*Vmax;
            node = node->next;
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
    node = getNodepointer(ori_graph, 1);
    for(int i=0;i<N;i++)
    {
        y[i] = influenceAll(node, 1, ori_price[0]);  //初始化局部最优
        pbest[i] = y[i];
    }
    gbest = pbest[0]; //初始化全局最优
}

void pso()
{
    int i,g;
    double w;
    Node node,retnode;
    for(g=0;g<G;g++)//进行G轮迭代
    {
        w=w2+(w1-w2)*(G-g)/G;
        for(i=0;i<N;i++)
        {
            for(int j=0;j<dim+1;j++)
            {v_all[i][j]=w*v_all[i][j]+c1*randd()*(pbest[i]-p[i][j])+c2*randd()*(gbest-p[i][j]);
                if(v_all[i][j]>Vmax)
                    v_all[i][j]=Vmax;
                p[i][j]+=v_all[i][j];
                if(p[i][j]<=0)
                 p[i][j]=0;
                 if(p[i][j]>=1)
                 p[i][j]=1;//++++++++++++这里可以设置x的范围，进一步思考!!!!!!
                printf("update round %d , p[%d][%d] is %f\n",g,i,j,p[i][j]);
            }
        }//更新一次v_all和p
        
        node = copy_graph_nodes(ori_graph);
        retnode = node;
        
        for(int i=0;i<N;i++)
        {
            ori_price[i] = p[i][0];
            for(int j=1;j<dim+1;j++)
            {
                node->infln = p[i][j];
                node = node->next;
            }
            node = retnode;
            y[i] = influenceAll(node, 1,ori_price[i]);
        }
        
        for(i=0;i<N;i++)
        {
            pbest[i]=MAX(pbest[i],y[i]);
            gbest=MAX(gbest,pbest[i]);
        }
        printf("update round %d of gbest is %f\n",g+1,gbest);
        printf("\n");
    }
}
