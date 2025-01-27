// SplitterConveyor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include<stdio.h>
#include<conio.h>
#include<stdio.h>

extern "C" {
// observe your project contents. We are mixing C files with cpp ones.
// Therefore, inside cpp files, we need to tell which functions are written in C.
// That is why we use extern "C" directive
#include<interface.h>
#include"SplitterConveyor.h"
}

int main()
{
	printf("Welcome to the Splitter Conveyor Application\n");
	initializeHardwarePorts();
	int t = -1;

	printf("\n\nPress: q, a, z, w, s, x or 0 ");

	while (t != '0') {
		t = _getch();
		switch (t) {
		case 'q': cylinder1_moveForward(); break;
		case 'a': cylinder1_moveBackward(); break;
		case 'z': cylinder1_stop(); break;
		case 'w': cylinder2_moveForward(); break;
		case 's': cylinder2_moveBackward(); break;
		case 'x': cylinder2_stop(); break;
		case 'e': cylinderStart_moveForward(); break;
		case 'd': cylinderStart_moveBackward(); break;
		case 'c': cylinderStart_stop(); break;
		case 'f': conveyorMove(); break;
		case 'v': conveyorStop(); break;
		}
	}

	
	writeDigitalU8(2, 0x00);
	closeChannels();
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
