/* Lab 3: Tablice */

#include <stdio.h>

int main(){


  static int tab[5]; /* deklaracja pięcioelemetowej tablicy o ustalonej dłuości
		      * (ang. fixed-length array (FLA)); domyślna wartość 0 */

  int ab[5]; /* deklaracja pięcioelemetowej tablicy o ustalonej długości;
	       * domyślna wartość - niezdefioniowana */

  int tab2[5] = {6,7,8,9,0}; /* deklaracja i inicjacja pięcioelemetowej tablicy
			      * o ustalonej długości*/

  void printtab(int n){
    int tab[100*n]; /* deklaracja pięcioelemetowej tablicy o nieustalonej długości
		     * (ang. variable-length array (VLA)); */
  }

  int cb[1000] = {[500]=1}; /* deklaracja i inicjacja tablicy o ustalonej
			     * długości - element z indeksem 500 = 1; pozostałe
			     * = 0*/
  
  int *ptr1 = tab; /* nazwa tablicy jest adresem jej pierwszego elementu */

  printf("tab[0] = %d\n", tab[0]); /* pierwszy element tablicy */
  printf("tab[1] = %d\n", tab[1]); /* drugi element tablicy */
  
  puts("wskaźnik jest zmienną przechowujacą adres");
  printf("ptr1 = %p\n", ptr1);
  printf("adres ptr1 = %p\n", &ptr1); 
  int *ptr2 = tab2;
  printf("ptr2 = %p\n", ptr2);
  printf("adres ptr2 = %p\n", &ptr2); 
 
  puts("nazwa tablicy jest stałym wskaźnikiem t.j. const int *tab");
  printf("tab = %p\n", tab);
  printf("adres tab = %p\n", &tab); 
  printf("adres tab = %p\n", &tab[0]);

  printf("tab2 = %p\n", tab2);
  printf("adres tab = %p\n", &tab2); 
  printf("adres tab = %p\n", &tab2[0]);

  puts("przypisawanie zawartości jednego wskaźnika drugiemu");
  ptr1 = ptr2;
    
  printf("ptr1 = %p\n", ptr1);
  printf("adress ptr1 = %p\n", &ptr1);
  printf("ptr2 = %p\n", ptr2);
  printf("adress ptr2 = %p\n", &ptr2);

  puts("dereferencja wskaźnika i operacje arytmetyczne na wskaźnikach");
  printf("ptr1 = %d\n", *ptr1);
  printf("adress ptr1 = %p\n", ptr1);
  printf("ptr1 = %d\n", *(ptr1+1));
  printf("adress ptr1 = %p\n", ptr1);
  printf("ptr1 = %d\n", *(++ptr1));
  printf("adress ptr1 = %p\n", ptr1); 
  printf("ptr1 = %d\n", *(ptr1));
  printf("adress ptr1 = %p\n", ptr1);

  printf("tab2 = %d\n", *tab2);
  printf("tab2 = %d\n", *(tab2+1));
  /* odkumentuj i przeanalizuj działanie */
  /* printf("tab2 = %d\n", *(tab2++)); */
  /* printf("ptr1 = %d\n", *(++(&ptr1))); */
  printf("tab2 = %d\n", *(tab2+2));

  printf("tab2 = %d\n", tab2[0]);
  printf("tab2 = %d\n", tab2[1]);
  printf("tab2 = %d\n", tab2[2]);
 
/* ** Zadanie 1: przeanalizuj kod, wykryj błędy i wyjaśnij ich przyczynę -
      odnieś się do komunikatów od kompilatora: */
 /* void printtab(int n){ */
 /*   static int tab[100*n];  */
 /* } */

 /* int main() */
 /* { */
 /*   int a[5] = {1,2,3,4,5}; */
 /*   int b[] = {6,7,8,9,0}; */
 /*   int c[5] = {0,2,3,4,5,6} */
 /*   int *ptr = a; */

 /*   a = b; */
 /*   b = ptr; */
      
 /* } */

/* ** Zadanie 2: napisz program obliczający średnią arytmetyczną i wariancję z
      wygenerownych losowo liczb z zakresu 0-1 przechowywanych w 100 elementowej
      tablicy typu float. Lczby mają być tak wygenerowane, aby podlegały
      rozkładowi normalnemu. */
 
/* ** Zadanie 3: napisz program wyszukujący wartość maksymalną i minimalną w
      tablicy z zadania 2.*/

/* ** Zadanie 4: napisz program drukujący histogram na postawie zawartości
      tablicy z zadania 2. W razie potrzeby zwiększ wymiar tablicy. */

 return 0;
}
