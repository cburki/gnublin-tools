// gnublin-sc16is750.cpp --- 
// 
// Filename     : gnublin-sc16is750.cpp
// Description  : SC16IS750 tools for easly interacting with SC16IS750 single UART and 8 additional I/Os.
// Author       : Christophe Burki
// Maintainer   : Christophe Burki
// Created      : Wed Jul 16 14:13:13 2014
// Version      : 1.0.0
// Last-Updated : Thu Jul 17 16:26:22 2014 (7200 CEST)
//           By : Christophe Burki
//     Update # : 75
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
#include "module_sc16is750.h"

/* -------------------------------------------------------------------------- */

gnublin_module_sc16is750 *sc16is750 = NULL;

int i2cAddress = 0x20;
int baudRate = 9600;
int pin = -1;
int value = -1;
char buffer[2048];
unsigned int portFlag = 0;
unsigned int inputFlag = 0;
unsigned int outputFlag = 0;
unsigned int writeFlag = 0;
unsigned int readFlag = 0;
int jsonFlag = 0;
int rawFlag = 0;


/**
 * @~english
 * @brief
 */
void help(void) {

    string helpString="This program was designed to easily interact with the SC16IS750 single UART.\n\n"
        "--help, -? Show this help\n"
        "--address <address>, -a <address> Specify the SC16IS750 i2c address (default is 0x20)\n"
        "--pin <pin>, -p <pin> Specify the additional I/O pin (0-7)\n"
        "--port, -P Specify that the command is applied to the whole port\n"
        "--output <value>, -o <value> Set pin or port as output with given <value> (0 = low / 1 = high)\n"
        "--input, -i Set pin as input and read its value\n"
        "--baud <baud>, -b <baud> Set the UART baud rate with the given <baud>\n"
        "--write <message>, -w <message> Write the <message> to the UART\n"
        "--read, -r Read from the UART, block while waiting for data\n\n"
        "--json Convert output to json format\n"
        "--raw Show output in raw format\n"
        "Examples:\n\n"
        "Write a message to the UART    : gnublin-sc16is750 -w \"Hello Word!\"\n"
        "Read from the UART             : gnublin-sc16is750 -r\n"
        "Set pin 0 high                 : gnublin-sc16is750 -p 0 -o 1\n"
        "Set port as output and as low  : gnublin-sc16is750 -P -o 0\n"
        "Read the value of pin 3        : gnublin-sc16is750 -p 3 -i\n";

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

    if (sc16is750->fail()) {
        printError("NOK", sc16is750->getErrorMessage());
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

    if (sc16is750->fail()) {
        printError("NOK", sc16is750->getErrorMessage());
        return;
    }

    if (rawFlag) {
        if (pin == -1) {
        	printf("%i\n", value);
        }
        else {
        	printf("%i:%i\n", pin, value);
        }
    }
    else if (jsonFlag) {
        if (pin == -1) {
        	printf("{\"value\" : \"%i\", \"status\" : \"OK\"}\n", value);
        }
        else {
        	printf("{\"value\" : \"%i\", \"pin\" : \"%i\", \"status\" : \"OK\"}\n", value, pin);
        }
    }
    else {
        if (pin == -1) {
        	printf("Value : %i\n", value);
        }
        else {
        	printf("Value pin %i : %i\n", pin, value);
        }
    }
}


/**
 * @~english
 * @brief
 *
 * @param buffer
 */
void printOutput(char *buffer) {
    
    std::string status = "OK";

    if (sc16is750->fail()) {
        printError("NOK", sc16is750->getErrorMessage());
        return;
    }
    
    if (rawFlag) {
        printf(buffer);
    }
    else if (jsonFlag) {
        printf("{\"buffer\" : \"%s\", \"status\" : \"OK\"}", buffer);
    }
    else {
        printf("Buffer : %s\n", buffer);
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
        {"port", no_argument, NULL, 'P'},
        {"output", required_argument, NULL, 'o'},
        {"input", no_argument, NULL, 'i'},
        {"baud", required_argument, NULL, 'b'},
        {"write", required_argument, NULL, 'w'},
        {"read", no_argument, NULL, 'r'},
        {"json", no_argument, &jsonFlag, 1},
        {"raw", no_argument, &rawFlag, 1},
        {0, 0, 0, 0}
    };
    
    int optionIndex = 0;
    int c = 0;
    while (1) {
		c = getopt_long(argc, argv, "?a:p:Po:ib:w:r", longOptions, &optionIndex);

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
            portFlag = 1;
            break;
        case 'o' :
            outputFlag = 1;
            value = atoi(optarg);
            break;
        case 'i' :
            inputFlag = 1;
            break;
        case 'b' :
            baudRate = strtol(optarg, NULL, 10);
            break;			
        case 'w' :
            writeFlag = 1;
            strcpy(buffer, optarg);
            printf("buffer=%s\n", buffer);
            break;
        case 'r' :
            readFlag = 1;
            break;
        default : 
            help();
            exit(1);
            break;
        }
    };

    sc16is750 = new gnublin_module_sc16is750(i2cAddress);
    
    if (outputFlag && (pin != -1)) {
        sc16is750->pinMode(pin, OUTPUT);
        sc16is750->digitalWrite(pin, value);
        printOutput();
    }
    else if (outputFlag && portFlag) {
	    pin = -1;
        sc16is750->portMode(OUTPUT);
        sc16is750->writePort(value);
        printOutput();
    }
    else if (inputFlag && (pin != -1)) {
        sc16is750->pinMode(pin, INPUT);
        value = sc16is750->digitalRead(pin);
        printOutput(value);
    }
    else if (inputFlag && portFlag) {
	    pin = -1;
        sc16is750->portMode(INPUT);
        value = sc16is750->readPort();
        printOutput(value);
    }
    else if (writeFlag) {
        int length = strlen(buffer);
        sc16is750->write(buffer, length);
        printOutput();
    }
    else if (readFlag) {
        int available = 0;
        while (available == 0) {
            available = sc16is750->rxAvailableData();
        }
        sc16is750->read(buffer, available);
        printOutput(buffer);
    }
    
    delete sc16is750;
	return 0;
}

/* -------------------------------------------------------------------------- */

// 
// gnublin-sc16is750.cpp ends here
