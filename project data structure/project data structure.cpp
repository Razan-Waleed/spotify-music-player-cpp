#include <iostream>
#include <string>
#include "Allsongs.h"
#include "Playlist.h"
#include "DoubleLinkedList.h"
#include "global.h"

using namespace std;

int main() {

    // Display welcome banner for the MP3 Music Player
    cout << R"(
################################################
#             MP3 Music Player                 #
################################################)" << endl;

    Allsongs songs;                               // Object that manages all songs in the library
    int choice;                                   // Variable to store user choice in main menu
    DoubleLinkedList<Playlist*> playlists;       // Doubly linked list to store all playlists

    // Load playlists from file when program starts
    loadFromPlaylistFile(&playlists, &songs);

    // Main program loop: keeps running until user exits
    while (true) {

        // Display main menu options
        cout << "1-Display Songs \n"
            << "2-PlayLists \n"
            << "3-Search \n"
            << "4-Search History\n"
            << "5-Sort\n"
            << "6-Play\n"
            << "7-History\n"
            << "8-last Played in History\n";
        cout << "0-Exit\n";
        cout << "enter your choice: " << endl;

        cin >> choice;
        cin.ignore();  // Clear the input buffer

        // Handle user selection using switch-case
        switch (choice) {

            // DISPLAY ALL SONGS
        case 1: {
            songs.displaysongs();                 // Show all songs in library
            char c;
            cout << "DO YOU WANT TO PLAY ANY SONG 'y,n'" << endl;
            cin >> c;

            if (c == 'y' || c == 'Y') {
                int id;
                cout << "enter id you want play" << endl;
                cin >> id;
                songs.playbyid(id);               // Play song by its ID
            }
            break;
        }

              // PLAYLIST MENU
        case 2: {
            int looping = 1;                      // Control loop for playlist menu

            // Playlist menu loop: allows multiple operations until user exits
            while (looping == 1) {
                cout << "1-Create Playlist\n"
                    << "2-Add song to Playlist\n"
                    << "3-Display Play list\n"
                    << "4-Display number of songs\n"
                    << "5-Delete \n"
                    << "6-shuffle\n"
                    << "7-play\n";
                cout << "enter your choice: " << endl;

                cin >> choice;
                cin.ignore();

                // Handle playlist menu choices
                switch (choice) {

                    // CREATE A NEW PLAYLIST
                case 1: {
                    string Name;
                    cout << "ENTER YOUR PLAYLIST NAME: " << endl;
                    getline(cin, Name);

                    Playlist* pl = new Playlist(&songs); // Create playlist object linked to all songs
                    pl->createplaylist(Name);            // Initialize playlist with given name
                    playlists.Add(pl);                   // Add playlist to the main playlist list

                    cout << "Playlist '" << Name << "' created!" << endl;

                    // Optionally add songs immediately after creating playlist
                    char addOpt;
                    cout << "Type 'a' to add songs now (or any key to skip): ";
                    cin >> addOpt;
                    cin.ignore();

                    if (addOpt == 'a' || addOpt == 'A') {
                        songs.displaysongs();           // Show all songs to choose from
                        int id;
                        while (true) {
                            cout << "Enter song ID to add (0 to exit): ";
                            cin >> id;
                            cin.ignore();
                            if (id == 0) break;       // Exit song adding loop
                            pl->addSong(id);           // Add selected song to playlist
                        }
                    }
                    tofile(&playlists);                 // Save playlists to file
                    break;
                }

                      // ADD SONGS TO EXISTING PLAYLIST
                case 2: {
                    if (playlists.size() == 0) {
                        cout << "No playlists available. Create one first." << endl;
                        break;
                    }

                    getplaylist(&playlists);           // Show list of playlists
                    cout << "Enter playlist number to add to: ";

                    int playlistchoice;
                    cin >> playlistchoice;
                    cin.ignore();

                    Playlist* pl = playlists.getByIndex(playlistchoice); // Get chosen playlist
                    if (!pl) {
                        cout << "Invalid choice." << endl;
                        break;
                    }

                    songs.displaysongs();               // Show all songs
                    int id;
                    while (true) {
                        cout << "Enter song ID to add (0 to exit): ";
                        cin >> id;
                        cin.ignore();
                        if (id == 0) break;
                        pl->addSong(id);                // Add selected song
                    }
                    tofile(&playlists);                 // Save changes
                    break;
                }

                      // DISPLAY PLAYLIST SONGS
                case 3: {
                    if (playlists.size() == 0) break;
                    getplaylist(&playlists);           // Show playlists

                    int playlistchoice;
                    cin >> playlistchoice;
                    cin.ignore();

                    Playlist* pl = playlists.getByIndex(playlistchoice);
                    if (pl) pl->DispalyEntirePlaylist(); // Display all songs in the selected playlist
                    break;
                }

                      // DISPLAY NUMBER OF SONGS IN PLAYLIST
                case 4: {
                    if (playlists.size() == 0) break;
                    getplaylist(&playlists);

                    int playlistchoice;
                    cout << "Enter playlist choice \n";
                    cin >> playlistchoice;
                    cin.ignore();

                    Playlist* pl = playlists.getByIndex(playlistchoice);
                    cout << "Number of songs in playlist "
                        << pl->getnameofplaylist()
                        << ": " << pl->getcount() << endl;
                    break;
                }

                      // DELETE PLAYLIST OR SONG FROM PLAYLIST
                case 5: {
                    cout << "1-Delete  playlist \n2-Delete song from playlist\n";
                    int choice;
                    cin >> choice;
                    cin.ignore();

                    // Delete entire playlist
                    if (choice == 1) {
                        if (playlists.size() == 0) {
                            cout << "No playlists to delete\n";
                            break;
                        }

                        getplaylist(&playlists);
                        int playlistchoice;
                        cout << "Enter playlist number to delete: ";
                        cin >> playlistchoice;
                        cin.ignore();

                        playlists.getByIndex(playlistchoice)->deletePlaylist(); // Delete playlist content
                        playlists.removeByIndex(playlistchoice);               // Remove playlist from list
                        tofile(&playlists);                                    // Save changes
                        break;
                    }

                    // Delete song from playlist
                    else if (choice == 2) {
                        getplaylist(&playlists);
                        int playlistchoice;
                        cin >> playlistchoice;
                        cin.ignore();

                        Playlist* pl = playlists.getByIndex(playlistchoice);
                        if (!pl) break;

                        pl->DispalyEntirePlaylist();           // Show songs in playlist
                        int id;
                        cout << "Enter id of song\n";
                        cin >> id;
                        cin.ignore();

                        pl->deleteSong(id);                     // Delete chosen song
                        tofile(&playlists);                     // Save changes
                        break;
                    }
                    break;
                }

                      // SHUFFLE PLAYLIST
                case 6: {
                    if (playlists.size() == 0) break;

                    getplaylist(&playlists);
                    int playlistchoice;
                    cout << "Enter play list to shuffle\n";
                    cin >> playlistchoice;
                    cin.ignore();

                    Playlist* pl = playlists.getByIndex(playlistchoice);
                    if (!pl) {
                        cout << "Play list Not Found" << endl;
                        break;
                    }
                    pl->shufflle();                           // Shuffle songs in playlist
                    break;
                }

                      // PLAY SONGS FROM PLAYLIST
                case 7: {
                    getplaylist(&playlists);
                    int id;
                    cout << "enter id of play list you want play " << endl;
                    cin >> id;
                    cin.ignore();

                    Playlist* pl = playlists.getByIndex(id);
                    if (!pl) {
                        cout << "Play list Not Found" << endl;
                        break;
                    }

                    int valid = pl->DispalyEntirePlaylist();  // Display songs before play
                    if (valid != 0) {
                        int idb;
                        cout << "enter id of Song you want play " << endl;
                        cin >> idb;
                        cin.ignore();
                        pl->playbyidplaylist(idb);           // Play chosen song
                    }
                    break;
                }

                      // EXIT PLAYLIST MENU
                default:
                    looping = 0;  // Exit playlist menu loop
                    break;
                }
            }
            break;
        }

              // SEARCH SONGS
        case 3: {
            cout << "Search by \n 1-Name\t 2-Artist : \t";
            int choice;
            cin >> choice;
            cin.ignore();

            // Search by song name
            if (choice == 1) {
                string inputName;
                cout << "Enter song name to search: ";
                getline(cin, inputName);

                inputName = strtolower(inputName);         // Convert input to lowercase for uniform search
                Song* s = songs.searchbyName(inputName);   // Search song by name

                if (s) {
                    s->displaysong();                      // Show song info
                    cout << "Do you want play it?'y,n'\n";
                    char c;
                    cin >> c;
                    cin.ignore();
                    if (c == 'y') songs.playbyid(s->getid());
                }
                else {
                    cout << "No songs found !\n";
                }
                break;
            }

            // Search by artist
            else if (choice == 2) {
                string inputArtist;
                cout << "Enter artist name to search: ";
                getline(cin, inputArtist);

                inputArtist = strtolower(inputArtist);     // Convert input to lowercase
                Song* s = songs.searchbyArtist(inputArtist);

                if (s) {
                    s->displaysong();
                    cout << "Do you want play it?'y,n'\n";
                    char c;
                    cin >> c;
                    cin.ignore();
                    if (c == 'y') songs.playbyid(s->getid());
                }
            }
        }

              // DISPLAY SEARCH HISTORY
        case 4:
            songs.DisplaySearchHistory();
            break;

            // SORT SONGS
        case 5: {
            cout << "Sort by \n 1-Most Played \t 2-Least Played \t 3-Recently played\n";
            int choice;
            cin >> choice;
            cin.ignore();

            if (choice == 1) songs.sortbymostplayed();          // Sort by most played
            else if (choice == 2) songs.sortbymostplayeddescending(); // Sort by least played
            else if (choice == 3) songs.sortrecentplayed();     // Sort by recent plays
            break;
        }

              // PLAY SONGS
        case 6: {
            cout << "1. Play from All Songs\n2. Play from a Playlist\n";
            int playChoice;
            cin >> playChoice;

            if (playChoice == 1) {
                songs.displaysongs();
                int id;
                cin >> id;
                songs.playbyid(id);                         // Play selected song from all songs
            }
            else if (playChoice == 2) {
                getplaylist(&playlists);
                int id;
                cin >> id;
                Playlist* pl = playlists.getByIndex(id);
                if (pl) {
                    pl->DispalyEntirePlaylist();
                    int songid;
                    cin >> songid;
                    pl->playbyidplaylist(songid);           // Play selected song from playlist
                }
            }
            break;
        }

              // DISPLAY PLAY HISTORY
        case 7:
            songs.displayHistory();
            break;

            // DISPLAY LAST PLAYED SONGS
        case 8:
            songs.displayLastPlayed();
            break;

            // EXIT PROGRAM
        default:
            return 0;
        }
    }
}
