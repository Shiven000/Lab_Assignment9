#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
    int     id;
    char    name;
    int     order; 
};

// Node for chained elements in the hash table
struct Node
{
    struct RecordType data;
    struct Node* next;
};

// HashType (Hash Table)
struct HashType
{
    struct Node* head;
};

// Compute the hash function
int hash(int x, int HashSize)
{
    return x % HashSize;
}

// insert a Record into the hash table
void insertRecord(struct HashType* Hash_Table, int HashSize, struct RecordType RecordOne)
{
    int index = hash(RecordOne.id, HashSize);

    // Create a new node for the Record
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed for a new node.\n");
        exit(-1);
    }
    newNode->data = RecordOne; newNode->next = NULL;

    // Insert the new node at the beginning of the chain
    if (Hash_Table[index].head == NULL) Hash_Table[index].head = newNode;
    else newNode->next = Hash_Table[index].head; Hash_Table[index].head = newNode;
    
}

// display all records at a given index of the hash table
void displayRecordsAtIndex(struct HashType* Hash_Table, int index)
{
    struct Node* current = Hash_Table[index].head;
    while (current != NULL)
    {
        printf("%d %c %d -> ", current->data.id, current->data.name, current->data.order);
        current = current->next;
    }
    printf("NULL\n");
}

// Function to display records in the hash structure
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType* Hash_Table, int HashSize)
{
    int i;

    for (i = 0; i < HashSize; ++i)
    {
        if (Hash_Table[i].head != NULL)
        {
            printf("index %d -> ", i);
            displayRecordsAtIndex(Hash_Table, i);
        }
    }
}

// Parses input file to an integer array
int parseData(char* inputFileName, struct HashType** ppHashTable, int HashSize)
{
    FILE* inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType RecordOne;

    *ppHashTable = (struct HashType*)malloc(sizeof(struct HashType) * HashSize);
    if (*ppHashTable == NULL)
    {
        printf("Cannot allocate memory for the hash table.\n");
        exit(-1);
    }

    // Initialize the hash table
    for (i = 0; i < HashSize; ++i)
    {
        (*ppHashTable)[i].head = NULL;
    }

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);

        for (i = 0; i < dataSz; ++i)
        {
            fscanf(inFile, "%d ", &n); RecordOne.id = n;
            fscanf(inFile, "%c ", &c); RecordOne.name = c;
            fscanf(inFile, "%d ", &n); RecordOne.order = n;

            insertRecord(*ppHashTable, HashSize, RecordOne);
        }

        fclose(inFile);
    }

    return dataSz;
}

// free the memory occupied by the hash table
void freeHashTable(struct HashType* Hash_Table, int HashSize)
{
    for (int i = 0; i < HashSize; ++i)
    {
        struct Node* current = Hash_Table[i].head;
        while (current != NULL)
        {
            struct Node* temp = current; current = current->next;
            free(temp);
        }
    }
    free(Hash_Table);
}

// print the records
void printRecords(struct HashType* Hash_Table, int HashSize)
{
    displayRecordsInHash(Hash_Table, HashSize);
}

int main(void)
{
    int HashSize = 10; // size of the hash table
    struct HashType* Hash_Table;
    int recordSz = 0;

    recordSz = parseData("input.txt", &Hash_Table, HashSize);
    printRecords(Hash_Table, HashSize);

    // free the memory allocated for the hash table
    freeHashTable(Hash_Table, HashSize);

    return 0;
}
