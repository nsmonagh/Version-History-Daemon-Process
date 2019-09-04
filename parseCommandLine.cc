/*
 * Filename        parseCommandLine.cc
 * Date            23 April 2019
 * Author          Noah Monaghan
 * Email           noah.monaghan@utdallas.edu
 * Course          CS 3377.502 Spring 2019
 * Version         1.0
 * Copyright 2019, All Rights Reserved
 *
 * Description
 *
 *     Contains the command line parser
 *     for program5.
 */

#include <utility>
#include <tclap/CmdLine.h>
#include "program5.h"

std::map<result, std::string> results;

std::string boolToString(bool b) {
  return b ? "true" : "false";
}

int indexOf(char* argv[], int argc, std::string argument) {
  int index = 0;
  while (index < argc && argv[index] != argument) ++index;
  return (index == argc ? -1 : index);
}

void tclap(int argc, char* argv[]) {
  //create the command line parser
  TCLAP::CmdLine cmd("cs3376dirmond Directory Monitor Daemon", ' ', "1.0");

  //create switch argument for daemon mode
  TCLAP::SwitchArg daemonSwitch("d", "daemon", "Run in daemon mode (forks to run as a daemon).", cmd, false);
  //create unlabled value argument for input filename
  TCLAP::UnlabeledValueArg<std::string> infileArg("infile", "The name of the configuration file. Defaults to cs3376dirmond.conf", false, "cs3376dirmond.conf", "config filename", cmd);

  //try-catch loop for parsing errors
  try {
    //parse command line arguments
    cmd.parse(argc, argv);
  } catch (TCLAP::ArgException &e) {
    //prints usage for command
    cmd.getOutput()->usage(cmd);
    //exits with failure since exception was thrown
    std::exit(EXIT_FAILURE);
  }

  //insert each result into the results map
  results.insert(std::pair<result, std::string>(isDaemon, boolToString(daemonSwitch.getValue())));
  results.insert(std::pair<result, std::string>(infile, infileArg.getValue()));
}
