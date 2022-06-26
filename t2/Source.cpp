#include <iostream>
#include <thread>
#include "bfs.h"

using namespace std;

#define ROWS 20
#define COLUMNS 40

int main() {
	int ax, ay, bx, by;
	cout << "A redak: ", cin >> ay;
	cout << "A stupac: ", cin >> ax;
	cout << "B redak: ", cin >> by;
	cout << "B stupac: ", cin >> bx;
	--ax, --ay, --bx, --by;

	char m[ROWS][COLUMNS];
	for (int i = 0; i < ROWS; ++i)
		for (int j = 0; j < COLUMNS; ++j)
			m[i][j] = (i < ROWS / 2 && j == COLUMNS / 2 - 1) ? '*' : '-';
	m[ay][ax] = 'A', m[by][bx] = 'B';


	auto print = [&]() {
		cout << "\033[2J\033[1;1H"; // system("cls");  
		m[ay][ax] = 'x';
		for (int i = 0; i < ROWS; ++i) {
			for (int j = 0; j < COLUMNS; ++j) cout << m[i][j];
			cout << endl;
		}
		this_thread::sleep_for(100ms);
		m[ay][ax] = '-';
	};

	auto pathmoves = pathMoves(m, { ay, ax }, { by, bx });
	while (!pathmoves.empty()) {
		auto p = pathmoves.top();
		ay += p.first, ax += p.second, pathmoves.pop(), print();
	}
	print();
	return 0;
}