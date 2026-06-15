#include <iostream>
#include <string>
#include <fstream>
#include "Allsongs.h"
#include "Song.h"               
#include "DoubleLinkedList.h"   
#include "global.h"            

using namespace std;
// Constructor: initializes data structures and loads data from files
Allsongs::Allsongs() {
    BSTl = new BST();
    Headofsongs = new DoubleLinkedList<Song*>();
    Headrecentlyplayed = new DoubleLinkedList<Song*>();
    loadfromfile();
    loadSearchHistory();
}
// Save all songs to file

void Allsongs::savetofile() {
    if (!Headofsongs || !Headofsongs->gethead()) return;
    ofstream file("musics.txt");
    DLLNode<Song*>* temp = Headofsongs->gethead();
    // Traverse circular list and write each song
    while (true) {
        file << temp->getData()->getid() << "," << temp->getData()->getname() << "," << temp->getData()->getartist();
        file << "," << temp->getData()->mostcount << "," << temp->getData()->recentlyplayed << endl;
        temp = temp->getNext();
        if (temp == Headofsongs->gethead()) break;
    }
}
// Load songs from file
void Allsongs::loadfromfile() {
    ifstream file("musics.txt");
    if (!file) {
        cout << "musics not found" << endl;
        return;
    }
    int mostrecent = 0;
    string line;
    while (getline(file, line)) {
        string id, name, artist, mostcount, recent;
        int i = 0;
        while (i < line.length() && line[i] != ',') id += line[i++];
        i++;
        while (i < line.length() && line[i] != ',') name += line[i++];
        i++;
        while (i < line.length() && line[i] != ',') artist += line[i++];
        i++;
        while (i < line.length() && line[i] != ',') mostcount += line[i++];
        i++;
        while (i < line.length()) recent += line[i++];
        Song* s = new Song(name, artist);
        count++;
        s->mostcount = stoi(mostcount);
        int songrecent = stoi(recent);
        s->recentlyplayed = songrecent;
        if (songrecent > mostrecent) {
            mostrecent = songrecent;
        }
        Headofsongs->Add(s);
    }
    recent_counter = mostrecent + 1;// Ensure next play is most recent
    file.close();
}
// Return number of songs
int Allsongs::getcount() {
    return count;
}
// Destructor: free allocated memory
Allsongs::~Allsongs() {
    if (Headofsongs) {
        Headofsongs->clear();
        delete Headofsongs;
    }
    if (Headrecentlyplayed) {
        Headrecentlyplayed->clear();
        delete Headrecentlyplayed;
    }
    if (BSTl) {
        BSTl->clear();
        delete BSTl;
    }
}
// Find song by ID
Song* Allsongs::getSongbyid(int id) {
    if (!Headofsongs) {
        cout << "No available songs" << endl;
        return NULL;
    }
    DLLNode<Song*>* temp = Headofsongs->gethead();
    while (true) {
        if (temp->getData()->getid() == id) {
            return temp->getData();
        }
        temp = temp->getNext();
        if (temp == Headofsongs->gethead()) break;
    }
    return NULL;
}
// Display all songs
void Allsongs::displaysongs() {
    if (!Headofsongs || !Headofsongs->gethead()) return;
    DLLNode<Song*>* temp = Headofsongs->gethead();
    while (true) {
        temp->getData()->displaysong();
        temp = temp->getNext();
        if (temp == Headofsongs->gethead()) break;
    }
}
// Merge two sorted lists
DLLNode<Song*>* Allsongs::mergeTwoLists(DLLNode<Song*>* a,
    DLLNode<Song*>* b,
    bool descending,
    bool useRecent) {
    if (!a) return b;// If first list empty
    if (!b) return a; // If second list empty

    DLLNode<Song*>* result;
    int val1, val2;

    if (useRecent) {
        val1 = a->getData()->recentlyplayed;
        val2 = b->getData()->recentlyplayed;
    }
    else {
        val1 = a->getData()->mostcount;
        val2 = b->getData()->mostcount;
    }

    if (descending) {
        if (val1 >= val2)
            result = a;
        else
            result = b;
    }
    else {
        if (val1 <= val2)
            result = a;
        else
            result = b;
    }

    DLLNode<Song*>* temp1;
    DLLNode<Song*>* temp2;

    if (result == a)
        temp1 = a->getNext();
    else
        temp1 = a;

    if (result == b)
        temp2 = b->getNext();
    else
        temp2 = b;

    result->setNext(mergeTwoLists(temp1, temp2, descending, useRecent));
    if (result->getNext()) {
        result->getNext()->setPrev(result);
    }
    result->setPrev(nullptr);
    return result;
}

// Merge sort the list
DLLNode<Song*>* Allsongs::mergeSortDLL(DLLNode<Song*>* head,
    bool descending,
    bool userecent) {
    if (!head || !head->getNext()) return head;

    
    DLLNode<Song*>* slow = head;
    DLLNode<Song*>* fast = head->getNext();
    while (fast && fast->getNext()) {
        slow = slow->getNext();
        fast = fast->getNext()->getNext();
    }

    DLLNode<Song*>* right = slow->getNext();
    slow->setNext(nullptr);
    if (right) right->setPrev(nullptr);

    DLLNode<Song*>* leftSorted = mergeSortDLL(head, descending, userecent);
    DLLNode<Song*>* rightSorted = mergeSortDLL(right, descending, userecent);

    return mergeTwoLists(leftSorted, rightSorted, descending, userecent);
}


void Allsongs:: sortbymostplayed() {  // Most played → Least played
    if (!Headofsongs || !Headofsongs->gethead()) {
        cout << "No songs available." << endl;
        return;
    }

    
    DLLNode<Song*>* tail = Headofsongs->gettail();
    DLLNode<Song*>* head = Headofsongs->gethead();
    tail->setNext(nullptr);
    head->setPrev(nullptr);
    head = mergeSortDLL(head, true, false);

    cout << "\nSongs sorted by Most Played \n" << endl;
    DLLNode<Song*>* temp = head;
    int count = 0;
    while (temp) {
        Song* s = temp->getData();
        if (s->mostcount > 0) {
            cout << ++count << ". ";
            s->displaysong();
        }
        temp = temp->getNext();
    }
    if (count == 0) cout << "NO songs was played" << endl;

    if (head) {
        temp = head;
        while (temp->getNext()) temp = temp->getNext();
        temp->setNext(head);
        head->setPrev(temp);
        Headofsongs->setHead(head);
        Headofsongs->setTail(temp);
    }
}

void Allsongs:: sortbymostplayeddescending() {  // Least → Most played
    if (!Headofsongs || !Headofsongs->gethead()) {
        cout << "No songs available." << endl;
        return;
    }

    DLLNode<Song*>* tail = Headofsongs->gettail();
    DLLNode<Song*>* head = Headofsongs->gethead();
    tail->setNext(nullptr);
    head->setPrev(nullptr);

    head = mergeSortDLL(head, false, false);  // ascending

    cout << "\n Songs sorted by Least Played\n" << endl;
    DLLNode<Song*>* temp = head;
    int count = 0;
    while (temp) {
        Song* s = temp->getData();
        if (s->mostcount > 0) {
            cout << ++count << ". ";
            s->displaysong();
        }
        temp = temp->getNext();
    }
    if (count == 0) cout << "NO songs was played" << endl;

    if (head) {
        temp = head;
        while (temp->getNext()) temp = temp->getNext();
        temp->setNext(head);
        head->setPrev(temp);
        Headofsongs->setHead(head);
        Headofsongs->setTail(temp);
    }
}

void Allsongs:: sortrecentplayed() {  
    if (!Headofsongs || !Headofsongs->gethead()) {
        cout << "No songs available." << endl;
        return;
    }

    DLLNode<Song*>* tail = Headofsongs->gettail();
    DLLNode<Song*>* head = Headofsongs->gethead();
    tail->setNext(nullptr);
    head->setPrev(nullptr);

    head = mergeSortDLL(head, true, true);  

    cout << "\n Recently Played Songs (Most recent first)\n" << endl;
    DLLNode<Song*>* temp = head;
    int count = 0;
    while (temp) {
        Song* s = temp->getData();
        if (s->recentlyplayed > 0) {
            cout << ++count << ". ";
            s->displaysong();
        }
        temp = temp->getNext();
    }
    if (count == 0) cout << "NO songs was played" << endl;

    if (head) {
        temp = head;
        while (temp->getNext()) temp = temp->getNext();
        temp->setNext(head);
        head->setPrev(temp);
        Headofsongs->setHead(head);
        Headofsongs->setTail(temp);
    }
}


void Allsongs::playbyid(int id) { //play song by id
    Song* temp = getSongbyid(id);
    if (!temp) return;
    DLLNode<Song*>* node = Headofsongs->gethead();
    if (!node) return;
    while (true) {
        if (node->getData() == temp) {
            play(node);
            return;
        }
        node = node->getNext();
        if (node == Headofsongs->gethead()) break;
    }
    cout << "Song not found in playlist." << endl;
}

void Allsongs::play(DLLNode<Song*>* played) {
    addToHistoryUnique(played->getData()->getid());// Save song to history file
    played->getData()->recentlyplayed = recent_counter; // Update recent counter
    recent_counter += 1;
    played->getData()->mostcount += 1;// Increase play count
    savetofile();
    cout << "Now playing " << played->getData()->getname() << endl;
    cout << "DO YOU WANT PLAY NEXT OR PREV or Replay 'N,P,r .0 to exit " << endl;
    char choice;
    cin.ignore();
    cout << "Enter your choice \n";
    cin >> choice;
    if (choice == 'n' || choice == 'N') {
        play(played->getNext());// Play next song
    }
    else if ((choice == 'p' || choice == 'P')) {
        play(played->getPrev());  // Play previous song
    }
    else if ((choice == 'r' || choice == 'R')) {
        play(played); // Replay current song
    }
    else {
        return;
    }
}

void Allsongs::DisplaySearchHistory() {
    stack<string> ToDisplay = SearchHistory;// Copy stack for display
    if (SearchHistory.empty() == true) {
        cout << "your Search History is Empty." << endl; // Check if history is empty
        return;
    }
    while (!ToDisplay.empty()) {
        cout << ToDisplay.top() << endl;
        ToDisplay.pop();
    }
}
void Allsongs::saveSearchHistory() {
    ofstream file("search_history.txt");
    if (!file) return;
    // Write stack content to file
    stack<string> temp = SearchHistory;
    while (!temp.empty()) {
        file << temp.top() << endl; 
        temp.pop();
    }
}
void Allsongs::loadSearchHistory() {
    ifstream file("search_history.txt");
    if (!file) return;

    stack<string> tempStack;
    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            tempStack.push(line);
        }
    }
    file.close();
    // Restore original order into SearchHistory
    
    while (!tempStack.empty()) {
        SearchHistory.push(tempStack.top());
        tempStack.pop();
    }
}

Song* Allsongs::searchbyName(string name) {
    BST tree;
    DLLNode<Song*>* temp = Headofsongs->gethead();
    int matchCount = 0;
    SearchHistory.push(name);
    saveSearchHistory();
    while (true) {
        string songName = strtolower(temp->getData()->getname());
        bool match = true;
        for (int k = 0; k < name.length(); k++) {
            if (k >= songName.length() || songName[k] != name[k]) {
                match = false;
                break;
            }
        }
        if (match) {
            tree.insert(temp->getData());// Insert match into BST
            matchCount++;
        }
        temp = temp->getNext();
        if (temp == Headofsongs->gethead()) break;
    }
    if (matchCount == 0) return NULL;
    if (matchCount == 1) return tree.getRoot()->getSong();
    cout << "Found matches:" << endl;
    int index = 0;
    tree.Display(tree.getRoot(), index);
    int choice;
    cout << "Which song do you mean? 0 to EXIT ";
    cin >> choice;
    cin.ignore();
    if (choice == 0) {
        return NULL;
    }
    else  if (choice > 0 && choice <= matchCount) {
        int current = 0;
        return tree.getByIndex(tree.getRoot(), choice, current);
    }
    return NULL;
}

Song* Allsongs::searchbyArtist(string artist) {
    BST tree;
    DLLNode<Song*>* temp = Headofsongs->gethead();
    int matchCount = 0;
    SearchHistory.push(artist);
    saveSearchHistory();

    while (true) {
        string songArtist = strtolower(temp->getData()->getartist());
        bool match = true;
        for (int k = 0; k < artist.length(); k++) {
            if (k >= songArtist.length() || songArtist[k] != artist[k]) {
                match = false;
                break;
            }
        }
        if (match) {
            tree.insert(temp->getData());
            matchCount++;
        }
        temp = temp->getNext();
        if (temp == Headofsongs->gethead()) break;
    }

    if (matchCount == 0) {
        cout << "No songs found for artist: " << artist << endl;
        return NULL;
    }
    if (matchCount == 1) {
        return tree.getRoot()->getSong();  
    }

    
    cout << "Found " << matchCount << " matches for artist '" << artist << "':\n" << endl;
    int index = 0;
    tree.Display(tree.getRoot(), index);

    int choice;
    cout << "\nWhich song do you mean? (Enter number, 0 to EXIT): ";
    cin >> choice;
    cin.ignore();

    if (choice == 0) {
        return NULL;
    }
    else if (choice > 0 && choice <= matchCount) {
        int current = 0;
        return tree.getByIndex(tree.getRoot(), choice, current);
    }
    else {
        cout << "Invalid choice." << endl;
        return NULL;
    }
}
void Allsongs::addToHistoryUnique(int songId) {
    ifstream inFile("history.txt");  // Open history file
    vector<int> tempIds;
    string line;
    if (inFile) {
        // Read all IDs except current one
        while (getline(inFile, line)) {
            if (!line.empty()) {
                int id = stoi(line);
                if (id != songId) tempIds.push_back(id);
            }
        }
        inFile.close();
    }
    ofstream outFile("history.txt");
    for (int id : tempIds) {
        outFile << id << endl;
    }
    outFile << songId << endl;// Add latest song at end
    outFile.close();
}

void Allsongs::displayHistory() {
    ifstream historyFile("history.txt");
    if (!historyFile) {
        cout << "History is empty." << endl;
        return;
    }
    stack<int> reverseOrder;
    string idStr;
    while (getline(historyFile, idStr)) {
        if (!idStr.empty()) {
            reverseOrder.push(stoi(idStr));
        }
    }
    historyFile.close();
    cout << "\n--- Your Playback History (Most Recent First) ---" << endl;
    if (reverseOrder.empty()) {
        cout << "No history found." << endl;
    }
    while (!reverseOrder.empty()) {
        int id = reverseOrder.top();
        reverseOrder.pop();
        Song* s = getSongbyid(id);
        if (s) {
            s->displaysong();
        }
    }
    cout << "------------------------------------------------\n" << endl;
}

void Allsongs::displayLastPlayed() {
    ifstream historyFile("history.txt");
    if (!historyFile) {
        cout << "No history found." << endl;
        return;
    }
    string line, lastId;
    while (getline(historyFile, line)) {
        if (!line.empty()) {
            lastId = line;
        }
    }
    historyFile.close();
    if (lastId.empty()) {
        cout << "History is empty." << endl;
    }
    else {
        int id = stoi(lastId);
        Song* s = getSongbyid(id);
        if (s) {
            cout << "\n>>> LAST PLAYED SONG <<<" << endl;
            s->displaysong();
            cout << "------------------------\n" << endl;
        }
    }
}