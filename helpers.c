/*
    Name: Karanvir Basson
    Title: Huffman Codes Algorithm
    Date: 05-11-2022
*/

#include "huffman.h"

//--HASH TABLE FUNCTIONS-------------------------------------------------

void initializeHashTable(Entry hashTable[INT8_MAX + 1]) { //Initialize each element in hash table

    for (int i = 0; i <= INT8_MAX; i++) { //For each Hashtable entry

        //Initialize key and values
        hashTable[i].character = i;
        hashTable[i].frequency = 0;
        strcpy(hashTable[i].code, "");

    }

}

void updateHashTableFrequency(Entry hashTable[INT8_MAX + 1], char current) { //Increment frequency value of char in hash table

    if (current < 0) return; //Char validity check

    //Update frequency
    int i = (int)(current);
    (hashTable[i].frequency)++;

}


void updateHashTableCodes(Entry hashTable[INT8_MAX + 1], Node* root, char str[MAX_CODE], int i, Direction direction) { //Update the huffman codes of each hash table entry using created Huffman tree

    if (root == NULL) { //Recursion Base Case

        return;

    } else { //Recursion Normal Case, uses preorder traversal

        if (direction != START) { //If not at root

            if (direction == LEFT) { //If traversed left

                str[i] = '0'; //Append zero to current traversal string

            } else { //If traversed right

                str[i] = '1'; //Append one to current traversal string

            }

            if (root -> character != -1) { //If valid character reached

                //Copy traversal string to corresponding hash table entry
                int index = (int)(root -> character);
                strcpy(hashTable[index].code, str);
                hashTable[index].code[i + 1] = '\0';

            }

        }

        //RECURSIVE CALLS TO TREE CHILDREN
        updateHashTableCodes(hashTable, root -> left, str, i + 1, LEFT);
        updateHashTableCodes(hashTable, root -> right, str, i + 1, RIGHT);

    }

}

void printHashTable(Entry hashTable[INT8_MAX + 1]) { //Print Hash table

    for (int i = 0; i <= INT8_MAX; i++) { //For each hash table entry

        //Print info
        printf("char %d = %c\nfrequency = %d\ncode = %s\n\n", i, hashTable[i].character, hashTable[i].frequency, hashTable[i].code);

    }

}

//-----------------------------------------------------------------------

//--HUFFMAN TREE FUNCTIONS-----------------------------------------------

Node* createNode(Entry* entry) { //Allocate and return an initialized node pointer

    Node* node = malloc(sizeof(Node)); //Allocate memory for Node
    if (node == NULL) return NULL; //NULL ptr check

    //Initialize Node
    node -> character = entry -> character;
    node -> frequency = entry -> frequency;

    node -> left = NULL;
    node -> right = NULL;

    return node;

}

void printNodes(Node* root) { //Given a tree, print it using recursion

    if (root == NULL) return; //NULL ptr check
        
    printf("\nNEW NODE\n\n"); //print that we have arrived to new node 

    //Print node character
    if (root -> character != -1) printf("Character %d: %c\n", root -> character, root -> character);
    else printf("Character %d: NONE\n", root -> character);

    printf("Frequency: %d\n", root -> frequency); //Print node

    //Print going to left
    if (root -> character != -1) printf("Going left on character %d, %c\n", root -> character, root -> character);
    else printf("Going left on character %d, frequency %d\n", root -> character, root -> frequency);

    printNodes(root -> left); 

    //Print going to right
    if (root -> character != -1) printf("Going right on character %d, %c\n", root -> character, root -> character);
    else printf("Going right on character %d, frequency %d\n", root -> character, root -> frequency);

    printNodes(root -> right);

}

void freeNodes(Node* root) { //Free Huffman tree

    if (root == NULL) { //Recursion base case

        return;

    } else { //Recursion normal case

        //Postorder traversal
        freeNodes(root -> left);
        freeNodes(root -> right);
        free(root); //Free current node

    }

}

//SORT NODE ARRAY USING MERGESORT, USED FOR CREATION OF HUFFMAN TREE

void mergeSort(Node* nodes[], int low, int high) { //Recursive calls for mergesort

    int mid = (low + high) / 2; //Get midpoint

    if (low < high) {

        //RECURSIVE CALLS TO BREAK ARRAY IN HALVES
        mergeSort(nodes, low, mid);
        mergeSort(nodes, mid + 1, high);

        //MERGE ARRAYS IN SORTED ORDER
        merge(nodes, low, mid, high);

    }

}

void merge(Node* nodes[], int low, int mid, int high) { //Merge 2 subarrays into larger sorted subarray

    Node* temp[high + 1]; //Temp array containing sorted items

    int i = low; //Index of subarray 1
    int j = mid + 1; //Index of subarray 2
    int k = low; //Index of temp

    while (i <= mid && j <= high) { //While neither subarray has been fully traversed

        //ADD LOWER ELEMENT TO TEMP ARRAY

        if (nodes[i] -> frequency <= nodes[j] -> frequency) {

            temp[k++] = nodes[i++];

        } else {

            temp[k++] = nodes[j++];

        }

    }

    if (i > mid) { //If subarray 1 fully traversed

        while (j <= high) { //Add remaining subarray 2 elements to temp array

            temp[k++] = nodes[j++];

        }

    } else { //If subarray 2 fully traversed

        while (i <= mid) { //Add remaining subarray 1 elements to temp array

            temp[k++] = nodes[i++];

        }

    }

    for (int a = low; a <= high; a++) { //Copy temp array to original array

        nodes[a] = temp[a];

    }

}

Node* createHuffmanTree(Node* nodes[], int* numNodes) { //Create Huffman tree from node array

    int copy = *numNodes; //Get original number of nodes

    for (int i = 0; i < (copy - 1); i++) { //For all nodes

        mergeSort(nodes, i, copy - 1); //Sort array

        //CREATE ENTRY FOR COMBINED NODE
        Entry entry;
        entry.character = -1;
        entry.frequency = (nodes[i] -> frequency) + (nodes[i + 1] -> frequency);
        
        //CREATE COMBINED NODE
        Node* new = createNode(&entry);
        new -> left = nodes[i];
        new -> right = nodes[i + 1];
        
        if (new == NULL) { //IF createNode() returns NULL
            
            for (int k = 0; k < (copy - 1); k++) {

                freeNodes(nodes[i]);

            }

            return NULL;

        }

        //REPLACE NODES IN ARRAY WITH COMBINED NODE
        nodes[i] = NULL;
        nodes[i + 1] = new;

        (*numNodes)++; //Update number of nodes

    }

    return nodes[copy - 1]; //Return root node

}

//-----------------------------------------------------------------------

//--USER INPUT FUNCTIONS-------------------------------------------------

char* decode(Node* root, char* userInput, int numChars) { //Given binary string, return corresponding char string

    Node* temp = root; //Traversal node ptr

    int k = 0;

    //Allocate traversal string, will be returned at end of function
    int size = numChars * sizeof(char) * MAX_CODE;
    char* currentStr = calloc(size, sizeof(char));
    if (currentStr == NULL) return NULL;

    int i = 0;

    while (i < strlen(userInput)) { //For all binary digits in string

        if (userInput[i] == '0') { //Go left if zero

            temp = temp -> left;


        } else if (userInput[i] == '1') { //Go right if one

            temp = temp -> right;

        } else { //Return if invalid

            printf("Invalid Input\n");
            free(currentStr);
            return NULL;

        }

        if (temp -> character != -1) { //If valid char reached

            currentStr[k++] = temp -> character; //Append char to end of traversal string
            temp = root; //Reset Traversal node ptr

        }

        i++;

    }

    return currentStr; //Return traversal string

}

char* encode(Entry hashTable[INT8_MAX + 1], char* userInput, int numChars) { //Given char string, return corresponding binary string

    //ALLOCATE STRING TO BE RETURNED
    int size = numChars * sizeof(char) * MAX_CODE;
    char* currentStr = calloc(size, sizeof(char));
    if (currentStr == NULL) return NULL;

    for (int i = 0; i < strlen(userInput); i++) { //For each char in char string

        strcat(currentStr, hashTable[(int)(userInput[i])].code); //Append corresponding Huffman code at back of result string

    }

    return currentStr; //Return resulting string

}

//-----------------------------------------------------------------------
