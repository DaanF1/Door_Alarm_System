<!-- Navigable Item -->
<a id="readme-top"></a>

<!-- General Information -->
<div align="center">
  <h1 align="center">Door Alarm System</h1>
  <img width="600" src="https://github.com/DaanF1/Door_Alarm_System/blob/main/Images/Breadboard_Setup.jpeg"/>
</div>

<!-- Divider -->
___

<!-- Table Of Contents -->
<details open>
 <summary><strong>📚 Table of Contents</strong></summary>
  
- [About This Repository](#about-this-repository)<br>
   - [Built With](#built-with)<br>
   - [MQTT Protocol](#mqtt-protocol)<br>
   - [Topics](#topics)<br>
   - [Wiring Diagram](#wiring-diagram)<br>
</details>

<!-- Divider -->
___

<!-- About This Repository -->
# About This Repository
This repository contains a basic door alarm system simulated on a breadboard using an MQTT service.

<!-- Built With -->
## Built With
This project was built using the [Arduino IDE](https://www.arduino.cc/en/software/), together with the [WiFi.h](https://github.com/arduino-libraries/WiFi/tree/master) and [PubSubClient.h](https://github.com/knolleary/pubsubclient) libraries.

<!-- Details -->
## MQTT Protocol
The project makes use of the MQTT (Message Queuing Telemetry Transport) protocol. The client subscribes to the broker, which acts like a middleman that transfers data to various topics. The client can control to which topics it subscribes. These topics can also send their data back to the client via the broker.
<div align="center">
    <img width="700" src="https://github.com/DaanF1/Door_Alarm_System/blob/main/Images/MQTT_Architecture.png"/>
</div>

## Topics
There are 2 topics for the project: doorOpened and alarm. Both of these topics can only be either 1 or 0 (true or false). The doorOpened topic is set to 1 if a door is opened via a single button press, and set to 0 when both buttons are pressed. The alarm topic is set to 1 if the alarm should soon be activated. This flickers the yellow LED first. After roughly 10 seconds the yellow LED will stop flickering and the red LED wil start flickering. The buzzer will then also start beeping an alarm sound.

## Wiring Diagram
The Wiring Diagram below shows the pin layout of the project, as well as the used components.
<div align="center">
    <img width="700" src="https://github.com/DaanF1/Door_Alarm_System/blob/main/Images/Schematic_Door_Alarm_System.png"/>
</div>

<!-- Back To Top -->
<p align="right"><a href="#readme-top">Back To Top</a></p>
