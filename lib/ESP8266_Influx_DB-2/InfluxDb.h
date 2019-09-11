
/**
    ESP8266 InfluxDb: Influxdb.h

    Purpose: Helps with sending measurements to an Influx database.

    @author Tobias Schürg
*/
#if defined(ESP8266)
#include <ESP8266HTTPClient.h>
#elif defined(ESP32)
#include <WiFi.h>
#include <HTTPClient.h>
#endif

#include <list>
#include "Arduino.h"

#include "InfluxData.h"

class Influxdb {
 public:
  Influxdb(String host, uint16_t port = 8086);

  void setDb(String db);
  void setDbAuth(String db, String user, String pass);

  void setVersion(uint16_t version);
  void setBucket(String bucket);
  void setOrg(String org);
  void setToken(String token);
  void setPort(uint16_t port);

  void prepare(InfluxData data);
  boolean write();

  boolean write(InfluxData data);
  boolean write(String data);

 private:
  HTTPClient http;
  String _host;
  uint16_t _port;
  String _db;
  String _user;
  String _pass;
  String _bucket;
  String _org;
  String _token;
  uint16_t _db_v;

  std::list<InfluxData> prepared;
  
  void begin();
};
