#include <stdio.h>
#include <wctype.h>
#include <wchar.h>
#include <locale.h>
 
int main (int argc, char *argv[]) {
    setlocale (LC_ALL, "pt_BR.UTF-8");
    wint_t wc;
    FILE *fin = fopen (argv[1], "r");
    do {
        wc = fgetwc (fin);
        if (wc <= L'~')
          wprintf(L"%lc", wc);
    } while (wc != WEOF);
    fclose (fin);
    return 0;
}