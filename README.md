# MSP430 projects

## code composer studio

install dependencies

```
sudo dnf install python3.9 python3.9-libs libnsl libnsl2
```

https://e2e.ti.com/support/processors-group/processors/f/processors-forum/1462212/ccstudio-ccs-20-1-installation-problem-blackhawk-breaks-installation

> Please note that Fedora is not an officially supported Linux distro by CCS hence we will only be able to provide limited support.

### CCS using distrobox

```shell
distrobox-enter fdm-ubuntu
unzip CCS_20.3.1.00005_linux.zip
cd CCS_20.3.1.00005_linux/
./ccs_setup_20.3.1.00005.run
```

then, you need to install dependencies

```shell
cd ti/ccs2031/ccs
📦[ubuntu ccs]$ ./theia/ccstudio
./theia/ccstudio: error while loading shared libraries: libgtk-3.so.0: cannot open shared object file: No such file or directory
📦[ubuntu ccs]$ sudo apt install libgtk-3
Reading package lists... Done
Building dependency tree... Done
Reading state information... Done
E: Unable to locate package libgtk-3
📦[ubuntu ccs]$ apt search libgtk-3
```

## gcc

enable the https://copr.fedorainfracloud.org/coprs/nielsenb/msp430-development-tools

```shell
sudo dnf copr enable nielsenb/msp430-development-tools
```

install

```shell
sudo dnf install msp430-elf-gcc msp430-elf-binutils msp430-elf-gdb mspds msp430flasher msp430-gcc-support-files dos2unix
```

The toolchain will be installed in `/usr/msp430-elf/`.
