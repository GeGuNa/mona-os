/*!
    \file  elf.h
    \brief utilities for ELF file format

    Copyright (c) 2003 HigePon
    WITHOUT ANY WARRANTY

    \author  HigePon
    \version $Revision$
    \date   create:2003/09/04 update:$Date$
*/
#ifndef _MONA_ELF_
#define _MONA_ELF_

#include <monapi.h>
#include <gui/System/Array.h>

typedef struct {
    byte  magic[4];      // 0x7F, 'E', 'L', 'F'
    byte  clazz;         // address size 1:32bit / 2:64bit
    byte  byteorder;     // 1:little / 2:big
    byte  headerversion; // 1
    byte  pad[9];        // padding
    word  type;          // 1:relocatable / 2:executable / 3:common / 4:core image
    word  archtype;      // 2:SPARK / 3:x86 / 4:68K
    dword fileversion;   // 1
    dword entrypoint;    // entry point for executable
    dword phdrpos;       // position at program header
    dword shdrpos;       // position at section header
    dword flag;          // 0
    word  hdrsize;       // ELF header size
    word  phdrent;       // program header entry size
    word  phdrcnt;       // program header entry count
    word  shdrent;       // section header entry size
    word  shdrcnt;       // section header entry count
    word  strsec;        // section number to string
} ELFHeader;

typedef struct {
    dword type;
    dword offset;
    dword virtualaddr;
    dword physaddr;
    dword filesize;
    dword memorysize;
    dword flags;
    dword align;
} ELFProgramHeader;

typedef struct {
    dword name;
    dword type;
    dword flags;
    dword address;
    dword offset;
    dword size;
    dword link;
    dword info;
    dword align;
    dword entsize;
} ELFSectionHeader;

class ELFLoader
{
public:
    ELFLoader(_A<byte> elf);
    ~ELFLoader();

public:
    inline int getImageSize() const { return this->imageSize; }
    inline int getErrorCode() const { return this->errorCode; }
    const char* getErrorName() const;
    dword load(_A<byte> image);

private:
    void prepare();
    bool isValidELF();

private:
    _A<byte> elf;
    int imageSize;
    int errorCode;
    ELFHeader header;
    _A<ELFProgramHeader> pheaders;
    _A<ELFSectionHeader> sheaders;
};

#endif
