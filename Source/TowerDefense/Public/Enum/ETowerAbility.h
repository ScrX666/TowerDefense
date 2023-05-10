#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ETowerAbility : uint8
{
	E_Damage,
	E_AttackRange,
	E_ParallelAttack,
	
	// 仅射击塔有效
	E_ShotRate,
	E_BulletSpeed,
	
	// Buff
	E_Buff
};