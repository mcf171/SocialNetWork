//
//  ConstantFile.h
//  SocialNetWork
//
//  Created by 王珏 on 15/12/21.
//  Copyright © 2015年 王珏. All rights reserved.
//

#ifndef ConstantFile_h
#define ConstantFile_h

#define NNODE 10
#define NEDGE 35
#define NSAMPLE 500
#define DIM 3

#define NODE_PATH "../SocialNetWorkGit/data/nodetest.txt"
#define EDGE_PATH "../SocialNetWorkGit/data/edgetest.txt"
#define PROP_PATH "../SocialNetWorkGit/data/proptest.txt"
#define SAMPLE_PATH "../SocialNetWorkGit/data/samples.txt"

#define INFMAX 100000000

enum status {initial, bounded, exact};

enum algorithm {precomputation, localGraph, neighborhood};
#endif /* ConstantFile_h */
