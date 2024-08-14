#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

class Fetchxios {
  public:
    struct Response {
      int statusCode;
      String body;
      JsonDocument json;
    
      Response() : statusCode(0), body("") {}
    };

    Fetchxios();
    void setBaseURL(const char* baseURL);
    void GET(const char* endpoint);
    void POST(const char* endpoint, const String& payload);
    void PUT(const char* endpoint, const char* payload);
    void DELETE(const char* endpoint);
    String getString();
    int getCode();
    Response getData();
    void end();

  private:
    HTTPClient http;
    String response;
    int httpCode;
    String baseURL;
};

Fetchxios::Fetchxios() {
  // Constructor
}

void Fetchxios::setBaseURL(const char* baseURL) {
  this->baseURL = String(baseURL);
}

void Fetchxios::GET(const char* endpoint) {
  String url = baseURL + endpoint;
  http.begin(url);
  httpCode = http.GET();
  if (httpCode > 0) {
    response = http.getString();
  } else {
    response = "Error on HTTP GET request";
  }
  http.end();
}

void Fetchxios::POST(const char* endpoint, const String& payload) {
  String url = baseURL + endpoint;
  http.begin(url);
  http.addHeader("Content-Type", "application/json");

  httpCode = http.POST(payload);

  if (httpCode > 0) {
    response = http.getString();
  } else {
    response = "Error on HTTP POST request";
  }

  http.end();  // Close connection
}

void Fetchxios::PUT(const char* endpoint, const char* payload) {
  String url = baseURL + endpoint;
  http.begin(url);
  http.addHeader("Content-Type", "application/json");
  httpCode = http.PUT(payload);
  if (httpCode > 0) {
    response = http.getString();
  } else {
    response = "Error on HTTP PUT  request ";
  }
  http.end();
}

void Fetchxios::DELETE(const char* endpoint) {
  String url = baseURL + endpoint;
  http.begin(url);
  httpCode = http.sendRequest("DELETE");
  if (httpCode > 0) {
    response = http.getString();
  } else {
    response = "Error on HTTP DELETE request";
  }
  http.end();
}

String Fetchxios::getString() {
  return response;
}

int Fetchxios::getCode() {
  return httpCode;
}

Fetchxios::Response Fetchxios::getData() {
  Response res;
  res.statusCode = httpCode;
  res.body = response;

  JsonDocument doc;
  DeserializationError error = deserializeJson(doc, response);

  if (!error) {
    res.json = doc;
  } else {
    Serial.println("Failed to parse JSON");
  }

  return res;
}

void Fetchxios::end() {
  http.end();
}
