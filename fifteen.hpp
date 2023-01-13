#pragma once

const int b_side = 4;

void play();
bool play_again();
void copy_board(int (&)[b_side][b_side], const int (&)[b_side][b_side]);
bool is_equal(const int (&)[b_side][b_side], const int (&)[b_side][b_side]);
void shuffle_board(int (&)[b_side][b_side]);
void get_neighbours(const int (&)[b_side][b_side], const int, int (&)[4]);
void get_elem_pos(const int (&)[b_side][b_side], const int, int* const, int* const);
void swap(int*, int*);
void display_board(const int (&)[b_side][b_side]);
int get_player_move(const int (&)[b_side][b_side]);
void sort_hints(int (&a)[4]);
bool is_number(const std::string&);
bool is_move_legal(const int, const int(&)[4]);
