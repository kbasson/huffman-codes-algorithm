/*
    Name: Karanvir Basson
    Title: Huffman Codes Algorithm
    Date: 05-11-2022
*/

//INCLUDE HEADER FILES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "newText.txt" //Name of file containing adjacency matrix
#define MAX_CODE 300 //Max length of the binary code of a char

typedef enum dir { //Enumerates the direction of travel when traversing tree, used to define Huffman encodings for each letter

    START,
    LEFT,
    RIGHT

} Direction;

typedef struct entry { //Represents an item in the has table

    char character; //Key

    int frequency; //Value 1
    char code[MAX_CODE]; //Value 2

} Entry;

typedef struct node { //Represents a node in Huffman tree

    //Data in each node
    char character;
    int frequency;

    //Pointer to children
    struct node* left;
    struct node* right;

} Node;

//--HASH TABLE FUNCTIONS-------------------------------------------------

void initializeHashTable(Entry hashTable[INT8_MAX + 1]); //Initialize each element in hash table
void updateHashTableFrequency(Entry hashTable[INT8_MAX + 1], char current); //Increment frequency value of char in hash table
void updateHashTableCodes(Entry hashTable[INT8_MAX + 1], Node* root, char str[MAX_CODE], int i, Direction direction); //Update the huffman codes of each hash table entry using created Huffman tree
void printHashTable(Entry hashTable[INT8_MAX + 1]); //Print Hash table

//-----------------------------------------------------------------------

//--HUFFMAN TREE FUNCTIONS-----------------------------------------------

Node* createNode(Entry* entry); //Allocate and return an initialized node pointer
void freeNodes(Node* root); //Free Huffman tree
void printNodes(Node* root); //Print Huffman tree

//SORT NODE ARRAY USING MERGESORT, USED FOR CREATION OF HUFFMAN TREE
void mergeSort(Node* nodes[], int low, int high); //Recursive calls for mergesort
void merge(Node* nodes[], int low, int mid, int high); //Merge 2 subarrays into larger sorted subarray

Node* createHuffmanTree(Node* nodes[], int* numNodes); //Create Huffman tree from node array

//-----------------------------------------------------------------------

//--USER INPUT FUNCTIONS-------------------------------------------------

char* decode(Node* root, char* userInput, int numChars); //Given binary string, return corresponding char string
char* encode(Entry hashTable[INT8_MAX + 1], char* userInput, int numChars); //Given char string, return corresponding binary string

//-----------------------------------------------------------------------
