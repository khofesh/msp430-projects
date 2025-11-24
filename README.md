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

### building projects

#### Configure and Build All Projects

```bash
mkdir build
cd build

cmake ..

# build all projects
cmake --build .
```

#### Build Specific Target

```bash
# build only MSP430G2553 blink_led
cmake --build build --target blink_led_g2553.elf

# build only MSP430FR2355 blink_led
cmake --build build --target blink_led_fr2355.elf
```

#### Clean Build

```bash
rm -rf build
mkdir build
cd build
cmake ..
cmake --build .
```

### Flashing to Device

#### Using MSP430Flasher

```bash
# MSP430G2553
sudo MSP430Flasher -n MSP430G2553 -w build/MSP430G2553/blink_led/blink_led_g2553.hex -v -z [VCC]

# MSP430FR2355
sudo MSP430Flasher -n MSP430FR2355 -w build/MSP430FR2355/blink_led/blink_led_fr2355.hex -v -z [VCC]
```
