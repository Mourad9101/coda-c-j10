#include "struct.h"

int verifierVictoire(Element board[HEIGHT][WIDTH]);

void initialiser_plateau(Element board[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1) {
                board[i][j] = WALL;
            } else {
                board[i][j] = EMPTY;
            }
        }
    }
}

void afficher_plateau(Element board[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}

void spawnJoueur(Element board[HEIGHT][WIDTH], PositionJoueur* joueurPos) {
    int x, y;
    do {
        x = rand() % (HEIGHT - 2) + 1;
        y = rand() % (WIDTH - 2) + 1;
    } while (board[x][y] != EMPTY);

    board[x][y] = PLAYER;
    joueurPos->x = x;
    joueurPos->y = y;
}

void spawnBox(Element board[HEIGHT][WIDTH]) {
    int x, y;
    int estAdjacenteMur;

    do {
        x = rand() % (HEIGHT - 2) + 1;
        y = rand() % (WIDTH - 2) + 1;
        
        estAdjacenteMur = (board[x-1][y] == WALL || board[x+1][y] == WALL || 
                           board[x][y-1] == WALL || board[x][y+1] == WALL);
    } while (board[x][y] != EMPTY || estAdjacenteMur);

    board[x][y] = BOX;
}

void spawnEmplacement(Element board[HEIGHT][WIDTH]) {
    int x, y;
    do {
        x = rand() % (HEIGHT - 2) + 1;
        y = rand() % (WIDTH - 2) + 1;
    } while (board[x][y] != EMPTY);

    board[x][y] = GOAL;
}

void DeplacementJoueur(Element board[HEIGHT][WIDTH], PositionJoueur* joueurPos, char direction) {
    int x = joueurPos->x;
    int y = joueurPos->y;
    int nouveauX = x, nouveauY = y;

    if (direction == 'w') nouveauX--;
    else if (direction == 's') nouveauX++;
    else if (direction == 'a') nouveauY--;
    else if (direction == 'd') nouveauY++;
    else {
        printf("Le mouvement n'existe pas! Utilise 'w', 's', 'a' ou 'd'.\n");
        return;
    }

    if (board[nouveauX][nouveauY] != WALL) {
        board[x][y] = EMPTY;
        board[nouveauX][nouveauY] = PLAYER;
        joueurPos->x = nouveauX;
        joueurPos->y = nouveauY;
    } else {
        printf("Vous ne pouvez pas passer à travers un mur !\n");
    }
}

void DeplacementBox(Element board[HEIGHT][WIDTH], PositionJoueur* joueurPos, char direction) {
    int x = joueurPos->x;
    int y = joueurPos->y;
    int boxX = x, boxY = y;

    if (direction == 'w') boxX--;
    else if (direction == 's') boxX++;
    else if (direction == 'a') boxY--;
    else if (direction == 'd') boxY++;

    if (board[boxX][boxY] == BOX) {
        int newBoxX = boxX + (boxX - x);
        int newBoxY = boxY + (boxY - y);

        if (board[newBoxX][newBoxY] != WALL && board[newBoxX][newBoxY] != BOX) {
            board[newBoxX][newBoxY] = BOX;
            board[boxX][boxY] = PLAYER;
            board[x][y] = EMPTY;
            joueurPos->x = boxX;
            joueurPos->y = boxY;

            if (verifierVictoire(board)) {
                printf("Bravo, vous avez gagné !\n");
                exit(0);
            }
        } else {
            printf("Vous ne pouvez pas pousser en dehors du plateau. !\n");
        }
    } else {
        DeplacementJoueur(board, joueurPos, direction);
    }
    if ((boxX > 0 && board[boxX - 1][boxY] == WALL) && 
        (boxX < HEIGHT - 1 && board[boxX + 1][boxY] == WALL) &&
        (boxY > 0 && board[boxX][boxY - 1] == WALL) &&
        (boxY < WIDTH - 1 && board[boxX][boxY + 1] == WALL)) {
        printf("La boîte est coincée contre le mur. Vous avez donc perdu.\n");
        exit(0);
    }
}


int verifierVictoire(Element board[HEIGHT][WIDTH]) {
    for (int i = 1; i < HEIGHT - 1; i++) {
        for (int j = 1; j < WIDTH - 1; j++) {
            if (board[i][j] == BOX && board[i][j] != GOAL) {
                return 0;
            }
        }
    }
    return 1;
}

int main() {
    Element board[HEIGHT][WIDTH];
    PositionJoueur joueurPos;

    srand(time(NULL));

    initialiser_plateau(board);
    spawnBox(board);
    spawnEmplacement(board);
    spawnJoueur(board, &joueurPos);

    afficher_plateau(board);

    char direction;
    while (1) {
        printf("Choisissez un mouvement: haut (w), bas (s), droite (d), gauche (a) ou m pour quitter ");
        scanf(" %c", &direction);

        if (direction == 'm') {
            break;
        }

        DeplacementBox(board, &joueurPos, direction);
        afficher_plateau(board);
        
    }

    return 0;
} 

