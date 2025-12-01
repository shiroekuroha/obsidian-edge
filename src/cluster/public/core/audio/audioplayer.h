#pragma once

#include "miniaudio.h"

namespace ObsidianEdge {
class AudioPlayer {
public:
    AudioPlayer();
    ~AudioPlayer();

    AudioPlayer(const AudioPlayer &other);
    AudioPlayer(AudioPlayer &&other) noexcept;

    auto operator=(const AudioPlayer &other) -> AudioPlayer &;
    auto operator=(AudioPlayer &&other) noexcept -> AudioPlayer &;

    void init();
    void yeet();

    void play(const char *path, bool loop = false);
    void play();
    void stop();

    void toggleMute();
    static void setVolume(float multiplier);

    [[nodiscard]] auto isPlaying() const -> bool;
    [[nodiscard]] auto isMuted() const -> bool;

private:
    ma_engine engine = {};
    ma_sound sound = {};

    bool m_isMuted = false;

    bool m_init;
    float m_volume;

private:
    static float s_masterVolume;
};
} // namespace ObsidianEdge
