//
// Created by Nicholas Miller on 4/17/18.
//

#include "Evaluation.h"
#include <iostream>

Move mini_max(const Board& game_state)
{
    std::vector<Move> moves = Search::generateMoveList(game_state);
    int bestScore = evaluate(game_state.makeMove(moves[0]));
    Move bestMove = moves[0];
    for (auto i = moves.begin(); i != moves.end(); i++)
    {
        int currScore = mini_max(game_state.makeMove(*i), 4, -10000, 10000, true);
        if (currScore > bestScore)
        {
            bestScore = currScore;
            bestMove = *i;
        }
    }
    return bestMove;
}

// pass parameters minimax(current Board, 4, -10000, 10000, true);
int mini_max(Board game_state, int depth, int alpha, int beta, bool is_max_player)
{

    // is the depth zero
    if (depth == 0)
        return evaluate(game_state);

    // are there no more possible game states
    std::vector<Board> children_states = get_states(game_state);
    if (children_states.size() == 0)
        return evaluate(game_state);

    // maximize and minimize the possible moves
    if (is_max_player) // if it the players turn
    {
        int v = alpha;
        for (Board b : children_states)
        {
            int v_prime = mini_max(b, depth - 1, v, beta, !is_max_player);
            if (v_prime > v)
                v = v_prime;
            if (v > beta)
                return beta;
        }
        return v;
    }
    else // if it's the opponents turn
    {
        int v = beta;
        for (Board b : children_states)
        {
            int v_prime = mini_max(b, depth - 1, alpha, v, !is_max_player);
            if (v_prime < v)
                v = v_prime;
            if (v < alpha)
                return alpha;
        }
        return v;
    }
}

std::vector<Board> get_states(Board curr)
{
    std::vector<Board> v;
    std::vector<Move> moves = Search::generateMoveList(curr);
    for (auto i = moves.begin(); i != moves.end(); i++)
    {
        v.push_back(curr.makeMove(*i));
    }
    return v;
}

int evaluate(Board game_state)
{
    int evaluation = 0;
    Piece **curr_board = game_state.getBoard();
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            evaluation += get_piece_value(curr_board[i][j], i, j);
        }
    }
    return evaluation;
}

int get_piece_value(Piece p, int x, int y)
{
    switch (p.getPieceCode())
    {
    // empty piece evaluation
    case epcEmpty:
        return 0;
        // white piece evaluation
    case epcWpawn:
        return white_pawn_eval[x][y];
    case epcWknight:
        return white_knight_eval[x][y];
    case epcWbishop:
        return white_bishop_eval[x][y];
    case epcWrook:
        return white_rook_eval[x][y];
    case epcWqueen:
        return white_queen_eval[x][y];
    case epcWking:
        return white_king_eval[x][y];

        // black piece evaluation
    case epcBpawn:
        return black_pawn_eval[x][y];
    case epcBknight:
        return black_knight_eval[x][y];
    case epcBbishop:
        return black_bishop_eval[x][y];
    case epcBrook:
        return black_rook_eval[x][y];
    case epcBqueen:
        return black_queen_eval[x][y];
    case epcBking:
        return black_king_eval[x][y];
    default:
        return 0;
    }
}
