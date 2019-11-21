//
//  main.cpp
//  pageReplacement
//
//  This code will take 2 different approaches for page replacement,
//  namely FIFO and Second Chance, and then show how many page faults
//  are found to show which one is the better approach.
//
#include <unordered_set>
#include <queue>
#include <vector>
#include <iostream>

#define SIZE 10000

using namespace std;

// If found, update boolean
static bool findPage(int x,int table[], bool secondChance[],int frames);
  
// Updates the page in memory and returns the index
static int replacePage(int x,int table[], bool secondChance[],int frames,int index);

static int secondFaults(vector <int> reference, int frames);
  
// Function to find page faults using FIFO
int fifoFaults(vector<int>pages,int capacity);

// function to find page faults using LRU
int lruFaults(vector<int>pages, int capacity);
  
// Driver code
int main()
{
    vector<int> reference;
    for(int i = 0; i < 10000; i++){
        reference.push_back(rand() % 100);
    }
    int frames = 20;
    int fifofaults = fifoFaults(reference, frames); //output = 7962
    int secondfaults = secondFaults(reference, frames); //output = 14
    int lrufaults;
    printf("Page faults in FIFO: %d\n", fifofaults);
    printf("Page faults in Second Chance: %d\n", secondfaults);
    return 0;
}

static bool findPage(int x,int table[], bool secondChance[],int frames)
{
    for(int i = 0; i < frames; i++)
    {
          
        if(table[i] == x)
        {
            // Mark second chance
            secondChance[i] = true;
              
            // Do not need to replace
            return true;
        }
    }
      
    // Return 'false' so that a page for replacement is selected
    // as he reuested page doesn't exist in memory
    return false;
}

static int replacePage(int x,int table[], bool secondChance[],int frames,int index)
{
    while(true)
    {
          
        // We found the page to replace
        if(!secondChance[index])
        {
            // Replace with new page
            table[index] = x;
              
            // Return updated index
            return (index + 1) % frames;
        }
          
        // marked as false to be replaced
        secondChance[index] = false;
          
        //index in rs updated
        index = (index + 1) % frames;
    }
}

static int secondFaults(vector<int>reference, int frames)
{
    int index = 0, pagefaults = 0;
    
    //table to store pages
    int table[frames];
      
    // second chance table
    bool secondChance[frames];
      
    for(int i = 0; i < reference.size(); i++)
    {
        // Finds if there exists a need to replace
        // any page at all
        if(!findPage(reference[index],table,secondChance,frames))
        {
            // Selects and replaces page
            index = replacePage(reference[index],table,secondChance,frames,index);
              
            // Update page faults
            pagefaults++;
        }
    }
    return pagefaults;
}

int fifoFaults(vector<int>pages,int capacity)
{
    //unordered set to quickly check if the
    //page exists
    unordered_set<int> s;
  
    // FIFO storage
    queue<int> indexes;
  
    // Start from initial page
    int page_faults = 0;
    for (int i=0; i<pages.size(); i++)
    {
        // Check if the set can hold more pages
        if (s.size() < capacity)
        {
            // Insert if not already present
            if (s.find(pages[i])==s.end())
            {
                s.insert(pages[i]);
  
                // increment page fault
                page_faults++;
  
                // Push the current page into queue
                indexes.push(pages[i]);
            }
        }
  
        // If page is full
        else
        {
            // Check if current page present
            if (s.find(pages[i]) == s.end())
            {
                int val = indexes.front();
  
                indexes.pop();
  
                // Remove the indexes page
                s.erase(val);
  
                // insert the current page
                s.insert(pages[i]);
  
                // push the current page into
                // the queue
                indexes.push(pages[i]);
  
                // Increment page faults
                page_faults++;
            }
        }
    }
    return page_faults;
}

int lruFaults(vector<int>pages, int capacity)
{
    int pageFaults = 0, cnt = 0;
    //List current pages in use
    unordered_set<int> table;
    
    
    for(int i = 0; i < pages.size(); i++){
        //inseret if not present
        
    }
    
    
    return pageFaults;
}
