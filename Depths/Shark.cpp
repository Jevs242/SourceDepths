// Fill out your copyright notice in the Description page of Project Settings.


#include "Shark.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Misc/OutputDeviceNull.h"

#define print(x) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT(x));


AShark::AShark()
{
	CapsuleComp = GetCapsuleComponent();
	SpriteComp = GetSprite();
	CameraComp = CreateDefaultSubobject<UCameraComponent>("Camera Component");
	SphereComp = CreateDefaultSubobject<USphereComponent>("Sphere Component");
	SpriteComp = CreateDefaultSubobject<UPaperFlipbookComponent>("Sprite Component");

	CapsuleComp->SetSimulatePhysics(true);
	CapsuleComp->SetEnableGravity(false);
	CameraComp->SetWorldLocation(BeginCameraLocation);
	SphereComp->SetupAttachment(CapsuleComp);
	SpriteComp->SetupAttachment(CapsuleComp);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AShark::OnBeginCollision);

	Health = MaxHealth;
}

void AShark::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveUp", this, &AShark::MoveUp);
	PlayerInputComponent->BindAxis("MoveRight", this, &AShark::MoveRight);
}

void AShark::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CameraComp->SetWorldLocation(BeginCameraLocation);
	
	if (DoStarted && !IsDead)
	{


		CounterDistance += (Speed * 2) * DeltaTime;


		Contamination += MinusContamination * DeltaTime;
		Health -= (Contamination / 10) * DeltaTime;
		Health = FMath::Clamp(Health, 0, 100);

		if (Contamination >= 100 && CounterRounds < 5)
		{
			MinusContamination--;
			CounterRounds++;
			Contamination = 0;
			Speed += 0.3;
		}

		if (Health <= 0 && !IsWasEaten)
		{
			Dead(false);
			IsWasEaten = false;
		}
	}


}

void AShark::BeginPlay()
{
	Super::BeginPlay();
	//APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	//this->DisableInput(PlayerController);
}

void AShark::MoveUp(float Value)
{
	if (DoStarted && !IsDead)
	{
		FVector Location = GetActorLocation();
		if (Location.Z <= Distance && Location.Z >= -Distance)
		{
			Location.Z += Value * Speed;
		}

		if (Location.Z > Distance)
		{
			Location.Z = Distance;
		}
		else if (Location.Z < -Distance)
		{
			Location.Z = -Distance;
		}
		SetActorLocation(Location);
	}
}

void AShark::MoveRight(float Value)
{
	if (DoStarted && !IsDead)
	{
		FVector Location = GetActorLocation();
		if (Location.X <= 0 && Location.X >= -200)
		{
			MoveValue = Value * Speed;
			if (Location.X == -200 || Location.X == 200)
			{
				MoveValue = 0;
			}
			Location.X += Value * Speed;
		}

		if (Location.X > 0)
		{
			Location.X = 0;
		}
		else if (Location.X < -200)
		{
			Location.X = -200;
		}
		SetActorLocation(Location);
	}
}

void AShark::Dead(bool WasEaten)
{
	IsDead = true;
	if (IsWasEaten)
	{
		SpriteComp->SetVisibility(false);

	}
	else
	{
		FOutputDeviceNull ar;
		this->CallFunctionByNameWithArguments(TEXT("Death"), ar, NULL, true);
	}
	IsDead = true;

	if (IsWasEaten)
	{
		if (WBP_Dead)
		{
			UWidget = CreateWidget<UUserWidget>(GetWorld(), WBP_Dead);

			if (UWidget)
			{


				UWidget->AddToViewport();

			}
		}
	}
	else 
	{
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AShark::DelayDead, 1, false);
	}
}

void AShark::DelayDead()
{
	if (WBP_Dead)
	{
		UWidget = CreateWidget<UUserWidget>(GetWorld(), WBP_Dead);

		if (UWidget)
		{


			UWidget->AddToViewport();

		}
	}
}


void AShark::OnBeginCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (DoStarted && !IsDead)
	{
		AEnemy* Enemy = Cast<AEnemy>(OtherActor);
		if (Enemy)
		{
			FTimerHandle TimerHandle;
			FOutputDeviceNull ar;
			this->CallFunctionByNameWithArguments(TEXT("Bite"), ar, NULL, true);
			switch (Enemy->NumberEnemy)
			{
			case 0:
				CounterKill++;
				Health += Healing;
				if (getCounterRounds() == 5)
				{
					Health += Healing;
				}
				Enemy->DeathFish = true;
				Enemy->DelayDestroy();
				break;
			case 1:
				this->CallFunctionByNameWithArguments(TEXT("OurDeath"), ar, NULL, true);
				IsWasEaten = true;
				Enemy->SpriteComp->SetFlipbook(Enemy->Sprites[3]);
				Enemy->DelayBite();

				Dead(true);
				break;
			case 2:
				Enemy->DelayDestroy();
				Health -= Damage;
				break;
			default:
				break;
			}
			Health = FMath::Clamp(Health, 0, 100);
		}
	}
}

void AShark::setDoStarted(bool Ready)
{
	if (Ready)
	{
		//APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		//this->EnableInput(PlayerController);
	}
	DoStarted = Ready;
}

bool AShark::getDead()
{
	return IsDead;
}

int AShark::getCounterKill()
{
	return CounterKill;
}

int AShark::getCounterDistance()
{
	return CounterDistance;
}

float AShark::getPercentHealth()
{
	return Health / MaxHealth;
}

float AShark::getPercentContamination()
{
	return Contamination / MaxContamination;
}

int AShark::getCounterRounds()
{
	return CounterRounds;
}
