#include <stdio.h>
#include <stdlib.h>


/*
Algoritm DivImp(P)
    Dacă P este problemă elementară
        R <- RezolvăDirect(P)
    Altfel
        [P1,P2] <- Descompune(P)
        R1 <- DivImp(P1)
        R2 <- DivImp(P2)
        R <- Combină(R1,R2)
    SfârșitDacă
SfârșitAlgoritm

6
0 1 2 3 4 5
4 1 8 4 3 5

4 1 8     avem  4  si apoi 1 8  -->   apoi 1 si 8 revenim -> 9 + 4 -> 13  ->
4 3 5     avem 4 si apoi 3 5 -->   3 si  5 revenim -> 8 + 4 = 12             ->   25


 */

int Divide(int a[], int st, int dr) {
    if (st == dr) {
        return a[st];
    }
    else {
        int m = (st + dr) / 2;
        int s1 = Divide(a, st, m);
        int s2 = Divide(a, m+1, dr);
        return s1 + s2;
    }
}



int main(void) {
    int n;
    int *a;

    scanf("%d", &n);
    a = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int s = Divide(a, 0, n-1);
    printf("%d\n", s);
    free(a);
    return 0;

}
