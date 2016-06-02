//
//  random.h
//  myproject
//
//  Created by chrystal_zl on 16/5/31.
//  Copyright © 2016年 chrystal_zl. All rights reserved.
//

#ifndef random_h
#define random_h

extern double randd();
extern int randi(int k);
extern double random_uniform(double a, double b);
extern int check_threshold( double th );
extern double generate_weight();
extern int Rand(int X,int Y);
extern void select_rand(int *id_set);

extern double getSecs();

extern void present( double v, int *xv );

extern double ddntime;

#endif /* random_h */
