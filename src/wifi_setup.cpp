#include <WiFi.h>
#include <WiFiManager.h>
#include <cstring>            // for strlen
#include "lcd_display.h"
#include "secrets.h"

void setupWiFiWithPortal(const String &deviceName) {
  WiFi.mode(WIFI_STA);
  WiFiManager wm;

  if (deviceName.length()) {
    wm.setHostname(deviceName.c_str());
  }

  if (strlen(WM_AP_NAME) > 0) {
    showWiFiPortal();
    bool ok = wm.autoConnect(WM_AP_NAME, strlen(WM_AP_PASS) ? WM_AP_PASS : nullptr);
    if (!ok) {
      lcdPrint2("WiFi failed", "Reboot...");
      delay(2000);
      ESP.restart();
    }
    // nice to show IP on success
    lcdPrint2("WiFi OK", WiFi.localIP().toString());
  }
}
