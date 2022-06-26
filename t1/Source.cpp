#include <iostream>
#include <thread>

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
			m[i][j] = ay == i && ax == j ? 'A' : by == i && bx == j ? 'B' : '-';

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

	int n1 = by - ay < 0 ? -1 : 1;
	int n2 = bx - ax < 0 ? -1 : 1;
	while (ay != by) ay += n1, print();
	while (ax != bx) ax += n2, print();
	print();
	return 0;
}