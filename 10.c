#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#define MAX_PRINT 20

int read_matrix(double * a, int m, int n, const char * name);
double f(int i, int j);
void init_matrix(double * a, int m, int n);
void print_matrix(double *a, int m, int n);
void solve(double * a, double * b , double * c, int m, int n, int k);


int read_matrix(double * a, int m, int n, const char * name) {
    int len = n * m; int i;
    FILE * fp;
    if(!(fp  = fopen(name, "r"))) return 0;
    for(i = 0; i < len; i++) {
        if(fscanf(fp, "%lf", a + i) != 1) return -1;
    }
    fclose(fp);
    return i;
}

double f(int i, int j) {
    return i * j + i + j - 2;
}

void init_matrix(double * a, int m, int n) {
    int i, j;
    for(i = 0; i < m; i++) 
        for(j = 0; j < n; j++) 
        a[i * n + j] = f(i, j);
}

void print_matrix(double *a, int m, int n) {
    int i , j; int mp = (m > MAX_PRINT) ? MAX_PRINT : m; int np = (n > MAX_PRINT) ? MAX_PRINT : n;
    for(i = 0; i < m; i++) {
        for(j = 0; j < n; j++)
            printf(" %f", a[i * n + j]);
        printf("\n");
    }
}

void solve(double * a, double * b , double * c, int m, int n, int k) {
    for(int i = 0; i < m; i++)
        for(int j = 0; j < k; j++)
            for(int t = 0; t < n; t++)
                c[i * k + j] += a[i * n + t] * b[t * k + j];
}


int main(int argc, char * argv[]) {
    double * a; double t;
    int n, m, k; int i, j;
    char * name1 = 0; char * name2 = 0;
    double *b, *c;
    if(argc < 4 || argc > 6 || (m = atoi(argv[1])) == 0 || (n = atoi(argv[2])) == 0 || (k = atoi(argv[3])) == 0)  {
        printf("Wrong input!\n");
        return 1;
    }
    if(argc == 5) name1 = argv[4];
    if(argc == 6) {
        name1 = argv[4];
        name2 = argv[5];
    }
    if(!(b = (double *) malloc (n * k * sizeof(double)))) {
        printf("Not enough memory!\n");
        return 2;
    }
    if(!(c = (double *) malloc (m * k * sizeof(double)))) {
        printf("Not enough memory!\n");
        return 2;
    }
    if(!(a = (double *) malloc (n * m * sizeof(double)))) {
        printf("Not enough memory!\n");
        return 2;
    }
    for(int i = 0; i < m * k; i++)
        c[i] = 0;
    if(name1) {
        int ret = read_matrix(a, m, n, name1);
        if(ret < 0) {
            free(a); free(b); free(c);
            return 1;
        }
    }
    else init_matrix(a, m, n);
    if(name2) {
        int ret2 = read_matrix(b, n, k, name2);
        if(ret2 < 0) {
            free(a); free(b); free(c);
            return 1;
        }
    }
    else init_matrix(b, n, k);
    print_matrix(a, m, n);
    printf("\n");
    print_matrix(b, n, k);
    printf("\n");
    t = clock();
    solve(a, b, c, m, n, k);
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf("The product is is\n");
    print_matrix(c, m, k);
    printf("Elapsed %.2f\n", t);
    free(a); free(b); free(c);
    return 0;
}