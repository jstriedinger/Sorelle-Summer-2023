// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SorelleConcept/SceneObject.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSceneObject() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	SORELLECONCEPT_API UClass* Z_Construct_UClass_ASceneObject();
	SORELLECONCEPT_API UClass* Z_Construct_UClass_ASceneObject_NoRegister();
	UPackage* Z_Construct_UPackage__Script_SorelleConcept();
// End Cross Module References
	void ASceneObject::StaticRegisterNativesASceneObject()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ASceneObject);
	UClass* Z_Construct_UClass_ASceneObject_NoRegister()
	{
		return ASceneObject::StaticClass();
	}
	struct Z_Construct_UClass_ASceneObject_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ASceneObject_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_SorelleConcept,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASceneObject_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "SceneObject.h" },
		{ "ModuleRelativePath", "SceneObject.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ASceneObject_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASceneObject>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ASceneObject_Statics::ClassParams = {
		&ASceneObject::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_ASceneObject_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ASceneObject_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ASceneObject()
	{
		if (!Z_Registration_Info_UClass_ASceneObject.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ASceneObject.OuterSingleton, Z_Construct_UClass_ASceneObject_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ASceneObject.OuterSingleton;
	}
	template<> SORELLECONCEPT_API UClass* StaticClass<ASceneObject>()
	{
		return ASceneObject::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ASceneObject);
	ASceneObject::~ASceneObject() {}
	struct Z_CompiledInDeferFile_FID_Users_peter_Documents_Unreal_Projects_SorelleConcept_Source_SorelleConcept_SceneObject_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_peter_Documents_Unreal_Projects_SorelleConcept_Source_SorelleConcept_SceneObject_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ASceneObject, ASceneObject::StaticClass, TEXT("ASceneObject"), &Z_Registration_Info_UClass_ASceneObject, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ASceneObject), 481193302U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_peter_Documents_Unreal_Projects_SorelleConcept_Source_SorelleConcept_SceneObject_h_64781780(TEXT("/Script/SorelleConcept"),
		Z_CompiledInDeferFile_FID_Users_peter_Documents_Unreal_Projects_SorelleConcept_Source_SorelleConcept_SceneObject_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_peter_Documents_Unreal_Projects_SorelleConcept_Source_SorelleConcept_SceneObject_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
