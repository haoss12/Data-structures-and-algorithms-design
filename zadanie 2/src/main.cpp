#include "sorting_algs.hh"
#include <chrono>

int main() {
        /** Wczytywanie n elementów **/
    int n = 750000;

    std::cout << "Proba wczytania " << n << " danych" << std::endl;

    auto start = std::chrono::high_resolution_clock::now();
    int counter = counting_elements(n, "projekt2_dane.csv");
    Movie* tab_quick = load_from_file (n, counter, "projekt2_dane.csv"); 
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Wczytano " << counter << " poprawnych danych" << std::endl;
    std::cout << "Czas wczytywania = " << (float)std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()/1000000;
    std::cout << " s" << std::endl;

    Movie* tab_merge = load_from_file (n, counter, "projekt2_dane.csv");
    Movie* tab_bucket = load_from_file (n, counter, "projekt2_dane.csv"); 

        /** Quick sort **/
    std::cout << "----------------------" << std::endl;
    std::cout << "Quick sort: " << std::endl;
    auto start1 = std::chrono::high_resolution_clock::now();
    quick_sort(tab_quick, 0, counter-1);
    // bucket_sort(tab, 0, counter-1);
    auto end1 = std::chrono::high_resolution_clock::now();
    if (verification(tab_quick, counter-1)) std::cout << "Sortowanie sie udalo" << std::endl;
	std::cout << "Czas sortowania = " << (float)std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1).count()/1000000;
    std::cout << " s" << std::endl;
    std::cout << "Srednia: " << average(tab_quick, counter - 1) << std::endl;
    std::cout << "Mediana: " << median(tab_quick, counter - 1) << std::endl;

        /** Merge sort **/
    std::cout << "----------------------" << std::endl;
    std::cout << "Merge sort: " << std::endl;
    auto start2 = std::chrono::high_resolution_clock::now();
    merge_sort(tab_merge, 0, counter-1);
    auto end2 = std::chrono::high_resolution_clock::now();
    if (verification(tab_quick, counter-1)) std::cout << "Sortowanie sie udalo" << std::endl;
	std::cout << "Czas sortowania = " << (float)std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2).count()/1000000;
    std::cout << " s" << std::endl;
    std::cout << "Srednia: " << average(tab_merge, counter - 1) << std::endl;
    std::cout << "Mediana: " << median(tab_merge, counter - 1) << std::endl;

        /** Bucket sort **/
    std::cout << "----------------------" << std::endl;
    std::cout << "Bucket sort: " << std::endl;
    auto start3 = std::chrono::high_resolution_clock::now();
    bucket_sort(tab_bucket, 0, counter-1);
    auto end3 = std::chrono::high_resolution_clock::now();
    if (verification(tab_quick, counter-1)) std::cout << "Sortowanie sie udalo" << std::endl;
	std::cout << "Czas sortowania = " << (float)std::chrono::duration_cast<std::chrono::microseconds>(end3 - start3).count()/1000000;
    std::cout << " s" << std::endl;
    std::cout << "Srednia: " << average(tab_bucket, counter - 1) << std::endl;
        std::cout << "Mediana: " << median(tab_bucket, counter - 1) << std::endl;

    // for (int i = 0; i < counter; i++)
    // {
    //     std::cout << tab[i] << std::endl;
    //     //std::cout << tab[counter - 1] << std::endl;
    // }
    return 0;
}


