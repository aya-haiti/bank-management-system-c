#ifndef EMPLOYE_H
#define EMPLOYE_H

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structure.h"
#include "date.h"
#include "historiqueTransaction.h"
#include "admin.h"
#include "revenir.h"
#include "saisirmotpasseavecetoiles.h"




void afficherMenuEmploye();
void AfficherMenuPrincipale();
// Fonction pour verifier les identifiants de connexion de l'employe
int verifierIdentifiantsEmploye(int empno, char *mot_de_passe) {
    FILE *fichier = fopen("employes.dat", "rb");
    if (fichier == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier des employes.\n");
        return 0;
    }

    employe e;
    while (fread(&e, sizeof(employe), 1, fichier) == 1) {
        if (e.empno == empno && strcmp(e.mot_passe, mot_de_passe) == 0) {
            fclose(fichier);
            return 1; // Connexion reussie
        }
    }

    fclose(fichier);
    return 0; // echec de la connexion
}

// Fonction principale de connexion employé
void connexionEmploye() {
    SetConsoleOutputCP(CP_UTF8);
    utilisateur utilisa;
    int empno;
    char mot_de_passe[50];

    // Calcul du nombre d'espaces pour centrer
    int center_padding = 20; // Ajustez ce nombre pour le centrage
    printf("\n%*s╔════════════════════════════════════════╗\n", center_padding, "");
    printf("%*s║       🌟 Connexion Employé 🌟          ║\n", center_padding, "");
    printf("%*s╚════════════════════════════════════════╝\n", center_padding, "");

    // Saisie du numéro d'employé
    printf("\n%*s╔════════════════════════════════════════╗\n", center_padding, "");
    printf("%*s║ Entrez votre numéro d'employé          ║\n", center_padding, "");
    printf("%*s╚════════════════════════════════════════╝\n", center_padding, "");
    printf("%*s➤ Réponse : ", center_padding, "");
    scanf("%d", &empno);

    // Saisie sécurisée du mot de passe avec des étoiles
    printf("\n%*s╔════════════════════════════════════════╗\n", center_padding, "");
    printf("%*s║ Entrez votre mot de passe              ║\n", center_padding, "");
    printf("%*s╚════════════════════════════════════════╝\n", center_padding, "");
    printf("%*s➤ Réponse : ", center_padding, "");
    saisirMotDePasse(mot_de_passe, sizeof(mot_de_passe));

    // Vérification des identifiants
    if (verifierIdentifiantsEmploye(empno, mot_de_passe)) {
        printf("\n\n%*s╔════════════════════════════════════════╗\n", center_padding, "");
        printf("%*s║       ✅ Connexion réussie !           ║\n", center_padding, "");
        printf("%*s╚════════════════════════════════════════╝\n", center_padding, "");
        printf("\n%*sBienvenue, Employé %s %s !\n", center_padding, "", utilisa.nom, utilisa.prenom);
        Sleep(2000);
        afficherMenuEmploye(); // Appel au menu de l'employé après une connexion réussie
    } else {
        printf("\n\n%*s╔════════════════════════════════════════╗\n", center_padding, "");
        printf("%*s║ ❌ Numéro ou mot de passe incorrect.   ║\n", center_padding, "");
        printf("%*s╚════════════════════════════════════════╝\n", center_padding, "");
    }
}

int verifierNumeroCompte(const char *numeroCompte) {
    // Verifier que la longueur est exactement de 16 caracteres
    if (strlen(numeroCompte) != 16) {
        return 0; // Longueur invalide
    }

    // Verifier que chaque caractere est un chiffre
    for (int i = 0; i < 16; i++) {
        if (!isdigit(numeroCompte[i])) {
            return 0; // Caractere non numerique trouve
        }
    }

    return 1; // Numero de compte valide
}

int verifierIdentifiant(const char *identifiant) {
    // Verifier que la longueur est exactement de 5 caracteres
    if (strlen(identifiant) != 5) {
        return 0; // Longueur invalide
    }

    // Verifier que chaque caractere est un chiffre
    for (int i = 0; i < 5; i++) {
        if (!isdigit(identifiant[i])) {
            return 0; // Caractere non numerique trouve
        }
    }

    return 1; // Identifiant valide
}

int verifierCode(const char *cod) {
    int longueur = strlen(cod);

    if (longueur < 4 || longueur > 6) return 0; // Longueur invalide
    for (int i = 0; i < longueur; i++) {
        if (!isdigit(cod[i])) return 0; // Doit contenir uniquement des chiffres
    }

    return 1; // Code valide
}

int identifiantExistant(const char *identifiant) {
    FILE *fp = fopen("utilisateurs.dat", "rb");
    if (fp == NULL) {
        printf("Erreur d'ouverture du fichier binaire\n");
        exit(1);
    }

    utilisateur user;
    while (fread(&user, sizeof(utilisateur), 1, fp)) {
        if (strcmp(user.identifiant, identifiant) == 0) {
            fclose(fp);
            return 1; // L'identifiant existe deje
        }
    }

    fclose(fp);
    return 0; // L'identifiant n'existe pas
}

int numeroCompteExistant(const char *numeroCompte) {
    FILE *fp = fopen("utilisateurs.dat", "rb");
    if (fp == NULL) {
        printf("Erreur d'ouverture du fichier binaire\n");
        exit(1);
    }

    utilisateur user;
    while (fread(&user, sizeof(utilisateur), 1, fp)) {
        if (strcmp(user.numeroCompte, numeroCompte) == 0) {
            fclose(fp);
            return 1; // Le numero de compte existe deje
        }
    }

    fclose(fp);
    return 0; // Le numero de compte n'existe pas
}

void creerCompte() {
    SetConsoleOutputCP(CP_UTF8);
    utilisateur newUser;
    char tempCode[7];
    int choixVille;
    int codeVille;
    FILE *fp;

    // Initialisation des champs pour eviter les valeurs indefinies
    memset(&newUser, 0, sizeof(utilisateur));

    // Ouverture du fichier binaire en mode "ajout binaire" (ab)
    fp = fopen("utilisateurs.dat", "ab");
    if (fp == NULL) {
        printf("\n\t\t\t⚠️ Erreur d'ouverture du fichier.\n");
        return;
    }

    // Saisie de l'identifiant avec verification d'unicite et validation numerique
    do {
        printf("\n\t\t\t╔════════════════════════════════════════╗\n");
        printf("\t\t\t║ Entrez identifiant (5 chiffres)        ║\n");
        printf("\t\t\t╚════════════════════════════════════════╝\n");
        printf("\t\t\t➤ Réponse : ");
        scanf("%5s", newUser.identifiant); // Limiter la saisie à 5 caractères

        // Vérifier que tous les caractères sont des chiffres
        int valide = 1;
        for (int i = 0; i < 5; i++) {
            if (!isdigit(newUser.identifiant[i])) {
                valide = 0;
                break;
            }
        }

        if (strlen(newUser.identifiant) != 5 || !valide) {
            printf("\t\t\t❌ Identifiant invalide. Il doit contenir exactement 5 chiffres.\n");
        } else if (identifiantExistant(newUser.identifiant)) {
            printf("\t\t\t❌ Cet identifiant existe déjà. Veuillez en choisir un autre.\n");
        } else {
            break; // L'identifiant est valide et unique
        }
    } while (1);

    // Saisie et validation du code personnel (4 à 6 chiffres)
    do {
        printf("\n\t\t\t╔═══════════════════════════════════════════╗\n");
        printf("\t\t\t║ Entrez un code personnel (4 à 6 chiffres) ║\n");
        printf("\t\t\t╚═══════════════════════════════════════════╝\n");
        printf("\t\t\t➤ Réponse : ");
        scanf("%6s", newUser.code); // Limiter la saisie à 6 caractères

        int valide = 1;
        int longueur = strlen(newUser.code);
        for (int i = 0; i < longueur; i++) {
            if (!isdigit(newUser.code[i])) {
                valide = 0;
                break;
            }
        }

        if (longueur < 4 || longueur > 6 || !valide) {
            printf("\t\t\t❌ Code invalide. Il doit contenir entre 4 et 6 chiffres.\n");
        } else {
            break; // Code valide
        }
    } while (1);

    // Confirmation du code personnel
    do {
        printf("\n\t\t\t╔════════════════════════════════════════╗\n");
        printf("\t\t\t║ Confirmez le code personnel            ║\n");
        printf("\t\t\t╚════════════════════════════════════════╝\n");
        printf("\t\t\t➤ Réponse : ");
        scanf("%6s", tempCode); // Limiter la saisie à 6 caractères

        if (strcmp(newUser.code, tempCode) != 0) {
            printf("\t\t\t❌ Les codes ne correspondent pas. Veuillez réessayer.\n");
        }
    } while (strcmp(newUser.code, tempCode) != 0);

    // Saisie des informations personnelles
    printf("\n\t\t\t╔════════════════════════════════════════╗\n");
    printf("\t\t\t║ Entrez les informations personnelles   ║\n");
    printf("\t\t\t╚════════════════════════════════════════╝\n");

    printf("\t\t\t➤ Nom : ");
    scanf("%99s", newUser.nom); // Limiter la saisie à 99 caractères

    printf("\t\t\t➤ Prénom : ");
    scanf("%99s", newUser.prenom); // Limiter la saisie à 99 caractères

    printf("\t\t\t➤ Numéro de téléphone : ");
    scanf("%19s", newUser.tele); // Limiter la saisie à 19 caractères

    // Sélection de la ville
    printf("\n\t\t\t╔════════════════════════════════════════╗\n");
    printf("\t\t\t║ Choisissez la ville parmi les options  ║\n");
    printf("\t\t\t╚════════════════════════════════════════╝\n");

    printf("\t\t\t1. Casablanca\n");
    printf("\t\t\t2. Rabat\n");
    printf("\t\t\t3. Marrakech\n");
    printf("\t\t\t4. Fès\n");

    do {
        printf("\n\t\t\t➤ Entrez le numéro correspondant à votre ville (1 à 4) : ");
        scanf("%d", &choixVille);

        switch (choixVille) {
            case 1:
                strcpy(newUser.ville, "Casablanca");
                codeVille = 100;
                break;
            case 2:
                strcpy(newUser.ville, "Rabat");
                codeVille = 101;
                break;
            case 3:
                strcpy(newUser.ville, "Marrakech");
                codeVille = 102;
                break;
            case 4:
                strcpy(newUser.ville, "Fès");
                codeVille = 103;
                break;
            default:
                printf("\t\t\t❌ Choix invalide. Veuillez choisir un numéro entre 1 et 4.\n");
                choixVille = 0; // Réinitialiser la boucle
        }
    } while (choixVille < 1 || choixVille > 4);

    // Saisie du numéro de compte
    do {
        printf("\n\t\t\t╔══════════════════════════════════════════╗\n");
        printf("\t\t\t║ Entrez le numéro de compte (16 chiffres) ║\n");
        printf("\t\t\t╚══════════════════════════════════════════╝\n");
        printf("\t\t\t➤ Réponse : ");
        scanf("%16s", newUser.numeroCompte); // Limiter la saisie à 16 caractères

        // Vérifier que tous les caractères sont des chiffres
        int valide = 1;
        for (int i = 0; i < 16; i++) {
            if (!isdigit(newUser.numeroCompte[i])) {
                valide = 0;
                break;
            }
        }

        if (strlen(newUser.numeroCompte) != 16 || !valide) {
            printf("\t\t\t❌ Numéro de compte invalide. Il doit contenir exactement 16 chiffres.\n");
        } else if (numeroCompteExistant(newUser.numeroCompte)) {
            printf("\t\t\t❌ Ce numéro de compte existe déjà. Veuillez en choisir un autre.\n");
        } else {
            break; // Le numéro de compte est valide et unique
        }
    } while (1);

    // Génération du RIB
    sprintf(newUser.rib, "123-%03d-%s", codeVille, newUser.numeroCompte);

    // Saisie du sexe avec validation
    do {
        printf("\n\t\t\t╔════════════════════════════════════════╗\n");
        printf("\t\t\t║ Entrez le sexe (M/F) :                 ║\n");
        printf("\t\t\t╚════════════════════════════════════════╝\n");
        printf("\t\t\t➤ Réponse : ");
        scanf(" %c", &newUser.sex[0]); // L'espace avant %c permet de consommer les caractères résiduels
        newUser.sex[1] = '\0'; // Terminateur nul

        // Convertir en majuscule pour standardiser
        newUser.sex[0] = toupper(newUser.sex[0]);

        if (newUser.sex[0] != 'M' && newUser.sex[0] != 'F') {
            printf("\t\t\t❌ Saisie invalide. Entrez 'M' ou 'F'.\n");
        }
    } while (newUser.sex[0] != 'M' && newUser.sex[0] != 'F');

    // Vérification de l'email
    int emailValide = 0;
    do {
        printf("\n\t\t\t╔═══════════════════════════════════════════════════╗\n");
        printf("\t\t\t║ Entrez l'email (doit se terminer par 'gmail.com') ║\n");
        printf("\t\t\t╚═══════════════════════════════════════════════════╝\n");
        printf("\t\t\t➤ Réponse : ");
        scanf("%99s", newUser.email); // Limiter la saisie à 99 caractères

        // Vérification que l'email se termine par "@gmail.com"
        char *suffix = "@gmail.com";
        int lenEmail = strlen(newUser.email);
        int lenSuffix = strlen(suffix);

        if (lenEmail > lenSuffix && strcmp(newUser.email + lenEmail - lenSuffix, suffix) == 0) {
            emailValide = 1; // L'email est valide
        } else {
            printf("\t\t\t❌ Erreur : L'adresse e-mail doit se terminer par '@gmail.com'. Veuillez réessayer.\n");
        }
    } while (emailValide == 0);

    // Saisie de la date de naissance avec validation
    int jour, mois, annee;
    int saisieValide = 0;
    do {
        printf("\n\t\t\t╔══════════════════════════════════════════╗\n");
        printf("\t\t\t║ Entrez la date de naissance (jj/mm/aaaa) ║\n");
        printf("\t\t\t╚══════════════════════════════════════════╝\n");
        printf("\t\t\t➤ Réponse : ");
        int result = scanf("%d/%d/%d", &jour, &mois, &annee);

        // Vérifier si la lecture a réussi
        if (result != 3) {
            printf("\t\t\t❌ Format incorrect. Veuillez entrer la date au format jj/mm/aaaa.\n");
            while (getchar() != '\n'); // Vider le tampon d'entrée
            continue;
        }

        // Valider la date
        if (dateValide(jour, mois, annee)) {
            saisieValide = 1;
            newUser.date_naissance1[0] = jour;
            newUser.date_naissance1[1] = mois;
            newUser.date_naissance1[2] = annee;
        } else {
            printf("\t\t\t❌ Date invalide. Veuillez réessayer.\n");
        }
    } while (!saisieValide);

    // Initialisation du solde
    newUser.solde = 0.0;

    // Écriture de l'utilisateur dans le fichier binaire
    if (fwrite(&newUser, sizeof(utilisateur), 1, fp) != 1) {
        printf("\n\t\t\t❌ Erreur lors de l'écriture des données.\n");
    } else {
        // Affichage des informations de l'utilisateur
        printf("\n\t\t\t╔════════════════════════════════════════╗\n");
        printf("\t\t\t║  Compte créé avec succès !             ║\n");
        printf("\t\t\t╚════════════════════════════════════════╝\n");
        printf("\n\t\t\tIdentifiant : %s\n", newUser.identifiant);
        printf("\t\t\tNom : %s %s\n", newUser.prenom, newUser.nom);
        printf("\t\t\tTéléphone : %s\n", newUser.tele);
        printf("\t\t\tVille : %s\n", newUser.ville);
        printf("\t\t\tNuméro de compte : %s\n", newUser.numeroCompte);
        printf("\t\t\tSexe : %c\n", newUser.sex[0]);
        printf("\t\t\tEmail : %s\n", newUser.email);
        printf("\t\t\tDate de naissance : %02d/%02d/%04d\n", newUser.date_naissance1[0], newUser.date_naissance1[1], newUser.date_naissance1[2]);
        printf("\t\t\tSolde initial : %.2f MAD\n", newUser.solde);
        printf("\t\t\tRIB : %s\n", newUser.rib);
    }

    fclose(fp); // Fermer le fichier
}

void afficherComptes() {
    SetConsoleOutputCP(CP_UTF8);
    FILE *fp;
    utilisateur user;

    // Ouvrir le fichier binaire en mode lecture
    fp = fopen("utilisateurs.dat", "rb");
    if (fp == NULL) {
        printf("\n\t\t\t╔════════════════════════════════════════╗\n");
        printf("\t\t\t║ Erreur : Impossible d'ouvrir le fichier des utilisateurs. ║\n");
        printf("\t\t\t╚════════════════════════════════════════╝\n");
        return;
    }

    printf("\n\t\t\t╔════════════════════════════════════════╗\n");
    printf("\t\t\t║    Liste des Utilisateurs              ║\n");
    printf("\t\t\t╚════════════════════════════════════════╝\n\n");

    // Affichage du tableau de comptes avec des bordures
    printf("\t\t╔══════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("\t\t║ Identifiant | Nom                | Prénom             | Téléphone  | Ville       ║\n");
    printf("\t\t╠══════════════════════════════════════════════════════════════════════════════════╣\n");

    // Lecture et affichage des informations des utilisateurs
    while (fread(&user, sizeof(utilisateur), 1, fp) == 1) {
        printf("\t\t║ %-12s | %-18s | %-18s | %-10s | %-7s ║\n",
               user.identifiant, user.nom, user.prenom, user.tele, user.ville);
        printf("\t\t║----------------------------------------------------------------------------------║\n");
    }

    printf("\t\t╚══════════════════════════════════════════════════════════════════════════════════╝\n");

    fclose(fp); // Fermer le fichier

    printf("\n\t\t\t╔════════════════════════════════════════╗\n");
    printf("\t\t\t║ Fin de la liste des utilisateurs.      ║\n");
    printf("\t\t\t╚════════════════════════════════════════╝\n");
}


/*
void afficherComptes() {
    SetConsoleOutputCP(CP_UTF8);
    FILE *fp;
    utilisateur user;

    // Ouvrir le fichier binaire en mode lecture
    fp = fopen("utilisateurs.dat", "rb");
    if (fp == NULL) {
        printf("\n\t\t\t╔════════════════════════════════════════╗\n");
        printf("\t\t\t║ Erreur : Impossible d'ouvrir le fichier des utilisateurs. ║\n");
        printf("\t\t\t╚════════════════════════════════════════╝\n");
        return;
    }

    printf("\n\t\t\t╔════════════════════════════════════════╗\n");
    printf("\t\t\t║     Lecture du fichier des utilisateurs...    ║\n");
    printf("\t\t\t╚════════════════════════════════════════╝\n");

    printf("\n\t\t\t===============================\n");
    printf("\t\t\t    LISTE DES UTILISATEURS\n");
    printf("\t\t\t===============================\n\n");

    // Lecture et affichage des informations des utilisateurs
    while (fread(&user, sizeof(utilisateur), 1, fp) == 1) {
        printf("\n\t\t\t╔════════════════════════════════════════╗\n");
        printf("\t\t\t║ Identifiant      : %-18s ║\n", user.identifiant);
        printf("\t\t\t║ Nom              : %-18s ║\n", user.nom);
        printf("\t\t\t║ Prénom           : %-18s ║\n", user.prenom);
        printf("\t\t\t║ Téléphone        : %-18s ║\n", user.tele);
        printf("\t\t\t║ Ville            : %-18s ║\n", user.ville);
        printf("\t\t\t║ Email            : %-18s ║\n", user.email);
        printf("\t\t\t║ Sexe             : %-18s ║\n", user.sex);
        printf("\t\t\t║ Date de Naissance: %02d/%02d/%04d ║\n",
               user.date_naissance1[0], user.date_naissance1[1], user.date_naissance1[2]);
        printf("\t\t\t║ Solde            : %.2f MAD         ║\n", user.solde);
        printf("\t\t\t║ RIB              : %-18s ║\n", user.rib);
        printf("\t\t\t╚════════════════════════════════════════╝\n");
        printf("\n\t\t\t------------------------------------------\n");
    }

    fclose(fp); // Fermer le fichier
    printf("\n\t\t\t╔════════════════════════════════════════╗\n");
    printf("\t\t\t║ Fin de la liste des utilisateurs.     ║\n");
    printf("\t\t\t╚════════════════════════════════════════╝\n");
}
*/

/*void afficherComptes() {
    SetConsoleOutputCP(CP_UTF8);
    FILE *fp;
    utilisateur user;

    // Ouvrir le fichier binaire en mode lecture
    fp = fopen("utilisateurs.dat", "rb");
    if (fp == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier des utilisateurs.\n");
        return;
    }

    printf("Lecture du fichier binaire...\n");

    printf("\t\t=============================\n");
    printf("\t\t    LISTE DES UTILISATEURS\n");
    printf("\t\t=============================\n\n");

    // Lecture et affichage des informations des utilisateurs
    while (fread(&user, sizeof(utilisateur), 1, fp) == 1) {
        printf("Identifiant      : %s\n", user.identifiant);
        printf("Nom              : %s\n", user.nom);
        printf("Prenom           : %s\n", user.prenom);
        printf("Telephone        : %s\n", user.tele);
        printf("Ville            : %s\n", user.ville);
        printf("Email            : %s\n", user.email);
        printf("Sexe             : %s\n", user.sex);
        printf("Date de Naissance: %02d/%02d/%04d\n",
               user.date_naissance1[0], user.date_naissance1[1], user.date_naissance1[2]);
        printf("Solde            : %.2f MAD\n", user.solde);
        printf("RIB              : %s\n", user.rib);
        printf("-------------------------------\n");
    }

    fclose(fp); // Fermer le fichier
    printf("\nFin de la liste des utilisateurs.\n");
}*/

void deposerMontant() {
    SetConsoleOutputCP(CP_UTF8);
    FILE *fp = fopen("utilisateurs.dat", "r+b");
    if (fp == NULL) {
        printf("\n\t\t\t╔════════════════════════════════════════╗\n");
        printf("\t\t\t║ Erreur d'ouverture du fichier des utilisateurs. ║\n");
        printf("\t\t\t╚════════════════════════════════════════╝\n");
        return;
    }

    utilisateur usr;
    char identifiant[20];
    double montant;
    int trouve = 0;

    // Demander l'identifiant de l'utilisateur
    printf("\n\t\t\t╔════════════════════════════════════════╗\n");
    printf("\t\t\t║ Entrez l'identifiant de l'utilisateur  ║\n");
    printf("\t\t\t╚════════════════════════════════════════╝\n");
    printf("\t\t\t➤ Réponse : ");
    fflush(stdin);
    fgets(identifiant, sizeof(identifiant), stdin);
    identifiant[strcspn(identifiant, "\n")] = '\0'; // Enlever le saut de ligne éventuel

    // Demander le montant à déposer
    printf("\n\t\t\t╔════════════════════════════════════════╗\n");
    printf("\t\t\t║ Entrez le montant à déposer en DH      ║\n");
    printf("\t\t\t╚════════════════════════════════════════╝\n");
    printf("\t\t\t➤ Montant : ");
    scanf("%lf", &montant);

    // Vérification du montant
    if (montant <= 0) {
        printf("\n\t\t\t❌ Montant invalide. Il doit être supérieur à 0.\n");
        fclose(fp);
        return;
    }

    // Parcours du fichier pour trouver l'utilisateur
    while (fread(&usr, sizeof(utilisateur), 1, fp)) {
        if (strcmp(usr.identifiant, identifiant) == 0) {
            trouve = 1;
            usr.solde += montant;  // Mise à jour du solde de l'utilisateur
            fseek(fp, -(long int)sizeof(utilisateur), SEEK_CUR);  // Retourner à la position précédente
            fwrite(&usr, sizeof(utilisateur), 1, fp);  // Écriture de la nouvelle donnée

            // Affichage des détails de la transaction
            printf("\n\t\t\t╔════════════════════════════════════════╗\n");
            printf("\t\t\t║ Dépôt effectué avec succès !           ║\n");
            printf("\t\t\t╚════════════════════════════════════════╝\n");
            printf("\n\t\t\tDétails du dépôt :\n");
            printf("\t\t\tIdentifiant : %s\n", usr.identifiant);
            printf("\t\t\tNom : %s %s\n", usr.prenom, usr.nom);
            printf("\t\t\tMontant déposé : %.2f DH\n", montant);
            printf("\t\t\tNouveau solde : %.2f DH\n", usr.solde);

            // Enregistrement de la transaction
            Transaction trans;
            strcpy(trans.identifiant, usr.identifiant);
            strcpy(trans.nom, usr.nom);
            strcpy(trans.prenom, usr.prenom);
            trans.montant = montant;
            trans.nouveauSolde = usr.solde;
            strcpy(trans.type, "Dépôt");
            trans.dateTransaction = obtenirDateActuelle();
            enregistrerTransaction(trans);

            break;
        }
    }

    fclose(fp);

    if (!trouve) {
        printf("\n\t\t\t❌ Utilisateur non trouvé.\n");
    }
}

void effectuerRetrait() {
    SetConsoleOutputCP(CP_UTF8);
    FILE *fp = fopen("utilisateurs.dat", "r+b");
    if (fp == NULL) {
        printf("\n\t\t\t╔═════════════════════════════════════════════════════════╗\n");
        printf("\t\t\t║ Erreur lors de l'ouverture du fichier des utilisateurs. ║\n");
        printf("\t\t\t╚═════════════════════════════════════════════════════════╝\n");
        return;
    }

    utilisateur usr;
    char identifiant[20];
    double montant;
    int trouve = 0;

    // Demander l'identifiant de l'utilisateur
    printf("\n\t\t\t╔══════════════════════════════════════════════════════╗\n");
    printf("\t\t\t║ Entrez votre identifiant pour effectuer un retrait : ║\n");
    printf("\t\t\t╚══════════════════════════════════════════════════════╝\n");
    printf("\t\t\t➤ Réponse : ");
    fflush(stdin);
    fgets(identifiant, sizeof(identifiant), stdin);
    identifiant[strcspn(identifiant, "\n")] = '\0'; // Enlever le saut de ligne éventuel

    // Demander le montant à retirer
    printf("\n\t\t\t╔════════════════════════════════════════╗\n");
    printf("\t\t\t║ Entrez le montant à retirer            ║\n");
    printf("\t\t\t╚════════════════════════════════════════╝\n");
    printf("\t\t\t➤ Montant : ");
    scanf("%lf", &montant);

    // Vérification du montant
    if (montant <= 0) {
        printf("\n\t\t\t❌ Montant invalide. Il doit être supérieur à 0.\n");
        fclose(fp);
        return;
    }

    // Parcours du fichier pour trouver l'utilisateur
    while (fread(&usr, sizeof(utilisateur), 1, fp)) {
        if (strcmp(usr.identifiant, identifiant) == 0) {
            trouve = 1;
            if (usr.solde >= montant) {
                usr.solde -= montant;  // Mise à jour du solde de l'utilisateur
                fseek(fp, -(long int)sizeof(utilisateur), SEEK_CUR);  // Retourner à la position précédente
                fwrite(&usr, sizeof(utilisateur), 1, fp);  // Écriture de la nouvelle donnée

                // Affichage des détails du retrait
                printf("\n\t\t\t╔════════════════════════════════════════╗\n");
                printf("\t\t\t║ Retrait effectué avec succès !         ║\n");
                printf("\t\t\t╚════════════════════════════════════════╝\n");
                printf("\n\t\t\tDétails du retrait :\n");
                printf("\t\t\tIdentifiant : %s\n", usr.identifiant);
                printf("\t\t\tNom : %s %s\n", usr.prenom, usr.nom);
                printf("\t\t\tMontant retiré : %.2f DH\n", montant);
                printf("\t\t\tNouveau solde : %.2f DH\n", usr.solde);

                // Enregistrement de la transaction
                Transaction trans;
                strcpy(trans.identifiant, usr.identifiant);
                strcpy(trans.nom, usr.nom);
                strcpy(trans.prenom, usr.prenom);
                trans.montant = -montant;  // Montant négatif pour indiquer un retrait
                trans.nouveauSolde = usr.solde;
                strcpy(trans.type, "Retrait");
                trans.dateTransaction = obtenirDateActuelle();
                enregistrerTransaction(trans);

            } else {
                printf("\n\t\t\t❌ Solde insuffisant pour effectuer ce retrait.\n");
            }
            break;
        }
    }

    fclose(fp);

    if (!trouve) {
        printf("\n\t\t\t❌ Identifiant non trouvé.\n");
    }
}

void modifierClient() {
    SetConsoleOutputCP(CP_UTF8);
    FILE *fp = fopen("utilisateurs.dat", "r+b");
    if (!fp) {
        printf("\n\t\t\t╔════════════════════════════════════════╗\n");
        printf("\t\t\t║ Erreur d'ouverture du fichier.         ║\n");
        printf("\t\t\t╚════════════════════════════════════════╝\n");
        return;
    }

    utilisateur usr;
    char identifiant[6];
    int choix;

    // Demander l'identifiant du client à modifier
    printf("\n\t\t\t╔══════════════════════════════════════════════╗\n");
    printf("\t\t\t║ Entrez l'identifiant du client à modifier :  ║\n");
    printf("\t\t\t╚══════════════════════════════════════════════╝\n");
    printf("\t\t\t➤ Réponse : ");
    scanf("%5s", identifiant);
    rewind(fp);

    // Parcourir les utilisateurs et rechercher celui avec l'identifiant donné
    while (fread(&usr, sizeof(utilisateur), 1, fp) == 1) {
        if (strcmp(usr.identifiant, identifiant) == 0) {
            // Afficher le menu de modification
            printf("\n\t\t\t╔════════════════════════════════════════╗\n");
            printf("\t\t\t║ Choisissez l'information à modifier :  ║\n");
            printf("\t\t\t╚════════════════════════════════════════╝\n");
            printf("\t\t\t1. Nom\n\t\t\t2. Prénom\n\t\t\t3. Téléphone\n");
            printf("\t\t\t4. Email\n\t\t\t5. Date de Naissance\n");
            printf("\t\t\t➤ Votre choix : ");
            scanf("%d", &choix);

            switch (choix) {
                case 1:
                    printf("\n\t\t\tEntrez le nouveau nom : ");
                    scanf(" %[^\n]s", usr.nom);
                    break;
                case 2:
                    printf("\n\t\t\tEntrez le nouveau prénom : ");
                    scanf(" %[^\n]s", usr.prenom);
                    break;
                case 3:
                    printf("\n\t\t\tEntrez le nouveau numéro de téléphone : ");
                    scanf(" %[^\n]s", usr.tele);
                    break;
                case 4:
                    printf("\n\t\t\tEntrez le nouvel email : ");
                    scanf(" %[^\n]s", usr.email);
                    break;
                case 5:
                    printf("\n\t\t\tEntrez la nouvelle année de naissance (jour-mois-année) : ");
                    scanf("%d", &usr.date_naissance[0].annee);
                    printf("\t\t\tEntrez le nouveau mois de naissance : ");
                    scanf("%d", &usr.date_naissance[1].mois);
                    printf("\t\t\tEntrez le nouveau jour de naissance : ");
                    scanf("%d", &usr.date_naissance[2].jour);
                    break;
                default:
                    printf("\n\t\t\t❌ Choix invalide.\n");
                    fclose(fp);
                    return;
            }

            // Retour à la position précédente pour écrire les nouvelles données de l'utilisateur
            fseek(fp, -(long int)sizeof(utilisateur), SEEK_CUR);
            fwrite(&usr, sizeof(utilisateur), 1, fp);

            printf("\n\t\t\t╔═════════════════════════════════════════════════════╗\n");
            printf("\t\t\t║ Les modifications ont été enregistrées avec succès. ║\n");
            printf("\t\t\t╚═════════════════════════════════════════════════════╝\n");
            break;
        }
    }

    if (feof(fp)) {
        printf("\n\t\t\t❌ Client avec l'identifiant '%s' introuvable.\n", identifiant);
    }

    fclose(fp);
}

void supprimerUtilisateurParIdentifiant() {
    SetConsoleOutputCP(CP_UTF8);
    FILE *fichierOriginal, *fichierTemp;
    utilisateur user;
    int trouve = 0;
    char identifiantASupprimer[6];

    // Demande de saisie de l'identifiant à supprimer
    printf("\n\t\t\t╔════════════════════════════════════════╗\n");
    printf("\t\t\t║ Entrez l'identifiant de l'utilisateur  ║\n");
    printf("\t\t\t║ à supprimer :                          ║\n");
    printf("\t\t\t╚════════════════════════════════════════╝\n");
    printf("\t\t\tRéponse : ");
    scanf("%5s", identifiantASupprimer);

    fichierOriginal = fopen("utilisateurs.dat", "rb");
    if (fichierOriginal == NULL) {
        printf("\n\t\t\t╔════════════════════════════════════════╗\n");
        printf("\t\t\t║ Impossible d'ouvrir le fichier        ║\n");
        printf("\t\t\t║ original.                                 ║\n");
        printf("\t\t\t╚════════════════════════════════════════╝\n");
        return;
    }

    fichierTemp = fopen("temp.dat", "wb");
    if (fichierTemp == NULL) {
        printf("\n\t\t\t╔════════════════════════════════════════╗\n");
        printf("\t\t\t║ Impossible de créer le fichier        ║\n");
        printf("\t\t\t║ temporaire.                            ║\n");
        printf("\t\t\t╚════════════════════════════════════════╝\n");
        fclose(fichierOriginal);
        return;
    }

    // Parcourir le fichier original
    while (fread(&user, sizeof(utilisateur), 1, fichierOriginal)) {
        if (strcmp(user.identifiant, identifiantASupprimer) == 0) {
            trouve = 1;
            // Ne pas écrire cet utilisateur dans le fichier temporaire
            continue;
        }
        fwrite(&user, sizeof(utilisateur), 1, fichierTemp);
    }

    fclose(fichierOriginal);
    fclose(fichierTemp);

    if (trouve) {
        // Suppression et renommage des fichiers
        remove("utilisateurs.dat");
        rename("temp.dat", "utilisateurs.dat");

        printf("\n\t\t\t╔════════════════════════════════════════╗\n");
        printf("\t\t\t║ Utilisateur avec l'identifiant %s      ║\n", identifiantASupprimer);
        printf("\t\t\t║ supprimé avec succès.                  ║\n");
        printf("\t\t\t╚════════════════════════════════════════╝\n");
    } else {
        remove("temp.dat");
        printf("\n\t\t\t╔════════════════════════════════════════╗\n");
        printf("\t\t\t║ Utilisateur avec l'identifiant %s    ║\n", identifiantASupprimer);
        printf("\t\t\t║ non trouvé.                          ║\n");
        printf("\t\t\t╚════════════════════════════════════════╝\n");
    }
}


/*
void supprimerUtilisateurParIdentifiant() {
    SetConsoleOutputCP(CP_UTF8);
    FILE *fichierOriginal, *fichierTemp;
    utilisateur user;
    int trouve = 0;
    char identifiantASupprimer[6];

    // Demande de saisie de l'identifiant e supprimer
    printf("Entrez l'identifiant de l'utilisateur e supprimer : ");
    scanf("%5s", identifiantASupprimer);

    fichierOriginal = fopen("utilisateurs.dat", "rb");
    if (fichierOriginal == NULL) {
        printf("Impossible d'ouvrir le fichier original.\n");
        return;
    }

    fichierTemp = fopen("temp.dat", "wb");
    if (fichierTemp == NULL) {
        printf("Impossible de creer le fichier temporaire.\n");
        fclose(fichierOriginal);
        return;
    }

    while (fread(&user, sizeof(utilisateur), 1, fichierOriginal)) {
        if (strcmp(user.identifiant, identifiantASupprimer) == 0) {
            trouve = 1;
            // Ne pas ecrire cet utilisateur dans le fichier temporaire
            continue;
        }
        fwrite(&user, sizeof(utilisateur), 1, fichierTemp);
    }

    fclose(fichierOriginal);
    fclose(fichierTemp);

    if (trouve) {
        remove("utilisateurs.dat");
        rename("temp.dat", "utilisateurs.dat");
        printf("Utilisateur avec l'identifiant %s supprime avec succes.\n", identifiantASupprimer);
    } else {
        remove("temp.dat");
        printf("Utilisateur avec l'identifiant %s non trouve.\n", identifiantASupprimer);
    }
}*/

void chercherEmploye() {
    SetConsoleOutputCP(CP_UTF8);
    FILE *fichier;
    employe emp;
    int empnoCherche;
    int trouve = 0;

    // Demander le numéro d'employé
    printf("\n\t\t╔═════════════════════════════════════════╗\n");
    printf("\t\t║ Entrez le numéro d'employé à rechercher ║\n");
    printf("\t\t╚═════════════════════════════════════════╝\n");
    printf("\t\t Numéro employé : ");
    scanf("%d", &empnoCherche);

    // Ouvrir le fichier contenant les informations des employés
    fichier = fopen("employes.dat", "r");
    if (fichier == NULL) {
        printf("\n\t\t╔════════════════════════════════════════╗\n");
        printf("\t\t║ Erreur : Impossible d'ouvrir le fichier ║\n");
        printf("\t\t╚════════════════════════════════════════╝\n");
        return;
    }

    // Parcourir le fichier
    while (fread(&emp, sizeof(employe), 1, fichier)) {
        if (emp.empno == empnoCherche) {
            // Employé trouvé
            printf("\n\t\t╔════════════════════════════════════════╗\n");
            printf("\t\t║            Employé trouvé              ║\n");
            printf("\t\t╚════════════════════════════════════════╝\n");
            printf("\nNuméro employé : %d\n", emp.empno);
            printf("Nom            : %s\n", emp.NOM);
            printf("Prénom         : %s\n", emp.prenom);
            printf("Adresse        : %s\n", emp.adresse);
            printf("Téléphone      : %s\n", emp.tel);
            printf("Email          : %s\n", emp.email);
            // Le mot de passe peut être masqué pour des raisons de sécurité
            printf("Mot de passe   : %s\n", emp.mot_passe);
            trouve = 1;
            break;
        }
    }

    if (!trouve) {
        printf("\n\t\t╔════════════════════════════════════════╗\n");
        printf("\t\t║ Aucun employé trouvé avec le numéro    ║\n");
        printf("\t\t║ %d.                                  ║\n", empnoCherche);
        printf("\t\t╚════════════════════════════════════════╝\n");
    }

    fclose(fichier);
}


/*
void chercherEmploye() {
    SetConsoleOutputCP(CP_UTF8);
    FILE *fichier;
    employe emp;
    int empnoCherche;
    int trouve = 0;

    // Demander le numero d'employe
    printf("Entrez le numero d'employe e rechercher : ");
    scanf("%d", &empnoCherche);

    // Ouvrir le fichier contenant les informations des employes
    fichier = fopen("employes.dat", "r");
    if (fichier == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier !!\n");
        return;
    }

    // Parcourir le fichier
    while (fread(&emp, sizeof(employe), 1, fichier)) {
        if (emp.empno == empnoCherche) {
            // Employe trouve
            printf("\nEmploye trouve :\n");
            printf("Numero employe : %d\n", emp.empno);
            printf("Nom : %s\n", emp.NOM);
            printf("Prenom : %s\n", emp.prenom);
            printf("Adresse : %s\n", emp.adresse);
            printf("Telephone : %s\n", emp.tel);
            printf("Email : %s\n", emp.email);
            // Le mot de passe peut etre masque pour des raisons de securite
            printf("Mot de passe : %s \n",emp.mot_passe);
            trouve = 1;
            break;
        }
    }
if (!trouve) {
        printf("\nAucun employe trouve avec le numero %d.\n",empnoCherche);
    }fclose(fichier);}
*/

void afficherMenuEmploye() {
    Options options;
char *MAIN_OPTIONS[]={
    BOLD "CREER UN COMPTE",
    BOLD "DEPOSER UN MONTANT",
    BOLD "RETRAIT UN MONTANT",
    BOLD "MODIFIER UN COMPTE",
    BOLD "AFFICHER LA LISTE DES COMPTES",
    BOLD "SUPPRIMER UN COMPTE",
    BOLD "AFFICHER LES TRANSACTIONS",
    BOLD "VOIR MES DONNEES",
    BOLD RED "REVENIR AU MENU PRINCIPAL"
};
    options.title = "MENU EMPLOYE";
    options.ops = MAIN_OPTIONS;
    options.len = sizeof(MAIN_OPTIONS) / sizeof(MAIN_OPTIONS[0]);

    int option = select_menu(options);
    switch(option){
        case 0:{
            system("cls");
            creerCompte();
            pause();
            system("cls");
            afficherMenuEmploye();
            break;
        }
        case 1:{
            system("cls");
            deposerMontant();
            pause();
            system("cls");
            afficherMenuEmploye();
            break;
        }
        case 2:{
            system("cls");
            effectuerRetrait();
            pause();
            system("cls");
            afficherMenuEmploye();
            break;
        }
        case 3:{
            system("cls");
            modifierClient();
            pause();
            system("cls");
            afficherMenuEmploye();
            break;
        }
        case 4:{
            system("cls");
            afficherComptes();
            pause();
            system("cls");
            afficherMenuEmploye();
            break;
        }
        case 5:{
            system("cls");
            supprimerUtilisateurParIdentifiant();
            pause();
            system("cls");
            afficherMenuEmploye();
            break;
        }
        case 6:{
            system("cls");
            afficherTransactionsParId();
            pause();
            system("cls");
            afficherMenuEmploye();
            break ;
        }
        case 7:{
            system("cls");
            chercherEmploye();
            pause();
            system("cls");
            afficherMenuEmploye();
            break;
        }
        case 8:{
            system("cls");
            AfficherMenuPrincipale();
        }
    }
}


#endif // EMPLOYE_H

