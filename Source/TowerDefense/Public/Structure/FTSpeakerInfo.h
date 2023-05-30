#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FTSpeakerInfo.generated.h"

USTRUCT()
struct FTSpeakerInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UTexture2D* SpeakerIcon;
};
