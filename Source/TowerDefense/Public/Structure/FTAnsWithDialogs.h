#pragma once

#include "CoreMinimal.h"
#include "FTAnsWithDialogs.generated.h"

USTRUCT(BlueprintType)
struct FTAnsWithDialogs
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UDataTable* NextDialog;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FText AnsText;
};
