// Fill out your copyright notice in the Description page of Project Settings.


#include "GenericField.h"

AGenericField::AGenericField()
{
	FieldSystemComponent = GetFieldSystemComponent();
}

void AGenericField::Explode(FVector CenterPosition)
{

	if (FieldSystemComponent)
	{
		// Strain Field
		FieldSystemComponent->ApplyStrainField(true, CenterPosition, SphereRadius, StrainMagnitude, 1);

		// Linear Velocity Field
		FieldSystemComponent->ApplyUniformVectorFalloffForce(true, CenterPosition, GetActorForwardVector(), SphereRadius, VelocityMagnitude);

		// Delete after explosion to avoid physics inconsistencies
		Destroy();
	}
}


void AGenericField::LinearForce(FVector Direction)
{

	if (FieldSystemComponent)
	{
		FieldSystemComponent->ApplyLinearForce(true, Direction, StrainMagnitude);

		// Delete after explosion to avoid physics inconsistencies
		Destroy();
	}
}

