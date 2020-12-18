#ifndef __KnightConfig_H
#define __KnightConfig_H

#include "Board.h"
#include <stack>

class KnightConfig 
{
private:
    bool move_available(int i, Board board) const;
    bool free(int i, Board board) const;

public:
    KnightConfig(int, int);
    void current_config() const;
    void next_config();
    bool has_config() const;

private:
    struct Config_Node
    {
        int knights, last_pos;
        Board board;
    };

    std::stack<Config_Node> config;
    Config_Node current;
};

KnightConfig::KnightConfig(int n, int k) 
{
    Board board(n);
    config.push({k, -1, board});
}

void KnightConfig::current_config() const 
{
    current.board.print();
}

void KnightConfig::next_config() 
{
    KnightConfig::Config_Node top = config.top();
    Board temp_board;
    while (top.knights != 0)
    {
        config.pop();
        for (int i = top.last_pos+1; i < top.board.length(); i++)
        {
            if(move_available(i, top.board)) 
            {
                temp_board = top.board;
                temp_board[i] = 'H';
                config.push({top.knights-1, i, temp_board});
            }
        }
        top = config.top();
    }
    current = top;
    config.pop();
}

bool KnightConfig::has_config() const
{
    return !config.empty();
}

bool KnightConfig::free(int i, Board board) const
{
    return i < 0 || i >= board.length() || board[i] == '_';
}

bool KnightConfig::move_available(int i, Board board) const
{
    int row_size = sqrt(board.length());
    return free(i, board) 
        && ((i % row_size != 0) ? free(i-2*row_size-1, board) && free(i+2*row_size-1, board) : true)
        && ((i % row_size != row_size-1) ? free(i-2*row_size+1, board) && free(i+2*row_size+1, board) : true) 
        && ((i % row_size > 1) ? free(i-row_size-2, board) && free(i+row_size-2, board) : true)
        && ((i % row_size < row_size-2) ? free(i-row_size+2, board) && free(i+row_size+2, board) : true);
}

#endif