This example shows a possible implementation of a bootloader using shared interrupts with the application.
The interrupts are called using pointers located in ram memory, allowing the bootloader and the application to use different interrupt routines.
The principle is that the vector table located at 0x0 specifies addresses of skeleton routines, which call up the vector routine via a function pointer callback.

This application was tested on the RL78G13 target board.

One led blinks with a frequency of one second, using interval timer. When the user presses a button, an interrupt is generated.
As a consequence, 4 Flash blocks located at 0xD000 get programmed with a counter pattern, to simulate a program upgrade.
Then the application is called, which blinks the led twice as fast and uses the pushbutton to turn on / off the other led on the target board.


Memory map:
The bootloader program is located in the first 4K block.
The Flash library is located at 0x2000.
The application is located starting at 0x3000.

The interrupt vector pointers are located in RAM at fixed addresses.
The flash libraries are used only by the bootloader, as it would be in a firmware update scenario.

The application vector table is located at a load address of 0x3000, and the linker locates its run address at 0x0 via the -Q directive.
The security id is used only by the bootloader, as well as the option bytes.

The application is started by jumping to its reset vector from within the bootloader code and goes through the low_level_init function so that its variables in ram are initialized.
In this way the ram contents are reused between bootloader and application.

The bootloader project includes the startup routine explicitly, since the main function got renamed to BL_main.
The same is true for all functions called by the bootloader (all have a BL_ prefix).
This is not necessary for the application itself but is required by the debugging environment (IAR) to properly distinguish the symbols while debugging.

To use the example, debug the bootloader project, which includes and downloads also the application image.
The application needs to be built in a separate step, altough it could be automated using a batch build.

To restart the bootloader from the application, it could be possible to issue a reset in software by trying to execute code from a non programmed flash location (0xFF), which is equivalent to executing an illegal instruction.
However be aware that while debugging, this trap is handled by the rom monitor and will not work with the debugger attached. Another alternative would be to make an indirect jump to the bootloader reset vector, which is located at address 0x0

