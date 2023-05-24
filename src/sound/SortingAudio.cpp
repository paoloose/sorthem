#include "sound/SortingAudio.h"

sf::Int16 sinewave(float frequency, float amplitude, float time) {
    double cycles = time * frequency;
    double rad = time * frequency * 2 * M_PI;
    double wave_amplitude = SOUND_AMPLITUDE * amplitude;
    return static_cast<sf::Int16>(wave_amplitude * sin(rad));
}

SortingAudio::SortingAudio() :
    m_frequency(DEFAULT_FREQUENCY), m_amp(DEFAULT_AMPLITUDE), m_time(0.f)
{
    initialize(SOUND_CHANNEL_COUNT, SOUND_SAMPLE_RATE);
}

SortingAudio::SortingAudio(float frequency, float amplitude, float wave_length) :
    m_frequency(frequency), m_amp(amplitude), m_time(0.f), m_wave_length(wave_length)
{
    initialize(SOUND_CHANNEL_COUNT, SOUND_SAMPLE_RATE);
}

void SortingAudio::setFrequency(float frequency) {
    m_frequency = frequency;
}

bool SortingAudio::onGetData(sf::SoundStream::Chunk &data) {
    std::size_t sampleCount = 4096;
    sf::Int16* samples = new sf::Int16[sampleCount];

    for (std::size_t i = 0; i < sampleCount; i++) {
        m_time += 1.f / SOUND_SAMPLE_RATE;
        samples[i] = sinewave(m_frequency, m_amp, m_time);
        if (m_time >= 0.1f) {
            data.sampleCount = i + 1;
            data.samples = samples;
            return false;
        }
    }

    data.sampleCount = sampleCount;
    data.samples = samples;
    return true;
}

void SortingAudio::onSeek(sf::Time timeOffset) {
    m_time = timeOffset.asSeconds();
}
