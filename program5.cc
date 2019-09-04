/*
 * Filename        program5.cc
 * Date            23 April 2019
 * Author          Noah Monaghan
 * Email           noah.monaghan@utdallas.edu
 * Course          CS 3377.502 Spring 2019
 * Version         1.0
 * Copyright 2019, All Rights Reserved
 *
 * Description
 *
 *     Contains the functionality for program5. 
 */

#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <sys/inotify.h>
#include "program5.h"

using namespace std;

ofstream log_file;
int fileDescriptor, wd;

int main(int argc, char* argv[]) {
  //parse commandline arguments
  tclap(argc, argv);

  //parse the config file
  parseConfigFile(false);

  //open log_file file for writing
  log_file.open(results[logFile]);
  if (results[verbose] == "true") {
    log_file << "Successfully started log file!" << std::endl;
  }
  if (results[verbose] == "true") {
    log_file << "isDaemon: " << results[isDaemon] << std::endl;
    log_file << "infile: " << results[infile] << std::endl;
    log_file << "verbose: " << results[verbose] << std::endl;
    log_file << "logFile: " << results[logFile] << std::endl;
    log_file << "password: " << results[password] << std::endl;
    log_file << "numVersions: " << results[numVersions] << std::endl;
    log_file << "watchDir: " << results[watchDir] << std::endl;
  }

  //start daemon if flagged
  if (results[isDaemon] == "true") {
    startDaemon();
  }

  //assign signal handlers to signals 1, 2, and 15
  signal(SIGHUP, signal_handler);
  signal(SIGINT, signal_handler);
  signal(SIGTERM, signal_handler);
  if (results[verbose] == "true") {
    log_file << "Successfully setup signal handling!" << std::endl;
  }

  //initialize inotify
  fileDescriptor = inotify_init();
  if (fileDescriptor < 0) {
    log_file << "Error initializing inotify" << std::endl;
    log_file.close();

    std::exit(EXIT_FAILURE);
  }
  else if (results[verbose] == "true") {
    log_file << "Successfully initialized inotify!" << std::endl;
  }

  //add watch directory
  wd = inotify_add_watch(fileDescriptor, results[watchDir].c_str(), IN_MODIFY);
  if (wd < 0) {
    log_file << "Error adding watch directory" << std::endl;
    log_file.close();

    std::exit(EXIT_FAILURE);
  }
  else if (results[verbose] == "true") {
    log_file << "Successfully added watch directory!" << std::endl;
  }
  log_file << "Watching: " << results[watchDir] << std::endl;

  //watch the speficied directory for changes
  while(1) {
    watchModify();
    sleep(1);
  }

  //exits successfully since no exception was thrown
  return EXIT_SUCCESS;
}
