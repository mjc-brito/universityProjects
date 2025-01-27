#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "game.h"
#include <cstdlib>
#include <time.h>    
#include "sequencia.h"

#define MAXNAME 50
#define CAPACIDADE 9

typedef struct _part {   // estrutura de uma peça
    char type;
    char player[MAXNAME];
    int turn;
    char* date;
    int coordX;
    int coordZ;
    int turnRemoved;
}part;

int gamemode;
int difficulty;
int gametype;
char player1[MAXNAME];
char player2[MAXNAME];
char matrix[3][3];
//sequencia storedParts = criaSequencia(CAPACIDADE);
//sequencia removedParts = criaSequencia(CAPACIDADE);
part storedList[CAPACIDADE];   // Lista de peças guardadas
int numElems = 0;
part removedParts[CAPACIDADE * 3];
int numRemovidos = 0;

void savegamedata(int gamemode1, int difficulty1, int gametype1,char* player11, char* player21) {
    gamemode = gamemode1;
    difficulty = difficulty1;
    gametype = gametype1;
    switch (gamemode) {
    case 1:
        strcpy_s(player1, player11);
        strcpy_s(player2, player21);
        break;
    case 2:
        strcpy_s(player1, player11);
        strcpy_s(player2, "PC");
        break;
    case 3:
        strcpy_s(player1, "PC1");
        strcpy_s(player2, "PC2");
        break;
    default:
        break;
    }
    
}

void gamestructure() {
    int x = 0;
    int z = 2;
    for (z = 2; z >= 0; z--) {
        printf("           ");
        for (x = 0; x < 3; x++) {
            printf("[ %d ] ", matrix[x][z]);
        }
        printf("\n");
    }
}

void inicializamatriz() {
    int x = 0;
    int z = 0;
    for (x = 0; x < 3; x++) {
        for (z = 0; z < 3; z++) {
            matrix[x][z] = 0;
        }
    }
}

void printPlayer1Game() {
    char aux[MAXNAME];
    int x = 0, z = 2;
    int n = 0;
    char matrixp1[3][3];

    for (z = 2; z >= 0; z--) {
        for (x = 0; x < 3; x++) {
            if (matrix[x][z] == 1) {
                aux[n] = x + 49;
                n++;
                aux[n] = ',';
                n++;
                aux[n] = z + 49;
                n++;
                aux[n] = '\n';
                n++;
                matrixp1[x][z] = 'X';
            }
            else
                matrixp1[x][z] = ' ';
        }
    }
    printf("X's coordinates:\n%s", aux);
    printf("\n");
    for (z = 2; z >= 0; z--) {
        printf("           ");
        for (x = 0; x < 3; x++) {
            printf("[ %c ] ", matrixp1[x][z]);
        }
        printf("\n");
    }
    printf("\n");
}

void printPlayer2Game() {
    char aux[MAXNAME];
    int x = 0, z = 2;
    int n = 0;
    char matrixp2[3][3];

    for (z = 2; z >= 0; z--) {
        for (x = 0; x < 3; x++) {
            if (matrix[x][z] == 2) {
                aux[n] = x + 49;
                n++;
                aux[n] = ',';
                n++;
                aux[n] = z + 49;
                n++;
                aux[n] = '\n';
                n++;
                matrixp2[x][z] = 'O';
            }
            else
                matrixp2[x][z] = ' ';
        }
    }
    printf("O's coordinates:\n %s", aux);
    printf("\n");
    for (z = 2; z >= 0; z--) {
        printf("           ");
        for (x = 0; x < 3; x++) {
            printf("[ %c ] ", matrixp2[x][z]);
        }
        printf("\n");
    }
    printf("\n");
}

void printPlayerNames(int playerturn) {
    if(playerturn == 1)
        printf("\n<---------------%s's turn--------------->\n", player1);
    if(playerturn == 2)
        printf("\n<---------------%s's turn--------------->\n", player2);
}

void atualizaMatriz(int playerturn, int x, int z, int type) {
    if (playerturn == 1 && type == 0)
        matrix[x - 1][z - 1] = 1;
    if (playerturn == 2 && type == 0)
        matrix[x - 1][z - 1] = 2;
    if (playerturn == 1 && type == 1)
        matrix[x - 1][z - 1] = 0;
    if (playerturn == 2 && type == 1)
        matrix[x - 1][z - 1] = 0;
}

int checkCell(int x, int z) {
    /*if (matrix[x - 1][z - 1] == 0)
        return 0;
    else
        return 1;*/
    return matrix[x - 1][z - 1];
}

int getGamemode() {
    return gamemode;
}

int getGametype() {
    return gametype;
}

char* getNamePlayer1() {
    return player1;
}

char* getNamePlayer2() {
    return player2;
}

char* getRandomCell() {
    srand((unsigned)time(NULL));
    int x = 0;
    int z = 0;
    char aux[2];

    x = 1 + (rand() % 3);
    z = 1 + (rand() % 3);

    printf("x:%d z:%d\n",x,z);
    aux[0] = x;
    aux[1] = z;

    return aux;
}

int getRandomType() {
    srand((unsigned)time(NULL));

    int x = 1 + (rand() % 2);

    return x;
}

int  checkWinner() {
    int winner;

    for (int i = 0; i <= 2; i++) {             // any of the rows is the same
        if (matrix[i][0] == matrix[i][1] && matrix[i][1] == matrix[i][2] && matrix[i][0] != 0) {
            winner = matrix[i][0];
            return winner;
        }
    }

    for (int i = 0; i <= 2; i++) {              // any of the columns is the same
        if (matrix[0][i] == matrix[1][i] && matrix[1][i] == matrix[2][i] && matrix[0][i] != 0) {
            winner = matrix[0][i];
            return winner;
        }
    }

    if (matrix[0][0] == matrix[1][1] && matrix[1][1] == matrix[2][2] && matrix[0][0] != 0) {  // 1st diagonal is the same
        winner = matrix[0][0];
        return winner;
    }

    if (matrix[0][2] == matrix[1][1] && matrix[1][1] == matrix[2][0] && matrix[0][2] != 0) {   // 2nd diagonal is the same
        winner = matrix[0][2];
        return winner;
    }

    // if we reached this point nobody has won yet

    for (int i = 0; i <= 2; i++) { // if any empty box on board then keep playing
        for (int j = 0; j <= 2; j++) {
            if (matrix[i][j] == 0) {
                winner = 0;
                return winner;
            }
        }
    }

    winner = -1; // all boxes full and nobody won so a tie has occurred
    return winner;
}

void addPart_storedList(int playerturn, int gameturn, char* currentTime, int coordenadaX, int coordenadaZ) {  // função que vai guardar uma peça na lista
    part partStored;

    if (playerturn == 1) {
        partStored.type = 'x';
        strcpy(partStored.player, player1);
    }
    if (playerturn == 2) {
        partStored.type = 'o';
        strcpy(partStored.player, player2);
    }
    partStored.turn = gameturn;
    partStored.date = currentTime;
    partStored.coordX = coordenadaX;
    partStored.coordZ = coordenadaZ;

    //adicionaPosSequencia(storedParts, &partStored, tamanhoSequencia(storedParts)+1);
    storedList[numElems] = partStored;
    numElems++;
}

void removeStoredPart(int gameturn, int coordenadaX, int coordenadaZ) {
    part auxPart;
    for (int i = 0; i < numElems; i++) {
        auxPart = storedList[i];
        if (auxPart.coordX == coordenadaX && auxPart.coordZ == coordenadaZ) {
            auxPart.turnRemoved = gameturn;
            //adicionaPosSequencia(removedParts, &auxPart, tamanhoSequencia(removedParts) + 1);
            removedParts[numRemovidos] = auxPart;
            numRemovidos++;
            //removePosSequencia(storedParts, i);
            for (int j = i; j < numElems; j++)
                storedList[j] = storedList[j + 1];
            numElems--;
        }
    }
}

void printStoredParts() {
    part auxPart;
    printf("\n");
    for (int i = 0; i < numElems; i++) {
        auxPart = storedList[i];
        printf("\nTurn %d: %c | %s | x:%d,z:%d", auxPart.turn, auxPart.type, auxPart.player, auxPart.coordX, auxPart.coordZ);
        printf("\nDate and time: %s", auxPart.date);
    }
    printf("\n\n");
}

void printRemovedParts() {
    part auxPart;
    printf("\n");
    for (int i = 0; i < numElems; i++) {
        auxPart = removedParts[i];
        printf("\nRemoved in turn %d: %c | %s | x:%d,z:%d", auxPart.turnRemoved, auxPart.type, auxPart.player, auxPart.coordX, auxPart.coordZ);
    }
    printf("\n\n");
}

