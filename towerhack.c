#include <stdio.h> // standard library for C
#include <string.h> // library for strings

int TowerLevel = 0;
int Coordinates = 0;
int XPosition = 1;

char a1 = 'X';
char a2 = ' ';
char a3 = ' ';
char a4 = ' ';
char a5 = ' ';
char a6 = ' ';

int main () {
	
	do {
				
		printf("Xposition = %d \n\n", XPosition);
					
		printf("Tower Level: %d \n", TowerLevel);
		printf("[1] Left [2] Right | [7] Exit \n\n");
						
		printf (".-----..-----..-----..-----..-----..-----.\n");
		printf ("||   ||||   ||||   ||||   ||||   ||||   ||\n");
		printf ("||   ||||   ||||   ||||   ||||   ||||   ||\n");
		printf ("||   ||||   ||||   ||||   ||||   ||||   ||\n");
		printf (".-----..-----..-----..-----..-----..-----.\n");
		printf (".-----..-----..-----..-----..-----..-----.\n");
		printf ("||   ||||   ||||   ||||   ||||   ||||   ||\n");
		
		int i = 1;		
		
		do {
						
			if (i == XPosition) { a1 = 'X';} 
			else { a1 = ' ';}
						
			printf ("|| %c ||", a1);
			i++;
		
		} while (i < 7);
		
		printf ("||   ||||   ||||   ||||   ||||   ||||   ||\n");
		printf (".-----..-----..-----..-----..-----..-----.\n\n");
		
		printf("Walk to: ");
		scanf("%d", &Coordinates);
		
			switch (Coordinates) {
				
				case 1:
					
					XPosition = XPosition - 1;
					break;
					
				case 2:
				
					XPosition = XPosition + 1;
					break;
					
				}
			
		if (XPosition == 0) { XPosition = 1;}
		if (XPosition == 7) { XPosition = 6;}
				
	} while (Coordinates != 7);
	
	return 0;
			
}
