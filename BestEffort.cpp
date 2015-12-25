//
//  BestEffort.cpp
//  SocialNetWork
//
//  Created by 王珏 on 15/12/23.
//  Copyright © 2015年 王珏. All rights reserved.
//

#include "BestEffort.hpp"
#include "Graph.hpp"
#include "Query.h"
#include "Node.hpp"
#include "Edge.hpp"
#include "Tree.hpp"
#include <vector>


/*
 * 计算在给定主题下的上界
 * @param u 给定点
 * @param S，种子集合
 * @param q，查询语句
 * @param chooseAlgorithm，用户选择算法
 */

double hat_delta_sigma(Node u,map<int, Node>S,Query q, algorithm choosAlgorithm)
{
    double result = 0;
    
    if (choosAlgorithm == precomputation) {

        result = hat_delta_p_u(u.MIA) - 1;
        
        if (S.size() != 0) {
            
            result = (1-u.ap_node_S_gamma)*result;
        }

    }
    
    return  result;
}

//针对LocalGraph算法，当进行在线查询时进行重构MIA
void preprocessOnline(Graph&g, Query q)
{
    map<int, Node>::iterator nodeIter;
    for (nodeIter = g.nodes.begin(); nodeIter != g.nodes.end(); nodeIter ++) {
		Node node = nodeIter->second;
        
        map<int, Edge*>::iterator edgeIter;
        for (edgeIter = node.neighbourEdge.begin(); edgeIter != node.neighbourEdge.end(); edgeIter++) {
            Edge* edge = edgeIter->second;
            
            double distance = q.topicDistribution[0]*edge->realDistribution[0]+q.topicDistribution[1]*edge->realDistribution[1]+q.topicDistribution[2]*edge->realDistribution[2];
            edge->distance = distance;
            edge->weight = distance;
        }
    }
    
    for (nodeIter = g.nodes.begin(); nodeIter != g.nodes.end(); nodeIter ++)
    {
        
		Dijkstra(g, nodeIter->second,(nodeIter->second.MIA));
    }
}


/*
 * 基于Precomputation的方法
 * precomputation方法只选取每条边上topic分布最大的topic
 * @param g 社交网络图
 */

void precomputationBased(Graph& g)
{
    
    map<int, Node>::iterator nodeIter;

    //对于图中的每个节点都将边设置为最大的topic值
    for (nodeIter = g.nodes.begin(); nodeIter != g.nodes.end(); nodeIter ++) {

        //获取社交网络图中每个节点
		Node node = nodeIter->second;
        
        map<int, Edge*>::iterator edgeIter;
		nodeIter->second.ap_node_S_gamma = 1.0;
        //获取节点的每个邻边将边的权重设置为最大的topic
        for (edgeIter = node.neighbourEdge.begin(); edgeIter != node.neighbourEdge.end(); edgeIter++) {
			Edge* edge = edgeIter->second;

            double maxDistance = 0;

			for (int i = 0; i < DIM; i++)
			{
				if(edge->realDistribution[i] > maxDistance)
                    maxDistance = edge->realDistribution[i];
			}
            edge->distance = maxDistance;
            edge->weight = maxDistance;
            edge->isVisited = false;
        }
    }
    
    //对每个节点计算构建MIA
    for (nodeIter = g.nodes.begin(); nodeIter != g.nodes.end(); nodeIter ++)
    {
        
		Dijkstra(g, nodeIter->second,nodeIter->second.MIA);
        
        //cout<<g.nodes[1].MIA->node->number<<endl;
    }
    
    //构建完每个节点的MIA之后可以计算每个节点的影响力上界。
    
    calculateGraph(g);
    
    //cout<<"create MIA";
}

void getLocalGraph(Tree tree,double theta,vector<Node> &nodes){
    
    if (tree.node->influence > theta)
        nodes.push_back(*tree.node);
    
    vector<Tree*>::iterator iterator;
    for (iterator = tree.nextNode.begin(); iterator != tree.nextNode.end(); iterator++)
        getLocalGraph(*(*iterator), theta, nodes);
    
}

/*
* localGraph算法是基于Precomputation算法的，然后通过Precomputation算法构建的图再构建一个子图
* @param g 社交网络图
* @param theta，用户自定义的阈值
* @param q 在线
*/
void localGraphBased(Graph& g,double theta, Query q)
{
    map<int, Node>::iterator nodeIter;
    precomputationBased(g);
/*
for (nodeIter = g.nodes.begin(); nodeIter != g.nodes.end(); nodeIter ++) {
		Node node = nodeIter->second;
        
        map<int,Edge*>::iterator edgeIter;
        for (edgeIter = node.neighbourEdge.begin(); edgeIter != node.neighbourEdge.end(); edgeIter++) {
            Edge* edge = edgeIter->second;
            //vector<double>::iterator distanceIter;
            double maxDistance = 0;
            //for (distanceIter = edge->realDistribution.begin(); distanceIter != edge->realDistribution.end(); distanceIter++) {
            //    if(*distanceIter > maxDistance)
            //        maxDistance = *distanceIter;
            //}
			for (int i = 0; i < DIM; i++)
			{
				if(edge->realDistribution[i] > maxDistance)
                    maxDistance = edge->realDistribution[i];
			}
            edge->distance = maxDistance;
            edge->weight = maxDistance;
        }
    }
*/

    //得到每个User的hat_gama;
    for (nodeIter = g.nodes.begin(); nodeIter != g.nodes.end(); nodeIter ++)
    {
        
        Dijkstra(g, nodeIter->second,(nodeIter->second.MIA));
        double distance = getLocalDistance(nodeIter->second.MIA, theta);

     //   cout<<"the hat_gama of "<<(*nodeIter).number<<" is :"<<distance<<endl;
    }
    
    
    for (nodeIter = g.nodes.begin(); nodeIter != g.nodes.end(); nodeIter ++)
    {
        Node node = nodeIter->second;
        vector<Node> nodes;
        nodes.clear();
        getLocalGraph(*node.MIA, theta, nodes);
        
        //tempNode.push_back(*nodeIter.)
    }

}

void neighborhoodBased(Graph& g)
{
   
}

double estInfUB(Node node, Graph g, double theta)
{
    double maxInfluence;
    
    return maxInfluence;
}

/*
 * 离线部分主要功能计算每个点的最大影响上界
 * 在Precomputation算法中是脱离了在线部分的查询Q，但是对于LocalGraph算法是需要结合在线查询的Q，但是只计算影响力大的点
 * @param g 社交网络图
 * @param theta 用户自定义阈值
 * @param bestEffort bestEffort算法对象
 * @param q 查询语句
 */

void bestEffortOffline(Graph g, double theta, BestEffort& bestEffort,Query q,algorithm chooseAlgorithm)
{
    
    //获取图中所有的Users

    if (chooseAlgorithm == precomputation) {
        //precomputaion算法
        precomputationBased(g);
    }
    else if(chooseAlgorithm == localGraph){
        //LocalGraph算法
        localGraphBased(g, theta, q);
    }

    //将计算后的节点插入优先队列
	for (map<int, Node>::iterator iter=g.nodes.begin(); iter!=g.nodes.end(); iter++)
    {  
		if (chooseAlgorithm == localGraph)
			iter->second.influence = iter->second.hat_delta_sigma_p;

        bestEffort.L.push(iter->second);
    }  

    
}



/*
 * 在线部分主要计算在给定主题分布下的精确上界
 * @param g 社交网络图
 * @param q，查询语句
 * @param theta，用户定义的阈值
 * @param bestEffort，bestEffort变量，保存优先队列和最大堆
 * @param chooseAlgorithm，用户选择算法
 */
map<int, Node>* bestEffortOnline(Graph g ,Query q, double theta, BestEffort& bestEffort,algorithm chooseAlgorithm)
{

    //S保存种子
    map<int, Node>* S = new map<int, Node>;

    //初始化一个空的最大堆
    while (!bestEffort.H.empty()) {
        bestEffort.H.pop();
    }

    S->clear();
    //预处理在线节点针对LocalGraph算法，如果不是LocalGraph算法
    if(chooseAlgorithm == localGraph)
        preprocessOnline(g, q);
    
    //K次循环找到所有合适的种子
    for (int i = 0; i < q.k ; i++)
    {

        
        do
        {
            //从离线的优先队列中和最大堆中考虑是否加入新的元素
            insertCandidates(bestEffort.L, bestEffort.H);
            
            //从堆顶取一个元素
            Node u = bestEffort.H.top();
            bestEffort.H.pop();
            
            //如果是初始状态那么久进一步计算在gama主题分布下的上界
            if (initial == u.currentStatus)
            {
                double sigma_new = hat_delta_sigma(u, *S, q,chooseAlgorithm);
                u.currentStatus = bounded;
                u.influence = sigma_new;
                bestEffort.H.push(u);
            }
            //如果已经是gamga主题分布下的上界则计算精确的上界
            else if (bounded == u.currentStatus)
            {
                double sigma_new = CalcMargin(u, g, theta, q, *S);
                u.currentStatus = exact;
                u.influence = sigma_new;
                bestEffort.H.push(u);
            }
            //如果已经是精确上界则直接弹出
            else if (exact == u.currentStatus)
            {
				(*S)[u.number]=u;
                map<int,Node>::iterator itertor;
                for (itertor = g.nodes.begin(); itertor != g.nodes.end(); itertor ++) {
                    
					if(!findKey(*S, itertor->second.number))
                       itertor->second.ap_node_S_gamma =  calAP(itertor->second, *S, q);
                }
                
                break;
            }
        }while (!bestEffort.H.empty());//end while
    }//end for
    
    return S;
}


/*
	Adding posible candidates from L
 */
void insertCandidates(priority_queue<Node> &L, priority_queue<Node> &H)
{
    //return if L is empty
    if (L.empty())
    {
        return;
    }
    
    //insertion process until H.top > L.top
    while (!L.empty())
    {
        if (H.empty() || H.top() <= L.top()) {
            H.push(L.top());
            L.pop();
        }else
            break;
    }
}


void initEdge(Graph g)
{
    
}


double sigma(map<int, Node> nodes, Graph g ,Query q)
{
    
    map<int, Node>::iterator itertor;
    double result = 0;
    for(itertor = g.nodes.begin(); itertor != g.nodes.end() ; itertor ++)
        result+=calAP(itertor->second, nodes, q );
    
    return result;
}


/*
 * 计算在给定主题下的精确上界
 * @param u 给定点
 * @param g 社交网络图
 * @param theta，用户定义阈值
 * @param gama，查询语句
 * @param S，种子集合
 */
double CalcMargin(Node u, Graph g, double theta, Query gamma, map<int, Node> S)
{
    double res = 0.0;
    
    //首先将网络中所有的边权值修改为给定主题下的权值
    g.changeGraph(gamma);
    
    //从新的图中获取点u
    Node* u_ = new Node(u);
    
    u_ = &g.nodes[u.number];

    u_->MIA->nextNode.clear();
    
    //构建在新图中u的MIA
    Dijkstra(g, *u_,u_->MIA);
    

    //计算MIA模型的上界
    res = hat_delta_p_u(u.MIA);
    u.influence = res - 1;

    
    return res-1;
}


double delta_sigma_v_S_gamma(Node v, map<int, Node> S_i, Query q, double theta, Graph g)
{
    CalcMargin(v, g, theta, q, S_i);
    return 1;
}

double prodChild(Tree* node,map<int, Node> S,Query q)
{
    double ap = 0;
    
	if(findKey(S, node->node->number))
        ap = 1;
    else
    {
        vector<Tree*>::iterator iterator;
        double childAp = 1;
        for (iterator = node->nextNode.begin(); iterator != node->nextNode.end(); iterator++) {

            childAp *=(1-prodChild(*iterator, S,q)*calPP(*((*iterator)->node),*node->node,q));
        }
    }
    
    return ap;
}

/*
	calculate the ap(u|S,r) i.e. equation (4) in paper
 */
double calAP(Node& u, map<int, Node> S, Query &q)
{
    double res = 0.0;
    //if(findKey(S, u.number))
    if (S.size() == 0) 

    {
        res = 1;
    }else{
		if(findKey(S, u.number))
            res = 1;
        else
        {
            res = prodChild(u.MIA, S,q);
        }
    }
    return res;
}


double calPP(Node sourceNode,Node targetNode, Query q)
{
    
    map<int, Edge*>::iterator iter;
    
    for (iter=sourceNode.neighbourEdge.begin(); iter!=sourceNode.neighbourEdge.end(); iter++)
    {
        if (iter->second->sourceNode->number == sourceNode.number&&  iter->second->targetNode->number)
            break;
    }
    double p = 0;
    if (iter != sourceNode.neighbourEdge.end()) {
        p = iter->second->realDistribution[0]*q.topicDistribution[0]+iter->second->realDistribution[1]*q.topicDistribution[1]+iter->second->realDistribution[2]*q.topicDistribution[2];
    }
    return p;
}
/*
	calculate the pp(w,v|r)
 */
double calPP(Edge edge, Query q)
{
 
    double p = 0;
    
     p = edge.realDistribution[0]*q.topicDistribution[0]+edge.realDistribution[1]*q.topicDistribution[1]+edge.realDistribution[2]*q.topicDistribution[2];
    
    return p;
}

/*
	find Node in M
 */
bool findNodeInM(const Node & findNode,  priority_queue<Node> M)
{
    
    while (!M.empty())
    {
        Node u  = M.top();
        M.pop();
        if (findNode.number == u.number)
            return true;
    }
    
    return false;
}

/*
	Adjust M due to new v.influence
 */
void adjustM(Node& oldNode, double new_inf, priority_queue<Node>& M)
{
    Node newNode = oldNode;
    newNode.influence = new_inf;
    priority_queue<Node> M_;
    while (!M.empty()) {
        Node u = M.top();
        M.pop();
        if (oldNode.number == u.number)
        {
            u = newNode;
            M_.push(u);
            return;
        }
        M_.push(u);
    }
    M = M_;
}

/*
	calculate the deta(u|S,r) showed in Line 14 in Algorithm 2
 */
double calDetaUSR(map<int, Node>&V, double theta)
{
    double res = 0.0;
    
	for (map<int, Node>::iterator i=V.begin(); i!=V.end(); i++)  
    {  
		if (i->second.influence >= theta)
            res += i->second.deta_u;
    }  

    return res;
}


/*
 * bestEffort算法入口，输入为一个图G，查询语句Q，以及用户定义的theta,最后一个参数是要选择的上界计算算法
 * @param g 社交网络图
 * @param q 查询语句
 * @param theta 用户自定义阈值
 * @param chooseAlgorithm 用户选择算法
 */
map<int, Node>* bestEffort(Graph g, Query q, double theta, algorithm chooseAlgorithm)
{
    vector<Node> node;
    
    BestEffort bestEffort;
    
    
    //首先进行离线处理
    bestEffortOffline(g, theta, bestEffort,q,chooseAlgorithm);

    //进行在线处理
    map<int, Node>* S = bestEffortOnline(g, q, theta, bestEffort,chooseAlgorithm);
    
    return S;
}
