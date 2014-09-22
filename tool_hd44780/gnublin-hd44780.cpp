// gnublin-hd44780.cpp --- 
// 
// Filename     : gnublin-hd44780.cpp
// Description  : HD44780 tools for easly interacting with the HD44680 LCD.
// Author       : Christophe Burki
// Maintainer   : Christophe Burki
// Created      : Thu Jul 17 16:35:30 2014
// Version      : 1.0.0
// Last-Updated : Sat Sep 20 17:47:58 2014 (7200 CEST)
//           By : Christophe Burki
//     Update # : 90
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
#include "module_hd44780.h"

/* -------------------------------------------------------------------------- */

gnublin_module_hd44780 *hd44780 = NULL;
gnublin_hd44780_driver *hd44780Driver = NULL;

char driver[64];
int rsPin = -1;
int enPin = -1;
int d4Pin = -1;
int d5Pin = -1;
int d6Pin = -1;
int d7Pin = -1;
int dsPin = -1;
int shcpPin = -1;
int stcpPin = -1;
int row = 1;
int col = 1;
int i2cAddress = 0x20;
char buffer[2048];
int jsonFlag = 0;
int rawFlag = 0;


/**
 * @~english
 * @brief
 */
void help(void) {

    string helpString="This program was designed to easily interact with the SC16IS750 single UART.\n\n"
        "--help, -? Show this help\n"
        "--rs=<pin> Specify the RS pin, specify the 74HC595 output when driver is 74hc595 (required)\n"
        "--en=<pin> Specify the EN pin, specify the 74HC595 output when driver is 74hc595 (required)\n"
        "--d4=<pin> Specify the D4 pin, specify the 74HC595 output when driver is 74hc595 (required)\n"
        "--d5=<pin> Specify the D5 pin, specify the 74HC595 output when driver is 74hc595 (required)\n"
        "--d6=<pin> Specify the D6 pin, specify the 74HC595 output when driver is 74hc595 (required)\n"
        "--d7=<pin> Specify the D7 pin, specify the 74HC595 output when driver is 74hc595 (required)\n"
        "--ds=<pin> Specify the 74HC595 serial data (DS) pin (required for driver 74hc595)\n"
        "--shcp=<pin> Specify the 74HC595 shift clock (SHCP) pin (required for driver 74hc595)\n"
        "--stcp=<pin> Specify the 74HC595 storage clock (STCP) pin (required for driver 74hc595)\n"
        "--text=<text>, -t <text> Specify the text to display\n"
        "--row=<row>, -r <row> Specify on which row to display the text\n"
        "--col=<col>, -c <col> Specify on which column to display the text\n"
        "--driver=<driver>, -d <driver> Specify the driver to access the LCD (gpio, 74hc595, mcp23017, sc16is750). Default to gpio.\n"
        "--address=<address>, -a <address> Specify the i2c address for the driver components (default is 0x20)\n"
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

    if (hd44780->fail()) {
        printError("NOK", hd44780->getErrorMessage());
        return;
    }
    
	/* Nothing to output. */
}


/**
 * @~english
 * @brief Main program.
 */
int main (int argc, char **argv) {
	
	struct option longOptions[] = {
    	{"help", no_argument, NULL, '?'},
        {"rs", required_argument, NULL, 'z'},
        {"en", required_argument, NULL, 'y'},
        {"d4", required_argument, NULL, 'x'},
        {"d5", required_argument, NULL, 'w'},
        {"d6", required_argument, NULL, 'v'},
        {"d7", required_argument, NULL, 'u'},
        {"ds", optional_argument, NULL, 'q'},
        {"shcp", optional_argument, NULL, 'p'},
        {"stcp", optional_argument, NULL, 'o'},
        {"text", required_argument, NULL, 't'},
        {"row", required_argument, NULL, 'r'},
        {"col", required_argument, NULL, 'c'},
        {"driver", required_argument, NULL, 'd'},
        {"address", required_argument, NULL, 'a'},
        {"json", no_argument, &jsonFlag, 1},
        {"raw", no_argument, &rawFlag, 1},
        {0, 0, 0, 0}
    };

    strcpy(driver, "gpio");
    int optionIndex = 0;
    int c = 0;
    while (1) {
		c = getopt_long(argc, argv, "?z:y:x:w:v:u:q:p:o:t:r:c:d:a:", longOptions, &optionIndex);

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
        case 'z' :
            rsPin = atoi(optarg);
            break;
        case 'y' :
            enPin = atoi(optarg);
            break;
        case 'x' :
            d4Pin = atoi(optarg);
            break;
        case 'w' :
            d5Pin = atoi(optarg);
            break;
        case 'v' :
            d6Pin = atoi(optarg);
            break;
        case 'u' :
            d7Pin = atoi(optarg);
            break;
        case 'q' :
            dsPin = atoi(optarg);
            break;
        case 'p' :
            shcpPin = atoi(optarg);
            break;
        case 'o' :
            stcpPin = atoi(optarg);
            break;
        case 't' :
            printf("length optarg=%d\n", strlen(optarg));
            strcpy(buffer, optarg);
            break;
        case 'r' :
            row = atoi(optarg);
            break;
        case 'c' :
            col = atoi(optarg);
            break;
        case 'd' :
            strcpy(driver, optarg);
            break;
        case('a') :
            i2cAddress = strtol(optarg, NULL, 16);
            break;
        default : 
            help();
            exit(1);
            break;
        }
    };

    if ((rsPin == -1) || (enPin == -1) || (d4Pin == -1) || (d5Pin == -1) || (d6Pin == -1) || (d7Pin == -1)) {
        rawFlag = 1;
        printError("NOK", "All the pins must be specified !");
        exit(1);
    }

    if (strcmp(driver, "gpio") == 0) {
        hd44780Driver = new gnublin_hd44780_driver_gpio(rsPin, enPin, d4Pin, d5Pin, d6Pin, d7Pin);
    }
    else if (strcmp(driver, "74hc595") == 0) {
        if ((dsPin == -1) || (shcpPin == -1) || (stcpPin == -1)) {
            rawFlag = 1;
            printError("NOK", "The DS, SHCP and STCP pins must be specified when using drive 74hc595 !");
            exit(1);
        }
        hd44780Driver = new gnublin_hd44780_driver_74hc595(rsPin, enPin, d4Pin, d5Pin, d6Pin, d7Pin, dsPin, shcpPin, stcpPin);
    }
    else if (strcmp(driver, "mcp23017") == 0) {
        hd44780Driver = new gnublin_hd44780_driver_mcp23017(rsPin, enPin, d4Pin, d5Pin, d6Pin, d7Pin);
        ((gnublin_hd44780_driver_mcp23017 *)hd44780Driver)->setAddress(i2cAddress);
    }
    else if (strcmp(driver, "sc16is750") == 0) {
        hd44780Driver = new gnublin_hd44780_driver_sc16is750(rsPin, enPin, d4Pin, d5Pin, d6Pin, d7Pin);
        ((gnublin_hd44780_driver_sc16is750 *)hd44780Driver)->setAddress(i2cAddress);
    }
    else {
        rawFlag = 1;
        printError("NOK", "Unsupported driver");
        exit(1);
    }

    hd44780 = new gnublin_module_hd44780(hd44780Driver);
    hd44780->init();
    hd44780->clear();
    hd44780->print(buffer, row, col);
    printOutput();
    
    delete hd44780Driver;
    delete hd44780;
	return 0;
}

/* -------------------------------------------------------------------------- */

// 
// gnublin-hd44780.cpp ends here
