#include "get_networks.h"

void scan_wifi()
{
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    Serial.println("\nscan start");

    // WiFi.scanNetworks will return the number of networks found
    int n = WiFi.scanNetworks();
    Serial.println("scan done");
    if (n == 0)
    {
        Serial.println("no networks found");
    }
    else
    {
        Serial.print(n);
        Serial.println(" networks found");
        for (int i = 0; i < n; ++i)
        {
            // print wifis to serial
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print(WiFi.SSID(i));
            Serial.print(" (");
            Serial.print(WiFi.RSSI(i));
            Serial.print(") Encryption: ");

            JSONDocument["ssid"] = WiFi.SSID(i);
            JSONDocument["strength"] = WiFi.RSSI(i);

            switch (WiFi.encryptionType(i))
            {
            case 4:
                JSONDocument["encryption"] = "WPA_WPA2_PSK";
                Serial.println("WPA_WPA2_PSK");
                break;
            case 3:
                JSONDocument["encryption"] = "WPA2_PSK";
                Serial.println("WPA2_PSK");
                break;
            case 0:
                JSONDocument["encryption"] = "open";
                Serial.println("open");
                break;
            case 1:
                JSONDocument["encryption"] = "WEP";
                Serial.println("WEP");
                break;
            case 2:
                JSONDocument["encryption"] = "WPA_PSK";
                Serial.println("WPA_PSK");
                break;
            case 5:
                JSONDocument["encryption"] = "WPA2_ENTERPRISE";
                Serial.println("WPA2_ENTERPRISE");
                break;
            default:
                JSONDocument["encryption"] = "";
                Serial.println("idk");
                break;
            }

            if(i == 0)
                JSONDocument["teamId"] = teamID; // set only once, since it's always the same

            String wifi_list = "";
            serializeJson(JSONDocument, wifi_list);

            SerialBT.println(wifi_list);
        }
    }
    Serial.println("");
}