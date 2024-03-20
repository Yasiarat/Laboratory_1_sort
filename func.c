#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ����� �������
void choosen(double *mas, int n) {
    int  i = 0, j = 0, mn = 0;
    double tem = 0, a, b;
    // ������� ��� �������, ������ � ������, � �.�. �� ���������� ������
    for (i = 0; i < n; i++) {
        mn = i;

        for (j = i + 1; j < n; j++) {
            a = abs(mas[mn]);
            b = abs(mas[j]);
            if (a < b)
                mn = j;
        }
        tem = mas[mn];
        mas[mn] = mas[i];
        mas[i] = tem;
    }
}

// ����������� �����
void recursia(double *mas, int n) {
    int i = 0;
    int j = n - 1;
    double mid = mas[n / 2];// ��������� ������ �� ���

    while (i <= j) { // ���� �� ����� �� �������, ���������� � ��� �������� � ����� ������
        while(abs(mas[i]) > abs(mid)) { // ���� ����� < �������, ���������������
            i++;
        }
        while(abs(mas[j]) < abs(mid)) { // ���� ����� > �������, ���������������
            j--;
        }
        if (i <= j) { // ������ ������� ��������� ��������
            double tmp = mas[i];
            mas[i] = mas[j];
            mas[j] = tmp;
            i++;
            j--;
        }
    }

    // ���������� ����������, ���� � ����� ������ �� ����� �� �����
    if (j > 0) {
        recursia(mas, j + 1);
    }
    if (i < n) {
        recursia(&mas[i], n - i);
    }
}

int main(void)
{
    double *mas;
    int n = 0, i = 0;

    scanf("%d", &n);
    mas = (double*)malloc(n * sizeof(double));

    for (i = 0; i < n; i++) {
        scanf("%lf", &mas[i]);
    }
    //choosen(mas, n);
    recursia(mas, n);

   for (i = 0; i < n; i++) {
       printf("%lf\n", mas[i]);
    }

    free(mas);
    return 0;
}
