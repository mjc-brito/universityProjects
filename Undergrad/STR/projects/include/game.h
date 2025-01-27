#pragma once
#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

typedef struct _game* game;
//typedef struct _coord* coord;
void savegamedata(int gamemode, int difficulty, int gametype,char* player1, char* player2);
void gamestructure();
void inicializamatriz();
void printPlayer1Game();
void printPlayer2Game();
void printPlayerNames(int playerturn);
void atualizaMatriz(int playerturn, int x, int z, int type);
int checkCell(int x, int z);
int getGamemode();
int getGametype();
char* getNamePlayer1();
char* getNamePlayer2();
char* getRandomCell();
int getRandomType();
int  checkWinner();

void addPart_storedList(int playerturn, int gameturn, char* currentTime, int coordenadaX, int coordenadaZ); 
void removeStoredPart(int gameturn, int coordenadaX, int coordenadaZ);
void printStoredParts();
void printRemovedParts();

#endif
