
#ifndef PRO2_FIND_H
#define PRO2_FIND_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "design.h"


char * fix(char is_forms[]){
    char *new_=(char *) malloc(100*sizeof(char));
    int n=0;

    for(int i=0 ; i< strlen(is_forms) ; i+=1){
        if(is_forms[i]=='*' && i>1){
            if(new_[n-1]!=',') {
                new_[n] = ',';
                n += 1;
            }
        }
        new_[n]=is_forms[i];
        n+=1;
    }
    return new_;
}


char* delete(char is_forms[] , char form[]){
    char* new_=(char *) malloc(100* sizeof(char));
    char test[100];
    int index=0;
    new_[0]='\0';
    for(int i=0 ; i <strlen(is_forms) ; i+=1){
        if(is_forms[i]==','){
            if(strcmp(test,form)!=0){
                test[strlen(test)]='\0';
                int len= strlen(new_);
                for(int j = len ; j< len+ strlen(test) ; j+=1){
                    new_[j]=test[j-len];
                    new_[j+1]='\0';
                }
                new_[strlen(new_)]='\0';

            }
            index=0;
        }
        else {
            test[index]=is_forms[i];
            test[index+1]='\0';
            index+=1;
        }
    }
    return new_;


}




char * check(char word[] , char is_forms[],char *username ){

    char form[100];
    char * test=(char *) malloc(100* sizeof(char));
    int index=0;
    char chr;
    int same=0;
    int end=0;
    int star=0;
    int len;
    len= strlen(is_forms);
    char const_[100];
    const_[0]='\0';
    strcat(const_,is_forms);
    const_[strlen(const_)]='\0';
    FILE *file;
    file= fopen(username, "r+");
    while(1){
        fgets(form ,100 ,file);
        if(form[0]=='&'){
            fclose(file);
            return is_forms;

        }
        form[strlen(form)-1]='\0';
        for(int i=0 ; i<len ; i+=1){
            if(const_[i]==','){
                if(star) {
                    char add_star[100];
                    add_star[0]='*';
                    add_star[1]='\0';
                    strcat(add_star,form);
                    form[0]='\0';
                    strcat(form,add_star);
                    form[strlen(form)]='\0';
                    star=0;
                }
                index=0;
                if(strcmp(form,test)==0){
                    while(1){
                        chr=fgetc(file);
                        if(chr=='*' || chr=='&') {
                            if(chr=='*') star=1;
                            char new_form[100];
                            new_form[0]='\0';
                            if(end==0) {
                                strcat(new_form, delete(fix(is_forms), test));
                                is_forms[0]='\0';
                                strcat(is_forms,new_form);
                            }
                            if(chr=='&'){
                                fclose(file);
                                return is_forms;
                            }
                            break;

                        }
                        else if(chr==word[0]){
                            same=1;
                            for (int j = 1; j < strlen(word); j += 1) {
                                if (word[j] != fgetc(file)) {
                                    break;
                                } else same += 1;
                            }
                            if (strlen(word) == same){
                                end=1;
                            }

                        }
                    }
                    if(end){
                        end=0;
                        break;
                    }
                }

            }
            else {
                test[index]=const_[i];
                test[index+1]='\0';
                index+=1;
            }
        }
    }

}




extern void search(char * username){
    char form[100];
    char is_forms[100];
    char all_word[100];
    char word[100];
    printf("Let's Find It !\n");
    getchar();
    gets(all_word);
    FILE *fp;
    fp= fopen(username,"r+");
    int n=0;
    all_word[strlen(all_word)]='\n';
    for(int i=0 ; i< strlen(all_word) ; i+=1){
        if(all_word[n]=='\n' || all_word[n]==' '){
            char c;
            int end=0;
            while(1) {
                fgets(form, 100, fp);
                while (1) {
                    c = fgetc(fp);
                    if (c == word[0]) {
                        int same = 1;
                        for (int j = 1; j < strlen(word); j += 1) {
                            if (word[j] != fgetc(fp)) {
                                break;
                            } else same += 1;
                        }

                        if (strlen(word) == same) {
                            form[strlen(form)-1] = ',';
                            if(form[1]!='*' )  strcat(is_forms,"*");
                            strcat(is_forms, form);

                        }

                    } else if (c == '*') {

                        break;
                    }
                    else if(c=='&') {
                        end=1;
                        break;
                    }
                }
                if(end) break;

            }
            break;
        }
        else {
            word[n]=all_word[i];
            word[n+1]='\0';
            n+=1;
        }
    }
    fclose(fp);
    int index=0;
    n+=1;
    for(int i=n ; i< strlen(all_word)-1 ; i+=1){
        if( i== strlen(all_word)-2 || all_word[n]==' '){
            char new_is_forms[100];
            new_is_forms[0]='\0';
            strcat(new_is_forms,check(word,is_forms, username));
            if(new_is_forms[0]!='\0') {
                is_forms[0]='\0';
                strcat(is_forms,new_is_forms);
            }
            index=0;
        }
        else{
            word[index]=all_word[i];
            word[index+1]='\0';
            index+=1;
        }

    }
    //printf("%s\n",is_forms);
    printf("Available in these forms Enter the form you want:\n");
    //printf("%s\n",is_forms);
    for(int i=0 ; i< strlen(is_forms) ; i+=1){
        if(is_forms[i]!='*') {
            printf("%c",is_forms[i]);
        }
    }
    char name_form[100];
    printf("Which form ?\n");
    gets(name_form);
    printf("1)Add\n2)Find\n3)Edit\n4)Remove\n5)Quit\n");
    char step;
    step=getchar();
    forms_handle(name_form, step ,username , 1);

}





#endif //PRO2_FIND_H
