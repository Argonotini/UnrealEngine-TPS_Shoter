// Shooter Game. By xDedic. All Rights reserved.

#include "Menu/UI/AMMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "AMGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/HorizontalBox.h"
#include "Menu/UI/AMLevelItemWidget.h"
#include "Sound/SoundCue.h"

DEFINE_LOG_CATEGORY_STATIC(LogAMMenuWidget, All, All);

void UAMMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (StartGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this, &UAMMenuWidget::OnStartGame);
	}

	if (QuitGameButton)
	{
		QuitGameButton->OnClicked.AddDynamic(this, &UAMMenuWidget::OnQuitGame);
	}

	InitLevelItems();
}


void UAMMenuWidget::InitLevelItems()
{
	const auto AMGameInstance = GetAMGameInstance();
	if (!AMGameInstance) return;

	checkf(AMGameInstance->GetLevelsData().Num() != 0, TEXT("Levels data must not be empty!"));

	if (!LevelItemsBox) return;
	LevelItemsBox->ClearChildren();

	for (auto LevelData : AMGameInstance->GetLevelsData())
	{
		const auto LevelItemWidget = CreateWidget<UAMLevelItemWidget>(GetWorld(), LevelItemWidgetClass);
		if (!LevelItemWidget) continue;

		LevelItemWidget->SetLevelData(LevelData);
		LevelItemWidget->OnLevelSelected.AddUObject(this, &UAMMenuWidget::OnLevelSelected);

		LevelItemsBox->AddChild(LevelItemWidget);
		LevelItemWidgets.Add(LevelItemWidget);
	}

	if (AMGameInstance->GetStartupLevelData().LevelName.IsNone())
	{
		OnLevelSelected(AMGameInstance->GetLevelsData()[0]);
	}
	else
	{
		OnLevelSelected(AMGameInstance->GetStartupLevelData());
	}
}

void UAMMenuWidget::OnLevelSelected(const FLevelData& Data)
{
	const auto AMGameInstance = GetAMGameInstance();
	if (!AMGameInstance) return;

	AMGameInstance->SetStartupLevelData(Data);

	for (auto LevelItemWidget : LevelItemWidgets)
	{
		if (LevelItemWidget)
		{
			const auto IsSelected = Data.LevelName == LevelItemWidget->GetLevelData().LevelName;
			LevelItemWidget->SetSelected(IsSelected);
		}
	}
}

void UAMMenuWidget::OnStartGame()
{
	PlayAnimation(HideAnimation);
	UGameplayStatics::PlaySound2D(GetWorld(), StartGameSound);
}

void UAMMenuWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
	if (Animation != HideAnimation) return;

	const auto AMGameInstance = GetAMGameInstance();
	if (!AMGameInstance) return;

	UGameplayStatics::OpenLevel(this, AMGameInstance->GetStartupLevelData().LevelName);
}

void UAMMenuWidget::OnQuitGame()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

UAMGameInstance* UAMMenuWidget::GetAMGameInstance() const
{
	if (!GetWorld()) return nullptr;
	return GetWorld()->GetGameInstance<UAMGameInstance>();
}