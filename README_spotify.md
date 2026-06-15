# Spotify-Inspired Music Player 🎵

A console-based MP3 music player built in C++ as a Data Structures course project. The system simulates core Spotify features using fundamental data structures including Doubly Linked Lists, Binary Search Trees, and Stacks.

---

## Features

- 🎵 **Song Library** — Display and manage all songs from file
- 📋 **Playlist Management** — Create, display, shuffle, and delete playlists
- ▶️ **Play Songs** — Play by ID or through a playlist
- 🔍 **Search** — Search songs with history tracking
- 🔀 **Shuffle** — Randomize playlist order
- 📜 **Play History** — Track recently played songs
- 💾 **File Persistence** — Songs, playlists, and history saved to files

---

## Data Structures Used

| Structure | Usage |
|---|---|
| Doubly Linked List | Playlist management and song navigation |
| Binary Search Tree (BST) | Song searching and sorting |
| Stack | Play history tracking |

---

## How to Run

```bash
g++ -o spotify "project data structure/project data structure.cpp" "project data structure/Allsongs.cpp" "project data structure/Playlist.cpp" "project data structure/DoubleLinkedList.cpp" "project data structure/BST.cpp" "project data structure/Song.cpp" "project data structure/DLLNode.cpp" "project data structure/Node.cpp" "project data structure/global.cpp"
```

---

## Menu Options

```
1 - Display Songs
2 - Playlists
3 - Search
4 - Search History
5 - Sort
6 - Play
7 - History
8 - Last Played in History
0 - Exit
```

---

## Project Structure

```
project data structure/
├── project data structure.cpp   ← Main entry point
├── Allsongs.h / Allsongs.cpp    ← Song library management
├── Playlist.h / Playlist.cpp    ← Playlist operations
├── DoubleLinkedList.h / .cpp    ← DLL implementation
├── BST.h / BST.cpp              ← Binary Search Tree
├── Song.h / Song.cpp            ← Song entity
├── DLLNode.h / DLLNode.cpp      ← DLL node
├── Node.h / Node.cpp            ← Generic node
└── global.h / global.cpp        ← Shared globals
```

---

## Built With

- C++
- Data Structures: Doubly Linked List, BST, Stack
- File I/O for persistence

---

*Developed as a group project — Year 1, Data Structures Course.*
