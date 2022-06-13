#include <iostream>
#include <vector>
#include <string>
#include <algorithm> 
#include <chrono>
#include<iomanip>

class TicTacToe{
private:

    int size;           //rozmiar planszy
    int required;       //znaki wymagane do wygranej
    int moves_done;     //liczba wykonanych ruchow na planszy
    int minmax_counter; //liczba wywolan minmaxa (uzywana do debuggowania)
    short** _board;     // 0 - puste pole, 1 - kolko, 2 - krzyżyk

public:

    TicTacToe(int _size, int _required);        //konstruktor klasy
    void print() const;                         //metoda rysujaca plansze gry w terminalu
    bool set_value(int x, int y, int value);    //ustawienie wartosci na danym polu
    bool is_free(int x, int y) const;           //sprawdzenie czy pole jest wolne
    bool is_full() const;                       //sprawdzenie czy cala plansza jest pelna
    void clear_field(int x, int y);             //usuniecie wartosci w danym polu
    void game_loop_pvp();           //petla gry - gracz kontra gracz 
    void game_loop_ai();            //petla gry - gracz kontra komputer 
    int game_result() const;        //metoda zwracajaca wynik gry
    int find_best_move(int depth);  //szukanie najlepszego ruchu na planszy 
                                    //dla danej glebokosci szukania
    int minmax(int value, int depth, int alpha, int beta, bool is_max); 
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
    
    size = _size; required = _required; moves_done = 0; minmax_counter = 0;

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
    std::cout << "  ";
    for (int i = 0; i < size; ++i)
    {
        std::cout << " " << i << "  ";
    }   //numeracja kolumn

    std::cout << std::endl;
    std::cout << std::string((4*size + 3), '=') << std::endl;
    for (int i = 0; i < size; ++i)
    {
        std::cout << "| ";
        for (int j = 0; j < size; ++j)
        {
            if (_board[i][j] == 0)
                std::cout << "  ";

            if (_board[i][j] == 1)
                std::cout << " O";

            if (_board[i][j] == 2)
                std::cout << " X";

            if (j < (size - 1))
            std::cout << " |";

        }
        std::cout << "  | " << i;   .//numeracja kolumn
        std::cout << std::endl;

        if (i < (size - 1))
        {
            std::cout << "| ";
            for (int k = 0; k < size - 1; ++k)
            {
                std::cout << "---+";
            }
            std::cout << "--- |" << std::endl;
        }
    }
    std::cout << std::string((4*size + 3), '=') << std::endl;
    std::cout << "Wykonane ruchy: " << moves_done << std::endl;
}

bool TicTacToe::is_free(int x, int y) const
{   //true kiedy wolne, false jesli zajete
    if (_board[y][x] != 0)
        return false;
    else
    return true;        
}

bool TicTacToe::is_full() const
{   //true jesli cala plansza zajeta
    return (moves_done == (size*size));
}

bool TicTacToe::set_value(int x, int y, int value)
{
    // 0 - puste pole, 1 - kolko, 2 - krzyżyk
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
    if (_board[y][x] != 0)
    {
        std::cout << "Blad: to pole jest zajete! " << std::endl;
        return false;        
    }
    if (value < 1 || value > 2)
    {
        std::cout << "Blad: niepoprawna wartosc do wpisania w pole! " << std::endl;
        return false;
    }
    _board[y][x] = value;
        moves_done++;

    return true; 
}

void TicTacToe::clear_field(int x, int y)
{
    if (_board[y][x] != 0)
    {
        _board[y][x] = 0;
        moves_done--;
    }
}

int TicTacToe::game_result() const
{   // -1 - wygrana gracza 2 (krzyzyka)
    //  1 - wygrana gracza 1 (kolka)
    int player1, player2, player1_2, player2_2;

    //minimalna liczba ruchow potrzebna do wygranej,
    //wczesniej nie ma potrzeby sprawdzac
    if (moves_done < (2*required - 1))
        return 0;

    // sprawdzenie pionu
    for (int i = 0; i < size; ++i)
    {
        player1 = 0; 
        player2 = 0;

        for (int j = 0; j < size - 1; ++j)
        {
            if (_board[j][i] != 0)
            {  
            if (_board[j][i] == _board[j+1][i])
            {
                if (_board[j][i] == 1)
                    player1++;

                else if (_board[j][i] == 2)
                    player2++;

                if (player1 == (required - 1))
                    return 1;

                if (player2 == (required - 1))
                    return -1;
            }
            else{player1 = 0; player2 = 0;}
            }
        } 
    }
    
    // sprawdzenie poziomu
    for (int i = 0; i < size; ++i)
    {
        player1 = 0; 
        player2 = 0;

        for (int j = 0; j < size - 1; ++j)
        {
            if (_board[i][j] != 0)
            { 
            if (_board[i][j] == _board[i][j+1])
            {
                if (_board[i][j] == 1)
                    player1++;

                else if (_board[i][j] == 2)
                    player2++;

                if (player1 == (required - 1))
                    return 1;

                if (player2 == (required - 1))
                    return -1;
            }
            else{player1 = 0; player2 = 0;}
            }
        } 
    }

    //sprawdzenie gornego prawego naroznika + diagonali ujemnej
    //oraz dolnego prawego naroznika + diagonali dodatniej
    for (int i = 0; i < size - required + 1; ++i)
    {
        player1 = 0; 
        player2 = 0;
        player1_2 = 0; 
        player2_2 = 0;

        for (int j = 0; j < size - (1 + i); ++j)
        {
            if (_board[j][i + j] != 0)
            { 
            if (_board[j][i + j] == _board[j + 1][i + j + 1])
            {
                if (_board[j][i + j] == 1)
                    player1++;

                else if (_board[j][i + j] == 2)
                    player2++;

                if (player1 == (required - 1))
                    return 1;

                if (player2 == (required - 1))
                    return -1;
            }
            else{player1 = 0; player2 = 0;}
            }
            if (_board[size - 1 - j][i + j] != 0)
            { 
            if (_board[size - 1 - j][i + j] == _board[size - 2 - j][i + j + 1])
            {
                if (_board[size - 1 - j][i + j] == 1)
                    player1_2++;

                else if (_board[size - 1 - j][i + j] == 2)
                    player2_2++;

                if (player1_2 == (required - 1))
                    return 1;

                if (player2_2 == (required - 1))
                    return -1;
            }
            else{player1_2 = 0; player2_2 = 0;}
            }
        } 
    }

    //sprawdzenie dolnego lewego naroznika 
    //oraz gornego lewego naroznika
    for (int i = 1; i < size - required + 1; ++i)
    {
        player1 = 0; 
        player2 = 0;
        player1_2 = 0; 
        player2_2 = 0;

        for (int j = 0; j < size - (1 + i); ++j)
        {
            if (_board[i + j][j] != 0)
            { 
            if (_board[i + j][j] == _board[i + j + 1][j + 1])
            {
                if (_board[i + j][j] == 1)
                    player1++;

                else if (_board[i + j][j] == 2)
                    player2++;

                if (player1 == (required - 1))
                    return 1;

                if (player2 == (required - 1))
                    return -1;
            }
            else{player1 = 0; player2 = 0;}
            }
            if (_board[size - 1 - i - j][j] != 0)
            { 
            if (_board[size - 1 - i - j][j] == _board[size - 2 - i - j][j + 1])
            {
                if (_board[size - 1 - i - j][j] == 1)
                    player1_2++;

                else if (_board[size - 1 - i - j][j] == 2)
                    player2_2++;

                if (player1_2 == (required - 1))
                    return 1;

                if (player2_2 == (required - 1))
                    return -1;
            }
            else{player1_2 = 0; player2_2 = 0;}
            }
        } 
    }
    
    return 0;
}

void TicTacToe::game_loop_pvp()
{
    int counter = size * size;
    short value = 0; 
    short temp_x, temp_y;
    do
    {
        std::cout << "1. kolko " << "2. krzyzyk" << std::endl;
        std::cout << "Kto ma rozpoczac: ";
        std::cin >> value;
        std::cin.clear();
        std::cin.ignore(1024, '\n');
        if (value < 1 || value > 2)
        {
            std::cout << "Bledny wybor! ";
        }
        
    } while (value < 1 || value > 2);

    //this->print();
    while (counter > 0)
    {
        system("cls");
        this->print();
        std::cout << "Ruch " << ((value == 1) ? "kolka" : "krzyzyka") << std::endl;
        do
        {
        std::cout << "Podaj wartosc x: ";
        std::cin >> temp_x;
        std::cout << "Podaj wartosc y: ";
        std::cin >> temp_y;
        } while (!this->set_value(temp_x, temp_y, value));
        
        if(this->game_result() != 0)
        {
            system("cls");
            this->print();
            std::cout << "Koniec gry!" << std::endl;
            std::cout << "Wygrywa " << ((this->game_result() == 1) ? "kolko!" : "krzyzyk!") << std::endl;
            break;
        }
        value = value == 1 ? 2 : 1; // zmiana znaku po ruchu na przeciwny
        counter--;
    }
    if (this->game_result() == 0)
    {
        system("cls");
        this->print();
        std::cout << "Koniec gry!" << std::endl << "Remis!";
    }

}

void TicTacToe::game_loop_ai()
{
    int counter = size * size;
    short temp_x, temp_y;
    short move = 0;
    short value;
    int depth_tab[8] = {9, 10, 8, 6, 4, 3, 2, 2};

    do
    {
        std::cout << "1. gracz (kolko) " << "2. komputer (krzyzyk)" << std::endl;
        std::cout << "Kto ma rozpoczac: ";
        std::cin >> value;
        std::cin.clear();
        std::cin.ignore(1024, '\n');
        if (value > 1 || value > 2)
        {
            std::cout << "Bledny wybor! ";
        }
        
    } while (value < 1 || value > 2);

    //int depth_tab2[8] = {9, 12, 10, 8, 6, 4, 3, 3};

    //zmienne do mierzenia czasu ruchu
    auto begin = std::chrono::high_resolution_clock::now ();
    auto end = std::chrono::high_resolution_clock::now ();
    auto elapsed = std::chrono::duration_cast < std::chrono::nanoseconds > (end - begin);
    
    while (counter > 0)
    {
        system("cls");
        this->print();
        std::cout << "Ruch " << ((value == 1) ? "kolka" : "krzyzyka") << std::endl;
        if (value == 2) //ruch komputera
        {
        std::cout << "Obliczanie najlepszego ruchu" << std::endl;
        begin = std::chrono::high_resolution_clock::now ();
        
        //wywolywanie szukania najlepszego ruchu z rozna glebokoscia
        //dla roznych faz rozgrywki, im dluzej trwa gra, tym mniej kombinacji
        //dzieki czemu komputer moze glebiej szukac i nie trwa to zbyt dlugo
        if (moves_done < ((size*size)/3))
        {
            move = this->find_best_move(depth_tab[size - 3]);
        }
        else if (moves_done < (2*(size*size)/3))
        {
            move = this->find_best_move(depth_tab[size - 3] + 1);
        }
        else if (moves_done >= (2*(size*size)/3))
        {
            move = this->find_best_move(depth_tab[size - 3] + 2);
        }

        //std::cout << "(" << move/10 << ", " << move%10 << ")" << std::endl;
        end = std::chrono::high_resolution_clock::now ();
        elapsed = std::chrono::duration_cast < std::chrono::nanoseconds > (end - begin);
        minmax_counter = 0;

        //zagranie znalezionego ruchu
        this->set_value(move/10, move%10, value);
        }
        else if (value == 1)    //kolej gracza
        {
            if (moves_done != 0)
            {   //statystyki ruchu komputera
            std::cout << "Czas szukania: " << std::fixed << std::setprecision(3) << elapsed.count () * 1e-9 << " sekund" << std::endl;
            std::cout << "Najlepszy znaleziony ruch (X, Y): ";
            std::cout << "(" << move/10 << ", " << move%10 << ")" << std::endl;
            }
            
            do
            {
            std::cout << "Podaj wartosc x: ";
            std::cin >> temp_x;
            std::cout << "Podaj wartosc y: ";
            std::cin >> temp_y;
            } while (!this->set_value(temp_x, temp_y, value));
        }
        //this->print();
        if(this->game_result() != 0)
        {
            system("cls");
            this->print();
            std::cout << "Koniec gry!" << std::endl;
            std::cout << "Wygrywa " << ((this->game_result() == 1) ? "kolko!" : "krzyzyk!") << std::endl;
            break;
        }
        value = value == 1 ? 2 : 1; // zmiana znaku po ruchu na przeciwny
        counter--;
    }
    if (this->game_result() == 0)
    {
        system("cls");
        this->print();
        std::cout << "Koniec gry!" << std::endl << "Remis!";
    }

}

int TicTacToe::find_best_move(int depth)
{
    int temp, temp_x = -1, temp_y = -1;
    int best = INT_MAX; 
    int value = 2;      //zawsze szukamy ruchu dla krzyzyka

    if (this->moves_done == 0)
    {   //optymalna strategia dla pierwszego ruchu to zagranie w którykolwiek narożnik
        return 0; 
    }

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            if (this->is_free(i, j))
            {   //ustawienie danej pozycji na planszy i przeszukanie jej minmaxem
                this->set_value(i, j, value);
                temp = this->minmax(value, depth, -INT_MAX, INT_MAX, true);
                this->clear_field(i, j);

                if (temp < best) //szukamy najnizszej wartosci
                {
                    temp_x = i; temp_y = j;
                    best = temp;
                }
            } 
        }
    }

    return (10*temp_x + temp_y);    //zwracam liczbe w postaci XY jako najlepszy ruch
}

int TicTacToe::minmax(int value, int depth, int alpha, int beta, bool is_max)
{
    //wartosc na planszy w tym momencie, pomnozona przez 100 
    //aby mozna bylo skutecznie uwzgledniac glebokosc w ewaluacji pozycji 
    int evaluation = 100 * this->game_result();
    //std::cout << "Wartosc ev: " << evaluation << std::endl;

    minmax_counter++;   //zwiekszenie licznika przy kazdej rekurencji
    
    if (evaluation != 0 || depth == 0)  //dojscie do wygranej/przegranej lub konca glebokosci
    {   //zwracamy wyniki wraz z uwzglednieniem glebokosci 
        if(is_max)
            return evaluation - depth;
        else
            return evaluation + depth;
    }
    
    if (evaluation == 0 && this->is_full()) //koniec miejsca na planszy i remis
    {
        return evaluation;
    }
    
    if (is_max) //maksymalizacja
    {
        value = value == 1 ? 2 : 1;
        int max = -INT_MAX;
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                if (this->is_free(i, j))
                {   //rekurencyjnie wywolujemy kolejne minmaxy i sprawdzamy kolejne pozycje 
                    this->set_value(i, j, value);
                    max = std::max(max, this->minmax(value, depth - 1, alpha, beta, false));
                    this->clear_field(i, j);

                    alpha = std::max(alpha, max);   //ciecie a-b
                    if (alpha >= beta)
                        return alpha;
                } 
            }
        }
        return max;
    }

    else    //minimalizacja
    {
        value = value == 1 ? 2 : 1;
        int min = INT_MAX;
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                if (this->is_free(i, j))
                {   //rekurencyjnie wywolujemy kolejne minmaxy i sprawdzamy kolejne pozycje 
                    this->set_value(i, j, value);
                    min = std::min(min, this->minmax(value, depth - 1, alpha, beta, true));
                    this->clear_field(i, j);

                    beta = std::min(beta, min);     //ciecie a-b
                    if (alpha >= beta)
                        return beta;
                } 
            }
        }
        return min;
    }
    
}