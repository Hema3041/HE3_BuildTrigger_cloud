#ifndef __HOAGS_AWSIOT_H__
#define __HOAGS_AWSIOT_H__

/* Standard includes. */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "MQTTClient.h"
#include "wifi_conf.h"
#include "lwip_netconf.h"

#include "hoags_config.h"
#include "queue.h"

#define MQTT_SELECT_TIMEOUT 1

#if ENABLE_AWSIOT_DATA_ANALYTICS
#define AWSIOT_DATA_ANALYTIC_TOPIC  "hoagsDataAnalytic"
#endif

#if ENABLE_AWSIOT_UI_CONTROLS
#define AWSIOT_UI_CONTROL_TOPIC     "hoagsUIControl"
#define AWSIOT_UI_CONTROL_ACK_TOPIC     "hoagsUIControlAck"
#endif

#define REGISTER_TOPIC        "hoags/register"
#define ANALYTIC_TOPIC        "hoags/analytics"

#define AWS_IOT_CORE_ENDPOINT   "a198fgj6igmrrt-ats.iot.ap-south-1.amazonaws.com"
#define AWS_IOT_CORE_MQTT_PORT  8883
#define HOAGS_MQTT_VERSION  3
#define HOAGS_MQTT_MAX_MESSAGE_LENGTH   512
#define HOAGS_CLIENT_ID         "IamHoags"

#define TMP_JSON_FILE   "lastAnalTmp.json"
#define JSON_FILE   "lastAnal.json"


#define AWS_IOT_ROOT_CA \
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


#define AWS_IOT_CLIENT_CA \
"-----BEGIN CERTIFICATE-----\n" \
"MIIDWTCCAkGgAwIBAgIUQ4muUL5E7pltNihgyJE2tNgiC8AwDQYJKoZIhvcNAQEL\n" \
"BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g\n" \
"SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTI0MDIxMjA4MDI1\n" \
"MVoXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0\n" \
"ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAMeDzeZjv+SWRVpDGBlZ\n" \
"F8DCouctChIieekJ3fPVrCXjDDWPF8TpzvutK5MmC4vb4NY2RY7PSNMOBjGXgOpW\n" \
"rC5gyvvqA9NrA25REjZKL1KcCrWLS0G0YDRdwO3XY/VUc11VoJx+v7IEcwfuWQPZ\n" \
"dFrYJoDgTDXJJQ4deaaOxf1IC+jadZPG8aEI8NDhJGMGzLFDzJLh29yOp1Jv2a39\n" \
"R9ftHGQ7VdeD3vb/8U3NniySSUhOJ7zhq27KMiLjXcmHGHCwlBec1bcXrmjYrXb5\n" \
"PwsZcHnpunh0ng+GjjMdo9kHgvt1yuwLwzpidJ4nkaSaExIgWCV86f/8r2704txE\n" \
"Pe8CAwEAAaNgMF4wHwYDVR0jBBgwFoAUoaMrp0IGpE8+Zh7J/8Y2s/Swi9MwHQYD\n" \
"VR0OBBYEFFYSBM1Cb1JFnu9NuUIh3lhuRGu0MAwGA1UdEwEB/wQCMAAwDgYDVR0P\n" \
"AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQDDcGuInp3Ruqh+p3KufYZR/8vS\n" \
"GzJ99jH43Gr5YUdJirAOnkiV+UIBvfjK+gjDsV5f0kX30YQXdQ6TaaHbeTjFqspT\n" \
"VvsrFIDiok/iPMy63sGDpsdEslkdVzjoTNj2jTx88WwsSU2hH2kfJbdFZGo/wT+d\n" \
"UYig3feMTbtngLI4dTb+BlrjQyCN8w82qrYrXjb34omAYuRabPljOC+Yxf682HBd\n" \
"TYNKyxMF1b3EyeBPBHTt/EIfbVcQEcLNg9UEsDH/NpsD/BySXCcXEybEAmXyPID+\n" \
"oKwJHlfvEZjFigTqNNXIl/MKnj1okuUNv/xUtbS6zqJS9rWkyj8/jzFNPKSu\n" \
"-----END CERTIFICATE-----\n" 

#define AWS_IOT_PRIVATE_KEY \
"-----BEGIN RSA PRIVATE KEY-----\n" \
"MIIEpQIBAAKCAQEAx4PN5mO/5JZFWkMYGVkXwMKi5y0KEiJ56Qnd89WsJeMMNY8X\n" \
"xOnO+60rkyYLi9vg1jZFjs9I0w4GMZeA6lasLmDK++oD02sDblESNkovUpwKtYtL\n" \
"QbRgNF3A7ddj9VRzXVWgnH6/sgRzB+5ZA9l0WtgmgOBMNcklDh15po7F/UgL6Np1\n" \
"k8bxoQjw0OEkYwbMsUPMkuHb3I6nUm/Zrf1H1+0cZDtV14Pe9v/xTc2eLJJJSE4n\n" \
"vOGrbsoyIuNdyYcYcLCUF5zVtxeuaNitdvk/Cxlweem6eHSeD4aOMx2j2QeC+3XK\n" \
"7AvDOmJ0nieRpJoTEiBYJXzp//yvbvTi3EQ97wIDAQABAoIBAQCwR9u38XCOFtvm\n" \
"GZwEYXykOxTWLyxTw5R1e9tY4vT8cLTL6cd1m6PfKS10EUxoYXkxq7gfqzRMDnsY\n" \
"fCVSaAwv2iPfGvAQb+ATK5xszXUsh2TK7O0se6P5ANFDFGlkTR61W7/SJgdX0aiV\n" \
"XFnYFd1BmvPCMOwFJdkQtKhUqpdy5hKNFtw60JURH5yAX6Tdb6TEMQwOTiiBDXhc\n" \
"WKqSehMNa0eo2Yb6CGxBbWbnZ5TVcTVwlK9xdr7N+X29p1QagiZUukwULvJk7IJ8\n" \
"SQIaKVBM8heNWLsnnwS+y1jfyV0Cts7BS7/9MdPHwiYCyFNEsM8iPatZTFu+VLQe\n" \
"VN2UvyZZAoGBAO1szDt9dq+9NrBZzu95aS47/lH7gUQB/ADuAMA2nH7Iu2GN4nfE\n" \
"fbeK92rZz9U2Ry7F4S/+a+CX2GPkO/CRGojHzTrASxDXj1lMrR0IA4XUEngz45dU\n" \
"iZAhymGTGzN0OaiIrNlbwf6VorVpPkexS2vm25aLhJrrsrrfL3YiMTzdAoGBANcf\n" \
"u9SnAqfODtbeaGFkaX+eIIN1Vr1SNeh5beo9fZhNUA/sh/PHdBqVf+ww17AaPZkK\n" \
"WGsuUyFXw2q/rDl7VLS7CuDZHK2/T/5QEijCafRyYwATILW7PZbOAUABmlH1goIK\n" \
"XeDO4urUcYWqz1iUXXyBfQvzO2A1LMvuoQST7SM7AoGAGHUPqMUo17uXCZ2GupZ4\n" \
"JkIZ1Zoh276UlgfuXd6CSnElFEyIWqwMAz82c3RSe3Um6gOKSeZceHtL2CZnokVg\n" \
"RVzHoFi0otyBsMI8RvRPYJbS/DzkIe+caBODBIAh2jALzHefzpgsKKyDYUqhFsOF\n" \
"sGzMi/p9Q3QqKiPZgMLO7aUCgYEAydb6cxGoCi3p+mx+3zJJUfXZZ75GfieOcOrN\n" \
"2EONfcK8ZdR10qLHKtIuTjudg5t7RAZS4215jgU8UwI34072MQR1tnW+1L51nZUf\n" \
"FKMkqrhQbxeDTz+5D6+FuLpIQrHpm32Ci5VRjyd4xAN5vBCojlMoMngqs5/wwf7J\n" \
"kPQCQVUCgYEAuUBZ7ien5YKb5Bur/usx/qhwjDzm0V+iAK52OvR+K5VTN8Ea2OZP\n" \
"CqE3ena8E52r+NMFlxaXPu2ibCU165VW3buvVFu8QJ51nculjYNr9W8XD+yj44iK\n" \
"DPlwAmRz0ujusrSdiNjxiXWuzQz8idCKGk9QmWdzuvgx8Tm4arOET2A=\n" \
"-----END RSA PRIVATE KEY-----\n"

#define PUB_SUB_UNIT_SIZE     128

enum mqttType
{
    MT_NONE,
    MT_REGISTER,
    MT_POWERUSAGE,
    MT_FILTERCHANGE,
    MT_PING,
    MT_ANALYTICS,
    MT_UIACK,
    MT_GASLEAK,

    
};

struct hoagsMqtt
{
    enum mqttType id;
    char* data;

};

#endif
