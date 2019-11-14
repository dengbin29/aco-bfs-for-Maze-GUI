#include<iostream>
#include<stack>
#include<bitset>
using namespace std;
//������
struct Point
{
	int x;
	int y;
};
//��ͼ��
template<int A, int B>
class Map
{
public:
	int(*p)[B];//1��ʾΪ�ϰ�����0��ʾ�÷����ͨ
	bitset<4>(*around)[B];//��¼ÿһ�����������ĸ������Ŀ�ѡ���
	int row;//����
	int col;//����
	Map()
	{
		p = new int[A][B];
		around = new bitset<4>[A][B];
	}
	Map(Map<A, B> & B1)
	{
		p = new int[A][B];
		around = new bitset<4>[A][B];
		row = B1.row;
		col = B1.col;
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				p[i][j] = B1.p[i][j];
				around[i][j] = B1.around[i][j];
			}
		}
	}
	Map<A, B> & operator=(Map<A, B> & B1)
	{
		row = B1.row;
		col = B1.col;
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				this->p[i][j] = B1.p[i][j];
				around[i][j] = B1.around[i][j];
			}
		}
		return *this;
	}
};

//start��ʼ�㣬 end��ֹ��
template<int A, int B>
bool FindPath(Map<A, B> & map, Point & start, Point & end)
{
	const int N1 = A;
	const int N2 = B;

	const int M = 10;//ÿһ�������ϵĸ���
	const int RcMax = 20;//��������
	const int IN = 1;//��Ϣ�صĳ�ʼ��

	double add[N1][N2];//ÿһ�ε���Ϣ����������
	double phe[N1][N2];//ÿһ��·���ϵ���Ϣ��
	double MAX = 0x7fffffff;

	double alphe, betra, rout, Q;//alphe��Ϣ�ص�Ӱ�����ӣ�betra·�߾����Ӱ�����ӣ�rout��Ϣ�صı��ֶȣ�Q���ڼ���ÿֻ��������·�����µ���Ϣ������
	double bestSolution = MAX;//��̾���
	stack<Point> Beststackpath;//����·��

	//��ʼ��������������Ϣ����
	alphe = betra = 2;
	rout = 0.7;
	Q = 10;

	//�ȸ�ͼ����Χ�����ϰ�
	for (int i = 0; i < map.col; i++)
	{
		map.p[0][i] = map.p[map.row - 1][i] = 1;
	}
	for (int i = 0; i < map.row; i++)
	{
		map.p[i][0] = map.p[i][map.col - 1] = 1;
	}
	//��ʼ��ͼ��ÿһ����������ܷ��ʱ�ʾλ��0��ʾ�ɷ���
	//��ʼ����Ϣ������
	for (int i = 0; i < N1; i++)
	{
		for (int j = 0; j < N2; j++)
		{
			phe[i][j] = IN;
			map.around[i][j].reset();//4������ȫ����Ϊ��ѡ
		}
	}

	//���ڷ���ѡ���ƫ��������   ����˳ʱ��ķ���
	Point offset[4];
	offset[0].x = 0; offset[0].y = 1;//����
	offset[1].x = 1; offset[1].y = 0;//����
	offset[2].x = 0; offset[2].y = -1;//����
	offset[3].x = -1; offset[3].y = 0;//����

	//ÿ��Mֻ���ϣ�ÿһ�ֽ�����Ž���ȫ����Ϣ�ظ���
	stack<Point> stackpath[M];
	//�����ϰ���ͼ
	Map<A, B> Ini_map[M];
	//��¼ÿһֻ���ϵĵ�ǰλ��
	Point Allposition[M];

	int s = 0;
	while (s < RcMax)//һ��RcMax��
	{

		//�����ÿһֻ���ϵ�·�ߴ洢ջ
		for (int i = 0; i < M; i++)
		{
			while (!stackpath[i].empty())
			{
				stackpath[i].pop();
			}
		}
		for (int i = 0; i < M; i++)
		{
			Ini_map[i] = map;
			//������ʼ��Ϊ�ϰ���
			Ini_map[i].p[start.x][start.y] = 1;
			//�����ջ
			stackpath[i].push(start);
			//��ʼ��ÿһֻ���ϵĵ�ǰλ��
			Allposition[i] = start;
		}

		//����Mֻ����ѭ��
		for (int j = 0; j < M; j++)
		{
			cout << "��" << j << "ֻ����" << endl;
			while (((Allposition[j].x) != (end.x) || (Allposition[j].y) != (end.y)))
			{
				cout << "<" << Allposition[j].x << "," << Allposition[j].y << ">" << endl;
				//ѡ����һ��
				double psum = 0;
				for (int op = 0; op < 4; op++)
				{
					//������һ�����ܵ�����
					int x = Allposition[j].x + offset[op].x;
					int y = Allposition[j].y + offset[op].y;

					if ((Ini_map[j].around[Allposition[j].x][Allposition[j].y])[op] == 0 && Ini_map[j].p[x][y] != 1)
					{
						psum += pow(phe[x][y], alphe) * pow((10.0 / stackpath[j].size()), betra);
					}
				}
				//�ж��Ƿ���ѡ��
				//���ҵ�����һ��
				if (psum != 0)
				{
					double drand = (double)(rand()) / (RAND_MAX + 1);
					double pro = 0;
					int re;
					int x, y;
					for (re = 0; re < 4; re++)
					{
						//������һ�����ܵ�����
						x = Allposition[j].x + offset[re].x;
						y = Allposition[j].y + offset[re].y;
						if ((Ini_map[j].around[Allposition[j].x][Allposition[j].y])[re] == 0 && Ini_map[j].p[x][y] != 1)
						{
							pro += (pow(phe[x][y], alphe) * pow((10.0 / stackpath[j].size()), betra)) / psum;
							if (pro >= drand)
							{
								break;
							}
						}
					}

					//��ջ
					Allposition[j].x = x;
					Allposition[j].y = y;
					stackpath[j].push(Allposition[j]);
					//�����ϰ�
					Ini_map[j].p[Allposition[j].x][Allposition[j].y] = 1;

				}
				else//û�ҵ�����һ��
				{
					//�����һ������ջ
					stackpath[j].pop();
					//������ջʱ���õ��ϰ�
					Ini_map[j].p[Allposition[j].x][Allposition[j].y] = 0;
					if (stackpath[j].empty())
					{
						return false;
						//cout << "ʧ��" << endl;
					}
					//���û��ݺ��Allposition
					if (Allposition[j].x == stackpath[j].top().x)
					{
						if ((Allposition[j].y - stackpath[j].top().y) == 1)//����
						{
							(Ini_map[j].around[stackpath[j].top().x][stackpath[j].top().y])[0] = 1;//��Ǹ÷����ѷ���
						}
						if ((Allposition[j].y - stackpath[j].top().y) == -1)//����
						{
							(Ini_map[j].around[stackpath[j].top().x][stackpath[j].top().y])[2] = 1;//��Ǹ÷����ѷ���
						}
					}
					if (Allposition[j].y == stackpath[j].top().y)
					{

						if ((Allposition[j].x - stackpath[j].top().x) == 1)//����
						{
							(Ini_map[j].around[stackpath[j].top().x][stackpath[j].top().y])[1] = 1;//��Ǹ÷����ѷ���
						}
						if ((Allposition[j].x - stackpath[j].top().x) == -1)//����
						{
							(Ini_map[j].around[stackpath[j].top().x][stackpath[j].top().y])[3] = 1;//��Ǹ÷����ѷ���
						}
					}
					Allposition[j].x = stackpath[j].top().x;
					Allposition[j].y = stackpath[j].top().y;
				}

			}
		}

		//��������·��
		double solution = 0;
		for (int i = 0; i < M; i++)
		{
			solution = 0;
			solution = stackpath[i].size();
			if (solution < bestSolution)
			{
				Beststackpath = stackpath[i];
				bestSolution = solution;
			}
		}
		//����ÿһֻ��������ÿһ��·�������µ���Ϣ������
		//��ʼ����Ϣ����������
		for (int i = 0; i < N1; i++)
		{
			for (int j = 0; j < N2; j++)
			{
				add[i][j] = 0;
			}
		}

		for (int i = 0; i < M; i++)
		{
			//�����ÿֻ���ϵ�·�ߵ��ܾ���solu
			double solu = 0;
			solu = stackpath[i].size();
			double d = Q / solu;
			while (!stackpath[i].empty())
			{
				add[stackpath[i].top().x][stackpath[i].top().y] += d;
				stackpath[i].pop();
			}
		}
		//������Ϣ��
		for (int i = 0; i < N1; i++)
		{
			for (int j = 0; j < N2; j++)
			{
				phe[i][j] = phe[i][j] * rout + add[i][j];
				//Ϊ��Ϣ������һ������ֵ������ֵ
				if (phe[i][j] < 0.0001)
				{
					phe[i][j] = 0.0001;
				}
				if (phe[i][j] > 20)
				{
					phe[i][j] = 20;
				}
			}
		}

		s++;
	}//��

	//�ҵ�·���������stackpath
	cout << "�ҵ�����·����" << endl;
	cout << "���·�߳���Ϊ�� ��" << Beststackpath.size() << "������" << endl;
	while (!Beststackpath.empty())
	{
		cout << "<" << Beststackpath.top().x << "," << Beststackpath.top().y << ">" << endl;
		Beststackpath.pop();
	}

	return true;
}

int main()
{
	//�����Թ�
	Map<10, 10> map;
	map.col = map.row = 10;
	int p[10][10];
	for (int i = 0; i < 10; i++)//��ʼ���Թ�
	{
		for (int j = 0; j < 10; j++)
		{
			p[i][j] = 0;
		}
	}
	//Ϊ�Թ������ϰ�
	p[1][3] = 1; p[1][7] = 1; p[2][3] = 1; p[2][7] = 1;
	p[3][5] = 1; p[3][6] = 0; p[4][2] = 1; p[4][3] = 1;
	p[4][4] = 1; p[5][4] = 1; p[6][2] = 1; p[6][6] = 1;
	p[7][2] = 1; p[7][3] = 1; p[7][4] = 1; p[7][6] = 1;
	p[8][1] = 1;
	map.p = p;
	Point start, end;
	start.x = start.y = 1;
	end.x = 8, end.y = 8;
	if (!FindPath<10, 10>(map, start, end))
	{
		cout << "���Թ��޽⣡" << endl;
	}
	getchar();
}