#include "movie.hh"

void quick_sort(Movie* tab, int start, int end)
{
	//kiedy koncowy fragment jest mniejszy badz rowny od 
    //poczatkowego to przerywamy sekwencje
	if (end <= start) 
	{
		return;
	}

    Movie temp;         //zmienna tymczasowa do zamieniania elementów
	int p = start-1;    //zmienne do poruszania sie po tablicy
	int q = end+1;      
	short pivot = tab[(start + end) / 2].get_rating();  //pivot ze srodka

	do  //petla wykonujaca sie dopoki mozna 
    {
        //szukamy miejsca po lewej stronie od pivota,
        //w ktorym element jest od niego wiekszy
        while (tab[++p].get_rating() < pivot){};
		//szukamy miejsca po prawej stronie od pivota,
        //w ktorym element jest od niego mniejszy
		while (tab[--q].get_rating() > pivot){};
		//gdy znajdziemy te miejsca 
        //to zamieniamy elementy miejscami
		if (p <= q)
		{
            temp = tab[p];
            tab[p] = tab[q];
            tab[q] = temp;
		}
    } while (p <= q);
    
	//rekurencyjne wywolanie quicksorta dla podtablicy po lewej stronie
	if (q > start)  
	{
		quick_sort(tab, start, q);
	}
    //rekurencyjne wywolanie quicksorta dla podtablicy po prawej stronie
	if (p < end)
	{
		quick_sort(tab, p, end);
	}

}

void merge(Movie* tab, int start, int middle, int end)
{
    //utworzenie tymczasowej tabeli 
    Movie* temp = new Movie[end-start+1];
    int p = start;      //miejsce początku lewej cześci tabeli
    int q = middle+1;   //miejsce początku prawej cześci tabeli 
    int r = 0;
    //petla dziala dopoki nie napotka "granicy" dla dowolnej czesci tablicy
    while (p <= middle && q <= end)
    {
        if (tab[q] < tab[p])
        {
            temp[r] = tab[q];
            q++;
        }
        else
        {
            temp[r] = tab[p];
            p++;
        }
        r++;
    }
    //przypadek kiedy dobijemy do granicy lewej tablicy
    //wypelniamy wowczas dalsza czesc prawej czesci
        while (q <= end)
        {
            temp[r] = tab[q];
            q++;
            r++;
        }
    //przypadek kiedy dobijemy do granicy prawej tablicy
        while (p <= middle)
        {
            temp[r] = tab[p];
            p++;
            r++;
        }
    //przepisanie danych spowrotem do oryginalnej tabeli
    for (int i = start; i <= end; i++) 
    {
        //std::cout << temp[i-start] << std::endl;
        tab[i] = temp[i-start];
    }
}

void merge_sort(Movie* tab, int start, int end)
{
    int middle = (start + end)/2;
    if (start < end)
    {
        merge_sort(tab, start, middle);
        merge_sort(tab, middle + 1, end);
        merge(tab, start, middle, end);
    }
}

void bucket_sort(Movie* tab, int start, int end)
{
    //int counter1 = 0, counter2 = 0, counter3 = 0, counter4 = 0, counter5 = 0;
    //int counter6 = 0, counter7 = 0, counter8 = 0, counter9 = 0, counter10 = 0;
    int counter[10] = {0,0,0,0,0,0,0,0,0,0};
    //petla zliczajaca ile ma byc elementow w poszczegolnych kubelkach
    for (int i = start; i <= end; i++)    
    {
        if (tab[i].get_rating() == 1)
            counter[0]++;
        if (tab[i].get_rating() == 2)
            counter[1]++;
        if (tab[i].get_rating() == 3)
            counter[2]++;
        if (tab[i].get_rating() == 4)
            counter[3]++;
        if (tab[i].get_rating() == 5)
            counter[4]++;
        if (tab[i].get_rating() == 6)
            counter[5]++;
        if (tab[i].get_rating() == 7)
            counter[6]++;
        if (tab[i].get_rating() == 8)
            counter[7]++;
        if (tab[i].get_rating() == 9)
            counter[8]++;
        if (tab[i].get_rating() == 10)
            counter[9]++;  
    }

    //utworzenie kubelkow o zadanym rozmiarze
    Movie* bucket1 = new Movie[counter[0]];
    Movie* bucket2 = new Movie[counter[1]];
    Movie* bucket3 = new Movie[counter[2]];
    Movie* bucket4 = new Movie[counter[3]];
    Movie* bucket5 = new Movie[counter[4]];
    Movie* bucket6 = new Movie[counter[5]];
    Movie* bucket7 = new Movie[counter[6]];
    Movie* bucket8 = new Movie[counter[7]];
    Movie* bucket9 = new Movie[counter[8]];
    Movie* bucket10 = new Movie[counter[9]];

    //wyczyszczenie licznikow by nie tworzyc nowych zmiennych
    for (int i = 0; i < 10; i++)
    {
        counter[i] = 0;
    }
    //zapisanie pozycji o poszczegolnej ocenie do poszczegolnych koszykow
    for (int j = start; j <= end; j++)    
    {
        if (tab[j].get_rating() == 1)
            bucket1[counter[0]++] = tab[j];
        if (tab[j].get_rating() == 2)
            bucket2[counter[1]++] = tab[j];
        if (tab[j].get_rating() == 3)
            bucket3[counter[2]++] = tab[j];
        if (tab[j].get_rating() == 4)
            bucket4[counter[3]++] = tab[j];
        if (tab[j].get_rating() == 5)
            bucket5[counter[4]++] = tab[j];
        if (tab[j].get_rating() == 6)
            bucket6[counter[5]++] = tab[j];
        if (tab[j].get_rating() == 7)
            bucket7[counter[6]++] = tab[j];
        if (tab[j].get_rating() == 8)
            bucket8[counter[7]++] = tab[j];
        if (tab[j].get_rating() == 9)
            bucket9[counter[8]++] = tab[j];
        if (tab[j].get_rating() == 10)
            bucket10[counter[9]++] = tab[j];   
    }

    //wsadzenie pozycji z kubelkow do glownej tabeli w poprawnej kolejnosci
    for (int k = start; k <= end; k++)
    {
        for (int i = 0; i < counter[0]; i++)
        {
        tab[k] = bucket1[i];
        k++;
        }
        for (int i = 0; i < counter[1]; i++)
        {
        tab[k] = bucket2[i];
        k++;
        }
        for (int i = 0; i < counter[2]; i++)
        {
        tab[k] = bucket3[i];
        k++;
        }
        for (int i = 0; i < counter[3]; i++)
        {
        tab[k] = bucket4[i];
        k++;
        }
        for (int i = 0; i < counter[4]; i++)
        {
        tab[k] = bucket5[i];
        k++;
        }
        for (int i = 0; i < counter[5]; i++)
        {
        tab[k] = bucket6[i];
        k++;
        }
        for (int i = 0; i < counter[6]; i++)
        {
        tab[k] = bucket7[i];
        k++;
        }
        for (int i = 0; i < counter[7]; i++)
        {
        tab[k] = bucket8[i];
        k++;
        }
        for (int i = 0; i < counter[8]; i++)
        {
        tab[k] = bucket9[i];
        k++;
        }
        for (int i = 0; i < counter[9]; i++)
        {
        tab[k] = bucket10[i];
        k++;
        }
    }
}
