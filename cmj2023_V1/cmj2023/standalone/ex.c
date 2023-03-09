#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////// main  
int main()
{
int i;
FILE *fic=NULL;
char ch[20];

fic=fopen("../web/data/f.js","r");
if (fic!=NULL)
    {
        printf("\n  OK ");
        fscanf(fic,"%s",ch);
        printf("\n *%s*", ch);
        fclose(fic);
    }
else printf("\n NIET");

return 0;
}
