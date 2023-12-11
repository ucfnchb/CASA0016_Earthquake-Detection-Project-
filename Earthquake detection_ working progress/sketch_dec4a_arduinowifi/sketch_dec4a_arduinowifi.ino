#include <WiFiNINA.h>
#include <ArduinoHttpClient.h>


const char* ssid = "CE-Hub-Student";
const char* password = "casa-ce-gagarin-public-service";

const char* serverName = "earthquake.usgs.gov";
const int port = 443; 

WiFiSSLClient wifiClient;
HttpClient client = HttpClient(wifiClient, serverName, port);

void setup() {

  Serial.begin(9600);


  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Connecting to WiFi...");
    WiFi.begin(ssid, password);
    delay(5000);
  }


  Serial.println("Connected to WiFi");
}

void loop() {
 
  Serial.println("Making HTTPS request...");
  client.get("/earthquakes/feed/v1.0/summary/4.5_hour.geojson");

  // Retrieve the response status code
  int statusCode = client.responseStatusCode();
  Serial.print("Status code: ");
  Serial.println(statusCode);

 
  if (statusCode > 0) {
    String response = client.responseBody();
    Serial.println("Received response:");
    Serial.println(response);
  } else {
   
    Serial.println("Error in HTTP request");
  }


  delay(10000);
}
