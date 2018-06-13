#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <ctype.h>
#define clear ' '
#define hit 'H'
#define miss 'X'

/* Author:JUDITH ANTONIO
Creation Date: 11/24/2015
BATTLESHIP GAME	
*/

typedef struct ship {

	char shiptype[200];
	int shipsize;
	int *X_Location;
	int *Y_Location;
	int *X_Hit;
	int *Y_Hit;
	int hits;
	struct ship *pt;

} ship;
typedef struct list {

	ship *head;
	char name[100];
	int num_hit;
	int num_miss;
	int num_sunk;
	int ships;

}list;

int User_Sonar = 0, PC_Sonar = 0,play_CRTL=0, play_CRT = 0;
ship *first = NULL;
ship *next = NULL;
int N = 0;

void iniciar(list *X, list *Y) {//iniciate the players information

	 int i = 0,j=0;
	
	
	for (i = 0; i < 3; i++) {
		printf("\n\n\n\n\n\n\n");
		printf("\t\t\tXXXXX   XXXX  XXXXXX XXXXXX XX     XXXXXX  XXXXX XX  XX XX XXXX\n");
		Sleep(1000);
		printf("\t\t\tXX  XX XX  XX   XX     XX   XX     XX     XX     XX  XX XX XX  XX\n");
		Sleep(1000);
		printf("\t\t\tXXXXX  XX  XX   XX     XX   XX     XXXX    XXXX  XXXXXX XX XXXX\n");
		Sleep(1000);
		printf("\t\t\tXX  XX XXXXXX   XX     XX   XX     XX         XX XX  XX XX XX\n");
		Sleep(1000);
		printf("\t\t\tXXXXX  XX  XX   XX     XX   XXXXXX XXXXXX XXXXX  XX  XX XX XX\n");
		Sleep(1000);
		//printf("\n\n");
		
		system("cls");
	}

	system("cls");
	

	printf("\n\n\n\n\n\n\n\t\t\t\t\tWHAT IS YOU NAME: ");
	
	scanf("%s", X->name);//get the user name
	strcpy(Y->name, "Computer");
//------------------- set all counters to zero----------------------//
	X->num_hit = 0;
	X->num_miss = 0;
	X->num_sunk = 0;
	X->ships = 0;
	Y->num_hit = 0;
	Y->num_miss = 0;
	Y->num_sunk = 0;
	Y->ships = 0;
//------------------------------------------------------//

}

void Print_Score(list *X, list *Y) {//print the players information in the screen

	printf("%s\t\t\t%s\n", X->name, Y->name);
	printf("Hit:  %d\t\t\tHit:  %d\n", X->num_hit, Y->num_hit);
	printf("Miss: %d\t\t\tMiss: %d\n", X->num_miss, Y->num_miss);
	printf("Sunk: %d\t\t\tSunk: %d\n", X->num_sunk, Y->num_sunk);


}

void Abandon_Ship(list *H,int grid[][10]) {//ADD the new ships

	int R, C,i;
	ship *Shp=NULL, *Shp1 = NULL;
	ship *last =  H->head;
	int crt = 0;

	for (i = 0; i < 2; i++) {
		
		R = rand() % 10;//chose the row position
		C = rand() % 10;//choose the col

		last = H->head;//last get the head para percorrer a list
		
		if (grid[R][C] == clear) {//if the choosen position is free
			crt++;
			Shp = (ship*)malloc(sizeof(ship));//allocate mamory for the new ship
			Shp->pt = NULL;

			if (H->head != NULL) {//if the list is not empty
				while (last->pt != NULL) {//look for the last element
					last = last->pt;
				}			
				last->pt = Shp;//last element pints to the new one
			}
			else
			H->head= Shp;//if the list was empty head points to the new element
			
			//add the info of the neew ship
			Shp->hits = 0;
			Shp->shipsize = 1;
			strcpy(Shp->shiptype, "Kayak");
			Shp->X_Location = (int*)calloc(sizeof(int), Shp->shipsize);
			Shp->Y_Location = (int*)calloc(sizeof(int), Shp->shipsize);
			Shp->X_Hit = (int*)calloc(sizeof(int), Shp->shipsize);
			Shp->Y_Hit = (int*)calloc(sizeof(int), Shp->shipsize);

			grid[R][C] = Shp->shiptype[0];
			Shp->X_Location[0] = R + 1;
			Shp->Y_Location[0] = C + 1;
			

			/*else {

				Shp1 = (ship*)malloc(sizeof(ship));
				Shp1->pt = NULL;
				last->pt = Shp1;
				Shp1->hits = 0;
				Shp1->shipsize = 1;
				strcpy(Shp1->shiptype, "Kayak");
				Shp1->X_Location = (int*)calloc(sizeof(int), Shp1->shipsize);
				Shp1->Y_Location = (int*)calloc(sizeof(int), Shp1->shipsize);
				Shp1->X_Hit = (int*)calloc(sizeof(int), Shp1->shipsize);
				Shp1->Y_Hit = (int*)calloc(sizeof(int), Shp1->shipsize);

				grid[R][C] = Shp1->shiptype[0];
				Shp1->X_Location[0] = R + 1;
				Shp1->Y_Location[0] = C + 1;
				last = Shp1;
			}*/

		}
		}
	
	}
//-------------------------Function that place the ship na grid e update the ship info na list
void Up_Ver(int V[][10], int size, int X, int Y, char c,ship* S) {//insert vertical up
	
	int i = X, j = 0;
	while (j<size) {	////verificar Vertical up	

		V[i][Y] = c;//fill the vector
		S->X_Location[j] = i + 1;//fill the array position
		S->Y_Location[j] = Y+1;
		i--;
		j++;
	}
}

void Dn_Ver(int V[][10], int size, int X, int Y, char c,ship* S) {//insert vertical down

	int i = X, j = 0;
	while (j<size) {	////verificar Vertical down	

		V[i][Y] = c;
		S->X_Location[j] = i + 1;//fill the array position
		S->Y_Location[j] = Y+1;
		i++;

		j++;
	}
}

void Rg_Hor(int V[][10], int size, int X, int Y, char c,ship* S) {//insert Hor rigth

	int	i = Y, j = 0;

	while (j<size) {	////verificar horizontal rigth	

		V[X][i] = c;

		S->X_Location[j] = X+1;//fill the array position
		S->Y_Location[j] = i+1;

		i++;
		j++;
	}
}

void Lf_Hor(int V[][10], int size, int X, int Y, char c,ship* S) {//insert HOR left


	int	i = Y;
	int j = 0;
	while (j<size) {

		V[X][i] = c;
		S->X_Location[j] = X+1;//fill the array position
		S->Y_Location[j] = i + 1;
		i--;
		j++;
	}
}

void UpDiag_Lf(int V[][10], int size, int X, int Y, char c,ship* S) {//insert diagon up left

	int i = X;
	int	j = 0;
	int	k = Y;
	while (j<size) {	////verificar Diagonal left up

		V[i][k] = c;
		S->X_Location[j] = i+1;//fill the array position
		S->Y_Location[j] = k + 1;
		i--;
		k--;
		j++;
	}
}

void UpDiag_Rgt(int V[][10], int size, int X, int Y, char c,ship* S) {//insert Diagonal rigth up

	int i = X, j = 0, k = Y;

	while (j<size) {	////verificar Diagonal rigth up

		V[i][k] = c;
		S->X_Location[j] = i + 1;//fill the array position
		S->Y_Location[j] = k + 1;
		i--;
		k++;
		j++;
	}
}

void DnDiag_Rgt(int V[][10], int size, int X, int Y, char c,ship* S) {//insert Diagonal rigth down

	int i = X, j = 0, k = Y;

	while (j<size) {	////verificar Diagonal rigth down

		V[i][k] = c;
		S->X_Location[j] = i + 1;//fill the array position
		S->Y_Location[j] = k + 1;
		i++;
		k++;
		j++;
	}
}

void DnDiag_Lf(int V[][10], int size, int X, int Y, char c,ship* S) {////insert Diagonal left down

	int	i = X, j = 0, k = Y;
	while (j<size) {	////verificar Diagonal left down

		V[i][k] = c;
		S->X_Location[j] = i + 1;//fill the array position
		S->Y_Location[j] = k + 1;
		i++;
		k--;
		j++;
	}
}
//----------------------------&&----------------------------------------------
int Checksonar(int Shp[][10],int *R, int *C) {

	//check if there is a submarine in game return 0 for no and 1 for yes
	//and pass back the one position of the sub

	int i, j, crt = 0;
	//look for sub
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			if (Shp[i][j] == 'S') {//if found
				*R = i;//pass the i location
				*C = j;//passs the j location
				crt++;
				break;
			}
		}
		if (crt != 0)
			break;
	}

	return crt;

}

void Main_menu(ship *Shp) {//present the main menu of the ships type and size---allow the user choose

	char Shp_typ[][50] = { "Aircraft Carrier","Battleship      ","Cruiser         ","Submarine       ","Patrol Boat     ","Kayak           ","Row boat        " };
	int Shp_siz[7] = { 5,4,3,3,2,1,1 }, i, opt, crt = 0;



	printf(" ____________________ ____________________ __________________ ________________ \n");
	printf("*     Num Option     |      Ship Type     |   Board Symbol   |   Ship Size    *\n");
	printf("*____________________*____________________*__________________*________________*\n");

	for (i = 0; i < 7; i++)

		printf("*          %d         |   %s |       %c          |       %d        *\n", i + 1, Shp_typ[i], Shp_typ[i][0], Shp_siz[i]);

	printf("*____________________*____________________*__________________*________________*\n\n");

	printf("Choose the number correspondet to the option: ");
	scanf("%d", &opt);
	if (opt < 1 || opt>7) {//verify if the choosen option is valid

		while (opt < 1 || opt>7) {// if not ask again
			printf("Choose any number from 1 to 7:  ");
			scanf("%d", &opt);
		}

	}
	strcpy(Shp->shiptype, Shp_typ[opt - 1]);//update the shiptype with the information of the menu
	Shp->shipsize = Shp_siz[opt - 1];//update the shipsize with the information of the menu
	
	//system("cls");
}

void print_User(int PC_ship[][10]){//print the user grid
int i, j;
printf("\n     A    B    C    D    E    F    G    H    I    J\n   ___________________________________________________\n");
for (i = 0; i<10; i++) {
	printf("\n   |    |    |    |    |    |    |    |    |    |    |\n");
	if(i!=9)
	printf("%d  ",i+1);
	
	else
		printf("%d ", i + 1);
		for (j = 0; j<10; j++) {
		
				printf("| %c  ", PC_ship[i][j]);
		if (j==9)
		printf("|    ");		
				}

		printf("\n   |____|____|____|____|____|____|____|____|____|____|\n");
		
}
	 	
}

void print_PC(int User_ship[][10]){//print the user grid
int i, j;
	
printf("\n   A    B    C    D    E    F    G    H    I    J\n  __________________________________________________\n\n1");
	for (i = 0; i<10; i++) {
		for (j = 0; j<10; j++){
		
				printf("| %c  ", User_ship[i][j]);
		if (j==9)
		printf("|    ");		
		
		}

		printf("\n  ___________________________________________________\n\n");
		if(i<=7)
			printf("%d", i + 2);
		else if(i==8)
		printf("%d",i+2);
}	
}

void create_ship(ship *P) {//create the list

	P->pt = NULL;//cada novo node aponta pra null

	if (first == NULL) {//se a lista esta vazia
		first = P;//first recebe o P e o next tbm
		next = P;
	}
	else {//para os outros elements
		next->pt = P;//o next aponta para o new
		next = P;//update o next
	}
}

void insert_ship(ship *User, int i) {//allocat memory for the strct elements and initialize them
 
	printf("\nFOR SHIP %d:\n", i);
	Main_menu(User);//call main Menu to get the type and ssize of the user ship
	User->hits = 0;
	//allocate memory para os elementos da struct
	User->X_Location = (int*)calloc(sizeof(int), User->shipsize);
	User->Y_Location = (int*)calloc(sizeof(int), User->shipsize);
	User->X_Hit = (int*)calloc(sizeof(int), User->shipsize);
	User->Y_Hit = (int*)calloc(sizeof(int), User->shipsize);
}

void PCinsert_ship(ship *User, ship *PC) {


	strcpy(PC->shiptype, User->shiptype);//copy the information of the usership to the pcship
	PC->shipsize = User->shipsize;
	PC->hits = 0;
	//allocate memory para os elementos da struct
	PC->X_Location = (int*)calloc(sizeof(int), PC->shipsize);
	PC->Y_Location = (int*)calloc(sizeof(int), PC->shipsize);
	PC->X_Hit = (int*)calloc(sizeof(int), PC->shipsize);
	PC->Y_Hit = (int*)calloc(sizeof(int), PC->shipsize);
	
}

void check_UserPos(int *X,int *Y) {//check if the given bow position are valid

	if (*X > 10 || *X <= 0) {//if not ask fornew X

		do {
			printf("Enter a number between 1 and 10 for X: ");
			scanf("%d", X);

		} while (*X >10 || *X <= 0);
	}

	if (*Y > 10 || *Y <= 0) {//and new Y

		do {
			printf("Enter a number between 1 and 10 for Y: ");
			scanf("%d", Y);

		} while (*Y >10 || *Y <= 0);
	}


}

int check_positions(int V[][10], ship *U, int check[8],int pos[8]) {//verify space to place the ship

	int size = U->shipsize, X = U->X_Location[0] - 1, Y = U->Y_Location[0] - 1;
	int j = 0, k = 0,i = 0;

	int ctr = 0;
	//using the ship size
	//count how many clear pos exist startin at the given pos
	//stop counting if the placement goes out of the grid
	if (V[X][Y] == clear) {// if the position is clear

		i = Y;

		while (j<size) {	////verificar horizontal rigth	
			
			if (V[X][i] == clear)
				pos[0]++;
			i++;
			if (i == 10)
				break;
			j++;
		}


		i = Y;
		j = 0;
		while (j<size) {	////verificar horizontal left

			if (V[X][i] == clear)
				pos[1]++;
			i--;
			if (i<0)
				break;
			j++;
		}


		i = X;
		j = 0;
		while (j<size) {	////verificar Vertical up	

			if (V[i][Y] == clear)
				pos[2]++;
			i--;
			if (i<0)
				break;
			j++;
		}

		i = X;
		j = 0;
		while (j<size) {	////verificar Vertical down

			if (V[i][Y] == clear)
				pos[3]++;
			i++;
			if (i == 10)
				break;
			j++;
		}


		i = X;
		j = 0;
		k = Y;
		while (j<size) {	////verificar Diagonal rigth up

			if (V[i][k] == clear)
				pos[4]++;
			i--;
			k++;
			if (i<0 || k == 10)
				break;
			j++;
		}


		i = X;
		j = 0;
		k = Y;
		while (j<size) {	////verificar Diagonal left up

			if (V[i][k] == clear)
				pos[5]++;
			i--;
			k--;
			if (i<0 || k<0)
				break;
			j++;
		}

		i = X;
		j = 0;
		k = Y;
		while (j<size) {	////verificar Diagonal rigth down

			if (V[i][k] == clear)
				pos[6]++;
			i++;
			k++;
			if (i == 10 || k == 10)
				break;
			j++;
		}


		i = X;
		j = 0;
		k = Y;
		while (j<size) {	////verificar Diagonal left down

			if (V[i][k] == clear)
				pos[7]++;
			i++;
			k--;
			if (i == 0 || k<0)
				break;
			j++;
		}


	}
	j = 0;

	//verify the aval posit in the array pos
	for (i = 0; i<8; i++) {

		if (pos[i] == size) {//if each pos match the size of the ship

			check[j] = i + 1;//check gets its index+1 to present it to the user
			ctr++;//count the number of aval options
			j++;
		}

	}

	return ctr;//return the num of aval optiion
}

void Fill_positions(int V[][10], int size, int X, int Y, char c, ship* U,int num) {
	//call the function to place the ship na grid and updated the info na list
	//num is the option chosen by the user

	switch (num) {// use it to place the ship in the corresponding location

	case 1: Rg_Hor(V, size, X, Y, c, U);
		break;

	case 2: Lf_Hor(V, size, X, Y, c, U);
		break;

	case 3:Up_Ver(V, size, X, Y, c, U);
		break;

	case 4:Dn_Ver(V, size, X, Y, c, U);
		break;

	case 5: UpDiag_Rgt(V, size, X, Y, c, U);
		break;

	case 6: UpDiag_Lf(V, size, X, Y, c, U);
		break;

	case 7: DnDiag_Rgt(V, size, X, Y, c, U);
		break;

	case 8: DnDiag_Lf(V, size, X, Y, c, U);
		break;

	default:
		break;

	}



}

void User_menu(int V[][10], ship *U,int check[],int pos[],int ctr) {

	//present the menu of the placemeent position to the user and get its option

	int size = U->shipsize, X = U->X_Location[0]-1, Y = U->Y_Location[0]-1;
	int j = 0, num, i = 0, val_pos = 0;
	char posi[][50] = { "Ho rigth","H left","V up","V down","D up_rigth", "D up_left","D down_rigth","D down_left" };
	char c = U->shiptype[0];
	Sleep(1000);
	system("cls");

	printf("@------------------>You have the following options<----------------------@\n");
	for (i = 0; i<8; i++) {

		if (pos[i] == size) {
			printf("@                        %d- %s                                   @\n", i + 1, posi[i]);
			j++;
		}
	}
	printf("@-------------------------------------------------------------------------@\n\n");
	do {
		printf("Enter the number correspend to the position:\n");
		scanf("%d", &num);

		for (i = 0; i<ctr; i++) {//presentt all valid option

			if (check[i] == num) {//verify if the user option is part of the valid option
				val_pos++;
				break;
			}
		}
		//if not keep asking
	} while (val_pos != 1);
	

	if (val_pos == 1) {//if the option is valid
		Fill_positions(V, size, X, Y, c, U, num);//call the function that fill the board and upd the list

	}
}

void PCFill_grid(ship* PC, int pc[][10]) {

	int ctr, i, j, k = 0, check[8] = { 0,0,0,0,0,0,0,0 }, pos[8] = { 0,0,0,0,0,0,0,0 };
	int num,R=0,X,Y,Chk,L=0;

	do {
	
		PC->X_Location[0]= (rand() % 10)+1;//get the x position form 1 to 10
		PC->Y_Location[0]= (rand() % 10)+1;//get the y position form 1 to 10
		
		ctr = check_positions(pc, PC, check, pos);//verify if there is space available for this ship

		if (ctr != 0) {//if there is
								//update the x and y with the value to mang the array
			X = PC->X_Location[0]-1;
			Y = PC->Y_Location[0]-1;

			if (PC->shipsize == 1) {//if it is a kayak don't need to present the menu
				pc[X][Y] = PC->shiptype[0];

			}

			else {//if not

				R = rand() % ctr;//choose a num between zero and the num of aval option
				Fill_positions(pc, PC->shipsize, X, Y, PC->shiptype[0], PC, check[R]);
				//call the fill post to update the pc info na grid e na list
			}
		}

		} while (ctr == 0);//loop until the pc choose an empty position

}

void UFill_grid(ship* U, int u[][10]){

	int ctr, i, j,k=0,check[8] = { 0,0,0,0,0,0,0,0 },pos[8] = { 0,0,0,0,0,0,0,0 };
	 	
	do{

			printf("ENTER THE  X and Y POSITION FOR THE BOW :");
			scanf("%d%d", &U->X_Location[0], &U->Y_Location[0]);//get the osition from the user


			check_UserPos(&U->X_Location[0], &U->Y_Location[0]);//check boundaries
			ctr = check_positions(u, U, check, pos);//get the number of avail option

			if (ctr != 0){//if there is aval pos
				if (U->shipsize == 1) {// if it is a kayak
					u[U->X_Location[0] - 1][U->Y_Location[0] - 1] = U->shiptype[0];

				}
				else
					User_menu(u, U, check,pos,ctr);//if not get the menu with all the option avail
			}
			else {//if the chosen pos is not free
				
				printf("CHOOSE ANOTHER POSITION\n");//get a new one
								
			}

	} while (ctr == 0);
		system("cls");
}

ship *Next_shp(ship *shp) {//return the adress of the next ship

	return shp->pt;
}

ship *Previuos_shp(list *H, ship *shp) {//return the adress of the previous ship

	ship *node = NULL;//aux var

	if (H->head != shp) {//if the ship is not the head

		node = H->head;//node recebe a head para percorrer a list

		while (Next_shp(node) != NULL) {//while is not o fim da list

			if (Next_shp(node) == shp)//se o proximo e o given ship
				break; //end the search
			node = Next_shp(node);//go to the next node
		}

	}

	return node;
}

void Remove_shp(list *H, ship *shp) {

	ship *prevs = NULL;


	if (H->head == shp) { //se o node a ser removido e a cabeca
		H->head = shp->pt;//cabeca aponta para o proximo node do node aser removido
	}

	else {//se nao

		prevs = Previuos_shp(H, shp);// acha o anterior do node a ser removido
		if (prevs != NULL)
			prevs->pt = shp->pt;//e faz com q ele aponte para o proximo do node a ser removido
		else
			H->head = shp->pt;
	}
	//libera a memoria
	free(shp->X_Hit);
	free(shp->Y_Hit);
	free(shp->X_Location);
	free(shp->Y_Location);
	free(shp);
}

void Shots(int *R,int *C,int player) {

	char colm[] = { 'a','b','c','d','e','f','g','h','i','j' },col;
	int row,i,j,crt=0;

	if(player==0){//User shots
	printf("Enter in the location of your shot...\nRow number: ");
	scanf("%d", &row);

	while (row >10 || row <= 0){
	
			printf("\nYOU CAN ENTER ANY NUMBER FROM 1 to 10: ");
			scanf("%d", &row);		
	} 
	*R = row - 1;

	printf("Column letter: ");
	/*fflush(stdin);
	scanf(" %c", &col);
	fflush(stdin);*/
	col = getche();
	col = tolower(col);

	while (crt == 0) {

	for (i = 0; i < 10; i++) {

		if (colm[i] == col) {
			*C = i;
			crt++;
			break;
		}
	}
	if(crt==0){
		printf("\nYOU CAN ENTER ANY LETTER FROM A to J: ");
		col = getche();
		col = tolower(col);
	}
	} 

	}

	else {//PC shots

		*R = (rand() % 10);
		*C = rand() % 10;
	}
}

 ship* search_Shp( list *H_shp,int R, int C) {//search for the hit ship

	ship *scr = H_shp->head,*tmp = NULL; //get the haed of the list to the search
	int i,ctr=0;

	while (scr != NULL) {//while it doesn't reach the end of the list

			//In each node--->Look for the ship that was the hit position

		for (i = 0; i < scr->shipsize; i++) {
			if (scr->X_Location[i] == R && scr->Y_Location[i] == C) {//if the ship is found
				//Update the X-Y hits
				scr->X_Hit[i] = R;
				scr->Y_Hit[i] = C;
				ctr++;
				scr->hits++;//update the num of hit posi
				tmp = scr;//get the adress of the found ship
				break;
			}

		}

		if (ctr != 0)
			break;
		scr = scr->pt;//got to the next node
	}
	return tmp;
}

/* int Check_removal(ship *Shp) {

	 int flag = 0;
	  
			 if (Shp->hits== Shp->shipsize) //verifica if the ship is fully hit													  
				 flag++;
		
	 return flag;
 }
 */

 void PCHits(int Shp_user[][10], int Shp_pc[][10],ship *User, list *pc,list *user_h) {

	int R, C, aban=0,i,j,sonar=0;
	char ans = ' ';
	ship *hit_shp = NULL, *ABN = pc->head;

	if (play_CRT == 0) {//play_CRT is a global val that is updat only once

		while (ABN != NULL) {//percore a list

			if (ABN->shipsize >= 3 && ABN->hits == (ABN->shipsize - 1)) {//check if o ship e d size >=3 e esta quase a afundar
				for (i = 0; i < ABN->shipsize; i++)//limpa as pos no array
					Shp_pc[ABN->X_Location[i] - 1][ABN->Y_Location[i] - 1] = clear;
	
				Remove_shp(pc, ABN);//remove it
				Abandon_Ship(pc, Shp_pc);//and call the abn function
				play_CRT++;// update this crtvar
				aban++;//update this one so the pc won't shot
				printf("\n%s USED IS TURN TO ABANON A SHIP\n", pc->name);
				break;

			}
			if (play_CRT != 0)
				break;
			ABN = ABN->pt;//got to the next node
		}

	}
	
if(aban==0 && sonar==0){//if the the aban function was not used

	Shots(&R, &C, 1);//chama o shots

	if (User_Sonar != 0 && PC_Sonar == 0) {//if the user choose to ping
		for (i = 0; i < 10; i++) {//look for a pos with S in the user grid
			for (j = 0; j < 10; j++) {
				if (Shp_user[i][j] == 'S') {//if found
				R = i;//update the shot pos
				C = j;
				PC_Sonar++;//updat the crtsvar
				sonar++;
				break;
				}
			}
			if (sonar == 1)
				break;
		}
		}
	
					 //verifica if the chosen position has a ship
	if (Shp_user[R][C] != clear && Shp_user[R][C] != miss && Shp_user[R][C] != hit) {
		
		Shp_user[R][C] = hit;//if so...hit it
		pc->num_hit++;//update the pc num of hits	
		hit_shp = search_Shp(user_h, R + 1, C + 1);//chama o procura lista e actualiza os X-Yhits
		
		//sunk = Check_removal(hit_shp);//chama o checkRemov para verificar s tem node a ser removido

		if (hit_shp->hits == hit_shp->shipsize) {//if the hit ship is full 
			Remove_shp(user_h, hit_shp);//Remove it
			pc->num_sunk++;//updated the pc ship sunks
			user_h->ships++;
		}
	}

	else if (Shp_user[R][C] == clear) {//verifica is the chosen position is empty

		Shp_user[R][C] = miss;//if so mark it as missed
		pc->num_miss++;//update the pc num of miss
	}

	else if (Shp_user[R][C] == miss || Shp_user[R][C] == hit)//verifica se ja foi usada
		printf("\nPC LOST ITS TURN FOR SHOTING INA USED POSITION\n");

	//Sleep(1000);
	//system("cls");
	
}
aban = 0; sonar = 0;//set them to zero in case abn was used
}

void UserHits(int Shp_PC[][10], int Shp_user[][10], int shadow[][10] ,ship *PC, list *user, list *pc_h) {

	int R, C,sonar=0, aban=0,p=0;
	char ans=' ';
	int i,j;
	ship *hit_shp = NULL,*ABN= user->head;
	
	if(play_CRTL==0){//gobal update only once
		
		while (ABN != NULL) {
			
			if(ABN->shipsize >= 3 && ABN->hits == (ABN->shipsize - 1)){
				
					printf("\nONE OF YOUR SHIP IS ABOUT TO BE SUNK\nWANNA ABANDON:  (y/n)");
					ans = getche();		
					p++;
					
		
			if (ans == 'y'|| ans == 'Y') {//if chose to abn

				for (i = 0; i < ABN->shipsize; i++)//clear the ship info na grid 
					Shp_user[ABN->X_Location[i] - 1][ABN->Y_Location[i] - 1] = clear;

				Remove_shp(user, ABN);//remove it
				Abandon_Ship(user, Shp_user);// add the new ships if aval space
				play_CRTL++;//upd crt
				aban++;
				printf("\n%s USED IS TURN TO ABANON A SHIP\n", user->name);
			}
			}
			if (p != 0)
				break;
		ABN = ABN->pt; 
	}
		
	}
	
	if (User_Sonar == 0 &&  Checksonar(Shp_PC, &R, &C) == 1) {//if there is a sonar in game
		//printf("%d%d", R, C);
		printf("There is a Submarine in Game...Wanna ping(y/n)? ");
		ans = getche();//get the user answer
		printf("\n");

		if (ans == 'y' || ans == 'Y') {
			
			User_Sonar++;//update crtvar
			shadow[R][C] = 'O';	//place the ping 
			sonar++;	
		}
	}
	if(aban ==0 && sonar==0) {//if did choose to ping or aban
	Shots(&R, &C, 0);

	if (Shp_PC[R][C] != clear && Shp_PC[R][C] != miss && Shp_PC[R][C] != hit) {

		Shp_PC[R][C] = hit;
		shadow[R][C]= hit;
		user->num_hit++;//updated the user hits
		
		hit_shp = search_Shp(pc_h, R + 1, C + 1);//chama o procura lista e actualiza os X-Yhits

	 
		if (hit_shp->hits == hit_shp->shipsize) {//if the hit ship is full 
			Remove_shp(pc_h, hit_shp);//Remove it
			user->num_sunk++;//updated the user ship sunks
			pc_h->ships++; //and count the num of ships removed it not necessary with the abn and sonar in place
		}
	}

	else if (Shp_PC[R][C] == clear) {// if the user miss a ship

		Shp_PC[R][C] = miss;//update the pc grid
		shadow[R][C] = miss;//and the shadow
		user->num_miss++;//and the miss num
	}

	else if (Shp_PC[R][C] == miss || Shp_PC[R][C] == hit)
			printf("\n You lost your turn because you already shot this position");

	//take of the O after the round with the sonar
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			if (shadow[i][j] == 'O')
				shadow[i][j] = clear;
		}
	}
	}
	aban = 0; sonar = 0;
}

void GAME_TIme(ship *User,ship *PC, list *Head_PC, list *Head_user, int user_grid[10][10], int PC_grid[10][10], int shadow[10][10]) {

	//for the first interaction show
	Print_Score(Head_user, Head_PC);// the initial scores
	print_User(user_grid);//user grid
	//print_PC(shadow);//and the pc empty grid
	print_PC(PC_grid);
	printf("LOADING");
	Sleep(10000);//wait 10sec
	system("cls");//clear the scre

	while (Head_user->head != NULL && Head_PC->head != NULL) {//while both list have elements

		printf("Your Turn\n");//user turn
		UserHits(PC_grid, user_grid, shadow, PC, Head_user, Head_PC);//user shot
		print_PC(PC_grid);
		//print_PC(shadow);//show is shot in the pc grid
		Print_Score(Head_user, Head_PC);//show current scores

		if (Head_user->head == NULL || Head_PC->head == NULL) {//if one list is empty break the loop
			break;//end execution
		}
		printf("WAIT FOR THE PC'S TURN...");
		Sleep(10000);//wait 10 sec
		system("cls");//clear scr

		printf("Computer's Turn\n");//pc turn
		PCHits(user_grid, PC_grid, User, Head_PC, Head_user);//pc shot
		Sleep(3000);//wait 3sec
		print_User(user_grid);//show its show in the pc grid
		Print_Score(Head_user, Head_PC);//show current score
		printf("WAIT FOR YOUR TURN...");
		Sleep(7000);//wait 7sec
		system("cls");

	}
	//ate the end of the game//show both grids
	system("cls");
	print_PC(PC_grid);//reveal pc ship pos
	print_User(user_grid);

	printf("Game Over\n");
	Print_Score(Head_user, Head_PC);//show final score and the winner
	if (Head_user->num_sunk > Head_PC->num_sunk)
		printf("%s is the winner\n", Head_user->name);
	else
		printf("%s is the winner\n", Head_PC->name);

}

int main() {

	srand((int)time(NULL));

	ship *User = NULL, *PC = NULL, *user_tmp = NULL;
	list *Head_PC = NULL, *Head_user = NULL;
	int num_ship,i,j, user_grid[10][10], PC_grid[10][10], shadow[10][10],cnt=0;

	for (i = 0; i < 10; i++) {//clear both grids
		for (j = 0; j < 10; j++) {
			user_grid[i][j] = clear;
			PC_grid[i][j] = clear;
			shadow[i][j]=clear;
		}
	}

	Head_PC = (list*)malloc(sizeof(list));//allocate PC_head list
	Head_user = (list*)malloc(sizeof(list));//allocate User_head list


	iniciar(Head_user, Head_PC);//call the iniciar
	printf("\t\t\t\t\tHOW MANY SHIPS TO PLAY  WITH: ");
	scanf("%d", &num_ship);//get the number of ships to use
	//Sleep(1000);
	system("cls");
	
	for (i = 0; i < num_ship; i++) {//creat the user list

		User = (ship*)malloc(sizeof(ship));//allocate the memory
		create_ship(User);//call add it in the list

		if (cnt == 0) {//initialize the head of the list with the first element	
			Head_user->head = User;
			cnt++;
		}

		insert_ship(User, i + 1);// allocate the lements from the stct
		UFill_grid(User, user_grid);//fill the pos
	}
	User = Head_user->head;//user gat the haed

	//******************************create PC Ships************************//
	cnt = 0;
	next = NULL;
	first = NULL;
	for (i = 0; i < num_ship; i++) {
		PC = (ship*)malloc(sizeof(ship));
		create_ship(PC);

		if (cnt == 0) {//initialize the head of the list with the first element
			Head_PC->head = PC;//initialize the head of the list with the first element
			cnt++;
		}
		PCinsert_ship(User, PC);//allocate the elm da strc
		PCFill_grid(PC, PC_grid);//add the pos
		User = User->pt;//get to the next node of the user to take the info need
	}  

	/*user_tmp = Head_PC->head;

	while (user_tmp != NULL){
		for (i = 0; i < user_tmp->shipsize;i++)
			printf("%d %d\n", user_tmp->X_Location[i], user_tmp->Y_Location[i]);
		user_tmp = user_tmp->pt;
		
	}*/
	
	GAME_TIme(User, PC, Head_PC, Head_user, user_grid, PC_grid, shadow);//game time

	free(Head_PC);//free the heads ate the end of the prog
	free(Head_user);

	return 0;
}