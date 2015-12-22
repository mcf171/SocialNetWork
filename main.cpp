//
//  main.cpp
//  SocialNetWork
//
//  Created by 王珏 on 15/12/21.
//  Copyright © 2015年 王珏. All rights reserved.
//

#include <iostream>
#include "Node.h"
#include <vector>


using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...

    vector<Node> nodes;
    Node node1;
    node1.index = 1;
    Node node2;
    node2.index = 2;
    
    nodes.push_back(node1);
    nodes.push_back(node2);
    
    Node node3;
    node3.index = 3;
    bool exist = findNode(nodes, node3);
    
    cout<<exist<<endl;
    
    node3.index = 1;
    exist = findNode(nodes, node3);
    
    cout<<exist<<endl;

    
    return 0;
}
