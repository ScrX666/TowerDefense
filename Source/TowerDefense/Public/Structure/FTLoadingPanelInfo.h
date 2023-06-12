#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FTLoadingPanelInfo.generated.h"

USTRUCT()
struct TOWERDEFENSE_API FTLoadingPanelInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UTexture2D* ChangeLevelTexture;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FText ChangeLevelText;

	/**
	 * @brief 开始渐变颜色
	 */
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,meta = (DisplayName = "开始渐变颜色"))
	FColor TextColorBegin;
	
	/**
	 * @brief 结束渐变颜色
	 */
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,meta = (DisplayName = "结束渐变颜色"))
	FColor TextColorENd;
};