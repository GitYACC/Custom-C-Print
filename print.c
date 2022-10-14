#include "print.h"

char specifiers[REG_SIZE];
int spec_amt = 0;
char *(*function_registry[REG_SIZE])(void *);

void register_fmt(char type, char *(*func)(void *)) {
    specifiers[spec_amt++] = type;
    int hash = (int)type << 20;
    function_registry[hash % REG_SIZE] = func;
}


void print(const char *fmt, ...) {
/* BASE SPECIFIERS
%i = int
%I = unsigned int
%f = float
%d = double
%D = long double
%c = char
%C = unsigned char
%l = long
%L = unsigned long
%x = short
%X = unsigned short
%s = string
%p = pointer
*/
    int total = 0;
    for(int _ = 0; _ < strlen(fmt); _++) {
        if(fmt[_] == '%') {
            if(fmt[_ + 1] == '%')
                continue;
            else
                total++;
        }
    }
    va_list args;
    va_start(args, total);

    int fspec = 0;
    char *fmt_r = malloc(sizeof(char *) * REG_SIZE);
    while(*fmt) {
        if(*fmt == '%') {
            fspec++;
            fmt++;
        }

        if(fspec) {
            fspec--;
            switch(*fmt) {
                case 'i':
                    asprintf(&fmt_r, "%s%d", fmt_r, va_arg(args, int));
                    break;
                case 'I':
                    asprintf(&fmt_r, "%s%d", fmt_r, va_arg(args, unsigned int));
                    break;
                case 'f':
                    asprintf(&fmt_r, "%s%f", fmt_r, va_arg(args, float));
                    break;
                case 'd':
                    asprintf(&fmt_r, "%s%f", fmt_r, va_arg(args, double));
                    break;
                case 'D':
                    asprintf(&fmt_r, "%s%Lf", fmt_r, va_arg(args, long double));
                    break;
                case 'c':
                    asprintf(&fmt_r, "%s%c", fmt_r, va_arg(args, char));
                    break;
                case 'C':
                    asprintf(&fmt_r, "%s%c", fmt_r, va_arg(args, unsigned char));
                    break;
                case 'l':
                    asprintf(&fmt_r, "%s%l", fmt_r, va_arg(args, long));
                    break;
                case 'L':
                    asprintf(&fmt_r, "%s%lu", fmt_r, va_arg(args, unsigned long));
                    break;
                case 'x':
                    asprintf(&fmt_r, "%s%d", fmt_r, va_arg(args, short));
                    break;
                case 'X':
                    asprintf(&fmt_r, "%s%hu", fmt_r, va_arg(args, unsigned short));
                    break;
                case 's':
                    asprintf(&fmt_r, "%s%s", fmt_r, va_arg(args, char *));
                    break;
                case 'p':
                    asprintf(&fmt_r, "%s%p", fmt_r, va_arg(args, void *));
                    break;
                case '%':
                    asprintf(&fmt_r, "%s%%", fmt_r);
                    break;
                default: {
                    int hash = (int)(*fmt) << 20;
                    const char *temp = function_registry[hash % REG_SIZE](va_arg(args, void *));
                    asprintf(&fmt_r, "%s%s", fmt_r, temp);
                }
            }
        } else {
            asprintf(&fmt_r, "%s%c", fmt_r, *fmt);
        }
        fmt++;
    }

    va_end(args);
    printf("%s", fmt_r);
    free(fmt_r);
}