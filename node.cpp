#include <bits/stdc++.h>
#include "node.h"
#include "utils.h"
using namespace std;
const int max_num = 1000;
node peers_array[max_num];
edge peers_edges[max_num][max_num];
int num;
double prob_choosing_edge;
void init(int n)
{
	srand(time(0));
	num = n;
	prob_choosing_edge = 3 * log(num) / num;
	block *genesis = create_block(NULL, num);
	for (int i = 0; i < num; i++)
	{
		double random_0to1 = get_uniform_0to1();
		peers_array[i].speed = random_0to1 < 0.5;
		peers_array[i].root = genesis;
		peers_array[i].balance = 0;
	}
}
void create_connected_graph()
{
	int cnt = 0;
	for (int i = 0; i < num; i++)
	{
		for (int j = i + 1; j < num; j++)
		{
			double random_0to1 = get_uniform_0to1();
			if (random_0to1 > prob_choosing_edge)
			{
				peers_edges[i][j].present = 0;
				peers_edges[j][i].present = 0;
			}
			else
			{
				peers_edges[i][j].present = 1;
				peers_edges[j][i] = peers_edges[i][j];
			}
		}
	}
}
int visited[max_num];
void dfs(int root)
{
	for (int i = 0; i < num; i++)
	{
		if (!visited[i] && peers_edges[root][i].present)
		{
			visited[i] = 1;
			dfs(i);
		}
	}
}
bool is_connected()
{
	for (int i = 0; i < num; i++)
	{
		visited[i] = 0;
	}
	visited[0] = 1;
	dfs(0);
	for (int i = 0; i < num; i++)
	{
		if (!visited[i])
		{
			return false;
		}
	}
	return true;
}
int get_balance(int x)
{
	return peers_array[x].balance;
}