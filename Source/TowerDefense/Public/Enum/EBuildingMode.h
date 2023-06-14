// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


UENUM(BlueprintType)
enum class EBuildingMode : uint8
{
	E_InBuildMode      UMETA(DisplayName="建造模式"),
	E_NotInBuildMode       UMETA(DisplayName="非建造模式"),
	E_InSillMode    UMETA(DisplayName="释放技能模式"),
	E_InHeroMode    UMETA(DisplayName="控制英雄模式"),
};