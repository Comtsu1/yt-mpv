#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void download_video(int all, int index, char **buf, ...)
{ // Downloads selected videos (through ID link)
  // TODO
    FILE *pipe;
    pipe = popen("mpv", "r");
    // see if we didn't open the file correctly
    if(pipe == NULL)
    {
        fprintf(stderr, "\n%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    exit(0);
    printf("%s", pipe);

    char ch;

    while( (ch = fgetc(pipe)) != EOF)
        putchar(ch);

    // close our current FILE
    pclose(pipe);
}
