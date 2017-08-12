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

		//!< Weapon Store Opened
		Provider->RecordEvent(TEXT("WeaponStoreOpened"));
		//!< Equipped Item(==Sword23)
		Provider->RecordEvent(TEXT("ItemEquipped"), { TEXT("ItemID"), TEXT("Sword23") });
		//!< Crafted Item(==Sword100(Metal==Steel, Modifier==Fire))
		Provider->RecordEvent(TEXT("ItemCrafted"), {
			{ TEXT("ItemID"), TEXT("Sword100") },
			{ TEXT("MetalUsed"), TEXT("Steel") },
			{ TEXT("DamageModifierType"), TEXT("Fire") },
		});
		//!< Purchase Item(==Sword23), which costs 10 Gems
		Provider->RecordItemPurchase(TEXT("Sword23"), TEXT("Gems"), 10, 1);
		//!< Got 10 Gems
		Provider->RecordCurrencyGiven(TEXT("Gems"), 10);
		//!< Purchase 100 Gems by 19 USD in Paypal
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
