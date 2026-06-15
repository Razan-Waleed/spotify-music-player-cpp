#ifndef SONG_HPP
#define SONG_HPP

#include <string>
#include <iostream>
using namespace std;
class Song {
private:
    string Name;
    string Artist;
    int id;

public:
    int mostcount = 0;
    int recentlyplayed = 0;
    int flag = 0;

    Song() {};
    Song(string n, string a);
    Song(string n, string a, int co);

    int getid();
    string getartist();
    string getname();
    void displaysong();
};

#endif#pragma once
