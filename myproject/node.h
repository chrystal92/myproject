//
//  node.h
//  myproject
//
//  Created by chrystal_zl on 16/6/2.
//  Copyright © 2016年 chrystal_zl. All rights reserved.
//

#ifndef node_h
#define node_h

typedef struct NodeType *Node;
struct NodeType
{
    int id;			// id of the node
    int numNeib;		// number of neighbors of the node
    Node *neighbor;		// Node pointers of neighbors
    int *neibID;		// ids of neighbors
    double *weight;		// the weights of the neighbors
    double sumweight;	// sum of the weights
    //++++++++
    int *whereNeibPutMe;		// the position where the neighbor puts me
    //++++++++
    int infln;		// 0 or 1, current situation of influence
    int *neibInfln;		// 0-1 vector of current influence situation of neighbors
    double thrhld;		// threshold of influence of the node
    Node next;
};


extern Node ori_graph;
extern int *id_select;

extern Node getNodepointer(Node graphnodes, int id);
extern int influenceAll(Node graphnodes, int id, double ori_price);
extern void destroy_graph_nodes(Node graphnodes);
extern Node copy_graph_nodes(Node graphnodes);
extern void initializeGraph();
extern void loadGraph();
extern void destroy_graph( double **gra );
extern int countNum1(Node graphnodes, int id);



#endif /* node_h */
