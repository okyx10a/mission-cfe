#!/bin/bash
echo "pls input app name:"
read app_name 

mkdir "$app_name"
cd "$app_name"


mkdir fsw
cd fsw


mkdir for_build
cd for_build

cat> Makefile << EOF

APPTARGET = "$app_name"

ENTRY_PT = 

OBJS = 

SOURCES = $(OBJS:.o=.c)

LOCAL_COPTS = 

EXEDIR=../exe

SHARED_LIB_LINK = 

BUILD_TYPE = CFE_APP

include ../cfe/cfe-config.mak

include ../cfe/debug-opts.mak

include $(CFE_PSP_SRC)/$(PSP)/make/compiler-opts.mak

INCLUDE_PATH = \
-I$(OSAL_SRC)/inc \
-I$(CFE_CORE_SRC)/inc \
-I$(CFE_PSP_SRC)/inc \
-I$(CFE_PSP_SRC)/$(PSP)/inc \
-I$(CFS_APP_SRC)/inc \
-I$(CFS_APP_SRC)/$(APPTARGET)/fsw/src \
-I$(CFS_MISSION_INC) \
-I../cfe/inc \
-I../inc

VPATH = $(CFS_APP_SRC)/$(APPTARGET)/fsw/src 

include $(CFE_CORE_SRC)/make/app-rules.mak
EOF

cd ..

mkdir mission_inc
mkdir platform_inc
mkdir src