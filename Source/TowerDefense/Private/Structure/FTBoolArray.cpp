// Fill out your copyright notice in the Description page of Project Settings.


#include "Structure/FTBoolArray.h"

FTBoolArray::FTBoolArray()
{
}

FTBoolArray::FTBoolArray(int Length)
{
	bool Boolean = false;
	Array = TArray<bool>(&Boolean,Length);
}

bool& FTBoolArray::operator[](int Index)
{
	return Array[Index];
}
