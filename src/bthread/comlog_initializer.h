// bthread - A M:N threading library to make applications more concurrent.
// Copyright (c) 2014 Baidu, Inc.
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//     http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// Author: Ge,Jun (gejun@baidu.com)
// Date: Mon Sep 15 10:51:15 CST 2014

#ifndef PUBLIC_BTHREAD_BTHREAD_COMLOG_INITIALIZER_H
#define PUBLIC_BTHREAD_BTHREAD_COMLOG_INITIALIZER_H

#include <com_log.h>                       // com_openlog_r, com_closelog_r
#include <butil/macros.h>

namespace bthread {

class ComlogInitializer {
public:
    ComlogInitializer() {
        if (com_logstatus() != LOG_NOT_DEFINED) {
            com_openlog_r();
        }
    }
    ~ComlogInitializer() {
        if (com_logstatus() != LOG_NOT_DEFINED) {
            com_closelog_r();
        }
    }
    
private:
    DISALLOW_COPY_AND_ASSIGN(ComlogInitializer);
};

}

#endif // PUBLIC_BTHREAD_BTHREAD_COMLOG_INITIALIZER_H
