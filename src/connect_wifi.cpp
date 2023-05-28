#include "connect_wifi.h"

void connect_wifi()
{
    String ssid = JSONDocument["ssid"].as<String>();
    String password = JSONDocument["password"].as<String>();

    // clear jsondocument for reusage
    JSONDocument.clear();

    Serial.print("\nssid chosen: ");
    Serial.println(ssid);
    JSONDocument["ssid"] = ssid;
    Serial.print("password: ");
    Serial.println(password);

    const long connection_timeout = 15000; // 15s
    long startConnection = 0;

    // Set WiFi to station mode and disconnect from an AP if it
    // was previously connected
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    // Initialize the WiFi network
    WiFi.begin(ssid.c_str(), password.c_str());
    Serial.println("\nConnecting");

    // Connect to the network
    // Check the connection status in a loop every 0.5 seconds
    // Since the connection can take some time and might fail,
    // it is necessary to check the connection status before
    // proceeding. To define a timeout for the action, the
    // current counter of the timer is stored
    startConnection = millis();
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);

        // Check if the defined timeout is exceeded
        if (millis() - startConnection > connection_timeout)
        {
            break;
        }
    }
    Serial.println("");

    // Check if connection was successful & send result to app
    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("Connection failed");
        JSONDocument["connected"] = false;
    }
    else
    {
        Serial.print("Connected to network: ");
        Serial.println(WiFi.SSID());
        Serial.print("Local IP address: ");
        Serial.println(WiFi.localIP());
        JSONDocument["connected"] = true;
    }

    JSONDocument["teamId"] = teamID;

    String wifi_status = "";
    serializeJson(JSONDocument, wifi_status);

    SerialBT.println(wifi_status);
}