#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h> 

struct level{
    char show[25];
};

struct player{
    char name[20+1];
    int position[2];
    int current_level;
    int max_level;
};


void menu(char *c);
void terrain(char *l);
void move(char *d, struct player *p,struct level lvl);
void showPlayer(char *plr, struct player p);
void resetPos(struct player *p);
void minplame();
struct level * generateLevels();
int choice();
char get_index(int x, int y, struct level lvl);

main(){
    struct level *game;
    struct player pl = {"zero", {2,0},0,1};
    bool status=true;
    char option[20+1];
    int i;

    game = generateLevels();


    printf("\tWelcome to the console game\n\n");
    printf("Start \nHelp \nExit \n");

    menu(option);
    showPlayer(game[pl.current_level].show,pl);
    while(status){

        printf("\n");
        printf("\n");
        printf("\nWhere would you like to move? (north, south, west, east)\n");
        fflush(stdin);
        gets(option);
        move(option, &pl, game[pl.current_level]);
        showPlayer(game[pl.current_level].show,pl);
        if(get_index(pl.position[1],pl.position[0],game[pl.current_level])=='a'){
            minplame();
            resetPos(&pl);
            pl.current_level++;
        }
        if(pl.current_level==3){
            status=false;
        }

    }
    
    printf("\nYou have finished your adventure through the world of code!\n");

}


void menu(char *c){ // main menu
        int pomoc=0;
        bool flag=true;
        while(flag){
            fflush(stdin);
            gets(c);
            printf("\n");

            if(strcmp(c,"Start")==0 || strcmp(c,"start")==0){
                if(pomoc==0){
                    printf("\nIt seems you have not read the tutorial, would you like to do it now? (yes/no)\n");
                    fflush(stdin);
                    gets(c);
                    printf("\n");
                    if(strcmp(c,"yes")==0){
                        printf("\nTo move around the map, follow the commands (north,south,east,west).\n");
                        printf("\nTiles marked as 'y' are unpassable, you may not move through them. Player is marked as 'o'.\n");
                        printf("\nWhen you get to the tile marked 'a' you will enter a battle with a random monster. That's when the game of RPS initiates.\n\n");
                        flag=false;
                    }
                    if(strcmp(c,"no")==0){
                        flag=false;
                    }
                }
                else
                    flag=false;
            }

            if(strcmp(c,"Help")==0 || strcmp(c,"help")==0){
                if(pomoc==0){
                    pomoc++;
                }
                printf("\nTo move around the map, follow the commands (north,south,east,west).\n");
                printf("\nTiles marked as 'y' are unpassable, you may not move through them. Player is marked as 'o'.\n");
                printf("\nWhen you get to the tile marked 'a' you will enter a battle with a random monster. That's when the game of RPS initiates.\n");
                printf("\nType start to begin.\n");

            }

            if(strcmp(c,"Exit")==0 || strcmp(c,"exit")==0){
                exit(1);
            }

        
    }
}

void terrain(char *l){ //function for drawing the terrain (not used anywhere in the code, written as a concept)
    int i,j;
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            putchar(l[i*3+j]);
        }
    printf("\n");
    }
}

void move(char *d, struct player *p, struct level lvl){ // function for movement
    int x = p->position[1];
    int y = p->position[0];
    if(strcmp(d,"north")==0){
        if(y-1<0){
            printf("\nYou may not go here\n");
        }      
        else if(get_index(x,y-1,lvl)=='y'){
            printf("\nYou may not go here\n");
        }
        else
            y-=1;
    }
    if(strcmp(d,"south")==0){
        if(y+1>4){
            printf("\nYou may not go here\n");
        }      
        else if(get_index(x,y+1,lvl)=='y'){
            printf("\nYou may not go here\n");
        }
        else
            y+=1;
    }
    if(strcmp(d,"west")==0){
        if(x+1>4){
            printf("\nYou may not go here\n");
        }      
        else if(get_index(x+1,y,lvl)=='y'){
            printf("\nYou may not go here\n");
        }
        else
            x+=1;
    }
    if(strcmp(d,"east")==0){ 
        if(x-1<0){
            printf("\nYou may not go here\n");
        }      
        else if(get_index(x-1,y,lvl)=='y'){
            printf("\nYou may not go here\n");
        }
        else
            x-=1;
    }
    p->position[1] = x;
    p->position[0] = y;
}

void showPlayer(char *plr, struct player p){ // function that draws the map with the player
    printf("y: %d, x: %d\nCurrent level: %d\n\n", p.position[0], p.position[1], p.current_level);
    int i,j;
    for(i=0;i<5;i++){
        for(j=0;j<5;j++){
            if((i==p.position[0]) && (j==p.position[1])){
                putchar('o');
            }
            else
                putchar(plr[i*5+j]);
        }
    printf("\n");
    }
    printf("\n");
}

void resetPos(struct player *p){ // reset the player position after he has reached a new level
    int x = 0;
    int y = 2;

    p->position[1] = x;
    p->position[0] = y;

}

struct level * generateLevels(){ // reads the structure from levels.txt and puts them in an array
    FILE *fptr;
    struct level * game;

    fptr = fopen("levels.txt","r");
    int i,j,k;
    char c = fgetc(fptr);
    k=atoi(&c);
    fgetc(fptr);

    game = (struct level *)malloc(k*sizeof(struct level));


    for(j=0;j<k;j++){
        struct level lvl;
        for(i=0;i<25;i++){
            lvl.show[i] = fgetc(fptr);
        }
        game[j]=lvl;
        fgetc(fptr);
    }
    fclose(fptr);
    return game;
}

void minplame(){ // function for the RPS minigame
    char *enemies[3] = {"Bandit", "Troll", "Dragon"};
    int hp = 2;
    int br = 0;
    int pc;
    int i,j;
    int k = rand() % 3;
    

    printf("\nYour foe is a:  %s\n", enemies[k]);
    while(hp>br){
        pc=rand() % 3;
        int player = choice();
        bool flag = false;
        if(pc==0 && player==1){
            flag=true;
        }
        if(pc==1 && player == 2){
            flag=true;
        }
        if(pc==2 && player == 0){
            flag=true;
        }
        if(pc==player){
            printf("\nNobody won!\n");
        }
        else if(flag==true){
            printf("\nYou have won the round!\n");
            br++;
        }
        else
            printf("\nYou have lost the round!\n");
    }

}

int choice(){ // used to convert the choice to int and forward it to the previous function
    char d[20];
    while(true){
        printf("\nChoose your move: rock, paper, scissors.\n");
        fflush(stdin);
        gets(d);
        if (strcmp(d, "paper")){
            return 0;
        }
        if(strcmp(d, "rock")){
            return 1;
        }
        if(strcmp(d, "scissors")){
            return 2;
        }
        printf("Wrong input");
    }


}

char get_index(int x, int y, struct level lvl){ // function that returns the type of tile (reads if its passable or not)
    return lvl.show[5*y +x];
    }

