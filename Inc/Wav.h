// Wav.h
// Copyright (c) 2024 Jules Bloomenthal, all rights reserved. Commercial use requires license.

#ifndef WAV_HDR
#define WAV_HDR

#include "mmeapi.h"				// linker: include winmm.lib
#include <string>
#include <vector>

using namespace std;

class Wav {
public:
	// audio data
	vector<short> samples;		// mono or stereo
	int nSamples = 0;			// # mono samples or # stereo pairs
	int nChannels = 0;			// 1 or 2
	int samplingRate = 0;		// samples per second
	int sigBitsPerSamp = 0;		// should be 16
	float duration = 0;			// in seconds (nSamples/samplingRate)
	// methods
	bool Read(string filename, bool verbose = false);
		// **** see comments in implementation: nSamples can be mistakenly high
		// **** a workaround: import to Audacity, select all, export to new .wav
	bool Play(float volume = 1);
	bool Stop();
	bool Pause();
	bool Resume();
	void SetVolume(float volume = 1);
	bool Play(int offset, int nsamples, float volume = 1, bool reuseDevice = true);
		// offset, nsamples: # mono samples or # stereo pairs
		// if !reuseDevice, add new device to mix
	float FractionPlayed();
	// device access
	WAVEHDR wh;
	HWAVEOUT waveOut = NULL;
	bool OpenDevice();
	// constructor
	Wav(string filename = "", bool verbose = false);
private:
	bool paused = true;
	// format
	int aveBytesPerSec = 0, blockAlign = 0;
	// playback
	time_t startPlay = 0;
	float accumulatedPlaytime = 0;
};

enum Channel { C_Left = 0, C_Right, C_Mono };

class WavView {
public:
	Wav *wav = NULL;
	int x = 0, y = 0, w = 0, h = 0, offset = 0, nSamples = 0;
	Channel channel;
	vector<float> vmin, vmax;
	WavView(int x, int y, int w, int h, Wav *wav, Channel ch);
	void Display();
};

#endif // WAV_HDR
