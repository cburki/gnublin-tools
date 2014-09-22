### Makefile --- 
## 
## Filename     : Makefile
## Description  : Makefile for the HD44780 tool.
## Author       : Christophe Burki
## Maintainer   : Christophe Burki
## Created      : Thu Jul 17 17:07:30 2014
## Version      : 1.0.0
## Last-Updated : Thu Sep 18 14:05:49 2014 (7200 CEST)
##           By : Christophe Burki
##     Update # : 9
## URL          : 
## Keywords     : 
## Compatibility: 
## 
######################################################################
## 
### Commentary   : 
## 
## 
## 
######################################################################
## 
### Change log:
## 
## 
######################################################################
## 
## This program is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License version 3 as
## published by the Free Software Foundation.
## 
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
## 
## You should have received a copy of the GNU General Public License
## along with this program; see the file LICENSE.  If not, write to the
## Free Software Foundation, Inc., 51 Franklin Street, Fifth
## ;; Floor, Boston, MA 02110-1301, USA.TARGET := gnublin-hd44780

## 
######################################################################
## 
### Code         :

TARGET := gnublin-hd44780
SOURCES := gnublin-hd44780.cpp

include ../Config.mk
include $(GNUBLINMKDIR)/gnublin.mk

CPPFLAGS += -I../../gnublin-modules/module_hd44780 -I../../gnublin-modules/module_mcp230xx  -I../../gnublin-modules/module_sc16is7x0
OBJECTS += ../../gnublin-modules/module_hd44780/module_hd44780.o ../../gnublin-modules/module_mcp230xx/module_mcp230xx.o ../../gnublin-modules/module_mcp230xx/module_mcp23017.o ../../gnublin-modules/module_sc16is7x0/module_sc16is7x0.o ../../gnublin-modules/module_sc16is7x0/module_sc16is750.o

######################################################################
### Makefile ends here
