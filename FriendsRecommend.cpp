/* Friend Recommends
INPUT: 
<Number of Nodes> <Number of Edges>
<Edge_1> <Edge_2> --- connected edge pairs

OUTPUT:
Rankwise friend recommendation
*/


#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<vector<int> > graph;
int nNodes;

void printList(vector<int> list) {
	cout << "[ ";
	for (int i =0 ; i < list.size(); ++i)
		cout << list[i] << ", ";
	cout << "]";
}

vector<int> sortWithRank(vector<int> list) {
	vector<int> indexes(list.size()); // store indexes
	for (int i = 0; i < indexes.size(); ++i) {
		indexes[i] = i;
	}

	for (int i = 0; i < list.size()-1; ++i) {
		for (int j = i+1; j < list.size(); ++j) {
			if (list[i] < list[j]) {
				int temp = list[j];
				list[j] = list[i];
				list[i] = temp; // swap
				temp = indexes[j];
				indexes[j] = indexes[i];
				indexes[i] = temp;
			}
		}
	}
	int cnt = 0;
	while(list[cnt] != 0)
		cnt++;
	indexes.resize(cnt);
	return indexes;
}

vector<int> getFriends(int start, int level) {
	int curLevel = 0;
	int curLevelMemberCount = 0;
	int nextLevelMemberCount = 0;
	vector<int> foundFriendsRank(nNodes);
	vector<int> visited(nNodes);
	queue<int> q;

	q.push(start);
	curLevelMemberCount = 1;

	while (!q.empty() && curLevel <= level) {
		int curr = q.front();
		q.pop();
		visited[curr] = true;
		if (curLevelMemberCount == 0) {
			curLevelMemberCount = nextLevelMemberCount;
			nextLevelMemberCount = 0;
			curLevel++;
		}
		curLevelMemberCount--;
		for (int i =0 ; i < graph[curr].size(); ++i) {
			++nextLevelMemberCount;
			if (! visited[graph[curr][i]]) {
				q.push(graph[curr][i]);
				if (curLevel == level-1)
					foundFriendsRank[graph[curr][i]]++;
			}
		}
	}
	return foundFriendsRank;
}

int main() {
	int nEdge;
	cin >> nNodes >> nEdge;

	graph.resize(nNodes);

	int x, y;
	for (int  i= 0; i < nEdge; ++i) {
		cin >> x >> y;
		graph[x].push_back(y);
		graph[y].push_back(x);
	}

	vector<int> list = getFriends(0, 1);
	
	vector<int> result = sortWithRank(list);
	printList(result);
}

/* SAMPLE INPUT:
10 12
0 1
0 2
0 3
0 4
1 5
1 7
2 5
2 6
3 5
3 8
4 7
4 9
*/
