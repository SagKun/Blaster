// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatTextBlock.h"
#include "Components/TextBlock.h"

void UChatTextBlock::SetBlockText(FString Message)
{
	FString BlockText = FString::Printf(TEXT("%s"), *Message);
	if (ChatText)
	{
		ChatText->SetText(FText::FromString(BlockText));
	}
}
