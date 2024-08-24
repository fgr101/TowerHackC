#include <stdio.h> // Standard library for C
#include <stdlib.h> // Contains the rand() function.
#include <time.h> // Time and random functions.
#include <string.h> // library for strings
#include <windows.h> // for BEEPS, sleep, and windows functionalities.

#ifdef _WIN32
#include <windows.h> // Required for Sleep() on Windows 
#endif

void ClearScreen();
void Generate();
void RollD6();
void DrawMap();
void Battle();
void PrintD6();

void SoundA();

int D6;
int EndBattle;

int XPCounter;
int XP;

int TowerLevel = 1;
int Coordinates = 0;
int YPosition = 1;
int XPosition = 1;

int f;
int i;


int Stairs[10];

char a1 = 'X';
char a2 = ' ';
char a3 = ' ';
char a4 = ' ';
char a5 = ' ';
char a6 = ' ';

int main () {
	
	srand(time(NULL));
	Generate();
	
	// Function that beeps a sound of frequency 750 for 1.0 sec. The
	// smallest value for the sound duration is 800, 900 or 1000.
	
	// So, the valid range for the `Beep()` function is:

	// - Minimum frequency: 37 Hz
	// - Maximum frequency: 32767 Hz

	//Beep(500, 970);
	
	do {
			
		ClearScreen();
		Battle();
		
		printf("XPCounter = %d \n", XPCounter);
		printf("XP = %d \n", XP);			
		printf("D6 = %d \n", D6);
		printf("Xposition = %d \n", XPosition);
		printf("Tower Level: %d \n", TowerLevel);
			
		printf("\n[1] Left [2] Right [3] Go Up [4] Go Down | [7] Exit \n\n");
						
		DrawMap();
			
		printf("\nWalk to: ");
		scanf("%d", &Coordinates);
		
			switch (Coordinates) {
				
				case 1:
					
					XPosition = XPosition - 1;
					break;
					
				case 2:
				
					XPosition = XPosition + 1;
					break;
					
				case 3:
				
					
					if (XPosition == Stairs[TowerLevel]) {
						
						TowerLevel ++;
						SoundA();
					
					}
					
					break;
				
				case 4:
									
					if (XPosition == Stairs[TowerLevel - 1]) {
						
						TowerLevel --;
						SoundA(); 
					
					}
				
					break;
					
			}
			
		if (XPosition == 0) { XPosition = 1;}
		if (XPosition == 7) { XPosition = 6;}
		if (TowerLevel == 0) { TowerLevel = 1;}
		if (TowerLevel == 11) { TowerLevel = 10;}
					
	} while (Coordinates != 7);
	
	return 0;
			
}

//CLS Function
void ClearScreen() {

	#ifdef _WIN32
		
		// Windows
		system("cls");

	#else
		
		// Unix-like systems
		system("clear");

	#endif

}

//Roll D6
void RollD6() {
	
	D6 = (rand() % 6) + 1;
			
}

void Generate() {
	
	//Generating RANDOM stairs.
	
	i = 1;
							
	do {	
				
		RollD6(); // Drawing STAIRS.
		Stairs[i] = D6;
			
		i++;
				
	} while (i < 10);
	
}

// Drawing the Tower	
void DrawMap() {
	
	if (TowerLevel <= 5) {
			
		f = 5;
				
		do {
				
			i = 1;		
					
			do {
									
				if (i == Stairs[f]) { a1 = '#';} //if (i == Stairs[i] && TowerLevel < f) { a1 = '#';} 
				else { a1 = '-';}
									
				printf (".--%c--.", a1);
				i++;
					
			} while (i < 7);

			printf ("\n||   ||||   ||||   ||||   ||||   ||||   ||\n");
					
			i = 1;		
					
			do {
									
				if (i == XPosition && TowerLevel == f) { a1 = 'X';} 
				else { a1 = ' ';}
									
				printf ("|| %c ||", a1);
				i++;
					
			} while (i < 7);
					
			printf ("\n||   ||||   ||||   ||||   ||||   ||||   ||\n");
			printf (".-----..-----..-----..-----..-----..-----.\n");
					
			f--;
					
		} while (f > 0);
			
	}
			
	if (TowerLevel >= 6 && TowerLevel <= 10 ) {
			
		f = 10;
				
		do {
				
			i = 1;		
					
			do {
									
				if (i == Stairs[f]) { a1 = '#';} //if (i == Stairs[i] && TowerLevel < f) { a1 = '#';} 
				else { a1 = '-';}
									
				printf (".--%c--.", a1);
				i++;
					
			} while (i < 7);

			printf ("\n||   ||||   ||||   ||||   ||||   ||||   ||\n");
					
			i = 1;		
					
			do {
									
				if (i == XPosition && TowerLevel == f) { a1 = 'X';} 
				else { a1 = ' ';}
									
				printf ("|| %c ||", a1);
				i++;
					
			} while (i < 7);
					
			printf ("\n||   ||||   ||||   ||||   ||||   ||||   ||\n");
			printf (".-----..-----..-----..-----..-----..-----.\n");
					
			f--;
					
		} while (f > 5);
			
	}	
	
}

void Battle(){
	
	EndBattle = 0;
	
	printf("\n\nBATTLE! YOU FOUND AN ENEMY!\n");
	printf ("===========================\n");
		
	do {
		
		printf ("\nENEMY ROLLING D6...\n");
		Sleep(1000);

		RollD6();
		PrintD6();
		
		int EnemyAttack = D6 + 1;
		
		printf ("Enemy: Orc [D6 +1]\n");
		printf ("Enemy Attack Pts = %d \n\n", EnemyAttack);
		
		//scanf("Add number to continue:", &Option);

				
		printf ("PLAYER ROLLING D6...\n");
		Sleep(1000);
		
		RollD6();
		PrintD6();
						
		int PlayerAttack = D6 + XP;
		
		printf ("Player: Player [D6 + XP]\n");
		printf ("Player Attack Pts = %d \n\n", PlayerAttack);
				
		if (PlayerAttack > EnemyAttack) {
			
			printf("YOU WIN!\n");
			printf("XP points +1!\n\n");
			
			XPCounter ++;
			if (XPCounter == 3) {XP++; XPCounter = 0;}
			EndBattle = 1;
			Sleep(1000);
				
		} else { printf("The ENEMY HITS YOU!\n");}
		
		//scanf("Add number 1 to continue:", &Option);
		Sleep(1000);
			
	} while (EndBattle != 1);
}

//Sounds
void SoundA(){Beep(700, 350);}

void PrintD6() {

	switch (D6) {
		
		case 1:   	
	
			printf("\n-----\n");
			printf("|   |\n");
			printf("| o |\n");
			printf("|   |\n");
			printf("-----\n");
			
			break;
	
		case 2:   	
	
			printf("\n-----\n");
			printf("| o |\n");
			printf("|   |\n");
			printf("| o |\n");
			printf("-----\n");
			
			break;
			
		case 3:
		
			printf("\n-----\n");
			printf("| o |\n");
			printf("| o |\n");
			printf("| o |\n");
			printf("-----\n");
			
			break;
			
		case 4:
		
			printf("\n-----\n");
			printf("|o o|\n");
			printf("|   |\n");
			printf("|o o|\n");
			printf("-----\n");
			
			break;
			
		case 5:
		
			printf("\n-----\n");
			printf("|o o|\n");
			printf("| o |\n");
			printf("|o o|\n");
			printf("-----\n");
			
			break;
			
		case 6:
		
			printf("\n-----\n");
			printf("|o o|\n");
			printf("|o o|\n");
			printf("|o o|\n");
			printf("-----\n");
			
			break;
			
	}
	
	printf("\n");

}
