// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "MyAnalytics.h"

#include "MyAnalyticsProvider.h"

#define LOCTEXT_NAMESPACE "FMyAnalyticsModule"

void FMyAnalyticsModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	MyAnalyticsProvider = MakeShareable(new FMyAnalyticsProvider());
}

void FMyAnalyticsModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	if (MyAnalyticsProvider.IsValid())
	{
		MyAnalyticsProvider->EndSession();
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMyAnalyticsModule, MyAnalytics)

