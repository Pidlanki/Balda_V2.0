#include "Balda.h"



Interface::Interface() {
	vector<vector<char>>table(ROW, vector<char>(COL));
	load_title();
	fill_play_table();
}

void Interface::SetColor(int text, ConsoleColor background) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

void Interface::show_1menu() {
	cout << "������ �����:\n"
		<< "a. 2 ������    b. ����� ����'�����\n>>";
}

void Interface::show_2menu() {
	cout << "� ���, ���� ����� ����� �������� ����� ������� ����� �� ����� �������� ���\n������ ����� ��������� ����'����:\n"
		<< "a. ������    b. �������(�� ��������)	c. ������(�� ��������)\n>> ";
}

void Interface::load_title() {
	ifstream fin;
	string buff;
	fin.open("title.txt");
	if (!fin.is_open()) {
		cout << "file can't be open\n";
		exit(EXIT_FAILURE);
	}
	for (int i = 0; fin.good(); i++) {
		getline(fin, buff);
		for (int i = 0; buff[i]; i++) {
			if (buff[i] == '*') {
				SetColor(LightGreen, Black);
				cout << buff[i];
			}
			else {
				SetColor(Blue, Black);
				cout << buff[i];
			}
		}
		cout << endl;
		SetColor(LightGreen, Black);
	}
	fin.close();
}

void Interface::fill_play_table() {
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			table[i][j] = '-';
		}
	}
}

void Interface::show_play_field() {
	system("cls");
	load_title();
	cout << "\t\t\t\t   0 1 2 3 4\n";
	for (int i = 0; i < ROW; i++) {
		SetColor(LightGreen, Black);
		cout << "\t\t\t\t" << i << ": ";
		for (int j = 0; j < COL; j++) {
			if (table[i][j] != '-') SetColor(Black, LightBlue);
			else if (table[i][j] == '-') SetColor(LightBlue, LightBlue);
			cout << table[i][j] << " ";
		}
		cout << endl;
	}
	SetColor(Blue, Black);
	cout << "����� 1-�� ������: ";
	for (int i = 0; i < f_player.pl_words.size(); i++) {
		cout << f_player.pl_words[i] << ", ";
	}
	cout << "\b\b." << endl;
	cout << "����: " << f_player.player_points << endl;
	cout << "����� 2-�� ������: ";
	for (int i = 0; i < s_player.pl_words.size(); i++) {
		cout << s_player.pl_words[i] << ", ";
	}
	cout << "\b\b." << endl;
	cout << "����: " << s_player.player_points << endl;
	cout << endl;
}

bool Interface::checking_free_places() {
	return false;
}