#include <iostream>
#include<conio.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>
#include"my_interaction_functions.h"
#include"game.h"
#include<windows.h> // for the Sleep function
extern "C" {
#include <FreeRTOS.h>
#include <task.h>
#include <timers.h>
#include <semphr.h>
#include <interface.h>	
#include <interrupts.h>
}
#define mainREGION_1_SIZE 8201
#define mainREGION_2_SIZE 29905
#define mainREGION_3_SIZE 7607
//#define portMAX_DELAY 10000
#define MAXNAME 50
#define MAXNUM 1

xSemaphoreHandle sem_X_finished = NULL;
xSemaphoreHandle sem_Z_finished = NULL;
xSemaphoreHandle sem_main_finished = NULL;
xSemaphoreHandle sem_XZ_finished = NULL;
xSemaphoreHandle sem_postgame = NULL;

xQueueHandle mbx_X = NULL;
xQueueHandle mbx_Z = NULL;
xQueueHandle mbx_part = NULL;

typedef struct _coord {
	int x;
	int z;
}coord;

time_t rawtime;
time_t current;
struct tm* timeinfo;
char* currentTime;
// ALTERADO

static void initialiseHeap(void)
{
	static uint8_t ucHeap[configTOTAL_HEAP_SIZE];
	/* Just to prevent 'condition is always true' warnings in configASSERT(). */
	volatile uint32_t ulAdditionalOffset = 19;
	const HeapRegion_t xHeapRegions[] =
	{
		/* Start address with dummy offsetsSize */
		{ ucHeap + 1,mainREGION_1_SIZE },
		{ ucHeap + 15 + mainREGION_1_SIZE,mainREGION_2_SIZE },
		{ ucHeap + 19 + mainREGION_1_SIZE +
		mainREGION_2_SIZE,mainREGION_3_SIZE },
		{ NULL, 0 }
	};
	configASSERT((ulAdditionalOffset +
		mainREGION_1_SIZE +
		mainREGION_2_SIZE +
		mainREGION_3_SIZE) < configTOTAL_HEAP_SIZE);
	/* Prevent compiler warnings when configASSERT() is not defined. */
	(void)ulAdditionalOffset;
	vPortDefineHeapRegions(xHeapRegions);
}

void vAssertCalled(unsigned long ulLine, const char* const pcFileName)
{
	static BaseType_t xPrinted = pdFALSE;
	volatile uint32_t ulSetToNonZeroInDebuggerToContinue = 0;
	/* Called if an assertion passed to configASSERT() fails. See
	http://www.freertos.org/a00110.html#configASSERT for more information. */
	/* Parameters are not used. */
	(void)ulLine;
	(void)pcFileName;
	printf("ASSERT! Line %ld, file %s, GetLastError() %ld\r\n", ulLine, pcFileName, GetLastError());
	taskENTER_CRITICAL();
	{
		/* Cause debugger break point if being debugged. */
		__debugbreak();
		/* You can step out of this function to debug the assertion by using
		the debugger to set ulSetToNonZeroInDebuggerToContinue to a non-zero
		value. */
		while (ulSetToNonZeroInDebuggerToContinue == 0)
		{
			__asm { NOP };
			__asm { NOP };
		}
	}
	taskEXIT_CRITICAL();
}

void inicializarPortos() {
	printf("\nwaiting for hardware simulator...");
	printf("\nReminding: gotoXZ requires kit calibration first...");
	createDigitalInput(0);
	createDigitalInput(1);
	createDigitalOutput(2);
	writeDigitalU8(2, 0);
	printf("\ngot access to simulator...");


	return;
}

void NormalGameTask(void* pvParameters) {

	int x = 0, z = 0;
	char aux2[2];
	int playerturn = 1; 
	int gameturn = 1;	// número da jogada
	coord coordenadas;
	int winner;

	xSemaphoreGive(sem_XZ_finished);
	if (xQueueSemaphoreTake(sem_main_finished, portMAX_DELAY) == pdTRUE);

	do{
		printf("\n\n<*************** Turn %d ***************>\n", gameturn);

		printPlayerNames(playerturn);
		gamestructure();
		if (getGamemode() == 1 ||(getGamemode() == 2 && playerturn == 1)) {
			printf("\nInsert X and Z (x,z): \n");
			scanf_s("%d,%d", &x, &z);
		}
		else {
			printf("entrei no else");
			do {
				strcpy(aux2, getRandomCell());
				x = aux2[0];
				z = aux2[1];
			}
			while (checkCell(x, z) != 0);
		}
		if (x < 1 || x>3 || z > 3 || z < 1) {
			printf("\nThat coordinate is not valid, you just lost your turn.\n");
			if (playerturn == 1)
				playerturn = 2;
			else {
				playerturn = 1;
				gameturn++;
			}
		}
		else {
			if (checkCell(x, z) == 0) {
				coordenadas.x = x;
				coordenadas.z = z;
				atualizaMatriz(playerturn, x, z, 0);
				xQueueSend(mbx_part, &coordenadas, portMAX_DELAY);
				if (xQueueSemaphoreTake(sem_X_finished, portMAX_DELAY) == pdTRUE && xQueueSemaphoreTake(sem_Z_finished, portMAX_DELAY) == pdTRUE) {
					PutPartInCell();
					xSemaphoreGive(sem_XZ_finished);
					if (xQueueSemaphoreTake(sem_main_finished, portMAX_DELAY) == pdTRUE);
				}

				time(&rawtime);
				timeinfo = localtime(&rawtime);
				currentTime = asctime(timeinfo);
				printf("%s", currentTime);
				addPart_storedList(playerturn, gameturn, currentTime, coordenadas.x, coordenadas.z);
				// ALTERADO

				if (playerturn == 1)
					playerturn = 2;
				else {
					playerturn = 1;
					gameturn++;
				}
			}
			else {
				printf("\nCell already occupied.\n");
				if (playerturn == 1)
					playerturn = 2;
				else {
					playerturn = 1;
					gameturn++;
				}
			}
		}
	} while (checkWinner() == 0);
	printf("\n");
	gamestructure();
	winner = checkWinner();
	switch (winner) {
		case 1:
			printf("\n\n              %s WINS!!\n\n", getNamePlayer1());
			break;
		case 2:
			printf("\n\n              %s WINS!!\n\n", getNamePlayer2());
			break;
		case -1:
			printf("\n\n              Oh no... It was a tie. \n\n");
			break;
		default:
			break;
	}
	xSemaphoreGive(sem_postgame);
}

void HybridGameTask(void* pvParameters) {
	int x = 0, z = 0;
	char aux2[2];
	int playerturn = 1;
	int gameturn = 1;
	int winner;
	coord coordenadas;

	xSemaphoreGive(sem_XZ_finished);
	if (xQueueSemaphoreTake(sem_main_finished, portMAX_DELAY) == pdTRUE);

	do{
		printf("\n\n<*************** Turn %d ***************>\n", gameturn);
		printPlayerNames(playerturn);
		gamestructure();
		if (getGamemode() == 1 || (getGamemode() == 2 && playerturn == 1)) {
			printf("\nInsert X and Z (x,z) you would like to put/remove: \n");
			scanf_s("%d,%d", &x, &z);
		}
		else {
				strcpy(aux2, getRandomCell());
				x = aux2[0];
				z = aux2[1];
		}
		if (x < 1 || x>3 || z > 3 || z < 1) {
			printf("\nThat coordinate is not valid, you just lost your turn.\n");
			if (playerturn == 1)
				playerturn = 2;
			else {
				playerturn = 1;
				gameturn++;
			}
		}
		else {
			if (checkCell(x, z) == 0) {
				coordenadas.x = x;
				coordenadas.z = z;
				atualizaMatriz(playerturn, x, z, 0);
				xQueueSend(mbx_part, &coordenadas, portMAX_DELAY);
				if (xQueueSemaphoreTake(sem_X_finished, portMAX_DELAY) == pdTRUE && xQueueSemaphoreTake(sem_Z_finished, portMAX_DELAY) == pdTRUE) {
					PutPartInCell();
					xSemaphoreGive(sem_XZ_finished);
					printf("dei luz verde para ir apanhar a box\n");
					if (xQueueSemaphoreTake(sem_main_finished, portMAX_DELAY) == pdTRUE);
				}

				time(&rawtime);
				timeinfo = localtime(&rawtime);
				currentTime = asctime(timeinfo);
				addPart_storedList(playerturn, gameturn, currentTime, coordenadas.x, coordenadas.z);
				// ALTERADO

				if (playerturn == 1)
					playerturn = 2;
				else {
					playerturn = 1;
					gameturn++;
				}
			}
			else {
				if (checkCell(x, z) != playerturn) {
					coordenadas.x = x;
					coordenadas.z = z;
					atualizaMatriz(playerturn, x, z, 1);
					xQueueSend(mbx_part, &coordenadas, portMAX_DELAY);
					if (xQueueSemaphoreTake(sem_X_finished, portMAX_DELAY) == pdTRUE && xQueueSemaphoreTake(sem_Z_finished, portMAX_DELAY) == pdTRUE) {
						TakePartFromCell();
						xSemaphoreGive(sem_XZ_finished);
						if (xQueueSemaphoreTake(sem_main_finished, portMAX_DELAY) == pdTRUE);
					}
					removeStoredPart(gameturn, coordenadas.x, coordenadas.z);
					// ALTERADO
				}
				else
					printf("\nYou can't remove your own piece.\n");
				if (playerturn == 1)
					playerturn = 2;
				else {
					playerturn = 1;
					gameturn++;
				}
			}
		}
	}while (checkWinner() == 0);

	printf("\n");
	gamestructure();
	winner = checkWinner();
	switch (winner) {
		case 1:
			printf("\n\n           %s WINS!!\n\n", getNamePlayer1());
			break;
		case 2:
			printf("\n\n           %s WINS!!\n\n", getNamePlayer2());
			break;
		case -1:
			printf("\n\n           Oh no... It was a tie. \n\n");
			break;
		default:
			break;
	}
	xSemaphoreGive(sem_postgame);
}

void RandomGameTask(void* pvParameters) {
	int x = 0, z = 0;
	char aux2[2];
	int playerturn = 1;
	int gameturn = 1;
	int winner;
	coord coordenadas;

	xSemaphoreGive(sem_XZ_finished);
	if (xQueueSemaphoreTake(sem_main_finished, portMAX_DELAY) == pdTRUE);

	do{
		printf("\n\n<*************** Turn %d ***************>\n", gameturn);
		printPlayerNames(playerturn);
		gamestructure();

		if (getGamemode() == 1 || (getGamemode() == 2 && playerturn == 1)) {
			printf("\nInsert X and Z (x,z): \n");
			scanf_s("%d,%d", &x, &z);
		}
		else {
			printf("entrei no else");
			do {
				strcpy(aux2, getRandomCell());
				x = aux2[0];
				z = aux2[1];
			} while (checkCell(x, z));
		}

		if(x<1 || x>3 || z >3 || z<1){
			printf("\nThat coordinate is not valid, you just lost your turn.\n");
			if (playerturn == 1)
				playerturn = 2;
			else {
				playerturn = 1;
				gameturn++;
			}
		}
		else {
			switch (getRandomType()) {
			case 1:
				if (checkCell(x, z) == 0) {
					coordenadas.x = x;
					coordenadas.z = z;
					atualizaMatriz(playerturn, x, z, 0);
					xQueueSend(mbx_part, &coordenadas, portMAX_DELAY);
					if (xQueueSemaphoreTake(sem_X_finished, portMAX_DELAY) == pdTRUE && xQueueSemaphoreTake(sem_Z_finished, portMAX_DELAY) == pdTRUE) {
						PutPartInCell();
						xSemaphoreGive(sem_XZ_finished);
						if (xQueueSemaphoreTake(sem_main_finished, portMAX_DELAY) == pdTRUE);
					}

					time(&rawtime);
					timeinfo = localtime(&rawtime);
					currentTime = asctime(timeinfo);
					addPart_storedList(playerturn, gameturn, currentTime, coordenadas.x, coordenadas.z);
					// ALTERADO

					if (playerturn == 1)
						playerturn = 2;
					else {
						playerturn = 1;
						gameturn++;
					}
				}
				else {
					printf("\nCell already occupied.\n");
					if (playerturn == 1)
						playerturn = 2;
					else {
						playerturn = 1;
						gameturn++;
					}
				}
				break;
			case 2:
				if (checkCell(x, z) == 0) {
					printf("\nEmpty cell.\n");
					if (playerturn == 1)
						playerturn = 2;
					else {
						playerturn = 1;
						gameturn++;
					}
				}
				else if (checkCell(x, z) != playerturn) {
					coordenadas.x = x;
					coordenadas.z = z;
					atualizaMatriz(playerturn, x, z, 1);
					xQueueSend(mbx_part, &coordenadas, portMAX_DELAY);
					if (xQueueSemaphoreTake(sem_X_finished, portMAX_DELAY) == pdTRUE && xQueueSemaphoreTake(sem_Z_finished, portMAX_DELAY) == pdTRUE) {
						TakePartFromCell();
						xSemaphoreGive(sem_XZ_finished);
						if (xQueueSemaphoreTake(sem_main_finished, portMAX_DELAY) == pdTRUE);
						removeStoredPart(gameturn, coordenadas.x, coordenadas.z);	
						// ALTERADO
					}
					if (playerturn == 1)
						playerturn = 2;
					else {
						playerturn = 1;
						gameturn++;
					}
				}
				else{
					printf("\nYou can't remove your own piece.\n");
					if (playerturn == 1)
						playerturn = 2;
					else {
						playerturn = 1;
						gameturn++;
					}
				}
				break;
			}
		}
	}while (checkWinner() == 0);

	printf("\n");
	gamestructure();
	winner = checkWinner();
	switch (winner) {
	case 1:
		printf("\n\n           %s WINS!!\n\n", getNamePlayer1());
		break;
	case 2:
		printf("\n\n           %s WINS!!\n\n", getNamePlayer2());
		break;
	case -1:
		printf("\n\n           Oh no... It was a tie. \n\n");
		break;
	default:
		break;
	}
	xSemaphoreGive(sem_postgame);
}

void postGameTask(void* pvParameters) {
	int option;
	int control = 0;

	xQueueSemaphoreTake(sem_postgame, portMAX_DELAY);
	printf("%d", uxSemaphoreGetCount(sem_postgame));

	do{
		printf("You finished your game, what would you like to see?\n");
		printf("-> Stored Parts Data (1)\n-> X's Player game(2)\n-> O's Player game(3)\n-> History of removed parts(4)\n-> Exit(5)\n");
		scanf(" %d", &option);

		switch (option) {
		case  1:
			printStoredParts();	// ALTERADO
			break;
		case 2:
			printPlayer1Game();
			break;
		case 3:
			printPlayer2Game();
			break;
		case 4:
			printRemovedParts();	// ALTERADO
			break;
		case 5:
			control = 1;
			break;
		default:
			printf("That option is not valid.\n");
			break;
		}
	} while (control == 0);
	vTaskSuspendAll();
}

void gotoX_task(void* pvParameters)
{
	int x;
	while (TRUE) {
		if (xQueueReceive(mbx_X, &x, portMAX_DELAY) == pdTRUE) {
			gotoX(x);
			xSemaphoreGive(sem_X_finished);
		}
	}
}

void gotoZ_task(void* pvParameters)
{
	int z;
	while (TRUE) {

		if (xQueueReceive(mbx_Z, &z, portMAX_DELAY) == pdTRUE) {
			gotoZ(z);
			xSemaphoreGive(sem_Z_finished);
		}
	}
}

void goto_XZ_task(void* pvParameters) {
	int x = 0;
	int z = 0;
	coord coordenadas;

	while (TRUE) {
		xQueueReceive(mbx_part, &coordenadas, portMAX_DELAY);
		x = coordenadas.x;
		z = coordenadas.z;
		xQueueSend(mbx_X, &x, portMAX_DELAY);
		xQueueSend(mbx_Z, &z, portMAX_DELAY);
	}
}

void goGetBox(void* pvParameters) {
	int x = 1, z = 1;
	while (TRUE) {
		if (xQueueSemaphoreTake(sem_XZ_finished, portMAX_DELAY) == pdTRUE) {
			xQueueSend(mbx_X, &x, portMAX_DELAY);
			xQueueSend(mbx_Z, &z, portMAX_DELAY);
			if (xQueueSemaphoreTake(sem_X_finished, portMAX_DELAY) == pdTRUE && xQueueSemaphoreTake(sem_Z_finished, portMAX_DELAY) == pdTRUE) {
				gotoY(1);
				gotoY(2);
				printf("dei luz verde \n");
				xSemaphoreGive(sem_main_finished);
			}
		}
	}
}

void menu() {
	int gamemode = 0;
	int gametype = 0;
	int difficulty = 0;
	int aux = 0;
	char player1[MAXNAME];
	char player2[MAXNAME];
	printf("\n\n--------------Welcome to the game of the cock!--------------\n\n");
	printf("Choose The Game Mode\n");
	do {
		printf("-> Human vs. Human (1)\n-> Human vs. PC (2)\n-> PC vs. PC (3)\n");
		scanf_s(" %d", &gamemode);
	} while (gamemode < 1 || gamemode > 3);

	switch (gamemode) {
		case 1:
			printf("\nInsert the name of the first player: ");
			scanf(" %s", player1);
			printf("\nInsert the name of the second player: ");
			scanf(" %s", player2);
			break;
		case 2:
			printf("\nInsert the name of the player: ");
			scanf(" %s", player1);
			break;
		case 3:
			break;
		default:
			break;
	}
	do {
		printf("\n\nChoose the type game you would like to play:\n-> Normal(1)\n-> Hybrid(2)\n-> Random(3)\n");
		scanf_s(" %d", &gametype);
	} while (gametype < 1 || gametype > 3);

	do {
		printf("\n\nChoose your difficulty(Easy '1' ; Hard '2'):");
		scanf_s(" %d", &difficulty);
	} while (difficulty < 1 || difficulty > 2);

	savegamedata(gamemode, difficulty, gametype, player1, player2);
}

void myDaemonTaskStartupHook(void) {

	sem_X_finished = xSemaphoreCreateCounting(10, 0);
	sem_Z_finished = xSemaphoreCreateCounting(10, 0);
	sem_main_finished = xSemaphoreCreateCounting(10, 0);
	sem_XZ_finished = xSemaphoreCreateCounting(10, 0);
	sem_postgame = xSemaphoreCreateCounting(10, 0);
	mbx_X = xQueueCreate(10, sizeof(int));
	mbx_Z = xQueueCreate(10, sizeof(int));
	mbx_part = xQueueCreate(10, sizeof(coord));
	switch (getGametype()) {
	case 1:
		xTaskCreate(NormalGameTask, "NormalGameTask", 100, NULL, 0, NULL);
		break;
	case 2:
		xTaskCreate(HybridGameTask, "HybridGameTask", 100, NULL, 0, NULL);
		break;
	case 3: 
		xTaskCreate(RandomGameTask, "RandomGameTask", 100, NULL, 0, NULL);
		break;
	default:
		break;
	}
	xTaskCreate(goto_XZ_task, "goto_XZ_task", 100, NULL, 0, NULL);
	xTaskCreate(gotoZ_task, "gotoZ_task", 100, NULL, 0, NULL);
	xTaskCreate(gotoX_task, "gotoX_task", 100, NULL, 0, NULL);
	xTaskCreate(goGetBox, "goGetBox", 100, NULL, 0, NULL);
	xTaskCreate(postGameTask, "postGameTask", 100, NULL, 0, NULL);
}

void calibragem() {
	printf("\ncallibrate kit manually and press enter...");
	int tecla = 0;
	while (tecla != 13) {
		tecla = _getch();
		switch (tecla)
		{
		case 'd':
			if (getXPos() != 3) {
				moveXRight();
				Sleep(150);
				while (getXPos() == -1)
				{

				}
				stopX();
			}
			break;
		case 'a':
			if (getXPos() != 1) {
				moveXLeft();
				Sleep(150);
				while (getXPos() == -1)
				{

				}
				stopX();
			}
			break;
		case 'w':
			if (getZPos() != 3) {
				moveZUp();
				Sleep(150);
				while (getZPos() == -1)
				{

				}
				stopZ();
			}
			break;
		case 's':
			if (getZPos() != 1) {
				moveZDown();
				Sleep(150);
				while (getZPos() == -1)
				{

				}
				stopZ();
			}
			break;
		case 'i':
			if (getYPos() != 3) {
				moveYInside();
				Sleep(150);
				while (getYPos() == -1)
				{

				}
				stopY();
			}
			break;
		case 'o':
			if (getYPos() != 1) {
				moveYOutside();
				Sleep(150);
				while (getYPos() == -1)
				{

				}
				stopY();
			}
			break;
		default:
			break;
		}
	}
}

int main(int argc, char** argv) {
	inicializarPortos();
	initialiseHeap();
	inicializamatriz();
	calibragem();
	menu();
	vApplicationDaemonTaskStartupHook = &myDaemonTaskStartupHook;
	vTaskStartScheduler();
	closeChannels();
}