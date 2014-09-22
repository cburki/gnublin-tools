### Makefile --- 
## 
## Filename     : Makefile
## Description  : Makefile for the SHT2x tool.
## Author       : Christophe Burki
## Maintainer   : Christophe Burki
## Created      : Thu Sep 18 14:23:04 2014
## Version      : 1.0.0
## Last-Updated : Thu Sep 18 14:23:53 2014 (7200 CEST)
##           By : Christophe Burki
##     Update # : 3
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

TARGET := gnublin-sht2x
SOURCES := gnublin-sht2x.cpp

include ../Config.mk
include $(GNUBLINMKDIR)/gnublin.mk

CPPFLAGS += -I../../gnublin-modules/module_sht2x
OBJECTS += ../../gnublin-modules/module_sht2x/module_sht2x.o

######################################################################
### Makefile ends here
