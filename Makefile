### Makefile --- 
## 
## Filename     : Makefile
## Description  : Top level make file for the gnublin tools.
## Author       : Christophe Burki
## Maintainer   : Christophe Burki 
## Created      : Fri Jul 18 12:52:42 2014
## Version      : 1.0.0
## Last-Updated : Fri Jul 18 13:01:40 2014 (7200 CEST)
##           By : Christophe Burki
##     Update # : 5
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
## ;; Floor, Boston, MA 02110-1301, USA.
## 
######################################################################
## 
### Code         :

include Config.mk

TOOLS := mcp23017 sc16is750 hd44780

all: ; $(foreach tool,$(TOOLS),(cd tool_$(tool); make) &&):

clean: ; $(foreach tool,$(TOOLS),(cd tool_$(tool); make clean) &&):

distclean: ; $(foreach tool,$(TOOLS),(cd tool_$(tool); make distclean) &&):
	rm -f *~

publish: ; $(foreach tool,$(TOOLS),(cd tool_$(tool); make publish) &&):

######################################################################
### Makefile ends here
