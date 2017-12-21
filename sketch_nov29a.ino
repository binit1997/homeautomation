#include <ESP8266WiFi.h>

const char* ssid = "iPhone";
const char* password = "qwerty13";

int ledPin = 15; // GPIO13
int ledPin1 = 0; // GPIO3
int relaypin = 5;//1
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  pinMode(ledPin1, OUTPUT);
  digitalWrite(ledPin1, LOW);

  pinMode(relaypin, OUTPUT);
  digitalWrite(relaypin, LOW);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  // Match the request

  int value = HIGH;
  int value2 = HIGH;
  int value1 = LOW;
  
  if (request.indexOf("/LED=ON") != -1)  {
    digitalWrite(ledPin, LOW);
    value = HIGH;
  }
  if (request.indexOf("/LED=OFF") != -1)  {
    digitalWrite(ledPin,HIGH);
    value = LOW;
  }

    if (request.indexOf("/LED1=ON") != -1)  {
    digitalWrite(ledPin1, LOW);
    value2 = HIGH;
  }
  if (request.indexOf("/LED1=OFF") != -1)  {
    digitalWrite(ledPin1,HIGH);
    value2 = LOW;
  }

  if (request.indexOf("/RELAY=ON") != -1)  {
    digitalWrite(relaypin, LOW);
    value1 = HIGH;
  }
  if (request.indexOf("/RELAY=OFF") != -1)  {
    digitalWrite(relaypin, HIGH);
    value1 = LOW;
  }

  // Set ledPin according to the request
  //digitalWrite(ledPin, value);

  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<center>");
  client.println("<body bgcolor= cyan>");
  client.println("<h1><font face= verdana>IC Project: Home Automation</font></h1>");

  client.println("<h3><font face= verdana>[15BEE065]</font></h3>");
  client.println("<br>");

  client.println("<table border = 3><tr><td>  LIGHT_ONE:  </td></td> </table>");
  client.println("<p>  </p>");
  client.println("<a href=\"/LED=ON\"\"><button>Turn OFF </button></a>");
  client.println("<a href=\"/LED=OFF\"\"><button>Turn ON </button></a><br />");

  client.print("(LIGHT_ONE is now: ");
  if (value == HIGH) {
    client.print("OFF)");
  } else {
    client.print("ON)");
  }
  client.println("<p> ...........  </p>");
  client.println("<p>   </p>");


    client.println("<table border = 3><tr><td>  LIGHT_TWO:  </td></td> </table>");
  client.println("<p>  </p>");
  client.println("<a href=\"/LED1=ON\"\"><button>Turn OFF </button></a>");
  client.println("<a href=\"/LED1=OFF\"\"><button>Turn ON </button></a><br />");

  client.print("(LIGHT_TWO is now: ");
  if (value2 == HIGH) {
    client.print("OFF)");
  } else {
    client.print("ON)");
  }
  client.println("<p> ...........  </p>");
  client.println("<p>   </p>");

  
  client.println("<table border = 3><tr><td>  RELAY_ONE:  </td></td> </table>");
  client.println("<p>  </p>");
  client.println("<a href=\"/RELAY=OFF\"\"><button> Turn OFF </button></a>");
  client.println("<a href=\"/RELAY=ON\"\"><button> Turn ON </button></a><br />");
  

  client.print("(RELAY_ONE is now: ");
  if (value1 == HIGH) {
    client.print("ON)");
  } else {
    client.print("OFF)");
  }


  client.println("<br><br>");
  client.println("</body>");
  client.println("</center>");
  client.println("</html>");

  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");

}

