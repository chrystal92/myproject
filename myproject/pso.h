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
#define N 50  //粒子群规模
#define G 5  //粒子群迭代次数
#define dim 20 //粒子维度

#define Vmax 5
#define Vmin -0.4

#define c1 2
#define c2 2
#define w1 0.9
#define w2 0.4

extern double price_discount[N];
extern double x[N][dim];
extern double p[N][dim+1];

extern double price_v[N];
extern double v[N][dim];
extern double v_all[N][dim+1];

extern double y[N];
extern double pbest[N];
extern double gbest;

extern double randd();
extern int randi(int k);
extern double* cal_fitness();
extern double MAX(double a,double b);
extern void init();
extern void pso();


#endif /* pso_h */
