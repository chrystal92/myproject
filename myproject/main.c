//
//  main.c
//  myproject
//
//  Created by chrystal_zl on 16/5/17.
//  Copyright © 2016年 chrystal_zl. All rights reserved.
//

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
    initializeGraph(); //生成网络结构
    init(); //初始化结果
    pso(); //粒子群迭代
    getchar();
    printf("end!");
    return 0;
}
