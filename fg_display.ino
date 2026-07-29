/**
* Kaipo Ojas
* fg_display.ino
*/

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <WebServer.h>
#include <MD_Parola.h>
#include <MD_MAX72XX.h>
#include <SPI.h>
#include <ESPmDNS.h> 
#include "MD_EyePair.h"
/**
* This program uses the ESP32 DevKit module to display various stock prices.
* Stocks display on a dot matrix display. 
* ESP32 is in STA and AP mode. Acts as STA to get current stock prices using apiKeys.
* ESP32 AP mode creates a local site for devices connected to same network to set what the display shows.
*/
#define DATA_PIN 23
#define CLK_PIN  18
#define CS_PIN   5
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES   4

/**
* Network name/SSID
*/
const char* STA_SSID = "Wifi_Network_Name";

/**
* Network password.
*/
const char* STA_PASS  = "Wifi_Password";

/**
* Access Point Name
*/
const char* AP_SSID  = "StockDisplay";

/**
* Access Point Password
*/
const char* AP_PASS  = "12345678";

String apiKey = "YOUR_ALPHA_VANTAGE_KEY";

//Used to display text
MD_Parola display = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

//Used to display custom symbols(for eyes)
MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

//Sets up Web server
WebServer server(80);

//Display Modes avilable
enum DisplayMode { MODE_VOO, MODE_FEAR_GREED, MODE_TEST, MODE_EYE, MODE_REPORT };
DisplayMode currentMode = MODE_TEST; //Initially sets to Test/Nothing shows

unsigned long lastUpdate = 0;

MD_EyePair eyes;

int currentBrightness = 1;

// ____Forward declarations __________
void connectSTA();
void createAP();
void handleRoot();
void handleSet();
void refreshData();
String getVOO();
String getFearGreed();
void showMessage(String msg);
String webpage();

/**
* Sets up dot matrix display, creates our AP site, and sets up STA mode.
*/
// ___Setup _____________
void setup() {
  Serial.begin(115200);
  //Sets up matrix display. Both Parole and MDMAXX
  mx.begin();

  display.begin();
  display.setIntensity(1);
  display.displayClear();

  eyes.begin(1, &mx, 500);

  //Connects ESP to our wifi as STA mode.
  WiFi.mode(WIFI_AP_STA);
  connectSTA();
  //Sets up the AP local site.
  createAP();

  server.on("/",    handleRoot);
  server.on("/set", handleSet);
  server.begin();

  if (MDNS.begin("stockdisplay")) {
    Serial.println("mDNS started - access at http://stockdisplay.local");
  }
}

// ______Loop___________
/**
* Loop / Running of program. Calls methods
*/
void loop() {
  server.handleClient();

  if (currentMode == MODE_EYE) {
    eyes.animate();
  }

  if (currentMode == MODE_REPORT) {
    if (display.displayAnimate()) {
      display.displayReset();
    }
  }

  if (millis() - lastUpdate > 300000) {
    lastUpdate = millis();
    if (currentMode != MODE_EYE) {
      display.begin();
      display.setIntensity(1);
      display.displayClear();
      refreshData();
    }
  }
}

// _____WiFi _________
/**
* Connects the ESP to the network.
*/
void connectSTA() {
  WiFi.begin(STA_SSID, STA_PASS);
  Serial.print("Connecting to WiFi");
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected! IP: " + WiFi.localIP().toString());
  } else {
    Serial.println("\nFailed to connect to WiFi (continuing in AP-only mode)");
  }
}

/**
* Creates and setups the AP local site.
*/
void createAP() {
  WiFi.softAP(AP_SSID, AP_PASS);
  Serial.println("AP started. IP: " + WiFi.softAPIP().toString());
}

// _______Web server handlers____________
/**
* The webpage to be displayed by the AP.
*/
String webpage() {
  String html;
  html += "<!DOCTYPE html><html><head>";
  html += "<title>Stock Display</title>";
  html += "<meta name='viewport' content='width=device-width,initial-scale=1'>";
  html += "<style>";
  html += "body{margin:0;min-height:100vh;display:flex;flex-direction:column;justify-content:center;align-items:center;font-family:georgia;background:#0a0a14;color:#4444ff;}";
  html += "h1{text-align:center;font-size:5vw;color:#3d7eff;text-shadow:0 0 10px #2233ff;}";
  html += ".card{background:#0a0a14;padding:30px;min-width:300px;text-align:center;}";
  html += ".current{font-size:1.2vw;margin-bottom:20px;color:#888;}";
  html += ".current span{color:#3d7eff;font-weight:bold;}";
  html += "select{font-size:1.5vw;border:2px solid #3d7eff;border-radius:3px;background:#0a0a14;color:#3d7eff;padding:5px;width:100%;margin-bottom:20px;}";
  html += "select option{background:#0a0a14;color:#3d7eff;}";
  html += ".brightness-label{font-size:1.2vw;margin-bottom:8px;display:block;}";
  html += "input[type=range]{width:100%;accent-color:#3d7eff;margin-bottom:20px;}";
  html += "input[type=submit]{background:#3d7eff;color:#0a0a14;border:none;padding:10px 30px;font-size:1.2vw;font-family:georgia;border-radius:3px;cursor:pointer;width:100%;font-weight:bold;}";
  html += "input[type=submit]:hover{background:#2233ff;box-shadow:0 0 10px #3d7eff;}";
  html += ".brightness-val{font-size:1vw;color:#888;}";
  html += "</style></head><body>";
  html += "<div class='card'>";
  html += "<h1>Stock Display</h1>";

  html += "<div class='current'>Currently showing: <span>";
  switch(currentMode) {
    case MODE_VOO:        
      html += "VOO Price"; 
      break;
    case MODE_FEAR_GREED: 
      html += "Fear &amp; Greed"; 
      break;
    case MODE_EYE:        
      html += "Eyes"; 
      break;
    case MODE_REPORT:     
      html += "Report"; 
      break;
    default:              
      html += "Test"; 
      break;
  }
  html += "</span></div>";

  html += "<form action='/set' method='get'>";
  html += "<select name='mode'>";
  html += "<option value='voo'" + String(currentMode == MODE_VOO ? " selected" : "") + ">VOO Price</option>";
  html += "<option value='fear'" + String(currentMode == MODE_FEAR_GREED ? " selected" : "") + ">Fear &amp; Greed</option>";
  html += "<option value='eyes'" + String(currentMode == MODE_EYE ? " selected" : "") + ">Eyes</option>";
  html += "<option value='report'" + String(currentMode == MODE_REPORT ? " selected" : "") + ">Report</option>";
  html += "<option value='test'" + String(currentMode == MODE_TEST ? " selected" : "") + ">Test</option>";
  html += "</select>";

  html += "<label class='brightness-label'>Brightness: <span class='brightness-val' id='bval'>" + String(currentBrightness) + "</span></label>";
  html += "<input type='range' name='brightness' min='0' max='15' value='" + String(currentBrightness) + "' oninput=\"document.getElementById('bval').innerText=this.value\">";

  html += "<input type='submit' value='Set'>";
  html += "</form>";
  html += "</div>";
  html += "</body></html>";
  return html;
}

/**
* Sends GET method when webpage is opened.
*/
void handleRoot() {
  server.send(200, "text/html", webpage());
}

/**
* Updates mode when updated through webpage.
*/
void handleSet() {
  if (server.hasArg("brightness")) {
    currentBrightness = server.arg("brightness").toInt();
    display.setIntensity(currentBrightness);
  }

  if (server.hasArg("mode")) {
    String mode = server.arg("mode");

    if (mode == "eyes") {
      display.displayClear();
      mx.begin();
      mx.clear();
      eyes.begin(1, &mx, 500);
      currentMode = MODE_EYE;
    } else {
      display.begin();
      display.setIntensity(currentBrightness);  // use saved brightness
      display.displayClear();

      if      (mode == "voo")    
        currentMode = MODE_VOO;
      else if (mode == "fear")   
        currentMode = MODE_FEAR_GREED;
      else if (mode == "report") 
        currentMode = MODE_REPORT;
      else                       
        currentMode = MODE_TEST;

      refreshData();
    }
  }
  server.send(200, "text/html", webpage());  // send back updated page instead of redirect
}
// ________Data fetching ____________
/**
* Gets the Vanguard S&P 500 ETF price
*/
String getVOO() {
  if (WiFi.status() != WL_CONNECTED) return "NO WIFI";

  HTTPClient http;
  http.begin("https://query1.finance.yahoo.com/v8/finance/chart/VOO?interval=1d&range=1d");
  http.addHeader("User-Agent", "Mozilla/5.0");
  int code = http.GET();

  if (code <= 0) {
    http.end();
    return "ERR";
  }

  DynamicJsonDocument doc(8192);
  deserializeJson(doc, http.getString());
  http.end();

  float price = doc["chart"]["result"][0]["meta"]["regularMarketPrice"].as<float>();
  float open  = doc["chart"]["result"][0]["meta"]["chartPreviousClose"].as<float>();

  if (price == 0) return "N/A";

  String direction = "";
  if (open != 0) {
    if (price > open)      
      direction = "U";
    else if (price < open) 
      direction = "D";
    else                   
      direction = "=";
  }

  return "$" + String((int)price) + direction;
}

/**
* Displays the current market fear and greed index.
*/  
String getFearGreed() {
  if (WiFi.status() != WL_CONNECTED) return "NO WIFI";

  HTTPClient http;
  http.begin("https://api.alternative.me/fng/");
  int code = http.GET();

  if (code <= 0) {
    http.end();
    return "ERR";
  }

  DynamicJsonDocument doc(1024);
  deserializeJson(doc, http.getString());
  http.end();

  int value = doc["data"][0]["value"].as<int>();
  if (value == 0) return "N/A";
  
  String type = "";

  String classification = String(doc["data"][0]["value_classification"]);
  if (classification == "Extreme Greed") 
    type = "EG";
  else if (classification == "Greed")
    type = "G";
  else if (classification == "Extreme Fear")
    type = "EF";
  else if (classification == "Fear")
    type = "F";
  else
    type = "";

  return type + " " + String(value);  // just "65" to keep it short on display
}

/**
* Displays stock price of given symbol.
*/
String getStockPrice(String symbol) {
  if (WiFi.status() != WL_CONNECTED) return "ERR";

  HTTPClient http;
  String url = "https://query1.finance.yahoo.com/v8/finance/chart/" + symbol + "?interval=1d&range=1d";
  http.begin(url);
  http.addHeader("User-Agent", "Mozilla/5.0");
  int code = http.GET();

  if (code <= 0) { http.end(); return "ERR"; }

  DynamicJsonDocument doc(8192);
  deserializeJson(doc, http.getString());
  http.end();

  float price = doc["chart"]["result"][0]["meta"]["regularMarketPrice"].as<float>();
  float open  = doc["chart"]["result"][0]["meta"]["chartPreviousClose"].as<float>();

  if (price == 0) return "ERR";

  String direction = "";
  if (open != 0) {
    if (price > open) 
      direction = "U";
    else if (price < open) 
      direction = "D";
    else 
      direction = "=";
  }

  return symbol + " $" + String((int)price) + " " + direction;
}

/**
* Report mode. Shows various primary stock day performances.
*/
String buildTickerString() {
  String symbols[] = {
    "AMZN", "AAPL", "TSLA", "GOOGL",
    "BTC-USD", "ETH-USD", "JPM", "NVDA",
    "BRK-B", "MSFT", "META", "LLY"
  };
  String names[] = {
    "AMZN", "AAPL", "TSLA", "GOOG",
    "BTC", "ETH", "JPM", "NVDA",
    "BRKB", "MSFT", "META", "LLY"
  };

  int count = 12;
  String ticker = "";

  for (int i = 0; i < count; i++) {
    Serial.println("Fetching: " + symbols[i]);

    HTTPClient http;
    String url = "https://query1.finance.yahoo.com/v8/finance/chart/" + symbols[i] + "?interval=1d&range=1d";
    http.begin(url);
    http.addHeader("User-Agent", "Mozilla/5.0");
    int code = http.GET();

    if (code > 0) {
      DynamicJsonDocument doc(4096);
      deserializeJson(doc, http.getString());

      float price = doc["chart"]["result"][0]["meta"]["regularMarketPrice"].as<float>();
      float open  = doc["chart"]["result"][0]["meta"]["chartPreviousClose"].as<float>();

      String direction = "=";
      if      (price > open) direction = "U";
      else if (price < open) direction = "D";

      // Format to 2 decimal places
      char priceStr[12];
      dtostrf(price, 1, 2, priceStr);

      ticker += names[i] + " " + String(priceStr) + " " + direction + "  ";
    } else {
      ticker += names[i] + " ERR  ";
    }

    http.end();
    delay(100);
  }

  return ticker;
}

// _______Display_______
/**
* Shows the stock price on screen.
*/
void showMessage(String msg) {
  display.displayClear();
  display.setTextAlignment(PA_CENTER);
  display.print(msg.c_str());
}

/**
* Updates the mode when changed.
*/
void refreshData() {
  String text;
  switch (currentMode) {
    case MODE_VOO:        
      text = "" + getVOO();   
      break;
    case MODE_FEAR_GREED: 
      text = "" + getFearGreed();       
      break;
    case MODE_EYE:
      break;
    case MODE_REPORT:
      text = buildTickerString();
      display.displayClear();
      display.setTextAlignment(PA_LEFT);
      display.displayScroll(text.c_str(), PA_LEFT, PA_SCROLL_LEFT, 80);
      return;
    default:              
      text = "HELLO";             
      break;
  }
  showMessage(text);
}
