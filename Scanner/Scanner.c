
#include "Scanner.h"
#include <stdio.h>

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

char readChar(FILE *file, int *line) {
    char c = fgetc(file);
    if (c == '\n') (*line)++;
    return c;
}



int isValidAttributes(char *attribute) {
    char *ptr = attribute;
    while (1) {
        // Ignorer les espaces
        while (isspace((unsigned char)*ptr)) ptr++;
        if (*ptr == '\0') break;

        // Extraire le nom de l'attribut
        char *attr_start = ptr;
        while (*ptr != '\0' && !isspace(*ptr) && *ptr != '=') ptr++;
        if (attr_start == ptr) return 0;

        // Passer à '='
        while (isspace(*ptr)) ptr++;
        if (*ptr != '=') return 0;
        ptr++;

        // Passer à la valeur
        while (isspace(*ptr)) ptr++;

        char delim = *ptr;
        if (delim != '"' && delim != '\'') return 0;
        ptr++;

        // Vérifier les caractères interdits dans la valeur
        while (*ptr != delim && *ptr != '\0') {
            if (*ptr == '<' || *ptr == '>') return 0;
            ptr++;
        }
        if (*ptr != delim) return 0;
        ptr++;
    }
    return 1;
}

// Structure pour un nœud de la stack (chaîne + pointeur vers le suivant)
typedef struct StackNode {
    char* data;
    struct StackNode* next;
} StackNode;

// Structure pour la stack elle-même (pointeur vers le sommet)
typedef struct {
    StackNode* top;
} StringStack;

// Initialise une stack vide
StringStack* StackCreate() {
    StringStack* stack = (StringStack*)malloc(sizeof(StringStack));
    if (!stack) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }
    stack->top = NULL;
    return stack;
}

// Vérifie si la stack est vide
bool StackIsEmpty(StringStack* stack) {
    return (stack->top == NULL);
}

// Empile une chaîne (alloue dynamiquement une copie)
void StackPush(StringStack* stack, const char* str) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (!newNode) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }

    newNode->data = strdup(str); // Copie la chaîne
    if (!newNode->data) {
        fprintf(stderr, "Erreur de duplication de chaîne\n");
        free(newNode);
        exit(EXIT_FAILURE);
    }

    newNode->next = stack->top;
    stack->top = newNode;
}

// Dépile et retourne la chaîne (libère la mémoire du nœud)
char* StackPop(StringStack* stack) {
    if (StackIsEmpty(stack)) {
        fprintf(stderr, "Stack vide\n");
        return NULL;
    }

    StackNode* temp = stack->top;
    char* poppedData = temp->data; // Récupère la chaîne avant de libérer le nœud
    stack->top = temp->next;
    free(temp); // Libère le nœud (mais pas la chaîne, car elle est retournée)

    return poppedData;
}

int isWhiteSpace(char character, int *line){
    if (character == ' ' || character == '\n' || character == '\t') {
        return 1;
    }

    return 0;
}

int isLetter(char character){
    if ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z')){
        return 1;
    }
    return 0;
}

StringStack* TagStack;


void handleClosingTag(FILE *file, char *character, int *line){
    // Skip white spaces
    *character = readChar(file, line);
    while (isWhiteSpace(*character, line)) *character = readChar(file, line);

    // If the character is not a literal so Error
    if (!isLetter(*character)) { printf("Error at line %d\n", *line); exit(1); }

    // Get the closing tag name
    char closingTagName[10000];
    int index = 0;
    while (isLetter(*character)){
        closingTagName[index++] = *character;
        *character = readChar(file, line);
    }
    closingTagName[index] = '\0';

    // If the closing tag name is not equal to the opening tag name so Error
    char *openingTagName = StackPop(TagStack);
    if(!openingTagName) { printf("Error at line %d\n", *line); exit(1); }
    if  (strcmp(closingTagName, openingTagName) != 0)
        { printf("Error at line %d\n", *line); exit(1); }

    // Skip white spaces
    while (isWhiteSpace(*character, line)) *character = readChar(file, line);

    // If the character is not a '>' so Error
    if (*character != '>') { printf("Error at line %d\n", *line); exit(1); }
}

void handleOpeningTag(FILE *file, char *character, int *line)
{
    // Get the tag name
    char tagName[100];
    int index = 0;
    while(isLetter(*character)){
        tagName[index++] = *character;
        *character = readChar(file, line);
    }
    tagName[index] = '\0';

    // check if the *character is not a white space and not '>', Error
    if (!isWhiteSpace(*character, line) && *character != '>' && *character != '/')
        { printf("Error at line %d\n", *line); exit(1); }

    // If the *character is '>' so is a self closing tag
    if (*character == '/'){
        *character = readChar(file, line);
        while(isWhiteSpace(*character, line)) *character = readChar(file, line);
        if(*character != '>') { printf("Error at line %d\n", *line); exit(1); }
    }

    if (*character == '>'){ StackPush(TagStack, tagName); return; }

    // Skip  white spaces
    while (isWhiteSpace(*character, line)) *character = readChar(file, line);

    // Check for attributes
    if (!isLetter(*character) && *character != '>' && *character != '/')
        { printf("Error at line %d\n", *line); exit(1); }

    if(*character == '>') { StackPush(TagStack, tagName); return; }

    if(*character == '/') {
        *character = readChar(file, line);
        while(isWhiteSpace(*character, line)) *character = readChar(file, line);
        if(*character != '>') { printf("Error at line %d\n", *line); exit(1); }
    }

    // Get attributes
    char attributeName[MAX];
    int index2 = 0;
    int isQuoted = 0;
    while (*character != '>' && *character != '<' && *character != EOF){

        if(*character == '"' || *character == '\'') isQuoted = !isQuoted;
        if(*character == '/' && !isQuoted) break;

        attributeName[index2++] = *character;
        *character = readChar(file, line);
    }

    attributeName[index2] = '\0';

    if(!isValidAttributes(attributeName)) { printf("Error at line %d\n", *line); exit(1); }

    if(*character == '>') { StackPush(TagStack, tagName); }
    if(*character == '/') {
        *character = readChar(file, line);
        while(isWhiteSpace(*character, line)) *character = readChar(file, line);
        if (*character != '>') { printf("Error at line %d\n", *line); exit(1); }
    }
}


void performLexicalAnalysis(FILE *file)
{
    TagStack = StackCreate();
    char character;
    int line = 1;

    while((character = readChar(file, &line)) != EOF)
    {

        // Skip white spaces
        while(isWhiteSpace(character, &line)) character = readChar(file, &line);
        if(character == EOF) break;

        // If the character is not a '<' so Error
        if (character != '<') { printf("Error at line %d\n", line); exit(1); }

        //  Skip white spaces
        character = readChar(file, &line);
        while (isWhiteSpace(character, &line)) character = readChar(file, &line);

        if (!isLetter(character) && character != '/')
            { printf("Error at line %d\n", line); exit(1); }

        // If the character is'/' so is a closing tag
        if (character == '/') { handleClosingTag(file, &character, &line); continue; }

        // If the character is not a letter so Error
        if (!isLetter(character)) { printf("Error at line %d\n", line); exit(1); }

        // So is an opening tag
        handleOpeningTag(file, &character, &line);

    }

    if(!StackIsEmpty(TagStack)) { printf("Error at line %d\n", line); exit(1); }
}

int main(){
    FILE *file = fopen("../index.html", "r");
    if (file == NULL) { printf("Error opening file\n"); exit(1); }

    performLexicalAnalysis(file);
    return 0;
}
