#include <stdio.h>
#include <stdlib.h>

/*funkcja shiftujaca tablice char, od drugiego parametru + 1 az do konca tablicy */
void shift(char*, const int, const int);

/* inicjalizacja pola zgodnie z podanymi warunkami poczatkowymi (przydzielenie pamiecie itd)*/
/* jako parametry przyjmuje wskaznik typu char, ktoremu zostanie przydzielona pamiec i stanie sie tablica */
/* oraz size, ktory zostanie "zwrocony" jako dlugosc tablicy */
void init_field(char**, int*);

/* funkcja bedaca sercem programu - jako argumenty przyjmuje wskaznik na tablice charow, dlugosc tablicy oraz */
/* liczbe iteracji. Wykonuje ona wszystkie reguly i ich zastosowanie */
void algae(char**, int*, int);

/* Swoja droga wydaje mi sie, ze taki algorytm wydajniejszy bylby na node'ach niz na tablicach, ze wzgledu na  */
/* latwosc dolaczania elementow po dowolnym elemencie bez potrzeby realokacji pamieci i shift'owania calej reszty */
int main()
{
    char *field = NULL;
    int size = 0, t = 10;

    init_field(&field, &size);
    printf("Podaj liczbe iteracji: ");
    /* scanf nie jest perfekcyjna funkcja do zczytywania ze wzgledu na brak obslugi bledow i prawdopodobnie jest wiele */
    /* sposobow na rozwiazanie tego problemu, jednak dla tak malego projektu nie spodziewam sie zlosliwych ludzi */
    /* wprowadzajacych zle dane, aby program sie wysypal */
    scanf("%d", &t);
    printf("\n");
    algae(&field, &size, t);
    /* po zakonczeniu wszystkich operacji zwalniam pamiec, ze wzgledu na "dobra praktyke" */
    /* oczywiscie system operacyjny sam zwolnilby pamiec po zakonczeniu dzialania programu, jednak jezeli bylby on */
    /* bardziej rozbudowany, nie zwalnianie pamieci po wykonaniu poszczegolnych jego czesci mogloby znacznie spowolnic */
    /* jego dzialanie, a nawet spowodac jego crash */
    free(field);
    return 0;
}

void init_field(char** field, int* size) {
    char c = '\0';

    printf("Podaj stan poczatkowy(A, lub B, dozwolone lancuchy):");
    (*size) = 1;
    /* zdanie na temat rzutowania malloc itp sa podzielone, jezeli chodzi o jezyk C, ktory automatycznie dopasowuje */
    /* odpowiedni typ bez potrzeby tego rzutowania. Ludzie spieraja sie tez, czy aby na pewno taki kod jest czytelny */
    /* szczegolnie kiedy rzutowanie jest bardziej skomplikowane, jednak jak dla mnie jest bardziej "uporzadkowany" */
    /* dzieki takiemu zabiegowi, dlatego wlasnie z niego korzystam, nawet jezeli nie jest to wymagane */
    (*field) = (char*)malloc((*size) * sizeof(char));
    /* zczytuje wprowadzony ciag, dpoki nie napotkam znaku nowej linii (ASCII 10) */
    /* podczas zczytywania "zwiekszam" pamięć poprzez realokacje przy kazdym przejsciu przez petle */
    while((c = (char)getchar()) != 10) {
        (*field) = (char*)realloc((*field), (*size) * sizeof(char));
        (*field)[(*size) - 1] = c;
        (*size)++;
    }
    /* na koniec przeprowadzam ostateczna realokacje aby "zamknac" lancuch znakow */
    (*field) = realloc((*field), (*size) * sizeof(char));
    (*field)[(*size) - 1] = '\0';
}
/* uwaga do zczytywanie: */
/* oczywiscie nie jest to optymalny sposob i prawdopodobnie duzo lepszym bylby buffer i ostateczne przepisanie go */
/* do tablicy o odpowiedniej dlugosci. Dzieki temu nie trzeba by bylo realokowac tablicy przy kazdym zczytanym charze */
/* jednak kod bylby wtedy bardziej skomplikowany i nieco mniej czytelny, takze wolalem zastosowac dla tak malego */
/* projektu ten sposob zczytywania danych z wejscia */



void algae(char** field, int* size, const int t) {
    int j = 0, i = 0;

    for(j = 0 ; j < t ; j++) {
        /* ustawiam i na 0, aby przy kazdej nowej iteracji sprawdzac string'a od poczatku */
        i = 0;

        /* sprawdzam, czy nie jestem na koncu string'a */
        while ((*field)[i] != '\0') {

            /* wprowadzam zasady w zaleznosci od napotkanego "stanu" glonu */
            if ((*field)[i] == 'A') {
                /* jezeli glon jest w stanie A, to wedlug regul musi przejsc w stan AB (A -> AB) */
                /* co za tym idzie musze ponownie zwiekszyc pamiec o ten jeden dodatkowy element */
                (*field) = (char*)realloc((*field), ((*size) + 1) * sizeof(char));
                /* sprawdzam, czy jest to ostatni element string'a, czy jednak jest cos za nim, co trzeba przesunac */
                if (i != (*size)-2) shift((*field), i, (*size));
                /* stosuje regule i ustawiam ostatni element tablicy (ktory de facto jest teraz niezdefiniowany) */
                /* aby zamykal stringa */
                (*field)[i] = 'A';
                (*field)[i + 1] = 'B';
                /* wole zamykac bez dodatkowych testow logicznych za kazdym razem gdy napotkam A */
                /* chodzi o to, ze bedzie zamkniety, jezeli A nie bedzie ostatnim elementem listy w funkcji shift */
                /* ktora przesunie przedostatni element na ostatni. */
                /* mimo, ze nie robilem zadnych testow wydaje mi sie, ze takie ewentualne nadpisanie i tak bedzie */
                /* szybsze niz kolejny test logiczny */
                (*field)[(*size)] = '\0';
                /* zmienna ktora wskazuje na jakiej pozycji obecnie znajduje w stringu musze zwiekszyc o 2, ze wzgledu */
                /* na to, ze pojawil sie jeden nowy element, ktory nie bedzie bral udzialu w tej iteracji */
                i += 2;
                (*size)++;
            } else if ((*field)[i] == 'B') {
                (*field)[i] = 'A';
                i++;
            } else {
                /* swego rodzaju obluga blednego stanu poczatkowego - Jezeli wprowadzony zostal inny stan niz ten */
                /* okreslony przez reguly, dzialanie funkcji zostanie zakonczone bez printowania nawet jednej iteracji */
                /* dzieki return;, ktory ma calkiem ciekawe zastosowanie w funkcjach typu void (tak, mozna go uzywac ) */
                /* poniewaz konczy on po prostu dzialanie funkcji, podczas gdy dla innych typow zawsze zwraca jakas */
                /* wartosc. */
                printf("Podano bledny stan poczatkowy.");
                return;
            }
        }
        /* printuje kazda iteracje, wraz z odpowiadajacym jej numerem */
        printf("%d. %s\n", j+1, *field);
    }
}

void shift(char* array, const int i, const int size) {
    int j = 0;
    /* shiftowac wole od konca, gdyz tak jest duzo prosciej - ostatni element nie jest wazny, gdyz jest dopiero dodany */
    /* nie jest to tez calkowity shift, poniewaz ostatni element nie zajmuje miejsca pierwszego */
    /* tylko zostaje niejako "wypchniety z tabeli, co nie jest problemem, bo i tak dopiero go dodalismy */
    /* i jest jeszcze nieokreslony, a na jego miejsce wejdzie zamkniecie stringa */
    for (j = size-1 ; j > i ; j--) {
        array[j] = array[j-1];
    }
}
