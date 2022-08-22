// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperSpriteComponent.h"
#include "Bubble.generated.h"

UCLASS()
class GAMEJAM_API ABubble : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABubble();

	UPROPERTY(EditAnywhere ,BlueprintReadWrite, Category = "Component")
		UPaperSpriteComponent* SpriteComp;
private:
	UPROPERTY(EditAnywhere , Category = "Property")
		float Speed = 20;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
