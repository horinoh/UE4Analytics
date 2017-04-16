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

		//!< �C�x���g���L�^ ... ����X���J����
		Provider->RecordEvent(TEXT("WeaponStoreOpened"));
		//!< �P�����t�C�x���g���L�^ ... ��(Sword23)�𑕔�����
		Provider->RecordEvent(TEXT("ItemEquipped"), { TEXT("ItemID"), TEXT("Sword23") });
		//!< ���������t�C�x���g���L�^ ... �S���ŉ������̌�(Sword100)���N���t�g����
		Provider->RecordEvent(TEXT("ItemCrafted"), {
			{ TEXT("ItemID"), TEXT("Sword100") },
			{ TEXT("MetalUsed"), TEXT("Steel") },
			{ TEXT("DamageModifierType"), TEXT("Fire") },
		});
		//!< �Q�[�����ʉ݂ōw�����L�^ ... 10�W�F���̌�(Sword23)��1�w������ 
		Provider->RecordItemPurchase(TEXT("Sword23"), TEXT("Gems"), 10, 1);
		//!< �Q�[�����ʉ݂��擾���L�^ ... 10�W�F�����擾����
		Provider->RecordCurrencyGiven(TEXT("Gems"), 10);
		//!< ���A���}�l�[�ŃQ�[�����ʉݍw�����L�^ ... Paypal�ɂ�100�W�F����19�h���ōw������
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
