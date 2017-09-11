// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "test/multiprocess_test.h"

#include "butil/base_switches.h"
#include "butil/command_line.h"

namespace butil {

#if !defined(OS_ANDROID)
ProcessHandle SpawnMultiProcessTestChild(
    const std::string& procname,
    const CommandLine& base_command_line,
    const LaunchOptions& options) {
  CommandLine command_line(base_command_line);
  // TODO(viettrungluu): See comment above |MakeCmdLine()| in the header file.
  // This is a temporary hack, since |MakeCmdLine()| has to provide a full
  // command line.
  if (!command_line.HasSwitch(switches::kTestChildProcess))
    command_line.AppendSwitchASCII(switches::kTestChildProcess, procname);

  ProcessHandle handle = kNullProcessHandle;
  LaunchProcess(command_line, options, &handle);
  return handle;
}
#endif  // !defined(OS_ANDROID)

CommandLine GetMultiProcessTestChildBaseCommandLine() {
  return *CommandLine::ForCurrentProcess();
}

// MultiProcessTest ------------------------------------------------------------

MultiProcessTest::MultiProcessTest() {
}

ProcessHandle MultiProcessTest::SpawnChild(const std::string& procname) {
  LaunchOptions options;
#if defined(OS_WIN)
  options.start_hidden = true;
#endif
  return SpawnChildWithOptions(procname, options);
}

ProcessHandle MultiProcessTest::SpawnChildWithOptions(
    const std::string& procname,
    const LaunchOptions& options) {
  return SpawnMultiProcessTestChild(procname, MakeCmdLine(procname), options);
}

CommandLine MultiProcessTest::MakeCmdLine(const std::string& procname) {
  CommandLine command_line = GetMultiProcessTestChildBaseCommandLine();
  command_line.AppendSwitchASCII(switches::kTestChildProcess, procname);
  return command_line;
}

}  // namespace butil
