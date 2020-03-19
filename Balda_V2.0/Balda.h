#pragma once
#include <iostream>
#include "windows.h" //для коректної укр мови та зміни кольрів у консолі
#include <ctime> //для рандомного пошуку
#include <fstream> // для файлового ввода/вивода
#include <string> // Шаблонний клас стрінг
#include <vector>
#include <iterator> // заголовочний файл ітераторів
#include <stack>
#include <set>
using namespace std;

enum ConsoleColor {
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

class Interface {
protected:
	Points f_player, s_player;
	int ROW = 5;//змінні відповідальні за розмір поля
	int COL = 5;
	vector<vector<char>>table;
	ConsoleColor background;
	int text;
public:
	Interface();

	void SetColor(int text, ConsoleColor background);
	void show_1menu();
	void show_2menu();
	void load_title();
	void fill_play_table();
	void show_play_field();
	//перевірка на вільні клітитки на столі
	bool checking_free_places();
};

//class Balda : public Interface {
//protected:
//	
//	
//	set <string> library;
//	
//	vector <string> used_words;
//public:
//	Balda() {}
//	//завантаження нового слова у текстовий файл словник
//	void add_to_lib(string word);
//	//завантаження словника з тхт в бінарне дерево
//	void load_words();
//	void game(string f_word);
//};
//
//
//
//class Player_logic : public Balda{
//
//public:
//	//перевірка коректності вводу координат
//	bool check_pos();
//	
//};
//
//class AI_logic : public Balda {
//	vector <AI_Word> ai_words;
//public:
//
//};