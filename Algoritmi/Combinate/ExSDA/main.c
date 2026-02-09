#include <stdio.h>
#include <stdlib.h>
#define maxi 10

typedef struct {
    int id;
    float medie;
    int an;
}Student;

typedef struct Anul{
    int val;
    int top;
    Student *stiva;
    struct Anul *next;

}Anul;

void adaugare_primu_nod(Anul **aux, int val, Student st) {
     (*aux)->val = val;
     (*aux)->top = 0;
     (*aux)->next = NULL;
     (*aux)->stiva = malloc(sizeof(Anul) * maxi);
     (*aux)->stiva[(*aux)->top] = st;
}


void crearea_lista_an(Anul **head, Student *st, int n) {
    Anul *aux = *head;
    for (int i = 0; i < n; i ++) {
        if (aux == NULL) { //adaugare primul nod
            aux = malloc(sizeof(Anul));
            aux->top = -1;
            adaugare_primu_nod(&aux, st[i].an, st[i]);
            *head = aux;
        }

        else {
            if (st[i].an == aux->val) { //adaugare la stiva daca nodul deja exista
                aux->top++;
                aux->stiva[aux->top] = st[i];
            }
            else { //adaugare nod next
                aux->next = malloc(sizeof(Anul));
                aux = aux->next;
                aux->val = st[i].an;
                aux->top = 0;
                aux->stiva = malloc(sizeof(Anul) * maxi);
                aux->stiva[aux->top] = st[i];
                aux->next = NULL;
            }
        }

    }
}

void afisare_lista_studenti(Anul *l, FILE *out) {
    while (l->top >= 0) {
        fprintf(out, "  %.2f %d\n", l->stiva[l->top].medie, l->stiva[l->top].id);
        l->top--;
    }
}

void afisare_lista(Anul *l, FILE *out) {
    while (l != NULL) {
        fprintf(out, "%d:\n", l->val);
        afisare_lista_studenti(l, out);
        l = l->next;
    }
}

void eliberare(Anul *l) {
    while (l != NULL) {
        Anul *urm = l->next;
        free(l->stiva);
        free(l);
        l = urm;
    }
}

void medie_recursiv(Student *st, int i, int n, float bursa_medie, int anul_trecut, FILE *out) {
    if (i == n) {
        return;
    }
    if (st[i].medie >= bursa_medie && st[i].an == anul_trecut) {
        fprintf(out, "%d %.2f\n", st[i].id, st[i].medie);
    }
    medie_recursiv(st, i+1, n, bursa_medie, anul_trecut, out);
}


void swap(Student *a, Student *b) {
    Student aux = *a;
    *a = *b;
    *b = aux;
}

void QuickSort(Student *arr, int st, int dr) {
    int i = st;
    int j = dr;

    Student pivot = arr[(st + dr) / 2];

    while (i <= j) {

        while (arr[i].an < pivot.an || (arr[i].an == pivot.an && arr[i].medie < pivot.medie)) {
            i++;
        }

        while (arr[j].an > pivot.an || (arr[j].an == pivot.an && arr[j].medie > pivot.medie)) {
            j--;
        }

        if (i <= j) {
            swap(&arr[i], &arr[j]);
            i++;
            j--;
        }
    }
    if (st < j) {
        QuickSort(arr, st, j);
    }
    if (i < dr) {
        QuickSort(arr, i, dr);
    }
}


void QuickSortDescMedie(Student *arr, int st, int dr) { //pentru Greedy
    int i = st;
    int j = dr;

    Student pivot = arr[(st + dr) / 2];
    while (i <= j) {
        while (arr[i].medie > pivot.medie) {
            i++;
        }

        while (arr[j].medie < pivot.medie) {
            j--;
        }

        if (i <= j) {
            swap(&arr[i], &arr[j]);
            i++;
            j--;
        }
    }

    if (st < j) {
        QuickSortDescMedie(arr, st, j);
    }
    if (i < dr) {
        QuickSortDescMedie(arr, i, dr);
    }
}

void afisare_studenti(Student *st, int n) {
    for (int i = 0; i < n; i++) {
        printf(" %d %.2f %d\n", st[i].id, st[i].medie, st[i].an);
    }
    printf("\n");
}

void Greedy(Student *st, Student ant, int i, int n, float M, int *nr_grupe, float *sum, FILE *out) {

    if (i >= n) {
        if (*sum <= M) {
            (*nr_grupe)++;
        }
        fprintf(out, "NUMAR GRUPE: %d\n", *nr_grupe);
        return;
    }

    if (((*sum) + st[i].medie <= M) && (ant.medie - st[i].medie <= 1.0)) {
        (*sum) += st[i].medie;
    }
    else {
        *sum = st[i].medie;
        ant = st[i];
        (*nr_grupe)++;
    }
    Greedy(st, ant, i + 1, n, M, nr_grupe, sum, out);
}


int main(int argc, char **argv) {
     if (argc != 3) {
         fprintf(stderr, "Nr argumente insuficient");
         exit(1);
     }

     FILE *f = fopen(argv[1], "r");
     if (f == NULL) {
         perror("Fisier intrare:");
         exit(1);
     }

     FILE *out = fopen(argv[2], "w");
     if (out == NULL) {
         perror("Fisier iesire:");
         exit(1);
     }
    int n;
    float M;
    fscanf(f, "%d %f", &n, &M);

    int id, an;
    float medie;

    Student *st = malloc(sizeof(Student) * n);

    for (int i = 0; i < n; i++) {
        int aux = fscanf(f, "%d %f %d", &id, &medie, &an);
        if (aux == 3) {
            st[i].id = id;
            st[i].medie = medie;
            st[i].an = an;
        }
        else {
            fprintf(stderr, "Date incorecte/incomplete");
            exit(1);
        }
    }
  //  afisare_studenti(st, n);
    QuickSort(st, 0, n-1);
    afisare_studenti(st, n);
    Anul *head = NULL;
    crearea_lista_an(&head, st, n);
    afisare_lista(head, out);

    fprintf(out, "studenti bursieri:\n");
    medie_recursiv(st, 0, n, 9.50, 2, out);

    QuickSortDescMedie(st, 0, n-1);
    afisare_studenti(st, n);

    int nr_grupe = 0;
    float sum = 0;
    Student ant = st[0];
    Greedy(st, ant, 0, n, M, &nr_grupe, &sum, out);

    if (head != NULL) {
        eliberare(head);
    }
    free(st);
    fclose(f);
    fclose(out);
    return 0;
}