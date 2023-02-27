#include <stdio.h>
#include <stdlib.h>

void show_help(int all, int index, char ** buf, ...)
{ // Show help when no arguments are presented
    fprintf(stdout, "This is the help page:"
		    "\n\t-h(elp)\t\t\tHelp"
            "\n\t-d(ownload)\t\tDownloads Youtube link ID" // TODO
            "\n\t-l(ist)\t\t\tLists all videos in a directory(Default \".\")\n");
// Exit our program
// as the user didn't put enough info
// or
// wanted to see help page
    exit(EXIT_SUCCESS);
}

