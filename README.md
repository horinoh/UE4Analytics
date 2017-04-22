# UE4Analytics

## 参考
* https://docs.unrealengine.com/latest/INT/Gameplay/Analytics/index.html
* https://www.unrealengine.com/blog/mobile-analytics-plugins-in-ue4

## エディタから
* Edit - Plugins - Analytics - 必要なものにチェックを入れる
    * FileLogging とか AnalyticsMulticast とか

## DefaultEngine.ini
* FileLogging を指定すると、Saved/Analytics/以下にログがJSON形式で出力される
* AnalyticsMulticast を指定する場合は ProviderModuleNames は [AnalyticsDevelopment] セクションに書かないとダメみたい
~~~
[Analytics]
ProviderModuleName=FileLogging
//ProviderModuleName=AnalyticsMulticast

[AnalyticsDevelopment]
//ProviderModuleNames=FileLogging,MyAnalytics

[AnalyticsTest]
~~~

## UE4Analytics.Build.cs
~~~
PublicDependencyModuleNames.AddRange(new string[] { ..., "Analytics" });
~~~

# プラグインの追加
* Edit - Plugin - New plugin - Blank - "MyAnalytics" として - Create plugin

## MyAnalytics.Build.cs
~~~
PrivateDependencyModuleNames.AddRange(
    new string[]
    {
        "CoreUObject",
        "Engine",
        "Slate",
        "SlateCore",
        // ... add private dependencies that you statically link with here ...	
        "Analytics",
        "Http",
        "Json",
    }
    );
~~~

## IMoudleInterface を継承しているのを IAnalyticsProviderModule を継承するように変更
* MyAnalytics.cpp, h を実装する

## MyAnalyticsProvider.h を追加
* MyAnalyticsProvider.h を実装する
    * AnalyticsSwrve.cpp あたりを参考にする

# テスト用サーバ準備

## Nginx
* https://nginx.org/en/download.html
* Stable を DL して解凍、ここでは c:\nginx へ配置することにした

### conf/nginx.con を編集
~~~
location / {
	root   html;
	#index  index.html index.htm;
	index  index.php index.html index.htm; # index.php を追加
}
# ↓コメントアウトされているのを有効にする
location ~ \.php$ {
	root           html;
	fastcgi_pass   127.0.0.1:9000;
	fastcgi_index  index.php;
	#fastcgi_param  SCRIPT_FILENAME  /scripts$fastcgi_script_name;
	fastcgi_param  SCRIPT_FILENAME  C:/nginx/html$fastcgi_script_name; # C:/nginx/html を指定
	include        fastcgi_params;
}
~~~

### start.bat を作成
~~~
@ECHO OFF
start c:\nginx\nginx.exe
start /b c:\nginx\php\php-cgi.exe -b 127.0.0.1:9000 -c c:\nginx\php\php.ini
~~~

### stop.bat を作成
~~~
@ECHO OFF
c:\nginx\nginx.exe -s quit
taskkill /f /IM nginx.exe
taskkill /f /IM php-cgi.exe
~~~

### html/index.php を作成
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
* DL して解凍、ここでは C\nginx\php へ配置することにした

## テスト
* nginx/start.bat を起動して http://localhost へアクセスしてなんか表示されれば成功