// Copyright (c) 2015, <your name>. All rights reserved. Use of this source code
// is governed by a BSD-style license that can be found in the LICENSE file.

library extension.example;

import 'dart:io';

import 'package:extension/extension.dart';

class Hello extends DokanOperations {

  int createFile(String filename, int accessMode, int sharedMode, int creationDisposition, int flagsAndAttributes) {
    return 1;
  }
}

void main() {
  DokanOptions dokan_options = new DokanOptions();
  dokan_options.version = DOKAN_VERSION;
  dokan_options.threadCount = 1;
  dokan_options.mountPoint = "f";

  dokan_options.options = 0;
  dokan_options.options |= DOKAN_OPTION_DEBUG;
  dokan_options.options |= DOKAN_OPTION_STDERR;
  dokan_options.options |= DOKAN_OPTION_KEEP_ALIVE;

  DokanOperations hello = new Hello();

  int status = DokanStart(dokan_options, hello);

  switch (status) {
    case DOKAN_SUCCESS:
      stderr.write("Success\n");
      break;
    case DOKAN_ERROR:
      stderr.write("Error\n");
      break;
    case DOKAN_DRIVE_LETTER_ERROR:
      stderr.write("Drive letter error\n");
      break;
    case DOKAN_DRIVE_INSTALL_ERROR:
      stderr.write("Driver install error\n");
      break;
    case DOKAN_START_ERROR:
      stderr.write("Driver something wrong\n");
      break;
    case DOKAN_MOUNT_ERROR:
      stderr.write("Can't assign a drive letter\n");
      break;
    case DOKAN_MOUNT_POINT_ERROR:
      stderr.write("Mount point error\n");
      break;
    default:
      stderr.write("Unknown error: $status\n");
      break;
  }

}