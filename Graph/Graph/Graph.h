#pragma once
#include<cmath>
#include"../../Stack_cplus/Stack_cplus/Stack.h"
#include"../../Queue_cpls/Queue_cpls/Queue.h"
#include"../../Vector/Vector/Vector.h"

typedef enum{UNDISCOVERED,DISCOVERED,VISITED} VStatus;//����״̬
typedef enum{UNDETERMINED,TREE,CROSS,FORWARD,BACKWARD} EType;//���ڱ�����������������

template<typename Tv,typename Te>
class Graph {
private:
	void reset() {//���ж��㡢�ߵĸ�����Ϣ��λ
		for (int i = 0;i < n;i++) {
			status(i) = UNDISCOVERED;dTime(i) = fTime(i) = -1;
			parent(i) = -1;priority(i) = INT_MAX;
			for (int j = 0;j < n;j++) {
				if(exists(i,j))
					type(i,j)=UNDETERMINED;
			}
		}
	}
	void BFS(int, int&);//(��ͨ��)������������㷨
	void DFS(int, int&);//(��ͨ��)������������㷨
	void BCC(int, int&, Stack<int>&);//(��ͨ��)����DFS��˫��ͨ�����ֽ��㷨
	bool TSort(int, int&, Stack<Tv>*);//(��ͨ��)����DFS�����������㷨
	template<typename PU>void PFS(int, PU);//(��ͨ��)���ȼ��������
public:
//����
	int n=0;//��������
	virtual int insert(Tv const&) = 0;//���붥�㣬���ر��
	virtual Tv remove(int) = 0;//ɾ�����㼰������ߣ����ظö������Ϣ
	virtual Tv& vertex(int) = 0;//����v������(�ö����ȷ����)
	virtual int inDegree(int) = 0;//����v�����
	virtual int outDegree(int) = 0;//����v�ĳ���
	virtual int firstNbr(int) = 0;//����v���׸��ڽӶ���
	virtual int nextNbr(int,int) = 0;//����v��(����ڶ���j)��һ�ڽӶ���
	virtual VStatus& status(int) = 0;//����v��״̬
	virtual int& dTime(int) = 0;//����v��ʱ���ǩdTime
	virtual int& fTime(int) = 0;//����v��ʱ���ǩfTime
	virtual int& parent(int) = 0;
	virtual int& priority(int) = 0;//����v�ڱ������е����ȼ���
//�ߣ�����Լ�����޶���߾�ͳһת��Ϊ�������һ������ߣ��Ӷ�������ͼ��������ͼ������
	int e=0;//������
	virtual bool exists(int, int) = 0;//��(v,u)�Ƿ����
	virtual void insert(Te const&, int, int, int) = 0;//�ڶ���v��u֮�����Ȩ��Ϊw�ı�e
	virtual Te remove(int, int) = 0;//ɾ������v��u֮��ı�e�����ظñ���Ϣ
	virtual EType& type(int, int) = 0;//��(v,u)������
	virtual Te& edge(int, int) = 0;//��(v,u)������(�ñ�ȷʵ����)
	virtual int& weight(int, int) = 0;
//�㷨
	void bfs(int);
	void dfs(int);
	void bcc(int);
	Stack<Tv>* tSort(int);
	void prim(int);//��С֧����Prim�㷨
	void dijkstra(int);//���·��dijkstra�㷨
	template<typename PU>void pfs(int, PU);//���ȼ��������
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
		dTime(-1), fTime(-1), parent(-1), priority(INT_MAX) {}//�ݲ�����Ȩ�����
};

template<typename Te>struct Edge {
	Te data;int weight;EType type;
	Edge(Te const& d, int w) :data(d), weight(w), type(UNDETERMINED) {}//����
};

template<typename Tv, typename Te>
class GraphMatrix : public Graph<Tv, Te> {//�������������ڽӾ�����ʽʵ�ֵ�ͼ
private:
	Vector<Vertex<Tv>> V;//���㼯(����)
	Vector<Vector<Edge<Te>*>> E;//�߼���(�ڽӾ���)
public:
	int& n =Graph<Tv,Te>::n;
	int& e = Graph<Tv, Te>::e;
	GraphMatrix() { n = e = 0; }//����
	~GraphMatrix()//����
	{
		for (int j = 0;j < n;j++)//���ж�̬������
			for (int k = 0;k < n;k++)//�߼�¼
				delete E[j][k];//����ɾ��
	}
	//����Ļ�������:��ѯ��i������(0<=i<n)
	virtual Tv& vertex(int i) { return V[i].data; }//����
	virtual int inDegree(int i) { return V[i].inDegree; }//���
	virtual int outDegree(int i) { return V[i].outDegree; }//����
	virtual int firstNbr(int i) { return nextNbr(i, n); }//�׸��ڽӶ���
	virtual int nextNbr(int i, int j)
	{
		while ((-1 < j) && (!exists(i, --j)));
		return j;//����������̽
	}
	virtual VStatus& status(int i) { return V[i].status; }
	virtual int& dTime(int i) { return V[i].dTime; }
	virtual int& fTime(int i) { return V[i].fTime; }
	virtual int& parent(int i) { return V[i].parent; }
	virtual int& priority(int i) { return V[i].priority; }
	//����Ķ�̬����
	virtual int insert(Tv const& vertex) {//���붥�㣬���ر��
		for (int j = 0;j < n;j++)
			E[j].insert(NULL);//������Ԥ��һ��Ǳ�ڵĹ�����
		n++;
		E.insert(Vector<Edge<Te>*>(n, n, (Edge<Te>*)NULL));//�����¶����Ӧ�ı�����
		return V.insert(Vertex<Tv>(vertex));//������������һ������
	}
	virtual Tv remove(int i) {//ɾ����i�����㼰�������(0<=i<n)
		for (int j = 0;j < n;j++)//���г���
			if (exists(i, j)) { delete E[i][j];V[j].inDegree--; }
		E.remove(i);n--;//ɾ����i��
		Tv vBak = vertex(i);V.remove(i);//ɾ������i
		for (int j = 0;j < n;j++)//�������
			if (Edge<Te> * e = E[j].remove(i)) {//����ɾ��
				delete e;
				V[j].outDegree--;
			}
		return vBak;
	}
	//�ߵ�ȷ�ϲ���
	virtual bool exists(int i, int j)
	{
		return (0 <= i) && (i < n) && (0 <= j) && (j < n) && E[i][j] != NULL;
	}
	//�ߵĻ�����������ѯ����i��j֮�������(0<=i,j<n��exists(i,j))
	virtual EType& type(int i, int j) { return E[i][j]->type; }//��(i,j)������
	virtual Te& edge(int i, int j) { return E[i][j]->data; }
	virtual int& weight(int i, int j) { return E[i][j]->weight; }
	//�ߵĶ�̬����
	virtual void insert(Te const& edge, int w, int i, int j)//����Ȩ��Ϊw���e=(i,j)
	{
		if (exists(i, j)) return;
		E[i][j] = new Edge<Te>(edge, w);
		e++;
		V[i].outDegree++;
		V[j].inDegree++;
	}
	virtual Te remove(int i, int j)//ɾ������i��j֮�������(exists(i,j))
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

template<typename Tv, typename Te>//������������㷨BFS�㷨(ȫͼ)
void Graph<Tv, Te>::bfs(int s) {//assert:0<=s<n
	reset();
	int clock = 0;int v = s;//��ʼ��
	do//��һ������ж���
		if (UNDISCOVERED == status(v))//һ��������δ���ֵĶ���
			BFS(v, clock);//���Ӹö����������һ��BFS
	while (s != (v = (++v%n)));//����ż�飬�ʲ�©����
}

template<typename Tv, typename Te>
void Graph<Tv, Te>::BFS(int v, int& clock) {
	Queue<int> Q;//���븨������
	status(v) = DISCOVERED;
	Q.enqueue(v);//��ʼ�����
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
	int clock = 0;int v = s;//��ʼ��
	do
		if (UNDISCOVERED == status(v))
			DFS(v, clock);
	while (s != (v = (++v%n)));
}

template<typename Tv, typename Te>
void Graph<Tv, Te>::DFS(int v, int& clock)
{
	dTime(v) = ++clock;status(v) = DISCOVERED;
	for (int u = firstNbr(v);-1 < u;u = nextNbr(v, u))//ö��v�������ھ�u
		switch (status(u)) {//������״̬�ֱ���
		case UNDISCOVERED://u��δ���֣���ζ��֧�������ڴ���չ
			type(v, u) = TREE;parent(u) = v;DFS(u, clock);break;
		case DISCOVERED://u�ѱ����ֵ���δ������ϣ�Ӧ�������ָ�������
			type(v, u) = BACKWARD;break;
		default://u�ѷ�����ϣ�visited������Ȧ�������ӳ�Ϯ��ϵ��Ϊǰ��߻���
			type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;break;
		}
	status(v) = VISITED;fTime(v) = ++clock;//���ˣ���ǰ����v����������
}

template<typename Tv, typename Te>
Stack<Tv>* Graph<Tv, Te>::tSort(int s)
{
	reset();
	int clock = 0;int v = s;
	Stack<Tv>* S = new Stack<Tv>;//��ջ��¼���򶥵�
	do {
		if (UNDISCOVERED == status(v))
			if (!TSort(v, clock, S)) {//clock���Ǳ���
				while (!S->empty())
					S->pop();break;
			}
	} while (s != (v = (++v%this->n)));
	return S;//������ΪDAG����S�ڸ������Զ�������򣻷���(��������������)��S��
}

template<typename Tv, typename Te>
void Graph<Tv, Te>::prim(int)
{

}

template<typename Tv, typename Te>
void Graph<Tv, Te>::dijkstra(int)
{
}

template<typename Tv, typename Te>//����DFS�����������㷨(����)
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
	status(v) = VISITED;S->push(vertex(v));//���㱻���ΪVISITEDʱ���漴��ջ
	return true;//v������������������
}

int min(int a, int b) {
	return a < b ? a : b;
}


template<typename Tv, typename Te> void Graph<Tv, Te>::bcc(int s) {//����DFS��BCC�ֽ��㷨
	reset();int clock = 0;int v = s;Stack<int> S;//ջS���Լ�¼�ѷ��ʵĶ���
	do
		if (UNDISCOVERED == status(v)) {//һ������δ���ֵĶ���(����ͨ����)
			BCC(v, clock, S);//���Ӹö��㷢������һ��BCC
			S.pop();//�������غ󣬵���ջ�����һ�����㡪����ǰ��ͨ������
		}
	while (s != (v = (++v%n)));
}





#define hca(x) (fTime(x))//���ô˴����õ�fTime[]�䵱hca[]
template<typename Tv, typename Te>//�������͡�������
void Graph<Tv, Te>::BCC(int v, int& clock, Stack<int>& S) {//assert:0<=v<n
	hca(v) = dTime(v) = ++clock;
	status(v) = DISCOVERED;
	S.push(v);//v�����ֲ���ջ
	for (int u = firstNbr;-1 < u;u = nextNbr(v, u))//ö��v�������ھ�u
	{
		switch (status(u)) {//��u��״̬�ֱ���
		case UNDISCOVERED:
			parent(u) = v;
			type(v, u) = TREE;
			BCC(u, clock, S);//�Ӷ���u������
			if (hca(u) < dTime(v))//�������غ�������u(ͨ�������)��ָ��v��������
				hca(v) = min(hca(v), hca(u));//��v������
			else {//������vΪ�ؽڵ�(u���¼���һ��BCC�������ж����ʱ��������ջS�Ķ���)
				while (v != S.pop());
				S.push(v);//���һ�����㣨�ؽڵ㣩������ջ�����ܼ���������
			}
			break;
		case DISCOVERED:
			type(v, u) = BACKWARD;//��ǣ�v,u����������"ԽСԽ��"��׼��
			if (u != parent(v))hca(v) = min(hca(v), dTime(u));//����hca[v]
			break;
		default://VISITED(digraphs only)
			type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
			break;
		}
	}
	status(v) = VISITED;//��v�ķ��ʽ���
}
#undef hca

template<typename Tv, typename Te>
template<typename PU>
void Graph<Tv, Te>::pfs(int s, PU prioUpdater)//���ȼ�������ȫͼ��
{//assert:0<=s<n
	reset();int v = s;//��ʼ��
	do
		if (UNDISCOVERED == status(v))
			PFS(v, prioUpdater);
	while (s != (v = (++v%n)));
}

template<typename Tv, typename Te> template<typename PU>//�������͡������͡����ȼ�������
void Graph<Tv, Te>::PFS(int s, PU prioUpdater) {//���ȼ�����(������ͨ��)
	priority(s) = 0;status(s) = VISITED;parent(s) = -1;//��ʼ�������s����PFS����
	while (1) {//����һ����ͱ߼���PFS����
		for (int w = firstNbr(s);-1 < w;w = nextNbr(s, w))
			prioUpdater(this, s, w);//���¶���w�����ȼ����丸����
		for (int shortest = INT_MAX, w = 0;w < n;w++)//Ѱ�����ȼ����(���ȼ�����С)�Ķ���
			if (UNDISCOVERED == status(w))
				if (shortest > priority(w))
				{
					shortest = priority(w);
					s = w;
				}
		if (VISITED == status(s))break;
		status(s) = VISITED;type(parent(s), s) = TREE;//��s���丸�����߼��������
	}
}//ͨ�������������ȼ����²���prioUpdater������ʵ�ֲ�ͬ���㷨����

template<typename Tv, typename Te>struct primPU {//���Prim�㷨�Ķ������ȼ�������
	virtual void operator()(Graph<Tv, Te>* g, int uk, int v) {
		if (UNDISCOVERED == g->status(v))//����ukÿһ��δ�����ֵ��ڽӶ���v
			if (g->priority(v) > g->weight(uk, v)) {//��Prim�������ɳ�
				g->priority(v) = g->weight(uk, v);//�������ȼ�
				g->parent(v) = uk;//���¸��ڵ�
			}
	}
};

template<typename Tv, typename Te>struct DijkstraPU {//���Dijkstra�㷨�Ķ������ȼ�������
	virtual void operator()(Graph<Tv, Te>* g, int uk, int v) {
		if (UNDISCOVERED == g->status(v))//����ukÿһ��δ�����ֵ��ڽӶ���v����dijkstra����
			if (g->priority(v) > g->priority(uk) + g->weight(uk, v)) {//���ɳ�
				g->priority(v) = g->priority(uk) + g->weight(uk, v);//�������ȼ�
				g->parent(v) = uk;//��ͬʱ���¸��ڵ�
			}
	}
};


