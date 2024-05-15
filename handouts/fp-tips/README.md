# Final Project Tip! (Not required, just FYI :-)!)
`FP_TIP1_2020.pdf`

Dudes, hi!  You should not use an LED as a photosensor (probably :-)).
Interesting stuff is available at Amazon; for example Elegoo 37 sensors kits:

https://www.amazon.com/ELEGOO-Upgraded-Tutorial-Compatible-MEGA2560/dp/B01MG49ZQ5/ref=sr_1_1?crid=21RA64N2T6DOX&keywords=elegoo+37+sensor&qid=1648602566&sprefix=elegoo+37+sensor%2Caps%2C71&sr=8-1

(we have a few of these kits....)

But! As part of our past pandemic preparedness, I wrote the attached, demonstrating
that you CAN do use an LED as a light sensor :-)!

More to the point: Great example (IHMO) of how to use some ultra-cool peripherals
on the PSoC.

All just FYI.  More "tips" coming....

Very best, Steve

---

# Final Project Tip #2!
`FP_TIP2_2020.pdf`

Dudes, hi!

Once again, the attached is nothing required, just FYI.  Do not let it
distract you.

Also:  Great temperature sensors available in the Elegoo kits in the lab.

But FYI as a demo of PSoC:  Did you know that you can use
an LED as a temperature sensor too.... ?   :-).   See attached.

Very best, Steve

---

# Final Project Tip #3
`TFT_User_Manual(1).pdf`

Graphics displays!

Sean and Eric wrote up a Creator project for using the
awesome TFT display in your kit! The "user manual" is attached,
and the project is on the course website on the PSoC
page (along with this manual).

Don't miss the needed resistors spec'd in the attached manual when
using the PSoC Stick powered by +5 volts - the TFT is 3.3V signal inputs
(although Vcc for the TFT can be +5 - but ONLY 3.3 on the other signal lines....)
(1K's and 2K's resistors....)

Very best, Steve

---

# Final Project Tip #4
`FP_TIP4.pdf`

SERIAL Communications with the PSoC Big Board!

Awesome way to interconnect your PSoC BB and Windows PC,
the same general way we've done all term with the Windows PC
and R31JP.  But, now, with PSoC!!

Very best, Steve

---

# FINAL PROJECT TIP 5: VGA
`video_slides.pdf`

Dudes, hi there!  Final project tip WITH MY SLIDES FROM LECTURE ATTACHED :-)

You can read about VGA and the PSoC here at the course website:

http://web.mit.edu/6.115/www/page/psoc-information.html

(Under PSoC-based VGA interface).

I have a small supply (first-come first-served, **in person** (not email) please) of these helper
boards - still needs work from you, but these help make the VGA connection as
we discussed in lecture:

https://www.waveshare.com/wiki/VGA_PS2_Board

You can check one of these boards out from me during the final project period.

Best,  Steve

---

# FINAL PROJECT TIP 6: Audio recording
`mic_with_0820.pdf`

Hi All!

Please find attached a partial schematic showing two circuits. The top is a recording circuit
for digitizing audio with a FET microphone and an ADC0820 analog-digital converter
(that's in your bag).   The lower circuit is a playback circuit for making sounds from your
DAC, as in Lab 3.

NOTE:  The schematics are "partials", they do NOT show, for example, the power connections
to all of the LM358's or the extensive bypassing you always need with the LM386.

One typical "FET Mic" that works with this circuit is:

http://www.digikey.com/product-search/en?keywords=102-1720-ND
Digikey part number: 102-1720-ND

I may have a few in my office :-).

Even *easier* is:

https://www.amazon.com/DAOKI-Microphone-Amplifier-GY-MAX4466-Adjustable/dp/B07YKG9Y16/ref=sr_1_3?crid=34NKLVE3P9HXZ&keywords=arduino+microphone&qid=1681574516&s=industrial&sprefix=arduino+microphone+%2Cindustrial%2C79&sr=1-3

(Also may have a few in my office. Again, ask in-person, not email please.)

Useful stuff if you want to be able to record and analyze sound as we discussed in lecture :-).

Very best,  Steve

---

# FINAL PROJECT TIP 7: Stand-alone 8051
`stand_alone.pdf`

Dudes, hi there!  Final project tip:

There is a stand-alone 8051 called the 2051 - a small mini
R31JP-on-a-chip, with built in program memory you can burn in our class
burners.  There's a datasheet for this part on the course website.

Available here:

https://www.digikey.com/en/products/detail/microchip-technology/AT89C2051-24PU/1118880

NOTE carefully the needed hookup (external crystal, pullup cap on
the reset line, etc.).

Best,  Steve

---

# FINAL PROJECT TIP 8: Bluetooth using the HC-06 module
`bluetooth.pdf`

All, hi!

For those of you who are considering wireless Bluetooth modules from the parts order,
this attachment shows you how to use an HC-06 module (available from Amazon, for example).

Eric drafted this, we're still working on it, but it has solid examples
showing how he connected an HC-O6 module and PSoC
to a laptop over Bluetooth :-).

Creator project is here:

https://web.mit.edu/6.115/www/page/psoc-information.html

Very best,  Steve

---

# FP gear
No attachments

Hi All!

-  I've put Amulet modules for those interested for the FP
at benches 8 and 12.  If someone needs these and you don't,
please let them use the bench.

BE CAREFUL :-).  The Amulet modules are $750 a piece.  ASK
FIRST if you don't understand what you're doing :-).  They are glass,
do not break them carelessly.

-  I've also put out 4 VGA monitors in the lab for those who want
them for the FP.  Please do NOT disconnect monitors from the
computers.  There are "free" VGA monitors on top of the benches,
for example, benches 49, 37, and 3.  Please do NOT remove
these from the lab.  But they are the "go to" monitors for
your project work.

-  Also, please be careful with your gear.  I found a kit power
supply lying around on a bench, I've stowed it, ask if yours
is missing.

THANKS!

WELL DONE finishing the labs :-)!

Very best,  Steve

---

# Final Project Tip #9
`FP_TIP9_TRIFECTA.pdf`

Hi All!

I've had a few questions about connecting PSoC BB and Stick.
Or, in some cases, connecting PSoC BB, Stick, and PC for three
way communication :-).

Example attached.  This is just one of many possible approaches.

NOTE: IMPORTANT:  ALL systems must be using a common
ground.  The PSoC's in this example MUST be running at the
same voltage level  (e.g., all 5 volts, or all 3.3).  In this attached
example, the communication is between a PSoC 5LP BB and
a PSoC 4 "Pioneer Board," but the PSoC 4 could have been
a stick running at 3.3v.

NOTE:  There must be a common ground between the systems.
In this attached case, the common ground is provided by the
two USB power connections (one for BB, one for Pioneer)
both of which go to the SAME ground of the Windows PC.  Generally,
you should ALSO have a common ground wire connecting
the two PSoC boards.  (You would have a PSoC Stick instead
of a Pioneer board.....).

ASK During office hours, in-person, if you do not understand
but want to do this.  Do not guess :-).  Ask.  In person.

Very best,  Steve

