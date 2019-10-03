/* Name: automator.cpp
 * Project: Automator
 * Author: Christian Starkjohann
 * Creation Date: 2006-02-01
 * Tabsize: 4
 * Copyright: (c) 2006 by OBJECTIVE DEVELOPMENT Software GmbH
 * License: Proprietary, free under certain conditions. See Documentation.
 * This Revision: $Id$
 */

/*
General Description:
This is the main program file for an FLTK based application which allows
downloading and uploading of programs to/from the Automator hardware.
*/

extern "C" {
#   include <stdio.h>
#   include <errno.h>
#   include "usbcalls.h"
#   include "parser.h"
}
#include <FL/Fl.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/fl_ask.H>
#include "gui.h"

#define IDENT_VENDOR_NUM        0x16c0
#define IDENT_VENDOR_STRING     "www.obdev.at"
#define IDENT_PRODUCT_NUM       1503
#define IDENT_PRODUCT_STRING    "Automator"

/* ------------------------------------------------------------------------- */

const char *usbErrorMessage(int errCode)
{
static char buffer[80];

    switch(errCode){
        case USB_ERROR_ACCESS:      return "Access to device denied";
        case USB_ERROR_NOTFOUND:    return "The specified device was not found";
        case USB_ERROR_BUSY:        return "The device is used by another application";
        case USB_ERROR_IO:          return "Communication error with device";
        default:
            sprintf(buffer, "Unknown USB error %d", errCode);
            return buffer;
    }
    return NULL;    /* not reached */
}

#define STATUS(string, delay)  ((Fl_Widget *)statusbar)->label(string); Fl::wait(delay)

static int  downloadData(char data[512])
{
usbDevice_t *dev = NULL;
int         err = 0, len, i;
char        buffer[132], status[256];

    if((err = usbOpenDevice(&dev, IDENT_VENDOR_NUM, IDENT_VENDOR_STRING, IDENT_PRODUCT_NUM, IDENT_PRODUCT_STRING, 1)) != 0){
        fl_alert("Error opening Automator device: %s", usbErrorMessage(err));
        goto errorOccurred;
    }
    STATUS("Status: setting address", 0.2);
    buffer[0] = 1;  /* report ID: setAddress */
    buffer[1] = buffer[2] = 0;
    if((err = usbSetReport(dev, USB_HID_REPORT_TYPE_FEATURE, buffer, 3)) != 0){
        fl_alert("Error setting address: %s", usbErrorMessage(err));
        goto errorOccurred;
    }
    for(i=0;i<4;i++){
        sprintf(status, "Status: receiving block %d of 4\n", i + 1);
        STATUS(status, 0.2);
        len = sizeof(buffer);
        /* report ID = 2 -> getData */
        if((err = usbGetReport(dev, USB_HID_REPORT_TYPE_FEATURE, 2, buffer, &len)) != 0){
            fl_alert("Error reading from device: %s", usbErrorMessage(err));
            goto errorOccurred;
        }
        if(len < 129){
            fl_alert("Error: Block with only %d bytes (instead of 128) received.", len - 1);
            goto errorOccurred;
        }
        memcpy(data + 128 * i, buffer + 1, 128);
    }
errorOccurred:
    if(dev != NULL)
        usbCloseDevice(dev);
    STATUS("Status: Done.", 0.2);
    STATUS("", 0);
    return err;
}

static int uploadData(char data[512])
{
usbDevice_t *dev = NULL;
int         err = 0, len, i;
char        buffer[132], status[256];

    if((err = usbOpenDevice(&dev, IDENT_VENDOR_NUM, IDENT_VENDOR_STRING, IDENT_PRODUCT_NUM, IDENT_PRODUCT_STRING, 1)) != 0){
        fl_alert("Error opening Automator device: %s", usbErrorMessage(err));
        goto errorOccurred;
    }
    STATUS("Status: setting address", 0.2);
    buffer[0] = 1;  /* report ID: setAddress */
    buffer[1] = buffer[2] = 0;
    if((err = usbSetReport(dev, USB_HID_REPORT_TYPE_FEATURE, buffer, 3)) != 0){
        fl_alert("Error setting address: %s", usbErrorMessage(err));
        goto errorOccurred;
    }
    for(i=0;i<4;i++){
        sprintf(status, "Status: sending block %d of 4\n", i + 1);
        STATUS(status, 0);
        len = sizeof(buffer);
        buffer[0] = 2;  /* report ID: setData */
        memcpy(buffer + 1, data + 128 * i, 128);
        if((err = usbSetReport(dev, USB_HID_REPORT_TYPE_FEATURE, buffer, 129)) != 0){
            fl_alert("Error writing to device: %s", usbErrorMessage(err));
            goto errorOccurred;
        }
    }
errorOccurred:
    if(dev != NULL)
        usbCloseDevice(dev);
    STATUS("Status: Done.", 0.2);
    STATUS("", 0);
    return err;
}

/* ------------------------------------------------------------------------- */

void    mainSaveToFile(void)
{
Fl_File_Chooser *chooser;
const char      *filename;
char            data[512];
FILE            *fp = NULL;

    if(downloadData(data) != 0)
        return;
    chooser = new Fl_File_Chooser(".", "*.prog", Fl_File_Chooser::CREATE, "Save Program File");
    chooser->preview(0);
    chooser->show();
    while(chooser->shown())
        Fl::wait();
    if((filename = chooser->value()) == NULL)
        goto errorOccurred;
    if((fp = fopen(filename, "r")) != NULL){
        fclose(fp);
        fp = NULL;
        if(!fl_ask("File exists. Do you want to overwrite the existing file?"))
            goto errorOccurred;
    }
    if((fp = fopen(filename, "w")) == NULL){
        fl_alert("Error creating file: %s", strerror(errno));
        goto errorOccurred;
    }
    parserWriteProgram(fp, data);
errorOccurred:
    if(fp != NULL)
        fclose(fp);
    delete chooser;
}

void    mainRestoreFromFile(void)
{
Fl_File_Chooser *chooser;
const char      *filename;
char            data[512];
int             err;
FILE            *fp = NULL;

    chooser = new Fl_File_Chooser(".", "*.prog", Fl_File_Chooser::SINGLE, "Open Program File");
    chooser->preview(0);
    chooser->show();
    while(chooser->shown())
        Fl::wait();
    if((filename = chooser->value()) == NULL)
        goto errorOccurred;
    if((fp = fopen(filename, "r")) == NULL){
        fl_alert("Error opening file: %s", strerror(errno));
        goto errorOccurred;
    }
    if((err = parserReadProgram(fp, data)) != 0){
        fl_alert(parserStrError(err));
    }else{
        uploadData(data);
    }
errorOccurred:
    if(fp != NULL)
        fclose(fp);
    delete chooser;
}

/* ------------------------------------------------------------------------- */

int main(int argc, char **argv)
{
Fl_Double_Window    *window = mainWindow();

    STATUS("", 0);
    window->show(argc, argv);
    return Fl::run();
}
