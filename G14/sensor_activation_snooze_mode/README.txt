This example project shows how to use the RJ timer in order to switch on/off a sensor during the sampling period of the ADC.

The system is driven in stop mode, and uses the 32KHz oscillator (FSUB).

The interval timer is used as a hardware trigger source for the ADC sampling.

At the beginning of a cycle, timer RJ is running and its output is either low or high, depending on what an external sensor requires to be in the switched off state.

After the elapsing of the timer RJ "idle time", the sensor gets powered on for a certain time before the measurement is taken.
This is accomplished by the output of timer RJ which toggles from the "idle" state to its active state.

The timer RJ event is processed by the DTC to:

- configure the next RJ timer match for the "powered on" sensor time
- start the interval timer
- power on the ADC comparators

After this event, the system goes back to stop mode.

The sensor needs a certain time to power on and reach a stable state. 
The interval timer needs to be programmed in order to trigger the ADC sampling only after the sensor is stable.

When the interval timer expires, the ADC is woken up, requesting its clock from the on chip high speed oscillator, then samples the input. 

If the measurement satisfies the wakeup conditions, snooze mode is exited and the CPU is woken up for reacting on the event
Otherwise, the system goes back to snooze mode.

After a (possibly short) delay the timer RJ issues again an event which triggers the DTC.
At this point the "powered on" sensor time is elapsed and the system needs to go back to sleep.
The interval timer is stopped by the DTC and the ADC is powered off.


During idle time, everything in the system is powered off besides from the timer RJ which is running with the 32kHz subsystem clock.
During the measurement time, the interval timer and the adc are additionally active while the sensor is powered on.

The maximum time interval between measurements is linked to the 32KHz clock and the 16-bit range of the RJ counter, about 2 seconds. 
Could be increased by adding other stages in the DTC configuration, reprogramming the timer RJ for several "idle times" instead of just one.

The demo has been tested on the RL78G14RPB board (USB-stick form factor promotion board)
