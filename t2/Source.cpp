#include <iostream>
#include <thread>
#include "bfs.h"

using namespace std;

#define ROWS 20
#define COLUMNS 40

int main() {
	short ax, ay, bx, by;
	cout << "A redak: ", cin >> ay;
	cout << "A stupac: ", cin >> ax;
	cout << "B redak: ", cin >> by;
	cout << "B stupac: ", cin >> bx;
	--ax, --ay, --bx, --by;

	char m[ROWS][COLUMNS];
	for (short i = 0; i < ROWS; ++i)
		for (short j = 0; j < COLUMNS; ++j)
			m[i][j] = ay == i && ax == j ? 'A' : by == i && bx == j ? 'B' : (
				i < ROWS / 2 && j == COLUMNS / 2 - 1) ? '*' : '-';

	auto print = [&]() {
		cout << "\033[2J\033[1;1H"; // system("cls");  
		m[ay][ax] = 'x';
		for (short i = 0; i < ROWS; ++i) {
			for (short j = 0; j < COLUMNS; ++j) cout << m[i][j];
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