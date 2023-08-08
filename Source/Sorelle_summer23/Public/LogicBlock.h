// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include <string>
#include <map>
#include <vector>
#include "LogicBlock.generated.h"









struct Value
{
	int Type;//0=float, 1 = FString, 2 = vector

	float F = 0;
	FString S = "";
	FVector V = FVector(0, 0, 0);

public:
	Value(float f) { F = f; Type = 0; }
	Value(FString s) { S = s; Type = 1; }
	Value(FVector v) { V = v; Type = 2; }
};

USTRUCT(BlueprintType)
struct FInput
{
	GENERATED_BODY()
public:
	std::string ParamName;
	int Type = -1;
	FString StringValue;
	float FloatValue;
	FVector VectorValue;

	FInput(FString ParamName_, float f) { FloatValue = f; Type = 0; ParamName = ToString(ParamName_); }
	FInput(FString ParamName_, FString s) { StringValue = s; Type = 1; ParamName = ToString(ParamName_); }
	FInput(FString ParamName_, FVector v) { VectorValue = v; Type = 2; ParamName = ToString(ParamName_); }
	FInput() {}
	std::string ToString(FString S) { return std::string(TCHAR_TO_UTF8(*(S.ToUpper()))); }
};




/**
 * 
 */
UCLASS()
class SORELLE_SUMMER23_API ULogicBlock : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "LooiFunctions", meta = (AutoCreateRefTerm = "AddMoreInputs", AdvancedDisplay = "Input1,Input2,Input3,Input1Name,Input2Name,Input3Name,AddMoreInputs"))
		static TArray<FInput> LogicInputInt(
			FString Input1Name,
			int Input1,
			FString Input2Name,
			int Input2,
			FString Input3Name,
			int Input3,
			TArray<FInput> AddMoreInputs
		)
	{
		if (Input1Name != "")AddMoreInputs.Add(FInput(Input1Name, (float)Input1));
		if (Input2Name != "")AddMoreInputs.Add(FInput(Input2Name, (float)Input2));
		if (Input3Name != "")AddMoreInputs.Add(FInput(Input3Name, (float)Input3));
		return AddMoreInputs;
	}

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "LooiFunctions", meta = (AutoCreateRefTerm = "AddMoreInputs", AdvancedDisplay = "Input1,Input2,Input3,Input1Name,Input2Name,Input3Name,AddMoreInputs"))
		static TArray<FInput> LogicInputFloat(
			FString Input1Name,
			float Input1,
			FString Input2Name,
			float Input2,
			FString Input3Name,
			float Input3,
			TArray<FInput> AddMoreInputs
		)
	{
		if (Input1Name != "")AddMoreInputs.Add(FInput(Input1Name, Input1));
		if (Input2Name != "")AddMoreInputs.Add(FInput(Input2Name, Input2));
		if (Input3Name != "")AddMoreInputs.Add(FInput(Input3Name, Input3));
		return AddMoreInputs;
	}


	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "LooiFunctions", meta = (AutoCreateRefTerm = "AddMoreInputs", AdvancedDisplay = "Input1,Input2,Input3,Input1Name,Input2Name,Input3Name,AddMoreInputs"))
		static TArray<FInput> LogicInputVector(
			FString Input1Name,
			FVector Input1,
			FString Input2Name,
			FVector Input2,
			FString Input3Name,
			FVector Input3,
			TArray<FInput> AddMoreInputs
		)
	{
		if (Input1Name != "")AddMoreInputs.Add(FInput(Input1Name, Input1));
		if (Input2Name != "")AddMoreInputs.Add(FInput(Input2Name, Input2));
		if (Input3Name != "")AddMoreInputs.Add(FInput(Input3Name, Input3));
		return AddMoreInputs;
	}
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "LooiFunctions", meta = (AutoCreateRefTerm = "AddMoreInputs", AdvancedDisplay = "Input1,Input2,Input3,Input1Name,Input2Name,Input3Name,AddMoreInputs"))
		static TArray<FInput> LogicInputBool(
			FString Input1Name,
			bool Input1,
			FString Input2Name,
			bool Input2,
			FString Input3Name,
			bool Input3,
			TArray<FInput> AddMoreInputs
		)
	{
		if (Input1Name != "")AddMoreInputs.Add(FInput(Input1Name, Input1 ? 1 : 0));
		if (Input2Name != "")AddMoreInputs.Add(FInput(Input2Name, Input2 ? 1 : 0));
		if (Input3Name != "")AddMoreInputs.Add(FInput(Input3Name, Input3 ? 1 : 0));
		return AddMoreInputs;
	}

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "LooiFunctions", meta = (AutoCreateRefTerm = "AddMoreInputs", AdvancedDisplay = "Input1,Input2,Input3,Input1Name,Input2Name,Input3Name,AddMoreInputs"))
		static TArray<FInput> LogicInputString(
			FString Input1Name,
			FString Input1,
			FString Input2Name,
			FString Input2,
			FString Input3Name,
			FString Input3,
			TArray<FInput> AddMoreInputs
		)
	{
		if (Input1Name != "")AddMoreInputs.Add(FInput(Input1Name, Input1));
		if (Input2Name != "")AddMoreInputs.Add(FInput(Input2Name, Input2));
		if (Input3Name != "")AddMoreInputs.Add(FInput(Input3Name, Input3));
		return AddMoreInputs;
	}





	static std::string ToString(FString F);
	static Value LogicBlock(std::map<std::string, Value>* Variables, FString Code);

	static float AssertReturnTypeFloat(Value V)
	{
		if (V.Type != 0)
		{
			DisplayError("Code failed to return a float");
			return 0;
		}
		return V.F;
	}
	static FVector AssertReturnTypeVector(Value V)
	{
		if (V.Type != 2)
		{
			DisplayError("Code failed to return a vector");
			return FVector(0, 0, 0);
		}
		return V.V;
	}
	static FString AssertReturnTypeString(Value V)
	{
		if (V.Type != 1)
		{
			DisplayError("Code failed to return a string");
			return "";
		}
		return V.S;
	}




	static void DisplayError(std::string Str)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, Str.c_str());
	}



	static void AddInputsToVars(TArray<FInput> Inputs, std::map<std::string, Value>* Vars)
	{
		//DisplayError("number of inputs " + std::to_string(Inputs.Num()));
		for (FInput In : Inputs)
		{
			if (In.Type == 0) Vars->insert({ In.ParamName, Value(In.FloatValue) });
			else if (In.Type == 1)Vars->insert({ In.ParamName, Value(In.StringValue) });
			else if (In.Type == 2)Vars->insert({ In.ParamName, Value(In.VectorValue) });
			else
			{
				DisplayError("Unrecognized type");
			}
		}
	}



	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "LooiFunctions", meta = (CompactNodeTitle = "."))
		static float LogicFloat(FString Code, TArray<FInput> Inputs)
	{
		std::map<std::string, Value> Vars;
		AddInputsToVars(Inputs, &Vars);
		return AssertReturnTypeFloat(LogicBlock(&Vars, Code));
	}

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "LooiFunctions", meta = (CompactNodeTitle = "."))
		static bool LogicBool(FString Code, TArray<FInput> Inputs)
	{
		std::map<std::string, Value> Vars;
		AddInputsToVars(Inputs, &Vars);
		return AssertReturnTypeFloat(LogicBlock(&Vars, Code)) > .5;
	}


	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "LooiFunctions", meta = (CompactNodeTitle = "."))
		static FString LogicString(FString Code, TArray<FInput> Inputs)
	{
		std::map<std::string, Value> Vars;
		AddInputsToVars(Inputs, &Vars);
		return AssertReturnTypeString(LogicBlock(&Vars, Code));
	}




	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "LooiFunctions", meta = (CompactNodeTitle = "."))
		static FVector LogicVector(FString Code, TArray<FInput> Inputs)
	{
		std::map<std::string, Value> Vars;
		AddInputsToVars(Inputs, &Vars);
		return AssertReturnTypeVector(LogicBlock(&Vars, Code));
	}




	
};
