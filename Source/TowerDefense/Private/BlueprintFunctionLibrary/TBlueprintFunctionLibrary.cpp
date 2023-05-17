// Fill out your copyright notice in the Description page of Project Settings.


#include "BlueprintFunctionLibrary/TBlueprintFunctionLibrary.h"

#include "GamePlay/TDataTableManager.h"
#include "Kismet/GameplayStatics.h"
#include "Structure/FTBoolArray.h"

TArray<FTBoolArray> UTBlueprintFunctionLibrary::GetRandomPath(int32 Width, int32 Length,int32 N)
{
    TArray<FTBoolArray> Grid;
	    FTBoolArray TArr(Length);
	for( int i = 0; i < Width; i++)
	{
	    Grid.Add(TArr);
	}
    for( int i = 0; i < Width; i++)
    {
        for( int j = 0; j < Length; j++)
        {
            Grid[i][j] = false;
        }
    }

    std::pair<int, int> Cur;
    Cur.first = 0;
    Cur.second = 0;
    Grid[0][0] = true;

    int dx[4] = { 1, 0, -1, 0 };
    int dy[4] = { 0, -1, 0, 1 };

    int dir = -1;
    int presist = 0;
    int pre = dir;
    while (N--)
    {
        bool stt[4];
        memset(stt, 0, sizeof(stt));
        for (int j = 0; j < 4; j++)
        {
            int i = dir;
            if (presist == 0)
            {
                do
                {
                    i = FMath::RandRange(0, 3);
                } while (stt[i] && i == pre);
                pre = i;
                dir = i;
                presist = FMath::RandRange(0, 4) + 3;
            }
            stt[i] = true;
            
            presist--;
            auto next = Cur;
            next.first += dx[i];
            next.second += dy[i];
            int x = next.first;
            int y = next.second;
            if (x >= Width || x < 0 || y >= Length || y < 0)
                continue;
    
            bool CheckResult = false;
            int count = 0;
    
            for (int k = 0; k < 4; k++)
            {
                int xx = dx[k] + x;
                int yy = dy[k] + y;
                if (xx >= Width || xx < 0 || yy >= Length || yy < 0)
                    continue;
                if (Grid[xx][yy])
                {
                    count++;
                }
            }
    
            if (count == 1) CheckResult = true;
            
            if (!Grid[x][y] && CheckResult)
            {
                Grid[x][y] = true;
                Cur.first = x;
                Cur.second = y;
                break;
            }
        }
    }

    int AbleCount = 0;
    for( int i = 0; i < Width; i++)
    {
        for( int j = 0; j < Length; j++)
        {
            if( Grid[i][j])
                AbleCount++;
        }
    }
    if( AbleCount < N / 2)
        return GetRandomPath(Width,Length,N);
    
    return Grid;
}

FName UTBlueprintFunctionLibrary::GetNextLevel(const FName CurrentLevelName)
{
    return
    TDataTableManager::GetInstance()->GetNextLevel(CurrentLevelName);
}

int32 UTBlueprintFunctionLibrary::GetTowerCoinsByClassAndName(TSubclassOf<ATMainTower> Tower, FName Name)
{
    if( Tower == ATMainBeamTower::StaticClass())
    {
        return TDataTableManager::GetInstance()->GetBeamTowerData(Name).CostCoins;
    }
    else
    {
        return TDataTableManager::GetInstance()->GetShotTowerData(Name).CostCoins;
    }
}
