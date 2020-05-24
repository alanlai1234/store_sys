#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

typedef struct cart
{
    char idcode[10];
	int amount;
    struct cart *next;
}CART;

typedef struct item
{
    char name[50];
    char descrip[100];
    char seller[20];
    char idcode[10];
    float price;
    int amount;
    struct item *next;
}ITEM;

char accname[20];

void print_item(ITEM *head){
	// TODO it will print out of the screen
    ITEM *move=head;
    int cur=1;
	clear();
	attron(COLOR_PAIR(4));

    while(move->next!=NULL){
        printw("(%d) $%f\nitem name : %s\n\n", cur++, move->price, move->name);
        move=move->next;
    }

	attron(COLOR_PAIR(2));
}

int login(char filename[]){
    char name[20], pw[25], name_login[20], psw_login[25];
    int flag;
    FILE *fp;
    fp=fopen(filename, "r");
	clear();
	curs_set(1);
    while(1){
        flag=0;
        //back from start
        fseek(fp, 0, SEEK_SET);

        printw("enter user name, enter 0 to exit : ");
		scanw("%s", name);

        //exit
        if(!strcmp(name, "0")){
            fclose(fp);
            return 0;
        }

        //scan from inputted name
        while(fscanf(fp, "%s %s", name_login, psw_login)!=EOF){
            //inputted name found
            if(!strcmp(name, name_login)){
                flag=1;
                break;
            }
        }
        
        //if inputted name found
        if(flag){
			clear();
            while(1){
                printw("enter password, or 0 to enter username again : ");
                scanw("%s", pw);
                //back to input name
                if(!strcmp(pw, "0")){
                    break;
                }
                //password correct
                if(!strcmp(pw, psw_login)){
                    strcpy(accname, name);
                    fclose(fp);
					
                    return 1;
                }
				clear();
                printw("password not match\n");
            }
            continue;
        }
		clear();
        printw("name not found\n");
    }
}
