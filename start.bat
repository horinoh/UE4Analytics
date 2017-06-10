@pushd c:nginx
start nginx.exe
start /b php\php-cgi.exe -b 127.0.0.1:9000 -c php\php.ini
@popd