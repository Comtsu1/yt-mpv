#include <stdio.h>
#include <stdbool.h>

#define __IS_MATCH_PRINT__ 0

bool is_match(const char *const needle, const char *const *const stack)
{ // sees if a word is contained in an array or words
    int cnt = 0;    
    bool found_match = 1;
    const char *p1, *p2;

    while(stack[cnt] != NULL)
    {   found_match = 1;

        // copy of needle
        p1 = needle;
        p2 = stack[cnt];

        if(__IS_MATCH_PRINT__) printf("n:%s, s:%s\n", p1, p2);
        if(__IS_MATCH_PRINT__) printf("\t%d\n", *p1 && *p2);
        
        // Check if strings are empty (prob something went wrong) FIXME later
        if(!(*p1 && *p2)) return 0;

        // See if we are the end of
        // our strings
        while(*p1 && *p2)
        {
            if(__IS_MATCH_PRINT__) printf("\t%d(%c),%d(%c)\n", *p1, *p1, *p2, *p2);
            if(*p1 != *p2) found_match = 0;
            p1++;
            p2++;
        } 

        // Check for tralling characters
        // Ex: neddle: he, stack: h
        // h == h
        // stack is now \0 so the while stops
        // but we still didnt compare 'e' from the needle
        if(*p1 || *p2) found_match = 0;

        //printf("c:%d, %d\n", *p1, *p2);

        // See if we found
        // our match
        if(found_match) return 1;
        
        // next word
        cnt++;
    }

    // No matches found
    return 0;
}
