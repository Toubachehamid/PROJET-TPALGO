#include "raylib.h" 
#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
 
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

void delay(float seconds) {
    double startTime = GetTime();
    double currentTime;

    do {
        currentTime = GetTime();
    } while (currentTime - startTime < seconds);
}

 

void drawList(Element* tete) {
    Element* current = tete;
    int xPos = 20;

    while (current != NULL) {

        DrawRectangle(xPos, 250, 60, 50,LIGHTGRAY);
        DrawRectangleLines(xPos, 250, 60, 50, BLACK);
        DrawText(TextFormat("%d", current->info), xPos + 25, 270, 20, RED);
        if (current->suiv != NULL) {
            DrawLine(xPos + 60, 265, xPos + 60 + 20, 265, BLACK);
            DrawText("<", xPos + 60, 254, 25, BLACK);
            DrawLine(xPos + 60, 285, xPos + 60 + 20, 285, BLACK);
            DrawText(">", xPos + 60 + 14, 274, 25, BLACK);
        }

        xPos += 80;
        current = current->suiv;
    }
}

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
      
        BeginDrawing();
        ClearBackground(c1);
        DrawText("Le trie a Bulles corespandant a la liste :",160,80,25,LIGHTGRAY);
        DrawLine(160,115,680,115,DARKGRAY);
        delay(1);
        drawList(tete);
        EndDrawing();

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
    }
    
    
    BeginDrawing();
    ClearBackground(c1);
    DrawText("Résultat de la recherche :", 160, 80, 25, LIGHTGRAY);
    DrawLine(160, 115, 680, 115, DARKGRAY);
    if (trouve == true)
     {
      while (current != NULL) {

        DrawRectangle(xPos, 250, 60, 50,LIGHTGRAY);
        DrawRectangleLines(xPos, 250, 60, 50, BLACK);
        if(current->info == valeur)
        {
            DrawRectangleLines(xPos-2,248,65,55,RED);
            DrawRectangle(20, 320, 200, 30, WHITE);
            DrawText("Element trouvé !", 25, 325, 20, BLACK);
            trouve = true;
        }
        DrawText(TextFormat("%d", current->info), xPos + 25, 270, 20, RED);
        if (current->suiv != NULL) {
            DrawLine(xPos + 60, 265, xPos + 60 + 20, 265, BLACK);
            DrawText("<", xPos + 60, 254, 25, BLACK);
            DrawLine(xPos + 60, 285, xPos + 60 + 20, 285, BLACK);
            DrawText(">", xPos + 60 + 14, 274, 25, BLACK);
        }

        xPos += 80;
        current = current->suiv;
      }
    }
    else
    {
                   ClearBackground(c1);
                    DrawText("La saisie que vous avez effectuée ne correspond à aucun élément.", 70, 210, 20, BLACK);
    }
    
    EndDrawing();
    delay(4);
}


int main() { 
    const int screenWidth = 900; 
    const int screenHeight = 500; 
    InitWindow(screenWidth, screenHeight, "Les fonctions fondamentales d'une liste doublement chaînée."); 
    SetTargetFPS(60); 
    Color c1 = (Color){ 61, 76, 65};
    Element* tete = NULL; 
    char inputText[10] = { 0 }; 
    Rectangle textBox = { 60, 80, 200, 45 }; 
    bool textBoxSelected = false; 
     int info ;

    while (!WindowShouldClose()) { 
        if (CheckCollisionPointRec(GetMousePosition(), textBox)) { 
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { 
                textBoxSelected = true; 
            } 
        } else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { 
            textBoxSelected = false; 
        } 
 
        if (textBoxSelected) { 
            int key = GetCharPressed(); 
            while (key > 0) { 
                if ((key >= '0' && key <= '9') && (strlen(inputText) < 9)) { 
                    int inputLength = strlen(inputText); 
                    inputText[inputLength] = (char)key; 
                    inputText[inputLength + 1] = '\0'; 
                } 
                key = GetCharPressed(); 
            } 
 
            if (IsKeyPressed(KEY_BACKSPACE)) { 
                int inputLength = strlen(inputText); 
                if (inputLength > 0) { 
                    inputText[inputLength - 1] = '\0'; 
                } 
            } 
        } 
 
     if (IsKeyPressed(KEY_I) && strlen(inputText) > 0) 
       { 
            info = atoi(inputText); 
            inserer(&tete, info); 
            inputText[0] = '\0'; 
       } 

       if (IsKeyPressed(KEY_T) && strlen(inputText) > 0)
       {
            info = atoi(inputText); 
            insererTrie(&tete, info); 
            inputText[0] = '\0';
       }

       if(IsKeyPressed(KEY_B))
       {
                trieABulles(tete);
       }

       if(IsKeyPressed(KEY_S))
       {
             info = atoi(inputText); 
            supprimerElement(&tete, info); 
            inputText[0] = '\0';
       }

       if (IsKeyPressed(KEY_R) && strlen(inputText) > 0)
       {
         info = atoi(inputText);
         rechercherElement(tete, info);
         inputText[0] = '\0';
       }  
    

   
        BeginDrawing(); 
        ClearBackground(c1); 
        drawList(tete); 
        DrawRectangleRec(textBox,LIGHTGRAY); 
        if (textBoxSelected ) 

        {
         DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
         DrawText(inputText, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);
         DrawText("Entrez un chiffre .", 64, 20, 20, BLACK); 
         }
        
        DrawText("- Pour réaliser une insertion , appuyez sur la touche 'I'.", 350, 65, 18,LIGHTGRAY); 
        DrawText("- Pour effectuer une insertion triée, appuyez sur la touche 'T'.", 350, 95, 18, LIGHTGRAY); 
        DrawText("- Pour supprimer un élément, cliquez sur la touche 'S'.", 350, 125, 18, LIGHTGRAY); 
        DrawText("- Pour rechercher un élément, appuyez sur la touche 'R'.", 350, 155, 18, LIGHTGRAY); 
        DrawText("- Pour effectuer le tri à bulle, appuyez sur la touche 'B'.", 350, 35, 18,LIGHTGRAY ); 

 
        EndDrawing(); 
    } 
 
    while(tete != NULL) { 
        Element* temp = tete; 
        tete = tete->suiv; 
        free(temp); 
    } 
 
    CloseWindow(); 
 
    return 0; 
}