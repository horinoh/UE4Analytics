@ECHO OFF
c:\nginx\nginx.exe -s quit
taskkill /f /IM nginx.exe
taskkill /f /IM php-cgi.exe