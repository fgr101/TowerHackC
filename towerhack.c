#include <stdio.h> // Standard library for C
#include <stdlib.h> // Contains the rand() function.
#include <time.h> // Time and random functions.
#include <string.h> // library for strings

#ifdef _WIN32
#include <windows.h> // Required for Sleep() on Windows 
#endif

void ClearScreen();
void Generate();
void RollD6();

int D6;

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
	
	
	do {
			ClearScreen();
				
			printf("D6 = %d \n", D6);
			printf("Xposition = %d \n", XPosition);
			printf("Tower Level: %d \n", TowerLevel);
			
			printf("\n[1] Left [2] Right [3] Go Up [4] Go Down | [7] Exit \n\n");
			
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
					
					}
					
					break;
				
				case 4:
									
					if (XPosition == Stairs[TowerLevel - 1]) {
						
						TowerLevel --; 
					
					}
				
					break;
					
			}
			
		if (XPosition == 0) { XPosition = 1;}
		if (XPosition == 7) { XPosition = 6;}
		if (TowerLevel == 0) { TowerLevel = 1;}
		if (TowerLevel == 6) { TowerLevel = 5;}
					
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

