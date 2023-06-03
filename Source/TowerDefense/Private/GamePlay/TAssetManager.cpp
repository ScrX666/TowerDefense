// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/TAssetManager.h"

UTAssetManager* UTAssetManager::Get()
{
	UTAssetManager* This = Cast<UTAssetManager>(GEngine->AssetManager);
	if( This)
	{
		return This;
	}
	else
	{
		return NewObject<UTAssetManager>();
	}
}

FString UTAssetManager::AsynLoadObject(FSoftObjectPath Path, FOnPackageLoaded OnPackageLoaded)
{
	FString Result;
	Result += FString::Printf(TEXT("StartLoad:\t%s\n"),*Path.ToString());

	CurrentLoadPackage = Path.ToString();
	LoadPackageAsync(CurrentLoadPackage,FLoadPackageAsyncDelegate::CreateLambda([=](const FName& PackageName,UPackage* LoadedPackage,EAsyncLoadingResult::Type Reslut)
	{
		if( Reslut == EAsyncLoadingResult::Succeeded)
		{
			OnPackageLoaded.ExecuteIfBound();
		}
	}),0, PKG_ContainsMap);
	return Result;
}

float UTAssetManager::GetCurrentLoadProgress(int32& LoadedCount, int32& RequestedCount) const
{
	return GetAsyncLoadPercentage(*CurrentLoadPackage);
}
