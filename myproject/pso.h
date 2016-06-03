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
#define dim NumNodes  //粒子维度

#define Vmax 5
#define Vmin -0.4

#define c1 2
#define c2 2
#define w1 0.9
#define w2 0.4

extern double randd();
extern int randi(int k);
extern void cal_fitness();
extern double MAX(double a,double b);
extern void init();
extern void pso();


#endif /* pso_h */
