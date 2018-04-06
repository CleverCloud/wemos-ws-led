#include <Adafruit_NeoPixel.h>    // https://github.com/adafruit/Adafruit_NeoPixel
#include <ESP8266WiFi.h>          
#include <WebSocketClient.h>      // https://github.com/morrissinger/ESP8266-Websocket

#define PIXEL_COUNT       30
#define WIFI_SSID         "INSERT YOUR WIFI SSID HERE"
#define WIFI_PASSWORD     "INSERT YOUR WIFI PASSWORD HERE"
#define WEBSOCKET_HOST    "INSERT YOUR HOSTNAME HERE"
#define WEBSOCKET_PORT    80
#define WEBSOCKET_PATH    "/"

struct RGB {
  byte r;
  byte g;
  byte b;
};

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, D4, NEO_GRB + NEO_KHZ800);
RGB stripView[PIXEL_COUNT];
WebSocketClient wsClient;
WiFiClient client;

bool connected;

void setup() {
  Serial.begin(9600); // Used for debugging messages

  // Initialize the LED strip
  for (int i = 0; i < strip.numPixels(); i = i + 1) {
    stripView[i] = {0, 0, 0};
  }
  strip.begin();
  strip.show();

  setup_wifi();
  setup_websocket();
}

void loop() {
  // If connection fails / breaks, the first LED blinks red
  if(!client.connected() || !connected) {
    stripView[0] = {255, 0, 0};
    renderStrip();
    delay(500);
    stripView[0] = {0, 0, 0};
    renderStrip();
    delay(500);
  } else {
    // When receiving data, process it and display the corresponding color on every LED
    // Expected format is: RRRGGGBBB (as in 255000000, 035127078, ...)
    // There is no error handling
    String data;
    wsClient.getData(data);
    if(data.length() > 0) {
      Serial.print("Received: ");
      Serial.println(data);
      int red   = data.substring(0, 3).toInt() / 255.0 * 100;
      int green = data.substring(3, 6).toInt() / 255.0 * 100;
      int blue  = data.substring(6, 9).toInt() / 255.0 * 100;
      Serial.print("Red: ");
      Serial.println(red);
      Serial.print("Green: ");
      Serial.println(green);
      Serial.print("Blue: ");
      Serial.println(blue);
      for (int i = 0; i < strip.numPixels(); i = i + 1) {
        stripView[i] = {red, green, blue};
      }
      renderStrip();
    }
  }
}


void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("WiFi is connected on ");
  Serial.println(WIFI_SSID);
  Serial.print("=> IP address : ");
  Serial.println(WiFi.localIP());
}

void setup_websocket() {
  wsClient.host = WEBSOCKET_HOST;
  wsClient.path = WEBSOCKET_PATH;
  Serial.println("Initiating connection...");
  if(client.connect(WEBSOCKET_HOST, WEBSOCKET_PORT)) {
    Serial.println("Connected.");
    Serial.println("Initializing websocket...");
    if(wsClient.handshake(client)) {
      Serial.println("Handshake successful.");
      connected = true;
    } else {
      Serial.println("Handshake failed.");
      connected = false;
    }
  } else {
    Serial.println("Connection failed.");
    connected = false;
  }
}

void renderStrip() {
  for (int i = 0; i < strip.numPixels(); i = i + 1) {
    strip.setPixelColor(i, stripView[i].r, stripView[i].g, stripView[i].b);
  }
  strip.show();
}

