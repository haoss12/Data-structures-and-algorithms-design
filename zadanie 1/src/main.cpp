#include <string>
#include <algorithm> //do mieszania tablicy dla symulacji losowości pakietów
#include <random>
#include "PriorityQueue.hh"

int main() {
    PriorityQueue <std::string> a;
    std::string message_to_send;
    std::string sended_message;
    std::string final_message;
    std::string temp;
 
    const int n = 10;    //liczba pakietow
    int randomized[n];   //tablica na pseudolosową kolejnośc pakietów
    std::mt19937 rng{std::random_device{}()};   //generator pseudolosowy
    
    for (int i = 0; i < n; i++){
        randomized[i] = i;
    }
    std::shuffle(&randomized[0], &randomized[10], rng);

    std::cout << "> wpisz wiadomosc:" << std::endl << "> ";
    std::getline(std::cin,message_to_send);
    
    int package_lenght = message_to_send.size()/n;
    int rest = message_to_send.size()%n;

    for (auto x : randomized){
        if (x == n-1)  //specjalny przypadek dla ostatniego pakietu
        {
        temp = message_to_send.substr((x)*package_lenght, package_lenght + rest);
        a.enqueue(temp, x+1);
        }
        else
        {
        temp = message_to_send.substr((x)*package_lenght, package_lenght);
        a.enqueue(temp, x+1);
        }
        sended_message = sended_message + temp;
    }

    for (int i = 0; i < n; i++){
        final_message = final_message+ a.removeMin(); //usuwamy elementy drukujac je az do konca kolejki
    }
    
    std::cout << "> wiadomosc bez sortowania:" << std::endl << "> ";
    std::cout << sended_message << std::endl;
    std::cout << "> wiadomosc z priorytetyzacja pakietow:" << std::endl << "> ";
    std::cout << final_message << std::endl;

    return 0;
}