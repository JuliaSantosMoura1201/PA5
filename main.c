/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int nodes[10];
int nodeAmount = 0;
int numbersToPrint[10];
int numbersToPrintAmount = 0;

int findSmallerNodePosition(char *line, int smallerNode){
    int smallerNodePosition;
    for(int i = 0; i < strlen(line); i++){
        if(line[i] - '0' ==  smallerNode){
            smallerNodePosition = i;
        }
    }
    return smallerNodePosition;
}

char *removeSmallerNode(char *line, int smallerNode){
    int smallerNodePosition = findSmallerNodePosition(line, smallerNode);
    char *str = malloc(strlen(line));
    char *str2 = malloc(strlen(line));

    strncpy(str, line, smallerNodePosition - 2);
    strncpy(str2, line + (smallerNodePosition+2), strlen(line));
    strcat(str, str2);

    return str;
}

int findSmallerNodeEdge(char *line, int smallerNode){
    
    int pos = findSmallerNodePosition(line, smallerNode);
    while(pos > 0){
        if(line[pos] == '(')
            break;
        pos--;
    }
    
    if(line[pos-2] != ')'){
        numbersToPrint[numbersToPrintAmount] = line[pos-2];
        numbersToPrintAmount++;
    }else{
        pos = pos-2;
        int parentesisToClose = 0;
        while(pos > 0){
            if(line[pos] == '(')
                parentesisToClose--;
            else if(line[pos] == ')')
                parentesisToClose++;
            else{
                if(parentesisToClose == 0 && line[pos] != ' ')
                    break;
            }
            pos --;
        }
        numbersToPrint[numbersToPrintAmount] = line[pos];
        numbersToPrintAmount++;
    }
}

int findSmallerNode(int p_nodes[]){
    int smallerNode = p_nodes[0];
    
    for(int i = 0; i < nodeAmount; i++){
        if(p_nodes[i] < smallerNode){
            smallerNode = nodes[i];
        }
    }
    
    return smallerNode;
}

void findNode(char *line, int position){
    int previousPosition = position-1;
    int fowardPosition = position+1;
    
    if(fowardPosition <= (strlen(line)-1) && previousPosition >= 0){
        if(line[previousPosition] == '(' && line[fowardPosition] == ')'){
            nodes[nodeAmount] = line[position] - '0';
            nodeAmount++;
        }
    }
}

void walksThroughTree(char *line){
    for(int i = 0; i < strlen(line); i++){
       findNode(line, i);
    }
}

int getNumbersAmount(char *line){
    int numbersAmount =0;
    for(int i = 0; i < strlen(line); i++){
        int previousPosition = i-1;
        int fowardPosition = i+1;
        
        if(fowardPosition <= (strlen(line)-1) && previousPosition >= 0){
            if(line[previousPosition] == '('){
                numbersAmount++;
            }
        }
    }
    return numbersAmount;
}

int main()
{   
    char entrada[100] = "(6 (1 (4)) (2 (3) (5)))";
    numbersToPrint[0] = -1;
    scanf("%[^\n]", entrada);
    char *newline = entrada;
    int numbersAmount = getNumbersAmount(newline);
    for(int i = 0; i<numbersAmount - 2; i++){
        nodeAmount = 0;
        walksThroughTree(newline);
        int smallerNode = findSmallerNode(nodes);
        findSmallerNodeEdge(newline, smallerNode);
        printf("%c ", numbersToPrint[numbersToPrintAmount -1 ]);
        newline = removeSmallerNode(newline, smallerNode);
    }
    
    printf("%d\n", numbersAmount);
    return 0;
}


