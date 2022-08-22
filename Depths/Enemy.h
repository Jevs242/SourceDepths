// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperFlipbookComponent.h"
#include "Components/SphereComponent.h"
#include "Enemy.generated.h"

UCLASS()
class GAMEJAM_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	int NumberEnemy; //1.Baby Sharks , 2.Adult Sharks , 3.Trash

	bool DeathFish = false;

	UPROPERTY(EditAnywhere, Category = "Property")
	int Speed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere , Category = "Components")
		UPaperFlipbookComponent* SpriteComp;

	UPROPERTY(EditAnywhere , Category = "Property")
		UPaperFlipbook* Sprites[4];

	UPROPERTY(EditAnywhere, Category = "Property")
		UPaperFlipbook* ColorFish[5];

	UPROPERTY(EditAnywhere, Category = "Property")
		UPaperFlipbook* NumberTrash[6];

	UPROPERTY(EditAnywhere , Category = "Components")
		USphereComponent* SphereComp;

	void DelayDestroy();
	void DelayBite();
	void SpawnBlood();
private:


	void FBite();
	void FDestroy();

};
