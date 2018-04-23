#ifndef EVALUATION_H
#define EVALUATION_H

#include "Board.h"
#include "Move.h"
#include "Search.h"
#include <vector>

Move mini_max(const Board &);
// Depth first search tree which implements alpha-beta pruning
int mini_max(const Board & currBoard, int depth, int alpha, int beta, bool is_max_player);

// evaluates the current board state
int evaluate(const Board& currBoard);

// gets the value of a piece at a give location
int get_piece_value(Piece p, int x, int y, bool is_end);

// calls generateMoveList, makes each move and appends to vector to be processed later.
std::vector<Board> get_states(const Board& curr);

// is the game in end game scenarios
bool is_end_game(const Board &);

//Material weights
const int material[] = {0,100,320,325,500,975,32767,
                        0,100,320,325,500,975,32767};

// Position tables
// Pawn table
const int pawn_table[8][8] = {{  0,   0,   0,   0,   0,   0,   0,   0},
                              { 50,  50,  50,  50,  50,  50,  50,  50},
                              { 10,  10,  20,  30,  30,  20,  10,  10},
                              {  5,   5,  10,  27,  27,  10,   5,   5},
                              {  0,   0,   0,  25,  25,   0,   0,   0},
                              {  5,  -5, -10,   0,   0,  10,  -5,   5},
                              {  5,  10 , 10, -25, -25,  10,  10,   5},
                              {  0,   0,   0,   0,   0,   0,   0,   0}};

// Knight table
const int knight_table[8][8] = {{ -50, -40, -30, -30, -30, -30, -40, -50},
                                { -40, -20,  0 ,  0 ,  0 ,  0 , -20, -40},
                                { -30,  0 ,  10,  15,  15,  10,  0 , -30},
                                { -30,  5 ,  15,  20,  20,  15,  5 , -30},
                                { -30,  0 ,  15,  20,  20,  15,  0 , -30},
                                { -30,  5 ,  10,  15,  15,  10,  5 , -30},
                                { -40, -20,  0 ,  5 ,  5 ,  0 , -20, -40},
                                { -50, -40, -30, -30, -30, -30, -40, -50}};

// Bishop table
const int bishop_table[8][8] = {{ -20, -10, -10, -10, -10, -10, -10, -20},
                                { -10,  0 ,  0 ,  0 ,  0 ,  0 ,  0 , -10},
                                { -10,  0 ,  5 ,  10,  10,  5 ,  0 , -10},
                                { -10,  5 ,  5 ,  10,  10,  5 ,  5 , -10},
                                { -10,  0 ,  10,  10,  10,  10,  0 , -10},
                                { -10,  10,  10,  10,  10,  10,  10, -10},
                                { -10,  5 ,  0 ,  0 ,  0 ,  0 ,  5 , -10},
                                { -20, -10, -40, -10, -10, -40, -10, -20}};

// Rook table
const int rook_table[8][8] = {{  0,  0,  0,  5,  5,  0,  0,  0},
                              { -5,  0,  0,  0,  0,  0,  0, -5},
                              { -5,  0,  0,  0,  0,  0,  0, -5},
                              { -5,  0,  0,  0,  0,  0,  0, -5},
                              { -5,  0,  0,  0,  0,  0,  0, -5},
                              { -5,  0,  0,  0,  0,  0,  0, -5},
                              {  5, 10, 10, 10, 10, 10, 10,  5},
                              {  0,  0,  0,  0,  0,  0,  0,  0}};

// Queen table
const int queen_table[8][8] = {{ -20, -10, -10, -5, -5, -10, -10, -20},
                               { -10,   0,   5,  0,  0,   0,   0, -10},
                               { -10,   5,   5,  5,  5,   5,   0, -10},
                               {  -5,   0,   5,  5,  5,   5,   0,   0},
                               {  -5,   0,   5,  5,  5,   5,   0,  -5},
                               { -10,   0,   5,  5,  5,   5,   5, -10},
                               { -10,   0,   0,  0,  0,   5,   0, -10},
                               { -20, -10, -10, -5, -5, -10, -10, -20}};

// King mid-game table
const int king_mid_table[8][8] = {{ -30, -40, -40, -50, -50, -40, -40, -30},
                                  { -30, -40, -40, -50, -50, -40, -40, -30},
                                  { -30, -40, -40, -50, -50, -40, -40, -30},
                                  { -30, -40, -40, -50, -50, -40, -40, -30},
                                  { -20, -30, -30, -40, -40, -30, -30, -20},
                                  { -10, -20, -20, -20, -20, -20, -20, -10},
                                  {  20,  20,  0 ,  0 ,  0 ,  0 ,  20,  20},
                                  {  20,  30,  10,  0 ,  0 ,  10,  30,  20}};

// King end-game table
const int king_end_table[8][8] = {{ -50, -40, -30, -20, -20, -30, -40, -50},
                                  { -30, -20, -10,   0,   0, -10, -20, -30},
                                  { -30, -10,  20,  30,  30,  20, -10, -30},
                                  { -30, -10,  30,  40,  40,  30, -10, -30},
                                  { -30, -10,  30,  40,  40,  30, -10, -30},
                                  { -30, -10,  20,  30,  30,  20, -10, -30},
                                  { -30, -30,   0,   0,   0,   0, -30, -30},
                                  { -50, -30, -30, -30, -30, -30, -30, -50}};

#endif