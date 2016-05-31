//
//  random.c
//  myproject
//
//  Created by chrystal_zl on 16/5/31.
//  Copyright © 2016年 chrystal_zl. All rights reserved.
//

#include "pso.h"
#include "random.h"
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
double randd()
{return (double)rand()/RAND_MAX;}//生成0，1之间的随机数

int randi(int k)
{return (int)(randd()*k+0.5);}