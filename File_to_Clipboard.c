#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>

int main(int nof, char *files[])
{
    // File Validation:

    FILE *fp = fopen(files[1], "r");
    if(fp == NULL)
    {
        printf("\nFile not Found!\n");
        exit(1);
    }

    // Finding number of claracters in file:

    int num_of_char = 0;
    char ch;
    while(1)
    {
        ch = fgetc(fp);
        if(ch == EOF){break;}
        num_of_char++;
    }
    if(num_of_char == 0)
    {
        printf("\nFile Empty!\n");
        exit(2);
    }
    fclose(fp);

    // Putting characters in string:

    fp = fopen(files[1], "r");
    char *content = (char*)malloc(num_of_char*sizeof(char));
    for(int i = 0; i < num_of_char; i++)
    {
        *(content+i) = fgetc(fp);
    }
    *(content+num_of_char) = '\0';
    fclose(fp);

    // Putting in clipboard:

    OpenClipboard(0);
    EmptyClipboard();
    const size_t len = strlen(content)+1;
    HGLOBAL hglob = GlobalAlloc(GMEM_MOVEABLE, len);
    memcpy(GlobalLock(hglob), content, len);
    GlobalUnlock(hglob);
    SetClipboardData(CF_TEXT, hglob);
    CloseClipboard();

    printf("\n(Press any key to continue)\n");
    getch();
    printf("\nContent successfully copied to clipboard.\n");

    free(content);
    return 0;
}