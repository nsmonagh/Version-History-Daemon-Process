#!/usr/bin/make -f
#
# Filename:        Makefile
# Date:            23 April 2019
# Author:          Noah Monaghan
# Email:           noah.monaghan@utdallas.edu
# Version:         1.1
# Copyright 2019, All Rights Reserved
#
# Description
#
#     Originally derived from an example given
#     courtesy of Dr. Stephen Perkins, this
#     simplified version has been modified to
#     make program4 using implicit rules.

CXX = g++
CPPFLAGS = -I /home/011/n/ns/nsm170001/include
CXXFLAGS = -Wall -Wextra -Werror -std=c++11
LDFLAGS = -L /home/011/n/ns/nsm170001/libs -static
LDLIBS = -l:librudeconfig.a
PROJECTNAME = assignment_4
EXEC = cs3376dirmond
OBJS = parseCommandLine.o parseConfigFile.o program5.o processControl.o inotifyFunctions.o signalHandling.o

.PHONY: all clean

all: $(EXEC)

clean:
	rm -f $(OBJS) *~ $(EXEC) *.log

$(EXEC): $(OBJS)
	$(CXX) -o $(EXEC) $(OBJS) $(LDFLAGS) $(LDLIBS)

backup:	clean
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURDIRNAME := $(shell basename `pwd`))
	@$(eval MKBKUPNAME := ~/backups/$(PROJECTNAME)-$(shell date +'%Y.%m.%d-%H:%M:%S').tar.gz)
	@echo
	@echo Writing Backup file to: $(MKBKUPNAME)
	@echo
	@-tar zcfv $(MKBKUPNAME) ../$(CURDIRNAME)
	@chmod 600 $(MKBKUPNAME)
	@echo
	@echo Done!
