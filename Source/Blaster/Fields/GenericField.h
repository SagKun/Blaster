// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Field/FieldSystemActor.h"
#include "GenericField.generated.h"

/**
 * 
 */
UCLASS()
class BLASTER_API AGenericField : public AFieldSystemActor
{
	GENERATED_BODY()
	
public:
	AGenericField();

	void Explode(FVector CenterPosition);
	void LinearForce(FVector Direction);

	UPROPERTY(EditAnywhere, Category = "Field Params")
		float SphereRadius = 100.f;

	UPROPERTY(EditAnywhere, Category = "Field Params")
		float VelocityMagnitude = 100.f;

	UPROPERTY(EditAnywhere, Category = "Field Params")
		float StrainMagnitude = 100.f;

protected:
	class UFieldSystemComponent* FieldSystemComponent;

private:

};
