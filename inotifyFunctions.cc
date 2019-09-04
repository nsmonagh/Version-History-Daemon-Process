/*
 * Filename        inotifyFunctions.cc
 * Date            23 April 2019
 * Author          Noah Monaghan
 * Email           noah.monaghan@utdallas.edu
 * Course          CS 3377.502 Spring 2019
 * Version         1.0
 * Copyright 2019, All Rights Reserved
 *
 * Description
 *
 *     Contains the functions for inotify.
 */

#include <array>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <linux/limits.h>
#include <sys/inotify.h>
#include "program5.h"

void watchModify() {
  size_t bufsiz = sizeof(struct inotify_event)+PATH_MAX+1;
  struct inotify_event *event = (struct inotify_event *) malloc(bufsiz);
  int length = read(fileDescriptor, event, bufsiz);

  if (results[verbose] == "true") {
    log_file << "Successfully read a new change in the watch directory!" << std::endl;
  }
  if ( length < 0 ) {
    log_file << "Error reading length of file descriptor" << std::endl;
    log_file.close();

    std::exit(EXIT_FAILURE);
  }  

  if (event->len) {
    if (event->mask & IN_MODIFY) {
      //get output of formatted date command
      std::string command = "date +\".%Y.%m.%d-%H:%M:%S\"";
      FILE* pipe = popen(command.c_str(), "r"); // open pipe to output
      std::array<char, 128> buffer;     // initialize buffer
      fgets(buffer.data(), 128, pipe);  // get pipe output into buffer
      pclose(pipe);                     // close pipe
	  if (results[verbose] == "true") {
        log_file << "Successfully calculated current date formatted as m.%Y.%m.%d-%H:%M:%S!" << std::endl;
      }

      //make directory .versions in watch directory if it does not exist
      command = "mkdir -p ";
      system(command.append(results[watchDir]).append("/.versions/").c_str());
	  if (results[verbose] == "true") {
        log_file << "Successfully checked that .versions directory exists in watched directory" << std::endl;
      }

      //copy file from watchDir to versions subfolder
      command = "cp ";
      system(command.append(results[watchDir]).append("/").append(event->name).append(" ").append(results[watchDir]).append("/.versions/").append(event->name).append(buffer.data()).c_str());
      if (results[verbose] == "true") {
        log_file << "Successfully copied modified file into versions folder!" << std::endl;
      }
      log_file << "File " << event->name << " was modified and placed into .versions" << std::endl;
    }
  }
}