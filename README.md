# Black1Playground

Have fun in my playground! Powered by **[FPM](https://github.com/Basics-V/FPM)**.

### Requirements
(General, OS-specific requirements can be found below)

- [Java](https://adoptium.net/temurin/releases)
- [Python (>=3.10)][python]
- [NitroPacker][nitropacker]
- [GNU Make](https://www.gnu.org/software/make/)
- [ARM GNU Toolchain][arm]

### macOS

GNU Make is included on your system already.  
Install [Homebrew](https://brew.sh/) if you haven't already.  
Download [NitroPacker][nitropacker] and add it to your PATH as `nitropacker`.

With Homebrew: `brew install --cask gcc-arm-embedded`

### Windows

Install [Git Bash](https://github.com/git-for-windows/git/releases/latest) and [Chocolatey](https://chocolatey.org/install#install-step2) if you haven't already.  
Download the [Python installer][python] and install it.  
Download the latest `arm-none-eabi` version (mingw) of the [ARM GNU Toolchain][arm] and add it to the PATH.  
Download [NitroPacker][nitropacker] and add it to your PATH.

With Chocolatey: `choco install make`

### Building

In the shell (Git Bash for Windows, Terminal for macOS):
```sh
$ make
```

[python]: https://www.python.org/downloads/
[nitropacker]: https://github.com/haroohie-club/NitroPacker/releases/latest
[arm]: https://gitlab.arm.com/tooling/gnu-toolchains-for-arm
