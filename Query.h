//
//  Query.h
//  SocialNetWork
//
//  Created by 王珏 on 15/12/21.
//  Copyright © 2015年 王珏. All rights reserved.
//

#ifndef Query_h
#define Query_h
#include <vector>

class Query{
    
public:
    
    vector<double> topicDistribution;
    int k;
    double epsilon;
};

#endif /* Query_h */
