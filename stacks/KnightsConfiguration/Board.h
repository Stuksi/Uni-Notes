#ifndef __Board_H
#define __Board_H

#include <iostream>
#include <cmath>
#include <cstring>
#include <cassert>

class Board 
{
public:
    Board();
    Board(int);
    Board(const Board&);
    Board &operator= (const Board&);
    ~Board();

    void print() const;
    size_t length() const;
    char operator[](size_t pos) const;
    char &operator[](size_t pos);
    
    char* get_data() const;
private:
    char* data;
    size_t size;
};

Board::Board() : size(0), data(nullptr) {}

Board::Board(int n) : size(n*n) 
{
    data = new char[size];
    for (size_t i = 0; i < size; i++)
    {
        data[i] = '_';
    }
}

Board::Board(const Board& board) : size(board.size) 
{
    data = new char[size];
    strcpy(data, board.data);
}

Board::~Board() {
    delete[] data;
}

Board &Board::operator= (const Board& board)
{
    if(this != &board) 
    {
        size = board.size;
        data = new char[size];
        strcpy(data, board.data);
    }
    return *this;
}

void Board::print() const 
{
    size_t n = sqrt(size), i = 0;
    while(i < size) 
    {
        std::cout << data[i++] << " ";
        if (i % n == 0)
        {
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
    std::cout << std::endl;
}

size_t Board::length() const
{
    return size;
}

char* Board::get_data() const
{
    return data;
}

char Board::operator[](size_t pos) const
{
    assert(pos >= 0 && pos < size);
    return data[pos];
}

char &Board::operator[](size_t pos)
{
    assert(pos >= 0 && pos < size);
    return data[pos];
}


#endif