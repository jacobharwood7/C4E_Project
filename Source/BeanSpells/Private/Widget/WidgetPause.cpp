#include "Widget/WidgetPause.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UWidgetPause::NativeConstruct()
{
	Super::NativeConstruct();
	if(resume)
	{		
		resume->OnClicked.AddUniqueDynamic(this,&UWidgetPause::ResumeButton);
	}
	if(quit)
	{
		quit->OnClicked.AddUniqueDynamic(this,&UWidgetPause::QuitButton);
	}
}


void UWidgetPause::ResumeButton()
{
	
	UE_LOG(LogTemp,Display,TEXT("PauseAttemptresume"))
	APlayerController* PC = GetOwningPlayer();
	UGameplayStatics::SetGamePaused(GetWorld(),false);
	
	PC->SetShowMouseCursor(false);
	PC->SetInputMode(FInputModeGameOnly());

	RemoveFromParent();
	
}

void UWidgetPause::QuitButton()
{
	UE_LOG(LogTemp,Display,TEXT("PauseAttemptquit"))
	
	APlayerController* PC = GetOwningPlayer();
	UKismetSystemLibrary::QuitGame(GetWorld(),PC,EQuitPreference::Quit,false);
}
