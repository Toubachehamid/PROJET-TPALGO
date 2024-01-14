#include <stdio.h>  
#include <stdlib.h>
 
typedef struct Element { 
    int info; 
    struct Element* prec; 
    struct Element* suiv; 
} Element;


Element* creerElement(int info) { 
    Element* newElement = (Element*)malloc(sizeof(Element)); 
    newElement->info = info; 
    newElement->prec = NULL; 
    newElement->suiv = NULL; 
    return newElement; 
} 

void inserer(Element** tete, int info) {
    Element* newElement = creerElement(info);
    if (*tete == NULL) {
        *tete = newElement;
    } else {
        Element* current = *tete;
        while (current->suiv != NULL) {
            current = current->suiv;
        }
        current->suiv = newElement;
        newElement->prec = current;
    }
} 

void insererTrie(Element** tete, int info) {
    Element* newElement = creerElement(info);
    Element* current;

    if (*tete == NULL || (*tete)->info >= newElement->info) {
    
        newElement->suiv = *tete;
        if (*tete != NULL) {
            (*tete)->prec = newElement;
        }
        *tete = newElement;
    } else {
        current = *tete;
        while (current->suiv != NULL && current->suiv->info < newElement->info) {
            current = current->suiv;
        }
        newElement->suiv = current->suiv;
        if (current->suiv != NULL) {
            current->suiv->prec = newElement;
        }
        current->suiv = newElement;
        newElement->prec = current;
    }
}

void supprimerElement(Element** tete, int valeur) {
    Element* current = *tete;

    while (current != NULL) {
        if (current->info == valeur) {

            if (current->prec == NULL) {
                *tete = current->suiv;
                if (current->suiv != NULL) {
                    current->suiv->prec = NULL;
                }
                free(current);
                current = *tete;
            } else {
            
                Element* temp = current;
                current->prec->suiv = current->suiv;
                if (current->suiv != NULL) {
                    current->suiv->prec = current->prec;
                }
                current = current->suiv;
                free(temp);
            }
        } else {
            current = current->suiv;
        }
    }
}


void rechercherElement(Element* tete, int valeur) {
    Element* current = tete;
    Element* c =tete;
    Color c1 = (Color){ 61, 76, 65};
    int xPos = 20;
    bool trouve=false;

    while (c != NULL)
    {
      if(c->info == valeur)
      {
        trouve = true;
        break;
      }
      c=c->suiv;
    } }


void trieABulles(Element* tete) {
    int swapped;
    Element* ptr1;
    Element* lptr = NULL;
    Color c1 = (Color){ 61, 76, 65};

    do {
        swapped = 0;
        ptr1 = tete;

        while (ptr1->suiv != lptr) {
            if (ptr1->info > ptr1->suiv->info) {
                int temp = ptr1->info;
                ptr1->info = ptr1->suiv->info;
                ptr1->suiv->info = temp;
                swapped = 1;
            }
            ptr1 = ptr1->suiv;
        }
        lptr = ptr1;
      
        

    } while (swapped);
}
void inserer(Element** tete, int info) {
    Element* newElement = creerElement(info);
    if (*tete == NULL) {
        *tete = newElement;
    } else {
        Element* current = *tete;
        while (current->suiv != NULL) {
            current = current->suiv;
        }
        current->suiv = newElement;
        newElement->prec = current;
    }
} 
int main() { 
return (0);
}