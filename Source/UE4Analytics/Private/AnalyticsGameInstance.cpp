// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Analytics.h"
#include "AnalyticsGameInstance.h"

#include "Analytics.h"
#include "IAnalyticsProvider.h"
//#include "AnalyticsEventAttribute.h"

void UAnalyticsGameInstance::Init()
{
	Super::Init();

	const auto Provider = FAnalytics::Get().GetDefaultConfiguredProvider();
	if (Provider.IsValid())
	{
		Provider->StartSession();

		//!< イベントを記録 ... 武器店が開いた
		Provider->RecordEvent(TEXT("WeaponStoreOpened"));
		//!< 単属性付イベントを記録 ... 剣(Sword23)を装備した
		Provider->RecordEvent(TEXT("ItemEquipped"), { TEXT("ItemID"), TEXT("Sword23") });
		//!< 複数属性付イベントを記録 ... 鉄製で炎属性の剣(Sword100)をクラフトした
		Provider->RecordEvent(TEXT("ItemCrafted"), {
			{ TEXT("ItemID"), TEXT("Sword100") },
			{ TEXT("MetalUsed"), TEXT("Steel") },
			{ TEXT("DamageModifierType"), TEXT("Fire") },
		});
		//!< ゲーム内通貨で購入を記録 ... 10ジェムの剣(Sword23)を1つ購入した 
		Provider->RecordItemPurchase(TEXT("Sword23"), TEXT("Gems"), 10, 1);
		//!< ゲーム内通貨を取得を記録 ... 10ジェムを取得した
		Provider->RecordCurrencyGiven(TEXT("Gems"), 10);
		//!< リアルマネーでゲーム内通貨購入を記録 ... Paypalにて100ジェムを19ドルで購入した
		Provider->RecordCurrencyPurchase(TEXT("Gems"), 100, TEXT("USD"), 19.0f, TEXT("Paypal"));

		Provider->FlushEvents();
	}
}

void UAnalyticsGameInstance::Shutdown()
{
	Super::Shutdown();

	const auto Provider = FAnalytics::Get().GetDefaultConfiguredProvider();
	if (Provider.IsValid())
	{
		Provider->EndSession();
	}
}
