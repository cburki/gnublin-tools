### Makefile --- 
## 
## Filename     : Makefile
## Description  : Makefile for the MCP23017 tool.
## Author       : Christophe Burki
## Maintainer   : Christophe Burki
## Created      : Thu Jul 17 17:08:42 2014
## Version      : 1.0.0
## Last-Updated : Mon Sep 22 11:11:10 2014 (7200 CEST)
##           By : Christophe Burki
##     Update # : 4
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
## ;; Floor, Boston, MA 02110-1301, USA.TARGET := gnublin-mcp23017

## 
######################################################################
## 
### Code         :

TARGET := gnublin-mcp23017
SOURCES := gnublin-mcp23017.cpp

include ../Config.mk
include $(GNUBLINMKDIR)/gnublin.mk

CPPFLAGS += -I../../gnublin-modules/module_mcp230xx
OBJECTS += ../../gnublin-modules/module_mcp230xx/module_mcp230xx.o ../../gnublin-modules/module_mcp230xx/module_mcp23017.o

######################################################################
### Makefile ends here
