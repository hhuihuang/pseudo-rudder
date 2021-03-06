# Automatically generated by configure - do not modify
# Configured with: ./configure --target-list=i386-softmmu --proj-name=sample_plugin --cc=gcc-3.4
prefix=/usr/local
bindir=${prefix}/bin
mandir=${prefix}/share/man
datadir=${prefix}/share/qemu
docdir=${prefix}/share/doc/qemu
MAKE=make
INSTALL=install
CC=gcc-3.4
HOST_CC=gcc
AR=ar
STRIP=strip -s -R .comment -R .note
OS_CFLAGS=
OS_LDFLAGS=
VL_OS_LDFLAGS=
ARCH_CFLAGS=
ARCH_LDFLAGS=
CFLAGS= -Wall -O2 -g -fno-strict-aliasing
LDFLAGS= -g
EXESUF=
AIOLIBS=-lrt -lpthread
ARCH=i386
CONFIG_GDBSTUB=yes
CONFIG_SLIRP=yes
CONFIG_OSS=yes
CONFIG_VNC_TLS=yes
CONFIG_VNC_TLS_CFLAGS= 
CONFIG_VNC_TLS_LIBS=-lgnutls  
VERSION=0.9.1
SRC_PATH=/home/hhui/Experiments/backup/BitBlaze/Total_Components/temu-1.0
TARGET_DIRS=i386-softmmu
VINE_PATH=
PROJECT_NAME=sample_plugin
BUILD_DOCS=yes
CONFIG_SDL=yes
SDL_LIBS=-L/usr/lib -lSDL
SDL_CFLAGS=-I/usr/include/SDL -D_GNU_SOURCE=1 -D_REENTRANT
TOOLS=qemu-img$(EXESUF) 
