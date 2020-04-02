#pragma once
#include <iostream>
#include "windows.h" //for correct ua language and color changes function in the console
#include <ctime> //for random search
#include <fstream> // for file I / O
#include <string> // template class string
#include <vector>
#include <iterator> // iterator header file
#include <queue>
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
//for counting player points
struct Points {//
	int player_points = 0;
	vector<string> pl_words;
};
//for unfiltered letter combinations
struct temp_AI_Word {
	queue<string> words;
	pair<queue<int>, queue<int>>coordinates;
	pair<vector<int>, vector<int>>pc_moves;
	int max_length = 10;
	int cur_max_len;
};
//for confirmed letter combinations
struct AI_Word {
	vector<string> words;
	pair<vector<int>, vector<int>>letter_coordinates;
	vector<char> letters;
};

class Interface {
protected:
	Points f_player, s_player;
	int ROW = 5;//variables are responsible for the size of the field
	int COL = 5;
	vector<vector<char>>table;

	
public:
	Interface();
	void load_title();
	void fill_play_table();
	void SetColor(int text, ConsoleColor background);
	static void show_1menu();
	void show_2menu();
	
	void show_play_field();
	//check for free cells on the table
	bool checking_free_places();
};

class Main_logic : public Interface {
protected:
	set<string> custom_library;
	vector <string> library;
	string current_word; //the current word collected
	string custom_words_file_name = "custom_words.txt",
		words_file_name = "words.txt";
	vector<int> moves;//the array of cells used during the current turn
	int step_count;//counter moves
	int x, y; //coordinates of active table cell
	int temp_x, temp_y; // temporary variables to remember the cell with the letter inserted
	
public:
	Main_logic();
	char game_menu();
protected:
	//upload a new word to a text file dictionary
	void add_to_lib(string word);
	//download dictionary from txt to binary tree
	void load_words(string file_name);
	//the main method of game
	virtual void game(string f_word);
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


class AI_logic : public Main_logic {
	bool difficulty; //not implemented
	AI_Word ai_words;//for confirmed letter combinations
	temp_AI_Word ai_temp_words;//for unfiltered letter combinations
	vector<vector<char>> matrix; //for forming the adjacency matrix when working with graphs
	int moves_count;//counts the number of movements in the turn
public:
	AI_logic();
	AI_logic(bool difficulty);//not implemented
protected:
	//the main method of game
	void game(string f_word) override;
	//logic of one turn of the AI
	void ai_moving();
	//forming the adjacency matrix for graph depth search algorithm
	void forming_matrix();
	//checking adjacent cells during matrix formation
	bool check_neighbors(int x, int y);
	//find unfiltered combinations of letters using graph depth search algorithm
	void find_words(int x, int y, int new_x, int new_y, string temp_word);
	// filtering combinations of letters by finding words in library
	void filter();
	//select a random word from a finite array of found words
	void choose_word();
	//check the correctness of the transmitted matrix coordinates during the 
	//graph depth search algorithm is working
	int check_next_position(int x, int y, int new_x);
};