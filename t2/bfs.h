#pragma once

// https://www.geeksforgeeks.org/shortest-path-from-a-source-cell-to-a-destination-cell-of-a-binary-matrix-through-cells-consisting-only-of-1s/
// https://clementmihailescu.github.io/Pathfinding-Visualizer/

#include <queue>
#include <stack>

using namespace std;

#define ROWS 20
#define COLUMNS 40

struct Point {
	int x, y;
};

struct Node {
	Point pt;
	int dist;
};

bool isValid(int row, int col) {
	return (row >= 0) && (col >= 0) && (row < ROWS) && (col < COLUMNS);
}

int dRow[] = { -1, 0, 0, 1 };
int dCol[] = { 0, -1, 1, 0 };

stack<Point> pathMoves(char m[][COLUMNS], Point src, Point dest) {
	stack<Point> pathmoves;
	int d[ROWS][COLUMNS];
	memset(d, -1, sizeof d);
	d[src.x][src.y] = 0;
	bool visited[ROWS][COLUMNS];
	memset(visited, false, sizeof visited);
	visited[src.x][src.y] = true;
	queue<Node> q;
	q.push({ src, 0 });

	while (!q.empty()) {
		Node curr = q.front();
		Point pt = curr.pt;
		if (pt.x == dest.x && pt.y == dest.y) {
			int xx = pt.x, yy = pt.y;
			int dist = curr.dist;
			d[pt.x][pt.y] = dist;
			while (xx != src.x || yy != src.y) {
				if (xx > 0 && d[xx - 1][yy] == dist - 1)
					pathmoves.push({ 0, 1 }), xx--;
				if (xx < ROWS - 1 && d[xx + 1][yy] == dist - 1)
					pathmoves.push({ 0, -1 }), xx++;
				if (yy > 0 && d[xx][yy - 1] == dist - 1)
					pathmoves.push({ 1, 0 }), yy--;
				if (yy < COLUMNS - 1 && d[xx][yy + 1] == dist - 1)
					pathmoves.push({ -1, 0 }), yy++;
				dist--;
			}
		}
		q.pop();
		for (int i = 0; i < 4; i++) {
			int row = pt.x + dRow[i];
			int col = pt.y + dCol[i];
			if (isValid(row, col) && !visited[row][col] && m[row][col] != '*') {
				visited[row][col] = true;
				q.push({ { row, col }, curr.dist + 1 });
				d[row][col] = curr.dist + 1;
			}
		}
	}
	return pathmoves;
}