// Game of fifteen
// Released under MIT license   https://opensource.org/licenses/mit-license.php

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>
#include "fifteen.hpp"

int main()
{
	bool game_is_running = true;

	while (game_is_running)
	{
		play();

		if (!play_again())
		{
			game_is_running = false;
		}
	}

	return 0;
}

void play()
{
	int board[b_side][b_side];
	int winboard[][b_side] = {
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 10, 11, 12},
		{13, 14, 15, 0}
	};

	copy_board(board, winboard);
	srand(static_cast<unsigned>(time(0)));

	do
	{
		shuffle_board(board);
	} while (is_equal(board, winboard));
	
	int move, move_counter = 0;
	bool game_cancel = false;

	while (!is_equal(board, winboard))
	{
		display_board(board);
		move = get_player_move(board);
		
		if (move == -1) // -1 means cancel the game by player
		{
			game_cancel = true;
			break;
		}
		else
		{	
			int from_y, from_x, to_y, to_x;
			
			get_elem_pos(board, move, &from_y, &from_x);
			get_elem_pos(board, 0, &to_y, &to_x);
			swap(&board[from_y][from_x], &board[to_y][to_x]);
			++move_counter;
		}
	}
	
	if (!game_cancel)
	{
		display_board(board);
		std::cout << "Congratulations!\n";
		std::cout << "Puzzle was completed by " << move_counter << " steps.\n";
	}
}

bool play_again()
{
	std::string s;

	std::cout << "Do you want to play again? (yes/no)\n";
	getline(std::cin >> std::ws, s);

	return (tolower(s[0]) == 'y');
}

void copy_board(int (&b)[b_side][b_side], const int (&bw)[b_side][b_side])
{
	for (int row = 0; row < b_side; row++)
	{
		for (int col = 0; col < b_side; col++)
		{
			b[row][col] = bw[row][col];
		}
	}
}

bool is_equal(const int (&b)[b_side][b_side], const int (&bw)[b_side][b_side])
{
	for (int row = 0; row < b_side; row++)
	{
		for (int col = 0; col < b_side; col++)
		{
			if (b[row][col] != bw[row][col])
			{
				return false;
			}
		}
	}

	return true;
}

void shuffle_board(int (&b)[b_side][b_side])
{
	int neighbours[4], rand_neighbour;
	int fromy, fromx, toy, tox;
	
	for (int i = 0; i < b_side * b_side * b_side * b_side; i++)
	{
		get_neighbours(b, 0, neighbours);
		
		int neighbours_count = 0;
			
		for (int i = 0; i < 4; i++)
		{
			if (neighbours[i] != 0)
			{
				++neighbours_count;
			}
		}
			
		rand_neighbour = neighbours[rand() % (neighbours_count + 1)];
		get_elem_pos(b, rand_neighbour, &fromy, &fromx);
		get_elem_pos(b, 0, &toy, &tox);
		swap(&b[fromy][fromx], &b[toy][tox]);
	}
}

void get_neighbours(const int (&b)[b_side][b_side], const int elem, int (&n)[4])
{
	int elem_y, elem_x;
	
	get_elem_pos(b, elem, &elem_y, &elem_x);
	
	n[0] = n[1] = n[2] = n[3] = 0;
	int index = 0;
	
	if (elem_y - 1 >= 0)
	{
		n[index++] = b[elem_y - 1][elem_x];
	}
	
	if (elem_y + 1 < b_side)
	{
		n[index++] = b[elem_y + 1][elem_x];
	}
	
	if (elem_x - 1 >= 0)
	{
		n[index++] = b[elem_y][elem_x - 1];
	}
	
	if (elem_x + 1 < b_side)
	{
		n[index] = b[elem_y][elem_x + 1];
	}
}

void get_elem_pos(const int (&b)[b_side][b_side], const int el, int* const y, int* const x)
{
	for (int row = 0; row < b_side; row++)
	{
		for (int col = 0; col < b_side; col++)
		{
			if (b[row][col] == el)
			{
				*y = row;
				*x = col;
				return;
			}
		}
	}
}

void swap(int* a, int* b)
{
	int temp;
	
	temp = *a;
	*a = *b;
	*b = temp;
}

void display_board(const int (&b)[b_side][b_side])
{
	static const std::string s1 = "+----+----+----+----+\n";
	static const std::string s2 = "|    |    |    |    |\n";

	std::cout << s1;

	for (int row = 0; row < b_side; row++)
	{
		std::cout << s2;
		std::cout << "| ";

		for (int col = 0; col < b_side; col++)
		{
			if (!b[row][col])
			{
				std::cout << "   | ";
			}
			else
			{
				std::cout << std::setw(2) << b[row][col] << " | ";
			}
		}

		std::cout << '\n';
		std::cout << s2 << s1;
		
	}
}

int get_player_move(const int (&b)[b_side][b_side])
{
	int legal_moves[4] = {0};
	
	get_neighbours(b, 0, legal_moves);
	sort_hints(legal_moves);
	
	while (true)
	{
		std::cout << "Your move: (";
		
		for (int i = 0; i < 3; i++)
		{
			if (!legal_moves[i])
			{
				continue;
			}
			
			std:: cout << legal_moves[i] << ", ";
		}
		
		std::cout << legal_moves[3] << " or Q for quit)\n> ";
		
		std::string s;
		int num;
		
		getline(std::cin >> std::ws, s);
		
		if ((s[0] == 'Q') || (s[0] == 'q'))
		{
			return -1;
		}
		
		if (is_number(s))
		{
			s = s.substr(0, 5);
			num = stoi(s);
			
			if ((num >= 1) && (num <= 15))
			{
				if (is_move_legal(num, legal_moves))
				{
					return num;
				}
			}
		}
		
		std::cout << "Illegal move!\n";
	}
}

void sort_hints(int (&a)[4])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (a[j] > a[j + 1])
			{
				swap(&a[j], &a[j + 1]);
			}
		}
	}
}

bool is_number(const std::string& s)
{
	for (auto it = s.begin(); it != s.end(); it++)
	{
		if (!isdigit(*it))
		{
			return false;
		}
	}
	
	return true;
}

bool is_move_legal(const int m, const int (&l)[4])
{
	for (int i = 0; i < 4; i++)
	{
		if (l[i] == m)
		{
			return true;
		}
	}
	
	return false;
}
