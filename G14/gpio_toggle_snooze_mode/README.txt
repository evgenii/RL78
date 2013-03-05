This example project uses the RJ timer to trigger DTC transfers in background.

The system is driven in stop mode, and uses the 15KHz oscillator (FSUB).

By default the LED on the RL78 promo board (connected on P7.7) should toggle with a frequency of about 2 sec.

Port 7 is being written in background with an alternating pattern of 0xFF and 0x0

The timer RJ event is processed by the DTC to:

- configure the next RJ timer match 
- write on the P7 data port

After this event, the system goes back to stop mode.

The maximum time interval between measurements is linked to the 15KHz clock and the 16-bit range of the RJ counter, so about 4,3 seconds max. 

The demo has been tested on the RL78G14RPB board (USB-stick form factor promotion board)
