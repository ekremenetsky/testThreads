#include <stdio.h>

void f(int a) {
        printf("f function, a = %d\n", a);
}

void g(int b) {
        printf("g function, b = %d\n", b);
}


int main (int argc, char *argv[]) {

    void (*pf)(int) = &f;// Объявление сообщает компилятору,
                         // что pf - это указатель на фукцию
                         // с одним аргументом типа int и
                         // возвращает тип void (ничего не
                         // возвразщает)
    pf(10); // Вызывается f(10)

    pf = &g;
    pf(20); // Вызывается g(20)

    return 0;
}
