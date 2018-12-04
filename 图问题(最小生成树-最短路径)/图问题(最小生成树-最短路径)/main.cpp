#include<iostream>
#include<vector>
#include<string>
#include<set>
#include<queue>
#include<functional>
using namespace std;


struct Vertex
{
	int num;	  //ÿ����㵱ǰ����ţ���matrix����ű���һ��
	string name;  //ÿ�����������Լ�������

	//�ڱ���ͼ��ʱ������Ǹýڵ��Ƿ񱻷��ʹ�
	int flag;

	//��kruscal��������ǽڵ㵱ǰ���ڼ��ϱ��
	int setNum;

	//��prim��������ʾ��ǰ����ǰ������ǰ�����MST�н����СȨֵ
	int pre;
	int w;

	//dijkstra�㷨�б�ʾǰ���͵�Դ�ڵ��·������
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

//�����ڽӾ���ķ�ʽ����ͼ
struct G
{
	int n;
	vector<Vertex> vertex;
	priority_queue<Edge, vector<Edge>, cmp> edge;   //�����Զ������С���ȶ���������߼�
	vector<vector<int>> matrix;
	void init()
	{
		cout << "input the nums of node��";
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
			//vertex[i].name = "xxx";  //Ŀǰ���Ȳ�������������ˣ�ֱ�������ֱ�ʾ��������
		}
		matrix.resize(n, vector<int>(n, 0));
		int a, b;
		while(1)
		{
			cin >> a >> b;
			if (a == 0) break;
			cin >> matrix[--a][--b];
			matrix[b][a] = matrix[a][b];		//��������ˣ���ʾ����һ������ͼ������������
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

//input the nums of node��7
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
//ͼ��������ȱ���
//ʱ�临�Ӷ� ��O(E+v)
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
//ͼ�Ĺ�����ȱ���
//ʱ�临�Ӷ� ��O(E+v)
void bfs(G g)
{
	queue<int> que;   //���м��ϱ������ �����ţ�ͨ�������ſ��Եõ���Ӧ�� vertex[i] �����н�������Ϣ
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
				g.vertex[j].flag = 1;		//����ǧ��ע�⣺����ڱ��Ž�������ʱ�ͱ�ʾ�Ѿ��������ˣ�Ӧ���ڷ�����к���Ϊ�ѷ��ʣ�������
			}
	}
}
void testDfs_Bfs()
{
	G g;
	g.init();
	cout << "\n\ndfs��";
	dfs(g);

	cout << "\n\n\nbfs: ";
	g.reset();
	bfs(g);

	cout << "\n\n\n";
}
//-----------------------------------------------------------------------------------------------------------------------------------










//<-----------------------------------------------------------------------------------------------------------------------------------
//��С������������̰�Ĳ��ԣ������ΪѰ�Ұ�ȫ��
//	����1��kruskal�� ��ʼ��ÿ�����Ϊһ�����ϣ�Ȼ��ʼͨ����С��ȥ�Լ��Ͻ��кϲ�����ֻʣ��һ������ʱ������������С������
//  ����2��prim�� ��һ��ʼ��ֻά��һ�����ϣ��ü����ڵĽڵ�֮��ı߶�����С��������Ҫ�ı�


//kruskal ֻ��Ҫ�����߼��͵㼯��������С���������Ա߼���ʾ��
//ʱ�临�Ӷ� ��O(Elgv)
void kruskal(G g)
{
	//��Ϊÿ�����������һ��set����vector��������Щ����
	vector<set<int>> vec(g.n);
	vector<Edge> res;
	int i, j, k;
	for (i = 0; i < g.n; i++)
	{
		vec[i].insert(i);
		//g.vertex[i].setNum = i;  //ÿ����㵱ǰ�����ļ��ϱ��, ��init�������Ѿ���ʼ������
	}

	//ÿ�ζ������ȶ�����ȡ����С�ߣ��жϸı߶�Ӧ����������Ƿ�λ�ڲ�ͬ���ϣ����򽫱߼��� res�� ���ںϼ���
	//ֱ��ֻʣ��һ��������Ԫ��ʱ��ֹ��Ҳ���� res��size���� g.n-1ʱ��
	while (res.size() != g.n - 1)
	{
		Edge e = g.edge.top();
		int v1 = e.a.num, v2 = e.b.num;
		int s1 = g.vertex[v1].setNum, s2 = g.vertex[v2].setNum;
		g.edge.pop();				//����Ҫ�������ͨ���߼��ҵ���Ӧ�Ľڵ㣬Ȼ�����е��޸Ĳ��������� vertex[i] �㼯����ɵģ���������
										// �߼��͵㼯֮�� num ����һֱ����ģ�����ͨ��num�����߲�����ϵ
		if (s1!=s2)
		{
			res.push_back(e);

			//�����ں�,С�ļ����ڵ���ļ�����
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
	cout << "\n\nkruskal��С������Ϊ��";
	for (auto e : res)
		cout << "(" << e.a.num + 1 << ", " << e.b.num + 1 << ")  ";

}

//prim ��Ҫ�ڽ�������� ��ǰ���͵�ǰ��СȨ��ֵ ��Ȼ����Ҫһ����С���ȶ���ÿ��ȡ��СȨ�صĽ�㣬ȥ����������������ǰ����Ȩ��
struct cmp2
{
	bool operator ()(Vertex* &a, Vertex* &b)
	{
		//��С���ȶ���
		return a->w > b->w;  
	}
};
//ʱ�临�Ӷ� ��O(Elgv)
void prim(G g)
{
	priority_queue < Vertex*, vector<Vertex*>, cmp2> que;
	priority_queue < Vertex*, vector<Vertex*>, cmp2> que2;

	int i, j;
	//����������û�������ӵĽڵ��Ȩ��Ϊ 1000
	for (i = 0; i < g.n; i++)
		for (j = 0; j < g.n; j++)
			if (g.matrix[i][j] == 0)
				g.matrix[i][j] = 1000;   

	g.vertex[0].w = 0;
	//ע������� auto &v һ��Ҫ����&�õ����ã�����ò�����ַ
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
			//�����������ȶ��в�֧���޸ģ�����ֻ�����������ȶ���ʵ��Ȩ���޸ĺ����±��һ���µ����ȶ���
			que2.push(tmp);				
		}
		que.swap(que2);			
	}
	cout << "\n\nprim��С������Ϊ��";
	for_each(g.vertex.begin(), g.vertex.end(), [](Vertex &v) { if(v.pre!=-1) cout << "(" << v.num + 1 << ", " << v.pre + 1 << ")  "; });
}

//��������ӣ�
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
	
	//��Ҫһ���Ѽ���vector<set<int>> vec(g.n);  �� ��С���ȶ��еı߼��� priority_queue<Edge, vector<Edge>, cmp> edge;
	//�����������һ�� setNum ��ʾ��ǰ��������ĸ�����
	//�����ںϾ�����һ���������е�insert����һ�����ϣ�Ȼ����ոü���
	//Ȼ������һ��vector<Edge> res; ��ÿ�α�����Ч�ߣ�
	//��ֹ���� res.size() ��ֵΪ g.n-1    ��������������������������������
	kruskal(g);


	//�õ�������С���ȶ��У�ע�����ȶ��б�����ǵ㼯��ÿ��Ԫ�ص�ָ�룡������ �� һ����㼯��
	//�����������ȶ��в�֧���޸ģ�����ֻ�����������ȶ���ʵ��Ȩ���޸ĺ����±��һ���µ����ȶ���
	//�����������preǰ����wȨ�����ԣ��ҳ�ʼʱֻ��vertex[0].w=0,�������Ȩ�ض�Ϊ1000�����
	//����ɽ�����ձ����pre���õ���С������
	//��ֹ���� ���ȶ��� que�������汣����ǻ�δ���뵽MST�Ľڵ㣬���Ե� que.size() Ϊ0ʱ��ʾ��ֹ  ��������������������������������
	prim(g);


	cout << "\n\n\n";
}
//-----------------------------------------------------------------------------------------------------------------------------------










//<-----------------------------------------------------------------------------------------------------------------------------------
/*
���·��:
	1. �����������㷨�������еı߽��� g.n-1 ���ɳڲ�����������һ�����
	2. �������������˳������ɳڲ�����Ҫ�������޻�ͼ
	3. Dijkstra�㷨��Ҫ�����б�ȨֵΪ�Ǹ�ֵ����prim�㷨˼�����ƣ�ͬ��ά��һ�����ϣ�ͬ��������� ǰ�����Ժ͵�Դ�ڵ�s��·������
	4. ���������㷨�����нڵ�����·��
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
	int isDirect;  //�Ƿ�������ͼ 1�ǣ�0����
	vector<Dvertex> vertex;
	vector<vector<int>> matrix;
	void init()
	{
		cout << "input the nums of node��";
		cin >> n;
		cout << "input the isDirect(1.yes, 0.no)��";
		cin >> isDirect;
		cout << "input the relationship like: ( num1 num2 weight )\n";
		vertex.resize(n);
		int i;
		for (i = 0; i < n; i++)
		{
			vertex[i].num = i;
			vertex[i].dPre = -1;
			vertex[i].dW = 1000;
			//Ŀǰ���Ȳ�������������ˣ�ֱ�������ֱ�ʾ��������
		}
		matrix.resize(n, vector<int>(n, 1000));
		int a, b;
		while (1)
		{
			cin >> a >> b;
			if (a == 0) break;
			cin >> matrix[--a][--b];
			if(!isDirect)
				matrix[b][a] = matrix[a][b];		//�Ƿ�������ͼ
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
//ʱ�临�Ӷ� ��O(vlgv+E)
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
	cout << "\n\nDijkstra���·��( s = " << s + 1 << " ) : \n";
	int i, j,sum;
	for(i=0;i<g.n;i++)
		if (i != s)
		{
			if (g.vertex[i].dPre == -1)
				cout << "  ��" << s + 1 << "����û��·������ " << i + 1 << "\n";
			else
			{
				sum = 0;
				myPrint(g, i, s, &sum);
				cout <<" ["<<sum<<"]"<<endl;
			}
		}
	cout << "\n\n\n";
}

//�����ͼ������
/*
input the nums of node��7
input the isDirect(1.yes, 0.no)��1
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
