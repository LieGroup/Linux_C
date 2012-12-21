/* more01.c 
 * Version: 0.1
 * read and print 24 lines then pause for a few special commands
 */
#include<stdio.h>
#include<stdlib.h>
#define PAGELINES 24
#define LINELEN 512

void show_more(FILE *);
int get_command();

int main(int argc, char *argv[])
{
    FILE *fin;

    if(argc==1) /* if no input file specified, read from stdin*/
        show_more(stdin);
    else
        while(--argc)
            if((fin = fopen(*++argv, "r")) != NULL)
            {
                show_more(fin);
                fclose(fin);
            }
            else
                exit(1);
    return 0;
}

void show_more(FILE *file)
{
    int nlines=0;
    char line[LINELEN];

    while(fgets(line, LINELEN, file))
    {
        if(nlines == PAGELINES) /* full screen?*/
        {
            int command = get_command();
            if(command==0) /* user press 'q' */
                break;
            nlines -= command; /* reset line count*/
        }

        if(fputs(line, stdout)==EOF)
            exit(1);
        nlines++;
    }
}

int get_command()
{
    int c;

    printf("\033[7m more? \033[m"); /* reverse white*/
    while((c=getchar())!=EOF)
    {
        switch(c)
        {
            case 'q':
                return 0;
            case ' ':
                return PAGELINES;
            case '\n':
                return 1;
        }
    }
    return 0;/* if EOF, stop reading*/
}
