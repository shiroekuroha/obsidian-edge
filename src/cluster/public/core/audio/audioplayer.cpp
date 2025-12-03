#include <pch.h>

#include "audioplayer.h"

#include "core/log/log.h"

namespace ObsidianEdge {
float AudioPlayer::s_masterVolume = 1.0f;

AudioPlayer::AudioPlayer() : m_init(false), m_volume(1.0f) { init(); }
AudioPlayer::~AudioPlayer() { yeet(); }

void AudioPlayer::init() {
    ma_result result = ma_engine_init(nullptr, &engine);

    OE_CORE_ASSERT(result == MA_SUCCESS, "Failed to initialize audio engine!");

    if (result == MA_SUCCESS) {
        m_init = true;
    } else {
        throw;
    }
}

void AudioPlayer::yeet() {
    if (isPlaying())
        ma_sound_uninit(&sound);

    ma_engine_uninit(&engine);
    m_init = false;
}

void AudioPlayer::play(const char *path, bool loop) {
    if (isPlaying())
        ma_sound_uninit(&sound);

    OE_CORE_ASSERT(ma_sound_init_from_file(&engine, path, 0, nullptr, nullptr, &sound) == MA_SUCCESS,
                   "Failed to play sound file at path: {0}", path);

    ma_sound_set_looping(&sound, loop);
    ma_sound_set_volume(&sound, s_masterVolume);
    ma_sound_start(&sound);
}

void AudioPlayer::play() {
    if (!isPlaying()) {
        ma_sound_start(&sound);
    }
}

void AudioPlayer::stop() {
    if (isPlaying()) {
        ma_sound_stop(&sound);
    }
}

void AudioPlayer::toggleMute() {
    m_isMuted = !m_isMuted;

    if (m_isMuted) {
        ma_engine_set_volume(&engine, 0.0f);
    } else {
        ma_engine_set_volume(&engine, s_masterVolume);
    }
}

auto AudioPlayer::isPlaying() const -> bool { return ma_sound_is_playing(&sound); }
auto AudioPlayer::isMuted() const -> bool { return m_isMuted; }
} // namespace ObsidianEdge
