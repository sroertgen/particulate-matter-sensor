# TODOs

Noch zu erledigen:

- [ ] Übersetzen
- [ ] Bebildern
- [ ] Setup of virtualenv einfügen
- [ ] Hintergrund-Informationen über Feinstaub und möglichen Ablauf eines Workshops/Projektes anfügen

## DIY-Feinstaubsensor mit Live-Monitorung

This project is adapted from the [luftdaten.info project](https://luftdaten.info). It uses the same hardware, just the code is rewritten, so that the sensor measures data every second instead of every three minutes and we send the data to our own database.

The purpose of this project is to raise awareness to themes like environment protection/pollution, particulate matter and IoT (Internet of Things).

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

This setup assumes you have a basic Debian installation, e.g. on your RaspberryPi or some other machine. Open the folder `database-setup` and edit the file `host_vars/db_server.yml` Fill in the IP address of the server, the username and the password. The user must have sudo-rights.

Create a virtual environment.

Make sure you are in the folder `database-setup`.

Then run `ansible-playbook playbook.yml`. This will set up an InfluxDB and a Grafana instance on the given server.

## Upload code to your NodeMCU

Open VisualStudio Code.

Make sure the Extension "PlattformIO" is installed.

Now we have to make sure that your sensor will send data to the correct server. Open the file `src/main.cpp` and set the correct IP-address of your server at `#define INFLUXDB_HOST`.

Plug in your NodeMCU module.

Open PlattformIO/Devices and make sure to get the USB port your module is plugged into.

Copy the path.

Open the file `sensor/plattformio.ini` and paste the copied path to `upload_port`.

Now click the Upload-Button to upload the code on your NodeMCU.

## Links and further information

- [Warum ist Feinstaub so gefähtlich? - Ein Bericht von Quarks.de](https://www.quarks.de/gesundheit/warum-feinstaub-so-gefaehrlich-ist/)
- [Was taugt der Feinstaubsensor SDS011](https://www.thethingsnetwork.org/community/berlin/post/was-taugen-feinstaubsensoren-aus-dem-land-des-lachelns-im-ttn-iot-lorawan-netz)
