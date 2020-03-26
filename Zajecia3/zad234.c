/* ** Zadanie 2: napisz program obliczający średnią arytmetyczną i wariancję z
      wygenerownych losowo liczb z zakresu 0-1 przechowywanych w 100 elementowej
      tablicy typu float. Lczby mają być tak wygenerowane, aby podlegały
      rozkładowi normalnemu. */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#define SIZE 100

void generate(float*, const int, const double, const double);
double average(const float*, const int);
double variance(const float*, const int);
float fmaxval(const float*, const int);
float fminval(const float*, const int);
int maxval(const int*, const int);
void histogram(const float*, const int);

int main() {
    int x = 0, size = SIZE;
    float random[SIZE], max = 0, min = 0;
    double avg = 0.0, vrc = 0.0;

    srand((unsigned)time(NULL));
    for (x = 0 ; x < SIZE ; x++) {
        random[x] = (float)((double)rand() / (double)(RAND_MAX));
    }
    avg = average(random, size);
    vrc = variance(random, size);
    generate(random, size, avg, vrc);
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

void generate(float* random, const int size, const double avg, const double vrc) {
    int i = 0;
    double x = 0.0, y = 0.0, s = 0.0, f = 0.0;

    for(i = 0 ; i < size/2 ; i += 2) {
        do {
            x = rand() / (double) RAND_MAX;
            y = rand() / (double) RAND_MAX;
            s = x * x + y * y;
        } while (s >= 1.0 || s == 0.0);
        f = sqrt(-2.0 * log(s) / s);

        random[i] = avg + vrc * f * x;
        random[i + 1] = avg - vrc * f * y;
    }
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
    int x = 0, y = 0, scale = 0, itmp = 0, expval = 0;
    double width = 0.1, tmp = 0.0;
    int histcol[10];
    char histogram[12][50];

    for (x = 0; x < 10; x++) {
        histcol[x] = 0;
    }

    for (x = 0; x < 10; x++) {

        for (y = 0; y < size; y++) {
            if (random[y] > tmp && random[y] < (tmp + width)) {
                histcol[x] += 1;
            }
        }
        tmp += width;
    }

    for (x = 0; x < 12; x++) {
        for (y = 0; y < 50; y++) {
            histogram[x][y] = ' ';
        }
    }

    scale = (maxval(histcol, 10) / 10);
    for( x = 10 ; x > 0 ; x--) {
        y = 10;
        expval = 0;
        while ((scale * x) / y >= 1) {
            expval++;
            y *= 10;
        }
        itmp = (int)((scale * x) / pow(10, expval - 2));
        /*  printf("\n\n%d\n\n", itmp); */
        histogram[10 - x][3] = (char) (((int) itmp % 10) + 48);
        itmp /= 10;
        histogram[10 - x][2] = (char) (((int) itmp % 10) + 48);
        itmp /= 10;
        histogram[10 - x][0] = (char) (((int) itmp % 10) + 48);
        if (expval / 10) {
            histogram[10 - x][6] = (char) ((expval % 10) + 48);
            expval /= 10;
            histogram[10 - x][5] = (char) ((expval % 10) + 48);
        } else {
            histogram[10 - x][5] = (char) ((expval % 10) + 48);
        }
    }
    for(x = 0 ; x < 12 ; x++) {
        histogram[x][1] = '.';
        histogram[x][4] = 'e';
        histogram[x][7] = '|';
        histogram[x][49] = '|';
    }
    for(x = 0 ; x < 50 ; x++) {
        histogram[10][x] = '-';
    }
    strcpy(histogram[11], "   x   | 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1.0");
    for (x = 0 ; x < 10 ; x++) {
        y = 9;
        while (histcol[x] / scale > 0) {
            histogram[y][x*4 + 9] = '#';
            histogram[y][x*4 + 10] = '#';
            histogram[y][x*4 + 11] = '#';
            histcol[x] -= scale;
            y--;
        }
    }

    printf("\n\n");
    for(x = 0 ; x < 12 ; x++) {
        for(y = 0 ; y < 50 ; y++) {
            printf("%c", histogram[x][y]);
        }
        printf("\n");
    }

}