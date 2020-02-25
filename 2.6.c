// + - ?
#include <stdio.h>
#include <stdlib.h>

typedef struct Tree{
        int elem;
        struct Tree * right;
        struct Tree * left;
        }Tree;

void Add (Tree ** p,int a){
    if(*p == NULL){
        Tree * tmp =(Tree*) malloc(sizeof(Tree)); // Выделяем память для нового элемента
        tmp->elem=a; // (*tmp).elem=a;
        tmp->right=NULL;
        tmp->left=NULL;
        *p = tmp; //
      }
    else{
          if((*p)->elem < a){
             Add(&((*p)->right), a); // Берем адрес конкретной ячейки справа для поиска в правом поддереве
          }
          else if((*p)->elem > a){
             Add(&((*p)->left), a); // Берем адрес конкретной ячейки слева для поиска в левом поддереве
          }
        }
    }

Tree* Find (Tree * p, int a, Tree** parent){
    //printf("before - %d %d\n", p->elem, a);
    if(p==NULL){
        //printf("after - %d", (*parent)->elem);
        //printf("%d no \n", a);
        return NULL;
    }

    else if(p->elem==a){ // (*p).elem==a;
           // parent = &p;
           // printf("fdxfdxdfafter - %d", parent->elem);
         //printf("%d yes \n",a);
         return p;
    }

// Путешествие по поддеревьям
    else if(p->elem < a){
        *parent = p;
        //printf("after - %d", (*parent)->elem);
        return Find(p->right, a, parent);}

    else if(p->elem > a){
        *parent = p;
        //printf("after - %d", parent->elem);
        return Find(p->left, a, parent);}
}

void Delete (Tree ** p, int a){
    Tree *tmp1 = *p; // присваиваем указателю tmp адрес Tree
    Tree** parent = &tmp1; // присваиваем указателю на указатель parent адрес укзателя tmp
    
    Tree * cur = Find(*p, a, parent);
  
    if(cur != NULL){
    
        if (cur->right != NULL){
            Tree* tmp = cur->right;
      

            if (tmp->left == NULL){
               
                if (*parent == cur){
              
                    (*p)->elem = tmp->elem;
                    (*p)->right = tmp->right;
                    free(tmp);
                }
                else{
                    tmp->left = cur->left;
                    (*parent)->right = tmp;
                    //printf("new  %d", (*parent)->right->elem);
                    free(cur);
                }
            }
            else{
                while (tmp->left->left != NULL){
                    tmp = tmp->left;
                }
                //printf("tmp2 %d\n", (tmp)->elem);
                cur->elem = tmp->left->elem;
                tmp->left=tmp->left->right;
                //(tmp)->left = NULL;
                //Tree * k = tmp->left;
                //tmp->left = k->right;
                //(*parent)->elem=k->elem;
                free(tmp->left);
            }

        }
        else if (cur->left != NULL){
            Tree* tmp = cur->left;
            printf("tmp %d\n", (tmp)->elem);

            if (tmp->right == NULL){
                //(cur)->elem = tmp->elem;
                if (*parent == cur){
                    //(*p) = tmp;
                    //free(cur);
                    (*p)->elem = tmp->elem;
                    (*p)->left = tmp->left;
                    free(tmp);
                }
                else{
                    (*parent)->left = tmp;
                    //printf("new  %d", (*parent)->left->elem);
                    free(cur);
                }
            }
            else{
                while (tmp->right->right != NULL){
                    tmp = tmp->right;
                }
                //printf("tmp2 %d\n", (tmp)->elem);
                cur->elem = tmp->right->elem;
                tmp->right=tmp->right->left;
                //(tmp)->left = NULL;
                //Tree * k = tmp->left;
                //tmp->left = k->right;
                //(*parent)->elem=k->elem;
                free(tmp->right);
            }

        }
        else{
            //printf("nul nul %d %d\n", (cur)->elem, cur);
            //printf("head %d %d\n", (*p)->elem, *p);
            if (*p == cur){
                //free(cur);
                (*p) = NULL;

            }
            //else if ((*parent)->right->elem == cur->elem){
            //    (*parent)->right = NULL;
            //}
            else{
                if (((*parent)->left != NULL) && ((*parent)->left->elem == cur->elem))
                {
                    (*parent)->left = NULL;
                }
                else{
                    (*parent)->right = NULL;
                }
            }
            free(cur);
        }
    }
    else
        printf("%d no \n", a);
}


void main (){

    Tree * head = NULL, **parent = NULL;
    char str[256];
    int b;

    while(scanf("%s",str)!=EOF){

        if(str[0]=='+'){
          b=atoi(str);
          Add(&head, b);
          //parent = &head;
        }

        else if(str[0]=='-'){
          b=atoi(str+1);
          Delete(&head, b);}

        else if(str[0]=='?'){
          b=atoi(str+1);
        
          Tree *tmp = head;
          parent = &tmp;
      
          Tree * p = Find(head, b, parent);
          if (p != NULL)
            printf("%d yes \n",b);
          else
            printf("%d no \n", b);
          //printf("par find %d\n", (*parent)->elem);
        }
    }

    /*printf("%d", head->elem);
    printf("%d", head->right->elem);
    printf("%d", head->left->elem);*/

    return 0;
}
