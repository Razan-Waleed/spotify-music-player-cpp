#ifndef PLAYLIST_HPP
#define PLAYLIST_HPP

#include "Allsongs.h"
#include "DoubleLinkedList.h"
#include "BST.h"
using namespace std;

class Playlist {
private:
    string Nameplaylist;
    BST* songsBST = NULL;
    int countofsongs = 0;
    Allsongs* song;
    DoubleLinkedList<Song*>* head = NULL;
    DoubleLinkedList<Song*>* shuffleplaying = NULL;
    int BSTshuffle();
    void preorder(Node* songs);
    void postorder(Node* songs);
    void inorder(Node* songs);
    int PlaylistId = 0;
    void Dispaly(Node* t);

public:
    Playlist(Allsongs* s);
    Playlist();

    void tofile(ofstream& file);
    int getcount();
    void printlist();
    void createplaylist(string name);
    string getnameofplaylist();
    void addSong(int songId, int silent = 0);
    
    void shufflle();
    int DispalyEntirePlaylist();
    void playbyidplaylist(int id);
    void DisplayTotalnum();
    void deleteSong(int songID);
    void deletePlaylist();
};

void tofile(DoubleLinkedList<Playlist*>* p);
void loadFromPlaylistFile(DoubleLinkedList<Playlist*>* p, Allsongs* songs);
int getplaylist(DoubleLinkedList<Playlist*>* p);

#endif
