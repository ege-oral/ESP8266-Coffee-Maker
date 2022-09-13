
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>


//---------------------------------------------------------------
//Our HTML webpage contents in program memory
const char MAIN_page_before_making_coffee[] PROGMEM = R"=====(
  <html lang="en">
<head>
    <style>
        @import url('https://fonts.googleapis.com/css?family=Montserrat:600&display=swap');
        body{
        margin-top: -250px;
        padding: 0;
        display: flex;
        height: 100vh;
        align-items: center;
        justify-content: center;
        background:grey;
        }
        span{
        position: relative;
        display: inline-flex;
        width: 180px;
        height: 55px;
        margin: 0 15px;
        perspective: 1000px;
        }
        span a{
        font-size: 19px;
        letter-spacing: 1px;
        transform-style: preserve-3d;
        transform: translateZ(-25px);
        transition: transform .25s;
        font-family: 'Montserrat', sans-serif;
        
        }
        span a:before{
        position: absolute;
        content: "coffee";
        height: 55px;
        width: 180px;
        display: flex;
        align-items: center;
        justify-content: center;
        border: 5px solid black;
        box-sizing: border-box;
        border-radius: 5px;
        }
        span a:after{
            position: absolute;
            content: "Make A coffee";
            height: 55px;
            width: 180px;
            display: flex;
            align-items: center;
            justify-content: center;
            border: 5px solid black;
            box-sizing: border-box;
            border-radius: 5px;
            background-color: greenyellow;
        }
        span a:before{
        color: #fff;
        background: purple;
        transform: rotateY(0deg) translateZ(25px);
        }
        span a:after{
        color: #000;
        transform: rotateX(90deg) translateZ(25px);
        }
        span a:hover{
        transform: translateZ(-25px) rotateX(-90deg);
        }


        .container {
        width: 300px;
        height: 280px;
        position: absolute;
        top: calc(50% - 140px);
        left: calc(50% - 150px);
        }
        .coffee-header {
        width: 100%;
        height: 80px;
        position: absolute;
        top: 0;
        left: 0;
        background-color: #ddcfcc;
        border-radius: 10px;
        }
        .coffee-header__buttons {
        width: 25px;
        height: 25px;
        position: absolute;
        top: 25px;
        background-color: #282323;
        border-radius: 50%;
        }
        .coffee-header__buttons::after {
        content: "";
        width: 8px;
        height: 8px;
        position: absolute;
        bottom: -8px;
        left: calc(50% - 4px);
        background-color: #615e5e;
        }
        .coffee-header__button-one {
        left: 15px;
        }
        .coffee-header__button-two {
        left: 50px;
        }
        .coffee-header__display {
        width: 50px;
        height: 50px;
        position: absolute;
        top: calc(50% - 25px);
        left: calc(50% - 25px);
        border-radius: 50%;
        background-color: #9acfc5;
        border: 5px solid #43beae;
        box-sizing: border-box;
        }
        .coffee-header__details {
        width: 8px;
        height: 20px;
        position: absolute;
        top: 10px;
        right: 10px;
        background-color: #9b9091;
        box-shadow: -12px 0 0 #9b9091, -24px 0 0 #9b9091;
        }
        .coffee-medium {
        width: 90%;
        height: 160px;
        position: absolute;
        top: 80px;
        left: calc(50% - 45%);
        background-color: #bcb0af;
        }
        .coffee-medium:before {
        content: "";
        width: 90%;
        height: 100px;
        background-color: #776f6e;
        position: absolute;
        bottom: 0;
        left: calc(50% - 45%);
        border-radius: 20px 20px 0 0;
        }
        .coffee {
        width: 60px;
        height: 20px;
        position: absolute;
        top: 0;
        left: calc(50% - 30px);
        background-color: #231f20;
        }
        .coffee::before {
        content: "";
        width: 50px;
        height: 20px;
        border-radius: 0 0 50% 50%;
        position: absolute;
        bottom: -20px;
        left: calc(50% - 25px);
        background-color: #231f20;
        }
        .coffee::after {
        content: "";
        width: 10px;
        height: 10px;
        position: absolute;
        bottom: -30px;
        left: calc(50% - 5px);
        background-color: #231f20;
        }
        .coffee-medium__arm {
        width: 70px;
        height: 20px;
        position: absolute;
        top: 15px;
        right: 25px;
        background-color: #231f20;
        }
        .coffee-medium__arm::before {
        content: "";
        width: 15px;
        height: 5px;
        position: absolute;
        top: 7px;
        left: -15px;
        background-color: #9e9495;
        }
        .coffee-medium__cup {
        width: 80px;
        height: 47px;
        position: absolute;
        bottom: 0;
        left: calc(50% - 40px);
        background-color: #FFF;
        border-radius: 0 0 70px 70px / 0 0 110px 110px;
        }
        .coffee-medium__cup::after {
        content: "";
        width: 20px;
        height: 20px;
        position: absolute;
        top: 6px;
        right: -13px;
        border: 5px solid #FFF;
        border-radius: 50%;
        }
        @keyframes liquid {
        0% {
            height: 0px;  
            opacity: 1;
        }
        5% {
            height: 0px;  
            opacity: 1;
        }
        20% {
            height: 62px;  
            opacity: 1;
        }
        95% {
            height: 62px;
            opacity: 1;
        }
        100% {
            height: 62px;
            opacity: 0;
        }
        }
        .coffee-medium__liquid {
        width: 6px;
        height: 63px;
        opacity: 0;
        position: absolute;
        top: 50px;
        left: calc(50% - 3px);
        background-color: #74372b;
        animation: liquid 4s 4s linear infinite;
        }
        .coffee-medium__smoke {
        width: 8px;
        height: 20px;
        position: absolute;  
        border-radius: 5px;
        background-color: #b3aeae;
        }
        @keyframes smokeOne {
        0% {
            bottom: 20px;
            opacity: 0;
        }
        40% {
            bottom: 50px;
            opacity: .5;
        }
        80% {
            bottom: 80px;
            opacity: .3;
        }
        100% {
            bottom: 80px;
            opacity: 0;
        }
        }
        @keyframes smokeTwo {
        0% {
            bottom: 40px;
            opacity: 0;
        }
        40% {
            bottom: 70px;
            opacity: .5;
        }
        80% {
            bottom: 80px;
            opacity: .3;
        }
        100% {
            bottom: 80px;
            opacity: 0;
        }
        }
        .coffee-medium__smoke-one {
        opacity: 0;
        bottom: 50px;
        left: 102px;
        animation: smokeOne 3s 4s linear infinite;
        }
        .coffee-medium__smoke-two {
        opacity: 0;
        bottom: 70px;
        left: 118px;
        animation: smokeTwo 3s 5s linear infinite;
        }
        .coffee-medium__smoke-three {
        opacity: 0;
        bottom: 65px;
        right: 118px;
        animation: smokeTwo 3s 6s linear infinite;
        }
        .coffee-medium__smoke-for {
        opacity: 0;
        bottom: 50px;
        right: 102px;
        animation: smokeOne 3s 5s linear infinite;
        }
        .coffee-footer {
        width: 95%;
        height: 15px;
        position: absolute;
        bottom: 25px;
        left: calc(50% - 47.5%);
        background-color: #41bdad;
        border-radius: 10px;
        }
        .coffee-footer::after {
        content: "";
        width: 106%;
        height: 26px;
        position: absolute;
        bottom: -25px;
        left: -8px;
        background-color: #000;
        }
    </style>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>coffee</title>
</head>
<body>
    <div class="container">
        <div class="coffee-header">
          <div class="coffee-header__buttons coffee-header__button-one"></div>
          <div class="coffee-header__buttons coffee-header__button-two"></div>
          <div class="coffee-header__display"></div>
          <div class="coffee-header__details"></div>
        </div>
        <div class="coffee-medium">
          <div class="coffee"></div>
          <div class="coffee-medium__arm"></div>
          <div class="coffee-medium__liquid"></div>
          <div class="coffee-medium__smoke coffee-medium__smoke-one"></div>
          <div class="coffee-medium__smoke coffee-medium__smoke-two"></div>
          <div class="coffee-medium__smoke coffee-medium__smoke-three"></div>
          <div class="coffee-medium__smoke coffee-medium__smoke-for"></div>
          <div class="coffee-medium__cup"></div>
        </div>
        <div class="coffee-footer"></div>
      </div>
    <span><a href="coffeeON"></a></span>
</body>
</html>
)=====";
//---------------------------------------------------------------

const char MAIN_page_after_making_coffee[] PROGMEM = R"=====(
  <html lang="en">
<head>
    <style>
        @import url('https://fonts.googleapis.com/css?family=Montserrat:600&display=swap');
        body{
        margin-top: -250px;
        padding: 0;
        display: flex;
        height: 100vh;
        align-items: center;
        justify-content: center;
        background:grey;
        }
        span{
        position: relative;
        display: inline-flex;
        width: 180px;
        height: 55px;
        margin: 0 15px;
        perspective: 1000px;
        }
        span a{
        font-size: 19px;
        letter-spacing: 1px;
        transform-style: preserve-3d;
        transform: translateZ(-25px);
        transition: transform .25s;
        font-family: 'Montserrat', sans-serif;
        
        }
        span a:before{
        position: absolute;
        content: "Preparing";
        height: 55px;
        width: 180px;
        display: flex;
        align-items: center;
        justify-content: center;
        border: 5px solid black;
        box-sizing: border-box;
        border-radius: 5px;
        }
        span a:after{
            position: absolute;
            content: "Stop Making";
            height: 55px;
            width: 180px;
            display: flex;
            align-items: center;
            justify-content: center;
            border: 5px solid black;
            box-sizing: border-box;
            border-radius: 5px;
            background-color: red;
        }
        span a:before{
        color: #fff;
        background: purple;
        transform: rotateY(0deg) translateZ(25px);
        }
        span a:after{
        color: #000;
        transform: rotateX(90deg) translateZ(25px);
        }
        span a:hover{
        transform: translateZ(-25px) rotateX(-90deg);
        }


        .container {
        width: 300px;
        height: 280px;
        position: absolute;
        top: calc(50% - 140px);
        left: calc(50% - 150px);
        }
        .coffee-header {
        width: 100%;
        height: 80px;
        position: absolute;
        top: 0;
        left: 0;
        background-color: #ddcfcc;
        border-radius: 10px;
        }
        .coffee-header__buttons {
        width: 25px;
        height: 25px;
        position: absolute;
        top: 25px;
        background-color: #282323;
        border-radius: 50%;
        }
        .coffee-header__buttons::after {
        content: "";
        width: 8px;
        height: 8px;
        position: absolute;
        bottom: -8px;
        left: calc(50% - 4px);
        background-color: #615e5e;
        }
        .coffee-header__button-one {
        left: 15px;
        }
        .coffee-header__button-two {
        left: 50px;
        }
        .coffee-header__display {
        width: 50px;
        height: 50px;
        position: absolute;
        top: calc(50% - 25px);
        left: calc(50% - 25px);
        border-radius: 50%;
        background-color: #9acfc5;
        border: 5px solid #43beae;
        box-sizing: border-box;
        }
        .coffee-header__details {
        width: 8px;
        height: 20px;
        position: absolute;
        top: 10px;
        right: 10px;
        background-color: #9b9091;
        box-shadow: -12px 0 0 #9b9091, -24px 0 0 #9b9091;
        }
        .coffee-medium {
        width: 90%;
        height: 160px;
        position: absolute;
        top: 80px;
        left: calc(50% - 45%);
        background-color: #bcb0af;
        }
        .coffee-medium:before {
        content: "";
        width: 90%;
        height: 100px;
        background-color: #776f6e;
        position: absolute;
        bottom: 0;
        left: calc(50% - 45%);
        border-radius: 20px 20px 0 0;
        }
        .coffe-medium__exit {
        width: 60px;
        height: 20px;
        position: absolute;
        top: 0;
        left: calc(50% - 30px);
        background-color: #231f20;
        }
        .coffe-medium__exit::before {
        content: "";
        width: 50px;
        height: 20px;
        border-radius: 0 0 50% 50%;
        position: absolute;
        bottom: -20px;
        left: calc(50% - 25px);
        background-color: #231f20;
        }
        .coffe-medium__exit::after {
        content: "";
        width: 10px;
        height: 10px;
        position: absolute;
        bottom: -30px;
        left: calc(50% - 5px);
        background-color: #231f20;
        }
        .coffee-medium__arm {
        width: 70px;
        height: 20px;
        position: absolute;
        top: 15px;
        right: 25px;
        background-color: #231f20;
        }
        .coffee-medium__arm::before {
        content: "";
        width: 15px;
        height: 5px;
        position: absolute;
        top: 7px;
        left: -15px;
        background-color: #9e9495;
        }
        .coffee-medium__cup {
        width: 80px;
        height: 47px;
        position: absolute;
        bottom: 0;
        left: calc(50% - 40px);
        background-color: #FFF;
        border-radius: 0 0 70px 70px / 0 0 110px 110px;
        }
        .coffee-medium__cup::after {
        content: "";
        width: 20px;
        height: 20px;
        position: absolute;
        top: 6px;
        right: -13px;
        border: 5px solid #FFF;
        border-radius: 50%;
        }
        @keyframes liquid {
        0% {
            height: 0px;  
            opacity: 1;
        }
        5% {
            height: 0px;  
            opacity: 1;
        }
        20% {
            height: 62px;  
            opacity: 1;
        }
        95% {
            height: 62px;
            opacity: 1;
        }
        100% {
            height: 62px;
            opacity: 0;
        }
        }
        .coffee-medium__liquid {
        width: 6px;
        height: 63px;
        opacity: 0;
        position: absolute;
        top: 50px;
        left: calc(50% - 3px);
        background-color: #74372b;
        animation: liquid 4s 4s linear infinite;
        }
        .coffee-medium__smoke {
        width: 8px;
        height: 20px;
        position: absolute;  
        border-radius: 5px;
        background-color: #b3aeae;
        }
        @keyframes smokeOne {
        0% {
            bottom: 20px;
            opacity: 0;
        }
        40% {
            bottom: 50px;
            opacity: .5;
        }
        80% {
            bottom: 80px;
            opacity: .3;
        }
        100% {
            bottom: 80px;
            opacity: 0;
        }
        }
        @keyframes smokeTwo {
        0% {
            bottom: 40px;
            opacity: 0;
        }
        40% {
            bottom: 70px;
            opacity: .5;
        }
        80% {
            bottom: 80px;
            opacity: .3;
        }
        100% {
            bottom: 80px;
            opacity: 0;
        }
        }
        .coffee-medium__smoke-one {
        opacity: 0;
        bottom: 50px;
        left: 102px;
        animation: smokeOne 3s 4s linear infinite;
        }
        .coffee-medium__smoke-two {
        opacity: 0;
        bottom: 70px;
        left: 118px;
        animation: smokeTwo 3s 5s linear infinite;
        }
        .coffee-medium__smoke-three {
        opacity: 0;
        bottom: 65px;
        right: 118px;
        animation: smokeTwo 3s 6s linear infinite;
        }
        .coffee-medium__smoke-for {
        opacity: 0;
        bottom: 50px;
        right: 102px;
        animation: smokeOne 3s 5s linear infinite;
        }
        .coffee-footer {
        width: 95%;
        height: 15px;
        position: absolute;
        bottom: 25px;
        left: calc(50% - 47.5%);
        background-color: #41bdad;
        border-radius: 10px;
        }
        .coffee-footer::after {
        content: "";
        width: 106%;
        height: 26px;
        position: absolute;
        bottom: -25px;
        left: -8px;
        background-color: #000;
        }
    </style>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Coffe</title>
</head>
<body>
    <div class="container">
        <div class="coffee-header">
          <div class="coffee-header__buttons coffee-header__button-one"></div>
          <div class="coffee-header__buttons coffee-header__button-two"></div>
          <div class="coffee-header__display"></div>
          <div class="coffee-header__details"></div>
        </div>
        <div class="coffee-medium">
          <div class="coffe-medium__exit"></div>
          <div class="coffee-medium__arm"></div>
          <div class="coffee-medium__liquid"></div>
          <div class="coffee-medium__smoke coffee-medium__smoke-one"></div>
          <div class="coffee-medium__smoke coffee-medium__smoke-two"></div>
          <div class="coffee-medium__smoke coffee-medium__smoke-three"></div>
          <div class="coffee-medium__smoke coffee-medium__smoke-for"></div>
          <div class="coffee-medium__cup"></div>
        </div>
        <div class="coffee-footer"></div>
      </div>
    <span><a href="CoffeeOFF"></a></span>
</body>
</html>
)=====";
//---------------------------------------------------------------
//Static IP address configuration
IPAddress staticIP(192, 168, 1, 130); //ESP static ip
IPAddress gateway(192, 168, 1, 1);   //IP Address of your WiFi Router (Gateway)
IPAddress subnet(255, 255, 255, 0);  //Subnet mask
IPAddress primaryDNS(8, 8, 8, 8);  //DNS
IPAddress secondaryDNS(8,8,4,4);


const char* deviceName = "Coffee_NodeMCU";
const char* ssid = "Network Name";
const char* password = "Network Password";

const uint8_t D_0 = 16;
const uint8_t D_2 = 4;

ESP8266WebServer server(80); //Server on port 80

//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void handleRoot() {
 Serial.println("You called root page");
 server.send(200, "text/html", MAIN_page_before_making_coffee); //Send web page
}

void handle_before_making_coffee() { 
 Serial.println("Make Coffe Page");
 digitalWrite(D_0, HIGH);
 digitalWrite(D_2, LOW);
 delay(500);
 digitalWrite(D_0, LOW);
 digitalWrite(D_2, HIGH);
 server.send(200, "text/html", MAIN_page_after_making_coffe); //Send web page
}

void handle_after_making_coffe() { 
 Serial.println("Stop Coffe Page");
 digitalWrite(D_0, HIGH);
 digitalWrite(D_2, LOW);
 delay(500);
 digitalWrite(D_0, LOW);
 digitalWrite(D_2, HIGH);
 server.send(200, "text/html", MAIN_page_before_making_coffee); //Send web page
}
//==============================================================
//                  SETUP
//==============================================================

void setup() {
  Serial.begin(115200);
   pinMode(D_0, OUTPUT);
  pinMode(D_2, OUTPUT);
 
  digitalWrite(D_0, LOW);
  digitalWrite(D_2, HIGH);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  if(!WiFi.config(staticIP, gateway, subnet, primaryDNS, secondaryDNS))
  {
    Serial.println("STA Failed to configure");
  }
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.on("/", handleRoot);      //Which routine to handle at root location. This is display page
  server.on("/CoffeeON", handle_before_making_coffee); //as Per  <a href="ledOn">, Subroutine to be called
  server.on("/CoffeeOFF", handle_after_making_coffee);
  server.begin();                  //Start server
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();          //Handle client requests
}
