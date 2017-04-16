// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ModuleManager.h"

#include "Interfaces/IAnalyticsProviderModule.h"
class IAnalyticsProvider;

class FMyAnalyticsModule : public IAnalyticsProviderModule
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	//!< IAnalyticsProviderModule
	virtual TSharedPtr<IAnalyticsProvider> CreateAnalyticsProvider(const FAnalyticsProviderConfigurationDelegate& GetConfigValue) const override { return MyAnalyticsProvider; }

	static inline FMyAnalyticsModule& Get() { return FModuleManager::LoadModuleChecked<FMyAnalyticsModule>("MyAnalytics"); }

private:
	TSharedPtr<IAnalyticsProvider> MyAnalyticsProvider;
};