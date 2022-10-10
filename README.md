# BlazeNet Device Firmware
In this repo are firmware projects for various BlazeNet devices. This is formed by a common base (which in turn is based on the [embedded-fw project](https://github.com/tristanseifert/embedded-fw-base)) that provides RTOS support and the protocol implementation.

## What's Included
Well, it's basically what it says on the tin… a bunch of firmware. It's broken up into several distinct chunks.

### Supporting libraries
Some code is shared by all devices, or consists of only data such as headers. These are provided by the following libraries:

*TODO: Implement and add more description*

### Bootloader
A relatively simple loader that's available on all devices, which implements secure firmware updates. Updates are downloaded into an external SPI flash, and applied by the loader, which also checks them for integrity. Additionally, it implements some last ditch recovery via NFC, for devices that contain a NFC element for pairing.

*TODO: Implement and add more description*

### Coordinator
Some coordinator devices feature smarts on the radio itself, which are implemented by the following firmwares:

- **host-radio:** Reference implementation of a host-controlled radio frontend, primarily geared at coordinators, though it could work as a device as well. A host is connected via SPI, and can send/receive packets using an interrupt-driven packet protocol.

### Device Base
A common base for device firmwares, provided in the form of a static library to be linked into a final application.

*TODO: What does it implement?*

### Supported Devices
The following devices are implemented, using the afforementioned device firmware base:

*TODO: Come up with devices*

## Building
Building the projects is accomplished using CMake. Change directories into the desired firmware (for a coordinator or end device firmware) and build it as normal. It'll automagically pull in common libraries here.
