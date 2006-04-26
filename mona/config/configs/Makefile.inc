PREFIX = /usr/local
NASM     = nasm
NDISASM  = ndisasm
CC       = gcc
CXX      = g++
LD       = ld
STRIP    = strip
AR       = ar cvru
RANLIB   = ranlib
INSTALL  = install
CFLAGS   = -nostdlib -Wall -fno-builtin -O3 -DMONA -DDEBUG_BUILD -DHOST_CYGWIN
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
NFLAGS   = -I $(MONADIR)/include/ -f gnuwin32
OSTYPE   = `uname -sr`
EXEEXT   = .exe

SYMPREFIX = _
USER_START_FUNCTION = _user_start