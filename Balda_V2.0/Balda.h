#pragma once
#include <iostream>
#include "windows.h" //��� �������� ��� ���� �� ���� ������ � ������
#include <ctime> //��� ���������� ������
#include <fstream> // ��� ��������� �����/������
#include <string> // ��������� ���� �����
#include <vector>
#include <iterator> // ������������ ���� ���������
#include <stack>
#include <set>
using namespace std;

enum class ConsoleColor {
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};
struct Points {//
	int player_points = 0;
	//int size = 0;
	//string* pl_words = new string[size];
	vector<string> pl_words;
};

struct AI_Word {
	string word;
	vector<int> coordinates;
};


class Balda abstract {
protected:
	Points f_player, s_player;
	
	set <string> library;
	
	vector <string> used_words;
public:
	Balda() {}
	//������������ ������ ����� � ��������� ���� �������
	void add_to_lib(string word);
	//������������ �������� � ��� � ������ ������
	void load_words();
};

class Interface {
protected:
	const int ROW = 5;//���� ���������� �� ����� ����
	const int COL = 5;
	char **table;
	ConsoleColor background;
	int text;
public:
	Interface();

	void SetColor(int text, ConsoleColor background);
	void show_1menu();
	void show_2menu();
	void load_title();
	void fill_play_table();
	void show_play_field()
};

class PVP_logic : public Balda, public Interface{

public:

};

class VSAI_logic : public Balda, public Interface {
	vector <AI_Word> ai_words;
public:

};