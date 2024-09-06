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
void RollEvent();
void UsePotion();

void EmptyRoom();
void PotionFound();
void GameOver();

void SoundA();

int D6;
int EnemyNumber;
int EnemyAttack;
int EndBattle;

int PlayerHP = 20;
int Potions;
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
		if (PlayerHP <= 0) {return 0;}

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
					
				case 7: 
				
					return 0;
					break;
					
				case 11:
				
					UsePotion();
					break;
					
			}
			
		if (XPosition == 0) { XPosition = 1;}
		if (XPosition == 7) { XPosition = 6;}
		if (TowerLevel == 0) { TowerLevel = 1;}
		if (TowerLevel == 11) { TowerLevel = 10;}
		
		if (Coordinates != 11) {
			
			ClearScreen();
			DrawMap();
			printf("\nWalk to: %d \n\n", Coordinates);
			Sleep(1000);
			RollEvent();
		
		}
									
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
	
	printf("PlayerHP = %d | XPCounter = %d | XP = %d | D6 = %d | Xposition = %d | \n", PlayerHP, XPCounter, XP, D6, XPosition);
	printf("Tower Level: %d | Potions: %d \n", TowerLevel, Potions);
		
	printf("\n[1] Left [2] Right [3] Go Up [4] Go Down | [11] Use Potion [7] Exit \n\n");
	
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
		
	printf("\nBattle! You found an enemy!\n");
	
	
	Sleep(1000);
	
	ClearScreen();
	
	do {
		
		printf ("\n[D6] ENEMY ROLLING D6...\n");
		Sleep(1000);

		RollD6();
		PrintD6();
		
		switch (EnemyNumber) {
			
			case 1: //Orc
		
				EnemyAttack = D6;
				break;
				
			case 2: //Wolf
		
				EnemyAttack = D6 + 1;
				break;
			
			case 3: //Skeleton
		
				EnemyAttack = D6 + 2;
				break;
				
			case 4: //EvilWarrior
		
				EnemyAttack = D6 + 3;
				break;
			
			case 5: //DevilBat
		
				EnemyAttack = D6 + 4;
				break;
				
			case 6: //Cyclops
		
				EnemyAttack = D6 + 5;
				break;
				
			case 7: //Dark Elf
		
				EnemyAttack = D6 + 6;
				break;
				
			case 8: //Skeleton Lord
		
				EnemyAttack = D6 + 7;
				break;
				
			case 9: //Wizard
		
				EnemyAttack = D6 + 8;
				break;
				
			case 10: //Demon
		
				EnemyAttack = D6 + 9;
				break;
				
			case 11: //BBEG
		
				EnemyAttack = D6 + 10;
				break;
		
		}
		
		printf ("Enemy: *** [D6 +%d]\n", (EnemyNumber - 1));
		printf ("Enemy Attack Pts = %d \n\n", EnemyAttack);
		
		//scanf("Add number to continue:", &Option);
				
		printf ("[D6] PLAYER ROLLING D6...\n");
		Sleep(1000);
		
		RollD6();
		PrintD6();
						
		int PlayerAttack = D6 + XP;
		
		printf ("HP: %d \n", PlayerHP);
		printf ("Player: Player [D6 + XP]\n");
		printf ("Player Attack Pts = %d \n\n", PlayerAttack);
				
		if (PlayerAttack > EnemyAttack) {
			
			printf("YOU WIN!\n");
			printf("XP points +1!\n\n");
			
			XPCounter ++;
			if (XPCounter == 3) {XP++; XPCounter = 0;}
			EndBattle = 1;
			Sleep(1000);
				
		} else {
			
				printf("The ENEMY HITS YOU!\n"); PlayerHP --;
				if (PlayerHP <= 0) {GameOver(); return;}
		
			}
		
		//scanf("Add number 1 to continue:", &Option);
		Sleep(1000);
			
	} while (EndBattle != 1);
}

//Sounds
void SoundA(){Beep(700, 350);}

void PrintD6() {
	
	printf("\n");
	
	switch (D6) {
		
		case 1:   	
	
			printf("-----\n");
			printf("|   |\n");
			printf("| o |\n");
			printf("|   |\n");
			printf("-----\n");
			
			break;
	
		case 2:   	
	
			printf("-----\n");
			printf("| o |\n");
			printf("|   |\n");
			printf("| o |\n");
			printf("-----\n");
			
			break;
			
		case 3:
		
			printf("-----\n");
			printf("| o |\n");
			printf("| o |\n");
			printf("| o |\n");
			printf("-----\n");
			
			break;
			
		case 4:
		
			printf("-----\n");
			printf("|o o|\n");
			printf("|   |\n");
			printf("|o o|\n");
			printf("-----\n");
			
			break;
			
		case 5:
		
			printf("-----\n");
			printf("|o o|\n");
			printf("| o |\n");
			printf("|o o|\n");
			printf("-----\n");
			
			break;
			
		case 6:
		
			printf("-----\n");
			printf("|o o|\n");
			printf("|o o|\n");
			printf("|o o|\n");
			printf("-----\n");
			
			break;
			
	}
	
	printf("\n");

}


void RollEvent() {
	
	printf ("[D6] ROLLING EVENT...\n");
	Sleep(1000);
	RollD6();
	PrintD6();
	Sleep(1000);
	
	switch (D6) {
		
		case 1:
		
			if (TowerLevel == 1) {EnemyNumber = 1; Battle();}
			break;
			
		case 2:
		
			if (TowerLevel == 1) {EnemyNumber = 1; Battle();}
			break;
				
		case 3:
		
			if (TowerLevel == 1) {EnemyNumber = 1; Battle();}
			break;
		
		case 4:		
		
			if (TowerLevel == 1 || TowerLevel == 3) {PotionFound();}
			break;
		
		case 5:
		
			if (TowerLevel == 1 || TowerLevel == 2 || TowerLevel == 3 || TowerLevel == 4) {EmptyRoom(); }
			if (TowerLevel == 5  || TowerLevel == 7 || TowerLevel == 8 || TowerLevel == 10) {EmptyRoom(); }
			if (TowerLevel == 6 || TowerLevel == 9) {PotionFound();}
			break;
		
		case 6:
		
			if (TowerLevel == 1) {}
			break;
	
	}

}

void GameOver() {

		printf("\n GAME OVER \n");
	
}

void EmptyRoom() {
	
	printf ("The room is empty.\n");
	Sleep(1000);
	
}

void PotionFound() {
	
	printf("You have found a potion!\n");
	Potions++;
	Sleep(1000);
	
}

void UsePotion() {
	
	if (Potions > 0 && PlayerHP < 20) {

		Potions --;
		PlayerHP ++;
		
		printf ("One potion has been used! +1 HP restored!");
		

	} else { 
		
		if (!Potions > 0) {printf ("You don't have any potions!");}
		if (Potions > 0 && !PlayerHP <= 20) {printf ("You are at maximum HP!");}
		
	}
	
	Sleep(1000);

}
