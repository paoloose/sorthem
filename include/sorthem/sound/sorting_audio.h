#pragma once

#include <SFML/Audio.hpp>
#include <cmath>

// 16-bit sound amplitude
#define SOUND_AMPLITUDE 32767.f
// standard sample rate
#define SOUND_SAMPLE_RATE 44100.f
#define SOUND_CHANNEL_COUNT 1
#define DEFAULT_FREQUENCY 800.f
#define DEFAULT_AMPLITUDE 1.f

namespace sorthem {

class SortingAudio : public sf::SoundStream {
    float m_frequency;
    float m_wave_length;
    float m_amp;
    float m_time;
  public:
    SortingAudio(float frequency, float amplitude, float wave_length);
    SortingAudio();
    void setFrequency(float frequency);
  private:
    virtual bool onGetData(Chunk& data);
    virtual void onSeek(sf::Time timeOffset);
};

}
