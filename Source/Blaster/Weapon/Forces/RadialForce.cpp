// Fill out your copyright notice in the Description page of Project Settings.


#include "RadialForce.h"
#include "DrawDebugHelpers.h"
#include "Blaster/Character/BlasterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

ARadialForce::ARadialForce()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

void ARadialForce::GetHitCharacters()
{
	// check if something got hit in the sweep
	WasSomethingHit = GetWorld()->SweepMultiByChannel(OutHits, FieldLocation, FieldLocation, FQuat::Identity, ECC_WorldStatic, ColSphere);

	//remove duplicate hit character(which happen a lottttt)
	for (auto& Hit : OutHits)
	{
		class ABlasterCharacter* HitCharacter = Cast<ABlasterCharacter>(Hit.GetActor());
		if (HitCharacter)
		{
			HitCharacters.AddUnique(HitCharacter);
		}
	}
}

void ARadialForce::GravityField(float Intensity)
{

	if (WasSomethingHit)
	{
		// loop through Hit Characters
		for (auto& Character : HitCharacters)
		{

			if (Character)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("character was hit"));
				UCharacterMovementComponent* Movement = Character->GetCharacterMovement();
				if (Movement)
				{
					Movement->bUseControllerDesiredRotation = false;
					Movement->AddImpulse((FieldLocation - Character->GetActorLocation()) * Intensity, true);
				}
			}

			//add this to add radial impulse on static meshes in the environement too
			/*
			* if (MeshComp)
			{
				// alternivly you can use  ERadialImpulseFalloff::RIF_Linear for the impulse to get linearly weaker as it gets further from origin.
				// set the float radius to 500 and the float strength to 2000.
				MeshComp->AddRadialImpulse(GetActorLocation(), 500.f, 2000.f, ERadialImpulseFalloff::RIF_Constant, true);
			}
			*/

		}
	}

	Destroy();
}

void ARadialForce::KnockingField(float Intensity)
{
	DrawDebugSphere(GetWorld(), FieldLocation, ColSphere.GetSphereRadius(), 50, FColor::Red, true);
	if (WasSomethingHit)
	{
		// loop through Hit Characters
		for (auto& Character : HitCharacters)
		{

			if (Character)
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("character was hit"));
				UCharacterMovementComponent* Movement = Character->GetCharacterMovement();
				if (Movement)
				{
					Movement->bUseControllerDesiredRotation = false;
					Movement->AddImpulse((Character->GetActorLocation() - FieldLocation) * Intensity, true);
				}
			}

			//add this to add radial impulse on static meshes in the environement too
			/*
			* if (MeshComp)
			{
				// alternivly you can use  ERadialImpulseFalloff::RIF_Linear for the impulse to get linearly weaker as it gets further from origin.
				// set the float radius to 500 and the float strength to 2000.
				MeshComp->AddRadialImpulse(GetActorLocation(), 500.f, 2000.f, ERadialImpulseFalloff::RIF_Constant, true);
			}
			*/

		}
	}

	//Destroy();
}

// Called when the game starts or when spawned
void ARadialForce::BeginPlay()
{
	Super::BeginPlay();
	ColSphere = FCollisionShape::MakeSphere(CollisionSphereRadius);
	FieldLocation = GetActorLocation();
	// draw collision sphere
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("This message will appear on the screen!"));
	GetHitCharacters();
}

// Called every frame
void ARadialForce::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

