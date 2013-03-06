To build the application, it is necessary to download the flash self programming libraries for the specific target.

After installation, copy pfdl.h, pfdl.inc, pfdl_types.h and pfdl.r87 into the dataflash_lib subfolder

To download the flash library, register on http://www2.renesas.eu/products/micro/download/

Then login and choose RL78 as a target.

Select "EEPROM_EMULATION_RL78" from the product list.


Note: the FDL T04 (pico library) is the one being used in the example, so you should select this. 
This flavor can *not* be used with an eeprom emulation layer on top.

The more featured T02 (tiny) & T01 (full) are siutable for more complex data flash management.
These can be used together with the respective eeprom emulation library EEL T02 / T01



