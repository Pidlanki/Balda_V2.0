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
	int ROW = 5;//���� ���������� �� ����� ����
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
	//�������� �� ���� ������� �� ����
	bool checking_free_places();
};

class Main_logic : public Interface {
protected:
	bool difficulty;
	set<string> custom_library;
	vector <string> library;
	string current_word; //������� ������ �����
	string custom_words_file_name = "custom_words.txt",
		words_file_name = "words.txt";
	vector <string> used_words;
	//����� ������������ ������� �� ��� ��������� ����
	vector<int> moves;
	int step_count;//�������� ����
	int x, y; //���������� ������� ������� �����
	int temp_x, temp_y; // �������� ���� ��� �����'���������� ������� � ��������� ������
	
public:
	Main_logic();
	//������������ ������ ����� � ��������� ���� �������
	void add_to_lib(string word);
	//������������ �������� � ��� � ������ ������
	void load_words(string file_name);
	char game_menu();
	//�������� ����� ���
	void game(string f_word);
	//����� ������ ���� ������
	void moving();
	//������ ���������� �� ���� ������� � ���� � 4 ����
	bool make_move(int x, int y, bool& is_new_lat_used);
	//������ ����� ����� �����
	void make_first_move(bool& is_new_lat_used);
	//����� ���� ����
	bool end_turn(bool& is_new_lat_used);
	//�������� ���������� ����� ���������
	bool check_pos();
	//�������� �� �������� ������������ ������� � ������ ����
	bool ch_past_pos(int x, int y);
	//�������� ����� �����
	
	void first_word_initialization(string f_word);
	//����������� ����
	void counting_points();
	//�������� �� ���������
	void checks_for_winner();
};


//class AI_logic : public Balda {
//	vector <AI_Word> ai_words;
//public:
//
//};