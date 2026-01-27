#include <stdio.h>
#include <stdlib.h>
const int di[]= {-1, -2, -2, -1, 1, 2, 2, 1};
const int dj[]= {2, 1, -1, -2, -2, -1, 1, 2};

typedef struct Matrice {
    int n, m;
    int a[10][10];
    int b[10][10];
}Matrice;

/*
 * Putem folosi Bk in plan pentru ca:
   - lucram cu un tablou bidimensional (matrice)
   - dimensiunea tabloului este fixa n x m
   - elementele tabloului apartin unei multimi finite
        + la fiecare pas putem face un nr maxim (finit) de 8 pasi
 */

void afisare_matrice(int (*a)[10], int n, int m, FILE *out);

int valid(Matrice *mat, int i, int j, int *sol) {
    if (*sol == 1) { //daca am gasit o solutie, ne oprim;
        return 0;
    }
    if (i < 0 || j < 0 || i >= mat->n || j >= mat->m) { //ne incadram in dimensiunea matricei
        return 0;
    }
    if (mat->a[i][j] != 0 || mat->b[i][j] != 0) { //trebuie sa fie pozitie valida
        return 0;
    }
    return 1;
}

int solutie(Matrice *mat, int i, int j) {
    if (i == mat->n-1 && j == mat->m-1) { //daca am ajuns pe poz de final, return 1 -> avem sol
        return 1;
    }
    return 0;
}

void Bk(Matrice *mat, int i, int j, int pas, int *sol, FILE *out) {
    if (!valid(mat, i, j, sol)) {
        return;
    }
    mat->b[i][j] = pas;
    if (solutie(mat, i, j)) { //daca am gasit o solutie, putem sa iesim (return) din cautare
        *sol = 1;
        afisare_matrice(mat->b, mat->n, mat->m, out); //afisam solutia gasita
        return;
    }
    for (int k = 0; k < 8; k ++) {
         Bk(mat, i + di[k], j + dj[k], pas + 1, sol, out);
    }
    mat->b[i][j] = 0;
}


void construire_matrice(Matrice *mat, FILE *f) {
    for (int i = 0; i < mat->n; i ++) {
        for (int j = 0; j < mat->m; j ++) {
            fscanf(f, "%d", &mat->a[i][j]);
            mat->b[i][j] = 0;
        }
    }
}

void afisare_matrice(int (*a)[10], int n, int m, FILE *out) {
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < m; j ++) {
            fprintf(out, "%d ", a[i][j]);
        }
        fprintf(out, "\n");
    }
}

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Nr incorect de argumente\n");
        exit(1);
    }
    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        perror("Eroare fisier citire");
        exit(1);
    }

    FILE *out = fopen(argv[2], "w");
    if (out == NULL) {
        perror("Eroare fisier iesire");
        exit(1);
    }

    Matrice mat; //pastram valorile pe stiva (nu pe heap folosing malloc) pentru ca avem suficient spatiu
    fscanf(f, "%d %d", &mat.n, &mat.m);
    construire_matrice(&mat, f);
   // afisare_matrice(mat.a, mat.n, mat.m, out);
    int sol = 0;
    Bk(&mat, 0, 0, 1, &sol, out);
    if (sol == 0) {
        afisare_matrice(mat.b, mat.n, mat.m, out);  //mat.b va fi 0 la final indiferent
    }
    fclose(f);
    fclose(out);
    return 0;
}