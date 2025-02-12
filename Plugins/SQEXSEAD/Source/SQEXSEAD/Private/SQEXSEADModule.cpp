#include "Modules/ModuleManager.h"
#include "SQEXSEADAudioDevice.h"

class FSQEXSEADModule : public IAudioDeviceModule
{
public:

	/** Creates a new instance of the audio device implemented by the module. */
	virtual FAudioDevice* CreateAudioDevice() override
	{
		return new FSQEXSEADAudioDevice;
	}
};

IMPLEMENT_MODULE(FSQEXSEADModule, SQEXSEAD );
