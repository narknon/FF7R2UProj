#pragma once

#include "CoreMinimal.h"
#include "Editor/UnrealEdEngine.h"
#include "ENDUnrealEdEngine.generated.h"

UCLASS(config=Engine, transient)
class ENDEDITOR_API UENDUnrealEdEngine : public UUnrealEdEngine
{
public:
	GENERATED_BODY()
	
	UENDUnrealEdEngine();
};