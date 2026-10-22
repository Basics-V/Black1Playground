// Sourced from ds-pokemon-hacking/swan
#pragma once
#include "wbtypes.h"

STRUCT_DECLARE(FileSystem)
STRUCT_DECLARE(FSFileIterDirParam)
STRUCT_DECLARE(FSFileIterDirResult)
STRUCT_DECLARE(FSFile)

ENUM_DECLARE_EX(SeekOrigin, u32)
enum SeekOrigin: u32 {
    IO_SEEK_SET = 0x0,
    IO_SEEK_CUR = 0x1,
    IO_SEEK_END = 0x2
};

C_DECL_BEGIN

extern FSFile* finit(FSFile* file);
extern b32 romfs_fopen(FSFile* file, const char* path);
extern b32 romfs_fclose(FSFile* file);
extern u32 romfs_fgetsize(FSFile* file);
extern b32 romfs_fseek(FSFile* file, u32 offset, SeekOrigin origin);
extern u32 romfs_ftell(FSFile* file);
extern u32 romfs_fread(FSFile* file, void* dest, u32 length);

C_DECL_END

struct FSFileIterDirParam
{
    FSFileIterDirResult* ResultPtr;
    b32 DontNeedReadName;
    int field_8;
    int field_C;
    int field_10;
    int field_14;
};

struct FSFile
{
    u32 field_0;
    u32 TableData;
    FileSystem* m_FileSystem;
    u32 CommandQueue;
    void* Request;
    u32 field_14;
    u32 field_18;
    u32 field_1C;
    u32 field_20;
    u16 NowDirID;
    u16 DirIterFileID;
    u32 SubTableOffset;
    u32 ParentDirID;
    union {
        FSFileIterDirParam IterDir;
    };
};
