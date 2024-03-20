#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
#define ABS(x) (x >= 0) ? (x) : -(x)

// Параметры по умолчанию
int size = 0; // количество элементов массива




// поиск выбором
void choosen(double *mas, int n) {
    int  i = 0, j = 0, mn = 0;
    double tem = 0, a, b;
    // находим мин элемент, ставим в начало, и т.д. со следующего номера
    for (i = 0; i < n; i++) {
        mn = i;

        for (j = i + 1; j < n; j++) {
            a = fabs(mas[mn]);
            b = fabs(mas[j]);
            if (a < b)
                mn = j;
        }
        tem = mas[mn];
        mas[mn] = mas[i];
        mas[i] = tem;
    }
}

// рекурсивный поиск
void recursia(double *mas, int n) {
    int i = 0;
    int j = n - 1;
    double mid = mas[n / 2];// разделяем массив на два

    while (i <= j) { // пока не дошли до медианы, сравниваем с ней элементы с обеих сторон
        while(fabs(mas[i]) > fabs(mid)) { // если число < медианы, останавливаемся
            i++;
        }
        while(fabs(mas[j]) < fabs(mid)) { // если число > медианы, останавливаемся
            j--;
        }
        if (i <= j) { // меняем местами неугодные элементы
            double tmp = mas[i];
            mas[i] = mas[j];
            mas[j] = tmp;
            i++;
            j--;
        }
    }

    // рекурсивно продолжаем, пока с обеих сторон не дойдём до конца
    if (j > 0) {
        recursia(mas, j + 1);
    }
    if (i < n) {
        recursia(&mas[i], n - i);
    }
}

// виды сравнения входных данных
// возрастание
int increase(double x, double y) {
    return (x > y) ? 1 : (x < y ? -1 : 0);
}
//убывание
int decrease(double x, double y) {
    return (x > y) ? -1 : (x < y ? 1 : 0);
}
// возрастание по модулю
int inc_abs(double x, double y) {
    return increase(fabs(x), fabs(y));
}
// убывание по модулю
int dec_abs(double x, double y) {
    return decrease(fabs(x), fabs(y));
}


// генерация случайного числа
double g_num(void) {
    double x = 0;
    double* p = &x;
    int i = 0;

    for (i = 0; i  < 8; i++) {
        *(p + i) = rand();
        return x; // НУЖНА ЛИ ПРОВЕРКА НА КОНЕЧНОСТЬ??? isfinite(d) ? d : 0.0;
    }
}

//
double g_mas(double* mas) {
    int i = 0;
    srand(time(NULL));// чтобы числа были разными

    for (i = 0; i < size; i++) {
        mas[i] = g_num();
    }
}

//
void start(void) {
    printf("Использование : \n\t --help or\n\t --n [a] --r [min] [max] --op 0|1|2|3\n");
}

void help(void) {
    printf("cправка.\n");
}

int main(int argc, char **argv) {
     int *a, *b; float *c;  // указатели на массив
     int n, op, min, max; // параметры
     int fl_n = 0, fl_r = 0, fl_op = 0; // флаги задания параметров


     if(argc <= 1) {
        start();
         //printf("Использование : \n\t%s --help or\n\t%s --n [a] --r [min] [max] --op 0|1|2|3\n", argv[0],argv[0]);
         return 0;
     }

     if(!strcmp(argv[1], "--help")){ // если строки ровны
         help();
         return 0;
     }

    for(int i = 1 ; i < argc; i++) { // пробегаемся по всем аргументам массива

        if(!strcmp(argv[i], "--n")){
            fl_n = 1;
            if((i+1 > argc-1) || (sscanf(argv[i+1], "%d", &n) != 1)) { // если аргументов недостаточно или он не целый
                printf("'--n' параметр требует целочисленного аргумента\n");
                return 0;
             }
        }
    // если есть доп параметры
        if(!strcmp(argv[i], "--r")){
            fl_r = 1;
            if(i+1>argc-1 || sscanf(argv[i+1], "%d", &min) != 1 || i+2>argc-1 || sscanf(argv[i+2], "%d", &max) != 1){
                printf("'--r' параметр требует пару целочисленных аргументов\n");
                return 0;
            }
        }

        if(!strcmp(argv[i], "--op")){
            fl_op = 1;
            if(i+1>argc-1 || sscanf(argv[i+1], "%d", &op) != 1 ) {
                printf("'--op' параметр требует аргумента 0|1|2|3\n");
                return 0;
             }
        }

    }


    if(fl_n == 0 & fl_r == 0 & fl_op != 0){
        n = 10;
        min = 0;
        max = 100;
        printf("По умолчанию: n = %d   min, max = %d, %d \n",n,min,max);
        printf("Задано: ор = %d \n", op);
    }else if(fl_n == 0 & fl_r != 0 & fl_op == 0){
        n = 10;
        op = 0;
        printf("По умолчанию: n = %d   op = %d \n",n,op);
        printf("Задано: min, max = %d, %d \n",min,max);
    }else if(fl_n != 0 & fl_r == 0 & fl_op == 0){
        op = 0;
        min = 0;
        max = 100;
        printf("По умолчанию: op = %d   min, max = %d, %d \n",op,min,max);
        printf("Задано: n = %d \n",n);
    }else if(fl_n == 0 & fl_r != 0 & fl_op != 0){
        n = 10;
        printf("По умолчанию: n = %d \n",n);
        printf("Задано: ор = %d    min, max = %d, %d \n", op,min,max);
    }else if(fl_n != 0 & fl_r != 0 & fl_op == 0){
        op = 0;
        printf("По умолчанию: op = %d \n",op);
        printf("Задано: n = %d  min, max = %d, %d \n",n,min,max);
    }else if(fl_n != 0 & fl_r == 0 & fl_op != 0){
        min = 0;
        max = 100;
        printf("По умолчанию: min, max = %d, %d \n",min,max);
        printf("Задано: n = %d   op = %d \n",n,op);
    }else if(fl_n != 0 & fl_r != 0 & fl_op != 0){
        printf("Задано: n = %d   op = %d   min, max = %d, %d \n",n,op,min,max);
    }

    // Выделение памяти
    a = (int*)malloc(n * sizeof(int));
    b = (int*)malloc(n * sizeof(int));
    c = (float*)calloc(n , sizeof(float));

    srand(time(NULL));
    for (int j = 0; j<n; j++){
        a[j] = rand()%(max - min + 1) + min;
        b[j] = rand()%(max - min + 1) + min;
        if(op == 0){
            c[j] = a[j] + b[j];
        }else if(op == 1){
            c[j] = a[j] - b[j];
        }else if(op == 2){
            c[j] = a[j] * b[j];
        }else if(op == 3){
            c[j] = (float)a[j] / b[j];
        }else{
            printf("Код операции задан неверно ! \n");
            return 0;
        }

        printf("a: %d ", a[j]);
        printf("b: %d ", b[j]);
        printf("c: %g \n", c[j]);
    }

     free(a);
     free(b);
     free(c);
     return 0;
 }
