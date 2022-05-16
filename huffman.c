/*
    Name: Karanvir Basson
    Title: Huffman Codes Algorithm
    Date: 05-11-2022
*/

#include "huffman.h"

int main() {

    //Define and initialize hash table
    Entry hashTable[INT8_MAX + 1];
    initializeHashTable(hashTable);

    FILE* file = fopen(FILENAME, "r"); //Open file for reading
    
    if (file == NULL) { //If file not found

        printf("File not found!\n");
        return -1;

    }

    int numChars = 0; //Hold number of chars

    while (!feof(file)) { //For all chars in file

        //Update frequency of char
        char current = fgetc(file);
        updateHashTableFrequency(hashTable, current);

        numChars++; //Increment num chars

    }

    fclose(file); //Close file

    int numNodes = 0; //Holds number of nodes to be created

    for (int i = 0; i <= INT8_MAX; i++) { //Get number of nodes to be created

        if (hashTable[i].frequency != 0) {
            
            numNodes++;

        }

    }

    int k = 0;
    Node* nodes[numNodes]; //Array of nodes

    for (int i = 0; i <= INT8_MAX; i++) { //Create all nodes in array

        if (hashTable[i].frequency != 0) {
            
            nodes[k] = createNode(&hashTable[i]);

            if (nodes[k] == NULL) { //If createNode() returns NULL
                
                for (int a = 0; a < k; a++) {

                    free(nodes[a]);

                }

                return -1;

            }

            k++;

        }

    }

    //Use node array to create Huffman Tree
    Node* root = createHuffmanTree(nodes, &numNodes);
    if (root == NULL) return -1;

    //DEFINE AND INITIALIZE TRAVERSAL STRING FOR updateHashTableCodes()
    char str[MAX_CODE];

    for (int i = 0; i < MAX_CODE; i++) {

        str[i] = '\0';

    }

    updateHashTableCodes(hashTable, root, str, -1, START);
    
    //printHashTable(hashTable);
    //printNodes(root); //Print Huffman Tree

    int size = numChars * sizeof(char) * MAX_CODE;
    char userInput[size]; //Holds user input

    while (1) { //Run main program

        //Prompt user entry
        printf("\nEnter 1 to convert user string to encoded binary\n");
        printf("Enter 2 to decode user binary string\n");
        printf("Enter 3 to write encoded text file to a new file\n");
        printf("Enter \"exit\" to quit!\n\n");

        printf("Enter choice here: ");
        scanf("%s", userInput);

        if (!strcmp(userInput, "exit")) { //If user exits
            
            printf("\nExiting Program!\n\n");
            break;

        } else if (!strcmp(userInput, "1")) { //If user wants to convert user string to encoded binary

            //Get user char string
            printf("Enter user string (enter \"-1\" to exit): ");
            scanf("%s", userInput);

            if (!strcmp(userInput, "-1")) { //If userInput == -1, exit program
                
                printf("\nExiting Program!\n\n");
                break;

            }

            char* result = encode(hashTable, userInput, numChars); //Encode char string and return result
            
            if (result != NULL) {

                printf("result = %s\n", result); //print result
                free(result);

            }

        } else if (!strcmp(userInput, "2")) { //If user wants to decode user binary string

            //Get user binary string
            printf("Enter Huffman code (enter \"exit\" to exit): ");
            scanf("%s", userInput);

            if (!strcmp(userInput, "exit")) { //If userInput == "exit", exit program
                
                printf("\nExiting Program!\n\n");
                break;

            }

            char* result = decode(root, userInput, numChars); //Encode binary string and return result

            if (result != NULL) {

                printf("result = %s\n", result); //print result
                free(result);

            }

        } else if (!strcmp(userInput, "3")) { //If user wants to write encoded text file to a new file

            //Prompt user for filename
            printf("Enter Filename (enter \"-1\" to exit): ");
            scanf("%s", userInput);

            if (!strcmp(userInput, "-1")) { //If userInput == -1, exit program
                
                printf("\nExiting Program!\n\n");
                break;

            }

            FILE* file = fopen(FILENAME, "r"); //Open original text file for reading
            FILE* write = fopen(userInput, "w"); //Open new text file for writing

            if (file == NULL || write == NULL) { //If either file ptr is NULL

                printf("File not found!\n");
                return -1;

            }    

            while (!feof(file)) { //For all original text file chars

                char current = fgetc(file);
                fprintf(write, "%s", hashTable[(int)(current)].code); //Write corresponding Huffman code to new file

            }

            //CLOSE FILES
            fclose(file); 
            fclose(write); 

            printf("\nWrite successful!\n");           
        
        } else { //If user input is invalid

            printf("\nInvalid input!\n");

        }

    }
    
    freeNodes(root); //Free Huffman Tree
    return 1;

}
