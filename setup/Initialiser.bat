@echo off

set /p localpath="Enter Path where torrents are to be downloaded: "

mkdir "%PROGRAMFILES(x86)%\Torrent Autodownloader"
echo %localpath% >"%PROGRAMFILES(x86)%\Torrent Autodownloader\torrentLocation.txt"

copy "%~dp0curl.exe" "%PROGRAMFILES(x86)%\Torrent Autodownloader\curl.exe"
copy "%~dp0ca-bundle.crt" "%PROGRAMFILES(x86)%\Torrent Autodownloader\ca-bundle.crt"

"%~dp0pathFinder.exe"

set /p localpath2=<"%PROGRAMFILES(x86)%\Torrent Autodownloader\torrentLocation.txt"

echo New folder created in %localpath2%.

mkdir "%localpath2%"
mkdir "%localpath2%\Torrent Downloader"
mkdir "%localpath2%\Torrent Downloader\Torrent Files"
copy "%~dp0The List.txt" "%localpath2%\Torrent Downloader\The List.txt"

copy "%~dp0TorrentAutoDownloader.exe" "%APPDATA%\Microsoft\Windows\Start Menu\Programs\Startup\TorrentAutoDownloader.exe"
copy "%~dp0TorrentAutoDownloader.exe" "%PROGRAMFILES(x86)%\Torrent Autodownloader\torrent.exe"

setx path "%PROGRAMFILES(x86)%\Torrent Autodownloader;%path%"

pause