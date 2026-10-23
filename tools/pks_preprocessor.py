import argparse
import os
from util import strip_comments

# TODO: Expression support
def sanitize_rhs(rhs:str) -> int | str:
    if rhs.startswith("0x"):
        return int(rhs, 16) # 0xABC
    try:
        return int(rhs) # 123
    except:
        return rhs[1:-1] # "word"

def strip_strings(line:str) -> str:
    out = True
    ret = ""
    for char in line:
        if char == '"':
            out = not out
        elif out:
            ret += char
    return ret

def replace_valid_macro(line:str, key:str, value:int | str) -> str:
    value = str(value) # Stringify
    # Helper function
    def is_var_char(char:str):
        return char.isalnum() or char in "_$"

    idx = 0
    in_str = False
    while idx < len(line):
        # Escape strings
        if line[idx] == '"':
            in_str = not in_str
        if in_str:
            idx += 1
            continue

        # Do not convert invalid matches
        pos = line[idx:].find(key)
        if pos == -1:
            break

        # Wait until approach
        if pos == 0:
            pos += idx

            # Assert that the define is not a substring of another
            if pos > 0:
                if is_var_char(line[pos - 1]):
                    idx = pos + 1
                    continue
            if pos + len(key) < len(line):
                if is_var_char(line[pos + len(key)]):
                    idx = pos + 1
                    continue

            # Replace
            line = line[:pos] + value + line[pos + len(key):]
        idx += 1

    return line

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description = "Minimal PokéScript Pre-Processor")

    parser.add_argument(
        "-p", "--process",
        type = str,
        required = True,
        help = "path to input PokéScript file (.pks)"
    )
    parser.add_argument(
        "-o", "--output",
        type = str,
        required = False,
        help = "path to output PokéScript file (.pks)"
    )
    parser.add_argument(
        "-i", "--include",
        type = str,
        required = False,
        action = "append",
        help = "path to include directory(/ies)"
    )

    args = parser.parse_args()
    include_dirs = ["."] + args.include if args.include is not None else []

    with open(args.process, "r") as file:
        target = file.read().split("\n")

    # Fetch includes from PKS
    include_files = []
    for line in target:
        line = line.strip()
        if line.startswith("#include"):
            # Search include directories for include files
            for path in include_dirs:
                include_file = os.path.join(path, line.split()[1][1:-1])
                if os.path.isfile(include_file) and include_file not in include_files:
                    include_files.append(include_file)
                    break

    # Load include lines into memory
    include_data = []
    for include in include_files:
        with open(include, "r") as file:
            include_data += file.read().split("\n")

    # Evaluate defines
    defines = {}
    for line in target + include_data:
        line = line.strip()
        if line.startswith("#define"):
            parts = line.split()
            assert parts[1] not in defines
            defines[parts[1]] = sanitize_rhs(parts[2])

    # Inject macros
    out_lines = []
    for idx, line in enumerate(target):
        if line.strip().startswith("#"):
            continue

        line = strip_comments(line)
        for define in defines:
            if define in strip_strings(line):
                line = replace_valid_macro(line, define, defines[define])
        out_lines.append(line)

    # Output (optionally to file)
    if args.output is not None:
        with open(args.output, "w+") as file:
            file.write("\n".join(out_lines))
    else:
        print("\n".join(out_lines), end = "")
