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

	//명령wiget 위젯클래스에 불러오기
	static ConstructorHelpers::FClassFinder<UOrderWidget> OrderWidget_C(TEXT("/Game/UI/BP_ORDERWidget"));
	if (OrderWidget_C.Succeeded())
	{
		OrderWidgetClass = OrderWidget_C.Class;
	}

	//HUDwidget 위젯클래스에 불러오기
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

	//화면에 HUD위젯 보여주기
	CurrentWidget = CreateWidget<UHUDWidget>(GetWorld(), HUDWidget);
	CurrentWidget->AddToViewport();

	//state와 현재hud위젯과 바인딩해주기
	auto MyPlayerState = Cast<AMyPlayerState>(PlayerState);
	CurrentWidget->BindPlayerState(MyPlayerState);
	MyPlayerState->OnPlayerStateChanged.Broadcast();

	//playercontroller 의 myturn 와 현재 hud위젯과 바인딩 해주기
	CurrentWidget->BindPlayerTurnState(this);

	//playerstate 랑 basic_rr 바인딩해주기
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

//마우스 프레스,릴리스 함수랑 바인딩
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

//현재RR을 이동시킨다
void AMyPlayerController::MoveRR(FVector2D MouseDelta)
{
	
	FVector MouseDeltaDirection(MouseDelta.Y, -MouseDelta.X, 0);
	FVector Force = FVector(-MouseDeltaDirection.X, -MouseDeltaDirection.Y, 0.0f).GetSafeNormal() * MouseDelta.Size()*10;
	auto currentRR2 = Cast<ABasic_RR>(GetPawn());
	currentRR2->MoveThisRR(Force);
	
	//movementmanager 스폰해서 움직임 멈추면 CycleTurn()
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

	//명령위젯 제거
	RemoveOrderWidget();

	//게임스코어 확인 함수실행
	CheckGameScore();
}

void AMyPlayerController::CheckGameScore()
{
	FTimerHandle TimerHandle2;
	//나의 폰 가져와서 null이면 lose 화면 
	if (UGameplayStatics::GetActorOfClass(GetWorld(), ABasic_RR::StaticClass()) == nullptr && UGameplayStatics::GetActorOfClass(GetWorld(), AAI_RR::StaticClass()) == nullptr)
	{
		//무승부
		ShowGameScoreWidgetDraw();

		GetWorld()->GetTimerManager().SetTimer(TimerHandle2, [&]()
			{
				ConsoleCommand("quit");
			}, 1.5, false);
	}
	if (UGameplayStatics::GetActorOfClass(GetWorld(), ABasic_RR::StaticClass()) != nullptr && UGameplayStatics::GetActorOfClass(GetWorld(), AAI_RR::StaticClass()) == nullptr)
	{
		//win 출력
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
	//명령위젯 제거
	if (OrderWidget != nullptr)
	{
		OrderWidget->RemoveFromViewport();
	}
}

void AMyPlayerController::SetMyTurn(bool myturn)
{
	//call on my turn changed(bool MyTurn) 델리게이트 멀티캐스팅 함수 broadcast해주기 --> hud위젯에 your turn 표시해주는것
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
