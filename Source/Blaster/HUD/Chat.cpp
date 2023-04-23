// Fill out your copyright notice in the Description page of Project Settings.


#include "Chat.h"
#include "ChatTextBlock.h"
#include "Components/ScrollBox.h"
#include "Blaster/PlayerController/BlasterPlayerController.h"
#include "Components/EditableTextBox.h"



void UChat::ChatSetup()
{
    SetVisibility(ESlateVisibility::Visible);
    bIsFocusable = true;
    UWorld* World = GetWorld();
    if (World)
    {
        OwningController = OwningController == nullptr ? World->GetFirstPlayerController() : OwningController;
        if (OwningController)
        {
            FInputModeGameAndUI InputModeData;
            InputModeData.SetWidgetToFocus(TakeWidget());
            OwningController->SetInputMode(InputModeData);
            OwningController->SetShowMouseCursor(true);
        }
    }
    ChatInput->SetFocus();
}



void UChat::OnTextCommitted(const FText& Text, const FString& PlayerName)
{
    OwningController = OwningController == nullptr ? GetOwningPlayer() : OwningController;
    if (ChatTextBlockClass && OwningController)
    {
        int32 LastIndex = ChatTextBlocks.Num();
        UChatTextBlock* ChatTextBlock = CreateWidget<UChatTextBlock>(GetOwningPlayer(), ChatTextBlockClass);
        if (ChatTextBlock)
        {
            ChatTextBlocks.Add(ChatTextBlock);
            const FString TextToDisplay = FString::Printf(TEXT("%s: %s"), *PlayerName, *Text.ToString());
            ChatTextBlock->SetBlockText(TextToDisplay);
            ChatTextBlocks.Add(ChatTextBlock);
            ChatTextBox->AddChild(ChatTextBlock);
            ChatTextBox->ScrollToEnd();
        }
        
    }
    ChatInput->SetText(FText::FromString(""));
    ChatInput->SetFocus();
}



void UChat::ChatTearDown()
{
    SetVisibility(ESlateVisibility::Collapsed);
    UWorld* World = GetWorld();
    if (World)
    {
        OwningController = OwningController == nullptr ? World->GetFirstPlayerController() : OwningController;
        if (OwningController)
        {
            FInputModeGameOnly InputModeData;
            OwningController->SetInputMode(InputModeData);
            OwningController->SetShowMouseCursor(false);
        }
    }
}