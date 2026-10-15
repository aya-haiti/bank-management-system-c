#ifndef DATE_H
#define DATE_H

#include <windows.h>
#include <ctype.h>

 typedef struct {
    int jour;
    int mois;
    int annee;
} Date; // Nom mod


Date time() {
    Date d;
    SYSTEMTIME Time;
    GetLocalTime(&Time);
    d.jour = Time.wDay;
    d.mois = Time.wMonth;
    d.annee = Time.wYear;
    return d;
}

Date obtenirDateActuelle() {
    SYSTEMTIME Time;
    GetLocalTime(&Time);
    Date d;
    d.jour = Time.wDay;
    d.mois = Time.wMonth;
    d.annee = Time.wYear;
    return d;
}


int estBissextile(int annee) {
    return (annee % 4 == 0 && (annee % 100 != 0 || annee % 400 == 0));
}

int joursDansMois(int mois, int annee) {
    int joursParMois[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (mois == 2 && estBissextile(annee)) {
        return 29;
    }
    return joursParMois[mois - 1];
}



int dateValide(int jour, int mois, int annee) {
    if (annee < 1900 || annee > 2100)
        return 0;
    if (mois < 1 || mois > 12)
        return 0;
    if (jour < 1 || jour > joursDansMois(mois, annee))
        return 0;
    return 1;
}

#endif // DATE_H
