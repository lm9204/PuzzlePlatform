// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"

#include "InterchangeProjectSettings.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem/MainMenu.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer & ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> MainMenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if(!ensure(MainMenuBPClass.Class != nullptr)) return;
	MainMenuClass = MainMenuBPClass.Class;
	
}

void UPuzzlePlatformsGameInstance::Init() 
{
	Super::Init();
	UE_LOG(LogTemp, Warning, TEXT("Init::Found Class %s "), *MainMenuClass->GetName());
}

void UPuzzlePlatformsGameInstance::LoadMenu()
{
	if(!ensure(MainMenuClass != nullptr)) return;
	Menu =  CreateWidget<UMainMenu>(this, MainMenuClass);
	
	if(!ensure(Menu != nullptr)) return;
	UE_LOG(LogTemp, Warning, TEXT("LoadMenu::work"));

	Menu->Setup();
	Menu->SetMenuInterface(this);
}



void UPuzzlePlatformsGameInstance::Host()
{
	if(Menu != nullptr)
	{
		Menu->Teardown();
	}
	GEngine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Hosting..."));

	UWorld* World = GetWorld();

	World->ServerTravel("/Game/ThirdPerson/Maps/ThirdPersonMap?listen");
}

void UPuzzlePlatformsGameInstance::Join(const FString& Address)
{
	if(Menu != nullptr)
	{
		Menu->Teardown();
	}
	APlayerController* PlayerController = GetFirstLocalPlayerController();

	PlayerController->ClientTravel(Address, TRAVEL_Absolute);
}
