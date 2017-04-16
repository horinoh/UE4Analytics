#pragma once

#include "Interfaces/IAnalyticsProvider.h"

#include "Engine.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

DEFINE_LOG_CATEGORY_STATIC(LogMyAnalytics, Display, All);

class FMyAnalyticsProvider : public IAnalyticsProvider
{
public:

	virtual bool StartSession(const TArray<FAnalyticsEventAttribute>& Attributes) override { SessionID = UserID + TEXT("-") + FDateTime::Now().ToString(); return true; }
	virtual void EndSession() override {}
	virtual FString GetSessionID() const override { return SessionID; }
	virtual bool SetSessionID(const FString& InSessionID) override { SessionID = InSessionID; return true; }
	virtual void FlushEvents() override
	{
		//const auto HttpRequest = FHttpModule::Get().CreateRequest();
		//HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
		//HttpRequest->SetURL(TEXT("http://")); //!< #TODO
		//HttpRequest->SetVerb(TEXT("POST"));
		//HttpRequest->OnProcessRequestComplete().BindRaw(this, &FMyAnalyticsProvider::OnProcessRequestComplete);
		//HttpRequest->SetContentAsString(JsonContent);
		//HttpRequest->ProcessRequest();

		UE_LOG(LogMyAnalytics, Display, TEXT("%s"), *JsonContent);
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::White, *JsonContent);
		JsonContent.Empty();
	}
	virtual void SetUserID(const FString& InUserID) override { UserID = InUserID; }
	virtual FString GetUserID() const override { return UserID; }
	virtual void RecordEvent(const FString& EventName, const TArray<FAnalyticsEventAttribute>& Attributes) override
	{
		JsonContent += TEXT("\"eventName\" : \"") + EventName + TEXT("\"\n");
		if (Attributes.Num())
		{
			JsonContent += TEXT("\"attributes\" : [\n");
			for (auto i : Attributes)
			{
				JsonContent += TEXT("\t{ \"name\" : \"") + i.AttrName + TEXT("\", \"value\" : \"") + i.AttrValue + TEXT("\"\n");
			}
			JsonContent += TEXT("]\n");
		}
	}

	void OnProcessRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
	{
		if (bSucceeded && HttpResponse.IsValid())
		{
			HttpRequest->GetURL();
			HttpResponse->GetResponseCode();
			HttpResponse->GetContentAsString();
		}
	}

private:
	FString SessionID;
	FString UserID = FPlatformMisc::GetLoginId();
	FString JsonContent;
};