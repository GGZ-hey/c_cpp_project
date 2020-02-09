#pragma once
#include<cmath>
#include"../../Stack_cplus/Stack_cplus/Stack.h"
#include"../../Queue_cpls/Queue_cpls/Queue.h"
#include"../../Vector/Vector/Vector.h"

typedef enum{UNDISCOVERED,DISCOVERED,VISITED} VStatus;//顶点状态
typedef enum{UNDETERMINED,TREE,CROSS,FORWARD,BACKWARD} EType;//边在遍历树中所属的类型

template<typename Tv,typename Te>
class Graph {
private:
	void reset() {//所有顶点、边的辅助信息复位
		for (int i = 0;i < n;i++) {
			status(i) = UNDISCOVERED;dTime(i) = fTime(i) = -1;
			parent(i) = -1;priority(i) = INT_MAX;
			for (int j = 0;j < n;j++) {
				if(exists(i,j))
					type(i,j)=UNDETERMINED;
			}
		}
	}
	void BFS(int, int&);//(连通域)广度优先搜索算法
	void DFS(int, int&);//(连通域)深度优先搜索算法
	void BCC(int, int&, Stack<int>&);//(连通域)基于DFS的双连通分量分解算法
	bool TSort(int, int&, Stack<Tv>*);//(连通域)基于DFS的拓扑排序算法
	template<typename PU>void PFS(int, PU);//(连通域)优先级搜索框架
public:
//顶点
	int n=0;//顶点总数
	virtual int insert(Tv const&) = 0;//插入顶点，返回编号
	virtual Tv remove(int) = 0;//删除顶点及其关联边，返回该顶点的信息
	virtual Tv& vertex(int) = 0;//顶点v的数据(该顶点的确存在)
	virtual int inDegree(int) = 0;//顶点v的入度
	virtual int outDegree(int) = 0;//顶点v的出度
	virtual int firstNbr(int) = 0;//顶点v的首个邻接顶点
	virtual int nextNbr(int,int) = 0;//顶点v的(相对于顶点j)下一邻接顶点
	virtual VStatus& status(int) = 0;//顶点v的状态
	virtual int& dTime(int) = 0;//顶点v的时间标签dTime
	virtual int& fTime(int) = 0;//顶点v的时间标签fTime
	virtual int& parent(int) = 0;
	virtual int& priority(int) = 0;//顶点v在遍历树中的优先级数
//边：这里约定，无定向边均统一转化为方向互逆的一对有向边，从而将无向图视作有向图的特例
	int e=0;//边总数
	virtual bool exists(int, int) = 0;//边(v,u)是否存在
	virtual void insert(Te const&, int, int, int) = 0;//在顶点v和u之间插入权重为w的边e
	virtual Te remove(int, int) = 0;//删除顶点v和u之间的边e，返回该边信息
	virtual EType& type(int, int) = 0;//边(v,u)的类型
	virtual Te& edge(int, int) = 0;//边(v,u)的数据(该边确实存在)
	virtual int& weight(int, int) = 0;
//算法
	void bfs(int);
	void dfs(int);
	void bcc(int);
	Stack<Tv>* tSort(int);
	void prim(int);//最小支撑树Prim算法
	void dijkstra(int);//最短路径dijkstra算法
	template<typename PU>void pfs(int, PU);//优先级搜索框架
};

template<typename Tv>struct Vertex {
	Tv data;
	int inDegree, outDegree;
	VStatus status;
	int dTime, fTime;
	int parent;
	int priority;
	Vertex(Tv const& d = (Tv)0) :
		data(d), inDegree(d), outDegree(d), status(UNDISCOVERED),
		dTime(-1), fTime(-1), parent(-1), priority(INT_MAX) {}//暂不考虑权重溢出
};

template<typename Te>struct Edge {
	Te data;int weight;EType type;
	Edge(Te const& d, int w) :data(d), weight(w), type(UNDETERMINED) {}//构造
};

template<typename Tv, typename Te>
class GraphMatrix : public Graph<Tv, Te> {//基于向量，以邻接矩阵形式实现的图
private:
	Vector<Vertex<Tv>> V;//顶点集(向量)
	Vector<Vector<Edge<Te>*>> E;//边集合(邻接矩阵)
public:
	int& n =Graph<Tv,Te>::n;
	int& e = Graph<Tv, Te>::e;
	GraphMatrix() { n = e = 0; }//构造
	~GraphMatrix()//析构
	{
		for (int j = 0;j < n;j++)//所有动态创建的
			for (int k = 0;k < n;k++)//边记录
				delete E[j][k];//逐条删除
	}
	//顶点的基本操作:查询第i个顶点(0<=i<n)
	virtual Tv& vertex(int i) { return V[i].data; }//数据
	virtual int inDegree(int i) { return V[i].inDegree; }//入度
	virtual int outDegree(int i) { return V[i].outDegree; }//出度
	virtual int firstNbr(int i) { return nextNbr(i, n); }//首个邻接顶点
	virtual int nextNbr(int i, int j)
	{
		while ((-1 < j) && (!exists(i, --j)));
		return j;//逆向线性试探
	}
	virtual VStatus& status(int i) { return V[i].status; }
	virtual int& dTime(int i) { return V[i].dTime; }
	virtual int& fTime(int i) { return V[i].fTime; }
	virtual int& parent(int i) { return V[i].parent; }
	virtual int& priority(int i) { return V[i].priority; }
	//顶点的动态操作
	virtual int insert(Tv const& vertex) {//插入顶点，返回编号
		for (int j = 0;j < n;j++)
			E[j].insert(NULL);//各顶点预留一条潜在的关联边
		n++;
		E.insert(Vector<Edge<Te>*>(n, n, (Edge<Te>*)NULL));//创建新顶点对应的边向量
		return V.insert(Vertex<Tv>(vertex));//顶点向量增加一个顶点
	}
	virtual Tv remove(int i) {//删除第i个顶点及其关联边(0<=i<n)
		for (int j = 0;j < n;j++)//所有出边
			if (exists(i, j)) { delete E[i][j];V[j].inDegree--; }
		E.remove(i);n--;//删除第i行
		Tv vBak = vertex(i);V.remove(i);//删除顶点i
		for (int j = 0;j < n;j++)//所有入边
			if (Edge<Te> * e = E[j].remove(i)) {//逐条删除
				delete e;
				V[j].outDegree--;
			}
		return vBak;
	}
	//边的确认操作
	virtual bool exists(int i, int j)
	{
		return (0 <= i) && (i < n) && (0 <= j) && (j < n) && E[i][j] != NULL;
	}
	//边的基本操作：查询顶点i与j之间的联边(0<=i,j<n且exists(i,j))
	virtual EType& type(int i, int j) { return E[i][j]->type; }//边(i,j)的类型
	virtual Te& edge(int i, int j) { return E[i][j]->data; }
	virtual int& weight(int i, int j) { return E[i][j]->weight; }
	//边的动态操作
	virtual void insert(Te const& edge, int w, int i, int j)//插入权重为w额边e=(i,j)
	{
		if (exists(i, j)) return;
		E[i][j] = new Edge<Te>(edge, w);
		e++;
		V[i].outDegree++;
		V[j].inDegree++;
	}
	virtual Te remove(int i, int j)//删除顶点i和j之间的联边(exists(i,j))
	{
		Te eBak = edge(i, j);
		delete E[i][j];
		E[i][j] = NULL;
		e--;
		V[i].outDegree--;
		V[j].inDegree--;
		return eBak;
	}
};

template<typename Tv, typename Te>//广度优先搜索算法BFS算法(全图)
void Graph<Tv, Te>::bfs(int s) {//assert:0<=s<n
	reset();
	int clock = 0;int v = s;//初始化
	do//逐一检查所有顶点
		if (UNDISCOVERED == status(v))//一旦遇到尚未发现的顶点
			BFS(v, clock);//即从该顶点出发启动一次BFS
	while (s != (v = (++v%n)));//按序号检查，故不漏不重
}

template<typename Tv, typename Te>
void Graph<Tv, Te>::BFS(int v, int& clock) {
	Queue<int> Q;//引入辅助队列
	status(v) = DISCOVERED;
	Q.enqueue(v);//初始化起点
	while (!Q.empty()) {
		int v = Q.dequeue();
		dTime(v) = ++clock;
		for (int u = firstNbr(v);-1 < u;u = nextNbr(v, u))
		{
			if (UNDISCOVERED == status(u)) {
				status(u) = DISCOVERED;
				Q.enqueue(u);
				type(v, u) = TREE;parent(u) = v;
			}
			else {
				type(v, u) = CROSS;
			}
		}
		status(v) = VISITED;
	}
}

template <typename Tv, typename Te>
void Graph<Tv, Te>::dfs(int s) {
	reset();
	int clock = 0;int v = s;//初始化
	do
		if (UNDISCOVERED == status(v))
			DFS(v, clock);
	while (s != (v = (++v%n)));
}

template<typename Tv, typename Te>
void Graph<Tv, Te>::DFS(int v, int& clock)
{
	dTime(v) = ++clock;status(v) = DISCOVERED;
	for (int u = firstNbr(v);-1 < u;u = nextNbr(v, u))//枚举v的所有邻居u
		switch (status(u)) {//并视其状态分别处理
		case UNDISCOVERED://u尚未发现，意味着支撑树可在此拓展
			type(v, u) = TREE;parent(u) = v;DFS(u, clock);break;
		case DISCOVERED://u已被发现但尚未访问完毕，应属被后代指向的祖先
			type(v, u) = BACKWARD;break;
		default://u已访问完毕（visited，有向圈），则视承袭关系分为前向边或跨边
			type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;break;
		}
	status(v) = VISITED;fTime(v) = ++clock;//至此，当前顶点v方告访问完毕
}

template<typename Tv, typename Te>
Stack<Tv>* Graph<Tv, Te>::tSort(int s)
{
	reset();
	int clock = 0;int v = s;
	Stack<Tv>* S = new Stack<Tv>;//用栈记录排序顶点
	do {
		if (UNDISCOVERED == status(v))
			if (!TSort(v, clock, S)) {//clock并非必需
				while (!S->empty())
					S->pop();break;
			}
	} while (s != (v = (++v%this->n)));
	return S;//若输入为DAG，则S内各顶点自顶向底排序；否则(不存在拓扑排序)，S空
}

template<typename Tv, typename Te>
void Graph<Tv, Te>::prim(int)
{

}

template<typename Tv, typename Te>
void Graph<Tv, Te>::dijkstra(int)
{
}

template<typename Tv, typename Te>//基于DFS的拓扑排序算法(单趟)
bool Graph<Tv, Te>::TSort(int v, int& clock, Stack<Tv>* S)
{
	dTime(v) = ++clock;status(v) = DISCOVERED;
	for (int u = firstNbr(v);-1 < u;u = nextNbr(v, u))
		switch (status(u)) {
		case UNDISCOVERED:
			parent(u) = v;
			type(v, u) = TREE;
			if (!TSort(u, clock, S))
				return false;
			break;
		case DISCOVERED:
			type(v, u) = BACKWARD;
			return false;
		default://VISITED(digraphs only)
			type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
			break;

		}
	status(v) = VISITED;S->push(vertex(v));//顶点被标记为VISITED时，随即入栈
	return true;//v及其后代可以拓扑排序
}

int min(int a, int b) {
	return a < b ? a : b;
}


template<typename Tv, typename Te> void Graph<Tv, Te>::bcc(int s) {//基于DFS的BCC分解算法
	reset();int clock = 0;int v = s;Stack<int> S;//栈S用以记录已访问的顶点
	do
		if (UNDISCOVERED == status(v)) {//一旦发现未发现的顶点(新连通分量)
			BCC(v, clock, S);//即从该顶点发出启动一次BCC
			S.pop();//遍历返回后，弹出栈中最后一个顶点——当前连通域的起点
		}
	while (s != (v = (++v%n)));
}





#define hca(x) (fTime(x))//利用此处闲置的fTime[]充当hca[]
template<typename Tv, typename Te>//顶点类型、边类型
void Graph<Tv, Te>::BCC(int v, int& clock, Stack<int>& S) {//assert:0<=v<n
	hca(v) = dTime(v) = ++clock;
	status(v) = DISCOVERED;
	S.push(v);//v被发现并入栈
	for (int u = firstNbr;-1 < u;u = nextNbr(v, u))//枚举v的所有邻居u
	{
		switch (status(u)) {//视u的状态分别处理
		case UNDISCOVERED:
			parent(u) = v;
			type(v, u) = TREE;
			BCC(u, clock, S);//从顶点u处深入
			if (hca(u) < dTime(v))//遍历返回后，若发现u(通过后向边)可指向v的真祖先
				hca(v) = min(hca(v), hca(u));//则v亦必如此
			else {//否则，以v为关节点(u以下即是一个BCC，且其中顶点此时正集中于栈S的顶部)
				while (v != S.pop());
				S.push(v);//最后一个顶点（关节点）重新入栈——总计至多两次
			}
			break;
		case DISCOVERED:
			type(v, u) = BACKWARD;//标记（v,u），并按照"越小越高"的准则
			if (u != parent(v))hca(v) = min(hca(v), dTime(u));//更新hca[v]
			break;
		default://VISITED(digraphs only)
			type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
			break;
		}
	}
	status(v) = VISITED;//对v的访问结束
}
#undef hca

template<typename Tv, typename Te>
template<typename PU>
void Graph<Tv, Te>::pfs(int s, PU prioUpdater)//优先级搜索（全图）
{//assert:0<=s<n
	reset();int v = s;//初始化
	do
		if (UNDISCOVERED == status(v))
			PFS(v, prioUpdater);
	while (s != (v = (++v%n)));
}

template<typename Tv, typename Te> template<typename PU>//顶点类型、边类型、优先级更新器
void Graph<Tv, Te>::PFS(int s, PU prioUpdater) {//优先级搜索(单个连通域)
	priority(s) = 0;status(s) = VISITED;parent(s) = -1;//初始化，起点s加至PFS树中
	while (1) {//将下一顶点和边加至PFS树中
		for (int w = firstNbr(s);-1 < w;w = nextNbr(s, w))
			prioUpdater(this, s, w);//更新顶点w的优先级及其父顶点
		for (int shortest = INT_MAX, w = 0;w < n;w++)//寻找优先级最大(优先级数最小)的顶点
			if (UNDISCOVERED == status(w))
				if (shortest > priority(w))
				{
					shortest = priority(w);
					s = w;
				}
		if (VISITED == status(s))break;
		status(s) = VISITED;type(parent(s), s) = TREE;//将s及其父的联边加入遍历树
	}
}//通过定义具体的优先级更新策略prioUpdater，即可实现不同的算法功能

template<typename Tv, typename Te>struct primPU {//针对Prim算法的顶点优先级更新器
	virtual void operator()(Graph<Tv, Te>* g, int uk, int v) {
		if (UNDISCOVERED == g->status(v))//对于uk每一尚未被发现的邻接顶点v
			if (g->priority(v) > g->weight(uk, v)) {//按Prim策略做松弛
				g->priority(v) = g->weight(uk, v);//更新优先级
				g->parent(v) = uk;//更新父节点
			}
	}
};

template<typename Tv, typename Te>struct DijkstraPU {//针对Dijkstra算法的顶点优先级更新器
	virtual void operator()(Graph<Tv, Te>* g, int uk, int v) {
		if (UNDISCOVERED == g->status(v))//对于uk每一尚未被发现的邻接顶点v，按dijkstra策略
			if (g->priority(v) > g->priority(uk) + g->weight(uk, v)) {//做松弛
				g->priority(v) = g->priority(uk) + g->weight(uk, v);//更新优先级
				g->parent(v) = uk;//并同时更新父节点
			}
	}
};


