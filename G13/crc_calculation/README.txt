This example project uses the high speed CRC feature of the RL78.

It has been tested on the RL78G13 TB (512K device, R5F100SL)

The project is for IAR Embedded Workbench.

After the aplication started, LED1 keeps blinking to show the code has been flashed correctly and is working past the CRC calculation stage.

If the CRC calculation is correct, LED2 gets turned on.


The settings for IAR Workbench to calculate the checksum are as follows: CRC16 (0x11021 polynomial), size 2, keep complement 'as is', MSB first, 32-bit checksum unit size, initial value 0x0

This is equivalento to the following settings made in the linker script:

	-J2,crc16,L,,CHECKSUM,,0x0=0x0-0x7FFFB

 
The checksum is placed in location 0x7FFFC-0x7FFFD

	-Z(CONST)CHECKSUM=0x7FFFC-0x7FFFD


The high speed CRC sum is computed over flash range 0x0 t0 0x7FFFB

	-Hff -h0x0000-0x7FFFB 




The project can be flashed via the renesas flash programmer software.
A workspace and project for the renesas flash programmer is placed in the TB_flash folder, to flash the application using the E1 emulator. 

However the E1 emulator cannot be used for debugging within IAR in this configuration.
This since the rom monitor firmware is included in the last 512/256 bytes of the flash address space and there is a conflict with the CRC signature placement in the last 4 bytes of the flash

An alternative would be to place the signature in the data flash, which is separate by the code flash