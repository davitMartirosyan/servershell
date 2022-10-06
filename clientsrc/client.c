#include "../include/servershell.h"

int main(void)
{
    while(1)
    {
        char *cmdline = readline("$: ");
        add_history(cmdline);
        printf("%s\n", cmdline);
        // lex(cmdline);
        // HTTP_send();
        // print_output();
    }
}