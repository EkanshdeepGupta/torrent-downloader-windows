#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <string.h>

using namespace std;

int main() {
    char programfiles[100];
    FILE *blah = popen("echo %PROGRAMFILES(x86)%", "r");
    fgets(programfiles, sizeof(programfiles), blah);
    for (int i=0; i<50; i++) {
        if (programfiles[i] ==  '\n') {
                programfiles[i] = '\0';
        };
    };

    cout << "PROGRAM FILES: " << programfiles << endl;

    strcat(programfiles, "\\Torrent Autodownloader\\torrentLocation.txt");

    cout << "LOC FILE: " << programfiles << endl;

    string path;
	ifstream pathstream;
	pathstream.open(programfiles);
	getline(pathstream, path);

	pathstream.close();

	if(path[0] == '\'' || path[0] == '"') {
		path.erase(0, 1);
	};

    if (path[path.length()-1] == ' ') {
        path.erase((path.length()-1), 1);
    };

	if(path[path.length()-1] == '\'' || path[path.length()-1] == '"') {
		path.erase((path.length()-1), 1);
	};

    if (path[path.length()-1] == ' ') {
        path.erase((path.length()-1), 1);
    };

	if(path[path.length()-1] == '/' || path[path.length()-1] == '\\') {
		path.erase((path.length()-1), 1);
	};

	if (path[path.length()-1] == ' ') {
        path.erase((path.length()-1), 1);
    };

	for (int i=0; i<path.length(); i++) {
        if(path[i] == '/') {
            path[i] = '\\';
        }
	}

    cout << "PATH: " << path << endl;


	ofstream pathoutstream(programfiles, ios::trunc);

	pathoutstream << path;

	pathoutstream.close();
}
