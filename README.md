# UE4Analytics

## 参考 (Cf.)
* https://docs.unrealengine.com/latest/INT/Gameplay/Analytics/index.html
* https://www.unrealengine.com/blog/mobile-analytics-plugins-in-ue4

## エディタから (In Editor)
* Edit - Plugins - Analytics - 必要なものにチェックを入れる (Add check as necessary)
    * FileLogging とか AnalyticsMulticast とか (For example FileLogging, AnalyticsMulticast..)

## DefaultEngine.ini
* FileLogging を指定すると、Saved/Analytics/以下にログがJSON形式で出力される (If FileLogging is specified, log will outout to Saved/Analytics/ in JSON format)
~~~
[Analytics]
ProviderModuleName=AnalyticsMulticast
ProviderModuleNames=MyAnalytics

[AnalyticsDevelopment]
ProviderModuleName=AnalyticsMulticast
ProviderModuleNames=FileLogging,MyAnalytics

[AnalyticsTest]
ProviderModuleName=AnalyticsMulticast
ProviderModuleNames=FileLogging,MyAnalytics

[AnalyticsDebug]
ProviderModuleName=AnalyticsMulticast
ProviderModuleNames=FileLogging,MyAnalytics
~~~

## UE4Analytics.Build.cs
~~~
PublicDependencyModuleNames.AddRange(new string[] { ..., "Analytics" });
~~~

## プラグインの追加 (Add plugin)
* Edit - Plugin - New plugin - Blank - "MyAnalytics" - Create plugin

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

## IMoudleInterface を継承しているのを IAnalyticsProviderModule を継承するように変更 (Modify inheriting IMoudleInterface to IAnalyticsProviderModule)
* MyAnalytics.cpp.h を実装する (Implement MyAnalytics.cpp.h)

## MyAnalyticsProvider.h を追加 (Add MyAnalyticsProvider.h)
* MyAnalyticsProvider.h を実装する (Implement MyAnalyticsProvider.h)
    * AnalyticsSwrve.cpp あたりを参考にする (Cf. AnalyticsSwrve.cpp)

## [テスト用サーバ準備 (Prepare test server)](https://github.com/horinoh/UE4Analytics/tree/master/Document/Server)

## テスト (Test)
* start.bat を起動して、UE4Analytics を実行 (Invoke start.bat and execute UE4Analytics)
	* http://localhost へアクセスしてなんか表示されれば成功 (Access to http://localhost, and if something is displayed it's OK)