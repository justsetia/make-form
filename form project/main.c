#include <stdio.h>
#include <string.h>
#include "greeting.h"
#include <stdlib.h>
#include "design.h"
#include "find.h"

#include<conio.h>

int check_form(char *username){
    FILE *fp;
    fp= fopen(username , "r");
    if (fgetc(fp)!='*') return 0;
    else return 1;
}

void create(char username[]){
    while(1) {
        printf("\nHow can I help you?\n");
        printf("1)Add\n2)Find\n3)Edit\n4)Remove\n5)Quit\n");
        char step;
        getchar();
        while (1) {
            step = getchar();
            system("cls");
            if(step=='5')return;
            if (step == '1' || step == '2' || step == '3' || step == '4') {
                system("cls");
                break;
            } else {
                printf("Invalid Choice try another\n");
                getchar();
            }
        }
        if (step == '2') {
            search(username);
        }
        else {
            printf("1)New form\n2)My forms\n");
            getchar();
            int choice;
            scanf("%d", &choice);
            system("cls");
            while(1) {
                if (choice == 1) {
                    char name_title[50];
                    printf("1)New form <<--\n2)My forms\n");
                    printf("Choose name for form :\n");
                    getchar();
                    gets(name_title);
                    printf("%s\n", name_title);
                    FILE *fp;
                    fp = fopen(username, "a");
                    fprintf(fp, "**%s\n&", name_title);
                    fprintf(fp, "&");
                    fclose(fp);
                } else {
                    printf("1)New form\n2)My forms <<--\n");
                }
                system("cls");
                if (check_form(username)) {
                    printf("Enter which form ?\n");
                    FILE *forms;
                    forms = fopen(username, "r");
                    char *title = (char *) malloc(100 * sizeof(char));
                    while (1) {
                        if (fgetc(forms) == EOF) break;
                        fgets(title, 50, forms);
                        if (title[0] == '*') printf("%s", title);

                    }
                    fclose(forms);
                    printf("\nEnter please :");
                    getchar();
                    gets(title);
                    forms_handle(title, step, username,0);
                    break;
                } else {
                    printf("There is no form create one:\n");
                    choice=1;
                }
            }
        }
    }

}

int main() {

    char *user_name=(char *) malloc(50* sizeof(char));

    user_name=enter();
    create(user_name);


    return 0;
}
