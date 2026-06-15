#include "Song.h"
using namespace std;
int idcounter = 100;

Song::Song(string n, string a) {
    Name = n;
    Artist = a;
    id = idcounter++;
}

Song::Song(string n, string a, int co) {
    Name = n;
    Artist = a;
    id = idcounter++;
    mostcount = co;
}

int Song::getid() {
    return id;
}

string Song::getartist() {
    return Artist;
}

string Song::getname() {
    return Name;
}

void Song::displaysong() {
    cout << "Name: " << Name << " ,Artist: " << Artist << " ,Id: " << id<<endl;
}