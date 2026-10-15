#ifndef afficherMenuPrincipal_H
#define afficherMenuPrincipal_H

#include <stdio.h>
#include <stdlib.h>
#include "couleur.h"
#include "admin.h"
#include "employe.h"
#include "utilisateur.h"



void asciiART() {
    printf("\n\n\n\n\n\n\n");
    printf("\t\t\t      #    #####   #     #           #####     #    #     # #   #\n");
    printf("\t\t\t     # #   #    #  #     #           #    #   # #   ##    # #  #\n");
    printf("\t\t\t    #   #  #    #  #     #           #    #  #   #  # #   # # #\n");
    printf("\t\t\t   ####### #####   ####### ********* #####  ####### #  #  # ##\n");
    printf("\t\t\t   #     # #   #   #     #           #    # #     # #   # # # #\n");
    printf("\t\t\t   #     # #    #  #     #           #    # #     # #    ## #  #\n");
    printf("\t\t\t   #     # #     # #     #           #####  #     # #     # #   #\n");

    printf("\n\n\n\t\t\t\t[");
    for (int i = 0; i < 3; i++) {
        printf("##############");
        Sleep(1000);
    }
    printf("]");
    system("cls");
    return;
}

void menuClient() {
Options options;
    char *MAIN_OPTIONS[] = {
        BOLD "SE CONNECTER",
        BOLD RED "REVENIR AU MENU PRINCIPAL",
    };
    options.title = "MENU UTILISATEUR";
    options.ops = MAIN_OPTIONS;
    options.len = sizeof(MAIN_OPTIONS) / sizeof(MAIN_OPTIONS[0]);

    int option = select_menu(options);
    switch (option) {
        case 0:{
            system("cls");
            connexionUtilisateur();
            break;}
        case 1:{
            system("cls");
            AfficherMenuPrincipale();
            break;}
    }
}

void EmployeMenuDisplay() {
    Options options;
    char *MAIN_OPTIONS[] = {
        BOLD "SE CONNECTER",
        BOLD RED "REVENIR AU MENU PRINCIPAL",
    };
    options.title = "MENU EMPLOYE";
    options.ops = MAIN_OPTIONS;
    options.len = sizeof(MAIN_OPTIONS) / sizeof(MAIN_OPTIONS[0]);

    int option = select_menu(options);
    switch (option) {
        case 0:{
            system("cls");
            connexionEmploye();
            break;}
        case 1:{
            system("cls");
            AfficherMenuPrincipale();
            break;}
    }
}

void adminMenuDisplay() {
    Options options;
    char *MAIN_OPTIONS[] = {
        BOLD "SE CONNECTER",
        BOLD RED"REVENIR AU MENU PRINCIPAL",
    };
    options.title = "MENU ADMINISTRATEUR";
    options.ops = MAIN_OPTIONS;
    options.len = sizeof(MAIN_OPTIONS) / sizeof(MAIN_OPTIONS[0]);

    int option = select_menu(options);
    switch (option) {
        case 0:{
            system("cls");
            loginAdmin();
            break;}
        case 1:{
            system("cls");
            AfficherMenuPrincipale();
            break;}
    }
}

void AfficherMenuPrincipale() {
    printf("\n\n\n\n\t\t");printf(":::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::");printf("\n");
    printf("\t\t");        printf("::                                                                   ::");printf("\n");
    printf("\t\t");        printf("::            *****************************************              ::");printf("\n");
    printf("\t\t");        printf("::            *                                       *              ::");printf("\n");
    printf("\t\t");        printf("::            *          WELCOME TO ARH BANK          *              ::");printf("\n");
    printf("\t\t");        printf("::            *                                       *              ::");printf("\n");
    printf("\t\t");        printf("::            *****************************************              ::");printf("\n");
    printf("\t\t");        printf("::                                                                   ::");printf("\n");
    printf("\t\t");        printf(":::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::");printf("\n");
    printf("\n\n\t\t");  printf("                          << LOADING >>                          ");
    printf("\n\n");
    Sleep(3000);

    Options options;
    char *MAIN_OPTIONS[] = {
        BOLD "CLIENT",
        BOLD "EMPLOYEE",
        BOLD "ADMINISTRATEUR",
    };

    options.title = "ETES VOUS UN ADMINISTRATEUR, UN EMPLOYEE OU UN CLIENT ?";
    options.ops = MAIN_OPTIONS;
    options.len = sizeof(MAIN_OPTIONS) / sizeof(MAIN_OPTIONS[0]);

    int option = select_menu(options);
    switch (option) {
    case 0:{
        system("cls");
        menuClient();
        break;}
    case 1:{
        system("cls");
        EmployeMenuDisplay();
        break;}
    case 2:{
        system("cls");
        adminMenuDisplay();
        break;}
    }
}

#endif
