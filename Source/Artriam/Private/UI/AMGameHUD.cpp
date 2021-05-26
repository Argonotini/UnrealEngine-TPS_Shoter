// Shooter Game. By xDedic. All Rights reserved.

#include "UI/AMGameHUD.h"
#include "Engine/Canvas.h"
#include "UI/AMBaseWidget.h"
#include "AMGameModeBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogAMGameHUD, All, All);

void AAMGameHUD::DrawHUD()
{
	Super::DrawHUD();
}

void AAMGameHUD::BeginPlay()
{
	Super::BeginPlay();

	GameWidgets.Add(EAMMatchState::InProgress, CreateWidget<UAMBaseWidget>(GetWorld(), PlayerHUDWidgetClass));
	GameWidgets.Add(EAMMatchState::Pause, CreateWidget<UAMBaseWidget>(GetWorld(), PauseWidgetClass));
	GameWidgets.Add(EAMMatchState::GameOver, CreateWidget<UAMBaseWidget>(GetWorld(), GameOverWidgetClass));

	for (auto GameWidgetPair: GameWidgets)
	{
		const auto GameWidget = GameWidgetPair.Value;
		if(!GameWidget) continue;

		GameWidget->AddToViewport();
		GameWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	if (GetWorld())
	{
		const auto GameMode = Cast<AAMGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnMatchStateChanged.AddUObject(this, &AAMGameHUD::OnMatchStateChanged);
		}
	}
}

void AAMGameHUD::OnMatchStateChanged(EAMMatchState State)
{
	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	if (GameWidgets.Contains(State))
	{
		CurrentWidget = GameWidgets[State];
	}

	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Visible);
		CurrentWidget->Show();
	}
	UE_LOG(LogAMGameHUD, Display, TEXT("Match state changed: %s"), *UEnum::GetValueAsString(State));
}

void AAMGameHUD::DrawCrossHair()
{
	const TInterval<float> Center(Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f);

	const float HalfLineSize = 10.0f;
	const float LineThickness = 2.0f;
	const FLinearColor LineColor = FLinearColor::Green;

	DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, LineColor, LineThickness);
	DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize, LineColor, LineThickness);
}