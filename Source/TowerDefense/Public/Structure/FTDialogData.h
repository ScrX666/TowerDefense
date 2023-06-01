#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FTAnsWithDialogs.h"
#include "DialogEvent/TBaseDialogEvent.h"
#include "Enum/ESpeakerFaceType.h"
#include "Interface/TDialogEventInterface.h"
#include "UObject/ScriptInterface.h"
#include "FTDialogData.generated.h"


USTRUCT()
struct FTDialogData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FName SpeakerId;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FText SpeakText;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	ESpeakerFaceType FaceType;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TArray<FTAnsWithDialogs> NextDialogs;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<ATBaseDialogEvent> DialogEvent;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	bool bIsBranch;
};

