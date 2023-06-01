#pragma once

#include "CoreMinimal.h"
#include "DialogEvent/TBaseDialogEvent.h"
#include "FTAnsWithDialogs.generated.h"
/*
 * 分支选项
 */
USTRUCT(BlueprintType)
struct FTAnsWithDialogs
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UDataTable* NextDialog;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FText AnsText;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<ATBaseDialogEvent> DialogEvent;
};
