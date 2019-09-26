//Evan Jackson
//Posix Shell Mini Project 1
//September 26, 2019
//
//The goal of the project is to read bytes from the current working project
//using fork, and then kill the subsequent children without destorying the
//parent function.

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;

int main()
{
    //Cout hello to show program is ready to run
    cout << "hello\n";
    //open this CPP file
    char input;
    int index, fd;
    char byte;
    scanf("%c",&input);
    scanf("%d",&index);
    fd = open("main.cpp", O_RDONLY);
    
    while(input != '%' && input == 'P') {
        // create child 1
        int child1 = fork();
        // create child 2 and 3
        int child2 = fork();

        if(child1>0 && child2>0) { //parent
            
            //create child 4
            int child4 = fork();
            if(child4==0) {
                lseek(fd,index + 3,SEEK_SET);
                read(fd, &byte, 1);
                printf("%c", byte);
                //return kills child
                return 0;
            }
            //get more input. look to end of else/if group.
            
        }
        else if(child1 == 0&& child2 > 0) {
            //first child
            lseek(fd,index,SEEK_SET);
            read(fd, &byte, 1);
            printf("%c", byte);
            return 0;
        }
        else if(child1 > 0 && child2 == 0) {
            //second child
            lseek(fd,index + 1,SEEK_SET);
            read(fd, &byte, 1);
            printf("%c", byte);
            return 0;
        }
        else {
            //third child
            lseek(fd,index + 2,SEEK_SET);
            read(fd, &byte, 1);
            printf("%c", byte);
            return 0;
            
        }
        cout << endl;
        //check for ending process
        //must use _%c to account for current line
        scanf(" %c",&input);
        scanf(" %d",&index);
    }
    close(fd);
    return 0;
}
