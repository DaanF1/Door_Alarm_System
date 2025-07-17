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
   - [Wiring Diagram](#wiring-diagram)<br>
- [MQTT Protocol](#mqtt-protocol)<br>
   - [Topics](#topics)<br>
   - [Viewing The Protocol](#viewing-the-protocol)<br>
</details>

<!-- Divider -->
___
<!-- Badges -->
[![GitHub Release](https://img.shields.io/github/v/release/DaanF1/Door_Alarm_System?style=for-the-badge&labelColor=%23000000)](https://github.com/DaanF1/Door_Alarm_System/releases)

<!-- About This Repository -->
# About This Repository
This repository contains a basic door alarm system simulated on a breadboard using an MQTT service.<br>
This project was built using the [Arduino IDE](https://www.arduino.cc/en/software/), together with the [WiFi.h](https://github.com/arduino-libraries/WiFi/tree/master) and [PubSubClient.h](https://github.com/knolleary/pubsubclient) libraries.<br>
<br>

<!-- Wiring Diagram -->
## Wiring Diagram
The Wiring Diagram below shows the pin layout of the project, as well as the used components.
<div align="center">
  <img width="700" src="https://github.com/DaanF1/Door_Alarm_System/blob/main/Images/Schematic_Door_Alarm_System.png"/>
</div>

<!-- Divider -->
___
<!-- MQTT Protocol -->
# MQTT Protocol
The project makes use of the MQTT (Message Queuing Telemetry Transport) protocol. The client subscribes to the broker, which acts like a middleman that transfers data to various topics. The client can control to which topics it subscribes. These topics can also send their data back to the client via the broker.
<div align="center">
  <img width="700" src="https://github.com/DaanF1/Door_Alarm_System/blob/main/Images/MQTT_Architecture.png"/>
</div>

<!-- Topics -->
## Topics
There are 2 topics for the project: doorOpened and alarm. Both of these topics can only be either 1 or 0 (true or false). The doorOpened topic is set to 1 if a door is opened via a single button press, and set to 0 when both buttons are pressed. The alarm topic is set to 1 if the alarm should soon be activated. This flickers the yellow LED first. After roughly 10 seconds the yellow LED will stop flickering and the red LED wil start flickering. The buzzer will then also start beeping an alarm sound.

<!-- Viewing The Protocol -->
## Viewing The Protocol
It is possible to view the data being transfered in real-time. For this you could use a tool like [MQTT Explorer](https://mqtt-explorer.com/). Just make sure to connect to the same broker as the program, and add the topics (see below).
<div align="center">
  <img width="700" src="https://github.com/DaanF1/Door_Alarm_System/blob/main/Images/MQTT_Explorer_Broker%20_Settings.png"/>
  <img width="700" src="https://github.com/DaanF1/Door_Alarm_System/blob/main/Images/MQTT_Explorer_Broker_Topics.png"/>
</div>

<!-- Back To Top -->
<p align="right"><a href="#readme-top">Back To Top</a></p>
