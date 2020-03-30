#include "Balda.h"

int main() {
	srand(time(NULL));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	char ch;
	string f_word;

	Main_logic Balda;
	
	do {
		Balda.show_1menu();
		cin >> ch;
		switch (ch) {
		case 'a':
			ch = Balda.game_menu();
			break;
		case 'b':

			break;
		default:
			break;
		}
	} while (ch != 'n');
	return 0;
}