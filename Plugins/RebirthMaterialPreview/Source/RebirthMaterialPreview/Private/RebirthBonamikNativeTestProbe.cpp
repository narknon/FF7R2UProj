// Owned native diagnostic only. No viewport, UHT, UObject layout, asset save,
// test substitution or AutomationController/worker discovery dependency.
#include "CoreMinimal.h"

#if WITH_DEV_AUTOMATION_TESTS

#include "Dom/JsonObject.h"
#include "HAL/FileManager.h"
#include "HAL/PlatformProcess.h"
#include "Misc/AutomationTest.h"
#include "Misc/CommandLine.h"
#include "Misc/CoreMisc.h"
#include "Misc/FileHelper.h"
#include "Misc/Parse.h"
#include "Misc/Paths.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "UObject/GarbageCollection.h"

DEFINE_LOG_CATEGORY_STATIC(LogRebirthBonamikNativeTest, Log, All);

namespace
{
    const TCHAR* const NativeBonamikTestClass = TEXT("FRebirthBonamikPreviewFixtureTest");
    const TCHAR* const NativeBonamikTestPath = TEXT("Rebirth.Preview.Bonamik.StandardSephirothOwnershipReset");

    bool WriteNativeBonamikResult(const TSharedRef<FJsonObject>& Report, FOutputDevice& Ar)
    {
        FString JSON;
        const FString Directory = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("BonamikNativeTest"));
        const FString Filename = FPaths::Combine(Directory, TEXT("Result.json"));
        Report->SetStringField(TEXT("result_path"), FPaths::ConvertRelativePathToFull(Filename));
        const bool bSerialized = FJsonSerializer::Serialize(Report, TJsonWriterFactory<>::Create(&JSON));
        const bool bSaved = bSerialized && IFileManager::Get().MakeDirectory(*Directory, true) &&
            FFileHelper::SaveStringToFile(JSON, *Filename, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM);
        Ar.Logf(TEXT("BonamikNativeTest result_written=%d path=%s"), bSaved ? 1 : 0, *Filename);
        return bSaved;
    }

    class FRebirthBonamikNativeTestExec final : public FSelfRegisteringExec
    {
    public:
        virtual bool Exec(UWorld*, const TCHAR* Cmd, FOutputDevice& Ar) override
        {
            if (!FParse::Command(&Cmd, TEXT("Rebirth.BonamikNativeTest"))) return false;
            // An unmarked user editor does not expose or execute this test route.
            if (!FParse::Param(FCommandLine::Get(), TEXT("RebirthBonamikNativeAutomation"))) return false;

            TSharedRef<FJsonObject> Report = MakeShared<FJsonObject>();
            Report->SetNumberField(TEXT("schema_version"), 1);
            Report->SetBoolField(TEXT("owned_marker"), true);
            Report->SetStringField(TEXT("run_id"), FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens));
            Report->SetNumberField(TEXT("process_id"), FPlatformProcess::GetCurrentProcessId());
            Report->SetStringField(TEXT("test_class"), NativeBonamikTestClass);
            Report->SetStringField(TEXT("full_test_path"), NativeBonamikTestPath);
            Report->SetStringField(TEXT("project_file"), FPaths::ConvertRelativePathToFull(FPaths::GetProjectFilePath()));
            Report->SetStringField(TEXT("execution_route"), TEXT("FAutomationTestFramework synchronous fixed Simple test"));
            Report->SetBoolField(TEXT("viewport_required"), false);
            Report->SetBoolField(TEXT("assets_saved"), false);
            Report->SetBoolField(TEXT("started"), false);
            Report->SetBoolField(TEXT("stopped"), false);
            Report->SetBoolField(TEXT("verified"), false);

            FString Error;
            if (!FString(Cmd).TrimStartAndEnd().IsEmpty()) Error = TEXT("arguments_not_supported");
            else if (!IsInGameThread()) Error = TEXT("game_thread_required");
            else if (!GIsEditor || IsEngineExitRequested() || IsGarbageCollecting()) Error = TEXT("editor_lifecycle_not_safe");
            else if (GIsAutomationTesting) Error = TEXT("another_automation_test_is_active");
            else if (GIsSlowTask || GIsPlayInEditorWorld) Error = TEXT("slow_task_or_pie_active");

            FAutomationTestFramework& Framework = FAutomationTestFramework::Get();
            const bool bRegistered = Framework.ContainsTest(NativeBonamikTestClass);
            Report->SetBoolField(TEXT("registered"), bRegistered);
            if (Error.IsEmpty() && !bRegistered) Error = TEXT("fixed_test_class_not_registered");

            if (!Error.IsEmpty())
            {
                Report->SetStringField(TEXT("status"), TEXT("REFUSED"));
                Report->SetStringField(TEXT("error"), Error);
                WriteNativeBonamikResult(Report, Ar);
                return true;
            }

            Report->SetStringField(TEXT("status"), TEXT("RUNNING_NATIVE_FIXTURE"));
            if (!WriteNativeBonamikResult(Report, Ar)) return true;
            const double Began = FPlatformTime::Seconds();
            // StartTestByName invokes this fixed SIMPLE test's RunTest immediately.
            // It uses the class registration key, not the dotted display path.
            Framework.StartTestByName(NativeBonamikTestClass, 0);
            FAutomationTestBase* Current = Framework.GetCurrentTest();
            const bool bStarted = GIsAutomationTesting && Current && Current->GetTestName() == NativeBonamikTestClass;
            Report->SetBoolField(TEXT("started"), bStarted);
            if (!bStarted)
            {
                if (GIsAutomationTesting && Current)
                {
                    Current->AddError(TEXT("Owned bridge started an unexpected test identity; result is not verified."));
                    Framework.DequeueAllCommands();
                    FAutomationTestExecutionInfo CleanupExecution;
                    Framework.StopTest(CleanupExecution);
                }
                Report->SetStringField(TEXT("status"), TEXT("FAILED"));
                Report->SetStringField(TEXT("error"), TEXT("fixed_test_did_not_start"));
                Report->SetNumberField(TEXT("elapsed_seconds"), FPlatformTime::Seconds() - Began);
                WriteNativeBonamikResult(Report, Ar);
                return true;
            }

            TArray<FAutomationTestInfo> FixedTestInfo;
            Current->GenerateTestNames(FixedTestInfo);
            const bool bExpectedIdentity = FixedTestInfo.Num() == 1 &&
                FixedTestInfo[0].GetFullTestPath() == NativeBonamikTestPath &&
                FixedTestInfo[0].GetTestName() == NativeBonamikTestClass &&
                !Current->IsComplexTask() && Current->GetRequiredDeviceNum() == 1 &&
                Current->GetTestFlags() == (EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter);
            if (!bExpectedIdentity) Current->AddError(TEXT("Owned bridge expected the fixed single-device Simple fixture identity."));
            // This exact fixture has no AddCommand/latent/network paths. In this
            // engine Execute* returns false if ANY command existed on entry, even
            // if that command completed immediately. Unexpected queued work is
            // reported as a failed test and cancelled before StopTest's empty-queue check.
            const bool bNoLatentCommands = Framework.ExecuteLatentCommands();
            const bool bNoNetworkCommands = Framework.ExecuteNetworkCommands();
            if (!bNoLatentCommands || !bNoNetworkCommands)
            {
                Current->AddError(TEXT("Owned synchronous fixture unexpectedly queued deferred work; execution is not verified."));
                Framework.DequeueAllCommands();
            }
            Report->SetBoolField(TEXT("no_latent_commands"), bNoLatentCommands);
            Report->SetBoolField(TEXT("no_network_commands"), bNoNetworkCommands);
            Report->SetBoolField(TEXT("expected_fixture_identity"), bExpectedIdentity);

            FAutomationTestExecutionInfo Execution;
            const bool bStoppedSuccessfully = Framework.StopTest(Execution);
            Report->SetBoolField(TEXT("stopped"), !GIsAutomationTesting && Framework.GetCurrentTest() == nullptr);
            Report->SetBoolField(TEXT("framework_success"), bStoppedSuccessfully);
            Report->SetBoolField(TEXT("execution_success"), Execution.bSuccessful);
            Report->SetNumberField(TEXT("errors"), Execution.GetErrorTotal());
            Report->SetNumberField(TEXT("warnings"), Execution.GetWarningTotal());
            Report->SetNumberField(TEXT("duration_seconds"), Execution.Duration);
            Report->SetNumberField(TEXT("elapsed_seconds"), FPlatformTime::Seconds() - Began);
            bool bMotionEvidence = false;
            bool bCovarianceEvidence = false;
            TArray<TSharedPtr<FJsonValue>> Entries;
            for (const FAutomationExecutionEntry& Entry : Execution.GetEntries())
            {
                TSharedRef<FJsonObject> Row = MakeShared<FJsonObject>();
                const TCHAR* Type = Entry.Event.Type == EAutomationEventType::Error ? TEXT("Error") :
                    Entry.Event.Type == EAutomationEventType::Warning ? TEXT("Warning") : TEXT("Info");
                Row->SetStringField(TEXT("type"), Type);
                Row->SetStringField(TEXT("message"), Entry.Event.Message);
                Row->SetStringField(TEXT("context"), Entry.Event.Context);
                Row->SetStringField(TEXT("filename"), Entry.Filename);
                Row->SetNumberField(TEXT("line_number"), Entry.LineNumber);
                Entries.Add(MakeShared<FJsonValueObject>(Row));
                bMotionEvidence |= Entry.Event.Type == EAutomationEventType::Info &&
                    Entry.Event.Message.StartsWith(TEXT("BonamikNativeMotion dynamic=220 "));
                bCovarianceEvidence |= Entry.Event.Type == EAutomationEventType::Info &&
                    Entry.Event.Message.StartsWith(TEXT("BonamikNativeCovariance "));
            }
            Report->SetArrayField(TEXT("entries"), Entries);
            Report->SetBoolField(TEXT("motion_evidence_present"), bMotionEvidence);
            Report->SetBoolField(TEXT("covariance_evidence_present"), bCovarianceEvidence);
            const bool bVerified = bExpectedIdentity && bNoLatentCommands && bNoNetworkCommands &&
                bStoppedSuccessfully && Execution.bSuccessful && Execution.GetErrorTotal() == 0 &&
                bMotionEvidence && bCovarianceEvidence && !GIsAutomationTesting && Framework.GetCurrentTest() == nullptr;
            Report->SetBoolField(TEXT("verified"), bVerified);
            Report->SetStringField(TEXT("status"), bVerified ? TEXT("VERIFIED_NATIVE_BONAMIK_FIXTURE") : TEXT("NATIVE_FIXTURE_FAILED"));
            WriteNativeBonamikResult(Report, Ar);
            return true;
        }
    };

    FRebirthBonamikNativeTestExec NativeBonamikTestExec;
}

#endif
