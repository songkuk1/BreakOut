#pragma once
#include "SoundManager.h"
#include <fstream>


SoundManager* SoundManager::GetInstance()
{
	static SoundManager instance;
	return &instance;
}

void SoundManager::Init()
{
	//메모리에 올리고 초기화
	XAudio2Create(&XAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
	//소리가 출력될 하드웨어를 대변하는 마스터링 보이스 객체 생성
	XAudio2->CreateMasteringVoice(&MasterVoice);

    LoadSFX(SOUND_KEY_PING_PONG, L".\\Resources\\Sound\\pingpong.wav");
}

void SoundManager::Release()
{

    for (auto& pair : sfxPoolMap)
    {
        for (IXAudio2SourceVoice* pVoice : pair.second)
        {
            pVoice->DestroyVoice();
        }
    }
    sfxPoolMap.clear();

    if (XAudio2)
    {
        XAudio2->Release();
        XAudio2 = nullptr;
    }

}

void SoundManager::PlaySFX(const std::wstring& key)
{
    auto dataIt = sfxDataMap.find(key);
    if (dataIt == sfxDataMap.end()) return;
    SoundData& data = dataIt->second;

    IXAudio2SourceVoice* pVoiceToPlay = nullptr;

    // 무조건 새로운 보이스 생성 (동시 재생 보장)
    HRESULT hr = XAudio2->CreateSourceVoice(&pVoiceToPlay, &data.wfx);
    if (FAILED(hr))
    {
        return; // 생성 실패 시 종료
    }

    // SFX 풀 맵에 새로운 보이스 추가
    auto poolIt = sfxPoolMap.find(key);
    if (poolIt == sfxPoolMap.end()) {
        sfxPoolMap[key] = std::vector<IXAudio2SourceVoice*>();
        poolIt = sfxPoolMap.find(key);
    }
    poolIt->second.push_back(pVoiceToPlay);

    // 버퍼 제출 및 재생
    XAUDIO2_BUFFER buffer = { 0 };
    buffer.AudioBytes = (UINT32)data.audioBytes.size();
    buffer.pAudioData = data.audioBytes.data();
    buffer.Flags = XAUDIO2_END_OF_STREAM;

    pVoiceToPlay->FlushSourceBuffers();
    hr = pVoiceToPlay->SubmitSourceBuffer(&buffer);

    if (SUCCEEDED(hr))
    {
        pVoiceToPlay->Start();
    }
}

bool SoundManager::LoadWavFile(const std::wstring& filePath, SoundData& outData)
{
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) { return false; }

    char riffId[4], waveId[4];
    DWORD fileSize;
    file.read(riffId, 4);
    file.read(reinterpret_cast<char*>(&fileSize), sizeof(DWORD));
    file.read(waveId, 4);

    if (memcmp(riffId, "RIFF", 4) != 0 || memcmp(waveId, "WAVE", 4) != 0) {
        file.close();
        return false;
    }

    // fmt 청크와 data 청크를 찾을 때까지 반복
    WavChunk chunk;
    bool fmtFound = false;
    bool dataFound = false;
    DWORD dataStartOffset = 0;

    while (file.read(reinterpret_cast<char*>(&chunk), sizeof(WavChunk)))
    {
        if (memcmp(chunk.id, "fmt ", 4) == 0)
        {
            file.read(reinterpret_cast<char*>(&outData.wfx), chunk.size);
            fmtFound = true;
        }
        else if (memcmp(chunk.id, "data", 4) == 0)
        {
            dataStartOffset = (DWORD)file.tellg();
            dataFound = true;
            break;
        }
        else
        {
            // 건너뛰기
            file.seekg(chunk.size, std::ios::cur);
        }
    }

    // fmt/data 청크 확인
    if (!fmtFound || !dataFound) {
        file.close();
        return false;
    }

    // 오디오 데이터 읽기
    outData.audioBytes.resize(chunk.size);
    file.seekg(dataStartOffset);
    file.read(reinterpret_cast<char*>(outData.audioBytes.data()), chunk.size);

    file.close();
    return true;
}

bool SoundManager::LoadSFX(std::wstring key, const std::wstring& filePath)
{
    SoundData soundData;
    if (LoadWavFile(filePath, soundData))
    {
        sfxDataMap[key] = soundData;
        return true;
    }

    return false;
}
