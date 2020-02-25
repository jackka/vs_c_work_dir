// 2.5 последнее удалить
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Slova{
    char *elem;
    struct Slova *next;
    }Slova;


void add(Slova ** list , char str[]){
    Slova * tmp = (Slova*) malloc (sizeof(Slova));
    tmp->elem = (char*) malloc (sizeof(strlen(str)));

    strcpy(tmp->elem , str);
    tmp -> next = *list;
    *list = tmp;
    }

void print_list(Slova * list){
    while(list!=NULL){
        printf("%s ",list->elem);
        list=list->next;
        }
    printf("\n");
    }

void delete(Slova * list){

    if(list==NULL){ return; }

    Slova * prev = list;
    Slova * p=list->next;

    while(p!=NULL){
        if (strcmp(list->elem, p->elem)==0){
            prev->next=p->next;
            free(p->elem);
            free(p);
            p = prev->next;
            }
        else {
            prev=p;
            p=p->next;
        }
    }
}

int main()
{
    Slova * head = NULL;
    char str[256];
    printf("%s", "Введите последовательность слов и нажмите Ctrl+D");
    while(scanf("%s",str)!=EOF){
    add(&head, str);
    }

    delete(head);
    print_list(head);

    return 0;
}

