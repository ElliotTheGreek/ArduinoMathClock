# Arduino Math Clock
A digital math clock to upset your friends

## What it is
 - A digital clock which displays the time as a set of two simple math problems.
 - A period (`.`) slowly moves across the bottom of the screen as the minute gets close to changing
![Math](https://user-images.githubusercontent.com/4521739/182193106-1d5b5c58-fb57-448d-927a-6dd5a23d25e7.png)

 - Just before the minute changes the time is revealed in regular format.
![Time](https://user-images.githubusercontent.com/4521739/182193959-b9604009-042a-4f91-96ad-3a128faf9ee1.png)

 - At any point the reveal button can be pushed to display the time.
![Box](https://user-images.githubusercontent.com/4521739/182194301-d49eed39-2cae-4953-b586-6a73786ca531.png)

## What you need
 - 1 Arduino Nano/power supply cord
 - 1 12x2 Liquid Crystal Display
 - 4 Buttons
 - some wire
 - some screws (for assembly)
 - some of your preferred glue (for assembly)

## Wiring it up
 - Wire up the 12x2 Liquid Crystal display to an arduino nano in the ordinary way.
 - Wire up the 4 button's ground to ground
 - Wire the other side of the 4 buttons as follows:
   - `Reveal` to `D12`
   - `Refresh` to `D6`
   - `Hour Set` to `D10`
   - `Minute Set` to `D8`

## Making the box
 - Use a laser cutter to cut the `BoxLaserCutout.svg` out of `1/8th "` material
 - Use your human eyes, brain and fingers to assemble the box.
 - Use the screws the mount the screen and buttons

## Moving the code
 - Use the program `Arduino 2` and open `MathClock/MathClock.ino`
 - Plug in your wired up `Arduino Nano`
 - Deploy the code

Enjoy all the fun math!
