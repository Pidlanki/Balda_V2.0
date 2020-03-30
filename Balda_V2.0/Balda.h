#pragma once
#include <iostream>
#include "windows.h" //for correct ua language and color changes function in the console
#include <ctime> //for random search
#include <fstream> // for file I / O
#include <string> // template class string
#include <vector>
#include <iterator> // iterator header file
#include <stack>
#include <set> //binary tree for custom words
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
	int ROW = 5;//variables are responsible for the size of the field
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
	//check for free cells on the table
	bool checking_free_places();
};

class Main_logic : public Interface {
protected:
	bool difficulty;
	set<string> custom_library;
	vector <string> library;
	string current_word; //the current word collected
	string custom_words_file_name = "custom_words.txt",
		words_file_name = "words.txt";
	vector <string> used_words;
	//the array of cells used during the current turn
	vector<int> moves;
	int step_count;//counter moves
	int x, y; //coordinates of active table cell
	int temp_x, temp_y; // temporary variables to remember the cell with the letter inserted
	
public:
	Main_logic();
	//upload a new word to a text file dictionary
	void add_to_lib(string word);
	//download dictionary from txt to binary tree
	void load_words(string file_name);
	char game_menu();
	//the main method of game
	void game(string f_word);
	//logic of one turn of the player
	void moving();
	//the process of moving to one cell in one of 4 directions
	bool make_move(int x, int y, bool& is_new_lat_used);
	//the process of entering the first letter
	void make_first_move(bool& is_new_lat_used);
	//end-of-turn logic
	bool end_turn(bool& is_new_lat_used);
	//check the correctness of the input coordinates
	bool check_pos();
	//check for cell reuse in one turn
	bool ch_past_pos(int x, int y);
	//inserts the first word
	void first_word_initialization(string f_word);
	//Scoring
	void counting_points();
	//check on the winner
	void checks_for_winner();
};


//class AI_logic : public Balda {
//	vector <AI_Word> ai_words;
//public:
//
//};