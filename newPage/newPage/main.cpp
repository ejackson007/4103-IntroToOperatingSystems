//
//  main.cpp
//  newPage
//
//  Created by Evan Jackson on 11/20/19.
//  Copyright © 2019 Evan Jackson. All rights reserved.
//

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
    //int t = 456;
    //cout << hex << t << endl;
        
    ifstream infile;
    infile.open("spice.txt");
    
    while(!infile.eof()){
        //for(int i = 0; i < SIZE + 3; i++){
        infile >> command >> hex >> address;
        //cout << "address is " << address << endl;
        updateTable(command, address, age);
        age++;
    }
    
    //    for(int i = 0; i < SIZE; i++)
    //        cout << IVT[i][0] << endl;
    //
    for(int i = 0; i < SIZE; i++){
        printf("INDEX: %d\n\tADDRESS:%d\n\tAGE:%d\n\n", i, IVT[i][0], IVT[i][1]);
    }
    printf("FAULTS:%d", faults);
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
            IVT[i][4] = 0;
            if(IVT[i][1] < min){
                min = IVT[i][1];
                minLocation = i;
            }
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
