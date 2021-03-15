#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAXCHAR 15

typedef struct chordNode{
    char root[MAXCHAR];
    char quality[MAXCHAR];
    int chordNum;
} chordNode;

typedef struct chordTree{
    struct chordNode *chord;
    struct chordTree *left;
    struct chordTree *right;
} chordTree;

chordNode *initializeChordNode(char *root, char *quality, int num)
{
    chordNode *newChordNode = (chordNode*) malloc(sizeof(chordNode));
    
    newChordNode->chordNum = num;
    strcpy(newChordNode->root, root);
    strcpy(newChordNode->quality, quality);

    return newChordNode;
}

chordTree *initializeChordTreeNode(chordNode *node)
{
    chordTree *newTreeNode = (chordTree*) malloc(sizeof(chordTree));

    newTreeNode->chord = node; 
    newTreeNode->left = NULL;
    newTreeNode->right = NULL;

    return newTreeNode;
}

int isEven(int num)
{
    if(num % 2 == 0)
        return 1;
    else
        return 0;
}

int *initializeOrder(int numChords)
{
    int *newOrder = calloc(numChords, sizeof(int));

    return newOrder;
}

void resetToInOrder(int *order, int numChords)
{
    for(int i = 0; i < numChords; i++)
        order[i] = i;
}

void shuffle(int *array, int size)
{
    srand(time(NULL));
    for(int j = 0; j < 10; j++)
        for(int i = 0; i < size - 1; i++)
        {
            int j = i + rand() / (RAND_MAX / (size - i) + 1);
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
}

int readNumChords(FILE *infile)
{
    int numChords;

    fscanf(infile, "%d", &numChords);

    return numChords;
}

char **readRoots(FILE *infile, int *numRoots)
{
    char **roots;

    fscanf(infile, "%d", numRoots);

    roots = (char **) malloc(*numRoots * sizeof(char*));

    for(int i = 0; i < *numRoots; i++)
    {
        roots[i] = (char *) malloc(MAXCHAR * sizeof(char));
        fscanf(infile, "%s", roots[i]);
    }
    printf("\n");

    return roots;
}

char **readQualities(FILE *infile, int *numQualities)
{
    char **qualities;

    fscanf(infile, "%d", numQualities);
    
    qualities = (char **) malloc(*numQualities * sizeof(char *));

    for(int i = 0; i < *numQualities; i++)
    {
        qualities[i] = (char *) malloc(MAXCHAR * sizeof(char));
        fscanf(infile, "%s", qualities[i]);
    }
    printf("\n");

    return qualities;
}

chordTree *insertToTree(chordTree *root, chordTree *node)
{
    if(root == NULL)
        root = node;
    else
    {
        if(root->chord->chordNum > node->chord->chordNum)
        {
            if(root->right == NULL)
                root->right = node;
            else
                root->right = insertToTree(root->right, node);
        }
        else
        {
            if(root->left == NULL)
                root->left = node;
            else 
                root->left = insertToTree(root->left, node);
        }
    }

    return root;
}

int balanceCheck(chordTree *root)
{
    
}

chordTree *rebalanceWrapper(chordTree *root)
{
    int balanceRequired = balanceCheck(root);
    
    if(balanceRequired)
        return rebalance(root);
    
    return root;
}

chordTree *insertWrapper(chordTree *root, chordTree *node)
{
    root = insertToTree(root, node);
    root = rebalanceWrapper(root);
}

char **createChords(int numRoots, int numQualities, int numChords, char **roots, char **qualities)
{
    char **chords;
    char tempChordName[MAXCHAR];
    int i;

    chords = (char **) malloc(numChords * sizeof(char *));

    for(i = 0; i < numChords; i++)
    {
        chords[i] = (char *) malloc(MAXCHAR * sizeof(char));
    }

    i = 0;
    for(int j = 0; j < numRoots; j++)
        for(int k = 0; k < numQualities; k++)
        {
            strcpy(tempChordName, roots[j]);
            strncat(tempChordName, qualities[k], strlen(qualities[k]));
            strcpy(chords[i], tempChordName);
            i++;
        }

    return chords;
}



void displayRow(int numChords, int *order, char **chords)
{
    for(int i = 0; i < numChords; i++)
        {
            if(isEven(numChords))
            {
                if(i % 12 == 0 && i > 1)
                    printf("\n");
            }
            else
            {
                if(i % 9 == 0 && i > 1)
                    printf("\n");
            }

            printf("\t%s ", chords[order[i]]);
        }
        printf("\n");
}

void displayShuffledRow(int numChords, int *order, char **chords, int numRows)
{
    for(int i = 0; i < numRows; i++)
    {
        shuffle(order, numChords);

        printf("Row #%i\n", i);
        displayRow(numChords, order, chords);
    }
}

int main(void)
{
    FILE *infile = fopen("triads.txt", "r");
    int *order;
    int numRoots, numQualities, numChords;
    char **roots, **qualities, **chords;
    chordTree *chordTree;

    numChords = readNumChords(infile);

    printf("Num chords: %i\n", numChords);
    
    roots = readRoots(infile, &numRoots);
    qualities = readQualities(infile, &numQualities);
    chords = createChords(numRoots, numQualities, numChords, roots, qualities);

    order = initializeOrder(numChords);
    resetToInOrder(order, numChords);

    printf("In order:\n");
    displayRow(numChords, order, chords);

    shuffle(order, numChords);

    displayShuffledRow(numChords, order, chords, 3);
    
}