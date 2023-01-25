#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

void wifi_init() {
    wifi_connect_loop();
}

void wifi_connect_loop() {
    printfs("connecting to wifi: %s:%s\n", WIFI_SSID, WIFI_PASS);
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    };

    printfs("connected to wifi");
}

bool wifi_check_connectivity() {
    return WiFi.status() == WL_CONNECTED;
}

int wifi_request_access(uint32_t uid, uint8_t reader) {
    WiFiClient client;
    HTTPClient http;
    char request_body[20];

    http.begin(client, reader == 0 ? LOGIN_REMOTE_ADDR : EXIT_REMOTE_ADDR);
    http.addHeader("Content-Type", "application/json");

    snprintf(request_body, sizeof(request_body), "{\"uid\": %zu}", uid);
    printfs("%u:%u:request_body:%s\n", reader, uid, request_body);

    int http_code = http.POST(request_body);
    printfs("respone http code: %d\n", http_code);

    return http_code == 200;
}