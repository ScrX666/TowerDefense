#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FTSpeakerInfo.generated.h"

enum class ESpeakerFaceType : uint8;

USTRUCT()
struct FTSpeakerInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TMap<ESpeakerFaceType,UTexture2D*> SpeakerFaces;
};
