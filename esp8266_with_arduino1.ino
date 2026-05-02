String ssid = "Simulator Wifi";   // Wi-Fi SSID
String password = "";            // Wi-Fi Password (leave empty if no password) virtual wi-fi has no password
String host = "https://api.thingspeak.com";
const int httpPort = 80;
//write API key
String uri = "/update?api_key=YOUR_API_KEY&field1=0"; // Replace YOUR_WRITE_API_KEY with your actual Write API Key

int setupESP8266(void) {
  Serial.begin(115200); // Start the Serial communication at 115200 baud rate
  Serial.println("AT"); // Check if the ESP8266 is responding
  delay(1000);
 
  
  // Connect to Wi-Fi
  Serial.println("AT+CWJAP=\"" + ssid + "\",\"" + password + "\"");
  delay(1000);
  
  // Open TCP connection to ThingSpeak
  Serial.println("AT+CIPSTART=\"TCP\",\"" + host + "\"," + String(httpPort));
  delay(1000);
}

void TemperatureUploadESP8266() {
  int temp = map(analogRead(A0), 0, 1023, 0, 100); // Convert potentiometer reading to a temperature value
  Serial.println(temp);
  
  // Construct the HTTP request
  String httpPacket = "GET " + uri + String(temp) + " HTTP/1.1\r\n" +
                      "Host: " + host + "\r\n" +
                      "Connection: close\r\n\r\n";
  
  // Send the HTTP request
  Serial.print("AT+CIPSEND=");
  Serial.println(httpPacket.length());
  delay(1000);
  
  Serial.print(httpPacket);
  delay(1000);
}

void setup() {
  setupESP8266(); // Setup the ESP8266 module
}

void loop() {
  TemperatureUploadESP8266(); // Upload temperature data
  delay(1500); // Wait for 15 seconds before sending the next data
}
