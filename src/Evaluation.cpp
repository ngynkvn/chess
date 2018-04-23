//
// Created by Nicholas Miller on 4/17/18.
//

#include "Evaluation.h"
#include <iostream>

Move mini_max(const Board &game_state)
{
    std::vector<Move> moves = Search::generateMoveList(game_state);
    int bestScore = evaluate(game_state.makeMove(moves[0]));
    Move bestMove = moves[0];
    for (auto i = moves.begin(); i != moves.end(); i++)
    {
        int currScore = mini_max(game_state.makeMove(*i), 3, -10000, 10000, true);
        if (currScore > bestScore)
        {
            bestScore = currScore;
            bestMove = *i;
        }
    }
    return bestMove;
}

// pass parameters minimax(current Board, 4, -10000, 10000, true);
int mini_max(const Board &game_state, int depth, int alpha, int beta, bool is_max_player)
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

std::vector<Board> get_states(const Board& curr)
{
    std::vector<Board> v;
    std::vector<Move> moves = Search::generateMoveList(curr);
    for (auto i = moves.begin(); i != moves.end(); i++)
    {
        v.push_back(curr.makeMove(*i));
    }
    return v;
}

bool is_end_game(const Board& game_state) {
    int piece_count = 0;
    Piece **curr_board = game_state.getBoard();

    for (int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if (curr_board[i][j].getPieceCode() != epcEmpty) piece_count++;
        }
    }

    if (piece_count < 12) {
        return true;
    }
    return false;
}

int evaluate(const Board& game_state)
{
    int evaluation = 0;
    Piece **curr_board = game_state.getBoard();
    bool is_end = is_end_game(game_state);

    /*  used to add an extra component to the evaluation by increasing score by the amount of possible moves.
     *  This increase the time to find a move significantly; therefore, it is not viable in the current build.
     *
     *  vector<Move> curr_moves = Search::generateMoveList(game_state);
     *
     *  if (curr_moves.size() > 0) {
     *  evaluation += curr_moves.size();
     *  }
     */

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            evaluation += get_piece_value(curr_board[i][j], i, j, is_end);
        }
    }

    return evaluation;
}

int get_piece_value(Piece p, int x, int y, bool is_end)
{
    int score = 0;

    // if end game and current piece is a king
    if (is_end && (p.getPieceCode() == epcBking || p.getPieceCode() == epcWking)) {
        if (p.getPieceCode() == epcBking) {
            score += material[5];
            score += -king_end_table[x][y];
            return -score;
        } else {
            score += material[5];
            score += king_end_table[x][y];
            return score;
        }
    }

    switch (p.getPieceCode())
    {
    // white evaluation
    case epcWpawn: {
        score += material[0];
        score += pawn_table[x][y];
        if (x == 0 || x == 7) score -= 15;
        return score;
    }
    case epcWknight: {
        score += material[1];
        score += knight_table[x][y];
        if (is_end) {
            score -= 10;
        }
        return score;
    }
    case epcWbishop: {
        score += material[2];
        score += bishop_table[x][y];
        if (is_end) {
            score += 10;
        }
        return score;
    }
    case epcWrook: {
        score += material[3];
        score += rook_table[x][y];
        return score;
    }
    case epcWqueen: {
        score += material[4];
        score += queen_table[x][y];
        if ((x != 7 || y != 3) && !is_end) {
            score -= 10;
        }
        return score;
    }
    case epcWking: {
        score += material[5];
        score += king_mid_table[x][y];
        return score;
    }


    // black evaluation
    case epcBpawn: {
        score += material[0];
        score += -pawn_table[x][y];
        if (x == 0 || x== 7) score -= 15;
        return -score;
    }
    case epcBknight: {
        score += material[1];
        score += -knight_table[x][y];
        if (is_end) {
            score -= 10;
        }
        return -score;
    }
    case epcBbishop: {
        score += material[2];
        score += -bishop_table[x][y];
        if (is_end) {
            score += 10;
        }
        return -score;
    }
    case epcBrook: {
        score += material[3];
        score += -rook_table[x][y];
        return -score;
    }
    case epcBqueen: {
        score += material[4];
        score += -queen_table[x][y];
        if ((x != 7 || y != 3) && !is_end) {
            score -= 10;
        }
        return -score;
    }
    case epcBking: {
        score += material[5];
        score += -king_mid_table[x][y];
        return -score;
    }

    // is there no piece
    default:
        return score;
    }
}
