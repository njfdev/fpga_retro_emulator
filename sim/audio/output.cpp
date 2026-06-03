#include "output.h"
#include <cstddef>
#include <cstdlib>
#include <stdexcept>

const float SQUARE_WAVE_FREQUENCY = 440.0;

int totalFrames = 0;
void audioCallback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount) {
  ma_int16* output = static_cast<ma_int16*>(pOutput);

  uint32_t channels = pDevice->playback.channels;

  for (int i = 0; i < frameCount*channels; i += channels) {
    for (int channel = 0; channel < channels; channel++) {
      output[i+channel] = (totalFrames%(int16_t)(44100/SQUARE_WAVE_FREQUENCY)) > 44100/(SQUARE_WAVE_FREQUENCY*2) ? 5000 : -5000;
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
