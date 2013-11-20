To build the application, it is necessary to download the flash self programming libraries for the specific target.

After installation, copy the FDL \lib contents (fdl.h, fdl_types.h, fdl.r87) into the dataflash_lib subfolder
After installation, copy the EEL \lib contents (eel.h, eel_types.h, eel.r87) into the eeprom_emulation_lib subfolder

The templates for the descriptors and the user defined types have to be modified by the user and are located in user_src

To download the flash library, register on http://www2.renesas.eu/products/micro/download/

Then login and choose RL78 as a target.

Select "EEPROM_EMULATION_RL78" from the product list.


Note: the FDL T02 (tiny library) is the one being used in the example, so you should select this. 
This flavor can be used with an eeprom emulation layer on top, EEL T02.





