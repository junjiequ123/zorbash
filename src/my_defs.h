//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#pragma once
#ifndef _MY_DEFS_H_
#define _MY_DEFS_H_

#define ENABLE_ASSERT        // Abort on errors
#define ENABLE_CRASH_HANDLER // Intercept SEGV

//
// RUN with --debug for extra memory checks
//
// RUN with --debug2 for out of bounds checks
//
#define ENABLE_DEBUG_TRACE               // (SLOW) Function tracing
#define ENABLE_DEBUG_EXTRA_BOUNDS_CHECKS // (SLOW)

#undef ENABLE_DEBUG_AI           // Monster AI decisions
#undef ENABLE_DEBUG_AI_ASTAR     // Astar AI path costs
#undef ENABLE_DEBUG_AI_WANDER    // AI wander path selection
#undef ENABLE_DEBUG_GFX_GL_BLEND // Use to debug specific blends
#undef ENABLE_DEBUG_PTRCHECK     // (VERY SLOW) Debug ptrcheck itself
#undef ENABLE_DEBUG_TILE         // Astar AI path costs
#undef ENABLE_DEBUG_UI           // User interface logs
#undef ENABLE_DEBUG_UI2          // User interface logs with inheritance
#undef ENABLE_DEBUG_UI_FOCUS     // Which windows we are over
#undef ENABLE_DEBUG_MEM_LEAKS
#undef ENABLE_DEBUG_THING_SER // Extra debugging in thing save/load

#define ENABLE_PTRCHECK_HISTORY 2 // Per pointer history
#undef ENABLE_LOG_TIMESTAMPS      // Full timestamps with date in logs
#undef ENABLE_UI_ASCII_MOUSE      // Show an in game mouse, not system mouse

#define ENABLE_SAVE_SNAPSHOT_FREQ 42 // How often/move count, to save a snapshot

#endif
