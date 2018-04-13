

#include "Board.h"
#include "Search.h"
#include "Game_Tree.h"

// Node Implementation
// determines if the current node is a terminal node or not
bool Node::is_terminal_node() {
    return (children.size() > 0);
}

// returns the current game state
Board Node::get_game_state() {
    return this->game_state;
}

// adds a node to children
void Node::add_child(Board game_state) {
    children.emplace_back(Node(game_state));
}



// Tree Implementation
// Tree constructor
// To be built with a depth of 4
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

// To fix
int Tree::evaluate(Node curr_node) {
    
}
