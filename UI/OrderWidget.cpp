// Fill out your copyright notice in the Description page of Project Settings.


#include "OrderWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Basic_RR.h"
#include "MyArrow.h"
#include "MyPlayerController.h"
#include "Skill_Cat_01.h"
#include <Kismet/GameplayStatics.h>
#include "AI_RR.h"

void UOrderWidget::NativeConstruct()
{
	Super::NativeConstruct();

	RRClass = Cast<UTextBlock>(GetWidgetFromName(TEXT("rrclass")));
	RRThumbnail = Cast<UImage>(GetWidgetFromName(TEXT("rrthumbnail")));
	RRLevel = Cast<UTextBlock>(GetWidgetFromName(TEXT("rrlevel")));

	Btn_Move = Cast<UButton>(GetWidgetFromName(TEXT("Btn_Move")));
	Btn_Skill = Cast<UButton>(GetWidgetFromName(TEXT("Btn_Skill")));
	Btn_Back = Cast<UButton>(GetWidgetFromName(TEXT("Btn_Back")));

	if (Btn_Move)
	{
		Btn_Move->OnClicked.AddDynamic(this, &UOrderWidget::Btn_Move_Cliked);
	}

	if (Btn_Skill)
	{
		Btn_Skill->OnClicked.AddDynamic(this, &UOrderWidget::Btn_Skill_Cliked);
	}

	if (Btn_Back)
	{
		Btn_Back->OnClicked.AddDynamic(this, &UOrderWidget::Btn_Back_Cliked);
	}
}

void UOrderWidget::Btn_Move_Cliked()
{
	//È­»ìÇ¥ »ý¼º
	FVector pawnLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	FVector arrowLocation(pawnLocation.X , pawnLocation.Y , pawnLocation.Z + 60);
	FRotator SpawnRotation(0, 0, 0);
	AMyArrow* SpawnedArrow = (AMyArrow*)GetWorld()->SpawnActor(AMyArrow::StaticClass(), &arrowLocation, &SpawnRotation);
	SpawnedArrow->SetActorScale3D(FVector(8, 6, 5));
	RemoveFromViewport();
}

void UOrderWidget::Btn_Skill_Cliked()
{
	auto current_rr = Cast<ABasic_RR>(GetWorld()->GetFirstPlayerController()->GetPawn());
	current_rr->Skill_01();
	RemoveFromViewport();
}

void UOrderWidget::Btn_Back_Cliked()
{
	RemoveFromViewport();
}

void UOrderWidget::BindRRState(class ABasic_RR* RRState)
{
	Basic_RRState = RRState;
	UpdateRRState();
}

void UOrderWidget::UpdateRRState()
{
	RRClass->SetText(Basic_RRState->GetRRClass());
	RRThumbnail->SetBrushFromTexture(Basic_RRState->GetRRThumbnail());
	RRLevel->SetText(FText::FromString(FString::FromInt(Basic_RRState->GetRRLevel())));
}

