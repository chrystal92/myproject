//
//  pso.c
//  myproject
//
//  Created by chrystal_zl on 16/5/19.
//  Copyright © 2016年 chrystal_zl. All rights reserved.
//

#include "pso.h"
#include "random.h"
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

void cal_fitness()//适应值函数
{
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<dim+1;j++)
            y_all[i][j]=p[i][j]*sin(10*PI*p[i][j])+2;
    }
    /*-----如下部分已删掉-----*/
    /*for(int i=0;i<N;i++)
     {
     price_y[i]=price_discount[i]*sin(10*PI*price_discount[i]+2);
     for(int j=0;j<dim;j++)
     y[i][j]=x[i][j]*sin(10*PI*x[i][j])+2;
     }*/
    //把*price_y和**y合并为**y_all
    /*{
     for(int m=0;m<N;m++)
     {y_all[m][0]=price_y[m];
     //printf("price_y[%d] is %f\n",m,price_y[m]);
     //printf("y_all[%d][0] is %f\n",m,y_all[m][0]);
     }
     for(int f=0;f<N;f++)
     for(int k=0;k<dim;k++)
     {y_all[f][k+1]=y[f][k];
     //printf("y_all[%d][%d] is %f\n",f,k+1,y_all[f][k+1]);
     }
     for(int ii=0;ii<N;ii++)
     for(int jj=0;jj<dim+1;jj++)
     printf("initial y_all[%d][%d] is %f\n",ii,jj,y_all[ii][jj]);
     printf("\n");
     
     }*/
    /*-----以上部分删除完毕-----*/
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
        //printf("initial price_discount[%d] is %f\n",i,price_discount[i]);
        //printf("initial price_v[%d] is %f\n",i,price_v[i]);
        //printf("\n");
        for(int j=0;j<dim;j++)
        {
            x[i][j]=randd();
            //printf("initial x[%d][%d] is %f\n",i,j,x[i][j]);
            v[i][j]=randd()*Vmax;
            //printf("initial v[%d][%d] is %f\n",i,j,v[i][j]);
        }
        //printf("\n");
    }
    //printf("\n");
    
    //把*price_discount和**x合并为**p
    {for(int m=0;m<N;m++)
        p[m][0]=price_discount[m];
        for(int f=0;f<N;f++)
            for(int k=0;k<dim;k++)
                p[f][k+1]=x[f][k];
        /*for(int ii=0;ii<N;ii++)
         for(int jj=0;jj<dim+1;jj++)
         //printf("initial p[%d][%d] is %f\n",ii,jj,p[ii][jj]);
         printf("\n");*/
    }
    
    //把*price_v和**v合并为**v_all
    {for(int m=0;m<N;m++)
        v_all[m][0]=price_v[m];
        for(int f=0;f<N;f++)
            for(int k=0;k<dim;k++)
                v_all[f][k+1]=v[f][k];
        /*for(int ii=0;ii<N;ii++)
         for(int jj=0;jj<dim+1;jj++)
         //printf("initial v_all[%d][%d] is %f\n",ii,jj,v_all[ii][jj]);
         printf("\n");*/
    }
    /*-----end-----初始化位置和速度-----end-----*/
    
    cal_fitness();
    //+++++++++++++++++++++++++++输出
    /*{for(int i=0;i<N;i++)
     {//printf("initial fitness price_y[%d] is %f\n",i,price_y[i]);
     for(int j=0;j<dim;j++)
     //printf("initial fitness y[%d][%d] is %f\n",i,j,y[i][j]);
     printf("\n");
     }
     for(int i=0;i<N;i++)
     for(int k=0;k<dim+1;k++)
     //printf("initial fitness y_all[%d][%d] is %f\n",i,k,y_all[i][k]);
     printf("\n");
     }*/
    //+++++++++++++++++++++++++++打印完毕
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
    /*已删掉的1.0版代码*/
    /*for(int i=0;i<N;i++)
     for(int j=0;j<dim+1;j++)
     {pbest_all[i][j]=y_all[i][j];}
     
     price_gbest = price_y[0];
     for(int i=0;i<N;i++)
     {
     price_pbest[i]=price_y[i];
     printf("initial price_pbest[%d] is %f\n",i,price_pbest[i]);
     price_gbest = MAX(price_gbest,price_y[i]);
     }
     printf("initial price_gbest is %f\n",price_gbest);
     printf("\n");
     
     for(int j=0;j<dim;j++)
     gbest[j]=y[0][j];
     for(int i=0;i<N;i++)
     for(int j=0;j<dim;j++)
     {pbest[i][j]=y[i][j];//初始的粒子自身历史最优值
     printf("initial pbest[%d][%d] is %f\n",i,j,pbest[i][j]);
     gbest[j]=MAX(gbest[j],y[i][j]);//初始的全局最优值
     //printf("initial gbest[%d] is %f\n",j,gbest[j]);
     }
     printf("\n");
     for(int i=0;i<dim;i++)
     printf("initial gbest[%d] is %f\n",i,gbest[i]);
     printf("\n");*/
    /*-----end-----初始化局部最优和全局最优-----end-----*/
    //把*price_pbest和**pbest合并为**pbest_all
    /*{for(int m=0;m<N;m++)
     pbest_all[m][0]=price_pbest[m];
     for(int f=0;f<N;f++)
     for(int k=0;k<dim;k++)
     pbest_all[f][k+1]=pbest[f][k];
     for(int ii=0;ii<N;ii++)
     for(int jj=0;jj<dim+1;jj++)
     //printf("initial pbest_all[%d][%d] is %f\n",ii,jj,pbest_all[ii][jj]);
     printf("\n");
     }*/
    //把price_gbest和*gbest合并为*gbest_all
    /*{gbest_all[0]=price_gbest;
     for(int i=0;i<dim+1;i++)
     gbest_all[i+1]=gbest[i];
     //printf("initial gbest_all[%d] is %f\n",i,gbest_all[i]);
     printf("\n");
     }*/
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
                //printf("update round %d of v_all[%d][%d] is %f\n",g+1,i,j,v_all[i][j]);
                //printf("update round %d of p[%d][%d] is %f\n",g+1,i,j,p[i][j]);
                /*if(p[i][j]<-1)
                 p[i][j]=-1;
                 if(p[i][j]>2)
                 p[i][j]=2;//++++++++++++这里可以设置x的范围，进一步思考!!!!!!
                 */
            }
            //printf("\n");
        }//更新一次v_all和p
        cal_fitness();
        /*for(int i=0;i<N;i++)
         for(int j=0;j<dim+1;j++)
         //printf("update round %d of fitness y_all[%d][%d] is %f\n",g+1,i,j,y_all[i][j]);
         printf("\n");*/
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
