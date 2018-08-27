/*
 * Copyright (C) 2018 goblinhack@gmail.com
 *
 * See the README file for license info.
 */

#pragma once

#ifndef _MY_MAIN_H_
#define _MY_MAIN_H_

#define ENABLE_ASSERT              // DIE on errors
#undef  ENABLE_PTRCHECK            // Check validity of pointers too
#undef  ENABLE_CRASH_HANDLER       // Intercept SEGV
#undef  ENABLE_GENERATE_TTF        // Edit .RUNME, look for ENABLE_GENERATE_TTF
#define ENABLE_INVERTED_GFX        // For vision impaired
#define ENABLE_THING_SANITY        // Checks on thing insert

/*
 * How much the wheel mouse moves.
 */
#define ENABLE_WHEEL_SCROLL_SPEED_SCALE         1.0
#define ENABLE_WHEEL_MAX_SCROLL_SPEED_SCALE     10

#define ENABLE_JOY_SCROLL_SPEED_SCALE           1.0
#define ENABLE_JOY_MAX_SCROLL_SPEED_SCALE       1.5

/*
 * Dungeon size
 */
#define GRID_WIDTH                  8
#define GRID_HEIGHT                 7

#define ROOM_WIDTH                  13
#define ROOM_HEIGHT                 9

#define MAP_WIDTH                   (GRID_WIDTH * ROOM_WIDTH)
#define MAP_HEIGHT                  (GRID_HEIGHT * ROOM_HEIGHT)

#define TILES_ACROSS                40 // per screen
#define TILES_DOWN                  24

#define MAX_TILE_WIDTH              64
#define MAX_TILE_HEIGHT             64

#define TILE_WIDTH                  32
#define TILE_HEIGHT                 32

/*
 * Console
 */
#define CONSOLE_CURSOR_COLOR        GRAY
#define CONSOLE_CURSOR_OTHER_COLOR  WHITE
#define CONSOLE_TEXT_COLOR          GRAY
#define CONSOLE_WIDTH               200
#define CONSOLE_HEIGHT              300

/*
 * Fonts
 */
#define FIXED_FONT                  "data/ttf/dejavu-nerd.ttf"
#define FONT_SIZE                   80

#define TTF_GLYPH_MIN               ' '
#define TTF_GLYPH_MAX               0xffff // SDL can only do 2b fonts
#define TTF_GLYPH_PER_ROW           60
#define TTF_CURSOR_CHAR             127

/*
 * Maximum number of thing types. This cannot be exceeded without changing
 * the message format in tx updates.
 */
#define TP_MAX                      10000

#include <string>

/*
 * Enhanced random number generator.
 */
#include "my_pcg_basic.h"
#define myrand()           pcg32_random()
#define mysrand(a)         pcg32_srandom(a,a)
#define random_range(a, b) (pcg32_boundedrand(b - a) + a)

//#define myrand() rand()

//#define mysrand(a) srand(a)

/*
 * Simple array routines
 */
#define ARRAY_SIZE(_array_)             (sizeof(_array_)/sizeof(_array_[0]))

#define FOR_ALL_IN_ARRAY(iterator, _array_)                                 \
    __typeof__(&_array_[0]) iterator;                                       \
    for ((iterator) = (_array_);                                            \
         (iterator) < ((_array_) + ARRAY_SIZE(_array_));                    \
         (iterator)++)

#define FOR_NEXT_IN_ARRAY(iterator, _array_)                                \
    for ((iterator)++;                                                      \
         (iterator) < ((_array_) + ARRAY_SIZE(_array_));                    \
         (iterator)++)

/*
 * GCC extension for offset
 */
#ifdef __GNUC__
#if defined(__GNUC__) && __GNUC__ > 3
#define STRUCT_OFFSET(STRUCT, MEMBER) __builtin_offsetof(STRUCT, MEMBER)
#else
#define STRUCT_OFFSET(STRUCT, MEMBER) \
                     ((size_t) ( (char *)&((st *)0)->m - (char *)0 ))
#endif
#else
#define STRUCT_OFFSET(STRUCT, MEMBER) \
                     ((size_t) ( (char *)&((st *)0)->m - (char *)0 ))
#endif

#define likely(x)       __builtin_expect((x),1)
#define unlikely(x)     __builtin_expect((x),0)

/*
 * Types
 */
#ifndef _BITS_STDINT_INTN_H
#ifndef __int8_t_defined
#ifndef _INT8_T
#define _INT8_T
typedef signed char          int8_t;
#endif /*_INT8_T */

#ifndef _INT16_T
#define _INT16_T
typedef short                int16_t;
#endif /* _INT16_T */

#ifndef _INT32_T
#define _INT32_T
typedef int                  int32_t;
#endif /* _INT32_T */

#ifndef _INT64_T
#define _INT64_T
typedef long long            int64_t;
#endif /* _INT64_T */
#endif

#ifndef _UINT8_T
#define _UINT8_T
typedef unsigned char        uint8_t;
#endif /*_UINT8_T */

#ifndef _UINT16_T
#define _UINT16_T
typedef unsigned short       uint16_t;
#endif /* _UINT16_T */

#ifndef _UINT32_T
#define _UINT32_T
typedef unsigned int         uint32_t;
#endif /* _UINT32_T */

#ifndef _UINT64_T
#define _UINT64_T
typedef unsigned long long   uint64_t;
#endif /* _UINT64_T */
#endif

/*
 * msys functions seem to accept either / or \ so we don't need to worry.
 */
#define DSEP "/"
#define DCHAR '/'

#define DIE(args...)                                                          \
    DYING("Died at %s:%s():%u", __FILE__, __FUNCTION__, __LINE__);            \
    CROAK(args);                                                              \
    exit(1);

extern uint8_t croaked;

#ifdef ENABLE_ASSERT
#define ASSERT(x)                                                             \
    if (!(x)) {                                                               \
        DIE("Failed assert");                                                 \
    }
#else
#define ASSERT(x)
#endif

void CROAK(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
void DYING(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
void LOG(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
void LOGS(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
void WARN(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
void CON(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
void TIP(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
void TIP2(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));

void CON(const wchar_t *fmt, ...);
void TIP(const wchar_t *fmt, ...);
void TIP2(const wchar_t *fmt, ...);

void con (const wchar_t *fmt);
void tip2 (const wchar_t *fmt);
void tip (const wchar_t *fmt);

#include "my_callstack.h"

void SDL_MSG_BOX(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
void MSG_BOX(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
void ERR(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
void DBG(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));

/*
 * main.c
 */
extern FILE *LOG_STDOUT;
extern FILE *LOG_STDERR;

#define MY_STDOUT (LOG_STDOUT ? LOG_STDOUT : stdout)
#define MY_STDERR (LOG_STDERR ? LOG_STDERR : stderr)

extern char *EXEC_FULL_PATH_AND_NAME;
extern char *EXEC_DIR;
extern char *DATA_PATH;
extern char *PYTHON_PATH;
extern char *GFX_PATH;
extern char *TTF_PATH;
extern uint8_t quitting;

void quit(void);
void restart(void);
void die(void);
int cereal_test(const std::string save_file);

#endif
