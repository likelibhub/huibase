##===================================================================##
## File Name: inc.mk
## Create Author: Tom Hui
## Create Date: Tue Sep 12 1359 2015
## Description:
##		Makefile header. This include some declaration for using in 
##	makefile. I create this file for reduce duplication.
## DONOT MODIFY THIS FILE UNTIL YOU UNDERSTAND THE DETAIL.
##===================================================================##

CC = g++
AR_CMD = ar cr

CFLAGS = -g

BIN_PATH = ../bin
LIB_PATH = ../lib

CXX_CFLAGS = -fPIC -O2 -g -Wall -Wextra -Werror -Wno-unknown-pragmas -fstack-protector-strong -fstack-protector -std=c++11
CXX_DEFINES :=
CXX_INCLUDE = -I../ -I../include -I../src

CC_CFLAGS :=
CC_DEFINES :=
CC_INCLUDE :=

SO_CXX_CFLAGS = -fpic -shared 
SO_C_CFLAGS :=

LINK_CXX_CFLAGS :=
LINK_CXX_LIBS := -L../lib -lhuibase -lhuicrypto -lhuihttp

LINK_CC_CFLAGS :=
LINK_CC_LIBS :=

AR_CC_CFLAGS :=

.PHONY: all clean install test type_test

OS_NAME = $(shell uname)

ifneq "$(OS_NAME)" "Linux"
CXX_DEFINES += -DHWINDOWS
CXX_CFLAGS = -O2 -g -Wall -Wextra -Werror -Wno-unknown-pragmas -std=c++11
endif

TTYPE = AFILE

TARGET :=


