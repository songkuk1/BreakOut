#pragma once
#include <xaudio2.h>
#include <string>
#include <string_view>

#include <vector>
#include "UVector.h"
#include <map>

//define으로 상수 정의하는것은 지양해야해서 본래 wsting_view를 이용해 문자열 상수를 정의하려고하였음
//하지만 LoadWavFile내용은 직접작성이 아닌, 제공되는 템플릿을 사용하였음
//그러므로 LoadWavFile내용또한 기존 방식에서 wstring_view를 인자로 받는 함수방식으로 고쳐야하는데, 이것을 고치기엔 공부가 부족하다고 판단되어
//define을 사용하여 상수를 정의함
#define SOUND_KEY_PING_PONG L"pingpong"

struct SoundData
{
	WAVEFORMATEX wfx;
	std::vector<BYTE> audioBytes;
};

struct WavChunk
{
	char id[4];
	DWORD size;
};

class SoundManager
{
public:
	SoundManager() {};
	~SoundManager() = default;
	static SoundManager* GetInstance();

	void Init();
	void Release();

	void PlaySFX(const std::wstring& key);

private:

	bool LoadWavFile(const std::wstring& filePath, SoundData& outData);
	bool LoadSFX(std::wstring key, const std::wstring& filePath);
	std::map<std::wstring, SoundData> sfxDataMap;
	IXAudio2* XAudio2;
	IXAudio2MasteringVoice* MasterVoice;
	std::map<std::wstring, std::vector<IXAudio2SourceVoice*>> sfxPoolMap;

};