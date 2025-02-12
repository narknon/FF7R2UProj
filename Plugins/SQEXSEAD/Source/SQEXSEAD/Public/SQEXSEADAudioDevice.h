#pragma once

#include "CoreMinimal.h"
#include "AudioDevice.h"

class FSQEXSEADSoundSource : public FSoundSource
{
public:
	/**
	 * Constructor
	 *
	 * @param	InAudioDevice	audio device this source is attached to
	 */
	FSQEXSEADSoundSource(FAudioDevice* InAudioDevice)
	: FSoundSource(InAudioDevice)
	{
	}
	virtual bool Init(FWaveInstance* WaveInstance) override
	{
	    return false;
	}
	
	/** Updates the sound source. */
    virtual void Update() override 
    {
    }
    
    /** Plays the sound source. */
    virtual void Play() override 
    {
    }
    
    /** Returns true if the sound source has finished playing. */
    virtual	bool IsFinished() override 
    {
        return true;
    }
    
    /** Pauses the sound source. */
    virtual void Pause() override 
    {
    }
};

class FSQEXSEADAudioDevice : public FAudioDevice
{
public:
	FSQEXSEADAudioDevice() : FAudioDevice()
	{
	}
	
	virtual FName GetRuntimeFormat(USoundWave* SoundWave) override
    {
        static const FName NAME_SQEXSEAD(TEXT("SQEXSEAD"));
        return NAME_SQEXSEAD;
    }
    	
    /** Creates a new platform specific sound source */
    virtual FSoundSource* CreateSoundSource() override
    {
        // create source source object
    	return new FSQEXSEADSoundSource(this);
    }
};