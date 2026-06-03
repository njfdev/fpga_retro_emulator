#pragma once

#include "miniaudio.h"

class AudioOutput {
public:
  AudioOutput();
  ~AudioOutput();

private:
  ma_device device;
  ma_device_config audio_config;

};
