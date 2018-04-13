

#include "Board.h"
#include "Search.h"
#include "Game_Tree.h"

// Node Implementation

bool Node::is_terminal_node() {
    return (children.size() > 0);
}


Board Node::get_game_state() {
    return this->game_state;
}


void Node::add_child(Board game_state) {
    children.emplace_back(Node(game_state));
}

// Tree Implementation
// To fix
Tree::Tree (Board game_state) {

}


int Tree::mini_max(Node curr_node, int alpha, int beta, bool is_max_player) {
    if (curr_node.is_terminal_node()) return evaluate(curr_node);

    if (is_max_player) // if it the players turn
    {
        int v = alpha;
        for (Node n : children) {
            int v_prime = mini_max(n, v, beta, max);
            if (v_prime > v) v = v_prime;
            if (v > beta) return beta;
        }
        return v;
    }
    else // if it's the opponents turn
    {
        int v = beta;
        for (Node n : children) {
            int v_prime = mini_max(n, alpha, v, !max);
            if (v_prime < v) v = v_prime;
            if (v < alpha) return alpha;
        }
        return v;
    }
}

int Tree::evaluate(Node curr_node) {
    int evaluation = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            int** curr_board = curr_node.getBoard();
            evaluation += get_piece_value(curr_board[i][j], i, j);
        }
    }
    return evaluation;
}


int** flip_table(int** white_table) {

}


int Tree::get_piece_value(Piece p, int x, int y) {
    switch (p.getPieceCode()) {
        // white piece evaluation
        case epcEmpty:
            return 0;
        case epcWpawn:
            return white_pawn_table[x][y];
        case epcWknight:
            return white_knight_table[x][y];
        case epcWbishop:
            return white_bishop_table[x][y];
        case epcWrook:
            return white_rook_table[x][y];
        case epcWqueen:
            return white_queen_table[x][y];
        case epcWking:
            return white_king_table[x][y];

        // black piece evaluation
        case epcBpawn:
            return black_pawn_table[x][y];
        case epcBknight:
            return black_knight_table[x][y];
        case epcBbishop:
            return black_bishop_table[x][y];
        case epcBrook:
            return black_rook_table[x][y];
        case epcBqueen:
            return black_queen_table[x][y];
        case epcBking:
            return black_king_table[x][y];
    }
}


