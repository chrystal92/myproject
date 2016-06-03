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
#include "influence.h"


int main()
{
    srand((unsigned)time(NULL));
    initializeGraph();
    //init();
    //pso();
    printf("sum number of influenced nodes is %d",influenceAll(ori_graph,1));
    getchar();
    printf("end!");
    return 0;
}
