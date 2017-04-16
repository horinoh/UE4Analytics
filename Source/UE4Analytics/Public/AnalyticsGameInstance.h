// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "AnalyticsGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UE4ANALYTICS_API UAnalyticsGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;
	virtual void Shutdown() override;
};
