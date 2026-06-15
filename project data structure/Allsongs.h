#ifndef ALLSONGS_HPP
#define ALLSONGS_HPP

#include "DoubleLinkedList.h"
#include "BST.h"
#include "Song.h"
#include <queue>
#include <stack>
#include <string>

class Allsongs {

    DoubleLinkedList<Song*>* Headofsongs = nullptr;
    DoubleLinkedList<Song*>* Headrecentlyplayed = nullptr;
    int recent_counter = 1;
    DLLNode<Song*>* mergeTwoLists(DLLNode<Song*>* a,
        DLLNode<Song*>* b,
        bool descending = true,
        bool useRecent = false);

    // Recursive merge sort - returns sorted head
    DLLNode<Song*>* mergeSortDLL(DLLNode<Song*>* head,
        bool descending = true,
        bool useRecent = false);
    int count = 0;
    void savetofile();
    void loadfromfile();

public:
    
   
    BST* BSTl = NULL;
    stack<string> SearchHistory;

    Allsongs();
    ~Allsongs();

   
    int getcount();
    Song* getSongbyid(int id);
    void displaysongs();
    void sortbymostplayed();
    void sortbymostplayeddescending();
   
    void sortrecentplayed();
    void playbyid(int id);
    void play(DLLNode<Song*>* played);
    void DisplaySearchHistory();
    Song* searchbyName(string name);
    Song* searchbyArtist(string artist);
    void addToHistoryUnique(int songId);
    void displayHistory();
    void displayLastPlayed();
    void loadSearchHistory();
    void saveSearchHistory();
};

#endif#pragma once
