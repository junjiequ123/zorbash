//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <strings.h> // do not remove
#include <string.h> // do not remove
#include <time.h> // do not remove
#include <unistd.h> // do not remove
#include <signal.h> // dirname
#include "my_sys.h"
#include "my_game.h"
#include "my_globals.h"
#include "my_traceback.h"

void callstack_dump (void)
{_
  IF_NODEBUG2 {
    return;
  }

  static int done;
  if (done) {
    return;
  }

  done = true;

  fprintf(MY_STDERR, "code trace\n");
  fprintf(MY_STDERR, "==========\n");
  for (auto depth = 0; depth < g_callframes_depth; depth++) {
    auto iter = &callframes[depth];
    fprintf(MY_STDERR, "(stack) %d %s, line %u\n", depth, iter->func, iter->line);
  }

  CON("code trace");
  CON("==========");
  for (auto depth = 0; depth < g_callframes_depth; depth++) {
    auto iter = &callframes[depth];
    CON("(stack) %d %s, line %u", depth, iter->func, iter->line);
  }
  done = false;
}

#ifdef ENABLE_CRASH_HANDLER

#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#if defined(__linux__)
#include <sys/prctl.h>
#include <linux/limits.h>
#endif

#ifdef __APPLE__
#include <sys/syslimits.h> // PATH_MAX
#include <mach-o/dyld.h>
#endif

#ifndef PATH_MAX
#define PATH_MAX 512
#endif

//
// Should work on linux only.
//
static void
debug_crash_handler(int sig)
{
  fprintf(stderr, "debug_crash_handler: Error: Signal %d:\n", sig);

  std::string pid(std::to_string(getpid()));

  const size_t max_path = PATH_MAX + 1;
  char prog_name[max_path];

#if defined __APPLE__
  uint32_t bufsize = max_path;
  _NSGetExecutablePath(prog_name, &bufsize);
#elif defined WIN32
  HMODULE module = GetModuleHandleA(NULL);
  GetModuleFileNameA(module, prog_name, max_path);
#elif defined __linux__
  int ret = readlink("/proc/self/exe", prog_name, max_path - 1);
  if (ret == -1) {
    ERR("Debug_crash_handler: Read process name failed");
    return;
  }

  if ((size_t)ret >= max_path) {
    ERR("Debug_crash_handler: Symlink too long");
  return;
  }
#else
  return;
#endif

#if defined __linux__
  //
  // Permissions for GDB
  //
  prctl(PR_SET_PTRACER, PR_SET_PTRACER_ANY, 0, 0, 0);
#endif

  auto child = fork();
  if (!child) {
    //
    // Start GDB
    //
#ifdef __APPLE__
    execl("/usr/bin/lldb", "lldb", "-p", pid.c_str(), nullptr);
#else
    execl("/usr/bin/gdb", "gdb", "--batch", "-n",
        "-ex", "thread apply all bt", prog_name, pid.c_str(), nullptr);
#endif
    assert(false && "Debugger failed to exec");
  } else {
    //
    // Wait for the child to stop
    //
    waitpid(child, nullptr, 0);
  }
}

void segv_handler (int sig)
{_
  static int crashed;

  if (crashed) {
    fprintf(MY_STDERR, "Nested crash!!!");
    exit(1);
  }

  crashed = 1;
  fprintf(MY_STDERR, "Crash!!!");
  traceback_dump();
  ERR("Crashed");

#if defined __linux__
  //
  // Seems to cause hang issues on mac M1
  //
  debug_crash_handler(sig);
#endif
}

void ctrlc_handler (int sig)
{_
  fprintf(MY_STDERR, "Interrupted!!!");
  traceback_dump();
  DIE_CLEAN("Interrupted");
}
#endif
