# UE4Analytics

## 参考
* https://docs.unrealengine.com/latest/INT/Gameplay/Analytics/index.html
* https://www.unrealengine.com/blog/mobile-analytics-plugins-in-ue4

## エディタから
* Edit - Plugins - Analytics - 必要なものにチェックを入れる
    * FileLogging, AnalyticsMulticast 等

## DefaultEngine.ini
*  FileLogging を指定すると、Saved/Analytics/以下にログがJSON形式で出力される
~~~
[Analytics]
ProviderModuleName=FileLogging

//ProviderModuleName=AnalyticsMulticast
//ProviderModuleNames=FileLogging,MyAnalytics

//ApiKey=XXX
//ApiSecret=YYY
//SendInterval=60

[AnalyticsDevelopment]

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
