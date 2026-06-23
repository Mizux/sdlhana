//
// Copyright (c) 2005, 2006 Wei Mingzhi <whistler@openoffice.org>
// All Rights Reserved.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; either version 2 of
// the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
// 02110-1301, USA
//

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.hpp"

static SDL_AudioDeviceID g_AudioDeviceID = 0;
static SDL_AudioSpec     g_AudioSpec;
bool                     g_fAudioOpened = false;

int SOUND_OpenAudio(int freq, int format, int channels, int samples) {
  if (g_fAudioOpened) {
    return 0;
  }

  g_AudioSpec.freq     = freq;
  g_AudioSpec.format   = (SDL_AudioFormat)format;
  g_AudioSpec.channels = channels;

  g_AudioDeviceID = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &g_AudioSpec);

  if (g_AudioDeviceID == 0) {
    fprintf(stderr, "WARNING: Couldn't open audio: %s\n", SDL_GetError());
    return -1;
  } else {
    g_fAudioOpened = true;
    return 0;
  }
}

SDL_AudioCVT* SOUND_LoadWAV(const char* filename) {
  SDL_AudioSpec  wavespec;
  unsigned char* buf;
  unsigned int   len;

  if (!g_fAudioOpened) {
    return nullptr;
  }

  if (SDL_LoadWAV(filename, &wavespec, &buf, &len) == -1) {
    return nullptr;
  }

  SDL_AudioCVT* wavecvt = (SDL_AudioCVT*)malloc(sizeof(SDL_AudioCVT));
  if (wavecvt == nullptr) {
    SDL_free(buf);
    return nullptr;
  }

  // Convert to device format using AudioStream
  SDL_AudioStream* stream = SDL_CreateAudioStream(&wavespec, &g_AudioSpec);
  if (stream == nullptr) {
    SDL_free(buf);
    free(wavecvt);
    return nullptr;
  }

  SDL_PutAudioStreamData(stream, buf, len);
  SDL_FlushAudioStream(stream);

  int converted_len = (int)SDL_GetAudioStreamQueued(stream);
  wavecvt->buf      = (unsigned char*)malloc(converted_len);
  wavecvt->len      = converted_len;
  wavecvt->len_mult = 1;

  SDL_GetAudioStreamData(stream, wavecvt->buf, converted_len);
  SDL_DestroyAudioStream(stream);
  SDL_free(buf);

  return wavecvt;
}

void SOUND_FreeWAV(SDL_AudioCVT* audio) {
  if (audio == nullptr) {
    return;
  }
  free(audio->buf);
  free(audio);
}

void SOUND_PlayWAV(SDL_AudioCVT* audio) {
  if (audio == nullptr || !g_fAudioOpened) {
    return;
  }

  // In SDL3, we can just push data to the device's default stream
  // or we can create a dedicated stream for each sound if we want mixing.
  // For simplicity, let's use the device's binded stream if available,
  // but it's easier to just use SDL_PutAudioStreamData on a stream binded to the device.

  static SDL_AudioStream* playback_stream = nullptr;
  if (playback_stream == nullptr) {
    playback_stream = SDL_CreateAudioStream(&g_AudioSpec, &g_AudioSpec);
    SDL_BindAudioStream(g_AudioDeviceID, playback_stream);
  }

  SDL_ClearAudioStream(playback_stream);
  SDL_PutAudioStreamData(playback_stream, audio->buf, audio->len);
}
