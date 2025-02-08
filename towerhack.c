#include <stdio.h> // Standard library for C
#include <stdlib.h> // Contains the rand() function.
#include <time.h> // Time and random functions.
#include <string.h> // library for strings

#ifdef _WIN32

	#include <windows.h>    // Required for CustomSleep() on Windows, for BEEPS, 
						   //sleep, and windows functionalities.
#else	
	
	#include <unistd.h> //Required for LINUX commands and unix-like systems
					    
#endif

void ClearScreen();
void Generate();
void RollD6();
void DrawMap();
void Battle();
void PrintD6();
void RollEvent();
void UsePotion();
void CustomSleep();

void EmptyRoom();
void PotionFound();
void GetXP();
void GameOver();

void SoundA();

char EnemyName[15];
int EnemyID;

int D6;
int EnemyNumber;
int EnemyHITPoints;
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

//Switchs

int SkipEvent = 0;

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
				
					if (XPosition == Stairs[TowerLevel- 1]) {
						
						TowerLevel ++;
						SoundA();
					
					} else {
						
						SkipEvent = 1;
						break;
												
					}
					
				case 4:
					
					if (XPosition == Stairs[TowerLevel - 2]) {
						
						TowerLevel --;
						SoundA(); 
						break;
					
					} else {
						
						SkipEvent = 1;
						break;
												
					}
			
				case 7: 
				
					return 0;
					break;
					
				case 11:
				
					UsePotion();
					break;
					
			}
			
		if (XPosition == 0) { 
			
			SkipEvent = 1;
			XPosition = 1;
			
		}
					
		if (XPosition == 7) { 
			
			SkipEvent = 1;
			XPosition = 6;
			
		}
		
		if (TowerLevel == 0) { TowerLevel = 1;}
		if (TowerLevel == 11) { TowerLevel = 10;}
		
		if (Coordinates != 11) {
			
			ClearScreen();
			DrawMap();
			printf("\nWalk to: %d \n", Coordinates);
			
			switch(Coordinates) {
				
				case 1:
					
					if (XPosition == 1 & SkipEvent == 1) { //ARREGLAR BUG
						
						printf("It's not possible to go left! There's the wall!!");						
						break;
						
					} else {
						
						printf("Going west...");
												
						}
						
					break;
				
				case 2:
				
					if (XPosition == 6 & SkipEvent == 1) { //ARREGLAR BUG
						
						printf("It's not possible to go right! There's the wall!!");						
						break;
						
					} else {
						
						printf("Going east...");
						break;
												
					}
				
				case 3:
					
					if (XPosition == Stairs[TowerLevel - 1] & SkipEvent == 0) { // RESOLVER ESTO

						printf("Going upstairs...");
						break;
					
					} else {

						printf("Imposible to go up without a stair!");
						break;					

					}
					
				case 4:

					if (XPosition == Stairs[TowerLevel - 2]) { //RESOLVER ESTO
						
						printf("Going downstairs...");
						break;
					
					} else {
						
						printf("Imposible to go down without a stair!");
						break;
					
					}
					
			}
			
			printf("\n\n");
			CustomSleep();
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
		
	CustomSleep();
	
	ClearScreen();
	
	switch (EnemyNumber) {
			
		
		// 1 Orc | 2 Wolf | 3 Skeleton | 4 Evil Warrior | 5 Devil Bat
		// 6 Cyclops | 7 Dark Elf | 8 Skeleton Lord | 9 Wizard | 10 Demon
		
		case 1: //Orc
				
			strcpy(EnemyName, "Orc");
			EnemyHITPoints = 0;
			break;
				
		case 2: //Wolf
			
			strcpy(EnemyName, "Wolf");
			EnemyHITPoints = 1;
			break;
			
		case 3: //Skeleton
		
			strcpy(EnemyName, "Skeleton");
			EnemyHITPoints = 2;
			break;
				
		case 4: //EvilWarrior
				
			strcpy(EnemyName, "Evil Warrior");
			EnemyHITPoints = 3;
			break;
			
		case 5: //DevilBat
		
			strcpy(EnemyName, "Devil Bat");
			EnemyHITPoints = 4;
			break;
				
		case 6: //Cyclops
				
			strcpy(EnemyName, "Cyclops");
			EnemyHITPoints = 5;
			break;
				
		case 7: //Dark Elf
				
			strcpy(EnemyName, "Dark Elf");
			EnemyHITPoints = 6;
			break;
				
		case 8: //Skeleton Lord
		
			strcpy(EnemyName, "Skeleton Lord");
			EnemyHITPoints = 7;
			break;
				
		case 9: //Wizard
		
			strcpy(EnemyName, "Wizard");
			EnemyHITPoints = 8;
			break;
				
		case 10: //Demon
				
			strcpy(EnemyName, "Demon");
			EnemyHITPoints = 9;
			break;
				
		case 11: //BBEG
		
			strcpy(EnemyName, "BBEG");
			EnemyHITPoints = 10;
			break;
		
	}
	
	do {
		
		printf ("\n[D6] ENEMY ROLLING D6...\n");
		CustomSleep();

		RollD6();
		PrintD6();
				
		EnemyAttack = D6 + EnemyHITPoints;
		
		printf ("Enemy: %s [D6 +%d]\n", EnemyName, (EnemyNumber - 1));
		printf ("Enemy Attack Pts = %d \n\n", EnemyAttack);
		
		//scanf("Add number to continue:", &Option);
				
		printf ("[D6] PLAYER ROLLING D6...\n");
		CustomSleep();
		
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
			CustomSleep();
				
		} else {
			
				printf("The ENEMY HITS YOU!\n"); PlayerHP --;
				if (PlayerHP <= 0) {GameOver();}
		
			}
		
		//scanf("Add number 1 to continue:", &Option);
		
		CustomSleep();
			
	} while (EndBattle != 1);
}

//Sounds
void SoundA(){
	
	#ifdef _WIN32
    	
		Beep(700, 350);
		
	#endif
	
}

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
	
	if (SkipEvent == 1) {
		
		D6 = 7;
		
	} else {
		
		printf ("[D6] ROLLING EVENT...\n");
		CustomSleep();
		RollD6();
		PrintD6();
		CustomSleep(); 
		
		}
		
	switch (D6) {
		
		// 1 Orc | 2 Wolf | 3 Skeleton | 4 Evil Warrior | 5 Devil Bat
		// 6 Cyclops | 7 Dark Elf | 8 Skeleton Lord | 9 Wizard | 10 Demon
		
		case 1:
		
			if (TowerLevel == 1) {EnemyNumber = 1; Battle();}
			if (TowerLevel == 2) {EnemyNumber = 1; Battle();}
			if (TowerLevel == 3) {EnemyNumber = 1; Battle();}
			if (TowerLevel == 4) {EnemyNumber = 1; Battle();}
			if (TowerLevel == 5) {EnemyNumber = 2; Battle();}
			if (TowerLevel == 6) {EnemyNumber = 3; Battle();}
			if (TowerLevel == 7) {EnemyNumber = 4; Battle();}
			if (TowerLevel == 8) {EnemyNumber = 5; Battle();}
			if (TowerLevel == 9) {EnemyNumber = 6; Battle();}
			if (TowerLevel == 10) {EnemyNumber = 7; Battle();}
			
			break;
			
		case 2:
		
			if (TowerLevel == 1) {EnemyNumber = 1; Battle();}
			if (TowerLevel == 2) {EnemyNumber = 1; Battle();}
			if (TowerLevel == 3) {EnemyNumber = 2; Battle();}
			if (TowerLevel == 4) {EnemyNumber = 2; Battle();}
			if (TowerLevel == 5) {EnemyNumber = 3; Battle();}
			if (TowerLevel == 6) {EnemyNumber = 4; Battle();}
			if (TowerLevel == 7) {EnemyNumber = 5; Battle();}
			if (TowerLevel == 8) {EnemyNumber = 6; Battle();}
			if (TowerLevel == 9) {EnemyNumber = 7; Battle();}
			if (TowerLevel == 10) {EnemyNumber = 8; Battle();}

			break;
				
		case 3:
		
			if (TowerLevel == 1) {EnemyNumber = 1; Battle();}
			if (TowerLevel == 2) {EnemyNumber = 1; Battle();}
			if (TowerLevel == 3) {EnemyNumber = 3; Battle();}
			if (TowerLevel == 4) {EnemyNumber = 3; Battle();}
			if (TowerLevel == 5) {EnemyNumber = 4; Battle();}
			if (TowerLevel == 6) {EnemyNumber = 5; Battle();}
			if (TowerLevel == 7) {EnemyNumber = 6; Battle();}
			if (TowerLevel == 8) {EnemyNumber = 7; Battle();}
			if (TowerLevel == 9) {EnemyNumber = 8; Battle();}
			if (TowerLevel == 10) {EnemyNumber = 9; Battle();}
						
			break;
		
		// 1 Orc | 2 Wolf | 3 Skeleton | 4 Evil Warrior | 5 Devil Bat
		// 6 Cyclops | 7 Dark Elf | 8 Skeleton Lord | 9 Wizard | 10 Demon
		
		case 4:		
			
			if (TowerLevel == 1) {PotionFound();}
			if (TowerLevel == 2) {EnemyNumber = 2; Battle();}
			if (TowerLevel == 3) {PotionFound();}
			if (TowerLevel == 4) {EnemyNumber = 4; Battle();}
			if (TowerLevel == 5) {EnemyNumber = 5; Battle();}
			if (TowerLevel == 6) {EnemyNumber = 6; Battle();}
			if (TowerLevel == 7) {EnemyNumber = 7; Battle();}
			if (TowerLevel == 8) {EnemyNumber = 8; Battle();}
			if (TowerLevel == 9) {EnemyNumber = 9; Battle();}
			if (TowerLevel == 10) {EnemyNumber = 10; Battle();}
			
			break;
		
		case 5:
		
			if (TowerLevel == 1 || TowerLevel == 2 || TowerLevel == 3 || TowerLevel == 4) {EmptyRoom(); }
			if (TowerLevel == 5  || TowerLevel == 7 || TowerLevel == 8 || TowerLevel == 10) {EmptyRoom(); }
			if (TowerLevel == 6 || TowerLevel == 9) {PotionFound();}
			
			break;
		
		case 6:
		
			GetXP();
			break;
			
		case 7: 
			
			SkipEvent = 0;
			break;
	
	}

}

void GameOver() {

		printf ("You've been killed by a %s.\n", EnemyName);
		printf ("You got up to floor %d.\n", TowerLevel); 
		
		printf("\n GAME OVER \n");
		
		CustomSleep();
		
		return;
	
}

void EmptyRoom() {
	
	printf ("The room is empty.\n");
	CustomSleep();
	
}

void PotionFound() {
	
	printf("You have found a potion!\n");
	Potions++;
	CustomSleep();
	
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
	
	CustomSleep();

}

void GetXP() {
	
	if (XP <= 10) {
	
		XPCounter ++;
		printf("You feel much stronger! You get +1 XP counter!");
		
		if (XPCounter == 3) {XP++; XPCounter = 0;}
		if (XP > 10) {XP = 10;} 
	
	} else { 
		
		printf("You are at maximum XP! You've reached the limit!\n"); 
		printf("You can't get anymore stronger!");
		
		}
			
	CustomSleep();
				
}

void CustomSleep() {
	
	#ifdef _WIN32 //For Windows
    
		Sleep(1000);
	
	#else //For Linux
    
		sleep(1);
				
	#endif
	
}


//======================================================================

//NOTES:

// Things to do:
// ====== == ==

// - Not to be able to move up if there isn’t a ladder.
// - Make a GAME OVER message when your character dies!
// - Add a second ladder in each of the stories.

// DONE
// ====

// - If you are next to the wall and want to go right “YOU CANNOT GO THAT 
//   WAY!”, the same happens when you want to move to the left and there’s a wall.


