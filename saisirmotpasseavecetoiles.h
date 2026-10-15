#ifndef SAISIRMOTPASSEAVECETOILE_H
#define SAISIRMOTPASSEAVECETOILE_H

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <conio.h> // Pour _getch()


// Fonction pour saisir un mot de passe avec des �toiles
void saisirMotDePasse(char *mot_de_passe, int taille) {
    int i = 0;
    char c;
    while (1) {
        c = _getch(); // Lecture d'un caract�re sans affichage
        if (c == 13) { // Touche Entr�e
            break;
        } else if (c == 8) { // Touche Backspace
            if (i > 0) {
                i--;
                printf("\b \b"); // Efface une �toile affich�e
            }
        } else if (i < taille - 1) {
            mot_de_passe[i++] = c;
            printf("*"); // Affiche une �toile
        }
    }
    mot_de_passe[i] = '\0'; // Fin de la cha�ne
}


#endif // SAISIRMOTPASSEAVECETOILE_H
