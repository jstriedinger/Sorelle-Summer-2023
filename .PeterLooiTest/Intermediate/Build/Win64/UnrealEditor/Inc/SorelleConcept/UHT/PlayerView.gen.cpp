// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SorelleConcept/PlayerView.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodePlayerView() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_APawn();
	ENGINE_API UClass* Z_Construct_UClass_UCameraComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UMaterial_NoRegister();
	SORELLECONCEPT_API UClass* Z_Construct_UClass_APlayerView();
	SORELLECONCEPT_API UClass* Z_Construct_UClass_APlayerView_NoRegister();
	UPackage* Z_Construct_UPackage__Script_SorelleConcept();
// End Cross Module References
	void APlayerView::StaticRegisterNativesAPlayerView()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(APlayerView);
	UClass* Z_Construct_UClass_APlayerView_NoRegister()
	{
		return APlayerView::StaticClass();
	}
	struct Z_Construct_UClass_APlayerView_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_camera_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_camera;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_sisterAMat_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_sisterAMat;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_sisterBMat_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_sisterBMat;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_sisterCMat_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_sisterCMat;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_APlayerView_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_APawn,
		(UObject* (*)())Z_Construct_UPackage__Script_SorelleConcept,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_APlayerView_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "PlayerView.h" },
		{ "ModuleRelativePath", "PlayerView.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_APlayerView_Statics::NewProp_camera_MetaData[] = {
		{ "Category", "PlayerView" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "PlayerView.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APlayerView_Statics::NewProp_camera = { "camera", nullptr, (EPropertyFlags)0x0020080000080009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(APlayerView, camera), Z_Construct_UClass_UCameraComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_APlayerView_Statics::NewProp_camera_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_APlayerView_Statics::NewProp_camera_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_APlayerView_Statics::NewProp_sisterAMat_MetaData[] = {
		{ "Category", "PlayerView" },
		{ "ModuleRelativePath", "PlayerView.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APlayerView_Statics::NewProp_sisterAMat = { "sisterAMat", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(APlayerView, sisterAMat), Z_Construct_UClass_UMaterial_NoRegister, METADATA_PARAMS(Z_Construct_UClass_APlayerView_Statics::NewProp_sisterAMat_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_APlayerView_Statics::NewProp_sisterAMat_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_APlayerView_Statics::NewProp_sisterBMat_MetaData[] = {
		{ "Category", "PlayerView" },
		{ "ModuleRelativePath", "PlayerView.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APlayerView_Statics::NewProp_sisterBMat = { "sisterBMat", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(APlayerView, sisterBMat), Z_Construct_UClass_UMaterial_NoRegister, METADATA_PARAMS(Z_Construct_UClass_APlayerView_Statics::NewProp_sisterBMat_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_APlayerView_Statics::NewProp_sisterBMat_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_APlayerView_Statics::NewProp_sisterCMat_MetaData[] = {
		{ "Category", "PlayerView" },
		{ "ModuleRelativePath", "PlayerView.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APlayerView_Statics::NewProp_sisterCMat = { "sisterCMat", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(APlayerView, sisterCMat), Z_Construct_UClass_UMaterial_NoRegister, METADATA_PARAMS(Z_Construct_UClass_APlayerView_Statics::NewProp_sisterCMat_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_APlayerView_Statics::NewProp_sisterCMat_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_APlayerView_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlayerView_Statics::NewProp_camera,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlayerView_Statics::NewProp_sisterAMat,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlayerView_Statics::NewProp_sisterBMat,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlayerView_Statics::NewProp_sisterCMat,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_APlayerView_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<APlayerView>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_APlayerView_Statics::ClassParams = {
		&APlayerView::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_APlayerView_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_APlayerView_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_APlayerView_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_APlayerView_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_APlayerView()
	{
		if (!Z_Registration_Info_UClass_APlayerView.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_APlayerView.OuterSingleton, Z_Construct_UClass_APlayerView_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_APlayerView.OuterSingleton;
	}
	template<> SORELLECONCEPT_API UClass* StaticClass<APlayerView>()
	{
		return APlayerView::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(APlayerView);
	APlayerView::~APlayerView() {}
	struct Z_CompiledInDeferFile_FID_Users_peter_Documents_Unreal_Projects_SorelleConcept_Source_SorelleConcept_PlayerView_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_peter_Documents_Unreal_Projects_SorelleConcept_Source_SorelleConcept_PlayerView_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_APlayerView, APlayerView::StaticClass, TEXT("APlayerView"), &Z_Registration_Info_UClass_APlayerView, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(APlayerView), 598292873U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_peter_Documents_Unreal_Projects_SorelleConcept_Source_SorelleConcept_PlayerView_h_3359626963(TEXT("/Script/SorelleConcept"),
		Z_CompiledInDeferFile_FID_Users_peter_Documents_Unreal_Projects_SorelleConcept_Source_SorelleConcept_PlayerView_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_peter_Documents_Unreal_Projects_SorelleConcept_Source_SorelleConcept_PlayerView_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
