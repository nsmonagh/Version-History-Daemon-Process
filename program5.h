/*
 * Filename        program5.h
 * Date            23 April 2019
 * Author          Noah Monaghan
 * Email           noah.monaghan@utdallas.edu
 * Course          CS 3377.502 Spring 2019
 * Version         1.0
 * Copyright 2019, All Rights Reserved
 *
 * Description
 *
 *     Contains shared resources between
 *     all files required for program 5.
 */

#ifndef PROGRAM5_H
#define PROGRAM5_H

#include <csignal>
#include <fstream>
#include <map>
#include <string>

enum result {isDaemon, infile, verbose, logFile, password, numVersions, watchDir};

extern std::map<result, std::string> results;

extern std::ofstream log_file;

extern int fileDescriptor;

extern int wd;

void tclap(int, char* []);

void parseConfigFile(bool);

void startDaemon();

void signal_handler(int);

void watchModify();

std::string boolToString(bool b);

#endif // PROGRAM5_H
