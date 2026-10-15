#ifndef UTILISATEUR_H
#define UTILISATEUR_H

#include <stdlib.h>
#include <ctype.h>

#include "structure.h"
#include "date.h"
#include "historiqueTransaction.h"
#include "employe.h"
#include "couleur.h"
#include "revenir.h"
#include "saisirmotpasseavecetoiles.h"


void afficherMenuUtilisateur();

int verifierIdentifiantsUtilisateur(const char *identifiant, const char *mot_de_passe, utilisateur *utilisa) {
    FILE *fichier = fopen("utilisateurs.dat", "rb");
    if (fichier == NULL){
        printf("Erreur : Impossible d'ouvrir le fichier des utilisateurs.\n");
        return 0;

  }
    utilisateur temp;
    while (fread(&temp, sizeof(utilisateur), 1, fichier) == 1) {
        if (strcmp(temp.identifiant, identifiant) == 0 && strcmp(temp.code, mot_de_passe) == 0) {
            *utilisa = temp;
            fclose(fichier);
            return 1; // Connexion r�ussie
        }
    }

    fclose(fichier);
    return 0; // �chec de la connexion
}

void connexionUtilisateur() {
    SetConsoleOutputCP(CP_UTF8);
    char identifiant[10], mot_de_passe[10];
    utilisateur utilisa;

    // Calcul du nombre d'espaces pour centrer
    int center_padding = 20; // Ajustez ce nombre pour le centrage
    printf("\n%*s╔════════════════════════════════════════╗\n", center_padding, "");
    printf("%*s║       🌟 Connexion Utilisateur 🌟      ║\n", center_padding, "");
    printf("%*s╚════════════════════════════════════════╝\n", center_padding, "");

    printf("\n%*s╔════════════════════════════════════════╗\n", center_padding, "");
    printf("%*s║ Entrez votre identifiant               ║\n", center_padding, "");
    printf("%*s╚════════════════════════════════════════╝\n", center_padding, "");
    printf("%*s➤ Réponse : ", center_padding, "");
    scanf("%s", identifiant);

    // Saisie sécurisée du mot de passe avec des étoiles
    printf("\n%*s╔════════════════════════════════════════╗\n", center_padding, "");
    printf("%*s║ Entrez votre mot de passe              ║\n", center_padding, "");
    printf("%*s╚════════════════════════════════════════╝\n", center_padding, "");
    printf("%*s➤ Réponse : ", center_padding, "");
    saisirMotDePasse(mot_de_passe, sizeof(mot_de_passe));

    // Vérification des identifiants
    if (verifierIdentifiantsUtilisateur(identifiant, mot_de_passe, &utilisa)) {
        printf("\n\n%*s╔════════════════════════════════════════╗\n", center_padding, "");
        printf("%*s║       ✅ Connexion réussie !           ║\n", center_padding, "");
        printf("%*s╚════════════════════════════════════════╝\n", center_padding, "");
        printf("\n%*sBienvenue, %s %s !\n", center_padding, "", utilisa.nom, utilisa.prenom);
        Sleep(2000);
        afficherMenuUtilisateur();
    } else {
        printf("\n\n%*s╔════════════════════════════════════════╗\n", center_padding, "");
        printf("%*s║ ❌ Identifiant ou mot de passe incorrect. ║\n", center_padding, "");
        printf("%*s╚════════════════════════════════════════╝\n", center_padding, "");
    }
}


long trouverUtilisateur(FILE *fp, const char *identifiant, const char *code) {
    utilisateur user;
    long position = 0;

    while (fread(&user, sizeof(utilisateur), 1, fp)) {
        if (strcmp(user.identifiant, identifiant) == 0 && strcmp(user.code, code) == 0) {
            return position;
        }
        position++;
    }

    return -1; // Utilisateur�non�trouv�
}

void chercherUtilisateur() {
    SetConsoleOutputCP(CP_UTF8);
    FILE *fp;
    utilisateur usr;
    char identifiantCherche[6];
    int trouve = 0;

    // Ouverture du fichier utilisateurs.dat
    fp = fopen("utilisateurs.dat", "rb");
    if (fp == NULL) {
        printf("\n\t\t\t\t\t╔════════════════════════════════════════╗\n");
        printf("\t\t\t\t\t║   ❌ Erreur : Impossible d'ouvrir le fichier. ║\n");
        printf("\t\t\t\t\t╚════════════════════════════════════════╝\n");
        return;
    }

    // Demander l'identifiant de l'utilisateur
    printf("\n\t\t\t\t\t╔════════════════════════════════════════╗\n");
    printf("\t\t\t\t\t║     🔍 Recherche d'un utilisateur      ║\n");
    printf("\t\t\t\t\t╚════════════════════════════════════════╝\n");

    printf("\n\t\t\t\t\t╔════════════════════════════════════════╗\n");
    printf("\t\t\t\t\t║ Entrez l'identifiant (5 chiffres) :    ║\n");
    printf("\t\t\t\t\t╚════════════════════════════════════════╝\n");
    printf("\t\t\t\t\t➤ Réponse : ");
    scanf("%5s", identifiantCherche);

    // Parcourir le fichier pour rechercher l'utilisateur
    while (fread(&usr, sizeof(utilisateur), 1, fp)) {
        if (strcmp(usr.identifiant, identifiantCherche) == 0) {
            trouve = 1;

            // Affichage des informations de l'utilisateur trouvé
            printf("\n\t\t\t\t\t╔════════════════════════════════════════╗\n");
            printf("\t\t\t\t\t║   ✅ Utilisateur trouvé !              ║\n");
            printf("\t\t\t\t\t╚════════════════════════════════════════╝\n");

            printf("\n\t\t\t\t\t╔═════════════════════════════════════════════╗\n");
            printf("\t\t\t\t\t║      Informations de l'utilisateur          ║\n");
            printf("\t\t\t\t\t╠═════════════════════════════════════════════╣\n");
            printf("\t\t\t\t\t║ Identifiant       : %-20s    ║\n", usr.identifiant);
            printf("\t\t\t\t\t║ Nom               : %-20s    ║\n", usr.nom);
            printf("\t\t\t\t\t║ Prénom            : %-20s    ║\n", usr.prenom);
            printf("\t\t\t\t\t║ Téléphone         : %-20s    ║\n", usr.tele);
            printf("\t\t\t\t\t║ Ville             : %-20s    ║\n", usr.ville);
            printf("\t\t\t\t\t║ Email             : %-20s    ║\n", usr.email);
            printf("\t\t\t\t\t║ Sexe              : %-20s    ║\n", usr.sex);
            printf("\t\t\t\t\t║ Numéro de compte  : %-20s    ║\n", usr.numeroCompte);
            printf("\t\t\t\t\t║ RIB               : %-20s║\n", usr.rib);
            printf("\t\t\t\t\t║ Date de Naissance : %02d/%02d/%04d              ║\n",
                   usr.date_naissance1[0], usr.date_naissance1[1], usr.date_naissance1[2]);
            printf("\t\t\t\t\t║ Solde             : %.2f MAD             ║\n", usr.solde);
            printf("\t\t\t\t\t╚═════════════════════════════════════════════╝\n");
            break;
        }
    }

    // Si aucun utilisateur n'a été trouvé
    if (!trouve) {
        printf("\n\t\t\t\t\t╔════════════════════════════════════════╗\n");
        printf("\t\t\t\t\t║   ❌ Utilisateur introuvable.          ║\n");
        printf("\t\t\t\t\t╚════════════════════════════════════════╝\n");
    }

    fclose(fp); // Fermer le fichier
}

void changerMotDePasse() {
    SetConsoleOutputCP(CP_UTF8);
    char identifiant[6];
    char codeActuel[7];
    char nouveauCode[7];
    char confirmationCode[7];
    long position;
    FILE *fp;

    // Ouverture du fichier en mode lecture et écriture binaire
    fp = fopen("utilisateurs.dat", "r+b");
    if (fp == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }

    // Saisie de l'identifiant
    printf("\n\t\t\t\t╔════════════════════════════════════════╗\n");
    printf("\t\t\t\t║   🌟 Changement de Mot de Passe 🌟     ║\n");
    printf("\t\t\t\t╚════════════════════════════════════════╝\n");

    do {
        printf("\n\t\t\t\t╔════════════════════════════════════════╗\n");
        printf("\t\t\t\t║ Entrez votre identifiant (5 chiffres) :║\n");
        printf("\t\t\t\t╚════════════════════════════════════════╝\n");
        printf("\t\t\t\t➤ Réponse : ");
        scanf("%5s", identifiant);

        // Vérifier que tous les caractères sont des chiffres
        int valide = 1;
        for (int i = 0; i < 5; i++) {
            if (!isdigit(identifiant[i])) {
                valide = 0;
                break;
            }
        }

        if (strlen(identifiant) != 5 || !valide) {
            printf("\n\t\t\t\t⚠️ Identifiant invalide. Il doit contenir exactement 5 chiffres.\n");
        } else {
            break; // Identifiant valide
        }
    } while (1);

    // Saisie du code actuel
    do {
        printf("\n\t\t\t\t╔════════════════════════════════════════╗\n");
        printf("\t\t\t\t║ Entrez votre mot de passe actuel       ║\n");
        printf("\t\t\t\t╚════════════════════════════════════════╝\n");
        printf("\t\t\t\t➤ Réponse : ");
        scanf("%6s", codeActuel);

        // Vérifier que tous les caractères sont des chiffres
        int valide = 1;
        int longueur = strlen(codeActuel);
        for (int i = 0; i < longueur; i++) {
            if (!isdigit(codeActuel[i])) {
                valide = 0;
                break;
            }
        }

        if (strlen(codeActuel) < 4 || strlen(codeActuel) > 6 || !valide) {
            printf("\n\t\t\t\t⚠️ Code actuel invalide. Il doit contenir entre 4 et 6 chiffres.\n");
        } else {
            break; // Code actuel valide
        }
    } while (1);

    // Recherche de l'utilisateur
    position = trouverUtilisateur(fp, identifiant, codeActuel);
    if (position == -1) {
        printf("\n\t\t\t\t⚠️ Identifiant ou mot de passe incorrect.\n");
        fclose(fp);
        return;
    }

    // Saisie du nouveau mot de passe
    do {
        printf("\n\t\t\t\t╔════════════════════════════════════════╗\n");
        printf("\t\t\t\t║ Entrez votre nouveau mot de passe      ║\n");
        printf("\t\t\t\t╚════════════════════════════════════════╝\n");
        printf("\t\t\t\t➤ Réponse : ");
        scanf("%6s", nouveauCode);

        // Vérifier que tous les caractères sont des chiffres
        int valide = 1;
        int longueur = strlen(nouveauCode);
        for (int i = 0; i < longueur; i++) {
            if (!isdigit(nouveauCode[i])) {
                valide = 0;
                break;
            }
        }

        if (strlen(nouveauCode) < 4 || strlen(nouveauCode) > 6 || !valide) {
            printf("\n\t\t\t\t⚠️ Nouveau code invalide. Il doit contenir entre 4 et 6 chiffres.\n");
            continue;
        }

        // Confirmation du nouveau mot de passe
        printf("\n\t\t\t\t╔════════════════════════════════════════╗\n");
        printf("\t\t\t\t║ Confirmez votre nouveau mot de passe   ║\n");
        printf("\t\t\t\t╚════════════════════════════════════════╝\n");
        printf("\t\t\t\t➤ Réponse : ");
        scanf("%6s", confirmationCode);

        if (strcmp(nouveauCode, confirmationCode) != 0) {
            printf("\n\t\t\t\t⚠️ Les mots de passe ne correspondent pas. Veuillez réessayer.\n");
        } else {
            break; // Nouveau mot de passe confirmé
        }
    } while (1);

    // Calcul de la position dans le fichier
    long offset = position * sizeof(utilisateur);
    fseek(fp, offset, SEEK_SET);

    // Lecture de l'utilisateur
    utilisateur user;
    fread(&user, sizeof(utilisateur), 1, fp);

    // Mise à jour du mot de passe
    strcpy(user.code, nouveauCode);

    // Remise du curseur à la position correcte pour l'écriture
    fseek(fp, offset, SEEK_SET);

    // Écriture de l'utilisateur mis à jour dans le fichier
    if (fwrite(&user, sizeof(utilisateur), 1, fp) != 1) {
        printf("\n\t\t\t\t⚠️ Erreur lors de la mise à jour du mot de passe.\n");
    } else {
        printf("\n\t\t\t\t╔════════════════════════════════════════╗\n");
        printf("\t\t\t\t║       ✅ Mot de passe modifié !        ║\n");
        printf("\t\t\t\t╚════════════════════════════════════════╝\n");
    }

    fclose(fp); // Fermer le fichier
}

void virement() {
    SetConsoleOutputCP(CP_UTF8);
    char identifiant[6];
    char ribDestinataire[40];
    double montant;
    int identifiantTrouve = 0;
    int ribTrouve = 0;

    utilisateur expediteur, destinataire;
    long positionExpediteur = -1;
    long positionDestinataire = -1;

    printf("\n\t\t\t╔════════════════════════════════════════╗\n");
    printf("\t\t\t║        🌟 Effectuer un Virement 🌟     ║\n");
    printf("\t\t\t╚════════════════════════════════════════╝\n");

    // Demander l'identifiant de l'utilisateur
    printf("\n\t\t\t╔════════════════════════════════════════╗\n");
    printf("\t\t\t║ Entrez votre identifiant :             ║\n");
    printf("\t\t\t╚════════════════════════════════════════╝\n");
    printf("\t\t\t➤ Réponse : ");
    scanf("%5s", identifiant);

    // Ouvrir le fichier utilisateurs.dat en lecture et écriture binaire
    FILE *fichier = fopen("utilisateurs.dat", "r+b");
    if (!fichier) {
        printf("\n\t\t\t⚠️ Erreur : Impossible d'ouvrir le fichier des utilisateurs.\n");
        return;
    }

    // Rechercher l'utilisateur par identifiant
    while (fread(&expediteur, sizeof(utilisateur), 1, fichier) == 1) {
        if (strcmp(expediteur.identifiant, identifiant) == 0) {
            identifiantTrouve = 1;
            positionExpediteur = ftell(fichier) - sizeof(utilisateur);
            break;
        }
    }

    if (!identifiantTrouve) {
        printf("\n\t\t\t⚠️ Identifiant non trouvé.\n");
        fclose(fichier);
        return;
    }

    // Demander le montant du virement
    printf("\n\t\t\t╔════════════════════════════════════════╗\n");
    printf("\t\t\t║ Entrez le montant du virement :        ║\n");
    printf("\t\t\t╚════════════════════════════════════════╝\n");
    printf("\t\t\t➤ Réponse : ");
    scanf("%lf", &montant);

    // Vérifier que le montant est positif
    if (montant <= 0) {
        printf("\n\t\t\t⚠️ Le montant doit être supérieur à zéro.\n");
        fclose(fichier);
        return;
    }

    // Demander le RIB du destinataire
    printf("\n\t\t\t╔════════════════════════════════════════╗\n");
    printf("\t\t\t║ Entrez le RIB du destinataire :        ║\n");
    printf("\t\t\t╚════════════════════════════════════════╝\n");
    printf("\t\t\t➤ Réponse : ");
    getchar(); // Consommer le caractère de nouvelle ligne
    fgets(ribDestinataire, sizeof(ribDestinataire), stdin);
    ribDestinataire[strcspn(ribDestinataire, "\n")] = '\0'; // Enlever le saut de ligne

    // Revenir au début du fichier pour rechercher le destinataire
    rewind(fichier);

    // Rechercher le destinataire par RIB
    while (fread(&destinataire, sizeof(utilisateur), 1, fichier) == 1) {
        if (strcmp(destinataire.rib, ribDestinataire) == 0) {
            ribTrouve = 1;
            positionDestinataire = ftell(fichier) - sizeof(utilisateur);
            break;
        }
    }

    if (ribTrouve) {
        // Vérifier que le solde est suffisant
        if (expediteur.solde < montant) {
            printf("\n\t\t\t⚠️ Solde insuffisant pour effectuer le virement.\n");
            fclose(fichier);
            return;
        }

        // Effectuer le virement
        expediteur.solde -= montant;
        destinataire.solde += montant;

        // Mettre à jour les informations de l'expéditeur dans le fichier
        fseek(fichier, positionExpediteur, SEEK_SET);
        fwrite(&expediteur, sizeof(utilisateur), 1, fichier);

        // Mettre à jour les informations du destinataire dans le fichier
        fseek(fichier, positionDestinataire, SEEK_SET);
        fwrite(&destinataire, sizeof(utilisateur), 1, fichier);

        printf("\n\t\t\t╔════════════════════════════════════════╗\n");
        printf("\t\t\t║    ✅ Virement effectué avec succès !  ║\n");
        printf("\t\t\t╚════════════════════════════════════════╝\n");
        printf("\t\t\tVotre nouveau solde est de %.2f DH.\n", expediteur.solde);
    } else {
        double totalDebit = montant + 10.0; // Montant + pénalité de 10 DH

        // Vérifier que le solde est suffisant
        if (expediteur.solde < totalDebit) {
            printf("\n\t\t\t⚠️ Solde insuffisant pour effectuer le virement avec la pénalité.\n");
            fclose(fichier);
            return;
        }

        // Débiter le montant + pénalité du solde de l'expéditeur
        expediteur.solde -= totalDebit;

        // Mettre à jour les informations de l'expéditeur dans le fichier
        fseek(fichier, positionExpediteur, SEEK_SET);
        fwrite(&expediteur, sizeof(utilisateur), 1, fichier);

        printf("\n\t\t\t⚠️ RIB du destinataire non trouvé.\n");
        printf("\t\t\tVirement effectué avec une pénalité de 10 DH.\n");
        printf("\t\t\tVotre nouveau solde est de %.2f DH.\n", expediteur.solde);
    }

    fclose(fichier);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void effectuerPaiementFacture() {
    SetConsoleOutputCP(CP_UTF8);
    char identifiant[20];
    int choix;
    double montant;
    char typeFacture[50];

    printf("\n\t\t\t╔════════════════════════════════════════╗\n");
    printf("\t\t\t║        🌟 Payer une Facture 🌟         ║\n");
    printf("\t\t\t╚════════════════════════════════════════╝\n");

    // Demander l'identifiant de l'utilisateur
    printf("\n\t\t\t╔════════════════════════════════════════╗\n");
    printf("\t\t\t║ Entrez votre identifiant :             ║\n");
    printf("\t\t\t╚════════════════════════════════════════╝\n");
    printf("\t\t\t➤ Réponse : ");
    if (scanf("%19s", identifiant) != 1) {
        printf("\n\t\t\t⚠️ Erreur de lecture de l'identifiant.\n");
        return;
    }

    FILE *fichier = fopen("utilisateurs.dat", "r+b");
    if (!fichier) {
        printf("\n\t\t\t⚠️ Erreur : Impossible d'ouvrir le fichier des utilisateurs.\n");
        return;
    }

    utilisateur usr;
    long positionUsr = -1;
    int utilisateurTrouve = 0;

    // Recherche de l'utilisateur par identifiant
    while (fread(&usr, sizeof(utilisateur), 1, fichier) == 1) {
        if (strcmp(usr.identifiant, identifiant) == 0) {
            utilisateurTrouve = 1;
            positionUsr = ftell(fichier) - sizeof(utilisateur);
            break;
        }
    }

    if (!utilisateurTrouve) {
        printf("\n\t\t\t⚠️ Identifiant non trouvé.\n");
        fclose(fichier);
        return;
    }

    // Affichage du menu de type de factures
    Options options;
    char *MAIN_OPTIONS[] = {
        BOLD "TELEPHONIE ET INTERNET",
        BOLD "EAU ET ELECTRICITE",
        BOLD "TRANSPORT ET BILLETTERIE",
        BOLD "ASSOCIATIONS",
        BOLD "ECOLES ET UNIVERSITES",
        BOLD RED "REVENIR AU MENU PRINCIPAL",
    };
    options.title = "PAYER VOTRE FACTURE ONLINE";
    options.ops = MAIN_OPTIONS;
    options.len = sizeof(MAIN_OPTIONS) / sizeof(MAIN_OPTIONS[0]);

    int option = select_menu(options);
    switch(option) {
        case 0: {
            system("cls");
            strcpy(typeFacture, "Internet");
            break;
        }
        case 1: {
            system("cls");
            strcpy(typeFacture, "Electricité");
            break;
        }
        case 2: {
            system("cls");
            strcpy(typeFacture, "Transport");
            break;
        }
        case 3: {
            system("cls");
            strcpy(typeFacture, "Associations");
            break;
        }
        case 4: {
            system("cls");
            strcpy(typeFacture, "Ecoles");
            break;
        }
    }

    // Saisie du montant
    printf("\n\t\t\t╔════════════════════════════════════════╗\n");
    printf("\t\t\t║ Entrez le montant de la facture :      ║\n");
    printf("\t\t\t╚════════════════════════════════════════╝\n");
    printf("\t\t\t➤ Réponse : ");
    if (scanf("%lf", &montant) != 1 || montant <= 0) {
        printf("\n\t\t\t⚠️ Montant invalide.\n");
        fclose(fichier);
        return;
    }

    // Vérification du solde
    if (usr.solde < montant) {
        printf("\n\t\t\t⚠️ Solde insuffisant pour effectuer le paiement.\n");
        fclose(fichier);
        return;
    }

    // Débiter le montant du solde
    usr.solde -= montant;

    // Mettre à jour l'utilisateur
    fseek(fichier, positionUsr, SEEK_SET);
    fwrite(&usr, sizeof(utilisateur), 1, fichier);

    fclose(fichier);

    // Créer la transaction
    Transaction trans;
    memset(&trans, 0, sizeof(Transaction));
    strcpy(trans.identifiant, usr.identifiant);
    strcpy(trans.nom, usr.nom);
    strcpy(trans.prenom, usr.prenom);
    trans.montant = montant;
    trans.nouveauSolde = usr.solde;
    strcpy(trans.type, "facture");
    strcpy(trans.motif, typeFacture);
    trans.dateTransaction = obtenirDateActuelle();

    // Enregistrer la transaction
    enregistrerTransaction(trans);

    printf("\n\t\t\t╔════════════════════════════════════════╗\n");
    printf("\t\t\t║ ✅ Paiement effectué avec succès !     ║\n");
    printf("\t\t\t╚════════════════════════════════════════╝\n");
    printf("\t\t\tVotre nouveau solde est de %.2f DH.\n", usr.solde);
}

void effectuerRecharge() {
    SetConsoleOutputCP(CP_UTF8);
    char identifiant[20];
    double montant;
    int choixOperateur;
    char operateur[20];

    printf("\n\t\t\t╔════════════════════════════════════════╗\n");
    printf("\t\t\t║        🌟 Effectuer une Recharge 🌟    ║\n");
    printf("\t\t\t╚════════════════════════════════════════╝\n");

    // Demander l'identifiant de l'utilisateur
    printf("\n\t\t\t╔════════════════════════════════════════╗\n");
    printf("\t\t\t║ Entrez votre identifiant :             ║\n");
    printf("\t\t\t╚════════════════════════════════════════╝\n");
    printf("\t\t\t➤ Réponse : ");
    if (scanf("%19s", identifiant) != 1) {
        printf("\n\t\t\t⚠️ Erreur de lecture de l'identifiant.\n");
        return;
    }

    FILE *fichier = fopen("utilisateurs.dat", "r+b");
    if (!fichier) {
        printf("\n\t\t\t⚠️ Erreur : Impossible d'ouvrir le fichier des utilisateurs.\n");
        return;
    }

    utilisateur usr;
    long positionUsr = -1;
    int utilisateurTrouve = 0;

    // Recherche de l'utilisateur par identifiant
    while (fread(&usr, sizeof(utilisateur), 1, fichier) == 1) {
        if (strcmp(usr.identifiant, identifiant) == 0) {
            utilisateurTrouve = 1;
            positionUsr = ftell(fichier) - sizeof(utilisateur);
            break;
        }
    }

    if (!utilisateurTrouve) {
        printf("\n\t\t\t⚠️ Identifiant non trouvé.\n");
        fclose(fichier);
        return;
    }

    // Affichage du menu opérateur
    Options options;
    char *MAIN_OPTIONS[] = {
        BOLD "MAROC TELECOM",
        BOLD "ORANGE",
        BOLD "INWI",
        BOLD RED "REVENIR AU MENU PRINCIPAL",
    };
    options.title = "EFFECTUER RECHARGE";
    options.ops = MAIN_OPTIONS;
    options.len = sizeof(MAIN_OPTIONS) / sizeof(MAIN_OPTIONS[0]);

    int option = select_menu(options);
    switch(option) {
        case 0: {
            system("cls");
            strcpy(operateur, "Maroc Telecom");
            break;
        }
        case 1: {
            system("cls");
            strcpy(operateur, "Orange");
            break;
        }
        case 2: {
            system("cls");
            strcpy(operateur, "Inwi");
            break;
        }
    }

    // Saisir le montant
    printf("\n\t\t\t╔════════════════════════════════════════╗\n");
    printf("\t\t\t║ Entrez le montant de la recharge :     ║\n");
    printf("\t\t\t╚════════════════════════════════════════╝\n");
    printf("\t\t\t➤ Réponse : ");
    if (scanf("%lf", &montant) != 1 || montant <= 0) {
        printf("\n\t\t\t⚠️ Montant invalide.\n");
        fclose(fichier);
        return;
    }

    // Vérification du solde
    if (usr.solde < montant) {
        printf("\n\t\t\t⚠️ Solde insuffisant pour effectuer la recharge.\n");
        fclose(fichier);
        return;
    }

    // Débiter le montant du solde
    usr.solde -= montant;

    // Mettre à jour l'utilisateur
    fseek(fichier, positionUsr, SEEK_SET);
    fwrite(&usr, sizeof(utilisateur), 1, fichier);

    fclose(fichier);

    // Créer la transaction
    Transaction trans;
    memset(&trans, 0, sizeof(Transaction));
    strcpy(trans.identifiant, usr.identifiant);
    strcpy(trans.nom, usr.nom);
    strcpy(trans.prenom, usr.prenom);
    trans.montant = montant;
    trans.nouveauSolde = usr.solde;
    strcpy(trans.type, "recharge");
    strcpy(trans.motif, operateur);
    trans.dateTransaction = obtenirDateActuelle();

    // Enregistrer la transaction
    enregistrerTransaction(trans);

    printf("\n\t\t\t╔════════════════════════════════════════════════════════╗\n");
    printf("\t\t\t║ ✅ Recharge chez %s effectuée avec succès ! ║\n", operateur);
    printf("\t\t\t╚════════════════════════════════════════════════════════╝\n");
    printf("\t\t\tVotre nouveau solde est de %.2f DH.\n", usr.solde);
}


void afficherMenuUtilisateur(){
    Options options;
char *MAIN_OPTIONS[]={
    BOLD "AFFICHER MES INFORMATIONS",
    BOLD "CHANGER MON PASSWORD",
    BOLD "EFFECTUER UN VIREMENT",
    BOLD "PAYER MES FACTURES",
    BOLD "EFFECTUER UN RECHARGE",
    BOLD "MON HISTORIQUE",
    BOLD RED "REVENIR AU MENU PRINCIPAL",
};
    options.title = "MENU UTILISATEUR";
    options.ops = MAIN_OPTIONS;
    options.len = sizeof(MAIN_OPTIONS) / sizeof(MAIN_OPTIONS[0]);

    int option = select_menu(options);
    switch(option){
        case 0:{
            system("cls");
            chercherUtilisateur();
            pause();
            system("cls");
            afficherMenuUtilisateur();
            break;
        }
        case 1:{
            system("cls");
            changerMotDePasse();
            pause();
            system("cls");
            afficherMenuUtilisateur();
            break;
        }
        case 2:{
            system("cls");
            virement();
            pause();
            system("cls");
            afficherMenuUtilisateur();
            break;
        }
        case 3:{
            system("cls");
            effectuerPaiementFacture();
            pause();
            system("cls");
            afficherMenuUtilisateur();
            break;
        }
        case 4:{
            system("cls");
            effectuerRecharge();
            pause();
            system("cls");
            afficherMenuUtilisateur();
            break;
        }
        case 5:{
            system("cls");
            afficherTransactionsParId();
            pause();
            system("cls");
            afficherMenuUtilisateur();
            break;
        }
        case 6:{
            system("cls");
            AfficherMenuPrincipale();
            break;
        }
    }
}


#endif // UTILISATEUR_H
