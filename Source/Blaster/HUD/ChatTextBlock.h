// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChatTextBlock.generated.h"

/**
 * 
 */
UCLASS()
class BLASTER_API UChatTextBlock : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetBlockText(FString Message);

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ChatText;
};
