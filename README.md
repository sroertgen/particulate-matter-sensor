# DIY-Feinstaubsensor mit Live-Monitorung

This project is adapted from the [luftdaten.info project](https://luftdaten.info). It uses the same hardware, just the code is rewritten, so that the sensor measures data every second insetad of every three minutes and we send the data to our own database.

Purpose of this project.

You will find here informations on how to set up the microcontroller based on the NodeMCU (ESP8266). Besides you will find informations on how to setup your own small database and grafana server with a RaspberryPi. This way you can send the data from the microcontroller to the RaspberryPi and display it easily.

## Parts and Costs

## Wiring of NodeMCU

This wiring uses the defualt wiring of the [luftdaten.info project](https://luftdaten.info/feinstaubsensor-bauen/).

DHT22:

- "+" of DHT22 to 3V of microcontroller
- "-" of DHT22 to GND of microcontroller
- "OUT" of DHT22 to D7 of microcontroller

SDS:

- "+" to 5V of microcontroller
- "-" to GND of microcontroller
- "TXDPIN" of SDS sensor to D1 of microcontroller
- "RXDPIN" of SDS sensor to D2 of microcontroller

## Drivers for NodeMCU Lua Amica Module

If you bought this [NodeMCU Moudle](https://www.amazon.de/gp/product/B07F5FJSYZ/ref=ppx_yo_dt_b_asin_title_o00_s00?ie=UTF8&psc=1) you might have to download the correct [CP2102 driver](https://www.silabs.com/products/development-tools/software/interface#drivers) so that your computer finds the microcontroller.

## Setup of RaspberryPi

### Setup InfluxDB and Grafana with Ansible

This setup assumes you have a basic ... installation.

## Upload code to your NodeMCU

## Links and further information

- [Warum ist Feinstaub so gefähtlich? - Ein Bericht von Quarks.de](https://www.quarks.de/gesundheit/warum-feinstaub-so-gefaehrlich-ist/)
- [Was taugt der Feinstaubsensor SDS011](https://www.thethingsnetwork.org/community/berlin/post/was-taugen-feinstaubsensoren-aus-dem-land-des-lachelns-im-ttn-iot-lorawan-netz)

