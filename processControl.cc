/*
 * Filename        processControl.cc
 * Date            23 April 2019
 * Author          Noah Monaghan
 * Email           noah.monaghan@utdallas.edu
 * Course          CS 3377.502 Spring 2019
 * Version         1.0
 * Copyright 2019, All Rights Reserved
 *
 * Description
 *
 *     Creates and maintains the daemon. 
 */

#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include "program5.h"

void startDaemon() {
  //open pid file as fstream to check if it already exists
  std::fstream pidFile ("cs3376dirmond.pid");
  
  //checks if pid file already exists
  if (pidFile.good()) {
    log_file << "Error daemon already running" << std::endl;
    log_file.close();

    std::exit(EXIT_FAILURE);
  }
  pidFile.close();

  //create daemonized child process
  pid_t pid = fork();

  //negative pid means it failed
  if (pid < 0) {
    log_file << "Error starting daemon" << std::endl;
    log_file.close();

    std::exit(EXIT_FAILURE);
  }
  //pid equal to zero means its the child
  else if (pid == 0) {
    log_file << "Child pid is " << getpid() << std::endl;

    //give daemon new SID for the OS
    pid_t sid = setsid();
    if (sid < 0) {
      log_file << "Error setting new SID" << std::endl;
	  log_file.close();

      exit(EXIT_FAILURE);
    }
    if (results[verbose] == "true") {
      log_file << "Child sid is " << sid << std::endl;
    }
    if (results[verbose] == "true") {
      log_file << "Successfully set new SID!" << std::endl;
    }

    //give daemon all file privileges
    umask(0);
    if (results[verbose] == "true") {
      log_file << "Successfully set file permissions!" << std::endl;
    }
   
    //open pid file to write child pid
    pidFile.open("cs3376dirmond.pid", std::ios::out);
    pidFile << getpid() << std::endl;
    pidFile.close();
    if (results[verbose] == "true") {
      log_file << "Successfully wrote pid to cs3376dirmond.pid!" << std::endl;
    }

    //if all actions above were successful, loop can start
    if (results[verbose] == "true") {
      log_file << "Successfully started daemon!" << std::endl;
    }
  }
  else {
    if (results[verbose] == "true") {
      log_file << "Exiting parent process..." << std::endl;
    }
    log_file.close();

    std::exit(EXIT_SUCCESS);
  }
}
