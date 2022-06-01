#include <iostream>
#include <vector>
#include <string>

class TicTacToe{
private:

    int size; 
    int required;
    //std::vector <int> board;
    short** _board;   // 0 - puste pole, 1 - kolko, 2 - krzyżyk

public:

    TicTacToe(int _size, int _required);
    void print() const;
    bool set_value(int x, int y, int value);

};

TicTacToe::TicTacToe (int _size, int _required)
{
    if (_size < 3 || _size > 10)
    {
        std::cout << "Blad: niepoprawny wymiar planszy! " << std::endl;
        return;
    }
    if (_required > _size || _required < 3)
    {
        std::cout << "Blad: niepoprawna liczba znakow w rzedzie! " << std::endl;
        return;
    }
    
    size = _size; required = _required;

    _board = new short* [_size];
    for (int i = 0; i < _size; i++)
    {
        _board[i] = new short [_size];
    }
    
    for (int i = 0; i < _size; i++)
    {
        for (int j = 0; j < _size; j++)
        {
            _board[i][j] = 0;
        }
    }
    
}

void TicTacToe::print() const
{
    std::cout << std::string(2*size + 1, '_') << std::endl << std::endl;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (_board[i][j] == 0)
            {
                std::cout << "  ";
            }
            if (_board[i][j] == 1)
            {
                std::cout << " O";
            }
            if (_board[i][j] == 2)
            {
                std::cout << " X";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::string(2*size + 1, '_') << std::endl;
}

bool TicTacToe::set_value(int x, int y, int value)
{
    if (x < 0 || x > size - 1)
    {
        std::cout << "Blad: niepoprawna wartosc x! " << std::endl;
        return false;
    }
    if (y < 0 || y > size - 1)
    {
        std::cout << "Blad: niepoprawna wartosc y! " << std::endl;
        return false;
    }
    if (_board[x][y] != 0)
    {
        std::cout << "Blad: to pole jest zajete! " << std::endl;
        return false;        
    }
    if (value < 1 || value > 2)
    {
        std::cout << "Blad: niepoprawna wartosc do wpisania w pole! " << std::endl;
        return false;
    }
    _board[x][y] = value;
    return true; 
}

int main() {
    short value = 1;
    TicTacToe game(3, 3);
    game.print();
    std::cout << std::endl << "flood" << std::endl;
    game.set_value(2,2,value);
    game.set_value(1,1,value);
    game.set_value(0,0,value);
    game.set_value(0,2,value);
    game.set_value(2,0,value);
    value = 2; 
    game.set_value(2,1,value);
    game.set_value(1,2,value);
    game.set_value(1,0,value);
    game.set_value(0,1,value);
    //game.set_value(2,3,1);
    //game.set_value(2,2,2);
    game.print();
    return 0;
}