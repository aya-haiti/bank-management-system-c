#ifndef ADMIN_H
#define ADMIN_H

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include "date.h"
#include "couleur.h"
#include "historiqueTransaction.h"
#include "structure.h"
#include "employe.h"
#include "revenir.h"
#include <ctype.h>

void affichenu();

int readAdminCredentials(char *username, char *password) {
    FILE *file = fopen("admin_credentials.txt", "r");
    if (file == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier des identifiants.\n");
        return 0;
    }

    // Lire le nom d'utilisateur et le mot de passe depuis le fichier
    if (fgets(username, 50, file) == NULL || fgets(password, 50, file) == NULL) {
        fclose(file);
        return 0;  // Retourner 0 si les identifiants ne sont pas valides
    }

    username[strcspn(username, "\n")] = 0; // Supprimer le caractere de nouvelle ligne
    password[strcspn(password, "\n")] = 0; // Supprimer le caractere de nouvelle ligne

    fclose(file);
    return 1;
}

// Fonction pour saisir un mot de passe avec des étoiles
void getPassword(char *mot_de_passe, int taille) {
    int i = 0;
    char c;
    while (1) {
        c = _getch(); // Lecture d'un caractère sans affichage
        if (c == 13) { // Touche Entrée
            break;
        } else if (c == 8) { // Touche Backspace
            if (i > 0) {
                i--;
                printf("\b \b"); // Efface une étoile affichée
            }
        } else if (i < taille - 1) {
            mot_de_passe[i++] = c;
            printf("*"); // Affiche une étoile
        }
    }
    mot_de_passe[i] = '\0'; // Fin de la chaîne
}

// Fonction principale de connexion administrateur
int loginAdmin() {
    SetConsoleOutputCP(CP_UTF8); // Support UTF-8
    char username[50], password[50];
    char storedUsername[50], storedPassword[50];

    // Lire les identifiants depuis le fichier
    if (!readAdminCredentials(storedUsername, storedPassword)) {
        printf("\n\t\t\t\t\t\tErreur : Impossible de lire les identifiants.\n");
        return 0;
    }

    // Affichage centré avec des tabulations
    printf("\n\t\t\t\t\t\t╔════════════════════════════════════════╗\n");
    printf("\t\t\t\t\t\t║       🌟 Connexion Admin 🌟            ║\n");
    printf("\t\t\t\t\t\t╚════════════════════════════════════════╝\n");

    printf("\n\t\t\t\t\t\t╔════════════════════════════════════════╗\n");
    printf("\t\t\t\t\t\t║ Entrez votre nom d'utilisateur :       ║\n");
    printf("\t\t\t\t\t\t╚════════════════════════════════════════╝\n");
    printf("\t\t\t\t\t\t➤ Réponse : ");
    scanf("%s", username);

    printf("\n\t\t\t\t\t\t╔════════════════════════════════════════╗\n");
    printf("\t\t\t\t\t\t║ Entrez votre mot de passe              ║\n");
    printf("\t\t\t\t\t\t╚════════════════════════════════════════╝\n");
    printf("\t\t\t\t\t\t➤ Réponse : ");
    getPassword(password, 50); // Masquer le mot de passe avec des étoiles

    // Vérifier si les identifiants sont corrects
    if (strcmp(username, storedUsername) == 0 && strcmp(password, storedPassword) == 0) {
        printf("\n\n\t\t\t\t\t\t╔════════════════════════════════════════╗\n");
        printf("\t\t\t\t\t\t║       ✅ Connexion réussie !           ║\n");
        printf("\t\t\t\t\t\t╚════════════════════════════════════════╝\n");
        printf("\n\t\t\t\t\t\tBienvenue, Admin !\n");
        Sleep(2000);
        affichenu();
        return 1;
    } else {
        printf("\n\n\t\t\t\t\t\t╔════════════════════════════════════════╗\n");
        printf("\t\t\t\t\t\t║ ❌ Identifiant ou mot de passe incorrect. ║\n");
        printf("\t\t\t\t\t\t╚════════════════════════════════════════╝\n");
        return 0;
    }
}

int numeroExiste(int empno) {
    FILE *fichier = fopen("employes.dat", "rb"); // Ouvrir le fichier en mode lecture binaire
    if (fichier == NULL) {
        // Si le fichier n'existe pas encore, aucun employe n'a ete enregistre
        return 0; // Le numero n'existe pas
    }

    employe e;
    // Parcourir le fichier pour chercher un employe avec le meme numero
    while (fread(&e, sizeof(employe), 1, fichier) == 1) {
        if (e.empno == empno) {
            fclose(fichier);
            return 1; // Le numero existe deje
        }
    }

    fclose(fichier);
    return 0; // Le numero n'existe pas
}

void ajouterEmploye() {
    SetConsoleOutputCP(CP_UTF8);
    employe e;
    FILE *fichier = fopen("employes.dat", "ab"); // Ouvrir le fichier en mode ajout binaire
    if (fichier == NULL) {
        printf("\n\t\t╔════════════════════════════════════════╗\n");
        printf("\t\t║  Erreur : Impossible d'ouvrir le fichier  ║\n");
        printf("\t\t╚════════════════════════════════════════╝\n");
        return;
    }

    printf("\n\t\t╔════════════════════════════════════════╗\n");
    printf("\t\t║       Ajout d'un nouvel employé        ║\n");
    printf("\t\t╚════════════════════════════════════════╝\n");

    // Vérification de l'unicité de empno
    int unique = 0;
    do {
        printf("\n\t\t➤ Entrez le numéro de l'employé (unique) : ");
        scanf("%d", &e.empno);

        if (numeroExiste(e.empno) == 1) {
            printf("\n\t\t╔══════════════════════════════════════════╗\n");
            printf("\t\t║  Erreur : Ce numéro d'employé existe déjà║\n");
            printf("\t\t║       Veuillez en saisir un autre.       ║\n");
            printf("\t\t╚══════════════════════════════════════════╝\n");
        } else {
            unique = 1; // Le numéro est unique
        }
    } while (unique == 0);

    // Saisie des autres informations de l'employé
    printf("\n\t\t➤ Entrez le nom de l'employé : ");
    scanf("%s", e.NOM);

    printf("\t\t➤ Entrez le prénom de l'employé : ");
    scanf("%s", e.prenom);

    printf("\t\t➤ Entrez la date de naissance (jour mois année) : ");
    scanf("%d %d %d", &e.naissance.jour, &e.naissance.mois, &e.naissance.annee);

    printf("\t\t➤ Entrez l'adresse de l'employé : ");
    scanf(" %[^\n]", e.adresse); // Lire une chaîne avec des espaces

    printf("\t\t➤ Entrez le numéro de téléphone de l'employé : ");
    scanf("%s", e.tel);

    // Saisie et vérification de l'adresse e-mail
    int emailValide = 0;
    do {
        printf("\t\t➤ Entrez l'adresse e-mail de l'employé (doit se terminer par @gmail.com) : ");
        scanf("%s", e.email);

        // Vérification que l'e-mail se termine par "@gmail.com"
        char *suffix = "@gmail.com";
        int lenEmail = strlen(e.email);
        int lenSuffix = strlen(suffix);

        if (lenEmail > lenSuffix && strcmp(e.email + lenEmail - lenSuffix, suffix) == 0) {
            emailValide = 1; // L'e-mail est valide
        } else {
            printf("\n\t\t╔════════════════════════════════════════╗\n");
            printf("\t\t║  Erreur : L'adresse e-mail doit se     ║\n");
            printf("\t\t║     terminer par '@gmail.com'.         ║\n");
            printf("\t\t╚════════════════════════════════════════╝\n");
        }
    } while (emailValide == 0);

    printf("\t\t➤ Entrez le mot de passe de l'employé : ");
    scanf("%s", e.mot_passe);

    // Écriture des informations dans le fichier
    fwrite(&e, sizeof(employe), 1, fichier);

    printf("\n\t\t╔════════════════════════════════════════╗\n");
    printf("\t\t║      Employé ajouté avec succès !      ║\n");
    printf("\t\t╚════════════════════════════════════════╝\n");

    fclose(fichier); // Fermer le fichier
    getchar();
}


/*void ajouterEmploye() {
    SetConsoleOutputCP(CP_UTF8);
    employe e;
    FILE *fichier = fopen("employes.dat", "ab"); // Ouvrir le fichier en mode ajout binaire
    if (fichier == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier.\n");
        return;
    }

    // Verification de l'unicite de empno
    int unique = 0;
    do {
        printf("Entrez le numero de l'employe (unique) : ");
        scanf("%d", &e.empno);

        if (numeroExiste(e.empno) == 1) {
            printf("Erreur : Ce numero d'employe existe deje. Veuillez en saisir un autre.\n");
        } else {
            unique = 1; // Le numero est unique
        }
    } while (unique == 0);

    // Saisie des autres informations de l'employe
    printf("Entrez le nom de l'employe : ");
    scanf("%s", e.NOM);

    printf("Entrez le prenom de l'employe : ");
    scanf("%s", e.prenom);

    printf("Entrez la date de naissance (jour mois annee) : ");
    scanf("%d %d %d", &e.naissance.jour, &e.naissance.mois, &e.naissance.annee);

    printf("Entrez l'adresse de l'employe : ");
    scanf(" %[^\n]", e.adresse); // Lire une chaene avec des espaces

    printf("Entrez le numero de telephone de l'employe : ");
    scanf("%s", e.tel);

    // Saisie et verification de l'adresse e-mail
    int emailValide = 0;
    do {
        printf("Entrez l'adresse e-mail de l'employe (doit se terminer par @gmail.com) : ");
        scanf("%s", e.email);

        // Verification que l'e-mail se termine par "@gmail.com"
        char *suffix = "@gmail.com";
        int lenEmail = strlen(e.email);
        int lenSuffix = strlen(suffix);

        if (lenEmail > lenSuffix && strcmp(e.email + lenEmail - lenSuffix, suffix) == 0) {
            emailValide = 1; // L'e-mail est valide
        } else {
            printf("Erreur : L'adresse e-mail doit se terminer par '@gmail.com'. Veuillez reessayer.\n");
        }
    } while (emailValide == 0);

    printf("Entrez le mot de passe de l'employe : ");
    scanf("%s", e.mot_passe);

    // ecriture des informations dans le fichier
    fwrite(&e, sizeof(employe), 1, fichier);

    printf("Employe ajoute avec succes !\n");

    fclose(fichier); // Fermer le fichier
    getchar();
}*/

void AfficherEmploye() {
    SetConsoleOutputCP(CP_UTF8);

    // Déclarer une variable de type employé pour stocker les données lues
    employe e;

    // Ouvrir le fichier en mode lecture binaire
    FILE *fichier = fopen("employes.dat", "rb");

    if (fichier == NULL) {
        printf("\n\t\t╔══════════════════════════════════════════════╗\n");
        printf("\t\t║    Erreur : Impossible d'ouvrir le fichier   ║\n");
        printf("\t\t╚══════════════════════════════════════════════╝\n");
        return;
    }

    printf("\n\t\t╔════════════════════════════════════════╗\n");
    printf("\t\t║        Liste des Employés              ║\n");
    printf("\t\t╚════════════════════════════════════════╝\n\n");

    // Lire chaque employé depuis le fichier et l'afficher
    while (fread(&e, sizeof(employe), 1, fichier) == 1) {
        printf("\t╔═══════════════════════════════════════════════╗\n");
        printf("\t║ Numéro de l'employé : %-18d \n", e.empno);
        printf("\t║ Nom                 : %-18s \n", e.NOM);
        printf("\t║ Prénom              : %-18s \n", e.prenom);
        printf("\t║ Date de naissance   : %02d/%02d/%04d        \n", e.naissance.jour, e.naissance.mois, e.naissance.annee);
        printf("\t║ Adresse             : %-18s \n", e.adresse);
        printf("\t║ Téléphone           : %-18s \n", e.tel);
        printf("\t║ Email               : %-18s \n", e.email);
        printf("\t║ Mot de passe        : %-18s \n", e.mot_passe);
        printf("\t╚═══════════════════════════════════════════════╝\n\n");
    }

    fclose(fichier); // Fermer le fichier après utilisation

    printf("\t\t╔════════════════════════════════════════╗\n");
    printf("\t\t║       Fin de la liste des employés     ║\n");
    printf("\t\t╚════════════════════════════════════════╝\n");
}


/*void AfficherEmploye() {
    SetConsoleOutputCP(CP_UTF8);
    // Declarer une variable de type employe pour stocker les donnees lues
    employe e;

    // Ouvrir le fichier en mode lecture binaire
    FILE *fichier = fopen("employes.dat", "rb");

    if (fichier == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier.\n");
        return;
    }

    printf("\n===== Liste des Employes =====\n");

    // Lire chaque employe depuis le fichier et l'afficher
    while (fread(&e, sizeof(employe), 1, fichier) == 1) {
        printf("Numero de l'employe : %d\n", e.empno);
        printf("Nom : %s\n", e.NOM);
        printf("Prenom : %s\n", e.prenom);
        printf("Date de naissance : %02d/%02d/%04d\n", e.naissance.jour, e.naissance.mois, e.naissance.annee);
        printf("Adresse : %s\n", e.adresse);
        printf("Numero de telephone : %s\n", e.tel);
        printf("Adresse e-mail : %s\n", e.email);
        printf("Mot de passe : %s\n", e.mot_passe);
        printf("-------------------------------\n");
    }

    fclose(fichier); // Fermer le fichier apres utilisation
}*/

void afficherEmploye(employe *emp) {
    SetConsoleOutputCP(CP_UTF8);
    printf("\nInformations actuelles de l'employe :\n");
    printf("Numero d'employe : %d\n", emp->empno);
    printf("Nom : %s\n", emp->NOM);
    printf("Prenom : %s\n", emp->prenom);
    printf("Date de naissance : %02d/%02d/%04d\n", emp->naissance.jour, emp->naissance.mois, emp->naissance.annee);
    printf("Adresse : %s\n", emp->adresse);
    printf("Telephone : %s\n", emp->tel);
    printf("Email : %s\n", emp->email);
    // Le mot de passe n'est pas affiche pour des raisons de securite
}

void modifierEmploye() {
    SetConsoleOutputCP(CP_UTF8);

    FILE *fp = fopen("employes.dat", "r+b");
    if (!fp) {
        printf("\n\t\t╔════════════════════════════════════════╗\n");
        printf("\t\t║  Erreur : Impossible d'ouvrir le fichier. ║\n");
        printf("\t\t╚════════════════════════════════════════╝\n");
        return;
    }

    employe emp;
    int empno, choix, trouve = 0;

    printf("\n\t\t╔════════════════════════════════════════╗\n");
    printf("\t\t║      Modification d'un Employé         ║\n");
    printf("\t\t╚════════════════════════════════════════╝\n");
    printf("\n\t\t ➤ Réponse :Entrez le numéro de l'employé à modifier : ");
    scanf("%d", &empno);
    getchar(); // Consommer le caractère de nouvelle ligne

    rewind(fp);

    while (fread(&emp, sizeof(employe), 1, fp) == 1) {
        if (emp.empno == empno) {
            trouve = 1;

            printf("\n\t\t===== Informations Actuelles =====\n");
            printf("\t╔═══════════════════════════════════════════════╗\n");
            printf("\t║ Numéro : %-30d \n", emp.empno);
            printf("\t║ Nom : %-34s \n", emp.NOM);
            printf("\t║ Prénom : %-31s \n", emp.prenom);
            printf("\t║ Date de Naissance : %02d/%02d/%04d       \n", emp.naissance.jour, emp.naissance.mois, emp.naissance.annee);
            printf("\t║ Adresse : %-30s \n", emp.adresse);
            printf("\t║ Téléphone : %-28s \n", emp.tel);
            printf("\t║ Email : %-33s \n", emp.email);
            printf("\t╚═══════════════════════════════════════════════╝\n");

            printf("\nChoisissez l'information à modifier :\n");
            printf("1. Nom\n2. Prénom\n3. Date de naissance\n4. Adresse\n5. Téléphone\n6. Mot de passe\n7. Email\n");
            printf("Entrez votre choix : ");
            scanf("%d", &choix);
            getchar(); // Consommer le caractère de nouvelle ligne

            switch (choix) {
                case 1:
                    printf("Entrez le nouveau nom : ");
                    fgets(emp.NOM, sizeof(emp.NOM), stdin);
                    emp.NOM[strcspn(emp.NOM, "\n")] = '\0';
                    break;
                case 2:
                    printf("Entrez le nouveau prénom : ");
                    fgets(emp.prenom, sizeof(emp.prenom), stdin);
                    emp.prenom[strcspn(emp.prenom, "\n")] = '\0';
                    break;
                case 3: {
                    int jour, mois, annee, valide;
                    char dateStr[11];
                    do {
                        printf("Entrez la nouvelle date de naissance (jj/mm/aaaa) : ");
                        fgets(dateStr, sizeof(dateStr), stdin);
                        dateStr[strcspn(dateStr, "\n")] = '\0';

                        if (sscanf(dateStr, "%d/%d/%d", &jour, &mois, &annee) == 3) {
                            valide = dateValide(jour, mois, annee);
                            if (!valide) {
                                printf("Date invalide. Veuillez réessayer.\n");
                            }
                        } else {
                            valide = 0;
                            printf("Format invalide. Veuillez entrer la date au format jj/mm/aaaa.\n");
                        }
                    } while (!valide);

                    emp.naissance.jour = jour;
                    emp.naissance.mois = mois;
                    emp.naissance.annee = annee;
                    break;
                }
                case 4:
                    printf("Entrez la nouvelle adresse : ");
                    fgets(emp.adresse, sizeof(emp.adresse), stdin);
                    emp.adresse[strcspn(emp.adresse, "\n")] = '\0';
                    break;
                case 5:
                    printf("Entrez le nouveau numéro de téléphone : ");
                    fgets(emp.tel, sizeof(emp.tel), stdin);
                    emp.tel[strcspn(emp.tel, "\n")] = '\0';
                    break;
                case 6:
                    printf("Entrez le nouveau mot de passe : ");
                    fgets(emp.mot_passe, sizeof(emp.mot_passe), stdin);
                    emp.mot_passe[strcspn(emp.mot_passe, "\n")] = '\0';
                    break;
                case 7:
                    printf("Entrez le nouvel email : ");
                    fgets(emp.email, sizeof(emp.email), stdin);
                    emp.email[strcspn(emp.email, "\n")] = '\0';
                    break;
                default:
                    printf("\nChoix invalide.\n");
                    fclose(fp);
                    return;
            }

            fseek(fp, -(long int)sizeof(employe), SEEK_CUR); // Revenir pour modifier
            fwrite(&emp, sizeof(employe), 1, fp);
            printf("\nLes modifications ont été enregistrées avec succès.\n");

            printf("\n\t\t===== Informations Modifiées =====\n");
            printf("\t╔═══════════════════════════════════════════════╗\n");
            printf("\t║ Numéro : %-30d \n", emp.empno);
            printf("\t║ Nom : %-34s \n", emp.NOM);
            printf("\t║ Prénom : %-31s \n", emp.prenom);
            printf("\t║ Date de Naissance : %02d/%02d/%04d       \n", emp.naissance.jour, emp.naissance.mois, emp.naissance.annee);
            printf("\t║ Adresse : %-30s \n", emp.adresse);
            printf("\t║ Téléphone : %-28s \n", emp.tel);
            printf("\t║ Email : %-33s \n", emp.email);
            printf("\t╔═══════════════════════════════════════════════╝\n");
            break;
        }
    }

    if (!trouve) {
        printf("\n\t\t╔════════════════════════════════════════╗\n");
        printf("\t\t║ Employé avec le numéro %d introuvable. ║\n", empno);
        printf("\t\t╚════════════════════════════════════════╝\n");
    }

    fclose(fp);
}


/*void modifierEmploye() {
    SetConsoleOutputCP(CP_UTF8);
    FILE *fp = fopen("employes.dat", "r+b");
    if (!fp) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }

    employe emp;
    int empno, choix, trouve = 0;

    printf("Entrez le numero de l'employe e modifier : ");
    scanf("%d", &empno);
    getchar(); // Pour consommer le caractere de nouvelle ligne

    rewind(fp);

    while (fread(&emp, sizeof(employe), 1, fp) == 1) {
        if (emp.empno == empno) {
            trouve = 1;
            afficherEmploye(&emp);

            printf("\nChoisissez l'information e modifier :\n");
            printf("1. Nom\n2. Prenom\n3. Date de naissance\n4. Adresse\n5. Telephone\n6. Mot de passe\n7. Email\n");
            printf("Entrez votre choix : ");
            scanf("%d", &choix);
            getchar(); // Pour consommer le caractere de nouvelle ligne

            switch (choix) {
                case 1:
                    printf("Entrez le nouveau nom : ");
                    fgets(emp.NOM, sizeof(emp.NOM), stdin);
                    emp.NOM[strcspn(emp.NOM, "\n")] = '\0';
                    break;
                case 2:
                    printf("Entrez le nouveau prenom : ");
                    fgets(emp.prenom, sizeof(emp.prenom), stdin);
                    emp.prenom[strcspn(emp.prenom, "\n")] = '\0';
                    break;
                case 3: {
                    int jour, mois, annee, valide;
                    char dateStr[11];

                    do {
                        printf("Entrez la nouvelle date de naissance (jj/mm/aaaa) : ");
                        fgets(dateStr, sizeof(dateStr), stdin);
                        dateStr[strcspn(dateStr, "\n")] = '\0';

                        // Verification du format de la date
                        if (sscanf(dateStr, "%d/%d/%d", &jour, &mois, &annee) == 3) {
                            valide = dateValide(jour, mois, annee);
                            if (!valide) {
                                printf("Date invalide. Veuillez reessayer.\n");
                            }
                        } else {
                            valide = 0;
                            printf("Format invalide. Veuillez entrer la date au format jj/mm/aaaa.\n");
                        }
                    } while (!valide);

                    emp.naissance.jour = jour;
                    emp.naissance.mois = mois;
                    emp.naissance.annee = annee;
                    break;
                }
                case 4:
                    printf("Entrez la nouvelle adresse : ");
                    fgets(emp.adresse, sizeof(emp.adresse), stdin);
                    emp.adresse[strcspn(emp.adresse, "\n")] = '\0';
                    break;
                case 5:
                    printf("Entrez le nouveau numero de telephone : ");
                    fgets(emp.tel, sizeof(emp.tel), stdin);
                    emp.tel[strcspn(emp.tel, "\n")] = '\0';
                    break;
                case 6:
                    printf("Entrez le nouveau mot de passe : ");
                    fgets(emp.mot_passe, sizeof(emp.mot_passe), stdin);
                    emp.mot_passe[strcspn(emp.mot_passe, "\n")] = '\0';
                    break;
                case 7:
                    printf("Entrez le nouvel email : ");
                    fgets(emp.email, sizeof(emp.email), stdin);
                    emp.email[strcspn(emp.email, "\n")] = '\0';
                    break;
                default:
                    printf("Choix invalide.\n");
                    fclose(fp);
                    return;
            }

            // Revenir en arriere pour ecraser les donnees de l'employe
            fseek(fp,-(long int)sizeof(employe), SEEK_CUR);
            fwrite(&emp, sizeof(employe), 1, fp);
            printf("Les modifications ont ete enregistrees avec succes.\n");
            afficherEmploye(&emp);
            break;
        }
    }

    if (!trouve) {
        printf("Employe avec le numero %d introuvable.\n", empno);
    }

    fclose(fp);
}*/

void supprimerEmployeParNumero() {
    SetConsoleOutputCP(CP_UTF8);
    FILE *fichierOriginal, *fichierTemp;
    employe emp;
    int trouve = 0;
    int empnoASupprimer;

    printf("\n\t\t╔════════════════════════════════════════╗\n");
    printf("\t\t║        Suppression d'un Employé        ║\n");
    printf("\t\t╚════════════════════════════════════════╝\n");
    printf("\n\t\t➤ Entrez le numéro de l'employé à supprimer : ");
    scanf("%d", &empnoASupprimer);

    fichierOriginal = fopen("employes.dat", "rb");
    if (fichierOriginal == NULL) {
        printf("\n\t\t╔═══════════════════════════════════════════╗\n");
        printf("\t\t║  Erreur : Impossible d'ouvrir le fichier. ║\n");
        printf("\t\t╚═══════════════════════════════════════════╝\n");
        return;
    }

    fichierTemp = fopen("temp.dat", "wb");
    if (fichierTemp == NULL) {
        printf("\n\t\t╔═══════════════════════════════════════════════v══════╗\n");
        printf("\t\t║  Erreur : Impossible de créer un fichier temporaire. ║\n");
        printf("\t\t╚══════════════════════════════════════════════════════╝\n");
        fclose(fichierOriginal);
        return;
    }

    // Lecture et réécriture dans le fichier temporaire
    while (fread(&emp, sizeof(employe), 1, fichierOriginal)) {
        if (emp.empno == empnoASupprimer) {
            trouve = 1;
            continue; // On ne copie pas cet employé dans le fichier temporaire
        }
        fwrite(&emp, sizeof(employe), 1, fichierTemp);
    }

    fclose(fichierOriginal);
    fclose(fichierTemp);

    if (trouve) {
        // Supprimer le fichier original et renommer le fichier temporaire
        if (remove("employes.dat") != 0) {
            printf("\n\t\t╔════════════════════════════════════════════════════════╗\n");
            printf("\t\t║  Erreur : Impossible de supprimer le fichier original. ║\n");
            printf("\t\t╚════════════════════════════════════════════════════════╝\n");
            return;
        }
        if (rename("temp.dat", "employes.dat") != 0) {
            printf("\n\t\t╔════════════════════════════════════════╗\n");
            printf("\t\t║  Erreur : Impossible de renommer le fichier temporaire. ║\n");
            printf("\t\t╚════════════════════════════════════════╝\n");
            return;
        }

        printf("\n\t\t╔═══════════════════════════════════════════════════════════╗\n");
        printf("\t\t║ Employé avec le numéro %d supprimé avec succès !          ║\n", empnoASupprimer);
        printf("\t\t╚═══════════════════════════════════════════════════════════╝\n");

        // Afficher les employés restants
        AfficherEmploye();
    } else {
        remove("temp.dat"); // Supprimer le fichier temporaire inutile
        printf("\n\t\t╔═══════════════════════════════════════════╗\n");
        printf("\t\t║  Aucun employé avec le numéro %d trouvé.  ║\n", empnoASupprimer);
        printf("\t\t╚═══════════════════════════════════════════╝\n");
    }
}


/*void supprimerEmployeParNumero(){
    SetConsoleOutputCP(CP_UTF8);
    FILE *fichierOriginal, *fichierTemp;
    employe emp;
    int trouve = 0;
    int empnoASupprimer;

    // Demande de saisie du numero d'employe e supprimer
    printf("Entrez le numero de l'employe e supprimer : ");
    scanf("%d", &empnoASupprimer);

    fichierOriginal = fopen("employes.dat", "rb");
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

    while (fread(&emp, sizeof(employe), 1, fichierOriginal)) {
        if (emp.empno == empnoASupprimer) {
            trouve = 1;
            // Ne pas ecrire cet employe dans le fichier temporaire
            continue;
        }
        fwrite(&emp, sizeof(employe), 1, fichierTemp);
    }

    fclose(fichierOriginal);
    fclose(fichierTemp);

    if (trouve) {
        // Supprimer le fichier original et renommer le fichier temporaire
        if (remove("employes.dat") != 0) {
            printf("Erreur lors de la suppression du fichier original.\n");
            return;
        }
        if (rename("temp.dat", "employes.dat") != 0) {
            printf("Erreur lors du renommage du fichier temporaire.\n");
            return;
        }
        printf("Employe avec le numero %d supprime avec succes.\n", empnoASupprimer);

        // Appeler la fonction AfficherEmploye() pour afficher les employes restants
        AfficherEmploye();

    } else {
        remove("temp.dat");
        printf("Employe avec le numero %d non trouve.\n", empnoASupprimer);
    }
}*/


void affichenu() {

Options options;
char *MAIN_OPTIONS[]={
    BOLD "AJOUTER UN EMPLOYE",
    BOLD "AFFICHER TOUS LES EMPLOYES",
    BOLD "MODIFIER UN EMPLOYE",
    BOLD "SUPPRIMER UN EMPLOYE",
    BOLD "AFFICHER LES TRANSACTIONS",
    BOLD "AFFICHER LA LISTE DES COMPTES",
    BOLD RED "REVENIR AU MENU PRINCIPAL",
};
    options.title = "MENU ADMINISTRATEUR";
    options.ops = MAIN_OPTIONS;
    options.len = sizeof(MAIN_OPTIONS) / sizeof(MAIN_OPTIONS[0]);

    int option = select_menu(options);
    switch(option){
        case 0:{
            system("cls");
            ajouterEmploye();
            pause();
            system("cls");
            affichenu();
            break;
        }
        case 1:{
            system("cls");
            AfficherEmploye();
            pause();
            system("cls");
            affichenu();
            break;
        }
        case 2:{
            system("cls");
            modifierEmploye();
            pause();
            system("cls");
            affichenu();
            break;
        }
        case 3:{
            system("cls");
            supprimerEmployeParNumero();
            pause();
            system("cls");
            affichenu();
            break;
        }
        case 4:{
            system("cls");
            afficherTransactionsParId();
            pause();
            system("cls");
            affichenu();
            break ;
        }
        case 5:{
            system("cls");
            afficherComptes();
            pause();
            system("cls");
            affichenu();
            break ;
        }
        case 6:{
            system("cls");
            AfficherMenuPrincipale();
            break;
        }
    }
}

#endif // ADMIN_H
