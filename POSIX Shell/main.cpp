//
//  main.cpp
//  POSIXSHELL
//
//  Created by Evan Jackson on 9/24/19.
//  Copyright © 2019 Evan Jackson. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <string>

using namespace std;

int main()
{
    cout << "hello\n";
    //open this CPP file
    char input;
    int index, fd;
    char byte;
    scanf("%c",&input);
    scanf("%d",&index);
    fd = open("main.cpp", O_RDONLY);
    
    while(input != '%' && input == 'P') {
        int child1 = fork();
        int child2 = fork();

        if(child1>0 && child2>0) { // is original parent
            
            int child4 = fork();
            if(child4==0) {
                //fourth child
                lseek(fd,index + 3,SEEK_SET);
                read(fd, &byte, 1);
                printf("%c", byte);
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
        //get input again, since this is the parent process
        scanf(" %c",&input);
        scanf(" %d",&index);
    }
    close(fd);
    return 0;
}
