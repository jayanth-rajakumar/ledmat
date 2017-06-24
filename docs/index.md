---
title: ledmat Documentation
favicon: "favicon.ico"
---
This page contains an in-depth explanation of the components needed, the schematics and how it all works. The assembly video linked below shows only how to put everything together. I recommend that you go through both before attempting to build this project. 


## Introduction

The goal of this project is to create a device that replicates the functions of a Speedstacks Tournament Display, which [retails for about $95 in the US](https://www.speedstacks.com/store/retail/speed-stacks-tournament-display-pro/). 

This has a 6 digit 7-segment display panel, and plugs into a stackmat timer via a standard audio jack. The stackmat outputs whatever time is on its display through a series of digital pulses. These pulses are received by the display and processed to convert them back to regular integers. Finally the time is displayed on the large 7-segment panel. 

## The data transmission protocol

Since I did not discover this on my own, I’m just going to link a couple of sources. The first is ‘Selfmade Stackmat Display’ by German programmer Florian Weingarten back in 2008. It was something very similar to what we are doing in this tutorial, except he used discrete components and a custom PCB, which means it would be very hard to make for anyone who is not familiar with electronics. It was encased in a box with a 7-segment display panel and buttons to save times and display averages. You can [see what it looked like here.](https://www.youtube.com/watch?v=Fj_J42mBATY)

Unfortunately, the tutorial he posted has long been taken down. We can only access the text using a web cache. Scroll down to the ‘How it works’ section for an explanation of the protocol. [http://web.archive.org/web/20100820185842/http://hackvalue.de:80/hv_atmel_stackmat](http://web.archive.org/web/20100820185842/http://hackvalue.de:80/hv_atmel_stackmat)

The second source is reddit user [/u/freundTech](https://www.reddit.com/u/freundtech). He made a project to control TwistyTimer from a G4 stackmat. Here is his comment with an excellent explanation of the protocol:
<div class="reddit-embed" data-embed-media="www.redditmedia.com" data-embed-parent="false" data-embed-live="false" data-embed-uuid="4444636c-5b2b-4f6e-8a48-3f5bc6cc87bc" data-embed-created="2017-06-24T08:39:49.846Z"><a href="https://www.reddit.com/r/Cubers/comments/64czya/wip_stackmat_timer_support_for_twistytimer_app/dg19s4y/">Comment</a> from discussion <a href="https://www.reddit.com/r/Cubers/comments/64czya/wip_stackmat_timer_support_for_twistytimer_app/">[WIP] Stackmat timer support for TwistyTimer app</a>.</div>

https://www.reddit.com/r/Cubers/comments/64czya/wip_stackmat_timer_support_for_twistytimer_app/dg19s4y/

## History of stackmat timer hacks

The earliest one I could find was the display by Florian that I described in the previous section. 
In 2014, Jeremy Fleischman (creator of TNoodle, the official WCA scrambling software) posted this on his website: https://www.jflei.com/2014/08/21/dialup-stackmat/.

It’s a really well written article that describes his progress in making a stackmat connect directly to a phone. He discovered that different phones filter the incoming audio signal very differently, and so getting a software based solution that works on all phones is near impossible. He was forced to make a custom PCB to shift the signal to frequencies that phones do not filter. While this is a great solution, it requires him to mass produce and ship those boards himself, in order to keep cost per unit low. 

The speedsolving forums thread https://www.speedsolving.com/forum/threads/of-stackmats-and-smartphones.49357/ where Jeremy posted about his project has a couple of replies from people who have successfully connected stackmats to their phones.

In 2015, CubeWizard23 and his brother made and sold a 7-segment display based stackmat display for $37.50. https://www.speedsolving.com/forum/threads/homemade-stackmat-tournament-display-prototype.55493.
They seem to have used an Arduino and a MAX232 chip to decode the stackmat data. It was a very robust design with a hard plastic case and tripod socket. They have not released any significant information about how they put their project together.

More recently, reddit user /u/freundTech used a new feature in Android 7.0 that allows unprocessed audio input to directly connect a stackmat with his customised version of Twisty Timer. Like the previous one, this solution too is device specific, and getting it to work on other android phones is a hit or miss.

## Making a display:  7-segment LEDs or LED Matrix?

So far, we can see that 7-segment LEDs are the main choice for people making stackmat displays. This is because they are available in a wide variety of sizes and colors. However, each digit has 10 pins, therefore a total of 50 pins would need to be connected for a 5 digit display. 

No microcontroller supports so many outputs, so we have to use a chip called the MAX7219 that takes up the task of driving up to 8 7-segment digits. Since even this chip does not have a lot of pins, it achieves the required functionality by multiplexing – i.e. turning on a digit, holding it for a few microseconds, turning it off and moving on to the next digit. This gives the impression of all the digits being on when viewed by the human eye. We can, infact achieve the same functionality from the microcontroller, but that will waste valuable processor time that is needed to accurately capture the incoming stackmat signal.

This is the approach taken by the others who have done this project. The wiring diagram would look something link this: http://www.batronix.com/images/graphics/circuits/exp-led2-sch.gif

Since this is quite an extensive wiring task, a simpler option would be to use preassembled MAX7219-LED boards. Such boards are in fact available for quite a low price (~$1). The main pitfall is that these are only available in tiny sizes, usually with 0.5” high digits. The resulting stackmat display would not be very clearly visible from more than a few feet away in a competition setting.

This leaves us with the final option: preassembled MAX7219 Dot-matrix LED boards. These cost significantly more than 7-segment boards, but are much bigger at about 1.2” and offer much greater customisability in what we can display on them. We can have custom fonts, text animation effects and even custom symbols. 

They are available in individual 8x8 pixel units, or as chains of four such units. We will use one 4-in-1 unit and one single unit cascaded together.

## Block diagram

This figure shows the overall big picture of what we are trying to achieve. We receive the signal from the stackmat’s 2.5mm jack and give it between a digital input pin and ground of an Arduino Nano microcontroller. The Arduino has a program uploaded to it which decodes the incoming data and displays it on the screen in real time. Power is supplied to the board through the Arduino’s USB port. A small powerbank can be used for this purpose.

## What you need and where to get them

The best place to buy components is from China, using a site like Aliexpress.com. If you pick the free shipping option, it may take 1-1.5 months for it to reach you, but it is worth it since the prices are very low. Alternatively, physical stores which specialize in electronic components may also stock these items.

I’ll provide the cheapest links I can find. Be aware that there is always the risk of the getting the wrong product, or having the product lost in shipment. If that happens, you will have to contact the seller for a refund and try another seller. 

An Arduino Nano board. $2.66
https://www.aliexpress.com/item/Nano-3-0-controller-compatible-with-arduino-nano-CH340-USB-driver-with-CABLE-NANO-V3-0/32686415387.html

Single 8x8 MAX7219 LED matrix. $1.26
https://www.aliexpress.com/item/MAX7219-dot-matrix-module-microcontroller-module-display-module-finished-goods/32667776876.html

4-in-1 MAX7219 LED Matrix. $3.83
https://www.aliexpress.com/item/MAX7219-Dot-Matrix-Module-For-Arduino-Microcontroller-4-In-One-Display-with-5P-Line/32616226423.html

2.5mm to 3.5mm, male to male audio cable. $0.97
https://www.aliexpress.com/item/1pcs-Replacement-Audio-Cable-2-5mm-to-3-5mm-jack-Cord-Male-to-Male-For-Bose/32811868565.html

Female 3.5mm audio jack. $0.93
https://www.aliexpress.com/item/20Pcs-3-5mm-Female-Audio-Connector-3-Pin-DIP-Headphone-Jack-Socket-PJ-301M/32704147531.html

Some single strand wire. ~$0

This covers all the core components needed for the project, totalling up to just under $10.

Some other tools and components you might require are.
1.	Soldering rod, lead and flux.
2.	Wire cutter and stripper
3.	A box to build the display in. I used an empty Pringles can.
4.	A tripod, if your box is small and you need to get it off the ground. You can get a cheap one for about a dollar here: https://www.aliexpress.com/item/New-Black-Mini-Tripod-Mount-Holder-for-Mobius-Action-Cam-Car-Key-Camera-High-Quality-Brand/32802953047.html
5.	Hot glue gun
6.	Insulation tape

## Setting up the software environment

1. Install the [Arduino IDE](https://www.arduino.cc/en/main/software).
2. Download the libraries [MD_Parola](https://github.com/MajicDesigns/MD_Parola) and [MD_MAX2XX](https://github.com/MajicDesigns/MD_MAX72XX) using 'Clone or download' -> 'Download ZIP'.
3. Extract the ZIPs to get two folders called MD_Parola-master and MD_MAX72XX-master. 
4. Move these folders to the Documents\Arduino\Libraries folder (On Windows only. more info on library installation can be found [here](https://www.arduino.cc/en/guide/libraries))
5. Open MD_MAX72XX-master\src\MD_MAX72XX.h. If it does not display well in notepad, try wordpad.
6. Search for USE_PAROLA_HW and replace the 1 next to it with a 0. Search for your hardware (usually USE_FC16_HW, see the full tutorial for more information) and replace the 0 next to it with a 1. Save the file and close it.
7. Download this repository and extract the ledmat.ino file. Open it, set the board to Arduino Nano in the Tools menu. Also make sure the correct Port is selected.
8. Upload the sketch, plug in the stackmat and enjoy!


## More stackmat projects

From the section on the history of stackmat hacks, we can see that connecting directly to a phone has been a rather difficult task. But by introducing the Arduino in the middle, the task of interpreting the data is no longer on the phone. 

We can transfer the decoded time data to the phone using a technology that will work the same no matter what the phone is: Bluetooth. The only hardware modification this will require is replacing the two LED matrix panels with a HC-05 bluetooth module. We can then modify any existing open source timer app to work with the Bluetooth module. I will have a tutorial for this linked here shortly.

![Prototype](https://raw.github.com/jayanth-rajakumar/ledmat/master/img_prototype.jpg)
