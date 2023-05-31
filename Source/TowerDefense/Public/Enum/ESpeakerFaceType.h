#pragma once


UENUM(BlueprintType)
enum class ESpeakerFaceType : uint8
{
    E_Default UMETA(DisplayName = "默认"),
	E_Happy      UMETA(DisplayName="开心"),
	E_Surprised       UMETA(DisplayName="惊讶"),
	E_Grieve    UMETA(DisplayName="伤心"),
	E_Fear    UMETA(DisplayName="害怕"),
	E_Shy    UMETA(DisplayName="害羞"),
	E_Hate    UMETA(DisplayName="厌恶"),
	E_Angry    UMETA(DisplayName="生气"),
};