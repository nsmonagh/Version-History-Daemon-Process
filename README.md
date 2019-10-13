## Version History Tracker

A command line application used to monitor a specified directory in cs3376dirmond.conf, and create backups of every modified file in a hidden folder called .verions located in the same place.

## Installation and Setup Instructions

Clone this repository. You will need `make`, `g++`, `tlcap`, and `rudeconfig` installed on your machine.

Installation for Ubuntu:

* `sudo apt-get install make g++`

* `wget https://downloads.sourceforge.net/project/tclap/tclap-1.2.2.tar.gz`

* `wget http://rudeserver.com/config/download/rudeconfig-5.0.5.tar.gz`

To Run the Application:

* Compile tclap and rudeconfig.

* Create a static library of the .o files in rudeconfig.

* Change the paths in the Makefile to point to compiled resources.

* Navigate to the cloned repository and run `make`.

* Then to run the application type `./cs3376dirmond`
