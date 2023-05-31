#pragma once

#include "TDialogEventInterface.generated.h"

UINTERFACE(BlueprintType)
class UTDialogEventInterface : public UInterface
{
	GENERATED_BODY()
};

class ITDialogEventInterface
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent)
	void TriggerDialogEvent();
	
};