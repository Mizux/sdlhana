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

#ifndef MAIN_H_
#define MAIN_H_

#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifdef _WIN32
#include <io.h>
#include <windows.h>
#define vsnprintf _vsnprintf
#else
#include <unistd.h>
#endif

#include <SDL3/SDL.h>

// Compatibility macros for SDL3 migration
#ifdef SDL_FreeSurface
#undef SDL_FreeSurface
#endif
#define SDL_FreeSurface SDL_DestroySurface

#ifdef SDL_SetColorKey
#undef SDL_SetColorKey
#endif
#define SDL_SetColorKey(s, b, k) SDL_SetSurfaceColorKey(s, b, k)

#ifdef SDL_FillRect
#undef SDL_FillRect
#endif
#define SDL_FillRect SDL_FillSurfaceRect

#ifdef SDL_MUSTLOCK
#undef SDL_MUSTLOCK
#endif
#define SDL_MUSTLOCK(s) false

#ifdef SDL_FreeCursor
#undef SDL_FreeCursor
#endif
#define SDL_FreeCursor SDL_DestroyCursor

#ifdef AUDIO_S16
#undef AUDIO_S16
#endif
#define AUDIO_S16 SDL_AUDIO_S16LE

#define SDL_HWSURFACE 0
#define SDL_SWSURFACE 0
#define SDL_SRCALPHA 0
#define SDL_SRCCOLORKEY true
#define SDL_Rmask 0
#define SDL_Gmask 0
#define SDL_Bmask 0
#define SDL_Amask 0
#define SDL_WM_SetCaption(t, i) SDL_SetWindowTitle(gpWindow, t)
#define SDL_UpdateRect(s, x, y, w, h) SDL_UpdateWindowSurface(gpWindow)
#define SDL_Flip(s) SDL_UpdateWindowSurface(gpWindow)
#define SDL_CreateRGBSurface(f, w, h, bpp, rm, gm, bm, am) SDL_CreateSurface(w, h, (gpScreen ? gpScreen->format : SDL_PIXELFORMAT_XRGB8888))
#define SDLK_LAST 1000
#define SDL_INIT_TIMER 0
#define SDL_AUDIO_S16 SDL_AUDIO_S16LE
#define SDL_MIX_MAXVOLUME 128
#define SDL_FULLSCREEN SDL_WINDOW_FULLSCREEN
#define SDL_SoftStretch(src, sr, dst, dr) SDL_BlitSurfaceScaled(src, sr, dst, dr, SDL_SCALEMODE_NEAREST)

inline const SDL_PixelFormatDetails* SDL_GetSurfaceFormatDetails(SDL_Surface* s) {
    return SDL_GetPixelFormatDetails(s->format);
}

#undef SDL_GetRGB
#undef SDL_MapRGB
#undef SDL_MapRGBA

inline void SDL_GetSurfaceRGB(Uint32 pixel, SDL_PixelFormat format, Uint8* r, Uint8* g, Uint8* b) {
    SDL_GetRGB(pixel, SDL_GetPixelFormatDetails(format), NULL, r, g, b);
}

inline Uint32 SDL_MapSurfaceRGB(SDL_PixelFormat format, Uint8 r, Uint8 g, Uint8 b) {
    return SDL_MapRGB(SDL_GetPixelFormatDetails(format), NULL, r, g, b);
}

inline Uint32 SDL_MapSurfaceRGBA(SDL_PixelFormat format, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    return SDL_MapRGBA(SDL_GetPixelFormatDetails(format), NULL, r, g, b, a);
}

#define SDL_GetRGB(pixel, format, r, g, b) SDL_GetSurfaceRGB(pixel, format, r, g, b)
#define SDL_MapRGB(format, r, g, b) SDL_MapSurfaceRGB(format, r, g, b)
#define SDL_MapRGBA(format, r, g, b, a) SDL_MapSurfaceRGBA(format, r, g, b, a)

struct SDL_AudioCVT_Compat {
    Uint8* buf;
    int len;
    int len_mult;
};

#define SDL_AudioCVT SDL_AudioCVT_Compat

#include "ini.hpp"

#ifdef WITH_CONFIG_H
#include "config.h"
#endif

#ifndef PREFIX
#define PREFIX "./"
#endif

#ifndef DATA_ROOT
#define DATA_ROOT PREFIX
#endif

#ifndef DATA_DIR
#define DATA_DIR DATA_ROOT "data/"
#endif

#ifndef CONFIG_FILE
#define CONFIG_FILE DATA_DIR "sdlhana.ini"
#endif

#ifndef SOUND_DIR
#define SOUND_DIR DATA_DIR "sfx/"
#endif

#ifndef IMAGES_DIR
#define IMAGES_DIR DATA_DIR "gfx/"
#endif

#ifndef FONTS_DIR
#define FONTS_DIR DATA_DIR "fonts/"
#endif

extern SDL_Window*  gpWindow;
extern SDL_Surface* gpScreen;
extern bool         g_fNoSound;

// main.cpp functions...
void UserQuit();

// util.cpp functions...
void  trim(char* str);
char* va(const char* format, ...);
int   RandomLong(int from, int to);
void  TerminateOnError(const char* fmt, ...);

char*        UTIL_StrGetLine(const char* buf, int width, int& length);
unsigned int UTIL_GetPixel(SDL_Surface* surface, int x, int y);
void         UTIL_PutPixel(SDL_Surface* surface, int x, int y, unsigned int pixel);
int          UTIL_GetPixel(
             SDL_Surface*   f,
             int            x,
             int            y,
             unsigned char* r,
             unsigned char* g,
             unsigned char* b);
int UTIL_PutPixel(SDL_Surface* f, int x, int y, unsigned char r, unsigned char g, unsigned char b);
int UTIL_PutPixelAlpha(
    SDL_Surface*  f,
    int           x,
    int           y,
    unsigned char r,
    unsigned char g,
    unsigned char b,
    unsigned char a);
void         UTIL_RevertSurfaceX(SDL_Surface* s);
void         UTIL_RevertSurfaceY(SDL_Surface* s);
void         UTIL_RevertSurfaceXY(SDL_Surface* s);
SDL_Surface* UTIL_ScaleSurface(SDL_Surface* s, int w, int h);
int          UTIL_ScaleBlit(SDL_Surface* src, SDL_Rect* sr, SDL_Surface* dst, SDL_Rect* dr);
void         UTIL_Scale2X(SDL_Surface* src, SDL_Surface* dst);
void         UTIL_HorzLine(
            SDL_Surface*  surface,
            short         x,
            short         y,
            short         l,
            unsigned char r,
            unsigned char g,
            unsigned char b);
void UTIL_VertLine(
    SDL_Surface*  surface,
    short         x,
    short         y,
    short         l,
    unsigned char r,
    unsigned char g,
    unsigned char b);
void UTIL_Rect(SDL_Surface* surface, int x1, int y1, int w, int h, int r, int g, int b);
void UTIL_VertLineShade(
    SDL_Surface*  surface,
    short         x,
    short         y,
    short         l,
    unsigned char r1,
    unsigned char g1,
    unsigned char b1,
    unsigned char r2,
    unsigned char g2,
    unsigned char b2);
void UTIL_HorzLineShade(
    SDL_Surface*  surface,
    short         x,
    short         y,
    short         l,
    unsigned char r1,
    unsigned char g1,
    unsigned char b1,
    unsigned char r2,
    unsigned char g2,
    unsigned char b2);
void UTIL_RectShade(
    SDL_Surface* surface,
    int          x,
    int          y,
    int          w,
    int          h,
    int          r1,
    int          g1,
    int          b1,
    int          r2,
    int          g2,
    int          b2,
    int          rt,
    int          gt,
    int          bt);
void UTIL_FillRect(SDL_Surface* surface, int x, int y, int w, int h, int r, int g, int b);
void UTIL_FillRectAlpha(
    SDL_Surface* surface,
    int          x,
    int          y,
    int          w,
    int          h,
    int          r,
    int          g,
    int          b,
    int          a);
void UTIL_Delay(int duration);
void UTIL_ToggleFullScreen();

// text.cpp functions...
void        InitTextMessage();
void        FreeTextMessage();
const char* msg(const char* name);

// compress.cpp functions...
int Decode(const char* filename, int headersize, unsigned char* buffer, int bufsize);
int Encode(
    const char*    filename,
    unsigned char* header,
    int            headersize,
    unsigned char* buffer,
    int            bufsize);

// config.cpp functions...
void LoadCfg();
void SaveCfg();

// sound.cpp functions...
int           SOUND_OpenAudio(int freq, int format, int channels, int samples);
void          SOUND_FillAudio(void* udata, unsigned char* stream, int len);
void          SOUND_PlayWAV(SDL_AudioCVT* audio);
void          SOUND_FreeWAV(SDL_AudioCVT* audio);
SDL_AudioCVT* SOUND_LoadWAV(const char* filename);

extern CIniFile cfg;

#endif
