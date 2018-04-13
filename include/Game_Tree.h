//
// Created by Nicholas Miller on 4/12/18.
//

#ifndef CHESS_GAME_TREE_H
#define CHESS_GAME_TREE_H

#include <vector>

using namespace std;


// Node class
class Node {
private:
    Board game_state;
    vector<Node> children;

public:
    Node(Board game_state) : game_state(game_state) {}
    bool is_terminal_node();
    Board get_state();
    void add_child(Board game_state);

};

// To fix
// Tree class
class Tree {
private:
    Node* root;

public:
    Tree(Board game_state);

    // Depth first search tree which implements alpha-beta pruning
    int mini_max(Node* curr_node, int depth, int alpha, int beta);

    // evaluates the current board state
    int evaluate(Node curr_node);
};




// flip table
int** flip_table(int** white_table) {

}

// Pawn evaluation tables
const int white_pawn_table[][] = {{0,   0,  0,  0,  0,  0,  0,  0},
                                  {50, 50, 50, 50, 50, 50, 50, 50},
                                  {10, 10, 20, 30, 30, 20, 10, 10},
                                  {5,  5,  10, 25, 25, 10,  5,  5},
                                  {0,  0,   0, 20, 20,  0,  0,  0},
                                  {5, -5, -10,  0,  0,-10, -5,  5},
                                  {5, 10,  10,-20,-20, 10, 10,  5},
                                  {0,  0,  0,  0,  0,  0,  0,  0}};

const int black_pawn_table[][] = flip_table(white_pawn_table);


// Knight evaluation tables
const int white_knight_table[][] = {{-50,-40,-30,-30,-30,-30,-40,-50},
                                    {-40,-20,  0,  0,  0,  0,-20,-40},
                                    {-30,  0, 10, 15, 15, 10,  0,-30},
                                    {-30,  5, 15, 20, 20, 15,  5,-30},
                                    {-30,  0, 15, 20, 20, 15,  0,-30},
                                    {-30,  5, 10, 15, 15, 10,  5,-30},
                                    {-40,-20,  0,  5,  5,  0,-20,-40},
                                    {-50,-40,-30,-30,-30,-30,-40,-50}};

const int black_knight_table[][] = flip_table(white_knight_table);


// Bishop evaluation tables
const int white_bishop_table[][] = {{-20,-10,-10,-10,-10,-10,-10,-20},
                                    {-10,  0,  0,  0,  0,  0,  0,-10},
                                    {-10,  0,  5, 10, 10,  5,  0,-10},
                                    {-10,  5,  5, 10, 10,  5,  5,-10},
                                    {-10,  0, 10, 10, 10, 10,  0,-10},
                                    {-10, 10, 10, 10, 10, 10, 10,-10},
                                    {-10,  5,  0,  0,  0,  0,  5,-10},
                                    {-20,-10,-10,-10,-10,-10,-10,-20}};

const int black_bishop_table[][] = flip_table(white_bishop_table);


// Rook evaluation tables
const int white_rook_table[][] = {{0,  0,  0,  0,  0,  0,  0,   0},
                                  {5, 10, 10, 10, 10, 10, 10,   5},
                                  {-5,  0,  0,  0,  0,  0,  0, -5},
                                  {-5,  0,  0,  0,  0,  0,  0, -5},
                                  {-5,  0,  0,  0,  0,  0,  0, -5},
                                  {-5,  0,  0,  0,  0,  0,  0, -5},
                                  {-5,  0,  0,  0,  0,  0,  0, -5},
                                  {0,  0,  0,  5,  5,  0,  0,  0}};

const int black_rook_table[][] = flip_table(white_rook_table);


// Queen evaluation tables
const int white_queen_table[][] = {{-20,-10,-10, -5, -5,-10,-10,-20},
                                   {-10,  0,  0,  0,  0,  0,  0,-10},
                                   {-10,  0,  5,  5,  5,  5,  0,-10},
                                   {-5,   0,  5,  5,  5,  5,  0, -5},
                                   {0,  0,  5,   5,   5,  5,  0, -5},
                                   {-10,  5,  5,  5,  5,  5,  0,-10},
                                   {-10,  0,  5,  0,  0,  0,  0,-10},
                                   {-20,-10,-10, -5, -5,-10,-10,-20}};

const int black_queen_table[][] = flip_table(white_queen_table);


// Mid game king evaluation table
const int white_king_middle_table[][] = {{-30,-40,-40,-50,-50,-40,-40,-30},
                                         {-30,-40,-40,-50,-50,-40,-40,-30},
                                         {-30,-40,-40,-50,-50,-40,-40,-30},
                                         {-30,-40,-40,-50,-50,-40,-40,-30},
                                         {-20,-30,-30,-40,-40,-30,-30,-20},
                                         {-10,-20,-20,-20,-20,-20,-20,-10},
                                         {20,  20,  0,  0,  0,  0, 20, 20},
                                         {20, 30, 10,  0,  0, 10, 30, 20}};

const int black_king_middle_table[][] = flip_table(white_king_middle_table);


// End game king evaluation table
const int white_king_end_table[][] = {{-50,-40,-30,-20,-20,-30,-40,-50},
                                      {-30,-20,-10,  0,  0,-10,-20,-30},
                                      {-30,-10, 20, 30, 30, 20,-10,-30},
                                      {-30,-10, 30, 40, 40, 30,-10,-30},
                                      {-30,-10, 30, 40, 40, 30,-10,-30},
                                      {-30,-10, 20, 30, 30, 20,-10,-30},
                                      {-30,-30,  0,  0,  0,  0,-30,-30},
                                      {-50,-30,-30,-30,-30,-30,-30,-50}};

const int black_king_end_table[][] = flip_table(white_king_end_table);


#endif //CHESS_GAME_TREE_H
