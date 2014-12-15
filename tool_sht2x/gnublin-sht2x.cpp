// gnublin-sht2x.cpp --- 
// 
// Filename     : gnublin-sht2x.cpp
// Description  : Tools for easly interacting with a SHT2x humidity and temperatur sensor.
// Author       : Christophe Burki
// Maintainer   : Christophe Burki
// Created      : Sat Sep 20 17:27:42 2014
// Version      : 1.0.0
// Last-Updated : Mon Oct 20 20:48:19 2014 (7200 CEST)
//           By : Christophe Burki
//     Update # : 60
// URL          : 
// Keywords     : 
// Compatibility: 
// 
// 

// Commentary   : 
// 
// 
// 
// 

// Change log:
// 
// 
// 
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 3 as
// published by the Free Software Foundation.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; see the file LICENSE.  If not, write to the
// Free Software Foundation, Inc., 51 Franklin Street, Fifth
// ;; Floor, Boston, MA 02110-1301, USA.
// 
// 

// Code         :

/* -------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include <gnublin.h>
#include "module_sht2x.h"

/* -------------------------------------------------------------------------- */

gnublin_module_sht2x *sht2x = NULL;

int temperature = 0;
int humidity = 0;
int farenheit = 0;
int jsonFlag = 0;
int rawFlag = 0;

/**
 * @~english
 * @brief
 */
void help(void) {

    string helpString="This program was designed to easily interact with the SC16IS750 single UART.\n\n"
        "--help, -? Show this help\n"
        "--temperature, -t Read the temperature in celcius\n"
        "--humidity, -h Read the relative humidity\n"
        "--celcius, -c Give the temperature in celcius\n"
        "--farenheit, -f Give the temperature in farenheit\n"
        "--json Convert output to json format\n"
        "--raw Show output in raw format\n"
        "Examples:\n\n"
        "\n";

    printf("%s", helpString.c_str());
}


/**
 * @~english
 * @brief
 *
 * @param error
 */
void printError(const char *error) {

    if (rawFlag) {
        std::cout << "NOK" << std::endl;
    }
    else if (jsonFlag) {
        std::cout << "{\"status\" : \"OK\", \"error\" : \"" << error << "\"}" << std::endl;
    }
    else {
        std::cout << "NOK : " << error << std::endl;
    }
}


/**
 * @~english
 * @brief
 *
 * @param output
 */
void printOutput(float output) {

    char buffer[6];
    sprintf(buffer, "%0.2f", output);

    if (rawFlag) {
        std::cout << buffer << std::endl;
    }
    else if (jsonFlag) {
        std::string message = "";
        if (temperature == 1) {
            message = "temperature";
        }
        if (humidity == 1) {
            message = "humidity";
        }
        std::cout << "{\"status\" : \"OK\", \"" << message << "\" : \"" << buffer << "\"}" << std::endl;
    }
    else {
        std::cout << "OK : " << buffer << std::endl;
    }
}


/**
 * @~english
 * @brief Main program.
 */
int main (int argc, char **argv) {
	
	struct option longOptions[] = {
    	{"help", no_argument, NULL, '?'},
        {"temperature", no_argument, &temperature, 1},
        {"humidity", no_argument, &humidity, 1},
        {"farenheit", no_argument, &farenheit, 1},
        {"json", no_argument, &jsonFlag, 1},
        {"raw", no_argument, &rawFlag, 1},
        {0, 0, 0, 0}
    };

    int optionIndex = 0;
    int c = 0;
    while (1) {
		c = getopt_long(argc, argv, "?thf", longOptions, &optionIndex);

        if (c == -1) {
            break;
        }
        
        switch (c) {
        case 0:
	        /* If this option set a flag, do nothing else now. */
            if (longOptions[optionIndex].flag != 0) {
        		break;
            }
        case '?' :
            help();
            return 0;
            break;
        case 't' :
            temperature = 1;
            break;
        case 'h' :
            humidity = 1;
            break;
        case 'f' :
            farenheit = 1;
            break;
        default : 
            help();
            exit(1);
            break;
        }
    };

    if ((temperature == 1) && (humidity == 1)) {
        printError("Could not read both humidity and temperature, choose one of the two !");
        exit(1);
    }

    sht2x = new gnublin_module_sht2x();
    sht2x->softReset();
    usleep(1000 * 50);
    
    float value = -99.99;
    if (temperature == 1) {
        value = sht2x->readTemperature();
        if (farenheit == 1) {
            value = sht2x->convertC2F(value);
        }
    }

    if (humidity == 1) {
        value = sht2x->readHumidity();
    }

    if (sht2x->fail()) {
        printError(sht2x->getErrorMessage());
        delete sht2x;
        return 1;
    }

    printOutput(value);
    delete sht2x;
	return 0;
}

/* -------------------------------------------------------------------------- */

// 
// gnublin-sht2x.cpp ends here
