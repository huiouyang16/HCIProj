#include "Application.h"
#include "TrackingApplication.h"
#include <windows.h>

int main(int argc, char *argv[]) {
    int result = MessageBoxEx(nullptr, TEXT("Use Detection Mode? (Tracking Mode in default)"),
                              "HCI Proj", MB_YESNO, LANG_ENGLISH);

    if (result == 6) {
        Application app;
        app.run();
    } else {
        TrackingApplication app;
        app.run();
    }
}


