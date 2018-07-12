#include <Arduino.h>
#include <WiFiClient.h>
#include <ESP8266WiFi.h>

#define DCK_PIN 13
#define DATA_PIN 14
#define LAT_PIN 12

WiFiServer server(80); //Initialize the server on Port 80

void setup() {
    pinMode(DCK_PIN, OUTPUT);
    pinMode(LAT_PIN, OUTPUT);
    pinMode(DATA_PIN, OUTPUT);

    WiFi.mode(WIFI_AP); //Our ESP8266-12E is an AccessPoint 
    WiFi.softAP("dev-pro-corp", "kwEhg5mn"); // Provide the (SSID, password); . 
    server.begin(); // Start the HTTP Server
}

unsigned int time;
int i;
int k;
int updateSpeed = 100; // ms
int lastUpdateMs = 0;
int headIndex = 0;

int getPrevIndexFrom(int index, int prevNumber) {
    int prevIndex = index - prevNumber;
    return prevIndex < 0 ? 16 + prevIndex : prevIndex;
}

void loop() {
    time = millis();

    if (lastUpdateMs == 0 || lastUpdateMs + updateSpeed < time) {
        lastUpdateMs = time;

        for(i = 0; i < 16; i++) {
            for (k = 0; k < 12; k++) {
                // 4095
                if (i == headIndex) {
                    digitalWrite(DATA_PIN, HIGH);
                } 
                // 3276
                /*else if (i == headIndex-1 && 
                    (k == 0 || k == 1 || k == 4 || k == 5 || k == 8 || k == 9)
                ) {
                    digitalWrite(DATA_PIN, HIGH);
                }*/
                // 2457
                /*else if (i == getPrevIndexFrom(headIndex, 1) && 
                    (k == 0 || k == 3 || k == 4 || k == 7 || k == 8 || k == 11)
                ) {
                    digitalWrite(DATA_PIN, HIGH);
                }*/
                // 1638
                else if (i == getPrevIndexFrom(headIndex, 1) && 
                    (k == 1 || k == 2 || k == 5 || k == 6 || k == 9 || k == 10)
                ) {
                    digitalWrite(DATA_PIN, HIGH);
                }
                // 819
                else if (i == getPrevIndexFrom(headIndex, 2) && 
                    (k == 2 || k == 3 || k == 6 || k == 7 || k == 10 || k == 11)
                ) {
                    digitalWrite(DATA_PIN, HIGH);
                }
                // 419
                /*else if (i == headIndex-4 && 
                    (k == 3 || k == 4 || k == 6 || k == 10 || k == 11)
                ) {
                    digitalWrite(DATA_PIN, HIGH);
                }*/
                // 210
                else if (i == getPrevIndexFrom(headIndex, 3) && 
                    (k == 4 || k == 5 || k == 7 || k == 10)
                ) {
                    digitalWrite(DATA_PIN, HIGH);
                }
                // 50
                else if (i == getPrevIndexFrom(headIndex, 4) && 
                    (k == 6 || k == 7 || k == 10)
                ) {
                    digitalWrite(DATA_PIN, HIGH);
                }
                // 1
                else if (i == getPrevIndexFrom(headIndex, 5) && 
                    (k == 11)
                ) {
                    digitalWrite(DATA_PIN, HIGH);
                }
                else {
                    digitalWrite(DATA_PIN, LOW);
                }
                digitalWrite(DCK_PIN, HIGH);
                digitalWrite(DCK_PIN, LOW);
            }
        }

        headIndex++;

        if (headIndex == 16) {
            headIndex = 0;
        }    

        digitalWrite(LAT_PIN, HIGH);
        digitalWrite(LAT_PIN, LOW);
    }
}