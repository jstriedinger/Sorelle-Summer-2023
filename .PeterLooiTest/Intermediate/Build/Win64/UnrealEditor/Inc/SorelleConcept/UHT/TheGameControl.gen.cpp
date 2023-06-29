// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SorelleConcept/TheGameControl.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTheGameControl() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	SORELLECONCEPT_API UClass* Z_Construct_UClass_APlayerView_NoRegister();
	SORELLECONCEPT_API UClass* Z_Construct_UClass_ATheGameControl();
	SORELLECONCEPT_API UClass* Z_Construct_UClass_ATheGameControl_NoRegister();
	UPackage* Z_Construct_UPackage__Script_SorelleConcept();
// End Cross Module References
	void ATheGameControl::StaticRegisterNativesATheGameControl()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ATheGameControl);
	UClass* Z_Construct_UClass_ATheGameControl_NoRegister()
	{
		return ATheGameControl::StaticClass();
	}
	struct Z_Construct_UClass_ATheGameControl_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_pv_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_pv;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ATheGameControl_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_SorelleConcept,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATheGameControl_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "TheGameControl.h" },
		{ "ModuleRelativePath", "TheGameControl.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATheGameControl_Statics::NewProp_pv_MetaData[] = {
		{ "Category", "TheGameControl" },
		{ "ModuleRelativePath", "TheGameControl.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ATheGameControl_Statics::NewProp_pv = { "pv", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(ATheGameControl, pv), Z_Construct_UClass_APlayerView_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ATheGameControl_Statics::NewProp_pv_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ATheGameControl_Statics::NewProp_pv_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ATheGameControl_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATheGameControl_Statics::NewProp_pv,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ATheGameControl_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ATheGameControl>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ATheGameControl_Statics::ClassParams = {
		&ATheGameControl::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_ATheGameControl_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_ATheGameControl_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_ATheGameControl_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ATheGameControl_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ATheGameControl()
	{
		if (!Z_Registration_Info_UClass_ATheGameControl.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ATheGameControl.OuterSingleton, Z_Construct_UClass_ATheGameControl_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ATheGameControl.OuterSingleton;
	}
	template<> SORELLECONCEPT_API UClass* StaticClass<ATheGameControl>()
	{
		return ATheGameControl::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ATheGameControl);
	ATheGameControl::~ATheGameControl() {}
	struct Z_CompiledInDeferFile_FID_Users_peter_Documents_Unreal_Projects_SorelleConcept_Source_SorelleConcept_TheGameControl_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_peter_Documents_Unreal_Projects_SorelleConcept_Source_SorelleConcept_TheGameControl_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ATheGameControl, ATheGameControl::StaticClass, TEXT("ATheGameControl"), &Z_Registration_Info_UClass_ATheGameControl, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ATheGameControl), 2357668840U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_peter_Documents_Unreal_Projects_SorelleConcept_Source_SorelleConcept_TheGameControl_h_215318243(TEXT("/Script/SorelleConcept"),
		Z_CompiledInDeferFile_FID_Users_peter_Documents_Unreal_Projects_SorelleConcept_Source_SorelleConcept_TheGameControl_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_peter_Documents_Unreal_Projects_SorelleConcept_Source_SorelleConcept_TheGameControl_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
