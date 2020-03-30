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
#include <array>
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

	void load_title();
	void fill_play_table();
public:
	Interface();

	void SetColor(int text, ConsoleColor background);
	void show_1menu();
	void show_2menu();
	
	void show_play_field();
	//перевірка на вільні клітитки на столі
	bool checking_free_places();
};

class Main_logic : public Interface {
protected:
	bool difficulty;
	set<string> custom_library;
	vector <string> library;
	string current_word; //поточне зібране слово
	string custom_words_file_name = "custom_words.txt",
		words_file_name = "words.txt";
	vector <string> used_words;
	//масив використаних клітинок під час поточного ходу
	vector<int> moves;
	int step_count;//лічильник ходів
	int x, y; //координати активної клітинки стола
	int temp_x, temp_y; // тимчасові змінні для запам'ятовування клітинки з всталеною буквою
	
public:
	Main_logic();
	//завантаження нового слова у текстовий файл словник
	void add_to_lib(string word);
	//завантаження словника з тхт в бінарне дерево
	void load_words(string file_name);
	char game_menu();
	//основний метод гри
	void game(string f_word);
	//логіка одного ходу людини
	void moving();
	//процес переміщення на одну клітинку в один з 4 боків
	bool make_move(int x, int y, bool& is_new_lat_used);
	//процес вводу першої букви
	void make_first_move(bool& is_new_lat_used);
	//логіка кінця ходу
	bool end_turn(bool& is_new_lat_used);
	//перевірка коректності вводу координат
	bool check_pos();
	//перевірка на повторне використання клітинки в одному ходу
	bool ch_past_pos(int x, int y);
	//вставляє перше слово
	
	void first_word_initialization(string f_word);
	//нарахування очок
	void counting_points();
	//перевірка на переможця
	void checks_for_winner();
};


//class AI_logic : public Balda {
//	vector <AI_Word> ai_words;
//public:
//
//};