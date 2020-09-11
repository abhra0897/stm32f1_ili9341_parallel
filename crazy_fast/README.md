This code fills the screen of the display at a super high speed. MCU is overclocked to 128MHz and compiled with optimization flag `-O1` .

- **Frames Per Second (FPS):**	119
- **Time to fill 240 frames:**	2005ms
- **Clock Frequency (AHB):**	128MHz
- **Data transfer speed:**		17.43 MB/s (Megabytes, not Megabits)
- **Compilation Flag:**			-O1

Please note that,
- Not all STM32F1 can be reliably overclocked to 128MHz. My other board simply doesn't work with this code.
- It is unstable sometimes.
- The display's maximum refresh rate maybe less than 119FPS. 119FPS is MCU's rate of transfering frames.

I don't see any practical usage of such high FPS. But it's a great achievement for me nonetheless. ;)
