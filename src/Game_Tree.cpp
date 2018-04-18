

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


int Tree::mini_max(Node curr_node, int depth, int alpha, int beta, bool max) {
    if (curr_node.is_terminal_node() || depth == 0) curr_node.evaluate();

    // if it is currently the players turn
    if (max) {
        int v = alpha;
        for (Node n : children) {
            int v_prime = mini_max(n, depth - 1, v, beta, !max);
            if (v_prime > v) v = v_prime;
            if (v > beta) return beta;
        }
        return v;
    }

    // if it is currently the opponents turn
    if (!max) {
        int v = beta;
        for (Node n : children) {
            int v_prime = mini_max(n, depth - 1, alpha, v, !max);
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

int Tree::get_piece_value(Piece p, int x, int y) {
    switch (p.getPieceCode()) {
        // white piece evaluation
        case epcEmpty:
            return 0;
        case epcWpawn:
            return white_pawn_table[y][x];
        case epcWknight:
            return white_knight_table[y][x];
        case epcWbishop:
            return white_bishop_table[y][x];
        case epcWrook:
            return white_rook_table[y][x];
        case epcWqueen:
            return white_queen_table[y][x];
        case epcWking:
            return white_king_table[y][x];

        // black piece evaluation
        case epcBpawn:
            return black_pawn_table[y][x];
        case epcBknight:
            return black_knight_table[y][x];
        case epcBbishop:
            return black_bishop_table[y][x];
        case epcBrook:
            return black_rook_table[y][x];
        case epcBqueen:
            return black_queen_table[y][x];
        case epcBking:
            return black_king_table[y][x];
    }
}


