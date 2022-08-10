
#ifndef PRO2_DESIGN_H
#define PRO2_DESIGN_H


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char ok[10];
unsigned long long int position=0;    //to see where it is the form
int list_index[100][100];
int stars;


int get_max(char *buffer){
    int max=0;
    int test=1;

    for(int i=0 ; i<strlen(buffer) ; i+=1){
        if(buffer[i]=='+'){
            if(test>max) {
                max=test;
                test=1;
            }
        }
        else test+=1;

    }
    return max;

}


void show_form(char *username ,char *name_form){
    int num_title=0;
    int max_size;
    int used_size=0;

    char check_2[100];
    int index=-1;
    FILE *fp;
    fp= fopen(username, "r");
    fseek(fp, position, SEEK_SET);
    char word;
    while(1){
        word= fgetc(fp);
        if(word=='>'){          //to print titles
            num_title+=1;
            while(1){
                word= fgetc(fp);
                if(word=='-') {
                    index+=1;
                    fgets(check_2,100,fp );
                    check_2[strlen(check_2)]='\0';
                    if(check_2[0]=='\n')max_size=used_size;
                    else max_size=get_max(check_2);
                    if(used_size>max_size){
                        max_size=used_size+1;
                    }
                    list_index[0][index]=max_size;
                    break;
                }
                printf("%c",word);
                used_size+=1;
            }
            for(int j=0 ; j<max_size-used_size ; j+=1){
                printf(" ");
            }
            printf("|");
            used_size=0;

        }
        else if(word=='*' || word==EOF)break;
    }
    printf("\n");

    fseek(fp, position, SEEK_SET);
    index=-1;
    int finish[100];
    int used=0;
    for(int in=0 ; in<num_title ; in+=1){
        list_index[1][in]=0;
        finish[in]=0;
    }
    while(1) {
        word = fgetc(fp);
        if(word=='-'){
            index +=1;
            char inner_info[100];
            fgets(inner_info,100 , fp);
            for(int i= list_index[1][index]; i<strlen(inner_info) ; i+=1){
                if(inner_info[i]=='+') {
                    for(int k=0 ; k<list_index[0][index]-used; k+=1) {
                        printf(" ");
                    }
                    printf("|");
                    list_index[1][index]+=1;
                    used=0;
                    break;
                }
                else if(inner_info[i]=='\n' || inner_info[i]=='&'){
                    for(int k=0 ; k<list_index[0][index]; k+=1) {
                        printf(" ");
                    }
                    printf("|");
                    finish[index]=1;
                }
                else{
                    list_index[1][index]+=1;
                    used+=1;
                    printf("%c",inner_info[i]);
                }
            }

        }
        else if(word=='*' || word=='&') {
            fseek(fp, position, SEEK_SET);
            printf("\n");
            index=-1;
        }

        for(int k=0 ; k<num_title ;k+=1){
            if(finish[k]==0)break;
            else if(k==num_title-1) {
                fclose(fp);
                return;
            }
        }

    }
}

int check_empty(char *username ,char *name_form){

    char check[100];

    FILE *forms;
    forms = fopen(username, "r");
    stars=0;
    while (1) {

        fgets(check, 50, forms);
        check[strlen(check)-1]='\0';
        position+=strlen(check)+2;
        stars+=1;
        if(!strcmp(check,name_form)){
            char check_char;
            check_char=fgetc(forms);
            if(check_char=='*' || check_char==EOF || check_char=='&'){
                return 0;        // it is empty
            }
            else return 1;       // it is not empty
        }
    }
}

void add_title(char *username){
    char title[100];
    printf("ADD A Title: ");
    getchar();
    gets(title);
    printf("OK? ");
    gets(ok);
    unsigned long long all;
    unsigned long long left;
    FILE *fp;
    fp = fopen(username, "r+");
    fseek(fp, 0, SEEK_END);
    all = ftell(fp);
    fseek(fp, position, SEEK_SET);
    left = all - position;
    char *buffer;
    buffer = (char *) malloc(sizeof(char) * left);
    size_t result = fread(buffer, 1, left, fp);
    buffer[strlen(buffer)] = '\0';
    fseek(fp, position, SEEK_SET);
    fprintf(fp, ">%s-", title);
    fprintf(fp, "\n%s", buffer);
    fclose(fp);
    system("cls");
}


void add_info(char * username){
    char title[100];
    printf("Choose Title:");
    getchar();
    gets(title);
    FILE *fp;
    fp= fopen(username, "r");
    fseek(fp, position, SEEK_SET);
    char word;
    int index=0;
    int n=0;
    int pass=0;
    while(1){
        word=fgetc(fp);
        pass+=1;
        if(word=='>'){
            n=0;
            while(word!='-'){
                word= fgetc(fp);
                pass+=1;
                if(word!=title[n]){
                    index+=1;
                    break;
                }
                n+=1;
            }
            if(word=='-') break;

        }
    }
    index-=1;

    for(int i=0 ; i<index ; i+=1){
        list_index[1][index]+=1;
    }
    pass+=list_index[1][index];

    printf("type:");
    gets(title);
    printf("OK? ");
    gets(ok);
    unsigned long long all;
    unsigned long long left;
    fp = fopen(username, "r+");
    fseek(fp, 0, SEEK_END);
    all = ftell(fp);
    fseek(fp, position+pass, SEEK_SET);
    left = all - position;             // I think has a bug
    char *buffer;
    buffer = (char *) malloc(sizeof(char) * left);
    size_t result = fread(buffer, 1, left, fp);
    buffer[strlen(buffer)] = '\0';
    fseek(fp , position+pass , SEEK_SET);
    fprintf(fp,"%s+",title);
    fprintf(fp, "%s", buffer);
    fclose(fp);
    system("cls");

}

void add(char *name_form,char *username){
    char title[100];
    char name_form2[100]={'*','*'};
    strcat(name_form2,name_form);
    if(check_empty(username,name_form2)==0) {

        printf("This form is empty add title: ");
        gets(title);
        unsigned long long all;
        unsigned long long left;
        FILE *fp;
        fp = fopen(username, "r+");
        fseek(fp, 0, SEEK_END);
        all = ftell(fp);
        fseek(fp, position, SEEK_SET);
        left = all - position;
        char *buffer;
        buffer = (char *) malloc(sizeof(char) * (left+1));
        size_t result = fread(buffer, 1, left, fp);
        buffer[strlen(buffer)] = '\0';
        fseek(fp, position, SEEK_SET);
        fprintf(fp, ">%s-", title);
        fprintf(fp, "\n%s", buffer);
        fclose(fp);
        system("cls");
    }
    while(1) {
        show_form(username, name_form2);
        printf("\n1)ADD Title\n2)ADD info\n3)Exit\n");
        int add;
        scanf("%d", &add);
        if (add == 1){
            system("cls");
            printf("\n1)ADD Title <<--\n2)ADD info\n3)Exit\n");
            add_title(username);
        }
        else if (add == 2) {
            system("cls");
            printf("\n1)ADD Title\n2)ADD info <<--\n3)Exit\n");
            add_info(username);
        }
        else break;
    }
}

int is_rmv=0;
int rep(char *username , char replace[] , char title[], char *name_form){

    int pass=0;
    char word;
    int is_same=1;
    title[strlen(title)]='\0';
    FILE *fp;
    fp = fopen(username, "r+");
    fseek(fp, position, SEEK_SET);
    while(1){

        word=fgetc(fp);
        pass+=1;
        if(word!='>' && word!='-' && word!='+'){
            if(word==title[0]){
                int n=0;
                is_same=1;
                while(title[n]!='\0'){
                    if(word!=title[n]) {
                        is_same=0;
                        break;
                    }
                    n+=1;
                    word=fgetc(fp);
                    pass+=1;
                }
                if(is_same==1){
                    pass-= strlen(title);
                    int all;
                    fseek(fp, 0, SEEK_END);
                    all = ftell(fp);
                    fclose(fp);
                    fp = fopen(username, "r+");
                    char *all_buffer= malloc(sizeof(char)*(all+1));
                    fread(all_buffer, 1, all, fp);
                    fclose(fp);
                    int no_change=0;
                    fp=fopen(username,"r+");
                    stars+=1;
                    position-=stars;
                    pass-=1;
                    for(int i=0 ; i<all ;i+=1){
                        if(i==pass+position) {
                            if(is_rmv==0) {
                                fprintf(fp,"%s",replace);
                                i+= strlen(title);
                            }
                            else i+= strlen(title)+1;

                        }
                        else if(all_buffer[i]=='&')break;
                        else fprintf(fp,"%c",all_buffer[i]);
                    }
                    fclose(fp);
                    position+=stars;
                    return 0;
                }
            }
        }
    }
}


void edit(char *name_form,char *username){
    char title[100];
    char replace[100];
    char name_form2[100]={'*','*'};
    strcat(name_form2,name_form);
    if(check_empty(username,name_form2)==0){
        add(name_form,username);
    }
    else {
        show_form(username,name_form2);
        printf("\nwhich word do you want to change?");
        getchar();
        gets(title);
        printf("\n");
        printf("Replace it with:");
        gets(replace);
        printf("OK? ");
        gets(ok);
        rep(username, replace,title, name_form2);
        system("cls");
        show_form(username,name_form2);
    }
}


void rmv(char *name_form,char *username){
    char remove[100];
    char name_form2[100]={'*','*'};
    strcat(name_form2,name_form);
    check_empty(username,name_form2);
    show_form(username,name_form2);
    printf("\nWhich word do you want to remove?");
    getchar();
    gets(remove);
    printf("OK? ");
    gets(ok);
    is_rmv=1;
    rep(username,NULL,remove,name_form);
    is_rmv=0;
    show_form(username,name_form2);

}


extern void forms_handle(char *name_form ,char step ,char *username , int plus){

    if(step=='1'){
        add(name_form, username);
    }
    else if(step=='3'){
        if(plus) position+1;
        edit(name_form,username);
    }
    else if(step=='4'){
        rmv(name_form,username);
    }


}


#endif //PRO2_DESIGN_H
