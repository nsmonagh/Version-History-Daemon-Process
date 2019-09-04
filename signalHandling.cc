/*
 * Filename        signalHandling.cc
 * Date            23 April 2019
 * Author          Noah Monaghan
 * Email           noah.monaghan@utdallas.edu
 * Course          CS 3377.502 Spring 2019
 * Version         1.0
 * Copyright 2019, All Rights Reserved
 *
 * Description
 *
 *     Handles signals to control the daemon. 
 */

#include <iostream>
#include <unistd.h>
#include <sys/inotify.h>
#include "program5.h"

void signal_handler(int signal) {
  switch(signal) {
    case 1:
      //reparse the config file
      parseConfigFile(true);
	  log_file.close();
	  log_file.open(results[logFile]);
      if (results[verbose] == "true") {
        log_file << "Successfully reparsed the config file!" << std::endl;
      }
	  if (results[verbose] == "true") {
        log_file << "verbose: " << results[verbose] << std::endl;
        log_file << "logFile: " << results[logFile] << std::endl;
        log_file << "numVersions: " << results[numVersions] << std::endl;
      }
      break;
    case 2:
    case 15:
      //cleanup inotify
      inotify_rm_watch(fileDescriptor, wd);
      close(fileDescriptor);
	  if (results[isDaemon] == "true") {
        //remove pid file
        if (remove("cs3376dirmond.pid") != 0) {
          log_file << "Error deleting cs3376dirmond.pid" << std::endl;
        }
        else if (results[verbose] == "true") {
          log_file << "Successfully deleted cs3376dirmond.pid!" << std::endl;
        }
	  }
      //close log_file file
      log_file.close();
      //kill daemon
      std::exit(EXIT_SUCCESS);
    default:
      break;
  }
}
