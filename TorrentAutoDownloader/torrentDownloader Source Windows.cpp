#define _WIN32_WINNT 0x0500

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <cstring>
#include <ctime>
#include <windows.h>

using namespace std;

void showFound(istream &katcr);
void pathFinder();
string curl();

ofstream log("C:\\Log\\torrentDownloaderLog.txt", std::ios::app);
string path;

int main(){
    ShowWindow( GetConsoleWindow(), SW_MINIMIZE );

    time_t currentTime;
    struct tm *localTime;

    time( &currentTime );
    localTime = localtime( &currentTime );

    int Day    = localTime->tm_mday;
    int Month  = localTime->tm_mon + 1;
    int Year   = localTime->tm_year + 1900;
    int Hour   = localTime->tm_hour;
    int Min    = localTime->tm_min;
    int Sec    = localTime->tm_sec;

    pathFinder();

    log << "-----RUN AT " << Day << "/" << Month << "/" << Year << " " << Hour << ":" << Min << ":" << Sec << "-----" << endl << endl;

    string fetchSiteCommand = "\"" + curl() + "-k --compressed https://kat.cr/tv/ -o \"" + path + "\\Torrent Downloader\\katcr.txt\"" + "\"";
    cout << fetchSiteCommand << endl;
    system(fetchSiteCommand.c_str());

    ifstream theList((path + "\\Torrent Downloader\\The List.txt").c_str());
    string nameOfShow;

    while (getline(theList, nameOfShow)) {
        if (nameOfShow == "" || nameOfShow[0] == ' ') {
            continue;
        };

        while (nameOfShow[nameOfShow.length() - 1] == ' ') {
            nameOfShow = nameOfShow.substr(0, nameOfShow.length()-1);
        };

        string tempLine;
        ifstream katcr((path + "\\Torrent Downloader\\katcr.txt").c_str());

        int count1 = 0;

        while (getline(katcr, tempLine)) {
            count1++;
            int posNameOfShow = tempLine.find(nameOfShow);
            if (posNameOfShow != -1) {
                if (tempLine.find("720p") == -1) {
                    cout << nameOfShow << "----" << "LINE NUMBER-----" << count1 << endl;
                    showFound(katcr);
                    break;
                };
            };
        };

        katcr.close();
    };

    theList.close();

    log << endl << endl;
    log.close();
};

void showFound(istream &katcr) {
	ifstream historyIn((path + "\\Torrent Downloader\\history.txt").c_str());
    string tempLine;
    getline(katcr, tempLine);
    getline(katcr, tempLine);

    int posOfSite1 = tempLine.find("href=\"");
    int posOfSite2 = tempLine.find(".torrent?", posOfSite1+6);
    int posOfName = tempLine.find("[kat.cr]");
    int posOfName2 = tempLine.find("\"", posOfName+ 10);
    string nameOfTorrent = tempLine.substr(posOfName+8, posOfName2-posOfName-8);

    log << "Name Of Torrent: " << nameOfTorrent << endl;

    string addOfSubpage = "https:" + tempLine.substr(posOfSite1+6, posOfSite2-posOfSite1+2);

    log << "Address of torrent page: " << addOfSubpage << endl;

    string command = "\"" + curl() + "-k --compressed -o \"" + path + "\\Torrent Downloader\\Torrent Files\\" + nameOfTorrent + ".torrent\" -A \"Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/48.0.2564.109 Safari/537.36\" \"" + addOfSubpage + "\"" + "\"";


    string notifyCommand = "\" mshta javascript:alert(\"Started Download of " + nameOfTorrent + "\");close() \"";

    bool downloadedBefore = false;
    string tempHistoryIn;

	while (getline(historyIn, tempHistoryIn)) {
		if (tempHistoryIn == nameOfTorrent) {downloadedBefore = true;};
	};

	historyIn.close();


	if (!(downloadedBefore)) {
		log << "Command run: " << command << endl;
		log << "Status: Downloaded." << endl << endl;

		ofstream historyOut((path + "\\Torrent Downloader\\history.txt").c_str(), std::ios::app);
		historyOut << nameOfTorrent << endl;
		historyOut.close();

    	system((notifyCommand).c_str());

    	system((command).c_str());
	}

	else {
		log << "Command NOT run: " << command << endl;
		log << "Status: Aborted." << endl << endl;
	};
};

void pathFinder() {
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

	ifstream pathstream;
	pathstream.open(programfiles);
	getline(pathstream, path);

	pathstream.close();

	cout << "PATH: " << path << endl;
};

string curl() {
    return " \"%PROGRAMFILES(x86)%\\Torrent Autodownloader\\curl\" ";
};
