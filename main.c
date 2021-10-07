#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
struct Cell{
	char value[4];
};
struct Cell table[9][9]={
		[0][0]={"HY1"},[0][1]={"HY2"},[0][2]={" "},[0][3]={"P"},[0][4]={"P"},[0][5]={"P"},[0][6]={" "},[0][7]={"HR1"},[0][8]={"HR2"},
		[1][0]={"HY4"},[1][1]={"HY3"},[1][2]={" "},[1][3]={"P"},[1][4]={"DR3"},[1][5]={"P"},[1][6]={" "},[1][7]={"HR4"},[1][8]={"HR3"},
		[2][0]={" "},[2][1]={" "},[2][2]={" "},[2][3]={"P"},[2][4]={"DR2"},[2][5]={"P"},[2][6]={" "},[2][7]={" "},[2][8]={" "},
		[3][0]={"P"},[3][1]={"P"},[3][2]={"P"},[3][3]={"P"},[3][4]={"DR1"},[3][5]={"P"},[3][6]={"P"},[3][7]={"P"},[3][8]={"P"},
		[4][0]={"P"},[4][1]={"DY3"},[4][2]={"DY2"},[4][3]={"DY1"},[4][4]={" "},[4][5]={"DB1"},[4][6]={"DB2"},[4][7]={"DB3"},[4][8]={"P"},
		[5][0]={"P"},[5][1]={"P"},[5][2]={"P"},[5][3]={"P"},[5][4]={"DG1"},[5][5]={"P"},[5][6]={"P"},[5][7]={"P"},[5][8]={"P"},
		[6][0]={" "},[6][1]={" "},[6][2]={" "},[6][3]={"P"},[6][4]={"DG2"},[6][5]={"P"},[6][6]={" "},[6][7]={" "},[6][8]={" "},
		[7][0]={"HG1"},[7][1]={"HG2"},[7][2]={" "},[7][3]={"P"},[7][4]={"DG3"},[7][5]={"P"},[7][6]={" "},[7][7]={"HB1"},[7][8]={"HB2"},
		[8][0]={"HG4"},[8][1]={"HG3"},[8][2]={" "},[8][3]={"P"},[8][4]={"P"},[8][5]={"P"},[8][6]={" "},[8][7]={"HR4"},[8][8]={"HB3"},
	};
int roll(){
	int dice=rand()%6;
	return dice+1;
}
void PrintBoard(struct Cell table[9][9]){
	int i,j;
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			printf("%-4s",table[i][j].value);
		}
		printf("\n");
	}
}
struct Point{
	char value[4];
	int x;
	int y;
	int finished;
	int inNest;
	int nestx;
	int nesty;
};
struct Player{
	char Color;
	struct Point pawns[4];
	struct Point tohome;
	struct Point nest;
	struct Point dest;
	struct Point moveToDest;
}yellow,blue,green,red;
struct Point LeaveCell(struct Point pawn,struct Point toHome){
	if(strcmp(table[toHome.x][toHome.y].value,"P")!=0){
		printf("Cant move pawn %s out of nest\n",pawn.value);
		return pawn;
	}
	pawn.inNest=0;
	strcpy(table[pawn.x][pawn.y].value,"-");
	strcpy(table[toHome.x][toHome.y].value,pawn.value);
	pawn.x=toHome.x;
	pawn.y=toHome.y;
	printf("Pawn %s moved out of nest\n",pawn.value);
	return pawn;
}

void UpdateCells(struct Point p){
	strcpy(table[p.x][p.y].value,p.value);
}
void UpdateTable(struct Player player){
	UpdateCells(player.pawns[0]);
	UpdateCells(player.pawns[1]);
	UpdateCells(player.pawns[2]);
	UpdateCells(player.pawns[3]);
}
void MoveToNest(char cell[4]){
	int index = cell[2]-'0';
	index--;
	char color =cell[1];
	if(color=='R'){
		red.pawns[index].x=red.pawns[index].nestx;
		red.pawns[index].y=red.pawns[index].nesty;
		red.pawns[index].inNest=1;
		UpdateTable(red);
	}
	else if(color=='G'){
		green.pawns[index].x=green.pawns[index].nestx;
		green.pawns[index].y=green.pawns[index].nesty;
		green.pawns[index].inNest=1;
		UpdateTable(green);
	}
	else if(color=='Y'){
		yellow.pawns[index].x=yellow.pawns[index].nestx;
		yellow.pawns[index].y=yellow.pawns[index].nesty;
		yellow.pawns[index].inNest=1;
		UpdateTable(yellow);
	}
	else if(color=='B'){
		blue.pawns[index].x=blue.pawns[index].nestx;
		blue.pawns[index].y=blue.pawns[index].nesty;
		blue.pawns[index].inNest=1;
		UpdateTable(blue);
	}
}
struct Point MovePawn(struct Point pawn,int count,struct Point dest,struct Point moveDest){
	int tmp = count;
	if(pawn.finished==1)return pawn;
	strcpy(table[pawn.x][pawn.y].value,"P");
	while(tmp>0){
		if((pawn.x==0&&pawn.y<5)||(pawn.x==3&&pawn.y>4&&pawn.y<8)||(pawn.x==3&&pawn.y<3)){
			if(strcmp(table[pawn.x][pawn.y+1].value,"P")==0){
				pawn.y++;
	    	}
	    	else if(table[pawn.x][pawn.y+1].value[1]!=pawn.value[1]){
	    		MoveToNest(table[pawn.x][pawn.y+1].value);
	    		pawn.y++;
			}
		}
		else if((pawn.x<3&&pawn.y==5)||(pawn.y==8&&pawn.x<5)||(pawn.y==5&&pawn.x<8)){
			if(strcmp(table[pawn.x+1][pawn.y].value,"P")==0){
				pawn.x++;
	    	}
	    	else if(table[pawn.x+1][pawn.y].value[1]!=pawn.value[1]){
	    		MoveToNest(table[pawn.x+1][pawn.y].value);
	    		pawn.x++;
			}
		}
		else if((pawn.x==5&&pawn.y>5)||(pawn.x==8&&pawn.y>3)||(pawn.x==5&&pawn.y>0)){
			if(strcmp(table[pawn.x][pawn.y-1].value,"P")==0){
				pawn.y--;
	    	}
	    	else if(table[pawn.x][pawn.y-1].value[1]!=pawn.value[1]){
	    		MoveToNest(table[pawn.x][pawn.y-1].value);
	    		pawn.y--;
			}
		}
		else if((pawn.y==3&&pawn.x>5)||(pawn.y==0&&pawn.x>3)||(pawn.y==3&&pawn.x>0)){
			if(strcmp(table[pawn.x-1][pawn.y].value,"P")==0){
				pawn.x--;
	    	}
	    	else if(table[pawn.x-1][pawn.y].value[1]!=pawn.value[1]){
	    		MoveToNest(table[pawn.x-1][pawn.y].value);
	    		pawn.x--;
			}
		}
		if(pawn.x==dest.x&&pawn.y==dest.y){
			do{
				pawn.x+=moveDest.x;
				pawn.y+=moveDest.y;
			}while((table[pawn.x+moveDest.x][pawn.y+moveDest.y].value[0]=='D'));
			pawn.finished=1;
			strcpy(table[pawn.x][pawn.y].value,pawn.value);
			return pawn;
		}
	   tmp--;
	}
	return pawn;
}
struct Player initializePlayer(char color,struct Point nest){
	struct Player player;
	player.Color=color;
	player.pawns[0].inNest=1;
	player.pawns[1].inNest=1;
	player.pawns[2].inNest=1;
	player.pawns[3].inNest=1;
	player.pawns[0].finished=0;
	player.pawns[1].finished=0;
	player.pawns[2].finished=0;
	player.pawns[3].finished=0;
	player.pawns[0].x=nest.x;
	player.pawns[0].y=nest.y;
	player.pawns[2].x=nest.x+1;
	player.pawns[2].y=nest.y;
	player.pawns[1].x=nest.x;
	player.pawns[1].y=nest.y+1;
	player.pawns[3].x=nest.x+1;
	player.pawns[3].y=nest.y+1;
	player.pawns[0].nestx=nest.x;
	player.pawns[0].nesty=nest.y;
	player.pawns[1].nestx=nest.x+1;
	player.pawns[1].nesty=nest.y;
	player.pawns[2].nestx=nest.x;
	player.pawns[2].nesty=nest.y+1;
	player.pawns[3].nestx=nest.x+1;
	player.pawns[3].nesty=nest.y+1;
	player.pawns[0].value[0]='H';
	player.pawns[0].value[1]=color;
	player.pawns[0].value[2]='1';
	player.pawns[0].value[3]=0;
	player.pawns[1].value[0]='H';
	player.pawns[1].value[1]=color;
	player.pawns[1].value[2]='2';
	player.pawns[1].value[3]=0;
	player.pawns[2].value[0]='H';
	player.pawns[2].value[1]=color;
	player.pawns[2].value[2]='3';
	player.pawns[2].value[3]=0;
	player.pawns[3].value[0]='H';
	player.pawns[3].value[1]=color;
	player.pawns[3].value[2]='4';
	player.pawns[3].value[3]=0;
	UpdateTable(player);
	return player;
}
int AllInNest(struct Player player){
	int i;
	for(i=0;i<4;i++){
		if(player.pawns[i].inNest==0)return 0;
	}
	return 1;
}
struct Player MovePawnInput(struct Player player,int dice){
	int pawnToMove;
	do{
		printf("Enter pawn no to move (1,2,3,4):");
		scanf("%d",&pawnToMove);
		pawnToMove--;
		if(player.pawns[pawnToMove].inNest==1)printf("You cant move this pawn.\n");
	}while(player.pawns[pawnToMove].inNest==1||(pawnToMove<0||pawnToMove>3));
	player.pawns[pawnToMove]=MovePawn(player.pawns[pawnToMove],dice,player.dest,player.moveToDest);
	return player;
}
int CheckVictory(struct Player player){
	int i;
	for(i=0;i<4;i++){
		if(player.pawns[i].finished==0)return 0;
	}
	return 1;
}
int WillMove(struct Player player){
	int i;
	for(i=0;i<4;i++){
		if(player.pawns[i].finished==0&&player.pawns[i].inNest==0){
			return 1;
		}
	}
	return 0;
}
int nextPawn(struct Player player){
	int i;
	for(i=0;i<4;i++){
		if(player.pawns[i].inNest==1){
			return i;
		}
	}
	return 4;
}
struct Player Play(struct Player player){
	printf("%c Plays\n",player.Color);
	printf("Rolling dice...");
	int dice = roll();
	printf("Its %d!\n",dice);
	if(dice==6&&nextPawn(player)!=4){
		printf("1-Move Pawn\n2-Move next pawn to board \n");
		int choice;
		scanf("%d",&choice);
		if(nextPawn(player)>0){
			if(choice==2){
			player.pawns[nextPawn(player)]=LeaveCell(player.pawns[nextPawn(player)],player.tohome);
			}
		else{
			player = MovePawnInput(player,dice);
			}
		}
		else{
			player.pawns[nextPawn(player)]=LeaveCell(player.pawns[nextPawn(player)],player.tohome);
		}
		
	}else{
		if(WillMove(player)==0){
			printf("You cant move until you put your next pawn in. You should roll 6!\n");
			UpdateTable(player);
			return player;
		}
		if(AllInNest(player)==1){
			printf("All of your pawns are in nest.\n");
		}
		else{
			if(nextPawn(player)>0)
			player = MovePawnInput(player,dice);
			else printf("You lose your turn.\n");
		}
	}
	UpdateTable(player);
	printf("\n");
	return player;
}
int main(int argc, char *argv[]) {
	srand(time(NULL));
	struct Point yellowNest;
	yellowNest.x=0;
	yellowNest.y=0;
	yellow=initializePlayer('Y',yellowNest);
	yellow.tohome.x=3;
	yellow.tohome.y=0;
	yellow.dest.x=4;
	yellow.dest.y=0;
	yellow.moveToDest.x=0;
	yellow.moveToDest.y=1;
	
	struct Point redNest;
	redNest.x=0;
	redNest.y=7;
	red=initializePlayer('R',redNest);
	red.tohome.x=0;
	red.tohome.y=5;
	red.dest.x=0;
	red.dest.y=4;
	red.moveToDest.x=1;
	red.moveToDest.y=0;
	
	struct Point blueNest;
	blueNest.x=7;
	blueNest.y=7;
	blue=initializePlayer('B',blueNest);
	blue.tohome.x=5;
	blue.tohome.y=8;
	blue.dest.x=4;
	blue.dest.y=8;
	blue.moveToDest.x=0;
	blue.moveToDest.y=-1;
	
	struct Point greenNest;
	greenNest.x=7;
	greenNest.y=0;
	green=initializePlayer('G',greenNest);
	green.tohome.x=8;
	green.tohome.y=3;
	green.dest.x=8;
	green.dest.y=4;
	green.moveToDest.x=-1;
	green.moveToDest.y=0;
	
	int pcount;
	printf("Enter player count 2-4: ");
	do{
		scanf("%d",&pcount);
	}while(pcount<=1||pcount>4);
	int i;
	while(1){
		for(i=1;i<=pcount;i++){
			if(i==1){
				yellow=Play(yellow);
				PrintBoard(table);
				if(CheckVictory(yellow)==1){
					printf("Player %c WON!\n",yellow.Color);
					break;
				}
			}
			if(i==2){
				red=Play(red);
				PrintBoard(table);
				if(CheckVictory(red)==1){
					printf("Player %c WON!\n",red.Color);
					break;
				}
			}
			if(i==3){
				green=Play(green);
				PrintBoard(table);
				if(CheckVictory(green)==1){
					printf("Player %c WON!\n",green.Color);
					break;
				}
			}
			if(i==4){
				blue=Play(blue);
				PrintBoard(table);
				if(CheckVictory(blue)==1){
					printf("Player %c WON!\n",blue.Color);
					break;
				}
			}
		}		
	}
	return 0;
}
