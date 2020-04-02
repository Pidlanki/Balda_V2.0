#include "Balda.h"

int main() {
	srand(time(NULL));

	char ch;
	string f_word;
	Interface inter;
	inter.load_title();
	Main_logic Balda;
	AI_logic vs_ai;
	do {
		Interface::show_1menu();
		cin >> ch;
		switch (ch) {
		case 'a':
			ch = Balda.game_menu();
			break;
		case 'b':
			ch = vs_ai.game_menu();
			break;
		default:
			break;
		}
	} while (ch != 'n');
	return 0;
}