// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"

bool UMainMenu::Initialize()
{
	bool IsSuccess = Super::Initialize();
	if(!IsSuccess) return false;

	// #setup
	if(!ensure(HostBtn != nullptr)) return false;
	HostBtn->OnClicked.AddDynamic(this, &UMainMenu::HostServer);
	if(!ensure(JoinBtn != nullptr)) return false;
	JoinBtn->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);
	if(!ensure(CancelBtn != nullptr)) return false;
	CancelBtn->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);
	//if(!ensure(JoinServerBtn != nullptr)) return false;
	//JoinServerBtn->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);

	
	return true;
}

void UMainMenu::SetMenuInterface(IMenuInterface* MenuInterface)
{
	this->AMenuInterface = MenuInterface;
}

void UMainMenu::Setup()
{
	this->AddToViewport();

	UWorld* World = GetWorld();
	APlayerController* PlayerController = World->GetFirstPlayerController();
	
	FInputModeUIOnly InputModeData;
	//InputModeData.SetWidgetToFocus(Menu->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	this->bIsFocusable = true;
	PlayerController->SetInputMode(InputModeData);

	PlayerController->bShowMouseCursor = true;	
}

void UMainMenu::Teardown()
{
	UWorld* World = GetWorld();
	APlayerController* PlayerController = World->GetFirstPlayerController();

	FInputModeGameOnly InputModeData;
	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = false;

	this->RemoveFromParent();
}


void UMainMenu::HostServer()
{
	if(AMenuInterface != nullptr)
	{
		AMenuInterface->Host();
	}
}

void UMainMenu::OpenJoinMenu()
{
	if(!ensure(MenuSwitcher != nullptr)) return;
	if(!ensure(JoinMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenu::OpenMainMenu()
{
	if(!ensure(MenuSwitcher != nullptr)) return;
	if(!ensure(MainMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(MainMenu);
}
