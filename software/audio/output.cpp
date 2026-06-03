#include "output.h"
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <limits>
#include <stdexcept>

#define WAVE_FREQUENCY 220.0
#define VOLUME 0.4
constexpr int16_t VOLUME16 = static_cast<int16_t>((std::numeric_limits<int16_t>::max())*VOLUME);

int totalFrames = 0;
void audioCallback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount) {
  ma_int16* output = static_cast<ma_int16*>(pOutput);

  uint32_t channels = pDevice->playback.channels;
  uint32_t sampleRate = pDevice->sampleRate;

  for (int i = 0; i < frameCount*channels; i += channels) {
    for (int channel = 0; channel < channels; channel++) {
      uint16_t framesPerPeriod = sampleRate/WAVE_FREQUENCY;
      float fractionOfPeriod = (totalFrames%framesPerPeriod)/static_cast<float>(framesPerPeriod);

      // SQUARE WAVE
      // output[i+channel] =  fractionOfPeriod < 0.5 ? -VOLUME16 : VOLUME16;

      // TRIANGLE WAVE
      output[i+channel] = fractionOfPeriod < 0.5 ? -VOLUME16+(fractionOfPeriod*4.0*VOLUME16) : VOLUME16-((fractionOfPeriod-0.5)*4.0*VOLUME16);

      // SAWTOOTH WAVE
      // output[i+channel] = VOLUME16-(fractionOfPeriod*2.0*VOLUME16);

      // WHITE NOISE
      // output[i+channel] = (((rand()%10000)/10000.0)-0.5)*2.0*VOLUME16;
    }
    totalFrames++;
  }
}

AudioOutput::AudioOutput() {
  audio_config = ma_device_config_init(ma_device_type_playback);
  audio_config.playback.format = ma_format_s16;
  audio_config.playback.channels = 2;
  audio_config.sampleRate = 44100;
  audio_config.dataCallback = audioCallback;
  // audio_config.pUserData = ;

  if (ma_device_init(NULL, &audio_config, &device) != MA_SUCCESS) {
    throw std::runtime_error("Could not successfully initialize a playback device!");
  }

  ma_device_start(&device);
}

AudioOutput::~AudioOutput() {
  ma_device_uninit(&device);
}
