#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

int main()
{
    char process;
    int position;
    cin >> process >> position;
    while (process != '%'){
        if (fork() == 0)
            cout << "Hello from child!\n";
        else
            cout << "Hello from parent!\n";
    }
}