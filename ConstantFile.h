//
//  ConstantFile.h
//  SocialNetWork
//
//  Created by 王珏 on 15/12/21.
//  Copyright © 2015年 王珏. All rights reserved.
//

#ifndef ConstantFile_h
#define ConstantFile_h

#define NNODE 8
#define NEDGE 22
#define NSAMPLE 500
#define DIM 3


//文件路径
//#define NODE_PATH "/Users/wangjue/Documents/project/c++_project1/SocialNetwork/SocialNetWork/SocialNetWork/data/paper_nodetest.txt"
//#define EDGE_PATH "/Users/wangjue/Documents/project/c++_project1/SocialNetwork/SocialNetWork/SocialNetWork/data/paper_edgetest.txt"
//#define PROP_PATH "/Users/wangjue/Documents/project/c++_project1/SocialNetwork/SocialNetWork/SocialNetWork/data/paper_proptest.txt"
//#define SAMPLE_PATH "/Users/wangjue/Documents/project/c++_project1/SocialNetwork/SocialNetWork/SocialNetWork/data/samples.txt"
//#define BEO_DIR "/Users/wangjue/Documents/project/c++_project1/SocialNetwork/SocialNetWork/SocialNetWork/data/beo/"
//#define TSO_DIR "/Users/wangjue/Documents/project/c++_project1/SocialNetwork/SocialNetWork/SocialNetWork/data/tso/"

#define NODE_PATH "../SocialNetWorkGit/data/paper_nodetest.txt"
#define EDGE_PATH "../SocialNetWorkGit/data/paper_edgetest.txt"
#define PROP_PATH "../SocialNetWorkGit/data/paper_proptest.txt"
#define SAMPLE_PATH "../SocialNetWorkGit/data/samples.txt"
#define BEO_DIR "../data/beo/"
#define TSO_DIR "../data/tso/"

#define INFMAX 100000000

//在bestEffort阶段的Node状态
enum status {initial, bounded, exact};

//用户选择的算法
enum algorithm {precomputation, localGraph, neighborhood};
#endif /* ConstantFile_h */
