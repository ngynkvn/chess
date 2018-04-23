//
// Created by Nicholas Miller on 4/17/18.
//

#include "Evaluation.h"
#include <iostream>

/*
Returns the best move by finding the move with the highest score
*/
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

/*
Finds the score of the board given into the parameter
--pass parameters minimax(current Board, 4, -10000, 10000, true);
*/
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

/*
Returns a vector of boards that show the outcome of each
possible move that can currently be made on the actual board
*/
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

/*

*/
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
            if(curr_board[i][j].getColor() == game_state.same())
            {
                evaluation += material[curr_board[i][j].getPieceCode()];
            }

            else if(curr_board[i][j].getColor() == game_state.opposite())
            {
                evaluation -= material[curr_board[i][j].getPieceCode()];
            }

            evaluation += get_piece_value(curr_board[i][j], i, j, is_end);
        }
    }

    return evaluation;
}

/*
Returns the piece value, which are in the Evaluation.h file
*/
int get_piece_value(Piece p, int x, int y, bool is_end)
{
    if (is_end && (p.getPieceCode() == epcBking || p.getPieceCode() == epcWking)) {
        if (p.getPieceCode() == epcBking) {
            return -king_end_table[x][y];
        } else {
            return king_end_table[x][y];
        }
    }

    switch (p.getPieceCode())
    {
    // white piece table lookup
    case epcWpawn:
        return pawn_table[x][y];
    case epcWknight:
        return knight_table[x][y];
    case epcWbishop:
        return bishop_table[x][y];
    case epcWrook:
        return rook_table[x][y];
    case epcWqueen:
        return queen_table[x][y];
    case epcWking:
        return king_mid_table[x][y];

    // black piece table lookup
    case epcBpawn:
        return -pawn_table[x][y];
    case epcBknight:
        return -knight_table[x][y];
    case epcBbishop:
        return -bishop_table[x][y];
    case epcBrook:
        return -rook_table[x][y];
    case epcBqueen:
        return -queen_table[x][y];
    case epcBking:
        return -king_mid_table[x][y];

    // is there no piece
    default:
        return 0;
    }
}
