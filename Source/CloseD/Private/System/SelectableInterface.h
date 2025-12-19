// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SelectableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USelectableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ISelectableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
    // 선택 됨
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void OnSelected();

    // 선택 해제
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void OnDeselected();

    // 선택 가능 여부
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    bool IsSelectable() const;

};
