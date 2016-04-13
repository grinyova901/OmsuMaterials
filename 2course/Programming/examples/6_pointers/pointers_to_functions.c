/*
    В языке C есть возможность определять указатели не только на данные (переменные указанного типа),
    но и на функции. Для справки: каждая объявленная в программе функция занимает некоторую область
    памяти, в которой располагаются все инструкции тела функции. Укзатель-на-функцию как раз содержит
    в себе адрес первого байта этих инструкций.

    Синтаксис объявления указателя на функцию следующий:
        <возращаемое_значение> (*<название_указателя>)(<список аргументов>);
    Здесь:
        -> <возращаемое_значение> и <список аргументов> - аналогичны объявлению функции
        -> круглые скобки вокруг знака указателя и его названия - обязательны.
    К примеру:
        // объявлен указатель на функцию, которая принимает два аргумента типа int и также возращает значение того же типа
        int (*p_func)(int, int);

        // Обратите внимание, что при пропуске скобок мы получаем простое объявление функции:
        int *p_func2(int, char); // на самом деле тут объявлена функция с названием p_func2, которая
                                 // принимает два аргумента - целое число (int) и символ (char), а возращает
                                 // указатель на целое число (int*)

    Для того, чтобы начать использовать p_func, нам нужна подходящая функция:
        // первая функция, подходящая под шаблон указателя. Складывает два числа, просто для примера
        int add_numbers(int num1, int num2)
        {
            return num1 + num2;
        }

        // вторая.
        int multiply_numbers(int num1, int num2)
        {
            return num1 * num2;
        }

        // теперь можно воспользоваться указателем p_func
        p_func = add_numbers; // устанавливаем переменную p_func равной первому байту инструкций функции add_numbers
        printf("2 + 8 = %d", p_func(2, 8)); // сделан вызов функции add_numbers через указатель

        // тот же указатель можно переназначать на другую функцию
        p_func = &multiply_numbers; // второй вариант синтаксиса присваивания. По существу, знак '&' не особо нужен,
                                    // но иногда его используют для подчёркивания того, что p_func - указатель на функцию
                                    // Различий с присваиванием "p_func = multiply_numbers;" используемый вариант не имеет
        printf("5 * 15 = %d", p_func(5, 15)); // сделан вызов функции multiply_numbers через указатель

    Для указателей на функции запрещены любые арифметические операции.
    Также нельзя присваивать указателю функцию, которая имеет другую сигнатуру (список аргументов и/или их типы)

    Полезным свойством является то, что указатель на функцию может быть использован как аргумент в другой функции:
        // Определяем функцию, которая принимает два аргумента: целое число и указатель на функцию
        void do_something(int num, int (*pf)(int, int)
        {
            printf("The result of operation is: %d", pf(num, num));
        }

        // и вызов можно сделать так:
        do_something(9, p_func); // p_func - указатель, определённый выше.

        // а можно так:
        do_something(9, add_numbers); // в явном виде используем название функции add_numbers
*/

#include <stdio.h>
#include <math.h>

void calculate_exp(double num)
{
    printf("exp of %lf is %lf\n", num, exp(num));
}

void calculate_log10(double num)
{
    if (num > 0.0) {
       printf("log10 of %lf is %lf\n", num, log10(num));
    } else {
        printf("Could not calculate log10 for negative or zero value\n");
    }
}

void calculate_abs(double num)
{
    printf("abs value of %lf is %lf\n", num, fabs(num));
}

int main(void)
{
    char func_symb;
    double number;

    printf("Enter real number: ");
    scanf("%lf", &number);
    getchar(); // читаем из стандартного потока ввода символ переноса строки ('\n', появляется в нём после нажатия клавиши Enter)

    printf("Choose the function to calculate\n(e - exponent, l - log10, other symbol - abs): ");
    scanf("%c", &func_symb);

    // объявляем указатель на функцию
    void (*p_func)(double);

    // по ведённому пользователем символу выбираем функцию
    switch (func_symb) {
        case 'e':
            p_func = calculate_exp;
            break;
        case 'l':
            p_func = calculate_log10;
            break;
        default:
            p_func = calculate_abs;
            break;
    }

    // вызываем выбранную функцию через указатель
    p_func(number);

    return 0;
}
