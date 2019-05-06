#if !defined(PERFT_H)
#define PERFT_H

#include "Board.h"
using u64 = unsigned long long;

std::tuple<u64,u64,u64> perft(Board& b, int depth);

#endif // PERFT_H
