#ifndef HISTORIQUETRANSACTION_H
#define HISTORIQUETRANSACTION_H

#include <stdlib.h>
#include <stdio.h>
#include "structure.h"
#include <ctype.h>

void afficherTransactionsParId() {
    utilisateur utilisa;
    FILE *fp = fopen("transactions.dat", "rb");
    if (fp == NULL) {
        printf("\n\t\t\t⚠️ Erreur lors de l'ouverture du fichier des transactions.\n");
        return;
    }

    Transaction trans;
    char identifiantRecherche[20];
    int found = 0;

    printf("\n\t\t\t╔════════════════════════════════════════════════╗\n");
    printf("\t\t\t║            📑 Transactions 📑                  ║\n");
    printf("\t\t\t╚════════════════════════════════════════════════╝\n");

    // Demander l'identifiant à rechercher
    printf("\n\t\t\t╔════════════════════════════════════════════════╗\n");
    printf("\t\t\t║ Entrez l'identifiant pour voir les transactions║\n");
    printf("\t\t\t╚════════════════════════════════════════════════╝\n");
    printf("\t\t\t➤ Réponse : ");
    fflush(stdin);
    fgets(identifiantRecherche, sizeof(identifiantRecherche), stdin);
    identifiantRecherche[strcspn(identifiantRecherche, "\n")] = 0;  // Enlever le newline

    printf("\n\t\t\t╔════════════════════════════════════════════════╗\n");
    printf("\t\t\t║ Transactions sont :                            ║\n");
    printf("\t\t\t╚════════════════════════════════════════════════╝\n");

    // Affichage de l'en-tête du tableau
    printf("\n\t\t\t╔════════════╦══════════════╦══════════════════╦════════════╦════════════════════════╗\n");
    printf("\t\t\t║   Date     ║  Montant     ║ Nouveau Solde    ║    Type    ║          Motif         ║\n");
    printf("\t\t\t╠════════════╬══════════════╬══════════════════╬════════════╬════════════════════════╣\n");

    while (fread(&trans, sizeof(Transaction), 1, fp) == 1) {
        if (strcmp(trans.identifiant, identifiantRecherche) == 0) {
            printf("\t\t\t║ %02d/%02d/%04d ║ %9.2f DH ║ %13.2f DH ║ %-10s ║ %-22s ║\n",
                   trans.dateTransaction.jour,
                   trans.dateTransaction.mois,
                   trans.dateTransaction.annee,
                   trans.montant,
                   trans.nouveauSolde,
                   trans.type,
                   trans.motif[0] ? trans.motif : "Pas de motif");
            found = 1;
        }
    }

    // Si aucune transaction n'est trouvée pour cet identifiant
    if (found == 0) {
        printf("\t\t\t╔════════════════════════════════════════════════╗\n");
        printf("\t\t\t║  Aucune transaction trouvée pour cet identifiant ║\n");
        printf("\t\t\t╚════════════════════════════════════════════════╝\n");
    }

    fclose(fp);
}


/*
void afficherTransactionsParId() {
    FILE *fp = fopen("transactions.dat", "rb");
    if (fp == NULL) {
        printf("Erreur lors de l'ouverture du fichier des transactions.\n");
        return;
    }

    Transaction trans;
    char identifiantRecherche[20];
    int found = 0;

    printf("Entrez l'identifiant pour voir toutes les transactions : ");
    fflush(stdin);
        fgets(identifiantRecherche, sizeof(identifiantRecherche), stdin);
        // Optionally remove the trailing newline:
        identifiantRecherche[strcspn(identifiantRecherche, "\n")] = 0;  // Eliminer le newline

    printf("\nTransactions pour %s:\n", identifiantRecherche);
    printf("| Date       | Montant   | Nouveau Solde | Type      | Motif                     |\n");
    printf("|------------|-----------|---------------|-----------|---------------------------|\n");

    while (fread(&trans, sizeof(Transaction), 1, fp) == 1) {  // S'assurer de la condition de boucle
        if (strcmp(trans.identifiant, identifiantRecherche) == 0) {
            printf("| %02d/%02d/%04d | %9.2f | %13.2f | %-9s | %-25s |\n",
                   trans.dateTransaction.jour,
                   trans.dateTransaction.mois,
                   trans.dateTransaction.annee,
                   trans.montant,
                   trans.nouveauSolde,
                   trans.type,
                   trans.motif[0] ? trans.motif : "Pas de motif ");
            found = 1;
        }
    }

    if (found==0) {
        printf("| Aucune transaction trouv�e pour cet identifiant\n");
}fclose(fp);}*/

void enregistrerTransaction(Transaction trans) {
    FILE *fp = fopen("transactions.dat", "ab");
    if (fp == NULL) {
        printf("Erreur d'ouverture du fichier des transactions.\n");
        return;
    }

    fwrite(&trans, sizeof(Transaction), 1, fp);
    fclose(fp);

    printf("\t\t\tTransaction enregistr�e le %02d/%02d/%04d.\n",
           trans.dateTransaction.jour,
           trans.dateTransaction.mois,
           trans.dateTransaction.annee);
}

#endif // HISTORIQUETRANSACTION_H
