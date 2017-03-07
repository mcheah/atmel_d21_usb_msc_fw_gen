# atmel_d21_usb_msc_fw_gen
Simple windows .exe to generate CRC32 checksum of a built binary and appending that value to the start of the binary for compatibility with Atmel's reference USB MSC bootloader

usage: CRC <binary file for checksum>
produces output file appended with _output
first 4 bytes are CRC32 checksum
next 12 bytes are signature string "ATMEL SAMD21" for compatibility with Atmel's SAMD21 USB Host MSC bootloader:
http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-42352-SAM-D21-XPRO-USB-Host-MSC-Bootloader_Training-Manual_AN8185.pdf
Download Atmel SAM D21 Xplained PRO -USB Host Bootloader Training here:
https://gallery.atmel.com/Products/Details/cd3a2ebd-7b7a-44b8-a2d2-6d0c3d291af4?

Uses lammertb's libCRC library for CRC32 calculations under MIT license
https://github.com/lammertb/libcrc
