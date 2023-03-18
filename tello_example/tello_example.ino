#include <Tello.h>
#include <ESP8266WiFi.h>

// WiFi network name and password:
const char * networkName = "TELLO-XXXX";//Replace with your Tello SSID
const char * networkPswd = "";

//Are we currently connected?
boolean connected = false;

Tello tello;

void setup() 
{
  Serial.begin(9600); 
  //Connect to the WiFi network
  connectToWiFi(networkName, networkPswd);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  if(connected )
  {
    tello.takeoff();
    delay(5000);
    tello.up(30);
    delay(2000);
    tello.down(30);
    delay(2000);
    tello.right(30);
    delay(2000);
    tello.left(30);
    delay(2000);
    tello.land();
    //you have 5 seconds to save your tello before it takes off again
    delay(5000);

    //do once and go into a while loop
    while(1)
    {
      delay(5000);
    }
  }
}

void connectToWiFi(const char * ssid, const char * pwd) 
{
  Serial.println("Connecting to WiFi network: " + String(ssid));

  // delete old config
  WiFi.disconnect(true);
  //register event handler
  WiFi.onEvent(WiFiEvent);

  //Initiate connection
  WiFi.begin(ssid, pwd);

  Serial.println("Waiting for WIFI connection...");
}

//wifi event handler
void WiFiEvent(WiFiEvent_t event) 
{
  switch (event) 
  {
    case WIFI_EVENT_STAMODE_CONNECTED:
      Serial.println("WiFi connected");
      break;
      
    case WIFI_EVENT_STAMODE_DISCONNECTED:
      Serial.println("WiFi disconnected");
      connected = false;
      break;
      
    case WIFI_EVENT_STAMODE_GOT_IP:
      Serial.print("WiFi connected! IP address: ");
      Serial.println(WiFi.localIP());
      //initialise Tello after we are connected
      tello.init();
      connected = true;
      break;
  }
}
