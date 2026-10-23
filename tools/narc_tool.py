import sys
#import ndspy.narc
import os
import shutil
from util import NARC

def expand_narc_inplace(path:str):
    with open(path, "rb") as file:
        narc = NARC(file.read()) # ndspy.narc.NARC
    os.remove(path)
    os.makedirs(path)
    for idx, dat in enumerate(narc.FAT.entries): # narc.files
        with open(os.path.join(path, str(idx)), "wb+") as elem:
            elem.write(dat.data) #elem.write(dat)

def pack_narc_inplace(path:str):
    idx = 0
    files = []

    total = 0
    for file in os.listdir(path):
        if os.path.isfile(os.path.join(path, file)):
            try:
                file = int(file)
                if file > total:
                    total = file
            except ValueError:
                pass

    for idx in range(total + 1):
        if os.path.exists(os.path.join(path, str(idx))):
            with open(os.path.join(path, str(idx)), "rb") as elem:
                files.append(elem.read())
        else:
            files.append(b"")
    shutil.rmtree(path)
    with open(path, "wb+") as file:
        file.write(NARC(files = files).serialize()) # ndspy.narc.NARC.fromFilesAndNames(files).save()

if __name__ == "__main__":
    assert len(sys.argv) == 2

    if os.path.isdir(sys.argv[1]):
        pack_narc_inplace(os.path.abspath(sys.argv[1]))
    elif os.path.isfile(sys.argv[1]):
        expand_narc_inplace(os.path.abspath(sys.argv[1]))
    else:
        raise FileNotFoundError("could not find a file or directory at path %s" % sys.argv[1])
