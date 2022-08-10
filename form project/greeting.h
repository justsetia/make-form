
#ifndef PRO2_GREETING_H
#define PRO2_GREETING_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int check_match(char username[] , int pass){

    char check[100];
    int add=0;
    FILE *fp;
    fp = fopen("users.txt", "r");
    while(1){
        check[add]=fgetc(fp);
        if(feof(fp)){
            fclose(fp);
            break;
        }
        if(check[add]==' '){
            check[add]='\0';
            int x;
            fscanf(fp,"%d",&x);        //for numbers
            if(strcmp(check,username)==0) {
                printf("This Username has already taken try another one \n");
                getchar();
                return 1;
            }
            else {
                add=-1;
                fgetc(fp);
            }
        }
        check[add+1]='\0';
        add+=1;
    }                              // wasn't same , so we add it
    fp = fopen("users.txt", "a");
    fprintf(fp, "%s ", username);
    fprintf(fp , "%d\n", pass);
    fclose(fp);
    FILE *file;
    file=fopen(username,"w");
    fclose(file);
    printf("Welcome :) \n");
    system("cls");
    return 0;
}


char * sign_up(){
    char *username=(char*) malloc(50* sizeof(char));
    int pass;
    while(1) {        //getting username and password
        printf("Enter username:");
        gets(username);
        printf("\nEnter password:");
        scanf("%d", &pass);
        if(check_match(username , pass)==0){
            return username;
        }
    }
}


char * log_in(){
    char *username=(char*) malloc(50* sizeof(char));
    int pass;
    int match=0;
    while(1) {        //getting username and password
        printf("Enter username:");
        gets(username);
        printf("\nEnter password:");
        scanf("%d", &pass);

        char check[100];
        int add=0;
        FILE *fp;
        fp = fopen("users.txt", "r");
        while(1){
            check[add]=fgetc(fp);
            if(feof(fp)){
                fclose(fp);
                break;
            }
            if(check[add]==' '){
                int check_pass;
                fscanf(fp,"%d",&check_pass);        //for numbers
                check[add]='\0';
                if(strcmp(check, username)==0 && (pass==check_pass) ) {
                    printf("You've logged in welcome\n");
                    match=1;      //match hast
                    fclose(fp);
                    system("cls");
                    break;
                }
                else{
                    add=-1;
                    fgetc(fp);
                }
            }
            check[add+1]='\0';
            add+=1;
        }
        if(match==1) return username;
        else {
            printf("Something went wrong try again \n");
            getchar();
        }
    }

}

extern char* enter(){
    printf("Welcome Do you Have an account?\n");
    printf("1)Yes I want to Log In\n2)No Create an account\n");
    int choice;
    while(1){
        scanf("%d",&choice);
        getchar();
        system("cls");
        if(choice==1 || choice==2){
            break;
        }
        else{
            printf("Invalid Choice!\n");
        }
    }
    //system("cls");
    if(choice==1){
        printf("1)Yes I want to Log In <<--\n2)No Create an account\n");
        return log_in();
    }
    else {
        printf("1)Yes I want to Log In <<--\n2)No Create an account<<--\n");
        return sign_up();
    }

}



#endif //PRO2_GREETING_H
