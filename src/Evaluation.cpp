//
// Created by Nicholas Miller on 4/17/18.
//

#include "Evaluation.h"
#include <iostream>
#include <algorithm>

/*
 * Returns the best move by finding the move with the highest score.
 * This is done by the recursive minimax algorithm which simulates play up to a certain depth and calculates 
 * a heuristical score. Scores can then be correlated with the initial move to make the best decision.
 */
int callCount = 0;
Move mini_max(Board &game_state)
{
    std::vector<Move> moves = Search::generateMoveList(game_state);
    callCount = 0;

    int bestScore = evaluate(game_state.makeMove(moves[0]));
    game_state.unmakeMove();
    Move bestMove = moves[0];
    for (auto &move : moves) {
        game_state.makeMove(move);
        int currScore = mini_max(game_state, 3, -10000, 10000, game_state.isWhite());
        game_state.unmakeMove();
        if (game_state.isWhite() && currScore > bestScore)
        {
            bestScore = currScore;
            bestMove = move;
        }
        else if (!game_state.isWhite() && currScore < bestScore)
        {
            bestScore = currScore;
            bestMove = move;
        }
    }
    std::cout << "Call count: " << callCount << std::endl;
    callCount = 0;
    return bestMove;
}

/*
 * Alpha beta pruning is implemented to reduce the size of the game tree and improve performance of the algorithm.
 */
int mini_max(Board &game_state, int depth, int alpha, int beta, bool is_max_player)
{
    callCount++;
    // is the depth zero
    if (depth == 0)
    {
        return evaluate(game_state);
    }

    // are there no more possible game states
    std::vector<Move> children_states = Search::generateMoveList(game_state);
    if (children_states.empty())
        return evaluate(game_state);

    // maximize and minimize the possible moves
    if (is_max_player) // if it the players turn
    {
        int v = alpha;
        for (Move m : children_states)
        {
            game_state.makeMove(m);
            int v_prime = mini_max(game_state, depth - 1, alpha, beta, !is_max_player);
            game_state.unmakeMove();
            v = std::max(v_prime, v);
            alpha = std::max(alpha, v);
            if (beta <= alpha){
                break;
            }
        }
        return v;
    }
    else // if it's the opponents turn
    {
        int v = beta;
        for (Move m : children_states)
        {
            game_state.makeMove(m);
            int v_prime = mini_max(game_state, depth - 1, alpha, beta, !is_max_player);
            game_state.unmakeMove();
            v = std::min(v_prime, v);
            beta = std::min(beta, v);
            if (beta <= alpha){
                break;
            }
        }
        return v;
    }
}

/*
Returns a vector of boards that show the outcome of each
possible move that can currently be made on the actual board
*/
std::vector<Board> get_states(const Board &curr)
{
    std::vector<Board> v;
    std::vector<Move> moves = Search::generateMoveList(curr);
    for (auto i = moves.begin(); i != moves.end(); i++)
    {
//        v.push_back(curr.makeMove(*i));
    }
    return v;
}

/*

*/
bool is_end_game(const Board &game_state)
{
    int piece_count = 0;
    ePieceCode **curr_board = game_state.getBoard();

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (curr_board[i][j] != epcEmpty)
                piece_count++;
        }
    }

    return piece_count < 12;
}

int evaluate(Board &game_state)
{
    int evaluation = 0;
    ePieceCode **curr_board = game_state.getBoard();
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

/*
 * Returns the piece value, which are in the Evaluation.h file
 * This makes use of the position tables found in Evaluation.h and also includes 
 * programmer-defined heuristics to slightly tweak how the engine plays.
 */
int get_piece_value(ePieceCode p, int x, int y, bool is_end)
{
    int score = 0;

    // if end game and current piece is a king
    if (is_end && (p == epcBking || p == epcWking))
    {
        if (p == epcBking)
        {
            score += material[5];
            score += black_king_end_table[x][y];
            return -score;
        }
        else
        {
            score += material[5];
            score += white_king_end_table[x][y];
            return score;
        }
    }

    switch (p)
    {
    // white evaluation
    case epcWpawn:
    {
        score += material[0];
        score += white_pawn_table[x][y];
        if (x == 0 || x == 7)
            score -= 15;
        return score;
    }
    case epcWknight:
    {
        score += material[1];
        score += white_knight_table[x][y];
        if (is_end)
        {
            score -= 10;
        }
        return score;
    }
    case epcWbishop:
    {
        score += material[2];
        score += white_bishop_table[x][y];
        if (is_end)
        {
            score += 10;
        }
        return score;
    }
    case epcWrook:
    {
        score += material[3];
        score += white_rook_table[x][y];
        return score;
    }
    case epcWqueen:
    {
        score += material[4];
        score += white_queen_table[x][y];
        if ((x != 7 || y != 3) && !is_end)
        {
            score -= 10;
        }
        return score;
    }
    case epcWking:
    {
        score += material[5];
        score += white_king_mid_table[x][y];
        return score;
    }

    // black evaluation
    case epcBpawn:
    {
        score += material[0];
        score += black_pawn_table[x][y];
        if (x == 0 || x == 7)
            score -= 15;
        return -score;
    }
    case epcBknight:
    {
        score += material[1];
        score += black_knight_table[x][y];
        if (is_end)
        {
            score -= 10;
        }
        return -score;
    }
    case epcBbishop:
    {
        score += material[2];
        score += black_bishop_table[x][y];
        if (is_end)
        {
            score += 10;
        }
        return -score;
    }
    case epcBrook:
    {
        score += material[3];
        score += black_rook_table[x][y];
        return -score;
    }
    case epcBqueen:
    {
        score += material[4];
        score += black_queen_table[x][y];
        if ((x != 7 || y != 3) && !is_end)
        {
            score -= 10;
        }
        return -score;
    }
    case epcBking:
    {
        score += material[5];
        score += black_king_mid_table[x][y];
        return -score;
    }

    // is there no piece
    default:
        return score;
    }
}
