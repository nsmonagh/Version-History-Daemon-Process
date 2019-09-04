/*
 * Filename        parseConfigFile.cc
 * Date            23 April 2019
 * Author          Noah Monaghan
 * Email           noah.monaghan@utdallas.edu
 * Course          CS 3377.502 Spring 2019
 * Version         1.0
 * Copyright 2019, All Rights Reserved
 *
 * Description
 *
 *     Parses the config file for program5.
 */

#include <cstring>
#include <iostream>
#include <utility>
#include <rude/config.h>
#include "program5.h"

using namespace rude;

void parseConfigFile(bool initialized) {
  // Create config object
  Config config;
  // load a configuration/.ini file
  if(config.load(results[infile].c_str())) {
    // read parameters section
    if (config.setSection("Parameters", false)) {
      // first call reads in definitions
      if(!initialized) {
        // read Verbose definition
        if (strcmp(config.getStringValue("Verbose"), "") != 0) {
          results.insert(std::pair<result, std::string>(verbose, boolToString(config.getBoolValue("Verbose"))));
          std::cout << "Successfully read Verbose definition!" << std::endl;
        }
        else {
          std::cout << "Error reading Verbose definition" << std::endl;
          std::exit(EXIT_FAILURE);
        }

        // read LogFile definition
        if (config.exists("LogFile")) {
          if (strcmp(config.getStringValue("LogFile"), "") != 0) {
            results.insert(std::pair<result, std::string>(logFile, config.getStringValue("LogFile")));
            std::cout << "Successfully read LogFile definition!" << std::endl;
          }
          else {
            results.insert(std::pair<result, std::string>(logFile, "cs3376dirmond.log"));
            std::cout << "No LogFile definition provided...using default" << std::endl;
          }
        }
        else {
          std::cout << "Error reading LogFile definition" << std::endl;
          std::exit(EXIT_FAILURE);
        }

        // read Password definition
        if (strcmp(config.getStringValue("Password"), "") != 0) {
          results.insert(std::pair<result, std::string>(password, config.getStringValue("Password")));
          std::cout << "Successfully read password definition!" << std::endl;
        }
        else {
          std::cout << "Error reading Password definition" << std::endl;
          std::exit(EXIT_FAILURE);
        }

        // read NumVersions definition
        if (strcmp(config.getStringValue("NumVersions"), "") != 0) {
          results.insert(std::pair<result, std::string>(numVersions, std::to_string(config.getIntValue("NumVersions"))));
          std::cout << "Successfully read NumVersions definition!" << std::endl;
        }
        else {
          std::cout << "Error reading NumVersions definition" << std::endl;
          std::exit(EXIT_FAILURE);
        }

        // read WatchDir definition
        if (strcmp(config.getStringValue("WatchDir"), "") != 0) {
          results.insert(std::pair<result, std::string>(watchDir, config.getStringValue("WatchDir")));
          std::cout << "Successfully read WatchDir definition!" << std::endl;
        }
        else {
          std::cout << "Error reading WatchDir definition" << std::endl;
          std::exit(EXIT_FAILURE);
        }
      }
      // additional calls modify definitions
      else {
        results.find(verbose)->second = config.getStringValue("Verbose");

        results.find(logFile)->second = config.getStringValue("LogFile");

        results.find(numVersions)->second = config.getStringValue("NumVersions");
      }
    }
    else {
      std::cout << "Error reading Parameters section" << std::endl;
      std::exit(EXIT_FAILURE);
    }
  }
  else {
    std::cout << config.getError() << std::endl;
    std::exit(EXIT_FAILURE);
  }
}
