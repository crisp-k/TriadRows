#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAXCHAR 15


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
