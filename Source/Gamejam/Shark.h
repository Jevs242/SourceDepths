// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Blueprint/UserWidget.h"

#include "Enemy.h"

#include "Shark.generated.h"

/**
 * 
 */
UCLASS()
class GAMEJAM_API AShark : public APaperCharacter
{
	GENERATED_BODY()

public:
	AShark();

	//Unreal Function

	UFUNCTION()
		void OnBeginCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	//Components

	UPROPERTY(EditAnywhere, Category = "Component")
	UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere , Category = "Component")
		USphereComponent* SphereComp;

	UCapsuleComponent* CapsuleComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Component")
	UPaperFlipbookComponent* SpriteComp;

	UPROPERTY(EditAnywhere) 
		TSubclassOf<UUserWidget> WBP_Dead;

	UUserWidget* UWidget;

	UFUNCTION(BlueprintCallable)
		void setDoStarted(bool Ready);


	//Get Funtions

	UFUNCTION(BlueprintPure)
		bool getDead();

	UFUNCTION(BlueprintPure)
		int getCounterKill();

	UFUNCTION(BlueprintPure)
		int getCounterDistance();

	UFUNCTION(BlueprintPure)
		float getPercentHealth();

	UFUNCTION(BlueprintPure)
		float getPercentContamination();

	UFUNCTION(BlueprintPure)
		int getCounterRounds();

	//Questions

		bool DoStarted = false;
		bool IsDead = false;
		bool IsWasEaten = false; 

private:

	//Input Function

	void MoveUp(float Value);
	void MoveRight(float Value);



	void Dead(bool WasEaten);
	void DelayDead();

	//Edit Property

	float Speed = 1.5;

	UPROPERTY(EditAnywhere, Category = "Property")
		FVector BeginCameraLocation= FVector(-300.0, -500.0, 0.000000);

	UPROPERTY(EditAnywhere, Category = "Property")
		float Distance = 230;

	UPROPERTY(EditAnywhere, Category = "Property")
		float MaxHealth = 100;

	UPROPERTY(EditAnywhere, Category = "Property")
		float MaxContamination = 100;

	UPROPERTY(EditAnywhere, Category = "Property")
		float Healing = 20;

	UPROPERTY(EditAnywhere, Category = "Property")
		float Damage = 20;

	//Not Edit Property

	int MoveValue;
	float Health;
	float Contamination;

	int CounterKill;
	int CounterRounds = 1;
	float CounterDistance;

	float MinusContamination = 6;

	bool isDead = false;
	

};
