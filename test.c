///
/// @author Amrit Bhogal on 2023-03-14
/// @brief 
/// @version 1.0.0
///

#include <stdio.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void sighandler(int sig)
{ exit(0); }

int main(int argc, const char *argv[], const char *envp[], const char *apple[])
{
    signal(SIGSEGV, &sighandler);
    puts("Args");
    size_t i = 0;
    for (const char *str = *argv; str; str = *++argv, i++)
        printf("\t[%zu] = %s\n", i, str);
    i = 0;
    puts("Env");
    for (const char *str = *envp; str; str = *++envp, i++)
        printf("\t[%zu] = %s\n", i, str);
    i = 0;
    puts("Apple");
    for (const char *str = *apple; str; str = *++apple, i++)
        printf("\t[%zu] = %s\n", i, str);
    i = 0;
    puts("Reading stack...");
    char c = '1';
    const char *str = &c;
    while (true) {
        str--;
        putchar(*str);
    }
}
