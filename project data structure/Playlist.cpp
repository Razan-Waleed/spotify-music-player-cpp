#include "Playlist.h"
#include <fstream>
#include <iostream>


// Save playlist to file
void Playlist::tofile(ofstream& file) {
    file << "-" << Nameplaylist << endl;           // Write playlist name with marker
    DLLNode<Song*>* t = head->gethead();           // Get head of playlist
    if (!t) return;

    // Write all song IDs in the playlist
    do {
        file << t->getData()->getid() << endl;
        t = t->getNext();
    } while (t != head->gethead());
}

// Return number of songs in playlist
int Playlist::getcount() {
    return countofsongs;
}

// Print all songs in playlist
void Playlist::printlist() {
    cout << "Playlist: " << Nameplaylist << endl;
    DLLNode<Song*>* t = head->gethead();

    if (!t) {
        cout << "Empty playlist\n";
        return;
    }

    // Traverse circular list and display songs
    do {
        t->getData()->displaysong();
        t = t->getNext();
    } while (t != head->gethead());
}

// Create a new playlist
void Playlist::createplaylist(string name) {
    Nameplaylist = name;                           // Set playlist name
    head = new DoubleLinkedList<Song*>();          // Playlist songs list
    shuffleplaying = new DoubleLinkedList<Song*>();// List for shuffled songs
    songsBST = new BST();                          // BST used for shuffle
    countofsongs = 0;
    PlaylistId++;
}

// Return playlist name
string Playlist::getnameofplaylist() {
    return Nameplaylist;
}

// Add song to playlist
void Playlist::addSong(int songId, int silent) {
    Song* s = song->getSongbyid(songId);           // Get song from Allsongs

    if (!s && silent == 0) {
        cout << "Song with ID " << songId << " not found!" << endl;
        return;
    }

    DLLNode<Song*>* temp = head->gethead();

    // Check if song already exists in playlist
    if (temp) {
        while (true) {
            if (songId == temp->getData()->getid()) {
                cout << "Song Already exist in playlist \n";
                return;
            }
            temp = temp->getNext();
            if (head->gethead() == temp) break;
        }
    }

    head->Add(s);                                  // Add song to playlist
    countofsongs++;

    if (silent == 0) {
        cout << "#" << s->getname() << " - by "
            << s->getartist()
            << " is added to playlist : "
            << Nameplaylist << endl;
    }
}

// Constructor with Allsongs pointer
Playlist::Playlist(Allsongs* s) {
    song = s;
}

// Default constructor
Playlist::Playlist() {
    songsBST = NULL;
}

// Insert playlist songs into BST for shuffle
int Playlist::BSTshuffle() {
    if (!head || !head->gethead()) {
        cout << "NO SONGS TO SHUFFLE" << endl;
        return 0;
    }

    if (songsBST) {
        songsBST->clear();
    }
    else {
        songsBST = new BST();
    }

    DLLNode<Song*>* temp = head->gethead();

    // Insert all playlist songs into BST
    do {
        songsBST->insert(temp->getData());
        temp = temp->getNext();
    } while (temp != head->gethead());

    return 1;
}

// Preorder traversal for shuffle
void Playlist::preorder(Node* songs) {
    if (!songs) return;
    songs->getSong()->displaysong();
    shuffleplaying->Add(songs->getSong());
    preorder(songs->getLeft());
    preorder(songs->getRight());
}

// Postorder traversal for shuffle
void Playlist::postorder(Node* songs) {
    if (!songs) return;
    postorder(songs->getLeft());
    postorder(songs->getRight());
    songs->getSong()->displaysong();
    shuffleplaying->Add(songs->getSong());
}

// Inorder traversal for shuffle
void Playlist::inorder(Node* songs) {
    if (!songs) return;
    inorder(songs->getLeft());
    songs->getSong()->displaysong();
    shuffleplaying->Add(songs->getSong());
    inorder(songs->getRight());
}

// Shuffle playlist using BST traversal
void Playlist::shufflle() {
    int valid = BSTshuffle();
    if (valid == 0) return;

    shuffleplaying->clear();
    srand(time(0));

    int countofshuffle = rand() % 3;
    if (countofshuffle > 2) countofshuffle = 0;

    if (countofshuffle == 0) {
        cout << "preorder: " << endl;
        preorder(songsBST->getRoot());
    }
    else if (countofshuffle == 1) {
        cout << "postorder: " << endl;
        postorder(songsBST->getRoot());
    }
    else {
        cout << "inorder: " << endl;
        inorder(songsBST->getRoot());
    }

    char c;
    cout << "Play shuffled songs? (y/n): ";
    cin >> c;

    if (c == 'y' || c == 'Y') {
        song->play(shuffleplaying->gethead());
    }
}

// Display BST nodes (preorder)
void Playlist::Dispaly(Node* t) {
    if (!t) return;
    t->getSong()->displaysong();
    Dispaly(t->getLeft());
    Dispaly(t->getRight());
}

// Display entire playlist
int Playlist::DispalyEntirePlaylist() {
    if (!head || !head->gethead()) {
        cout << "no songs" << endl;
        return 0;
    }

    cout << "Name of playlist is: " << Nameplaylist << endl;
    DLLNode<Song*>* temp = head->gethead();

    while (true) {
        temp->getData()->displaysong();
        temp = temp->getNext();
        if (temp == head->gethead()) break;
    }
    return 1;
}

// Play a song from playlist by ID
void Playlist::playbyidplaylist(int id) {
    Song* temp = song->getSongbyid(id);
    if (!temp) return;

    DLLNode<Song*>* node = head->gethead();
    if (!node) return;

    while (true) {
        if (node->getData() == temp) {
            song->play(node);
            return;
        }
        node = node->getNext();
        if (node == head->gethead()) break;
    }

    cout << "Song not found in playlist." << endl;
}

// Display total number of songs
void Playlist::DisplayTotalnum() {
    cout << countofsongs;
}

// Delete a song from playlist
void Playlist::deleteSong(int songID) {
    DLLNode<Song*>* current = head->gethead();

    // Search for song
    while (current != nullptr && current->getData()->getid() != songID) {
        current = current->getNext();
        if (current == head->gethead()) break;
    }

    if (current == nullptr || current->getData()->getid() != songID) {
        cout << "Song doesn't exist" << endl;
        return;
    }

    // Handle deletion cases
    if (current == head->gethead() && current == head->gettail()) {
        head->setHead(nullptr);
        head->setTail(head->gethead());
    }
    else if (current == head->gethead()) {
        head->setHead(current->getNext());
        head->gettail()->setNext(current->getNext());
        head->gethead()->setPrev(head->gettail());
    }
    else if (current == head->gettail()) {
        head->setTail(current->getPrev());
        head->gettail()->setNext(head->gethead());
    }
    else {
        current->getPrev()->setNext(current->getNext());
        current->getNext()->setPrev(current->getPrev());
    }

    delete current;
    cout << "Song deleted successfully" << endl;
    countofsongs--;
}

// Delete entire playlist
void Playlist::deletePlaylist() {
    DLLNode<Song*>* current = head->gethead();

    while (current != nullptr) {
        DLLNode<Song*>* next = current->getNext();
        delete current;
        if (next == head->gethead()) break;
        current = next;
    }

    head->setHead(nullptr);
    head->setTail(nullptr);
    cout << "Playlist deleted successfully\n";
}

// Save all playlists to file
void tofile(DoubleLinkedList<Playlist*>* p) {
    ofstream file("playlist.txt");
    int size = p->size();

    if (size == 0) {
        cout << " no playlists here " << endl;
        return;
    }

    for (int i = 0; i < size; i++) {
        p->getByIndex(i)->tofile(file);
    }

    file.close();
}

// Load playlists from file
void loadFromPlaylistFile(DoubleLinkedList<Playlist*>* p, Allsongs* songs) {
    ifstream file("playlist.txt");
    if (!file) {
        cout << "playlist.txt not found" << endl;
        return;
    }

    string line;
    Playlist* currplaylist = NULL;

    while (getline(file, line)) {
        if (!line.empty() && line[0] == '-') {
            string Name = line.substr(1);
            Playlist* pl = new Playlist(songs);
            pl->createplaylist(Name);
            p->Add(pl);
            currplaylist = pl;
        }
        else {
            if (currplaylist != NULL) {
                int number = stoi(line);
                currplaylist->addSong(number, 1);
            }
        }
    }
    file.close();
}

// Display playlists and return status
int getplaylist(DoubleLinkedList<Playlist*>* p) {
    int size = p->size();

    if (size == 0) {
        cout << " no playlists here " << endl;
        return 0;
    }

    for (int i = 0; i < size; i++) {
        cout << i << "- "
            << p->getByIndex(i)->getnameofplaylist()
            << endl;
    }
    return 1;
}
