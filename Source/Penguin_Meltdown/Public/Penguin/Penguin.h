// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Penguin.generated.h"

UENUM(BlueprintType)
enum class EPenguinType : uint8
{
	Green 	UMETA(DisplayName = "Green"),
	Red 	UMETA(DisplayName = "Red"),
	Yellow	UMETA(DisplayName = "Yellow"),
	Blue	UMETA(DisplayName = "Blue")
};

UCLASS()
class PENGUIN_MELTDOWN_API APenguin : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APenguin();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TMap <USkeletalMesh*, UAnimationAsset*> PenguinMap;

	UPROPERTY(EditAnywhere)
		UMaterialInterface* GreenMaterial;

	UPROPERTY(EditAnywhere)
		UMaterialInterface* RedMaterial;

	UPROPERTY(EditAnywhere)
		UMaterialInterface* YellowMaterial;

	UPROPERTY(EditAnywhere)
		UMaterialInterface* BlueMaterial;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Get/Set for penguin type
	void SetPenguinType(EPenguinType Type);
	EPenguinType GetPenguinType();

	//Get/Set for polar take function
	bool IsPolarControlled();
	bool SetPolarControl(bool Control);

private:

	EPenguinType PenguinType = EPenguinType::Green;

	bool bIsPolarControl = false;

	class AIceland* CheckIcelandUnderPenguin();
};
