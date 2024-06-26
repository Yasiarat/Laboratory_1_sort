#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <time.h>

// Параметры по умолчанию
int dim = 100; // количество элементов массива
int arr = 1; // упорядоченность входного массива
int sort = 1; // какой метод сотртировки использовать
int prnt = 0; // флаг, выводить ли массив

// счётчики
int swap = 0;// количество обменов элементов массива местами
int comp = 0;// количество сравнений элементов массива



// поиск выбором
void choosen(double *mas, int n) {
    int  i = 0, j = 0, mx = 0;
    double tem = 0, a, b;
    // находим max элемент, ставим в начало, и т.д. со следующего номера
    for (i = 0; i < n; i++) {
        mx = i;

        for (j = i + 1; j < n; j++) {
            a = fabs(mas[mx]);
            b = fabs(mas[j]);
            comp++;
            if (a < b)
                mx = j;
        }
        comp++;
        if (mx != i) {
            tem = mas[mx];
            mas[mx] = mas[i];
            mas[i] = tem;
            swap++;
        }
    }
}

// рекурсивная реализация быстрой сортировки
void recursia(double *mas, int n) {
    int i = 0;
    int j = n - 1;
    double mid = mas[n / 2];// разделяем массив на два

    while (i <= j) { // пока не дошли до медианы, сравниваем с ней элементы с обеих сторон
        while(fabs(mas[i]) > fabs(mid)) { // если число < медианы, останавливаемся
            comp++;
            i++;
        }
        comp++;

        while(fabs(mas[j]) < fabs(mid)) { // если число > медианы, останавливаемся
            comp++;
            j--;
        }
        comp++;

        if (i <= j) { // меняем местами неугодные элементы
            comp++;
            swap += (i < j) ? 1 : 0;

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

// генерация случайного числа
double g_num(void) {

    double x = 0;

    x = (rand() + 0.2352532*rand())* pow(-1, rand());
    return x; // НУЖНА ЛИ ПРОВЕРКА НА КОНЕЧНОСТЬ??? isfinite(d) ? d : 0.0;
}

// генерация массива случайных чисел
double g_mas(double* mas) {
    int i = 0;
    srand(time(NULL));// чтобы числа были разными

    for (i = 0; i < dim; i++) {
        mas[i] = g_num();
    }
}

// стартовый вывод
void start(void) {
    printf("\t\t Доброго времени суток! \n   Вы находитесь в проекте Ратовой Ярославы, студента 105 группы ВМК МГУ:\n");
    printf("\t\t 'СРАВНЕНИЕ СОРТИРОВОК' \n ");
    printf("\n");
    printf("\t Не знаете, как пользоваться? - Не проблема!\n");
    printf("  Введите '--help' или просто '-H' и Вам высветится справка.\n");
    printf("  Будьте внимательны: ключ '--help' не используется в сочетании с другими ключами!!!\n");
    printf("\n");
    printf("\tНемного о том, что происходит:\n");
    printf("  В программе реализованы две сортировки: быстрая и выбором\n");
    printf("  Здесь сортируются числа двойной точности\n");
    printf("  Числа упорядочиваются по невозрастанию модулей, т.е. при сравнении элементов не учитывается знак.\n");
    printf("  После выполнения сортировки программа выведет число сравнений и обменов элементов массива\n");

}

// справка
void help(void) {
    printf("\t\tВот справка:\n  1) --dim (-D) - размер массива. По умолчанию 100\n");
    printf("  2) --arr (-A) |1|2|3|4|- вид входного массива. По умолчанию 1\n");
    printf("\tВ качестве аргумента принимает число от 1 до 4:\n");
    printf("\t 1 - элементы упорядочены\n");
    printf("\t 2 - элементы упорядочены в обратном порядке\n");
    printf("\t 3 - случайный порядок элементов\n");
    printf("\t 4 - случайный порядок элементов, но не как в предыдущем\n");
    printf("  3) --sort (-S) |1|2| - вид сортировки. По умолчанию 1\n");
    printf("\tВ качестве аргумента принимает числа 1 или 2:\n");
    printf("\t 1 - сортировка выбором\n");
    printf("\t 2 - быстрая сортировка\n");
    printf("  4) --print (-P) |0|1| - выводит отсортированный массив. По умолчанию 0\n");
    printf("\tВ качестве аргумента принимает числа 0 или 1:\n");
    printf("\t 0 - не выводить\n");
    printf("\t 1 - вывести массив\n");
    printf("\n");
    printf("  Пример ввода:\n");
    printf("\t --dim 10 -A 2 - выполнит сортировку 10 элементов, упорядоченных по невозрастанию\n");
    printf("\n");
    printf("\t\t Пользуйтесь на здоровье!\n");
}

int main(int argc, char** argv) {
     int i;
     int fl_D = 0, fl_A = 0, fl_S = 0, fl_P = 0; // флаги задания параметров


     if(argc <= 1) {
        start(); // поздороваемся
         return 0;
     }

     if(!strcmp(argv[1], "--help") || !strcmp(argv[1], "-H")){ // если строки ровны
         help(); // выведем возможные ключи и что они делают
         return 0;
     }

    for(int i = 1 ; i < argc; i++) { // пробегаемся по всем аргументам массива

        if(!strcmp(argv[i], "--dim") || !strcmp(argv[i], "-D")){ // ключ задаёт размер входного массива
            i++;

            if(fl_D != 0) { // если дважды ввели один и тот же аргумент
                printf("  Вы ввели два одинаковых ключа! Я буду использовать последний.\n");
             }
            // если нет аргумента или он не валидный
             if ((i == argc) || (atoi(argv[i]) == 0) || (atoi(argv[i]) <= 0)) {//
                printf("  Без аргумента мне не справиться с задачей... \n Ключ '--dim' принимает в качестве аргумента натуральное число.\n");
                return 0;
            }
            fl_D = 1;
            dim = atoi(argv[i]);
        }
    // упорядоченность входного массива
        else if(!strcmp(argv[i], "--arr") || !strcmp(argv[i], "-A")){
            i++;
            if(fl_A != 0) { // если дважды ввели один и тот же аргумент
                printf("  Вы ввели два одинаковых ключа! Я буду использовать последний.\n");
             }
             // если нет аргумента или он не валидный
            if((i == argc) || (atoi(argv[i]) > 4) || (atoi(argv[i]) < 1)){
                printf("  Без аргументов мне не справиться с задачей... \n Ключ '--arr' принимает в качестве аргумента числа от 1 до 4.\n Чтобы узнать подробнее, для чего они нужны, напишите '--help' или '-H'\n");
                return 0;
            }

             fl_A = 1;
            arr = atoi(argv[i]);
        }
        // какой сортировкой воспользоваться
        else if(!strcmp(argv[i], "--sort") || !strcmp(argv[i], "-S")){
            i++;
            if(fl_S != 0) { // если дважды ввели один и тот же аргумент
                printf("  Вы ввели несколько одинаковых ключа! Я буду использовать последний.\n");
             }
             // если нет аргумента или он не валидный
            if((i == argc) || (atoi(argv[i]) > 2) || (atoi(argv[i]) < 1)){
                printf("  Без аргументов мне не справиться с задачей... \n Ключ '--sort' принимает в качестве аргумента числа от 1 или 2.\n Чтобы узнать подробнее, для чего они нужны, напишите '--help' или '-H'\n");
                return 0;
            }

             fl_S = 1;
            sort = atoi(argv[i]);
        }
        else if(!strcmp(argv[i], "--print") || !strcmp(argv[i], "-P")){
            i++;
            if(fl_P != 0) { // если дважды ввели один и тот же аргумент
                printf("  Вы ввели несколько одинаковых ключа! Я буду использовать последний.\n");
             }
             // если нет аргумента или он не валидный
            if((i == argc) || (atoi(argv[i]) > 1) || (atoi(argv[i]) < 0)){
                printf("  Без аргументов мне не справиться с задачей... \n Ключ '--sort' принимает в качестве аргумента числа от 1 или 2.\n Чтобы узнать подробнее, для чего они нужны, напишите '--help' или '-H'\n");
                return 0;
            }

             fl_P = 1;
            prnt = atoi(argv[i]);
        }
        else {
            printf("  Не знаю команды '%s'... \n  Но есть список известных мне ключей! Чтобы открыть его введите '--help' или просто '-H'\n", argv[i]);
            printf("  Будьте внимательны: ключ '--help' не используется в сочетании с другими ключами!!!\n");
            return 0;
        }

    }


    // пора воспользоваться введёнными данными

    // выделение памяти и проверка, выделилась ли она
    double *mas = (double*)calloc(dim, sizeof(double));

    if (!mas) {
        printf("  Не удалось выделить нужное количество памяти(");
        return 0;
    }

    //если массив должен быть отсортирован
    if (arr == 1) {
        for (i = dim - 1; i >= 0; i--) {
            mas[i] += dim - i;
        }
    }

    //если массив должен быть отсортирован в обратном порядке
    else if (arr == 2) {
        for (i = 1; i <= dim; i++) {
            mas[i] += i;
        }
    }
    // иначе, генерируем массив случайных чисел
    else {
       g_mas(mas);
    }


    // перейдём к сортировке
    if (sort == 1) {
        choosen(mas, dim);
    }

    else if (sort == 2) {
        recursia(mas, dim);
    }


   printf("\t Число сравнений элементов массива: %d\n", comp);
   printf("\t Число обменов элементов массива: %d\n", swap);

    if (prnt == 1) {
        if (dim >= 1000) {
            printf("  Массив слишком большой. При выводе он заполонит Вам весь экран. Поэтому я отказываюсь его печатать.\n");
            printf("  Если вам прям очень хочется посмотреть на отсортированный массив, передайте в ключ '--dim' аргумент меньше 1000");
            free(mas);
            return 0;
        }
        printf("  Отсортированный по невозрастанию модулей массив:\n");
        for (i = 0; i < dim; i++) {
            printf("%lf ", mas[i]);
        }
    }

    free(mas);
    return 0;
 }
