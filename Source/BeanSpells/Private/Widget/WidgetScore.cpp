

#include "Widget/WidgetScore.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UWidgetScore::NativeConstruct()
{
	Super::NativeConstruct();
	if(ScoreText)
	{
		ScoreText->SetText(FText::FromString("Score : 0"));
	}
	if(HealthBar)
	{
		HealthBar->SetPercent(1.0f);
	}
	if(HealthStats)
	{
		HealthStats->SetText(FText::FromString(FString::Printf(TEXT("%d / %d"),100,100)));
	}
}

void UWidgetScore::UpdateScore(int score)
{
	if(ScoreText)
	{
		ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score : %d"), score)));
	}
}

void UWidgetScore::UpdateHealth(float newHealthRatio, float max)
{
	if(HealthBar)
	{
		HealthBar->SetPercent(newHealthRatio);
	}
	if(HealthStats)
	{
		HealthStats->SetText(FText::FromString(FString::Printf(TEXT("%d / %d"),int(newHealthRatio * max),int(max))));
	}
}
