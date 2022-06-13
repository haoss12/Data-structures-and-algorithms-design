#include "tictactoe.hh"


int main() {
    int size = 0, required = 0, game_type = 0;

    system("cls");
    std::cout << "Gra kolko-krzyzyk" << std::endl;

    do  //wybor rozmiaru planszy
    {
        std::cout << "Podaj rozmiar planszy <3, 10>: ";
        std::cin >> size;
        std::cin.clear();
        std::cin.ignore(1024, '\n');
        if (size < 3 || size > 10)
        {
            std::cout << "Bledne wymiary planszy! ";
        }
        
    } while (size < 3 || size > 10);

    do  //wybor liczby znakow do zwyciestwa
    {
        std::cout << "Podaj liczbe znakow do wygranej: ";
        std::cin >> required;
        std::cin.clear();
        std::cin.ignore(1024, '\n');
        if (required < 3 || required > size)
        {
            std::cout << "Bledna liczba znakow! ";
        }
        
    } while (required < 3 || required > size);

    TicTacToe game(size, required);

    do  //wybor trybu gry
    {
        std::cout << "1. gracz kontra gracz" << std::endl;
        std::cout << "2. gracz kontra komputer" << std::endl;
        std::cout << "Wybierz typ gry: ";
        std::cin >> game_type;
        std::cin.clear();
        std::cin.ignore(1024, '\n');
        if (game_type < 1 || game_type > 2)
        {
            std::cout << "Bledny typ gry! ";
        }
        
    } while (game_type < 1 || game_type > 2);

    if (game_type == 1)
        game.game_loop_pvp();

    else if (game_type == 2)
        game.game_loop_ai();
    
    return 0;
}