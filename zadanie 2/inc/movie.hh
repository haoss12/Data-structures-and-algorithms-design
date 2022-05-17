#include <iostream>
#include <fstream>
#include <string>

class Movie
{
private:
    int ID;             //id filmu
    std::string title;  //tytul filmu
    short rating;       //oceny 0 - 10, krótszy typ dla oszczędności miejca

public:
    Movie (const int & _ID, const std::string & _title, const short & _rating):
        ID(_ID), title(_title), rating(_rating) {}
    Movie ():
        ID(), title(), rating() {};

    void set_data(const int & _ID, const std::string & _title, const short & _rating)
    {
        ID = _ID; title = _title; rating = _rating;
    }

    int get_ID () const {return ID;}
    std::string get_title () const {return title;}
    short get_rating () const {return rating;}
    void set_ID(const int & _ID) {ID = _ID;}
    void set_title(const std::string & _title) {title = _title;}
    void set_rating(const short & _rating) {rating = _rating;}
    bool operator < (const Movie & m2) const
    {
        return (rating < m2.rating);
    }
    bool operator > (const Movie & m2) const
    {
        return (!(*this < m2));
    }
};

std::ostream & operator << (std::ostream & strm, const Movie & m)
{
  strm << m.get_ID() << "," << m.get_title() << "," << m.get_rating();
  return strm;
}

int counting_elements(int n, std::string nazwa)
{   //funkcja ktora sprawdza ile z n elementow jest poprawnych
    std::ifstream file(nazwa);
    std::string temp;
    int counter = 0;
    while (std::getline(file, temp))
    {
        //sprawdzenie poprawnosci danej linii
        //linie uznaje za poprawną jeśli jej pierwszy i ostatni znak 
        //to cyfry, wtedy mamy zarówo ID jak i ocene filmu
        if (isdigit(temp[0]) && isdigit(temp[temp.length() - 1]))
        {   
            if (counter == n-1)
            {
                break;
            }
            counter++;
        }
    }
    file.close();
    return counter;
}

Movie* load_from_file(int n, int counter, std::string nazwa)
{
    std::ifstream file(nazwa);
    std::string temp;
    int i = 0;
    int temp_index;
    int index_length;
    int temp_rating;
    Movie* tab = new Movie[counter];    //utworzenie nowej tablicy o zadanym rozmiarze

    while (std::getline(file, temp))
    {   //sprawdzenie poprawnosci danej linii
        //linie uznaje za poprawną jeśli jej pierwszy i ostatni znak 
        //to cyfry, wtedy mamy zarówo ID jak i ocene filmu
        if (isdigit(temp[0]) && isdigit(temp[temp.length() - 1]))
        {   
            //wyjscie z pętli kiedy dojdziemy do konca zakresu
            if (i == counter)
            {
                break;
            }
            temp_index = stoi(temp); //odczytanie ID
            index_length = std::to_string(temp_index).length(); //odczytanie dlugosci ID
            if (temp[temp.length() - 5] == ',') //przypadek kiedy ocena to 10.0
            {
            tab[i].set_data(temp_index, temp.substr(index_length + 1, temp.length() - 6 - index_length), 10);
            }
            else    //pozostale oceny 0.0-9.0
            {
            temp_rating = stoi(temp.substr(temp.length() - 3));
            tab[i].set_data(temp_index, temp.substr(index_length + 1, temp.length() - 5 - index_length), temp_rating);
            }
            i++;
        }
    }
    file.close();
    return tab;
}

bool verification(Movie* tab, int counter)
{   //sprawdzamy czy poprzedni element jest wiekszy od nastepnego
    //jesli tak, to sortowanie sie nie powiodło
	for (int i = 1; i <= counter; i++)
	{
		if (tab[i] < tab[i - 1])
		{
			return false;
		}
	}
    return true;
}

float average(Movie* tab, int counter)
{
    float temp_avg;
    for (int i = 0; i <= counter; i++)
    {
        temp_avg += tab[i].get_rating();
    }
    return temp_avg/(counter+1);
}

int median(Movie* tab, int counter)
{
    if ((counter+1) % 2 == 0)
    {
        return (tab[counter/2].get_rating() + tab[(counter/2) - 1].get_rating())/2;
    }
    return tab[counter/2].get_rating();
}