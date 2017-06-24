# ledmat
Arduino-based project to make a tournament display for speedcubing and speedstacking that is compatible with all major timers. Uses MAX7219 driven LED matrices as the display.

First assemble the hardware according to the schematics. A full tutorial will be up shortly. Instructions given below are for the software only.

1. Install the [Arduino IDE](https://www.arduino.cc/en/main/software).
2. Download the libraries [MD_Parola](https://github.com/MajicDesigns/MD_Parola) and [MD_MAX2XX](https://github.com/MajicDesigns/MD_MAX72XX) using 'Clone or download' -> 'Download ZIP'.
3. Extract the ZIPs to get two folders called MD_Parola-master and MD_MAX72XX-master. 
4. Move these folders to the Documents\Arduino\Libraries folder (On Windows only. more info on library installation can be found [here](https://www.arduino.cc/en/guide/libraries))
5. Open MD_MAX72XX-master\src\MD_MAX72XX.h. If it does not display well in notepad, try wordpad.
6. Search for USE_PAROLA_HW and replace the 1 next to it with a 0. Search for your hardware (usually USE_FC16_HW, see the full tutorial for more information) and replace the 0 next to it with a 1. Save the file and close it.
7. Download this repository and extract the ledmat.ino file. Open it, set the board to Arduino Nano in the Tools menu. Also make sure the correct Port is selected.
8. Upload the sketch, plug in the stackmat and enjoy!

![Prototype](https://raw.github.com/jayanth-rajakumar/ledmat/master/img_prototype.jpg)
