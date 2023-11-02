#include "WidgetScore.h"

#include "Components/TextBlock.h"

void UWidgetScore::NativeConstruct()
{
	Super::NativeConstruct();
	if(ScoreText)
	{
		ScoreText->SetText(FText::FromString("Score : 0"));
	}
}

void UWidgetScore::UpdateScore(int score)
{
	if(ScoreText)
	{
		ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score : %d"), score)));
	}
}
