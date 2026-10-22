#include "RebirthCookLogFilter.h"

#include "CoreGlobals.h"
#include "HAL/PlatformAtomics.h"
#include "Logging/LogMacros.h"
#include "Misc/CommandLine.h"
#include "Misc/CoreMisc.h"
#include "Misc/FeedbackContext.h"
#include "Misc/OutputDeviceHelper.h"
#include "Misc/Parse.h"

DEFINE_LOG_CATEGORY_STATIC(LogRebirthCook, Log, All);

namespace
{
	const TCHAR* const MismatchSizePrefix = TEXT("Mismatch size for type ");
	const TCHAR* const MismatchHashPrefix = TEXT("Mismatch hash for type ");

	bool RebirthCookStartsWith(const TCHAR* Text, const TCHAR* Prefix)
	{
		return FCString::Strncmp(Text, Prefix, FCString::Strlen(Prefix)) == 0;
	}

	ELogVerbosity::Type RebirthCookLevel(ELogVerbosity::Type Verbosity)
	{
		return static_cast<ELogVerbosity::Type>(Verbosity & ELogVerbosity::VerbosityMask);
	}

	/** The two messages RenderCore's FShaderMapBase::Serialize logs for a frozen shader map saved by another build. */
	bool IsForeignShaderLayoutMismatch(const TCHAR* Text, ELogVerbosity::Type Verbosity, const FName& Category)
	{
		static const FName ShaderLogCategory(TEXT("LogShaders"));
		return Text != nullptr
			&& RebirthCookLevel(Verbosity) == ELogVerbosity::Error
			&& Category == ShaderLogCategory
			&& (RebirthCookStartsWith(Text, MismatchSizePrefix) || RebirthCookStartsWith(Text, MismatchHashPrefix));
	}

	/** Same test on a line already recorded by the engine's own context ("[Context : ]LogShaders: Error: Mismatch ..."). */
	bool IsRecordedForeignShaderLayoutMismatch(const FString& Line)
	{
		return Line.Contains(TEXT("LogShaders: Error: Mismatch size for type "), ESearchCase::CaseSensitive)
			|| Line.Contains(TEXT("LogShaders: Error: Mismatch hash for type "), ESearchCase::CaseSensitive);
	}

	/**
	 * GWarn for commandlets. Forwards everything to the engine's own feedback context and keeps its own error/warning
	 * history, because the summary after Commandlet->Main() reads GWarn->GetErrors()/GetWarnings() from GWarn itself.
	 */
	class FRebirthCookFeedbackContext final : public FFeedbackContext
	{
	public:
		explicit FRebirthCookFeedbackContext(FFeedbackContext& InInner)
			: Inner(InInner)
		{
			TreatWarningsAsErrors = Inner.TreatWarningsAsErrors;

			TArray<FString> Existing;
			Inner.GetErrors(Existing);
			for (const FString& Line : Existing)
			{
				if (IsRecordedForeignShaderLayoutMismatch(Line))
				{
					FPlatformAtomics::InterlockedIncrement(&Downgraded);
				}
				else
				{
					AddError(Line);
				}
			}
			Existing.Reset();
			Inner.GetWarnings(Existing);
			for (const FString& Line : Existing)
			{
				AddWarning(Line);
			}
		}

		int32 GetDowngradedCount() const
		{
			return FPlatformAtomics::AtomicRead(&Downgraded);
		}

		virtual void Serialize(const TCHAR* V, ELogVerbosity::Type Verbosity, const FName& Category) override
		{
			const bool bDowngrade = IsForeignShaderLayoutMismatch(V, Verbosity, Category);
			if (bDowngrade)
			{
				Verbosity = ELogVerbosity::Display;
			}
			Record(V, Verbosity, Category);
			Inner.Serialize(V, Verbosity, Category);
			if (bDowngrade)
			{
				NoteDowngrade();
			}
		}

		virtual void Serialize(const TCHAR* V, ELogVerbosity::Type Verbosity, const FName& Category, const double Time) override
		{
			const bool bDowngrade = IsForeignShaderLayoutMismatch(V, Verbosity, Category);
			if (bDowngrade)
			{
				Verbosity = ELogVerbosity::Display;
			}
			Record(V, Verbosity, Category);
			Inner.Serialize(V, Verbosity, Category, Time);
			if (bDowngrade)
			{
				NoteDowngrade();
			}
		}

		virtual bool YesNof(const FText& Question) override { return Inner.YesNof(Question); }
		virtual bool ReceivedUserCancel() override { return Inner.ReceivedUserCancel(); }
		virtual FContextSupplier* GetContext() const override { return Inner.GetContext(); }
		virtual void SetContext(FContextSupplier* InSupplier) override { Inner.SetContext(InSupplier); }
		virtual TWeakPtr<SBuildProgressWidget> ShowBuildProgressWindow() override { return Inner.ShowBuildProgressWindow(); }
		virtual void CloseBuildProgressWindow() override { Inner.CloseBuildProgressWindow(); }
		virtual void Flush() override { Inner.Flush(); }
		virtual void Dump(FArchive& Ar) override { Inner.Dump(Ar); }
		virtual bool IsMemoryOnly() const override { return Inner.IsMemoryOnly(); }
		virtual bool CanBeUsedOnAnyThread() const override { return Inner.CanBeUsedOnAnyThread(); }
		virtual bool CanBeUsedOnMultipleThreads() const override { return Inner.CanBeUsedOnMultipleThreads(); }

	private:
		void Record(const TCHAR* V, ELogVerbosity::Type Verbosity, const FName& Category)
		{
			ELogVerbosity::Type Effective = RebirthCookLevel(Verbosity);
			if ((Effective != ELogVerbosity::Error && Effective != ELogVerbosity::Warning) || !IsRunningCommandlet())
			{
				return;
			}
			if (Effective == ELogVerbosity::Warning && (TreatWarningsAsErrors || Inner.TreatWarningsAsErrors))
			{
				Effective = ELogVerbosity::Error;
			}
			FString Line;
			if (FContextSupplier* Supplier = Inner.GetContext())
			{
				Line = Supplier->GetContext() + TEXT(" : ");
			}
			Line += FOutputDeviceHelper::FormatLogLine(Effective, Category, V);
			if (Effective == ELogVerbosity::Error)
			{
				AddError(Line);
			}
			else
			{
				AddWarning(Line);
			}
		}

		void NoteDowngrade()
		{
			FPlatformAtomics::InterlockedIncrement(&Downgraded);
			if (FPlatformAtomics::InterlockedCompareExchange(&bAnnounced, 1, 0) == 0)
			{
				UE_LOG(LogRebirthCook, Warning,
					TEXT("Retail cooked materials were loaded whose shader maps were frozen by Square Enix's build (their shader types differ from this editor's), so the engine discards those shader maps. ")
					TEXT("Its 'Mismatch size/hash for type' messages are logged at Display and do not fail this commandlet. Run with -RebirthKeepShaderMismatchErrors to count them as errors again."));
			}
		}

		FFeedbackContext& Inner;
		volatile int32 Downgraded = 0;
		volatile int32 bAnnounced = 0;
	};

	FRebirthCookFeedbackContext* GRebirthCookFeedback = nullptr;
	FFeedbackContext* GRebirthCookOriginalWarn = nullptr;
}

namespace RebirthCookLogFilter
{
	void Install()
	{
		if (!IsRunningCommandlet() || GRebirthCookFeedback != nullptr || GWarn == nullptr)
		{
			return;
		}
		if (FParse::Param(FCommandLine::Get(), TEXT("RebirthKeepShaderMismatchErrors")))
		{
			UE_LOG(LogRebirthCook, Display, TEXT("-RebirthKeepShaderMismatchErrors: retail shader map layout mismatches stay errors."));
			return;
		}
		GRebirthCookOriginalWarn = GWarn;
		// Never deleted: another thread may still hold the pointer it read from GWarn when Uninstall() runs.
		GRebirthCookFeedback = new FRebirthCookFeedbackContext(*GWarn);
		GWarn = GRebirthCookFeedback;
		UE_LOG(LogRebirthCook, Display, TEXT("Commandlet log filter installed: retail shader map layout mismatches are logged at Display instead of failing the commandlet."));
	}

	void Uninstall()
	{
		if (GRebirthCookFeedback == nullptr)
		{
			return;
		}
		const int32 Count = GRebirthCookFeedback->GetDowngradedCount();
		if (GWarn == GRebirthCookFeedback)
		{
			GWarn = GRebirthCookOriginalWarn;
		}
		if (Count > 0)
		{
			UE_LOG(LogRebirthCook, Display, TEXT("%d retail shader map layout mismatch message(s) were logged at Display instead of Error."), Count);
		}
	}
}
