#ifndef STRUCTURE_H
#define STRUCTURE_H


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


typedef struct {
    char identifiant[20];
    char nom[100];
    char prenom[100];
    double montant;
    double nouveauSolde;
    char type[100];
    Date dateTransaction;
    char motif[100];  // Date de la transaction
} Transaction;


typedef struct {
    int empno;         // Num�ro employ�
    char NOM[50];      // Nom de l'employ�
    char prenom[50];   // Pr�nom de l'employ�
    Date naissance;    // Date de naissance
    char adresse[100]; // Adress
    char tel[100];     // T�l�phone
    char mot_passe[100]; // Mot de passe
    char email[100];
} employe;

typedef struct {
    char identifiant[6];     // Identifiant (5 chiffres + '\0')
    char code[7];            // Code personnel (4 � 6 chiffres + '\0')
    char nom[100];           // Nom de l'utilisateur
    char prenom[100];        // Pr�nom de l'utilisateur
    char tele[20];           // Num�ro de t�l�phone
    char ville[50];          // Ville de r�sidence
    char email[100];         // Email (v�rifi� pour se terminer par '@gmail.com')
    char sex[2];             // Sexe ('M' ou 'F' + '\0')
    char numeroCompte[17];   // Num�ro de compte (16 chiffres + '\0')
    int date_naissance1[3];
    Date date_naissance[3] ;   // Date de naissance (jour, mois, ann�e)
    double solde;            // Solde initial (0.0)
    char rib[40];            // RIB complet (code banque, code ville, num�ro de compte)
} utilisateur;


#endif // STRUCTURE_H

