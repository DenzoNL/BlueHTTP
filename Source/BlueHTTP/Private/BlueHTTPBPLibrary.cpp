// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "BlueHTTPPrivatePCH.h"
#include "BlueHTTPBPLibrary.h"
#include "Runtime/Online/HTTP/Public/Http.h"

FBlueHTTPConfigStruct UBlueHTTPBPLibrary::Config;

UBlueHTTPBPLibrary::UBlueHTTPBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

void UBlueHTTPBPLibrary::BlueHTTPRequest(FString MetricName, float Value)
{
	FHttpModule* Http = &FHttpModule::Get();
	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->SetURL(Config.Url);
	Request->SetVerb("POST");
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->SetContentAsString("{ \"device_uid\":\"" + UKismetSystemLibrary::GetUniqueDeviceId() + "\", \"api_key\":\"" + Config.ApiKey + "\", \"metric_name\":\"" + MetricName + "\", \"platform_name\":\""+ UGameplayStatics::GetPlatformName() +"\", \"game_build_id\":1, \"value\":" + FString::SanitizeFloat(Value) + "}");
	Request->ProcessRequest();
}

void UBlueHTTPBPLibrary::BlueHTTPSetConfig(FBlueHTTPConfigStruct UserConfig)
{
	Config = UserConfig;
}

FBlueHTTPConfigStruct UBlueHTTPBPLibrary::BlueHTTPGetConfig()
{
	return Config;
}

