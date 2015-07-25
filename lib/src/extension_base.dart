// Copyright (c) 2015, <your name>. All rights reserved. Use of this source code
// is governed by a BSD-style license that can be found in the LICENSE file.

library extension.base;

import 'dart-ext:extension';

import 'dart:io';

const int DOKAN_VERSION               = 730;

const int DOKAN_OPTION_DEBUG          = 1;
const int DOKAN_OPTION_STDERR         = 2;
const int DOKAN_OPTION_ALT_STREAM     = 4;
const int DOKAN_OPTION_KEEP_ALIVE     = 8;
const int DOKAN_OPTION_NETWORK        = 16;
const int DOKAN_OPTION_REMOVABLE      = 32;

const int DOKAN_SUCCESS               = 0;
const int DOKAN_ERROR                 = -1;
const int DOKAN_DRIVE_LETTER_ERROR    = -2;
const int DOKAN_DRIVE_INSTALL_ERROR   = -3;
const int DOKAN_START_ERROR           = -4;
const int DOKAN_MOUNT_ERROR           = -5;
const int DOKAN_MOUNT_POINT_ERROR     = -6;

String RootDirectory = "C:";

class DokanOptions {
  int version;
  int threadCount;
  int options;
  int globalContext;
  String mountPoint;

  DokanOptions() {
    options = 0;
    threadCount = 0;
    globalContext = 0;
  }
}

abstract class DokanOperations {
  int createFile(String filename, int accessMode, int sharedMode, int creationDisposition, int flagsAndAttributes);
}

void DbgPrint(String message) {
  stderr.write(message);
}

int DokanMain(DokanOptions dokan_options, DokanOperations dokan_operations) native "DokanMain";
