#include<iostream>
#include<vector>
#include<string>
#include<set>
#include<queue>
#include<functional>
using namespace std;


struct Vertex
{
	int num;	  //每个结点当前的序号，与matrix中序号保持一致
	string name;  //每个结点可以有自己的名字

	//在遍历图的时候来标记该节点是否被访问过
	int flag;

	//在kruscal中用来标记节点当前所在集合编号
	int setNum;

	//在prim中用来表示当前结点的前驱，当前结点最MST中结点最小权值
	int pre;
	int w;

	//dijkstra算法中表示前驱和到源节点的路径长度
	int dPre;
	int dW;
};

struct Edge
{
	Vertex a, b;
	int weight;
};

struct cmp
{
	bool operator ()(Edge &a, Edge &b)
	{
		return a.weight > b.weight;
	}
};

//采用邻接矩阵的方式保存图
struct G
{
	int n;
	vector<Vertex> vertex;
	priority_queue<Edge, vector<Edge>, cmp> edge;   //采用自定义的最小优先队列来保存边集
	vector<vector<int>> matrix;
	void init()
	{
		cout << "input the nums of node：";
		cin >> n;
		cout << "input the relationship like: ( num1 num2 weight )\n";
		vertex.resize(n);
		int i;
		for (i = 0; i < n; i++)
		{
			vertex[i].num = i;
			vertex[i].flag = 0;
			vertex[i].setNum = i;
			vertex[i].pre = -1;
			vertex[i].w = 1000;
			vertex[i].dPre = -1;
			vertex[i].dW = 1000;
			//vertex[i].name = "xxx";  //目前就先不给结点起名字了，直接用数字表示它的名字
		}
		matrix.resize(n, vector<int>(n, 0));
		int a, b;
		while(1)
		{
			cin >> a >> b;
			if (a == 0) break;
			cin >> matrix[--a][--b];
			matrix[b][a] = matrix[a][b];		//这里别忘了，表示这是一个无向图！！！！！！
			Edge e;
			e.a = vertex[a];
			e.b = vertex[b];
			e.weight = matrix[a][b];
			edge.push(e);
		}
	}
	void reset()
	{
		int i, j;
		for (i = 0; i < n; i++)
		{
			vertex[i].flag = 0;
			vertex[i].setNum = i;
		}

		while (!edge.empty())
			edge.pop();
		for (i = 0; i < n; i++)
			for (j = i + 1; j < n; j++)
				if (matrix[i][j] > 0)
				{
					Edge e;
					e.a = vertex[i];
					e.b = vertex[j];
					e.weight = matrix[i][j];
					edge.push(e);
				}
	}
};

//input the nums of node：7
//input the relationship like : (num1 num2 weight)
//1 3 1
//1 4 1
//1 6 1
//3 4 1
//2 3 1
//5 7 1
//6 7 1
//0 0 0





//<-----------------------------------------------------------------------------------------------------------------------------------
//图的深度优先遍历
//时间复杂度 ：O(E+v)
void dfs_visit(G &g, int cur)
{
	int j;
	cout << g.vertex[cur].num+1<<"  ";
	g.vertex[cur].flag = 1;
	for (j = 0; j < g.n; j++)
		if (j != cur && g.matrix[cur][j] > 0 && g.vertex[j].flag == 0)
			dfs_visit(g, j);
}
void dfs(G &g)
{
	int i;
	for (i = 0; i < g.n; i++)
		if (g.vertex[i].flag == 0)
			dfs_visit(g, i);
}
//图的广度优先遍历
//时间复杂度 ：O(E+v)
void bfs(G g)
{
	queue<int> que;   //所有集合保存的是 结点序号，通过结点序号可以得到对应的 vertex[i] 中所有结点相关信息
	que.push(0);
	g.vertex[0].flag = 1;
	int i,j;
	while (!que.empty())
	{
		i = que.front();
		cout << g.vertex[i].num+1 << "  ";
		que.pop();
		for (j = 0; j < g.n; j++)
			if (j != i && g.matrix[i][j] > 0 && g.vertex[j].flag == 0)
			{
				que.push(j);
				g.vertex[j].flag = 1;		//这里千万注意：结点在被放进队列中时就表示已经被访问了，应该在放入队列后标记为已访问！！！！
			}
	}
}
void testDfs_Bfs()
{
	G g;
	g.init();
	cout << "\n\ndfs：";
	dfs(g);

	cout << "\n\n\nbfs: ";
	g.reset();
	bfs(g);

	cout << "\n\n\n";
}
//-----------------------------------------------------------------------------------------------------------------------------------










//<-----------------------------------------------------------------------------------------------------------------------------------
//最小生成树：基于贪心策略，其核心为寻找安全边
//	方法1：kruskal， 开始以每个结点为一个集合，然后开始通过最小边去对集合进行合并，当只剩下一个集合时，就生成了最小生成树
//  方法2：prim， 从一开始就只维持一个集合，该集合内的节点之间的边都是最小二叉树需要的边


//kruskal 只需要操作边集和点集，最终最小生成树是以边集表示的
//时间复杂度 ：O(Elgv)
void kruskal(G g)
{
	//先为每个结点来创建一个set，用vector来保存这些集合
	vector<set<int>> vec(g.n);
	vector<Edge> res;
	int i, j, k;
	for (i = 0; i < g.n; i++)
	{
		vec[i].insert(i);
		//g.vertex[i].setNum = i;  //每个结点当前所处的集合编号, 在init函数中已经初始化过了
	}

	//每次都从优先队列中取出最小边，判断改边对应的两个结点是否位于不同集合，是则将边加入 res， 并融合集合
	//直到只剩下一个集合有元素时终止，也即是 res的size等于 g.n-1时；
	while (res.size() != g.n - 1)
	{
		Edge e = g.edge.top();
		int v1 = e.a.num, v2 = e.b.num;
		int s1 = g.vertex[v1].setNum, s2 = g.vertex[v2].setNum;
		g.edge.pop();				//这里要想清楚，通过边集找到对应的节点，然后所有的修改操作都是在 vertex[i] 点集中完成的！！！！！
										// 边集和点集之间 num 号是一直不变的，可以通过num让两者产生联系
		if (s1!=s2)
		{
			res.push_back(e);

			//集合融合,小的集合融到大的集合中
			if (s1 < s2)
			{
				s1 = s1 + s2;
				s2 = s1 - s2;
				s1 = s1 - s2;
			}
			for (auto num : vec[s2])
			{
				g.vertex[num].setNum = s1;
				vec[s1].insert(num);
			}
			vec[s2].clear();
		}
	}
	cout << "\n\nkruskal最小生成树为：";
	for (auto e : res)
		cout << "(" << e.a.num + 1 << ", " << e.b.num + 1 << ")  ";

}

//prim 需要在结点中声明 其前驱和当前最小权重值 ，然后需要一个最小优先队列每次取最小权重的结点，去更新其它相连结点的前驱和权重
struct cmp2
{
	bool operator ()(Vertex* &a, Vertex* &b)
	{
		//最小优先队列
		return a->w > b->w;  
	}
};
//时间复杂度 ：O(Elgv)
void prim(G g)
{
	priority_queue < Vertex*, vector<Vertex*>, cmp2> que;
	priority_queue < Vertex*, vector<Vertex*>, cmp2> que2;

	int i, j;
	//这里让两个没有相连接的节点的权重为 1000
	for (i = 0; i < g.n; i++)
		for (j = 0; j < g.n; j++)
			if (g.matrix[i][j] == 0)
				g.matrix[i][j] = 1000;   

	g.vertex[0].w = 0;
	//注意这里的 auto &v 一定要加上&得到引用，否则得不到地址
	for (auto &v : g.vertex)		
		que.push(&v);
	
	while (!que.empty())
	{
		Vertex* v = que.top(), *tmp;
		que.pop();
		int n = que.size();
		while (n--)
		{
			tmp = que.top();
			que.pop();
			if (g.matrix[v->num][tmp->num] < tmp->w)
			{
				tmp->pre = v->num;
				tmp->w = g.matrix[v->num][tmp->num];
			}
			//这里由于优先队列不支持修改，所以只能用两个优先队列实现权重修改后重新变成一个新的优先队列
			que2.push(tmp);				
		}
		que.swap(que2);			
	}
	cout << "\n\nprim最小生成树为：";
	for_each(g.vertex.begin(), g.vertex.end(), [](Vertex &v) { if(v.pre!=-1) cout << "(" << v.num + 1 << ", " << v.pre + 1 << ")  "; });
}

//输入的例子：
/*
1 2 2
1 3 4
1 4 1
2 4 3
2 5 10
3 4 2
3 6 5
4 5 7
4 6 8
4 7 4
5 7 6
6 7 1
0 0 0
*/
void testMst()
{
	G g;
	g.init();
	
	//需要一个堆集合vector<set<int>> vec(g.n);  和 最小优先队列的边集合 priority_queue<Edge, vector<Edge>, cmp> edge;
	//结点属性中有一个 setNum 表示当前结点属于哪个集合
	//集合融合就是让一个集合所有点insert到另一个集合，然后清空该集合
	//然后结果由一个vector<Edge> res; 来每次保存有效边，
	//终止条件 res.size() 其值为 g.n-1    ！！！！！！！！！！！！！！！！
	kruskal(g);


	//用到两个最小优先队列，注意优先队列保存的是点集中每个元素的指针！！！！ 和 一个结点集合
	//这里由于优先队列不支持修改，所以只能用两个优先队列实现权重修改后重新变成一个新的优先队列
	//结点属性中有pre前驱和w权重属性，且初始时只有vertex[0].w=0,其它结点权重都为1000无穷大
	//结果由结点最终保存的pre来得到最小生成树
	//终止条件 优先队列 que（）里面保存的是还未加入到MST的节点，所以当 que.size() 为0时表示终止  ！！！！！！！！！！！！！！！！
	prim(g);


	cout << "\n\n\n";
}
//-----------------------------------------------------------------------------------------------------------------------------------










//<-----------------------------------------------------------------------------------------------------------------------------------
/*
最短路径:
	1. 贝尔曼福特算法：对所有的边进行 g.n-1 次松弛操作，适用于一般情况
	2. 利用拓扑排序的顺序进行松弛操作，要求有向无环图
	3. Dijkstra算法：要求所有边权值为非负值，跟prim算法思想类似，同样维持一个集合，同样结点中有 前驱属性和到源节点s的路径长度
	4. 弗洛伊德算法：所有节点对最短路径
*/
struct Dvertex
{
	int num;
	string name;
	int dPre;
	int dW;
};
struct Dg
{
	int n;
	int isDirect;  //是否是有向图 1是，0不是
	vector<Dvertex> vertex;
	vector<vector<int>> matrix;
	void init()
	{
		cout << "input the nums of node：";
		cin >> n;
		cout << "input the isDirect(1.yes, 0.no)：";
		cin >> isDirect;
		cout << "input the relationship like: ( num1 num2 weight )\n";
		vertex.resize(n);
		int i;
		for (i = 0; i < n; i++)
		{
			vertex[i].num = i;
			vertex[i].dPre = -1;
			vertex[i].dW = 1000;
			//目前就先不给结点起名字了，直接用数字表示它的名字
		}
		matrix.resize(n, vector<int>(n, 1000));
		int a, b;
		while (1)
		{
			cin >> a >> b;
			if (a == 0) break;
			cin >> matrix[--a][--b];
			if(!isDirect)
				matrix[b][a] = matrix[a][b];		//是否是无向图
		}
	}
	void reset()
	{
		int i;
		for (i = 0; i < n; i++)
		{
			vertex[i].dPre = -1;
			vertex[i].dW = 1000;
		}
	}
};
struct cmp3
{
	bool operator ()(Dvertex *&a, Dvertex *&b)
	{
		return a->dW > b->dW;
	}
};
void myPrint(Dg g, int cur, int s, int *sum)
{
	if (cur == s)
		cout << s + 1;
	else if (cur == -1)
		return;
	else
	{
		myPrint(g, g.vertex[cur].dPre, s, sum);
		cout << "------("<<g.matrix[g.vertex[cur].dPre][cur]<<")----->"<<cur + 1;
		*sum = (*sum) + g.matrix[g.vertex[cur].dPre][cur];
	}
}
//时间复杂度 ：O(vlgv+E)
void dijkstra(Dg g, int s)
{
	priority_queue<Dvertex*, vector<Dvertex*>, cmp3> que;
	priority_queue<Dvertex*, vector<Dvertex*>,cmp3> que2;
	g.vertex[s].dW = 0;
	for (auto &v : g.vertex)
		que.push(&v);
	Dvertex *vt,*tmp;
	while (!que.empty())
	{
		vt = que.top();
		que.pop();
		while (!que.empty())
		{
			tmp = que.top();
			que.pop();
			if (vt->dW + g.matrix[vt->num][tmp->num] < tmp->dW)
			{
				tmp->dPre = vt->num;
				tmp->dW = vt->dW + g.matrix[vt->num][tmp->num];
			}
			que2.push(tmp);
		}
		que.swap(que2);
	}
	cout << "\n\nDijkstra最短路径( s = " << s + 1 << " ) : \n";
	int i, j,sum;
	for(i=0;i<g.n;i++)
		if (i != s)
		{
			if (g.vertex[i].dPre == -1)
				cout << "  从" << s + 1 << "出发没有路径到达 " << i + 1 << "\n";
			else
			{
				sum = 0;
				myPrint(g, i, s, &sum);
				cout <<" ["<<sum<<"]"<<endl;
			}
		}
	cout << "\n\n\n";
}

//输入的图的例子
/*
input the nums of node：7
input the isDirect(1.yes, 0.no)：1
input the relationship like: ( num1 num2 weight )
1 2 2
1 4 1
2 4 3
2 5 10
3 1 4
3 6 5
4 3 2
4 5 2
4 6 8
4 7 4
5 7 6
7 6 1
0 0 0
*/
void testDijkstra()
{
	Dg g;
	g.init();
	for (int i = 0; i < g.n; i++)
	{
		dijkstra(g, i);
		g.reset();
	}
}







int main()
{
	//testDfs_Bfs();

	//testMst();

	testDijkstra();

	cout << "\n\n\n";
	return 0;
}
