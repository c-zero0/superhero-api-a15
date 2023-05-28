#include "get_details.h"

void get_details()
{
    // get url
    String url = "http://proiectia.bogdanflorea.ro/api/superhero-api/character?id=" + JSONDocument["id"].as<String>();
    Serial.println(url);

    // Define the HTTP client
    HTTPClient http;

    // Define the connection parameters and, optionally,
    // set the connection timeout, especially if accessing
    // a server with a longer response time (such as a
    // free API server)
    http.begin(url);
    http.setConnectTimeout(30000); // connect timeout
    http.setTimeout(30000);        // response timeout

    // Send HTTP request
    int httpResponseCode = http.GET();

    // Check response code
    if (httpResponseCode > 0)
    {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);

        // Get response data
        String payload = http.getString();

        // deserializejson implicitly clears jsondocument, useful for reusage
        DeserializationError error = deserializeJson(JSONDocument, payload.c_str());

        if (error)
        {
            Serial.println(error.c_str());
        }
        else
        {
            String id = JSONDocument["id"];          // "565"
            String name = JSONDocument["name"];      // "Robin VI"
            String image = JSONDocument["imageUrl"]; // "https://bogdanflorea.ro/images/superhero-api/robin-vi-565.png"

            JsonObject powerstats = JSONDocument["powerstats"];
            String powerstats_intelligence = powerstats["intelligence"]; // "50"
            String powerstats_strength = powerstats["strength"];         // "8"
            String powerstats_speed = powerstats["speed"];               // "25"
            String powerstats_durability = powerstats["durability"];     // "20"
            String powerstats_power = powerstats["power"];               // "17"
            String powerstats_combat = powerstats["combat"];             // "70"

            JsonObject biography = JSONDocument["biography"];
            String biography_full_name = biography["full-name"];   // "Carrie Kelley"
            String biography_alter_egos = biography["alter-egos"]; // "No alter egos found."

            JsonArray biography_aliases = biography["aliases"]; // 0: "-", 1: "-", 2: "..."

            String biography_place_of_birth = biography["place-of-birth"];     // "Gotham City"
            String biography_first_appearance = biography["first-appearance"]; // "-"
            String biography_publisher = biography["publisher"];               // "DC Comics"
            String biography_alignment = biography["alignment"];               // "neutral"

            JsonObject appearance = JSONDocument["appearance"];
            String appearance_gender = appearance["gender"]; // "Female"
            String appearance_race = appearance["race"];     // "Human"

            String appearance_height_0 = appearance["height"][0]; // "-"
            String appearance_height_1 = appearance["height"][1]; // "0 cm"

            String appearance_weight_0 = appearance["weight"][0]; // "- lb"
            String appearance_weight_1 = appearance["weight"][1]; // "0 kg"

            String appearance_eye_color = appearance["eye-color"];   // "Green"
            String appearance_hair_color = appearance["hair-color"]; // "Red"

            String work_occupation = JSONDocument["work"]["occupation"]; // "-"
            String work_base = JSONDocument["work"]["base"];             // "-"

            String connections_group_affiliation = JSONDocument["connections"]["group-affiliation"]; // "-"
            String connections_relatives = JSONDocument["connections"]["relatives"];                 // "-"

            String description = "Powerstats\n   Intelligence: " + powerstats_intelligence + "\n   Strength: " + powerstats_strength + "\n   Durability: " + powerstats_durability + "\n   Power: " + powerstats_power + "\n   Combat: " + powerstats_combat + "\nBiography\n   Full name: " + biography_full_name + "\n   Alter egos: " + biography_alter_egos + "\n   Aliases\n";
            int i = 1;
            for (JsonVariant value : biography_aliases)
            {
                description = description + "      " + (i++) + ": " + value.as<String>() + "\n";
            }
            description = description + "   Place of birth: " + biography_place_of_birth + "\n   First appearance: " + biography_first_appearance + "\n   Publisher: " + biography_publisher + "\n   Alignment: " + biography_alignment + "\nAppearance\n   Gender: " + appearance_gender + "\n   Race: " + appearance_race + "\n   Height\n      1: " + appearance_height_0 + "\n      2: " + appearance_height_1 + "\n   Weight:\n      1: " + appearance_weight_0 + "\n      2: " + appearance_weight_1 + "\n   Eye color: " + appearance_eye_color + "\n   Hair color: " + appearance_hair_color + "Work\n   Occupation: " + work_occupation + "\n   Base: " + work_base + "\nConnections\n   Group affiliation: " + connections_group_affiliation + "\n   Relatives: " + connections_relatives;

            // clear JSONDocument for reusage
            JSONDocument.clear();

            JSONDocument["id"] = id;
            JSONDocument["name"] = name;
            JSONDocument["image"] = image.c_str();
            JSONDocument["description"] = description;
            JSONDocument["teamId"] = teamID;

            String get_details_response = "";
            serializeJson(JSONDocument, get_details_response);

            SerialBT.println(get_details_response);
            Serial.println(get_details_response);
        }
    }
    else
    {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
    }
    // Free resources - terminate the http object
    http.end();
}