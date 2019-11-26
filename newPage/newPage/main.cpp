//Evan Jackson & William Jarboe
//November 24, 2019
//Mini project 4 & 5
//
//The goal of this project is to emulate the a page replacement algorithm. The program
//also uses no advance data structures, using only iostream and fstream in std. The
//program reads in an instruction of 0, 1, or 2, as well as an address in hex. The
//program will then systematically put the page into the Inverted Page Table,
//removing pages as needed.

#include <iostream>
#include <fstream>

#define SIZE 16
//if memory is 64K and each page is 4K, table is size 16
int IVT[SIZE][5] = {0};
//page number | frame number | valid bit | modified bit | reference bit
int faults = 0;
bool isFull = false;

using namespace std;

void updateTable(int command, int address, int age);
void fillTable(int address, int command, int age);
void doCommand(int address, int command, int age);
bool searchTable(int address);

int main(int argc, const char * argv[]) {
    int command, address, age = 0;
        
    ifstream infile;
    infile.open("spice.txt");

    
    while(!infile.eof()){
        infile >> command >> hex >> address;
        updateTable(command, address, age);
        age++;
    }
    
    for(int i = 0; i < SIZE; i++){
        printf("FRAME:%d\n\tADDRESS:%d\n\tFRAME NUMBER:%d\n", i, IVT[i][0], IVT[i][1]);
        printf("\tVALID BIT: %d\n\tMODIFIED BIT: %d\n\tREFERENCE BIT: %d\n\n",IVT[i][2],IVT[i][3],IVT[i][4]);
    }
    
    printf("FAULTS:%d\n", faults);
    return 0;
}

void updateTable(int command, int address, int age){
    if(!isFull)
        fillTable(address, command, age);
    else
        doCommand(address, command, age);
}

void fillTable(int address, int command, int age){
    static int iteration = 0; // know how many times this function has been used
    IVT[iteration][0] = address; // set page
    IVT[iteration][1] = age; // set frame
    IVT[iteration][2] = 1; // set valid bit to 1
    if(command == 1)
        IVT[iteration][3] = 1; // set modification to 1 if write
    IVT[iteration][4] = 1; // set reference bit to 1
    iteration++;
    faults++;
    if(iteration == SIZE)
        isFull = true;
}

void doCommand(int address, int command, int age){
    //2 cases. Either its there or it isnt
    bool present = false; // assume it isnt, and change when found
    for(int i = 0; i < SIZE; i++){
        if(IVT[i][0] == address){
            IVT[i][4] = 1;
            present = true;
            break;
        }
    }
    if(!present){
        int min = INT_MAX; //search for oldest value
        int minLocation = 0;
        for(int i = 0; i < SIZE; i++){
            //set reference back to 0, and find which one to replace
            if(IVT[i][1] < min && IVT[i][4] == 0){
                min = IVT[i][1];
                minLocation = i;
            }
            IVT[i][4] = 0;
        }
        //replace page and increment fault
        IVT[minLocation][0] = address;
        IVT[minLocation][1] = age;
        if(command == 1){
            IVT[minLocation][2] = 1; // set mod if write
        }
        IVT[minLocation][4] = 1;
        faults++;
    }
}
