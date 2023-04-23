// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RadialForce.generated.h"

UCLASS()
class BLASTER_API ARadialForce : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARadialForce();


	void GetHitCharacters();
	void GravityField(float Intensity);
	void KnockingField(float Intensity);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	TArray<FHitResult> OutHits;

	UPROPERTY()
	TArray<class ABlasterCharacter*> HitCharacters;

	UPROPERTY(EditAnywhere)
	float CollisionSphereRadius=1000;

	FCollisionShape ColSphere;

	FVector FieldLocation;

	bool WasSomethingHit;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
