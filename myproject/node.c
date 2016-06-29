//
//  node.c
//  myproject
//
//  Created by chrystal_zl on 16/6/2.
//  Copyright © 2016年 chrystal_zl. All rights reserved.
//

#include "node.h"
#include "pso.h"
#include "random.h"
#include "param.h"

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <sys/malloc.h>

#define _CRT_SECURE_NO_DEPRECATE 1
#define RECORD_GRAPH

Node ori_graph;
int *id_select;//随机选取初始传播源

double **initial_graph()
{
    double **gra;
    int i,j;
    
    printf("Initialize Graph...");
    gra = (double**) calloc( NumNodes, sizeof(*gra) );
    for(i=0; i<NumNodes; i++)
        gra[i] = (double*) calloc( NumNodes, sizeof(**gra) );
    
    for(i=0; i<NumNodes; i++)
        for(j=0; j<NumNodes; j++)
            gra[i][j] = 0.0;
    
    for(i=0; i<NumNodes-1; i++)
        for(j=i+1; j<NumNodes; j++)
            if( check_threshold(CONNECT_PARAM) )
            {
                gra[i][j] = generate_weight();
                gra[j][i] = gra[i][j];
            }
    printf("done.\n");
    return gra;
}

void dircted_weight(double **gra) //由边的权值变成有向图
{
    int i,j;
    double sum;
    printf("change the weight of edge...\n");
    for(j=0;j<NumNodes;j++)
    {
        sum = 0.0;
        for(i=0;i<NumNodes;i++)
        {
            
            sum += gra[i][j];}
        //printf("sum of all to node[%d] is %.2f\n",j,sum);
        if(sum != 0.0)
            for(i=0;i<NumNodes;i++)
                gra[i][j] = gra[i][j]/sum;
    }
    
}

void show(double **gra)
{
    int i,j;
    for(i=0;i<NumNodes;i++)
    {
        for(j=0;j<NumNodes;j++)
            printf("%2.4f\t",gra[i][j]);
        printf("\n");
    }
}

void destroy_graph( double **gra )
{
    int i;
    for(i=0; i<NumNodes; i++)
        free(gra[i]);
    free(gra);
}

void connection_remedy( double **gra )    //保证图的连通性
{
    int i, j, k, goon=1;
    int x[NumNodes],y[NumNodes];
    
    printf("Remedy connectivity...");
    for(i=0; i<NumNodes; i++)
    {
        x[i] = 0;
        y[i] = 0;
    }
    
    x[0] = 1;
    
    while(goon == 1)
    {
        goon = 0;
        for(i=0; i<NumNodes; i++)
            if(x[i]==1 && y[i]==0)
            {
                goon = 1;
                y[i] = 1;
                for(j=0; j<NumNodes; j++)
                    if(gra[i][j]>0)
                        x[j] = 1;
            }
    }
    
    for(k=0; k<NumNodes; k++)
        if(x[k]==0)
        {
            gra[k][k-1] = generate_weight();
            gra[k-1][k] = gra[k][k-1];
            x[k] = 1;
            goon = 1;
            while(goon == 1)
            {
                goon = 0;
                for(i=0; i<NumNodes; i++)
                    if(x[i]==1 && y[i]==0)
                    {
                        goon = 1;
                        y[i] = 1;
                        for(j=0; j<NumNodes; j++)
                            if(gra[i][j]>0)
                                x[j] = 1;
                    }
            }
        }
    
    printf("done.\n");
}

void record_graph(double **gra)
{
    FILE *file;
    int i,j;
    
    file = fopen("recordGraph", "w");
    
    for(i=0; i<NumNodes; i++)
    {
        for(j=0; j<NumNodes; j++)
            fprintf(file, "  %lf", gra[i][j]);
        fprintf(file, "\n");
    }
    
    fclose(file);
}

Node newnode()
{
    Node node;
    
    node = (Node)malloc(sizeof(*node));
    
    node->id = 0;
    node->numNeib = 0;
    node->neighbor = NULL;
    node->neibID = NULL;
    node->weight = NULL;
    node->sumweight = 0.0;
    //+++++++++
    node->whereNeibPutMe = NULL;
    //+++++++++
    node->infln = 0;
    node->neibInfln = NULL;
    node->thrhld = 0.0;
    node->next = NULL;
    
    return node;
}

Node getNodepointer(Node graphnodes, int id)  //取得指向id节点的指针
{
    Node node;
    int i;
    
    node = graphnodes;
    
    //	if(id>1)
    for(i=1; i<id; i++)
        node = node->next;
    
    return node;
}

Node transform_graph(double **gra)
{
    Node node, retnode, tempnode;
    int i,j,k,r, count;
    int tempinfln;
    double sum;
    id_select = (int*) calloc( NumOri_Nodes, sizeof(id_select) );
    
    id_select = select_rand(id_select);
    retnode = newnode();
    node = retnode;
    
    node->id = 1;
    
    for(i=2; i<=NumNodes; i++)
    {
        tempnode = newnode();
        tempnode->id = i;
        node->next = tempnode;
        node = tempnode;
    }
    
    node = retnode;
    for(i=0; i<NumNodes; i++)
    {for(r=0;r<NumOri_Nodes;r++)
            if(node->id==id_select[r])
                node->infln = 1;
        node=node->next;}      //初始传播源的状态设为1
    
    node = retnode;
    for(i=0; i<NumNodes; i++)
    {
        //printf("start id = %d:\n",node->id);
        count = 0;
        for(j=0; j<NumNodes; j++)
            if(gra[j][i]>0.0)
                count++;
        node->numNeib = count;
        //printf("num of Neibors is %d\n",count);
        //printf("infln is %d\n",node->infln);
        
        node->thrhld = randg();
        //printf("thrhld is %f\n",node->thrhld);
        
        node->neighbor = (Node*)calloc(count, sizeof(Node));
        node->neibID = (int*)calloc(count, sizeof(int));
        node->weight = (double*)calloc(count, sizeof(double));
        node->neibInfln = (int*)calloc(count, sizeof(int));
        node->whereNeibPutMe = (int*)calloc(count, sizeof(int));
        
        k = 0;
        tempinfln=0;
        for(j=0; j<NumNodes; j++)
            if(gra[j][i]>0.0)
            {
                node->neighbor[k] = getNodepointer(retnode, j+1);
                node->neibID[k] = j+1;
                //printf("node->neibID[%d] is %d\t",k,node->neibID[k]);
                node->weight[k] = gra[j][i] * UPPER_INFL;
                //printf("node->weight[%d] is %f\t",k,node->weight[k]);
                node->neibInfln[k] = node->neighbor[k]->infln;
                //printf("this neighbor is %d\n",node->neighbor[k]->infln);
                k++;
            }
        sum = 0.0;
        for(k=0; k<count; k++){
            if(node->neibInfln[k]==1)
                sum += node->weight[k];}
        node->sumweight = sum;
        //printf("sumweight is %f\n",node->sumweight);
        node->thrhld += node->sumweight;
        //printf("update thrhld is %f\n",node->thrhld);
        //printf("********end id %d\n\n",node->id);
        node = node->next;
    }
    //+++++++++
    node = retnode;
    for(i=1; i<=NumNodes; i++)
    {
        for(j=0; j<node->numNeib; j++)
        {
            for(k=0; k<node->neighbor[j]->numNeib; k++)
                if(node->neighbor[j]->neibID[k] == i)
                {
                    node->whereNeibPutMe[j] = k;
                    break;
                }
        }
        node = node->next;
    }
    //+++++++++
    return retnode;
}

int influenceAll(Node graphnodes, int id, double ori_price)
{
    Node bef_node,retbef_node,retaft_node;
    int cur=0,sum_bef,sum_aft,temp;
    
    sum_bef = countNum1(graphnodes,1);
    sum_aft = sum_bef+1;
    bef_node = getNodepointer(graphnodes, id);//上一个时间段截止时的状态记录
    retbef_node = bef_node;
    
    while(1)
    {
        if(sum_aft < sum_bef)
        {
            printf("program failed....please check bug!!!\n");
            break;
        }
        if(sum_aft == sum_bef)
            break;
        
        Node aft_node;
        aft_node = copy_graph_nodes(bef_node);//修改本时间段内的状态
        retaft_node = aft_node;
        
        sum_bef = countNum1(bef_node,1);
        sum_aft = sum_bef;
        
        for(int i=0;i<NumNodes;i++)
        {
            if(bef_node->infln == 1)
                printf("ddnAlarm: id %d have been influenced!\n",bef_node->id);
            else if (bef_node->thrhld >= ori_price)
            {
                aft_node->infln = 1;
                sum_aft ++;
                printf("update id %d is influenced!\n",aft_node->id);
                for(int k=0; k<aft_node->numNeib; k++)
                {
                    temp = aft_node->whereNeibPutMe[k];
                    aft_node->neighbor[k]->sumweight += aft_node->neighbor[k]->weight[temp];
                    //printf("update sumweight of neib[%d] is %f\n",k,aft_node->neighbor[k]->sumweight);
                    aft_node->neighbor[k]->thrhld += aft_node->neighbor[k]->sumweight;
                    //printf("update thrhld of neib[%d] is %f\n",k,aft_node->neighbor[k]->thrhld);
                }
            }
            else
                printf("id %d thrhld is %f,not enough to let him buy!\n",bef_node->id,bef_node->thrhld);
            
            bef_node = bef_node->next;
            aft_node = aft_node->next;
        }
        //printf("check round %d end!\n",cur+1);
        //printf("\n");
        
        bef_node = retbef_node;
        aft_node = retaft_node;
        bef_node = copy_graph_nodes(aft_node);
        retbef_node = bef_node;
        destroy_graph_nodes(aft_node);
        
        cur++;
    }
    return sum_aft;
}

void destroy_graph_nodes(Node graphnodes)
{
    Node node, temp_node;
    int i;
    
    temp_node = graphnodes;
    for(i=0; i<NumNodes; i++)
    {
        free(temp_node->neighbor);
        free(temp_node->neibID);
        free(temp_node->weight);
        free(temp_node->neibInfln);
        //++++++++
        free(temp_node->whereNeibPutMe);
        //++++++++
        temp_node = temp_node->next;
    }
    
    node = graphnodes;
    temp_node = node;
    for(i=0; i<NumNodes; i++)
    {
        node = temp_node->next;
        free(temp_node);
        temp_node = node;
    }
}

Node copynode(Node ori_node)	// do not copy "->next" or "->neighbor[i]"
{
    Node node;
    int i;
    
    node = newnode();
    
    node->id = ori_node->id;
    node->numNeib = ori_node->numNeib;
    node->sumweight = ori_node->sumweight;
    node->infln = ori_node->infln;
    node->thrhld = ori_node->thrhld;
    
    node->neighbor = (Node*)calloc(node->numNeib, sizeof(Node));
    node->neibID = (int*)calloc(node->numNeib, sizeof(int));
    node->weight = (double*)calloc(node->numNeib, sizeof(double));
    node->neibInfln = (int*)calloc(node->numNeib, sizeof(int));
    
    node->whereNeibPutMe = (int*)calloc(node->numNeib, sizeof(int));
    
    for(i=0; i<node->numNeib; i++)
    {
        node->neibID[i] = ori_node->neibID[i];
        node->weight[i] = ori_node->weight[i];
        node->neibInfln[i] = ori_node->neibInfln[i];
        
        node->whereNeibPutMe[i] = ori_node->whereNeibPutMe[i];
    }
    
    return node;
}

Node copy_graph_nodes(Node graphnodes)  //返回的是复制后头节点的位置
{
    Node retgraphnodes, node, ori_node, old_node;
    int i;
    
    ori_node = graphnodes;
    retgraphnodes = copynode(ori_node);
    node = retgraphnodes;
    old_node = node;
    
    ori_node = ori_node->next;
    
    while(ori_node != NULL)
    {
        node = copynode(ori_node);
        old_node->next = node;
        old_node = node;
        ori_node = ori_node->next;
    }
    
    node = retgraphnodes;
    while(node != NULL)
    {
        for(i=0; i<node->numNeib; i++)
            node->neighbor[i] = getNodepointer(retgraphnodes, node->neibID[i]);
        node = node->next;
    }
    
    return retgraphnodes;
}

void initializeGraph()
{
    double **gra;
    
    gra = initial_graph();
    connection_remedy(gra);
    //show(gra);
    dircted_weight(gra);
    //show(gra);
    //getchar();
    
    
#ifdef RECORD_GRAPH
    record_graph(gra);
#endif
    
    ori_graph = transform_graph(gra);
    printf("ori_graph start...\n");
    destroy_graph(gra);
    
}
void loadGraph()
{
    FILE *file;
    int i,j;
    double **gra;
    
    gra = (double**) calloc( NumNodes, sizeof(*gra) );
    for(i=0; i<NumNodes; i++)
        gra[i] = (double*) calloc( NumNodes, sizeof(**gra) );
    
    file = fopen("recordGraph", "r");
    
    for(i=0; i<NumNodes; i++)
        for(j=0; j<NumNodes; j++)
            fscanf(file, "  %lf", &gra[i][j]);
    
    fclose(file);
    
    ori_graph = transform_graph(gra);
    
    destroy_graph(gra);
}
int countNum1(Node graphnodes, int id)
{
    Node node = getNodepointer(graphnodes, id);
    int count1=0;
    for(int i=0;i<NumNodes;i++)
    {
        if(node->infln == 1)
            count1++;
        node=node->next;
    }
    //printf("count1 is %d\n",count1);
    return count1;
}
