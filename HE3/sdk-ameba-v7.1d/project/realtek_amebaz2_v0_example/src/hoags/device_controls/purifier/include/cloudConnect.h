#ifndef CLOUD_CONNECT_H
#define CLOUD_CONNECT_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "hoags_config.h"
#include <lwip_netconf.h>
#include "objects.h"
#include "netif.h"
#include "remoteDiag.h"
#include "MQTTClient.h"
#include <semphr.h>
#include "ota_h3.h"
#include "wifi_constants.h"
#include "sockets.h"
#include "wifi_conf.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"


#define PACKET_SIZE 100
#define VERISON_SIZE 20
#define PING_INTERVAL_SECONDS 300

#define MARKER "5a5a"
#define TCP_SERVER_MARKER "9a9a"

#define IOT_ENDPOINT "a1mt9okht7d0e8-ats.iot.ap-south-1.amazonaws.com"
#define IOT_PORT_NUMBER 8883
#define CLIENT_ID "Lotier:"
#define LOTIER_TOPIC "/hoags/livpure/lotier"
#define HOAGS_MQTT_VERSION  3

#define TIME_SET_FOR_REGISTRATION_CHECK 1 //time in minutes

//#define MODEL_NO "LVPR0010001PURDX"
#define MODEL_NO_SIZE 30

typedef enum {
    REG_TAG = 1,
    RD_RES_TAG,
    PING_MSG_TAG,
}MSG_TYPE_TAGS;

typedef enum {
    DEV_TAG = 1,
    MACID_TAG,
    VERSION_TAG,
    RD_RSP_TAG,
}DATA_TYPE_TAGS;

#define CUST_NAME_TAG "0004"
#define PROD_TYPE_TAG "0005"
#define USER_ID_TAG "0006"
#define FRIENDLY_NAME_TAG "0007"

int sendDataToCloud(char data[]);
void string_to_hex(char *hex_output,const  char *input);
void makeDataPacket(unsigned char packet[], const int msgType, const char *msgData);


#define IOT_ROOT_CA \
"-----BEGIN CERTIFICATE-----\n" \
"MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF\n" \
"ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6\n" \
"b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL\n" \
"MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv\n" \
"b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj\n" \
"ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM\n" \
"9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw\n" \
"IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6\n" \
"VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L\n" \
"93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm\n" \
"jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC\n" \
"AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA\n" \
"A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI\n" \
"U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs\n" \
"N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv\n" \
"o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU\n" \
"5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy\n" \
"rqXRfboQnoZsG4q5WTP468SQvvG5\n" \
"-----END CERTIFICATE-----\n"


#define IOT_CLIENT_CA \
"-----BEGIN CERTIFICATE-----\n" \
"MIIDWTCCAkGgAwIBAgIUBx6q12BgVoa93KxYGW0MQ9FKE38wDQYJKoZIhvcNAQEL\n" \
"BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g\n" \
"SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTI1MDMxMTEzNTAy\n" \
"MVoXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0\n" \
"ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBANHhvTmD4Rmf2vIrbM+P\n" \
"3hgZBMUPVQWYRIcshsD/MUzduEKMJ7CbX2fpP9mx77PmctRWWxjSXZcASJ4iE87B\n" \
"p6FPbGA7Te7qKnbkgi7n/BC3/JUHtOkTZV3mZzZXTz0PBlZc+QO+7ynLmfI20eur\n" \
"zmmTdPtM8qTjHH1XM1oH+CtWhzMo4em0V/ZHKGxhngxdGE3KX+/cPbUXgfw9eILo\n" \
"QqVQn0YvGREAUpyTimYWTwoVOcbfjRZ4EdtNSjuFbUJu8ELSBQ7nMariwqccMTSm\n" \
"3FLsQiTce3m+KBT6Z7K1wXMZrXRtM0UvQGoiJOOm5VAggGvTMnYFPC9Fl9j1lfID\n" \
"mLECAwEAAaNgMF4wHwYDVR0jBBgwFoAU2cjIdSG4TQVFaErZjUhQCiM/WsswHQYD\n" \
"VR0OBBYEFDv4F54fL7AuUg7KrsS7/PCu6vMIMAwGA1UdEwEB/wQCMAAwDgYDVR0P\n" \
"AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQCpLRSn6cesmSIUOYW0ALMnpgKr\n" \
"gCBvA7IyIQvqUXYuhiqy/k8EHiquiDRV/IPlKVhGSWdtvO8TMBELcbXKkDxLplRG\n" \
"8IOY4BJB85CnjP9LagICKmHCtRwZ+kXUxWJzoUszchoWMD49MR6VkAZo0VCYPwpY\n" \
"GNnN+fvOzFyXZTVEbscxLci2rq8vcsFw8PwKjHP8yTM2hkGhOTyPs/rJKxFQ25iE\n" \
"jKN0rn+xC1/PbVL7hwIBeCzxxIq8y/CDt+SiqnwdOFpxdTorVEUjtrvBMWkncLpS\n" \
"eywyIqyEfMpgWu+GXPR3ekw4f0C5lrm8WIqFNljr6A4a7jxP5qLGOkT8V1o9\n" \
"-----END CERTIFICATE-----\n" 

#define IOT_PRIVATE_KEY \
"-----BEGIN RSA PRIVATE KEY-----\n" \
"MIIEpAIBAAKCAQEA0eG9OYPhGZ/a8itsz4/eGBkExQ9VBZhEhyyGwP8xTN24Qown\n" \
"sJtfZ+k/2bHvs+Zy1FZbGNJdlwBIniITzsGnoU9sYDtN7uoqduSCLuf8ELf8lQe0\n" \
"6RNlXeZnNldPPQ8GVlz5A77vKcuZ8jbR66vOaZN0+0zypOMcfVczWgf4K1aHMyjh\n" \
"6bRX9kcobGGeDF0YTcpf79w9tReB/D14guhCpVCfRi8ZEQBSnJOKZhZPChU5xt+N\n" \
"FngR201KO4VtQm7wQtIFDucxquLCpxwxNKbcUuxCJNx7eb4oFPpnsrXBcxmtdG0z\n" \
"RS9AaiIk46blUCCAa9MydgU8L0WX2PWV8gOYsQIDAQABAoIBAQCQ2uxutca2mM3U\n" \
"NoRy/SicGShhmaNkqSMi6GhY68hq9NwnkfQSwCmo3iNjbJuz3mmCg9d72jUd8uQr\n" \
"v/lLyfyYKOjzwfqX2qZUSIJRPWuLXnDFqvwBoZFkrZCuwLO/wI7vLFvxaeZHQm6N\n" \
"7agUsA9Wbp9ekk0l4FnZaEXY7Ycq4N2XIZ9633lDS6ZscyqKQ/H0vlwM4r2Mct+4\n" \
"xzmEDXFMBWnv2VVoXnGZp9hfYaXrYe5jRaNatQTL8Hf2LZ532Z7fstoeDsMwMavb\n" \
"x5SiWuZp9neosQKwdsZrCkKWdBLatNov+ETrOA0UfKVUanwLRCkADUhCr9GSSPyb\n" \
"pUURWSABAoGBAOjplg4PP8fDW/zOk7f34GvREoOgwj65ZcT7aHbXmdyfX5KlqHlJ\n" \
"8KBw00CJm4dr4fQcxbLNEH22eKimOhd/frxeaDQGx3TA2LPpD5MuWocMkzHh+kRz\n" \
"4SDyIl815IFxsDA9FfePXMkrwZZBh4uQUtlu8RTMvhQZQ4s7SsUQmjfhAoGBAOav\n" \
"uXUPzGDp0AoQqi4tN5n291Xcdx5R5o3CCbJekQRZ2TMVUuMkIWNutWkP27wLLzt+\n" \
"KKqP5lvnUE7HKKBB8RH4x03+NAPqX77L4oG3EJuEquqYUZ/Jf/0S/iued13OHTa8\n" \
"n9S6o4LathOQAy9tZZR9ng/Oc1LQ8e/LBl0F0zrRAoGAZ9+lGGgcnc62u6y1nJpj\n" \
"8DGx/Bo6BxdQF+W31SiaahZ53UEcPduIAUXQMTwtrNukTeZ3FSL3c9lpPm3EAq7N\n" \
"qty/xFQxqBRJkRMj6xQFM62cB+csYlL72GGkiqnSWxiE5z6XCW1aiC2HjKd09/1J\n" \
"tccQpaIaM4SA5xtuYSziWoECgYEAzJqJJCG6BS77/SFgv4oNabqZDwd2g2bi1VKH\n" \
"pTOo7bH/Kga8uIegMX/M2P1eyD8nSl4QFY+CIntcSDLufo1eErGTnEJdwidLen99\n" \
"S82hpj4aFe65Xr6qjT0eQHPRrVqVoKnWHSjYw8PWgC1YFeWyleyAl8ZllMuL+kIZ\n" \
"R8JV4jECgYAsgh8mRT4RJ/IOkuLxRt7BxKWTv6QS1r66kTHAlxrvZtgo/RJxB8Q0\n" \
"Ym6nL0UkHGy5RIXToD0nQBMIQU54QMeN78hmhjTMk8L1lzy4eU1XqOMCEk3Lh9op\n" \
"JAy3wpmcnhqxLuRXS6lsLAhymYeiQLz6HSMW9m/zWpkbv9lcLARX2w==\n" \
"-----END RSA PRIVATE KEY-----\n"

#endif // CLOUD_CONNECT_H
