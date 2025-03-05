#include "HSFLipSyncEditorEdModeToolkit.h"
#include "HSFLipSyncEditorEdMode.h"
#include "Engine/Selection.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"
#include "EditorModeManager.h"
#include "JsonObjectConverter.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "HSFLipMapJSONStructures.h"
#include "DesktopPlatformModule.h"
#include <IDesktopPlatform.h>
#include "Engine/Selection.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"
#include "EditorModeManager.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Serialization/JsonSerializer.h"
#include "Dom/JsonObject.h"
#include "UObject/Package.h"
#include "UObject/SavePackage.h" // Include for FSavePackageArgs and Save package functionality
#include "AssetRegistry/AssetRegistryModule.h"


#define LOCTEXT_NAMESPACE "FHSFLipSyncEditorEdModeToolkit"

FHSFLipSyncEditorEdModeToolkit::FHSFLipSyncEditorEdModeToolkit()
{
}

void FHSFLipSyncEditorEdModeToolkit::Init(const TSharedPtr<IToolkitHost>& InitToolkitHost)
{
    struct Locals
    {
        // Open a file dialog for JSON using DesktopPlatformModule
        static bool OpenJsonFileDialog(FString& OutFilePath)
        {
            IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
            if (DesktopPlatform)
            {
                TArray<FString> OutFiles;
                const void* ParentWindowHandle = FSlateApplication::Get().FindBestParentWindowHandleForDialogs(nullptr);

                if (DesktopPlatform->OpenFileDialog(
                    ParentWindowHandle,
                    TEXT("Import HSFLipMap JSON"),
                    TEXT(""),
                    TEXT(""),
                    TEXT("JSON Files (*.json)|*.json"),
                    EFileDialogFlags::None,
                    OutFiles))
                {
                    OutFilePath = OutFiles[0];
                    return true;
                }
            }
            return false;
        }

        static void ReadKeyFrames(FHSFLipSyncDataKeyFrame& NewKeyFrame, TSharedPtr<FJsonObject> KeyFrameObject)
        {
            NewKeyFrame.Phoneme = FName(*KeyFrameObject->GetStringField(TEXT("Phoneme")));
            NewKeyFrame.StartTime = KeyFrameObject->GetNumberField(TEXT("StartTime"));
            NewKeyFrame.EndTime = KeyFrameObject->GetNumberField(TEXT("EndTime"));
            NewKeyFrame.Center = KeyFrameObject->GetNumberField(TEXT("Center"));
            NewKeyFrame.Power = KeyFrameObject->GetNumberField(TEXT("Power"));
            TArray<TSharedPtr<FJsonValue>> ShapesArray = KeyFrameObject->GetArrayField(TEXT("Shapes"));

            for (const auto& ShapesValue : ShapesArray)
            {
                TSharedPtr<FJsonObject> ShapesObject = ShapesValue->AsObject();
                float ShapesVal = ShapesObject->GetNumberField(TEXT("Value"));
                NewKeyFrame.Shapes.Add(FName(*ShapesObject->GetStringField(TEXT("Key"))), ShapesVal);
            }
        }
        static void ReadEmotions(FHSFLipSyncDataEmotion NewEmotion, TSharedPtr<FJsonObject> JsonObject)
        {
            NewEmotion.StartTime = JsonObject->GetNumberField(TEXT("StartTime"));
            NewEmotion.EndTime = JsonObject->GetNumberField(TEXT("EndTime"));
            NewEmotion.Calm = JsonObject->GetIntegerField(TEXT("Calm"));
            NewEmotion.Anger = JsonObject->GetIntegerField(TEXT("Anger"));
            NewEmotion.Joy = JsonObject->GetIntegerField(TEXT("Joy"));
            NewEmotion.Sorrow = JsonObject->GetIntegerField(TEXT("Sorrow"));
            NewEmotion.ExcitementLevel = JsonObject->GetIntegerField(TEXT("ExcitementLevel"));
        }
        static void ReadAttributes(FHSFLipMapShape& NewShape, TSharedPtr<FJsonObject> JsonObject)
        {
            // Process Attributes
            if (JsonObject->HasField(TEXT("Attributes")))
            {
                TArray<TSharedPtr<FJsonValue>> AttributesArray = JsonObject->GetArrayField(TEXT("Attributes"));
                for (const auto& AttributeValue : AttributesArray)
                {
                    TSharedPtr<FJsonObject> AttributeObject = AttributeValue->AsObject();
                    FHSFLipMapShapeAttribute NewAttribute;

                    TSharedPtr<FJsonObject> AttributeElement = AttributeObject->GetObjectField(TEXT("Value"));
                    if (AttributeElement->HasField(TEXT("Data")))
                    {
                        // Modify this block to map the Key to the correct AttributeType
                        TArray<TSharedPtr<FJsonValue>> DataArray = AttributeElement->GetArrayField(TEXT("Data"));
                        for (const auto& DataValue : DataArray)
                        {
                            TSharedPtr<FJsonObject> DataObject = DataValue->AsObject();

                            // Get the Key to determine the AttributeType
                            FString Key = DataObject->GetStringField(TEXT("Key"));

                            // Define a variable for the attribute type
                            EHSFLipMapShapeAttributeType AttributeType = EHSFLipMapShapeAttributeType::TranslateX; // Default

                            ReadAttributeType(AttributeType, Key);

                            // Now retrieve the associated value and add it to the attribute data
                            float DataVal = DataObject->GetNumberField(TEXT("Value"));
                            NewAttribute.Data.Add(AttributeType, DataVal);
                        }

                    }

                    // Add the attribute to shape
                    NewShape.Attributes.Add(FName(*AttributeObject->GetStringField(TEXT("Key"))), NewAttribute);
                }
            }
        }

        static void ReadAttributeType(EHSFLipMapShapeAttributeType& AttributeType, FString Key)
        {
            // Map the Key to the appropriate AttributeType
            if (Key.Equals(TEXT("EHSFLipMapShapeAttributeType::TranslateX")))
            {
                AttributeType = EHSFLipMapShapeAttributeType::TranslateX;
            }
            else if (Key.Equals(TEXT("EHSFLipMapShapeAttributeType::TranslateY")))
            {
                AttributeType = EHSFLipMapShapeAttributeType::TranslateY;
            }
            else if (Key.Equals(TEXT("EHSFLipMapShapeAttributeType::TranslateZ")))
            {
                AttributeType = EHSFLipMapShapeAttributeType::TranslateZ;
            }
            else if (Key.Equals(TEXT("EHSFLipMapShapeAttributeType::RotateX")))
            {
                AttributeType = EHSFLipMapShapeAttributeType::RotateX;
            }
            else if (Key.Equals(TEXT("EHSFLipMapShapeAttributeType::RotateY")))
            {
                AttributeType = EHSFLipMapShapeAttributeType::RotateY;
            }
            else if (Key.Equals(TEXT("EHSFLipMapShapeAttributeType::RotateZ")))
            {
                AttributeType = EHSFLipMapShapeAttributeType::RotateZ;
            }
            else if (Key.Equals(TEXT("EHSFLipMapShapeAttributeType::ScaleX")))
            {
                AttributeType = EHSFLipMapShapeAttributeType::ScaleX;
            }
            else if (Key.Equals(TEXT("EHSFLipMapShapeAttributeType::ScaleY")))
            {
                AttributeType = EHSFLipMapShapeAttributeType::ScaleY;
            }
            else if (Key.Equals(TEXT("EHSFLipMapShapeAttributeType::ScaleZ")))
            {
                AttributeType = EHSFLipMapShapeAttributeType::ScaleZ;
            }
            else
            {
                // Log a warning if the Key doesn't match any known type
                UE_LOG(LogTemp, Warning, TEXT("Unknown attribute key: %s"), *Key);
            }
        }

        static void ReadAudioData(FHSFLipMapShape& NewShape, TSharedPtr<FJsonObject> JsonObject)
        {
            if (JsonObject->HasField(TEXT("AudioMin")))
                NewShape.AudioMin = JsonObject->GetNumberField(TEXT("AudioMin"));
            if (JsonObject->HasField(TEXT("AudioMax")))
                NewShape.AudioMax = JsonObject->GetNumberField(TEXT("AudioMax"));
            if (JsonObject->HasField(TEXT("AudioPower")))
                NewShape.AudioPower = JsonObject->GetNumberField(TEXT("AudioPower"));
            if (JsonObject->HasField(TEXT("bBlend")))
                NewShape.bBlend = JsonObject->GetBoolField(TEXT("bBlend"));
            if (JsonObject->HasField(TEXT("BlendIn")))
                NewShape.BlendIn = JsonObject->GetNumberField(TEXT("BlendIn"));
            if (JsonObject->HasField(TEXT("BlendOut")))
                NewShape.BlendOut = JsonObject->GetNumberField(TEXT("BlendOut"));
            if (JsonObject->HasField(TEXT("bRandomize")))
                NewShape.bRandomize = JsonObject->GetBoolField(TEXT("bRandomize"));
            if (JsonObject->HasField(TEXT("RandomMin")))
                NewShape.RandomMin = JsonObject->GetNumberField(TEXT("RandomMin"));
            if (JsonObject->HasField(TEXT("RandomMax")))
                NewShape.RandomMax = JsonObject->GetNumberField(TEXT("RandomMax"));
        }
        // Parse the JSON array from a file path
        static bool ParseJsonArrayFromFile(const FString& FilePath, TArray<TSharedPtr<FJsonObject>>& JsonArray)
        {
            FString JsonString;
            if (FFileHelper::LoadFileToString(JsonString, *FilePath))
            {
                if (JsonString.IsEmpty())
                {
                    UE_LOG(LogTemp, Error, TEXT("Failed to load JSON file: The content is empty."));
                    return false;
                }

                // Try to deserialize the JSON array
                TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonString);
                TArray<TSharedPtr<FJsonValue>> JsonValueArray;
                if (FJsonSerializer::Deserialize(JsonReader, JsonValueArray))
                {
                    for (const TSharedPtr<FJsonValue>& Value : JsonValueArray)
                    {
                        if (Value->Type == EJson::Object)
                        {
                            JsonArray.Add(Value->AsObject());
                        }
                    }
                    UE_LOG(LogTemp, Log, TEXT("JSON array deserialized successfully."));
                    return true;
                }
                else
                {
                    // Log the error if deserialization fails
                    UE_LOG(LogTemp, Error, TEXT("Failed to deserialize JSON array."));
                }
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("Failed to load JSON file from path: %s"), *FilePath);
            }

            return false;
        }

        // Button handler to create the asset from parsed JSON using the factory
        static FReply OnCreateHSFMapButtonClicked()
        {
            // Open the JSON file dialog
            FString FilePath;
            if (!OpenJsonFileDialog(FilePath))
            {
                return FReply::Handled();
            }

            TArray<TSharedPtr<FJsonObject>> ParsedJsonArray;
            if (ParseJsonArrayFromFile(FilePath, ParsedJsonArray))
            {
                // Process each HSFLipMap
                for (const TSharedPtr<FJsonObject>& JsonObject : ParsedJsonArray)
                {
                    FString AssetName = JsonObject->GetStringField(TEXT("Name"));
                    FString PackagePath = TEXT("/Game/LipSync/LipMap/") / AssetName ;
                    FString AssetPath = TEXT("/Game/LipSync/LipMap/");

                    UPackage* NewPackage = CreatePackage(*PackagePath);

                    // Use the factory to create the asset
                    UHSFLipMapFactory* Factory = NewObject<UHSFLipMapFactory>();
                    UHSFLipMap* NewAsset = Cast<UHSFLipMap>(Factory->FactoryCreateNew(UHSFLipMap::StaticClass(), NewPackage, FName(*AssetName), RF_Standalone | RF_Public, nullptr, GWarn));

                    // Populate the asset with data from JSON
                    TSharedPtr<FJsonObject> Properties = JsonObject->GetObjectField(TEXT("Properties"));
                    NewAsset->Version = FName(*Properties->GetStringField(TEXT("version")));

                    // Process Shapes
                    if (Properties->HasField(TEXT("Shapes")))
                    {
                        TArray<TSharedPtr<FJsonValue>> ShapesArray = Properties->GetArrayField(TEXT("Shapes"));
                        for (const auto& ShapeValue : ShapesArray)
                        {
                            TSharedPtr<FJsonObject> ShapeObject = ShapeValue->AsObject();


                            TSharedPtr<FJsonObject> ShapeElement = ShapeObject->GetObjectField(TEXT("Value"));

                            FHSFLipMapShape NewShape;
                            ReadAttributes(NewShape, ShapeElement);
                            ReadAudioData(NewShape, ShapeElement);

                            // Add the shape to the map in the asset
                            NewAsset->Shapes.Add(FName(*ShapeObject->GetStringField(TEXT("Key"))), NewShape);
                        }
                    }

                    // Process Shapes
                    if (Properties->HasField(TEXT("DefaultShape")))
                    {
                        TSharedPtr<FJsonObject> DefaultShapeObject = Properties->GetObjectField(TEXT("DefaultShape"));
                        FHSFLipMapShape NewShape;
                        ReadAttributes(NewShape, DefaultShapeObject);
                        ReadAudioData(NewShape, DefaultShapeObject);

                        // Add the shape to the map in the asset
                        NewAsset->DefaultShape = NewShape;
                    }

                    // Process Shapes
                    if (Properties->HasField(TEXT("MaxDifferenceShape")))
                    {
                        TSharedPtr<FJsonObject> MaxDifferenceShape = Properties->GetObjectField(TEXT("MaxDifferenceShape"));
                        FHSFLipMapShape NewShape;
                        ReadAttributes(NewShape, MaxDifferenceShape);
                        ReadAudioData(NewShape, MaxDifferenceShape);

                        // Add the shape to the map in the asset
                        NewAsset->MaxDifferenceShape = NewShape;
                    }

                    NewAsset->MarkPackageDirty();
                    NewPackage->SetDirtyFlag(true);


                    FAssetRegistryModule::AssetCreated(NewAsset);	

                    FString FilePathDest = FString::Printf(TEXT("%s%s%s"), *AssetPath, *FString(*AssetName), *FPackageName::GetAssetPackageExtension());
                    //bool bSuccess = UPackage::SavePackage(NewPackage, NewAsset, EObjectFlags::RF_Public | EObjectFlags::RF_Standalone, *FilePathDest);

                    //UE_LOG(LogTemp, Warning, TEXT("Saved Package: %s"), bSuccess ? TEXT("True") : TEXT("False"));
                }
            }

            return FReply::Handled();
        }static FReply OnCreateHSFPackButtonClicked()
        {
            // Open the JSON file dialog
            FString FilePath;
            if (!OpenJsonFileDialog(FilePath))
            {
                return FReply::Handled();
            }

            TArray<TSharedPtr<FJsonObject>> ParsedJsonArray;
            if (ParseJsonArrayFromFile(FilePath, ParsedJsonArray))
            {
                // Process each HSFLipMap
                for (const TSharedPtr<FJsonObject>& JsonObject : ParsedJsonArray)
                {
                    FString AssetName = JsonObject->GetStringField(TEXT("Name"));
                    FString PackagePath = TEXT("/Game/LipSync/Lsd/") / AssetName;
                    FString AssetPath = TEXT("/Game/LipSync/Lsd/");

                    UPackage* NewPackage = CreatePackage(*PackagePath);

                    // Use the factory to create the asset
                    UHSFLipSyncDataPackFactory* Factory = NewObject<UHSFLipSyncDataPackFactory>();
                    UHSFLipSyncDataPack* NewAsset = Cast<UHSFLipSyncDataPack>(Factory->FactoryCreateNew(UHSFLipSyncDataPack::StaticClass(), NewPackage, FName(*AssetName), RF_Standalone | RF_Public, nullptr, GWarn));

                    // Populate the asset with data from JSON
                    TSharedPtr<FJsonObject> Properties = JsonObject->GetObjectField(TEXT("Properties"));

                    // Process Shapes
                    if (Properties->HasField(TEXT("Data")))
                    {
                        TArray<TSharedPtr<FJsonValue>> DataArray = Properties->GetArrayField(TEXT("Data"));
                        for (const auto& DataValue : DataArray)
                        {
                            TSharedPtr<FJsonObject> DataObject = DataValue->AsObject();
                            TSharedPtr<FJsonObject> DataElement = DataObject->GetObjectField(TEXT("Value"));
                            FHSFLipSyncData NewData;
                            
                            //Read File Info
                            if (DataElement->HasField(TEXT("Info")))
                            {
                                FHSFLipSyncDataInfo NewDataInfo;
                                TSharedPtr<FJsonObject> InfoObject = DataElement->GetObjectField(TEXT("Info"));
                                NewDataInfo.Version = FName(*InfoObject->GetStringField(TEXT("version")));
                                NewDataInfo.AudioLength = InfoObject->GetNumberField(TEXT("AudioLength"));
                                NewDataInfo.AvgAudioPower = InfoObject->GetNumberField(TEXT("AvgAudioPower"));
                                NewDataInfo.MaxAudioPower = InfoObject->GetNumberField(TEXT("MaxAudioPower"));
                                TArray<TSharedPtr<FJsonValue>> KeyOrderArray = InfoObject->GetArrayField(TEXT("KeyOrder"));

                                for (const auto& KeyOrderValue : KeyOrderArray)
                                    NewDataInfo.KeyOrder.Add(FName(KeyOrderValue->AsString()));

                                NewData.Info = NewDataInfo;
                            }
                            //Read KeyFrame Data
                            if (DataElement->HasField(TEXT("KeyFrames")))
                            {
                                TArray<FHSFLipSyncDataKeyFrame> NewKeyFrameData;
                                TArray<TSharedPtr<FJsonValue>> KeyFrameArray = DataElement->GetArrayField(TEXT("KeyFrames"));

                                for (const auto& KeyFrameValue : KeyFrameArray)
                                {
                                    FHSFLipSyncDataKeyFrame NewKeyFrame;
                                    TSharedPtr<FJsonObject> KeyFrameObject = KeyFrameValue->AsObject();

                                    ReadKeyFrames(NewKeyFrame, KeyFrameObject);

                                    NewKeyFrameData.Add(NewKeyFrame);
                                }


                                NewData.KeyFrames = NewKeyFrameData;
                            }
                            //Read KeyFrame Data
                            if (DataElement->HasField(TEXT("OverrideKeyFrames")))
                            {
                                TArray<FHSFLipSyncDataKeyFrame> NewKeyFrameData;
                                TArray<TSharedPtr<FJsonValue>> KeyFrameArray = DataElement->GetArrayField(TEXT("OverrideKeyFrames"));

                                for (const auto& KeyFrameValue : KeyFrameArray)
                                {
                                    FHSFLipSyncDataKeyFrame NewKeyFrame;
                                    TSharedPtr<FJsonObject> KeyFrameObject = KeyFrameValue->AsObject();

                                    ReadKeyFrames(NewKeyFrame, KeyFrameObject);

                                    NewKeyFrameData.Add(NewKeyFrame);
                                }


                                NewData.OverrideKeyFrames = NewKeyFrameData;
                            }
                            //Read Emotions Data
                            if (DataElement->HasField(TEXT("Emotions")))
                            {
                                TArray<FHSFLipSyncDataEmotion> NewEmotionsData;
                                TArray<TSharedPtr<FJsonValue>> EmotionArray = DataElement->GetArrayField(TEXT("Emotions"));

                                for (const auto& EmotionValue : EmotionArray)
                                {
                                    FHSFLipSyncDataEmotion NewEmotion;
                                    TSharedPtr<FJsonObject> EmotionObject = EmotionValue->AsObject();

                                    ReadEmotions(NewEmotion, EmotionObject);

                                    NewEmotionsData.Add(NewEmotion);
                                }


                                NewData.Emotions = NewEmotionsData;
                            }
                            //Read JpOverrideEmotions Data --- Remake only
                            /*if (DataElement->HasField(TEXT("JpOverrideEmotions")))
                            {
                                TArray<FHSFLipSyncDataEmotion> NewEmotionsData;
                                TArray<TSharedPtr<FJsonValue>> EmotionArray = DataElement->GetArrayField(TEXT("JpOverrideEmotions"));

                                for (const auto& EmotionValue : EmotionArray)
                                {
                                    FHSFLipSyncDataEmotion NewEmotion;
                                    TSharedPtr<FJsonObject> EmotionObject = EmotionValue->AsObject();

                                    ReadEmotions(NewEmotion, EmotionObject);

                                    NewEmotionsData.Add(NewEmotion);
                                }


                                NewData.JpOverrideEmotions = NewEmotionsData;
                            }*/
                            //Read JpOverrideEmotions Data
                            if (DataElement->HasField(TEXT("OverrideEmotions")))
                            {
                                TArray<FHSFLipSyncDataEmotion> NewEmotionsData;
                                TArray<TSharedPtr<FJsonValue>> EmotionArray = DataElement->GetArrayField(TEXT("OverrideEmotions"));

                                for (const auto& EmotionValue : EmotionArray)
                                {
                                    FHSFLipSyncDataEmotion NewEmotion;
                                    TSharedPtr<FJsonObject> EmotionObject = EmotionValue->AsObject();

                                    ReadEmotions(NewEmotion, EmotionObject);

                                    NewEmotionsData.Add(NewEmotion);
                                }


                                NewData.OverrideEmotions = NewEmotionsData;
                            }
                            // Add the shape to the map in the asset
                            NewAsset->Data.Add(FName(*DataObject->GetStringField(TEXT("Key"))), NewData);
                        }
                    }


                    NewAsset->MarkPackageDirty();
                    NewPackage->SetDirtyFlag(true);


                    FAssetRegistryModule::AssetCreated(NewAsset);

                    FString FilePathDest = FString::Printf(TEXT("%s%s%s"), *AssetPath, *FString(*AssetName), *FPackageName::GetAssetPackageExtension());
                    //bool bSuccess = UPackage::SavePackage(NewPackage, NewAsset, EObjectFlags::RF_Public | EObjectFlags::RF_Standalone, *FilePathDest);

                    //UE_LOG(LogTemp, Warning, TEXT("Saved Package: %s"), bSuccess ? TEXT("True") : TEXT("False"));
                }
            }

            return FReply::Handled();
        }

        // Utility function to create the button
        static TSharedRef<SWidget> CreateHSFMapAssetButton()
        {
            return SNew(SButton)
                .Text(LOCTEXT("CreateAssetButton", "Create HSF Map from JSON"))
                .OnClicked_Static(&Locals::OnCreateHSFMapButtonClicked);
        }
        static TSharedRef<SWidget> CreateHSFPackAssetButton()
        {
            return SNew(SButton)
                .Text(LOCTEXT("CreateAssetButton", "Create HSF Pack from JSON"))
                .OnClicked_Static(&Locals::OnCreateHSFPackButtonClicked);
        }
    };

    const float Factor = 256.0f;

    SAssignNew(ToolkitWidget, SBorder)
        .HAlign(HAlign_Center)
        .Padding(25)
        [
            SNew(SVerticalBox)
                + SVerticalBox::Slot()
                .AutoHeight()
                .HAlign(HAlign_Center)
                .Padding(50)
                [
                    SNew(STextBlock)
                        .AutoWrapText(true)
                        .Text(LOCTEXT("HelperLabel", "Select a JSON file to create the HSF Map asset"))
                ]
                + SVerticalBox::Slot()
                .HAlign(HAlign_Center)
                .AutoHeight()
                [
                    Locals::CreateHSFMapAssetButton()
                ]

                + SVerticalBox::Slot()
                .AutoHeight()
                .HAlign(HAlign_Center)
                .Padding(50)
                [
                    SNew(STextBlock)
                        .AutoWrapText(true)
                        .Text(LOCTEXT("HelperLabel", "Select a JSON file to create HSF Data Pack the asset"))
                ]
                + SVerticalBox::Slot()
                .HAlign(HAlign_Center)
                .AutoHeight()
                [
                    Locals::CreateHSFPackAssetButton()
                ]

        ];

    FModeToolkit::Init(InitToolkitHost);
}

FName FHSFLipSyncEditorEdModeToolkit::GetToolkitFName() const
{
    return FName("HSF LipSync");
}

FText FHSFLipSyncEditorEdModeToolkit::GetBaseToolkitName() const
{
    return NSLOCTEXT("HSFLipSyncEditorEdModeToolkit", "DisplayName", "HSF LipSync Tool");
}

class FEdMode* FHSFLipSyncEditorEdModeToolkit::GetEditorMode() const
{
    return GLevelEditorModeTools().GetActiveMode(FHSFLipSyncEditorEdMode::EM_HSFLipSyncEditorEdModeId);
}

#undef LOCTEXT_NAMESPACE
