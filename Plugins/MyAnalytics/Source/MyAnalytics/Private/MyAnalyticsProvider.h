#pragma once

#include "Interfaces/IAnalyticsProvider.h"

#include "Engine.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "CondensedJsonPrintPolicy.h"

DEFINE_LOG_CATEGORY_STATIC(LogMyAnalytics, Display, All);

class FMyAnalyticsProvider : public IAnalyticsProvider
{
public:

	virtual bool StartSession(const TArray<FAnalyticsEventAttribute>& Attributes) override { SessionID = UserID + TEXT("-") + FDateTime::Now().ToString(); return true; }
	virtual void EndSession() override { if (Events.Num()) { FlushEvents(); } }
	virtual FString GetSessionID() const override { return SessionID; }
	virtual bool SetSessionID(const FString& InSessionID) override { SessionID = InSessionID; return true; }
	virtual void FlushEvents() override
	{
		Root->SetArrayField(TEXT("events"), Events);

		auto HttpRequest = FHttpModule::Get().CreateRequest();
		HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
		HttpRequest->SetURL(TEXT("http://localhost/index.php"));
		HttpRequest->SetVerb(TEXT("POST"));
		{
			FString String;
#if UE_BUILD_SHIPPING
			const auto Writer = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&String);
#else
			const auto Writer = TJsonWriterFactory<>::Create(&String);
#endif
			FJsonSerializer::Serialize(Root.ToSharedRef(), Writer);
			HttpRequest->SetContentAsString(String);

			UE_LOG(LogMyAnalytics, Display, TEXT("%s"), *String);
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::White, *String);
		}
		HttpRequest->OnProcessRequestComplete().BindRaw(this, &FMyAnalyticsProvider::OnProcessRequestComplete);
		HttpRequest->ProcessRequest();

		Events.Empty();
		Root.Reset();
		Root = MakeShareable(new FJsonObject());
	}
	virtual void SetUserID(const FString& InUserID) override { UserID = InUserID; }
	virtual FString GetUserID() const override { return UserID; }
	virtual void RecordEvent(const FString& EventName, const TArray<FAnalyticsEventAttribute>& Attributes) override
	{
		TSharedPtr<FJsonObject> Ev = MakeShareable(new FJsonObject());

		//!< イベント名
		Ev->SetStringField(TEXT("eventName"), EventName);
		//!< アトリビュート配列
		if (Attributes.Num())
		{
			TArray<TSharedPtr<FJsonValue>> Attrs;
			for (auto i : Attributes)
			{
				TSharedPtr<FJsonObject> At = MakeShareable(new FJsonObject());
				At->SetStringField(TEXT("name"), i.AttrName);
				At->SetStringField(TEXT("value"), i.AttrValueString);
				Attrs.Add(MakeShareable(new FJsonValueObject(At)));
			}
			Ev->SetArrayField(TEXT("attributes"), Attrs);
		}

		//!< イベントを配列に追加
		Events.Add(MakeShareable(new FJsonValueObject(Ev)));
	}

	void OnProcessRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
	{
		if (bSucceeded && HttpResponse.IsValid())
		{
			if (EHttpResponseCodes::Ok == HttpResponse->GetResponseCode())
			{
				if (HttpRequest->GetVerb() == TEXT("POST"))
				{
					const auto String = HttpResponse->GetContentAsString();

					UE_LOG(LogMyAnalytics, Display, TEXT("%s"), *String);
					GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, *String);
				}
			}
		}
	}

private:
	FString SessionID;
	FString UserID = FPlatformMisc::GetLoginId();

	TSharedPtr<FJsonObject> Root = MakeShareable(new FJsonObject());
	TArray<TSharedPtr<FJsonValue>> Events;
};