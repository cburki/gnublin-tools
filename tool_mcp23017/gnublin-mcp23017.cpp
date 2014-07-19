// gnublin-mcp23017.cpp --- 
// 
// Filename     : gnublin-mcp23017.cpp
// Description  : MCP23017 tools for easly interacting with IO expander based on MCP23017.
// Author       : Christophe Burki
// Maintainer   : Christophe Burki
// Created      : Wed Apr 30 12:43:13 2014
// Version      : 1.0.0
// Last-Updated : Thu Jul 17 16:32:13 2014 (7200 CEST)
//           By : Christophe Burki
//     Update # : 71
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
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2, or (at your option)
// any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; see the file COPYING.  If not, write to the
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
#include "module_mcp23017.h"

/* -------------------------------------------------------------------------- */

gnublin_module_mcp23017 *mcp23017 = NULL;;

int i2cAddress = 0x20;
int pin = -1;
int port = -1;
int value = 0;
unsigned int inputFlag = 0;
unsigned int outputFlag = 0;
int jsonFlag = 0;
int rawFlag = 0;


/**
 * @~english
 * @brief
 */
void help(void) {

    string helpString="This program was designed to easily interact with the MCP23017 IO expander.\n\n"
        "-? Show this help\n"
        "--address <address>, -a <address> Specify the MCP23017 i2c address (default is 0x20)\n"
        "--pin <pin>, -p <pin> Specify the IO pin (0-15)\n"
        "--port <port>, -P <port> Specify the IO port (0-1)\n"
        "--output <value>, -o <value> Set pin or port as output with given <value> (0 = low / 1 = high)\n"
        "--input, -i Set pin as input and read its value\n"
        "--json Convert output to json format\n"
        "--raw Show output in raw format\n"
        "Examples:\n\n"
        "Set pin 0 high                  : gnublin-mcp23017 -p 0 -o 1\n"
        "Set pin 1 of port 1 low         : gnublin-mcp23017 -p 8 -o 0\n"
        "Set port 0 as output and as low : gnublin-mcp23017 -P 0 -o 0\n"
        "Read the state of output pin 3  : gnublin-mcp23017 -p 3 -r\n"
        "Read the value of pin 3         : gnublin-mcp23017 -p 3 -i\n";
    
    printf("%s", helpString.c_str());
}



/**
 * @~english
 * @brief
 *
 * @param status
 * @param error
 */
void printError(const char *status, const char *error) {

    if (rawFlag) {
        printf("%s\n", status);
    }
    else if (jsonFlag) {
        printf("{\"status\" : \"%s\", \"error\" : \"%s\"}\n", status, error);
    }
    else {
        printf("%s : %s\n", status, error);
    }
}


/**
 * @~english
 * @brief
 */
void printOutput(void) {
    
    std::string status = "OK";

    if (mcp23017->fail()) {
        printError("NOK", mcp23017->getErrorMessage());
        return;
    }
    
	/* Nothing to output. */
}


/**
 * @~english
 * @brief
 *
 * @param value
 */
void printOutput(int value) {
    
    std::string status = "OK";

    if (mcp23017->fail()) {
        printError("NOK", mcp23017->getErrorMessage());
        return;
    }

    if (rawFlag) {
        if (pin == -1) {
        	printf("%i:%i\n", port, value);
        }
        else {
        	printf("%i:%i\n", pin, value);
        }
    }
    else if (jsonFlag) {
        if (pin == -1) {
        	printf("{\"value\" : \"%i\", \"port\" : \"%i\", \"status\" : \"OK\"}\n", value, port);
        }
        else {
        	printf("{\"value\" : \"%i\", \"pin\" : \"%i\", \"status\" : \"OK\"}\n", value, pin);
        }
    }
    else {
        if (pin == -1) {
        	printf("Value port %i : %i\n", port, value);
        }
        else {
        	printf("Value pin %i : %i\n", pin, value);
        }
    }
}


/**
 * @~english
 * @brief Main program.
 */
int main (int argc, char **argv) {

	struct option longOptions[] = {
    	{"help", no_argument, NULL, '?'},
        {"address", required_argument, NULL, 'a'},
        {"pin", required_argument, NULL, 'p'},
        {"port", required_argument, NULL, 'P'},
        {"output", required_argument, NULL, 'o'},
        {"input", no_argument, NULL, 'i'},
        {"json", no_argument, &jsonFlag, 1},
        {"raw", no_argument, &rawFlag, 1},
        {0, 0, 0, 0}
    };
    
    int optionIndex = 0;
    int c = 0;
    while (1) {
		c = getopt_long(argc, argv, "?a:p:P:o:i", longOptions, &optionIndex);

        if (c == -1) {
            break;
        }
        
        switch (c) {
        case 0:
	        /* If this option set a flag, do nothing else now. */
            if (longOptions[optionIndex].flag != 0) {
        		break;
            }
        case('?') :
            help();
            exit(0);
            break;
        case('a') :
            i2cAddress = strtol(optarg, NULL, 16);
            break;
        case 'p' :
            pin = atoi(optarg);
            break;
        case 'P' :
            port = atoi(optarg);
            break;
        case 'o' :
            outputFlag = 1;
            value = atoi(optarg);
            break;
        case 'i' :
            inputFlag = 1;
            break;
        default : 
            help();
            exit(1);
            break;
        }
    };

    mcp23017 = new gnublin_module_mcp23017();
    mcp23017->setAddress(i2cAddress);
    
    if (outputFlag && (pin != -1)) {
        port = -1;
        mcp23017->pinMode(pin, OUTPUT);
        mcp23017->digitalWrite(pin, value);
        printOutput();
    }
    else if (outputFlag && (port != -1)) {
	    pin = -1;
        mcp23017->portMode(port, OUTPUT);
        mcp23017->writePort(port, value);
        printOutput();
    }
    else if (inputFlag && (pin != -1)) {
        port = -1;
        mcp23017->pinMode(pin, INPUT);
        value = mcp23017->digitalRead(pin);
        printOutput(value);
    }
    else if (inputFlag && (port != -1)) {
	    pin = -1;
        mcp23017->portMode(port, INPUT);
        value = mcp23017->readPort(port);
        printOutput(value);
    }
    
    delete mcp23017;
	return 0;
}

/* -------------------------------------------------------------------------- */

// 
// gnublin-mcp23017.cpp ends here
