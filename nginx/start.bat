@ECHO OFF
start c:\nginx\nginx.exe
start /b c:\nginx\php\php-cgi.exe -b 127.0.0.1:9000 -c c:\nginx\php\php.ini