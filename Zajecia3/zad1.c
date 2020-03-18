/* ** Zadanie 1: przeanalizuj kod, wykryj błędy i wyjaśnij ich przyczynę -
      odnieś się do komunikatów od kompilatora: */
 void printtab(int n){
   static int tab[100*n]; /* static dla VLA (VLA supportowane dopiero od C99?)*/
 }

int main()
 {
   int a[5] = {1,2,3,4,5};
   int b[] = {6,7,8,9,0};
   int c[5] = {0,2,3,4,5,6} /* brak ; na koncu, oraz zbyt dużo zadeklarowanych elementów do zbyt malej tablicy*/
   int *ptr = a;

   a = b; /* proba przypisania wskaznika tablicy do innego wskaznika tablicy? Operacja niedozwolona - aby skopiowac tablice musimy kopiowac kazdy element po kolei */
   b = ptr; /* to samo co wyzej */
	/* brak return dla funkcji typu int */
 }