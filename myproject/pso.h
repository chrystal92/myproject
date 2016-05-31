//
//  pso.h
//  myproject
//
//  Created by chrystal_zl on 16/5/19.
//  Copyright © 2016年 chrystal_zl. All rights reserved.
//

#ifndef pso_h
#define pso_h

#define PI 3.14159265
#define N 5  //粒子群规模
#define G 2  //粒子群迭代次数
#define dim 3  //粒子维度
int cur_n;
#define Vmax 0.4
#define Vmin -0.4

#define c1 2
#define c2 2
#define w1 0.9
#define w2 0.4

extern double price_discount[N];//商家选择的折扣
extern double x[N][dim];//选择的初始节点
extern double p[N][dim+1];//粒子群

extern double price_v[N];//折扣的速度
extern double v[N][dim];//节点的速度
extern double v_all[N][dim+1];

extern double price_y[N];//折扣的适应值
extern double y[N][dim];//节点的适应值
extern double y_all[N][dim+1];

extern double price_pbest[N];//折扣的局部最优
extern double pbest[N][dim];//节点的局部最优
extern double pbest_all[N][dim+1];

extern double price_gbest;//折扣的全局最优
extern double gbest[dim];//节点的全局最优
extern double gbest_all[dim+1];


extern double randd();
extern int randi(int k);
extern void cal_fitness();
extern double MAX(double a,double b);
extern void init();
extern void pso();


#endif /* pso_h */
