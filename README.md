# MSP430 projects

## code composer studio

install dependencies

```
sudo dnf install python3.9 python3.9-libs libnsl libnsl2
```

https://e2e.ti.com/support/processors-group/processors/f/processors-forum/1462212/ccstudio-ccs-20-1-installation-problem-blackhawk-breaks-installation

> Please note that Fedora is not an officially supported Linux distro by CCS hence we will only be able to provide limited support.

## gcc

enable the https://copr.fedorainfracloud.org/coprs/nielsenb/msp430-development-tools

```shell
sudo dnf copr enable nielsenb/msp430-development-tools
```

install

```shell
sudo dnf install msp430-elf-gcc msp430-elf-binutils msp430-elf-gdb mspds msp430flasher msp430-gcc-support-files dos2unix
```
