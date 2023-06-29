// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SorelleConcept/SorelleConceptGameModeBase.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSorelleConceptGameModeBase() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	SORELLECONCEPT_API UClass* Z_Construct_UClass_ASorelleConceptGameModeBase();
	SORELLECONCEPT_API UClass* Z_Construct_UClass_ASorelleConceptGameModeBase_NoRegister();
	UPackage* Z_Construct_UPackage__Script_SorelleConcept();
// End Cross Module References
	void ASorelleConceptGameModeBase::StaticRegisterNativesASorelleConceptGameModeBase()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ASorelleConceptGameModeBase);
	UClass* Z_Construct_UClass_ASorelleConceptGameModeBase_NoRegister()
	{
		return ASorelleConceptGameModeBase::StaticClass();
	}
	struct Z_Construct_UClass_ASorelleConceptGameModeBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ASorelleConceptGameModeBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_SorelleConcept,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASorelleConceptGameModeBase_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "SorelleConceptGameModeBase.h" },
		{ "ModuleRelativePath", "SorelleConceptGameModeBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ASorelleConceptGameModeBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASorelleConceptGameModeBase>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ASorelleConceptGameModeBase_Statics::ClassParams = {
		&ASorelleConceptGameModeBase::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009002ACu,
		METADATA_PARAMS(Z_Construct_UClass_ASorelleConceptGameModeBase_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ASorelleConceptGameModeBase_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ASorelleConceptGameModeBase()
	{
		if (!Z_Registration_Info_UClass_ASorelleConceptGameModeBase.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ASorelleConceptGameModeBase.OuterSingleton, Z_Construct_UClass_ASorelleConceptGameModeBase_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ASorelleConceptGameModeBase.OuterSingleton;
	}
	template<> SORELLECONCEPT_API UClass* StaticClass<ASorelleConceptGameModeBase>()
	{
		return ASorelleConceptGameModeBase::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ASorelleConceptGameModeBase);
	ASorelleConceptGameModeBase::~ASorelleConceptGameModeBase() {}
	struct Z_CompiledInDeferFile_FID_Users_peter_Documents_Unreal_Projects_SorelleConcept_Source_SorelleConcept_SorelleConceptGameModeBase_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_peter_Documents_Unreal_Projects_SorelleConcept_Source_SorelleConcept_SorelleConceptGameModeBase_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ASorelleConceptGameModeBase, ASorelleConceptGameModeBase::StaticClass, TEXT("ASorelleConceptGameModeBase"), &Z_Registration_Info_UClass_ASorelleConceptGameModeBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ASorelleConceptGameModeBase), 1599306552U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_peter_Documents_Unreal_Projects_SorelleConcept_Source_SorelleConcept_SorelleConceptGameModeBase_h_1664633054(TEXT("/Script/SorelleConcept"),
		Z_CompiledInDeferFile_FID_Users_peter_Documents_Unreal_Projects_SorelleConcept_Source_SorelleConcept_SorelleConceptGameModeBase_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_peter_Documents_Unreal_Projects_SorelleConcept_Source_SorelleConcept_SorelleConceptGameModeBase_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
