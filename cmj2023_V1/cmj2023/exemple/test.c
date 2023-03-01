#include <stdio.h>
#include <string.h>

int main() {
    char str[100];
    printf("Entrez une chaîne de caractères : ");
    fgets(str, sizeof(str), stdin);
    int len = strlen(str);
    if (len >= 3) { // vérifier qu'il y a suffisamment de caractères pour supprimer le deuxième avant-dernier
        str[len-3] = '\0'; // mettre le troisième caractère avant la fin à zéro pour supprimer le deuxième avant-dernier
    }
    printf("La chaîne sans le deuxième avant-dernier caractère est : %s\n", str);
    return 0;
}