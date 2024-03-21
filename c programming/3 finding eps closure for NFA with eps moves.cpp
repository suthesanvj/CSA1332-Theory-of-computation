#include<stdio.h>
#include<string.h>

int trans_table[10][5][3];
char symbol[5];
int e_closure[10][10], ptr, state;

void find_e_closure(int x);

int main() {
    int i, j, k, n, num_states, num_symbols;

    for (i = 0; i < 10; i++) {
        for (j = 0; j < 5; j++) {
            for (k = 0; k < 3; k++) {
                trans_table[i][j][k] = -1;
            }
        }
    }

    printf("How many states in the NFA with e-moves: ");
    scanf("%d", &num_states);
    printf("How many symbols in the input alphabet including e: ");
    scanf("%d", &num_symbols);
    printf("Enter the symbols without space. Give 'e' first: ");
    scanf("%s", symbol);

    for (i = 0; i < num_states; i++) {
        for (j = 0; j < num_symbols; j++) {
            printf("How many transitions from state %d for the input %c: ", i, symbol[j]);
            scanf("%d", &n);
            for (k = 0; k < n; k++) {
                printf("Enter the transitions %d from state %d for the input %c: ", k + 1, i, symbol[j]);
                scanf("%d", &trans_table[i][j][k]);
            }
        }
    }

    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            e_closure[i][j] = -1;
        }
    }

    for (i = 0; i < num_states; i++) {
        state = i;
        ptr = 0;
        find_e_closure(i);
    }

    for (i = 0; i < num_states; i++) {
        printf("e-closure(%d)= {", i);
        for (j = 0; j < num_states; j++) {
            if (e_closure[i][j] != -1) {
                printf("%d, ", e_closure[i][j]);
            }
        }
        printf("}\n");
    }

    return 0;
}

void find_e_closure(int x) {
    int i, j, y;

    for (i = 0; i < 3; i++) { // Assuming epsilon transitions are always represented by index 0
        y = trans_table[x][0][i];
        if (y != -1) {
            e_closure[state][ptr++] = y;
            find_e_closure(y);
        }
    }
}

