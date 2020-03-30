#include "Balda.h"



Interface::Interface() {
	load_title();
	fill_play_table();
}

void Interface::SetColor(int text, ConsoleColor background) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

void Interface::show_1menu() {
	cout << "Select a mode:\n"
		<< "a. 2 players    b. VS computer\n>>";
}

void Interface::show_2menu() {
	cout << "Select the AI level:\n"
		<< "a. standart    b. hard\n>> ";
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
		table.push_back(vector<char>());
		for (int j = 0; j < COL; j++) {
			table[i].push_back('-');
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
	cout << "1st player words: ";
	for (int i = 0; i < f_player.pl_words.size(); i++) {
		cout << f_player.pl_words[i] << ", ";
	}
	cout << "\b\b." << endl;
	cout << "Points: " << f_player.player_points << endl;
	cout << "2nd player words: ";
	for (int i = 0; i < s_player.pl_words.size(); i++) {
		cout << s_player.pl_words[i] << ", ";
	}
	cout << "\b\b." << endl;
	cout << "Points: " << s_player.player_points << endl;
	cout << endl;
}

bool Interface::checking_free_places() {
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (table[i][j] == '-') return 1;	
		}
	}
	return 0;
}

Main_logic::Main_logic(): step_count(0), x(0), y(0), temp_x(0), temp_y(0), Interface() {
	load_words(custom_words_file_name);
	load_words(words_file_name);
}

void Main_logic::add_to_lib(string word) {
	ofstream fout;
	string buff;
	fout.open(custom_words_file_name, ofstream::app);
	if (!fout.is_open()) {
		cout << "file can't be open\n";
		exit(EXIT_FAILURE);
	}
	fout << word << endl;
	fout.close();
}

void Main_logic::load_words(string file_name) {
	
	ifstream fin;
	string buff;
	fin.open(file_name);
	if (!fin.is_open()) {
		cout << "file can't be open\n";
		exit(EXIT_FAILURE);
	}
	if (file_name == "words.txt") {
		for (int i = 0; fin.good(); i++) {
			fin >> buff;
			library.push_back(buff);
		}
	}
	else {
		for (int i = 0; fin.good(); i++) {
			fin >> buff;
			custom_library.insert(buff);
		}
	}
	fin.close();
}

char Main_logic::game_menu() {
	char ch = 'y';
	string f_word;
	bool loop_end = 0;
	cout << "Enter the first five-letter word, or press \"r\" to select a random word\n>>";
	do {
		do {
			if (ch == 'n') cout << "Please re-enter the first word (it must contain exactly " << COL << " leters)\n>>";
			cin >> f_word;
			/*if (f_word.size() != 5 && f_word != "r")
				cout << "Введіть слово яке містить 5 букв, або літеру \"r\"\n>>";*/
		} while (f_word.size() != 5 && f_word != "r");
		//vector<string>::iterator r = find(library.begin(), library.end(), f_word);
		auto temp_f_word = find(library.begin(), library.end(), f_word);
		auto custom_f_word_temp = custom_library.find(current_word);
		if (f_word != "r" && temp_f_word == library.end() && custom_f_word_temp == custom_library.end()) {
			cout << "The word \"" << f_word << "\" is not in the dictionary, want to add it to the dictionary?\n(y/n)>> ";
			cin >> ch;
			if (ch == 'y') { add_to_lib(f_word); loop_end = 1; }
			continue;
		}
		loop_end = 1;
	} while (!loop_end);
	
	game(f_word);
	cout << "Want to play again? \n(y/n)>> ";
	cin >> ch;
	return ch;
}

void Main_logic::game(string f_word) {
	first_word_initialization(f_word);
	do {
		current_word.clear();
		//show_arr(table);
		show_play_field();
		//cout << endl;
		step_count++;
		SetColor(Red, Black);
		(step_count % 2) ? (cout << "The 1st player turn:\n") : (cout << "The 2nd player turn:\n");
		SetColor(Blue, Black);
		moving();
		counting_points();
	} while (checking_free_places());
	checks_for_winner();
}

void Main_logic::moving() {
	//string word;
	char move, letter;
	int count = 0;
	bool is_new_lat_used = 0;
	//vector<int> stack_moves;

	do {
		if (count == 0) {
			cout << "Enter the coordinates of the original cell using the space bar\n>> ";
			do {
				cin >> x >> y;
				if (check_pos())
					cout << "Invalid coordinates, enter the coordinates of the cell next to another letter to form a word\n>> ";
			} while (check_pos());
		}
		//чи не занята клітинка
		if (!count) {
			make_first_move(is_new_lat_used);
			count++;
		}
		cout << "Next move\n>> ";
		cin >> move;
		switch (move)//процес переміщення по дошці
		{
		case 'w':
			if (make_move(x - 1, y, is_new_lat_used)) {
				count++;
				x--;
			}
			else cout << "Invalid coordinates, or this cell is already in use. Try again!\n";
			break;
		case 'd':
			if (make_move(x, y + 1, is_new_lat_used)) {
				count++;
				y++;
			}
			else cout << "Invalid coordinates, or this cell is already in use. Try again!\n";
			
			break;
		case 's':
			if (make_move(x + 1, y, is_new_lat_used)) {
				count++;
				x++;
			}
			else cout << "Invalid coordinates, or this cell is already in use. Try again!\n";
			break;
		case 'a':
			if (make_move(x, y - 1, is_new_lat_used)) {
				count++;
				y--;
			}		
			else cout << "Invalid coordinates, or this cell is already in use. Try again!\n";
			break;
		case 'Q':
			if (end_turn(is_new_lat_used)) {
				count = 0;
				moves.clear();
				return;
			} 
			break;
		default:
			break;
		}
	} while (true);
}

bool Main_logic::make_move(int x, int y, bool& is_new_lat_used) {
	char letter;
	if (table[x][y] != '-' && x >= 0 && !ch_past_pos(x, y)) {
		current_word += table[x][y];
		cout << current_word << endl;
		moves.insert(moves.end(), x);
		moves.insert(moves.end(), y);
		return true;
	}
	else if (table[x][y] == '-' && x >= 0 && !is_new_lat_used) {
		cout << "Enter a letter\n>> ";
		cin >> letter;
		current_word += letter;
		table[x][y] = letter;
		cout << current_word << endl;
		temp_x = x;
		temp_y = y;
		is_new_lat_used++;
		moves.insert(moves.end(), x);
		moves.insert(moves.end(), y);
		return true;
	}
	else return false;
}

void Main_logic::make_first_move(bool& is_new_lat_used) {
	char letter;
	if (table[x][y] == '-') {
		cout << "Enter the first letter\n>> ";
		cin >> letter;
		current_word += letter;
		table[x][y] = letter;
		temp_x = x;
		temp_y = y;
		is_new_lat_used++;
		moves.insert(moves.end(), x);
		moves.insert(moves.end(), y);
	}
	else if (table[x][y] != '-') {
		current_word += table[x][y];
		moves.insert(moves.end(), x);
		moves.insert(moves.end(), y);
	}
}

bool Main_logic::end_turn(bool& is_new_lat_used) {
	char move;
	auto lib_temp = find(library.begin(), library.end(), current_word);
	auto custom_lib_temp = custom_library.find(current_word);
	auto temp_used_fwords = find(f_player.pl_words.begin(), f_player.pl_words.end(), current_word);
	auto temp_used_swords = find(s_player.pl_words.begin(), s_player.pl_words.end(), current_word);
	if (temp_used_fwords != f_player.pl_words.end() || temp_used_swords != s_player.pl_words.end()) {
		cout << "This word has already been used, think further! Or skip the turn(\"E\")\n>>";
		cin >> move;
		if (is_new_lat_used) table[temp_x][temp_y] = '-';
		is_new_lat_used = 0;
		current_word.clear();
		if (move == 'E') return 1;
		system("pause");
		system("cls");
		show_play_field();
		return 1;
	}
	else if (lib_temp == library.end() && custom_lib_temp == custom_library.end()) {
		cout << "The word \"" << current_word << "\" is not in the dictionary, want to add it to the dictionary?\n(y/n)>> ";
		cin >> move;
		if (move == 'y') {
			add_to_lib(current_word);
			return 1;
		}
		else if (move == 'n') {
			cout << "Think better, or press \"E\" to skip the turn\n>> ";
			cin >> move;
			if (is_new_lat_used) table[temp_x][temp_y] = '-';
			is_new_lat_used = 0;
			current_word.clear();
			system("cls");
			show_play_field();
			if (move == 'E') return 1;
			return 1;
		}
	}
	else  return 1;
}

bool Main_logic::check_pos() {
	bool r = 0, l = 0, u = 0, d = 0;
	if (x < COL && x >= 0 && y < ROW && y >= 0) {
		if (x + 1 < COL)
			if (table[x + 1][y] != '-' && !ch_past_pos(x + 1, y)) u = 1;
		if (x - 1 >= 0)
			if (table[x - 1][y] != '-' && !ch_past_pos(x - 1, y)) d = 1;
		if (y + 1 < ROW)
			if (table[x][y + 1] != '-' && !ch_past_pos(y + 1, y)) r = 1;
		if (y - 1 >= 0)
			if (table[x][y - 1] != '-' && !ch_past_pos(y - 1, y)) l = 1;
		if (u == 1 || d == 1 || l == 1 || r == 1) return false;
		else return true;
		/*if ((x + 1 < COL && !ch_past_pos(x + 1, y)) || (x - 1 >= 0 && !ch_past_pos(x - 1, y))
			|| (y + 1 < ROW && !ch_past_pos(y + 1, y)) || (x - 1 >= 0 && !ch_past_pos(y - 1, y))) return false;*/
	}
	else return true;
}

bool Main_logic::ch_past_pos(int x, int y) {
	if (moves.size() != 0) {
		for (int i = 0; i < moves.size(); i += 2) {
			if (moves[i] == x && moves[i + 1] == y) return true;
		}
	}
	return false;
}

void Main_logic::first_word_initialization(string f_word) {
	if (f_word == "r") {
		while (f_word.size() != COL) {
			f_word = library[rand() % library.size()];
		}
	}
	for (int i = 0; i < COL; i++) {
		table[ROW / 2][i] = f_word[i];
	}
}

void Main_logic::counting_points() {
	if (step_count % 2) { // визначає чій був хід
		f_player.pl_words.push_back(current_word);
		f_player.player_points += current_word.size();
	}
	else {
		s_player.pl_words.push_back(current_word);
		s_player.player_points += current_word.size();
	}
}

void Main_logic::checks_for_winner() {
	if (f_player.player_points > s_player.player_points) cout << "The first player wins!\n";
	else if (f_player.player_points < s_player.player_points) cout << "The second player won!\n";
	else cout << "Draw!\n";
}
