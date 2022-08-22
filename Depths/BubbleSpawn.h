// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Bubble.h"
#include "BubbleSpawn.generated.h"

UCLASS()
class GAMEJAM_API ABubbleSpawn : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABubbleSpawn();

	UPROPERTY(EditAnywhere, Category = "Component")
		UBoxComponent* SpawnBox;

	UPROPERTY(EditAnywhere, Category = "Component")
		UBoxComponent* DestroyBox;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SpawnBubble();

	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:

	UPROPERTY(EditAnywhere, Category = "Object")
		TSubclassOf<ABubble> BP_Bubble;

};
