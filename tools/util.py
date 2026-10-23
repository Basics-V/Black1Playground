import io
import struct

# Adapted from MCMi460/PokeBound/tools/rePPTXT
class DataStream(io.BytesIO):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)

    def read_u8(self):
        return int(struct.unpack("<B", super().read(1))[0])    
    def read_s8(self):
        return int(struct.unpack("<b", super().read(1))[0])

    def read_u16(self):
        return struct.unpack("<H", super().read(2))[0]
    def read_s16(self):
        return struct.unpack("<h", super().read(2))[0]

    def read_u32(self):
        return struct.unpack("<I", super().read(4))[0]
    def read_s32(self):
        return struct.unpack("<i", super().read(4))[0]

    def write_u8(self, var: int):
        super().write(struct.pack("<B", var))
    def write_s8(self, var: int):
        super().write(struct.pack("<b", var))

    def write_u16(self, var: int):
        super().write(struct.pack("<H", var))
    def write_s16(self, var: int):
        super().write(struct.pack("<h", var))

    def write_u32(self, var: int):
        super().write(struct.pack("<I", var))
    def write_s32(self, var: int):
        super().write(struct.pack("<i", var))

    def seek_start(self):
        super().seek(0, io.SEEK_SET)
    def seek_pos(self, offset):
        super().seek(offset, io.SEEK_SET)
    def seek_next(self, offset):
        super().seek(offset, io.SEEK_CUR)
    def seek_end(self):
        super().seek(0, io.SEEK_END)

    def __bytes__(self) -> bytes:
        return self.getvalue()

    def __len__(self):
        return self.getbuffer().nbytes

def strip_comments(string):
    line = False
    block = False
    ret = ""
    for idx, char in enumerate(string):
        if len(string) > idx + 1:
            match string[idx:idx+2]:
                case "//":
                    line = True
                case "/*":
                    block = True
                case "*/":
                    block = False
        if char == "\n":
            line = False
        if not line and not block:
            ret += char
    return ret.replace("*/", "")

# Credit for structure reference:
# PlatinumMaster/NitroSharp/Formats/NARC/NARC.cs
class NARC:
    magic = 0x4352414E
    le = 0xFFFE
    version = 0x100

    class FATB:
        magic = 0x46415442

        class Entry:
            def __init__(self, data:bytes | DataStream = None):
                if isinstance(data, DataStream):
                    self.destBegin = data.read_u32()
                    self.destEnd = data.read_u32()
                elif isinstance(data, bytes):
                    self.data = DataStream(data)

            def read(self, stream:DataStream, fimg_base:int):
                start = stream.tell()
                stream.seek_pos(fimg_base + self.destBegin)
                self.data = stream.read(self.destEnd - self.destBegin)
                stream.seek_pos(start) # Reset position

        def __init__(self, data:bytes = None):
            self.entries = []
            if data is not None and isinstance(data, bytes):
                data = DataStream(data)
                fileCount = data.read_u16()
                data.seek_next(2)
                for i in range(fileCount):
                    self.entries.append(self.Entry(data))
                data.seek_next(0x18)
                fimg_base = data.tell()
                for entry in self.entries:
                    entry.read(data, fimg_base)

    def __init__(self, data:bytes = None, **kwargs:dict) -> None:
        data = DataStream(data)
        if len(data) > 0:
            self.deserialize(data)
        else:
            self.FAT = self.FATB()

        files = kwargs.get("files", None)
        if files is not None:
            assert all(isinstance(file, bytes) for file in files)
            for idx, file in enumerate(files):
                if idx < len(self.FAT.entries):
                    self.FAT.entries[idx] = self.FATB.Entry(file)
                else:
                    self.FAT.entries.append(self.FATB.Entry(file))

    def deserialize(self, data:DataStream) -> None:
        data.seek_start()
        assert data.read_u32() == self.magic # NARC file magic
        assert data.read_u16() == self.le # LE NARCs only
        data.seek_pos(0x18)
        self.FAT = self.FATB(data.read())

    def serialize(self) -> bytes:
        out = DataStream()

        # Header
        out.write_u32(self.magic)
        out.write_u16(self.le)
        out.write_u16(self.version)
        out.write_u32(0x0)
        out.write_u16(0x10)
        out.write_u16(0x3)

        out.write_u32(self.FATB.magic)
        out.write_u32(len(self.FAT.entries) * 0x8 + 0xC)
        out.write_u16(len(self.FAT.entries))
        out.write_u16(0)
        offset = 0
        for entry in self.FAT.entries:
            out.write_u32(offset)
            out.write_u32(offset + len(entry.data))
            offset += len(entry.data)
        
        # FNTB
        out.write_u32(0x464E5442)
        out.write_u32(0x10)
        out.write_u32(0x4)
        out.write_u32(0x10000)

        # FIMG
        out.write_u32(0x46494D47)
        fimg_chunk_size_offset = out.tell()
        out.write_u32(0)
        for entry in self.FAT.entries:
            out.write(bytes(entry.data))
        chunk_size = out.tell() - fimg_chunk_size_offset + 4
        file_size = out.tell()
        out.seek_pos(fimg_chunk_size_offset)
        out.write_u32(chunk_size)
        out.seek_pos(0x8)
        out.write_u32(file_size)

        return bytes(out)
