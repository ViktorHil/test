This is the README file for the Automator USB device.

Automator is a hardware device which controls relays (switches) similar to
the way how punched tape was used in teletypes. You can also compare it to
musical box where a cylinder with tiny pins plays a melody on a metal comb.
Automator learns by example: Each relay can be controlled with a key. When
you press the keys to control the relays, Automator records your actions
for later playback.

This type of device may be useful for many applications. The prototype has
been built for an artist who wants to animate puppets and other objects. It
uses Objective Development's firmware-only USB driver for Atmel's AVR
microcontrollers to download and upload program files. From a technical
point of view, it demonstrates how a HID class device can be controlled
with native Windows API functions without a dedicated device driver.


FILES IN THE DISTRIBUTION
=========================
Readme.txt ........ The file you are currently reading.
firmware .......... Source code of the controller firmware.
firmware/usbdrv ... USB driver -- See Readme.txt in that directory for info
application ....... Source code of the host software.
circuit ........... Circuit diagrams in PDF and EAGLE 4 format. A free
                    version of EAGLE is available for Linux, Mac OS X and
                    Windows from http://www.cadsoft.de/.
License.txt ....... Public license (GPL2) for all contents of this project.
Changelog.txt ..... Logfile documenting changes in soft-, firm- and hardware.


BUILDING AND INSTALLING
=======================
This project can be built on Unix (Linux, FreeBSD or Mac OS X) or Windows.

Building on Windows:
You need WinAVR for the firmware and MinGW, MSYS and FLTK 1.1 for the host
software. Visual C++ instead of MinGW might work as well, but we prefer
free development environments. These packages can be downloaded from:
    WinAVR: http://winavr.sourceforge.net/
    MinGW and MSYS: http://www.mingw.org/
    FLTK 1.1: http://www.fltk.org/
Install the packages in this order and follow the installation instructions
of the respective package. Hint: Use the big ready-made archives for MinGW
and MSYS, not the individual packages. You can identify these by their file
size.

To build the firmware with WinAVR, change into the "firmware" directory,
check whether you need to edit the "Makefile" (e.g. change the ISP upload
tool) and type "make" to compile the source code. Before you upload the code
to the device with "make flash", you should set the fuses with "make fuse".

In order to build the application, you must first build and install FLTK
(usually a task of running "./configure", then "make" and then "make
install" in an MSYS window). Then change to the "application" directory and
edit the "Makefile". Comment out the definitions which are for Unix only
and uncomment those for Windows. Then type "make" to build "Automator.exe".
Alternatively, if everything is installed in the default locations, you
can type "make -f Makefile.windows".

Building on Unix (Linux, FreeBSD and Mac):
You need the GNU toolchain and avr-libc for the firmware and FLTK 1.1 and
libusb for the application. These packages can be downloaded from:
    GNU toolchain and avr-libc: See
        http://www.nongnu.org/avr-libc/user-manual/install_tools.html
    FLTK 1.1: http://www.fltk.org/
    libusb: http://libusb.sourceforge.net/
Install the packages in any order and follow the instructions for the
respective package.

To build the firmware, change to the "firmware" directory, edit "Makefile"
to use the programmer of your choice and type "make" to compile the source
code. Before you upload the code to the device with "make flash", you
should set the fuses with "make fuse".

In order to build the application, make sure that the commands
'fltk-config' and 'libusb-config' are in your search path. Then change
directory to "application", check whether you need to edit "Makefile"
(should not be necessary on Unix) and type "make" to build the "Automator"
application.


WORKING WITH AUTOMATOR
======================
The device has 8 relays and related wire clamps, 4 wire clamps for external
switches, 8 programming keys controlling the relays, 4 input keys to
simulate the external switches, one Reset/Record key, one Stop/Store key,
one trim-pot and various LEDs.

When you first power up Automator, the program memory is empty. To enter a
program, hold down the "Reset/Record" key (the Status LED will reflect the
clock rate while you hold the key) and press the program keys for those
relays you intend to program. The LEDs related to these relays will light.
If you made an error, clear all LEDs (still holding "Reset/Record") with
the "Stop/Store" key.

After deciding which channels to program (all other channels will not be
affected), release the "Reset/Record" key and start entering the program
immediately. Press the program keys to activate relays. Where the program
must wait for an exxternal event, close the an external switch or press the
related simulation key.

When you are done programming, press the "Stop/Store" key immediately to
store your program. You can now start it from the beginning by pressing the
"Reset/Record" key once.

Recording is done in units of a clock rate. This clock rate is shown
through the Status LED while you hold the "Reset/Record" key and can be
adjusted with the trim-pot. Try playback with a different clock rate than
used during recording!

When you have a program which suits your needs, you can archive it on your
computer using the host software. Connect the device to the USB bus, start
the "Automator" software and click the "Save to File" button. An FLTK File
Chooser will pop up which lets you store the program in a file. Automator
writes human readable text files which may even be modified with an editor.
To upload a (modified) program to the device, click the "Restore from File"
button and choose the file to upload.


USING THE USB DRIVER FOR YOUR OWN PROJECTS
==========================================
Automator is a rather complex example because it was built for a real
purpose. It demonstrates how a USB HID can be controlled from Windows using
only native Windows API functions. If you want a more basic example, we
recommend that you download "PowerSwitch" or "HIDKeys". The former is the
simplest example available while the latter is the simplest example
implementing a HID. Both projects can be downloaded from
http://www.obdev.at/products/avrusb/.


ABOUT THE LICENSE
=================
It is our intention to make our USB driver and this demo application
available to everyone. Moreover, we want to make a broad range of USB
projects and ideas for USB devices available to the general public. We
therefore want that all projects built with our USB driver are published
under an Open Source license. Our license for the USB driver and demo code is
the GNU General Public License Version 2 (GPL2). See the file "License.txt"
for details.

If you don't want to publish your source code under the GPL2, you can simply
pay money for AVR-USB. As an additional benefit you get USB PIDs for free,
licensed exclusively to you. See the file "CommercialLicense.txt" for details.


MORE INFORMATION
================
For more information about Objective Development's firmware-only USB driver
for Atmel's AVR microcontrollers please visit the URL

    http://www.obdev.at/products/avrusb/

A technical documentation of the driver's interface can be found in the
file "firmware/usbdrv/usbdrv.h".


--
(c) 2006, 2007 by OBJECTIVE DEVELOPMENT Software GmbH.
http://www.obdev.at/
