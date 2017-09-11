// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "butil/process/process_handle.h"

#include "butil/file_util.h"
#include "butil/process/internal_linux.h"

namespace butil {

ProcessId GetParentProcessId(ProcessHandle process) {
  ProcessId pid =
      internal::ReadProcStatsAndGetFieldAsInt64(process, internal::VM_PPID);
  if (pid)
    return pid;
  return -1;
}

FilePath GetProcessExecutablePath(ProcessHandle process) {
  FilePath stat_file = internal::GetProcPidDir(process).Append("exe");
  FilePath exe_name;
  if (!ReadSymbolicLink(stat_file, &exe_name)) {
    // No such process.  Happens frequently in e.g. TerminateAllChromeProcesses
    return FilePath();
  }
  return exe_name;
}

}  // namespace butil
