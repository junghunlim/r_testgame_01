// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "OrderWidget.h"
#include "HUDWidget.h"
#include "GameScoreWidget.h"
#include "Engine.h"
#include "MyPlayerState.h"
#include "Basic_RR.h"
#include "AI_RR.h"
#include <Kismet/GameplayStatics.h>
#include "Components/PrimitiveComponent.h"
#include "r_testgameGameModeBase.h"
#include "MovementManager.h"

AMyPlayerController::AMyPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;

	//���wiget ����Ŭ������ �ҷ�����
	static ConstructorHelpers::FClassFinder<UOrderWidget> OrderWidget_C(TEXT("/Game/UI/BP_ORDERWidget"));
	if (OrderWidget_C.Succeeded())
	{
		OrderWidgetClass = OrderWidget_C.Class;
	}

	//HUDwidget ����Ŭ������ �ҷ�����
	static ConstructorHelpers::FClassFinder<UHUDWidget> HUDWidget_C(TEXT("/Game/UI/BP_HUDWidget"));
	if (HUDWidget_C.Succeeded())
	{
		HUDWidget = HUDWidget_C.Class;
	}

	static ConstructorHelpers::FClassFinder<UGameScoreWidget> GameScoreWidget_C(TEXT("/Game/UI/BP_GameScoreWidget"));
	if (GameScoreWidget_C.Succeeded())
	{
		GameScoreWidget = GameScoreWidget_C.Class;
	}
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//ȭ�鿡 HUD���� �����ֱ�
	CurrentWidget = CreateWidget<UHUDWidget>(GetWorld(), HUDWidget);
	CurrentWidget->AddToViewport();

	//state�� ����hud������ ���ε����ֱ�
	auto MyPlayerState = Cast<AMyPlayerState>(PlayerState);
	CurrentWidget->BindPlayerState(MyPlayerState);
	MyPlayerState->OnPlayerStateChanged.Broadcast();

	//playercontroller �� myturn �� ���� hud������ ���ε� ���ֱ�
	CurrentWidget->BindPlayerTurnState(this);

	//playerstate �� basic_rr ���ε����ֱ�
	TArray<AActor*> basic_rr;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABasic_RR::StaticClass(), basic_rr);

	auto current_rr1 =  Cast<ABasic_RR>(basic_rr[0]);
	current_rr1->BindPlayerRRState1(MyPlayerState);

	if (basic_rr.Num() > 1)
	{
		auto current_rr2 = Cast<ABasic_RR>(basic_rr[1]);
		current_rr2->BindPlayerRRState2(MyPlayerState);
	}

	if (basic_rr.Num() > 2)
	{
		auto current_rr3 = Cast<ABasic_RR>(basic_rr[2]);
		current_rr3->BindPlayerRRState3(MyPlayerState);
	}

	MyPlayerState->OnPlayerStateChanged.Broadcast();
}

void AMyPlayerController::ShowOrderWidget()
{	
	OrderWidget = CreateWidget<UOrderWidget>(GetWorld(), OrderWidgetClass);
	OrderWidget->AddToViewport();
	auto currentRR1 = Cast<ABasic_RR>(GetPawn());
	OrderWidget->BindRRState(currentRR1);
}

void AMyPlayerController::ShowGameScoreWidgetWin()
{
	CurrentGameScoreWidget = CreateWidget<UGameScoreWidget>(GetWorld(), GameScoreWidget);
	CurrentGameScoreWidget->AddToViewport();
	CurrentGameScoreWidget->SetGameScoreWin();
}

void AMyPlayerController::ShowGameScoreWidgetLose()
{
	CurrentGameScoreWidget = CreateWidget<UGameScoreWidget>(GetWorld(), GameScoreWidget);
	CurrentGameScoreWidget->AddToViewport();
	CurrentGameScoreWidget->SetGameScoreLose();
}

void AMyPlayerController::ShowGameScoreWidgetDraw()
{
	CurrentGameScoreWidget = CreateWidget<UGameScoreWidget>(GetWorld(), GameScoreWidget);
	CurrentGameScoreWidget->AddToViewport();
	CurrentGameScoreWidget->SetGameScoreDraw();
}

void AMyPlayerController::quitgame()
{
	this->ConsoleCommand("quit");
}

//���콺 ������,������ �Լ��� ���ε�
void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("LeftClick", IE_Pressed, this, &AMyPlayerController::InputLeftMouseButtonPressed);
	InputComponent->BindAction("LeftClick", IE_Released, this, &AMyPlayerController::InputLeftMouseButtonReleased);

}

void AMyPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

}

//����RR�� �̵���Ų��
void AMyPlayerController::MoveRR(FVector2D MouseDelta)
{
	
	FVector MouseDeltaDirection(MouseDelta.Y, -MouseDelta.X, 0);
	FVector Force = FVector(-MouseDeltaDirection.X, -MouseDeltaDirection.Y, 0.0f).GetSafeNormal() * MouseDelta.Size()*10;
	auto currentRR2 = Cast<ABasic_RR>(GetPawn());
	currentRR2->MoveThisRR(Force);
	
	//movementmanager �����ؼ� ������ ���߸� CycleTurn()
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
		{
			AMovementManager* MovementManager = (AMovementManager*)GetWorld()->SpawnActor(AMovementManager::StaticClass());

		}, 0.5, false);
}

void AMyPlayerController::StartTurn()
{
	bool myturn = true;
	SetMyTurn(myturn);

}

void AMyPlayerController::EndTurn()
{
	bool myturn = false;
	SetMyTurn(myturn);

	//������� ����
	RemoveOrderWidget();

	//���ӽ��ھ� Ȯ�� �Լ�����
	CheckGameScore();
}

void AMyPlayerController::CheckGameScore()
{
	FTimerHandle TimerHandle2;
	//���� �� �����ͼ� null�̸� lose ȭ�� 
	if (UGameplayStatics::GetActorOfClass(GetWorld(), ABasic_RR::StaticClass()) == nullptr && UGameplayStatics::GetActorOfClass(GetWorld(), AAI_RR::StaticClass()) == nullptr)
	{
		//���º�
		ShowGameScoreWidgetDraw();

		GetWorld()->GetTimerManager().SetTimer(TimerHandle2, [&]()
			{
				ConsoleCommand("quit");
			}, 1.5, false);
	}
	if (UGameplayStatics::GetActorOfClass(GetWorld(), ABasic_RR::StaticClass()) != nullptr && UGameplayStatics::GetActorOfClass(GetWorld(), AAI_RR::StaticClass()) == nullptr)
	{
		//win ���
		ShowGameScoreWidgetWin();

		GetWorld()->GetTimerManager().SetTimer(TimerHandle2, [&]()
			{
				ConsoleCommand("quit");
			}, 1.5, false);
	}
	if (UGameplayStatics::GetActorOfClass(GetWorld(), ABasic_RR::StaticClass()) == nullptr && UGameplayStatics::GetActorOfClass(GetWorld(), AAI_RR::StaticClass()) != nullptr)
	{
		//lose
		ShowGameScoreWidgetLose();
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("lose"));

		GetWorld()->GetTimerManager().SetTimer(TimerHandle2, [&]()
			{
				ConsoleCommand("quit");
			}, 1.5, false);

	}

}

void AMyPlayerController::RemoveOrderWidget()
{
	//������� ����
	if (OrderWidget != nullptr)
	{
		OrderWidget->RemoveFromViewport();
	}
}

void AMyPlayerController::SetMyTurn(bool myturn)
{
	//call on my turn changed(bool MyTurn) ��������Ʈ ��Ƽĳ���� �Լ� broadcast���ֱ� --> hud������ your turn ǥ�����ִ°�
	OnPlayerTurnChanged.Broadcast(myturn);
	bEnableClickEvents = myturn;
}

void AMyPlayerController::InputLeftMouseButtonPressed()
{
	bClickLeftMouse = true;
}

void AMyPlayerController::InputLeftMouseButtonReleased()
{
	bClickLeftMouse = false;
}
