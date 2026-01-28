#include <stdio.h>
#define maxi 10

int v[maxi], x[maxi];
int sol = 0;


/*
    Se consideră n tipuri de bancnote, cu valorile v[1] v[2] ... v[n], ordonate strict crescător.
    Se cere să se determine o modalitate de a plăti integral o sumă dată S cu bancnotele disponibile,
    știind că se pot folosi oricâte bancnote de orice tip.


     Date intrare:
        5 375
        1 5 10 50 100
 */

/*
      Problema poate fi rezolvata cu backtracking pentru ca:
        - solutia x[] poate fi reprez sub forma unui tablou de valori
        - solutia x[] va contine cate din cele n bancote au fost folosite -> n - finit deci dimensiunea lui x[] e finita
        - x[i] ia valori dintr-o multime finita, (0,S) (unde 1 <= S <= 1000)
 */

void afisare(int n) {
    sol = 1;  // marcam ca am gasit o solutie
    for (int i = 0; i < n; i ++) {
        printf("%d ", x[i]);
    }
}

int valid(int k, int sum, int S) {
    if (sum + x[k] * v[k] <= S) { //daca inca nu am ajuns la suma, e mai mica decat trebuie, continuam
        return 1;
    }
    return 0;
}

int solutie(int k, int sum, int n, int S) {
    if ((k == n - 1) && (sum + x[k] * v[k] == S)) { //daca am luat la rand fiecare bancnota de un nr >= 0 ori, si am ajuns suma necesara -> avem solutie
        return 1;
    }
    return 0;
}

void Bk(int k, int sum, int n, int S) {
    if (k < n) {
        for (int i = 0; i <= (S - sum) && !sol; i ++) { //optimizare: mergem de fiecare daca pana la (S-sum)/v[k] (rezulta din sum + x[k] * v[k] == S)
            x[k] = i;
            if (valid(k, sum, S)) {
                if (solutie(k, sum, n, S)) {
                    afisare(n);
                }
                else {
                    Bk(k+1, sum + x[k] * v[k], n, S);
                }
            }
        }
    }
}

int main(void) {
    int n, S;
    scanf("%d %d", &n, &S);

    for (int i = 0; i < n; i ++) {
        scanf("%d", &v[i]);
    }

    Bk(0, 0, n, S);
    return 0;

}