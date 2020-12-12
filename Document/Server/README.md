# テスト用サーバ準備 (Prepare test server)

## Nginx
* https://nginx.org/en/download.html
* Stable を DL して解凍、ここでは c:\nginx へ配置することにした (Download Stable, and put to C:\nginx in this case)

### conf/nginx.conf を編集 (Edit conf/nginx.conf)
~~~
location / {
	root   html;
	#index  index.html index.htm;
	index  index.php index.html index.htm; # index.php を追加
}
# ↓コメントアウトされているのを有効にする (↓Enable disabled)
location ~ \.php$ {
	root           html;
	fastcgi_pass   127.0.0.1:9000;
	fastcgi_index  index.php;
	#fastcgi_param  SCRIPT_FILENAME  /scripts$fastcgi_script_name;
	fastcgi_param  SCRIPT_FILENAME  C:/nginx/html$fastcgi_script_name; # C:/nginx/html を指定
	include        fastcgi_params;
}
~~~

### start.bat を作成した (I created start.bat)
~~~
@pushd c:nginx
start nginx.exe
start /b php\php-cgi.exe -b 127.0.0.1:9000 -c php\php.ini
@popd
~~~

### stop.bat を作成した (I created stop.bat)
~~~
@pushd c:\nginx
nginx.exe -s quit
taskkill /f /IM nginx.exe
taskkill /f /IM php-cgi.exe
@popd
~~~

### html/index.php を作成 (I created html/index.php) 
~~~
<?php
$json = file_get_contents('php://input');
if(!empty($json)) {
    var_dump(json_decode($json, true));
    file_put_contents('UE4POST.json', $json, LOCK_EX);
}
else {
    $json = file_get_contents('UE4POST.json');
    if(!empty($json)) {
        var_dump(json_decode($json, true));
    }
}
phpinfo();
~~~

## PHP
* http://www.php.net/downloads.php
* DL して解凍、ここでは C:\nginx\php へ配置することにした (Download and put to C:\nginx\php in this case)
