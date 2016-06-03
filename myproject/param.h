//
//  param.h
//  myproject
//
//  Created by chrystal_zl on 16/6/2.
//  Copyright © 2016年 chrystal_zl. All rights reserved.
//

#ifndef param_h
#define param_h

#define LARGE_NUM  1.0e10


// on graph structure
#define NumNodes 	20  //网络中节点数
#define NumOri_Nodes 3 //初始投放的节点数
#define CONNECT_PARAM	0.002
#define UPPER_INFL 0.2

#define UPPER_WEIGHT	5
#define LOWER_WEIGHT	1


// on objective function
#define SIMU_NUM	500		//or 5000

//+++
//extern int TARGET_NUM;
//+++

// on problem type
#define TARGET_NUM 	 8


// on solve type
#define SOLVE_TYPE  1	// 1-7
/***
 1  value greedy
 2  distance					(SPL with r=1)
 3  longpath greedy			(MPLR with r=1)
 4  forest weight greedy		(SPFWR with r=1)
 5  2+1						(SPL)
 6  3+1						(MPLR)
 7  4+1						(SPFWR)
 ***/

#define DISSIMTYPE  3   // 1-3
/***
 1  1/x
 2  sum x / x
 3  upper-x
 ***/

#define TOPK  8

#endif /* param_h */
