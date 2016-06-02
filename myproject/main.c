//
//  main.c
//  myproject
//
//  Created by chrystal_zl on 16/5/17.
//  Copyright © 2016年 chrystal_zl. All rights reserved.
//
/*测试函数为 y=x*sin(10*pi*x)+2     x取值范围[-1, 2]*/
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "pso.h"
#include "random.h"
#include "node.h"
#include "param.h"
int main()
{
    srand((unsigned)time(NULL));
    init();
    pso();
    
    initializeGraph();
    int id_select[10]={0};//随机选取10个节点作为初始传播源
    select_rand(id_select);
    getchar();
    printf("end!");
    return 0;
}
