This example shows how to output a PWM waveform out of timer KB0, using timer KC0 to gate the output synchronously.

Particularly in this example it is shown that pin uart tx0 can be used to transmit data, although the timer kc pin output would be located on the same pad.

However the gating functionality of timer kc can be used internally without having to assign the phisical pin output.

This has been tested on the target board for RL78i1A (QB-R5F107DE-TB)


