/* ** Zadanie 2: napisz program obliczający średnią arytmetyczną i wariancję z
      wygenerownych losowo liczb z zakresu 0-1 przechowywanych w 100 elementowej
      tablicy typu float. Lczby mają być tak wygenerowane, aby podlegały
      rozkładowi normalnemu. */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

double average(const float*, const int);
double variance(const float*, const int);
float fmaxval(const float*, const int);
float fminval(const float*, const int);
int maxval(const int*, const int);
void histogram(const float*, const int);







int main() {
    int x = 0, size = 100;
    float random[100], max = 0, min = 0;
    double avg = 0.0, vrc = 0.0;

    srand((unsigned)time(NULL));
    for (x = 0 ; x < 100 ; x++) {
        random[x] = (float)((double)rand() / (double)(RAND_MAX));
    }
    avg = average(random, size);
    vrc = variance(random, size);
    max = fmaxval(random, size);
    min = fminval(random, size);

    printf("\nAverage = %lf", avg);
    printf("\nVariance = %lf", vrc);
    printf("\nMax = %lf", max);
    printf("\nMin = %lf", min);

    histogram(random, size);
}

double average(const float* random, const int size) {
    int x = 0;
    double average = 0.0;
    for (x = 0 ; x < size ; x++ ) {
        average += random[x];
    }
    average /= size;
    return (average);
}

double variance(const float* random, const int size) {
    int x = 0;
    double variance = 0.0, avg = 0.0;
    avg = average(random, size);
    for (x = 0 ; x < size ; x++) {
        variance += pow((random[x] - avg), 2);
    }
    variance /= size;
    return (variance);
}

/* ** Zadanie 3: napisz program wyszukujący wartość maksymalną i minimalną w
      tablicy z zadania 2.*/

float fmaxval(const float* random, const int size) {
    int x = 0;
    float max = 0;
    max = random[0];
    for(x = 1 ; x < size ; x++) {
        if (random[x] > max) max = random[x];
    }

    return(max);
}

float fminval(const float* random, const int size) {
    int x = 0;
    float min = 0;
    min = random[0];
    for(x = 1 ; x < size ; x++) {
        if (random[x] < min) min = random[x];
    }

    return(min);
}

int maxval(const int* random, const int size) {
    int x = 0, max = 0;
    max = random[0];
    for(x = 1 ; x < size ; x++) {
        if (random[x] > max) max = random[x];
    }

    return(max);
}







void histogram(const float* random, const int size) {
    int x = 0, y = 0, scale = 0, itmp = 0;
    double width = 0.1, tmp = 0.0;
    int hist[10];
    char histogram[12][45];

    for (x = 0 ; x < 10 ; x++) {
        hist[x] = 0;
    }

    for (x = 0 ; x < 10 ; x++) {

        for(y = 0 ; y < size ; y++) {
            if (random[y] > tmp && random[y] < (tmp + width)) {
                hist[x] += 1;
            }
        }
        tmp += width;
    }

    for(x = 0 ; x < 12 ; x++) {
        for(y = 0 ; y < 45 ; y++) {
            histogram[x][y] = ' ';
        }
    }

    scale = maxval(hist, 10) / 5;
    if (scale*10 > 99) {
        itmp = scale;
        histogram[0][2] = (char)((itmp%10)+48);
        itmp /= 10;
        histogram[0][1] = (char)((itmp%10)+48);
        itmp /= 10;
        histogram[0][0] = (char)((itmp%10)+48);
    }
    for (x = 10; x > 0; x--) {
        if(scale*x > 9) {
            itmp = scale*x;
            histogram[10-x][1] = (char)((itmp%10)+48);
            itmp /= 10;
            histogram[10-x][0] = (char)((itmp%10)+48);
        } else {
            histogram[10-x][0] = (char)((scale*x)+48);
        }
    }
    strcpy(histogram[11], " x |0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1.0 ");
    for(x = 0 ; x < 11 ; x++) {
        histogram[x][3] = '|';
    }
    for(x = 0 ; x < 12 ; x++) {
        histogram[x][44] = '|';
    }
    for(x = 0 ; x < 45 ; x++) {
        histogram[10][x] = '-';
    }


    printf("\n\n");

    for (x = 0 ; x < 10 ; x++) {
        y = 9;
        while (hist[x] / scale > 0) {
            histogram[y][x*4 + 4] = '#';
            histogram[y][x*4 + 5] = '#';
            histogram[y][x*4 + 6] = '#';
            hist[x] -= scale;
            y--;
        }
    }


    for(x = 0 ; x < 12 ; x++) {
        for(y = 0 ; y < 45 ; y++) {
            printf("%c", histogram[x][y]);
        }
        printf("\n");
    }


}