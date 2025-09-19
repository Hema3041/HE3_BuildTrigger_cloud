/*******************************************************************************
 * Copyright (c) 2014, 2015 IBM Corp.
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * and Eclipse Distribution License v1.0 which accompany this distribution.
 *
 * The Eclipse Public License is available at
 *    http://www.eclipse.org/legal/epl-v10.html
 * and the Eclipse Distribution License is available at
 *   http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * Contributors:
 *    Allan Stockdill-Mander - initial API and implementation and/or initial documentation
 *    Ian Craggs - convert to FreeRTOS
 *******************************************************************************/

#include "MQTTFreertos.h"
#include "netdb.h"
#include "hoags_config.h"


XIP_SEC_RODATA_SECTION const char AWS_IOT_ROOT_CA[] = \
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
"-----END CERTIFICATE-----\n";


XIP_SEC_RODATA_SECTION const char AWS_IOT_CLIENT_CA[]  = \
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
"-----END CERTIFICATE-----\n";

XIP_SEC_RODATA_SECTION const char AWS_IOT_PRIVATE_KEY[]  = \
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
"-----END RSA PRIVATE KEY-----\n";


#ifdef LWIP_IPV6
#undef LWIP_IPV6
#endif
#ifdef inet_ntop
#undef inet_ntop
#endif
#ifdef inet_pton
#undef inet_pton
#endif
#define LWIP_IPV6 0
#if LWIP_IPV6
#define inet_ntop(af,src,dst,size) \
    (((af) == AF_INET6) ? ip6addr_ntoa_r((src),(dst),(size)) \
     : (((af) == AF_INET) ? ipaddr_ntoa_r((src),(dst),(size)) : NULL))
#define inet_pton(af,src,dst) \
    (((af) == AF_INET6) ? inet6_aton((src),(dst)) \
     : (((af) == AF_INET) ? inet_aton((src),(dst)) : 0))
#else /* LWIP_IPV6 */
#define inet_ntop(af,src,dst,size) \
    (((af) == AF_INET) ? ipaddr_ntoa_r((src),(dst),(size)) : NULL)
#define inet_pton(af,src,dst) \
    (((af) == AF_INET) ? inet_aton((src),(dst)) : 0)
#endif /* LWIP_IPV6 */

int ThreadStart(Thread* thread, void (*fn)(void*), void* arg)
{
	int rc = 0;
	uint16_t usTaskStackSize = (configMINIMAL_STACK_SIZE * 5);
	UBaseType_t uxTaskPriority = uxTaskPriorityGet(NULL); /* set the priority as the same as the calling task*/

	rc = xTaskCreate(fn,	/* The function that implements the task. */
		"MQTTTask",			/* Just a text name for the task to aid debugging. */
		usTaskStackSize,	/* The stack size is defined in FreeRTOSIPConfig.h. */
		arg,				/* The task parameter, not used in this case. */
		uxTaskPriority,		/* The priority assigned to the task is defined in FreeRTOSConfig.h. */
		&thread->task);		/* The task handle is not used. */

	return rc;
}


void MutexInit(Mutex* mutex)
{
	mutex->sem = xSemaphoreCreateMutex();
}

int MutexLock(Mutex* mutex)
{
	return xSemaphoreTake(mutex->sem, portMAX_DELAY);
}

int MutexUnlock(Mutex* mutex)
{
	return xSemaphoreGive(mutex->sem);
}


void TimerCountdownMS(Timer* timer, unsigned int timeout_ms)
{
	timer->xTicksToWait = timeout_ms / portTICK_PERIOD_MS; /* convert milliseconds to ticks */
	vTaskSetTimeOutState(&timer->xTimeOut); /* Record the time at which this function was entered. */
}


void TimerCountdown(Timer* timer, unsigned int timeout) 
{
	TimerCountdownMS(timer, timeout * 1000);
}


int TimerLeftMS(Timer* timer) 
{
	xTaskCheckForTimeOut(&timer->xTimeOut, &timer->xTicksToWait); /* updates xTicksToWait to the number left */
	return (timer->xTicksToWait * portTICK_PERIOD_MS);
}


char TimerIsExpired(Timer* timer)
{
	return xTaskCheckForTimeOut(&timer->xTimeOut, &timer->xTicksToWait) == pdTRUE;
}


void TimerInit(Timer* timer)
{
	timer->xTicksToWait = 0;
	memset(&timer->xTimeOut, '\0', sizeof(timer->xTimeOut));
}

#if CONFIG_USE_POLARSSL

int FreeRTOS_read(Network* n, unsigned char* buffer, int len, int timeout_ms)
{
	TickType_t xTicksToWait = timeout_ms / portTICK_PERIOD_MS; /* convert milliseconds to ticks */
	TimeOut_t xTimeOut;
	int recvLen = 0;

	int so_error;
	socklen_t errlen = sizeof(so_error);

	vTaskSetTimeOutState(&xTimeOut); /* Record the time at which this function was entered. */
	do
	{
		int rc = 0;
#if defined(LWIP_SO_SNDRCVTIMEO_NONSTANDARD) && (LWIP_SO_SNDRCVTIMEO_NONSTANDARD == 0)
		// timeout format is changed in lwip 1.5.0
		struct timeval timeout;
		timeout.tv_sec  = xTicksToWait / 1000;
		timeout.tv_usec = ( xTicksToWait % 1000 ) * 1000;
		setsockopt(n->my_socket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(struct timeval)); 
#else
		setsockopt(n->my_socket, SOL_SOCKET, SO_RCVTIMEO, &xTicksToWait, sizeof(xTicksToWait)); 
#endif
#if (MQTT_OVER_SSL)
		if (n->use_ssl) {
			rc = ssl_read(n->ssl, buffer + recvLen, len - recvLen);

			getsockopt(n->my_socket, SOL_SOCKET, SO_ERROR, &so_error, &errlen);
			if (so_error && so_error != EAGAIN) {
				n->disconnect(n);
			}
		} else
#endif
		rc = recv(n->my_socket, buffer + recvLen, len - recvLen, 0);
		if (rc > 0)
			recvLen += rc;
		else if (rc < 0)
		{
			getsockopt(n->my_socket, SOL_SOCKET, SO_ERROR, &so_error, &errlen);
			if (so_error != EAGAIN) {
				n->disconnect(n);
			}
			recvLen = rc;
			break;
		}
	} while (recvLen < len && xTaskCheckForTimeOut(&xTimeOut, &xTicksToWait) == pdFALSE);

	return recvLen;
}

int FreeRTOS_write(Network* n, unsigned char* buffer, int len, int timeout_ms)
{
	TickType_t xTicksToWait = timeout_ms / portTICK_PERIOD_MS; /* convert milliseconds to ticks */
	TimeOut_t xTimeOut;
	int sentLen = 0;

	int so_error;
	socklen_t errlen = sizeof(so_error);

	vTaskSetTimeOutState(&xTimeOut); /* Record the time at which this function was entered. */
	do
	{
		int rc = 0;
#if defined(LWIP_SO_SNDRCVTIMEO_NONSTANDARD) && (LWIP_SO_SNDRCVTIMEO_NONSTANDARD == 0)
		// timeout format is changed in lwip 1.5.0
		struct timeval timeout;
		timeout.tv_sec  = xTicksToWait / 1000;
		timeout.tv_usec = ( xTicksToWait % 1000 ) * 1000;
		setsockopt(n->my_socket, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(struct timeval)); 
#else
		setsockopt(n->my_socket, SOL_SOCKET, SO_SNDTIMEO, &xTicksToWait, sizeof(xTicksToWait));
#endif
#if (MQTT_OVER_SSL)
		if (n->use_ssl) {
			rc = ssl_write(n->ssl, buffer + sentLen, len - sentLen);

			getsockopt(n->my_socket, SOL_SOCKET, SO_ERROR, &so_error, &errlen);
			if (so_error && so_error != EAGAIN) {
				n->disconnect(n);
			}
		} else
#endif
		rc = send(n->my_socket, buffer + sentLen, len - sentLen, 0);
		if (rc > 0)
			sentLen += rc;
		else if (rc < 0)
		{
			getsockopt(n->my_socket, SOL_SOCKET, SO_ERROR, &so_error, &len);
			if (so_error != EAGAIN) {
				n->disconnect(n);
			}
			sentLen = rc;
			break;
		}
	} while (sentLen < len && xTaskCheckForTimeOut(&xTimeOut, &xTicksToWait) == pdFALSE);

	return sentLen;
}


void FreeRTOS_disconnect(Network* n)
{
	shutdown(n->my_socket, SHUT_RDWR);
	close(n->my_socket);
	n->my_socket = -1;

#if (MQTT_OVER_SSL)
	if (n->use_ssl) {
		ssl_free(n->ssl);
		free(n->ssl);
		n->ssl = NULL;
	}
#endif
}

void NetworkInit(Network* n)
{
	n->my_socket = -1;
	n->mqttread = FreeRTOS_read;
	n->mqttwrite = FreeRTOS_write;
	n->disconnect = FreeRTOS_disconnect;

#if (MQTT_OVER_SSL)
	n->use_ssl = 1;
	n->ssl = NULL;
	n->conf = NULL;
	n->rootCA = AWS_IOT_ROOT_CA;
	n->clientCA = AWS_IOT_CLIENT_CA;
	n->private_key = AWS_IOT_PRIVATE_KEY;
	n->ciphersuites = NULL;
#endif
}


#if (MQTT_OVER_SSL)
static int mqtt_tls_verify( void *data, x509_crt *crt, int depth, int *flags ) 
{
	char buf[1024]; 

	mqtt_printf(MQTT_DEBUG, "\nVerify requested for (Depth %d):\n", depth ); 
	x509_crt_info( buf, sizeof( buf ) - 1, "", crt ); 
	mqtt_printf(MQTT_DEBUG, "%s", buf ); 

	if( ( (*flags) & BADCERT_EXPIRED ) != 0 ) 
		mqtt_printf(MQTT_DEBUG, "  ! server certificate has expired\n" ); 

	if( ( (*flags) & BADCERT_REVOKED ) != 0 ) 
		mqtt_printf(MQTT_DEBUG, "  ! server certificate has been revoked\n" ); 

	if( ( (*flags) & BADCERT_CN_MISMATCH ) != 0 ) 
		mqtt_printf(MQTT_DEBUG, "  ! CN mismatch\n" ); 

	if( ( (*flags) & BADCERT_NOT_TRUSTED ) != 0 ) 
		mqtt_printf(MQTT_DEBUG, "  ! self-signed or not signed by a trusted CA\n" ); 

	if( ( (*flags) & BADCRL_NOT_TRUSTED ) != 0 ) 
		mqtt_printf(MQTT_DEBUG, "  ! CRL not trusted\n" ); 

	if( ( (*flags) & BADCRL_EXPIRED ) != 0 ) 
		mqtt_printf(MQTT_DEBUG, "  ! CRL expired\n" ); 

	if( ( (*flags) & BADCERT_OTHER ) != 0 ) 
		mqtt_printf(MQTT_DEBUG, "  ! other (unknown) flag\n" ); 

	if ( ( *flags ) == 0 ) 
		mqtt_printf(MQTT_DEBUG, "  This certificate has no flags\n" ); 

	return( 0 ); 
}

static int my_random(void *p_rng, unsigned char *output, size_t output_len)
{
	rtw_get_random_bytes(output, output_len);
	return 0;
}
#endif // #if (MQTT_OVER_SSL)




#elif CONFIG_USE_MBEDTLS /* CONFIG_USE_POLARSSL */

int FreeRTOS_read(Network* n, unsigned char* buffer, int len, int timeout_ms)
{
	TickType_t xTicksToWait = timeout_ms / portTICK_PERIOD_MS; /* convert milliseconds to ticks */
	TimeOut_t xTimeOut;
	int recvLen = 0;

	int so_error;
	socklen_t errlen = sizeof(so_error);

	vTaskSetTimeOutState(&xTimeOut); /* Record the time at which this function was entered. */
	do
	{
		int rc = 0;
#if defined(LWIP_SO_SNDRCVTIMEO_NONSTANDARD) && (LWIP_SO_SNDRCVTIMEO_NONSTANDARD == 0)
		// timeout format is changed in lwip 1.5.0
		struct timeval timeout;
		timeout.tv_sec  = xTicksToWait / 1000;
		timeout.tv_usec = ( xTicksToWait % 1000 ) * 1000;
		setsockopt(n->my_socket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(struct timeval)); 
#else
		setsockopt(n->my_socket, SOL_SOCKET, SO_RCVTIMEO, &xTicksToWait, sizeof(xTicksToWait)); 
#endif
#if (MQTT_OVER_SSL)
		if (n->use_ssl) {
			rc = mbedtls_ssl_read(n->ssl, buffer + recvLen, len - recvLen);

			getsockopt(n->my_socket, SOL_SOCKET, SO_ERROR, &so_error, &errlen);
			if (so_error && so_error != EAGAIN) {
				n->disconnect(n);
			}
		} else
#endif
		rc = recv(n->my_socket, buffer + recvLen, len - recvLen, 0);
		if (rc > 0)
			recvLen += rc;
		else if (rc < 0)
		{
			getsockopt(n->my_socket, SOL_SOCKET, SO_ERROR, &so_error, &errlen);
			if (so_error != EAGAIN) {
				n->disconnect(n);
			}
			recvLen = rc;
			break;
		}
	} while (recvLen < len && xTaskCheckForTimeOut(&xTimeOut, &xTicksToWait) == pdFALSE);

	return recvLen;
}

int FreeRTOS_write(Network* n, unsigned char* buffer, int len, int timeout_ms)
{
	TickType_t xTicksToWait = timeout_ms / portTICK_PERIOD_MS; /* convert milliseconds to ticks */
	TimeOut_t xTimeOut;
	int sentLen = 0;

	int so_error;
	socklen_t errlen = sizeof(so_error);

	vTaskSetTimeOutState(&xTimeOut); /* Record the time at which this function was entered. */
	do
	{
		int rc = 0;
#if defined(LWIP_SO_SNDRCVTIMEO_NONSTANDARD) && (LWIP_SO_SNDRCVTIMEO_NONSTANDARD == 0)
		// timeout format is changed in lwip 1.5.0
		struct timeval timeout;
		timeout.tv_sec  = xTicksToWait / 1000;
		timeout.tv_usec = ( xTicksToWait % 1000 ) * 1000;
		setsockopt(n->my_socket, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(struct timeval)); 
#else
		setsockopt(n->my_socket, SOL_SOCKET, SO_SNDTIMEO, &xTicksToWait, sizeof(xTicksToWait));
#endif
#if (MQTT_OVER_SSL)
		if (n->use_ssl) {
			rc = mbedtls_ssl_write(n->ssl, buffer + sentLen, len - sentLen);

			getsockopt(n->my_socket, SOL_SOCKET, SO_ERROR, &so_error, &errlen);
			if (so_error && so_error != EAGAIN) {
				n->disconnect(n);
			}
		} else
#endif
		rc = send(n->my_socket, buffer + sentLen, len - sentLen, 0);
		if (rc > 0)
			sentLen += rc;
		else if (rc < 0)
		{
			getsockopt(n->my_socket, SOL_SOCKET, SO_ERROR, &so_error, (socklen_t *)&len);
			if (so_error != EAGAIN) {
				n->disconnect(n);
			}
			sentLen = rc;
			break;
		}
	} while (sentLen < len && xTaskCheckForTimeOut(&xTimeOut, &xTicksToWait) == pdFALSE);

	return sentLen;
}


void FreeRTOS_disconnect(Network* n)
{
	shutdown(n->my_socket, SHUT_RDWR);
	close(n->my_socket);
	n->my_socket = -1;

#if (MQTT_OVER_SSL)
	if (n->use_ssl) {
		mbedtls_ssl_free(n->ssl);
		mbedtls_ssl_config_free(n->conf);
		free(n->ssl);
		free(n->conf);
		n->ssl = NULL;
		n->conf = NULL;
	}
#endif
}

void NetworkInit(Network* n)
{
	n->my_socket = -1;
	n->mqttread = FreeRTOS_read;
	n->mqttwrite = FreeRTOS_write;
	n->disconnect = FreeRTOS_disconnect;

#if (MQTT_OVER_SSL)
	n->use_ssl = 1;
	n->ssl = NULL;
	n->conf = NULL;
	n->rootCA = AWS_IOT_ROOT_CA;
	n->clientCA = AWS_IOT_CLIENT_CA;
	n->private_key = AWS_IOT_PRIVATE_KEY;
	n->ciphersuites = NULL;

#endif
}


#if (MQTT_OVER_SSL)
static int mqtt_tls_verify( void *data, mbedtls_x509_crt *crt, int depth, int *flags ) 
{ 
	char buf[1024]; 

	mqtt_printf(MQTT_DEBUG, "\nVerify requested for (Depth %d):\n", depth ); 
	mbedtls_x509_crt_info( buf, sizeof( buf ) - 1, "", crt ); 
	mqtt_printf(MQTT_DEBUG, "%s", buf ); 

	if( ( (*flags) & MBEDTLS_X509_BADCERT_EXPIRED ) != 0 ) 
		mqtt_printf(MQTT_DEBUG, "  ! server certificate has expired\n" ); 

	if( ( (*flags) & MBEDTLS_X509_BADCERT_REVOKED ) != 0 ) 
		mqtt_printf(MQTT_DEBUG, "  ! server certificate has been revoked\n" ); 

	if( ( (*flags) & MBEDTLS_X509_BADCERT_CN_MISMATCH ) != 0 ) 
		mqtt_printf(MQTT_DEBUG, "  ! CN mismatch\n" ); 

	if( ( (*flags) & MBEDTLS_X509_BADCERT_NOT_TRUSTED ) != 0 ) 
		mqtt_printf(MQTT_DEBUG, "  ! self-signed or not signed by a trusted CA\n" ); 

	if( ( (*flags) & MBEDTLS_X509_BADCRL_NOT_TRUSTED ) != 0 ) 
		mqtt_printf(MQTT_DEBUG, "  ! CRL not trusted\n" ); 

	if( ( (*flags) & MBEDTLS_X509_BADCRL_EXPIRED ) != 0 ) 
		mqtt_printf(MQTT_DEBUG, "  ! CRL expired\n" ); 

	if( ( (*flags) & MBEDTLS_X509_BADCERT_OTHER ) != 0 ) 
		mqtt_printf(MQTT_DEBUG, "  ! other (unknown) flag\n" ); 

	if ( ( *flags ) == 0 ) 
		mqtt_printf(MQTT_DEBUG, "  This certificate has no flags\n" ); 

	return( 0 ); 
}

static void* my_calloc(size_t nelements, size_t elementSize)
{
	size_t size;
	void *ptr = NULL;

	size = nelements * elementSize;
	ptr = pvPortMalloc(size);

	if(ptr)
		memset(ptr, 0, size);

	return ptr;
}

static int my_random(void *p_rng, unsigned char *output, size_t output_len)
{
	rtw_get_random_bytes(output, output_len);
	return 0;
}
#endif // #if (MQTT_OVER_SSL)


int NetworkConnect(Network* n, char* addr, int port)
{
	struct sockaddr_in sAddr;
	int retVal = -1;
	struct hostent *hptr;
	char   **pptr;
	char   str[32];
	int	keepalive_enable = 1;
	int keep_idle = 30;
	if(n->my_socket >= 0){
		n->disconnect(n);
	}
	if ((hptr = gethostbyname(addr)) == 0)
	{
		mqtt_printf(MQTT_DEBUG, "gethostbyname failed!");
		goto exit;
	}
	pptr = hptr->h_addr_list;
	for(; *pptr!=NULL; pptr++)
	{
		inet_ntop(hptr->h_addrtype, (const ip_addr_t *)*pptr, str, sizeof(str));
	}
	inet_ntop(hptr->h_addrtype, (const ip_addr_t *)hptr->h_addr, str, sizeof(str));
	sAddr.sin_family = AF_INET;
	sAddr.sin_port = htons(port);
	sAddr.sin_addr.s_addr = inet_addr(str);
	mqtt_printf(MQTT_DEBUG, "addr = %s", str);
	if ((n->my_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
	{
		goto exit;
	}
	setsockopt( n->my_socket, SOL_SOCKET, SO_KEEPALIVE,
			(const char *) &keepalive_enable, sizeof( keepalive_enable ) );	
	setsockopt( n->my_socket, IPPROTO_TCP, TCP_KEEPIDLE,
			(const char *) &keep_idle, sizeof( keep_idle ) );	
	if ((retVal = connect(n->my_socket, (struct sockaddr*)&sAddr, sizeof(sAddr))) < 0)
	{
		close(n->my_socket);
		n->my_socket = -1; //shaik:
		mqtt_printf(MQTT_DEBUG, "Connect failed!!");
		goto exit;
	}
#if (MQTT_OVER_SSL)
	mbedtls_x509_crt *root_crt;
	mbedtls_x509_crt *client_crt;
	mbedtls_pk_context *client_rsa;

	root_crt = NULL;
	client_crt = NULL;
	client_rsa = NULL;
	if ( n->use_ssl != 0 ) {

		mbedtls_platform_set_calloc_free(my_calloc, vPortFree);

		n->ssl = (mbedtls_ssl_context *) hoagsMalloc( sizeof(mbedtls_ssl_context) );
		n->conf = (mbedtls_ssl_config *) hoagsMalloc( sizeof(mbedtls_ssl_config) );
        if(n->conf != NULL)
		{
			printf("*****For n->conf memory allocated*******\n");  
		}      
		if (( n->ssl == NULL )||( n->conf == NULL )) {
			mqtt_printf(MQTT_DEBUG, "malloc ssl failed!");
			goto err;
		}

		mbedtls_ssl_init(n->ssl);
		mbedtls_ssl_config_init(n->conf);

		if((mbedtls_ssl_config_defaults(n->conf,
				MBEDTLS_SSL_IS_CLIENT,
				MBEDTLS_SSL_TRANSPORT_STREAM,
				MBEDTLS_SSL_PRESET_DEFAULT)) != 0) {
			mqtt_printf(MQTT_DEBUG, "ssl config defaults failed!");
			goto err;
		}

        if (n->ciphersuites) {
			mbedtls_ssl_conf_ciphersuites(n->conf, n->ciphersuites);
		}

		//mbedtls_ssl_conf_own_cert(n->conf, client_crt, client_rsa);
		mbedtls_ssl_set_bio(n->ssl, &n->my_socket, mbedtls_net_send, mbedtls_net_recv, NULL);
		mbedtls_ssl_conf_rng(n->conf, my_random, NULL);	

		if((mbedtls_ssl_setup(n->ssl, n->conf)) != 0) {
			mqtt_printf(MQTT_DEBUG,"mbedtls_ssl_setup failed!");
			goto err;
		}

		if (n->rootCA != NULL) {
			root_crt = (mbedtls_x509_crt *) hoagsMalloc( sizeof(mbedtls_x509_crt), 1);
			if ( root_crt == NULL ) {
				mqtt_printf(MQTT_DEBUG, "malloc root_crt failed!");
				goto err;
			}
	
			
			mbedtls_x509_crt_init(root_crt);
			
			if (mbedtls_x509_crt_parse( root_crt, (const unsigned char *)n->rootCA, strlen(n->rootCA)+1 ) != 0) {
				mqtt_printf(MQTT_DEBUG, "parse root_crt failed!");
				goto err;
			}
	
 			mbedtls_ssl_conf_ca_chain( n->conf, root_crt, NULL);
			mbedtls_ssl_conf_authmode(n->conf, MBEDTLS_SSL_VERIFY_REQUIRED);
			mbedtls_ssl_conf_verify( n->conf, (int (*)(void *, mbedtls_x509_crt *, int, uint32_t *))mqtt_tls_verify, NULL );
			mqtt_printf(MQTT_DEBUG, "root_crt parse done");
		} else {
			mbedtls_ssl_conf_authmode(n->conf, MBEDTLS_SSL_VERIFY_NONE);
		}

		if (n->clientCA != NULL && n->private_key != NULL) {
	
			client_crt = (mbedtls_x509_crt *) hoagsMalloc( sizeof(mbedtls_x509_crt), 1);
			if ( client_crt == NULL ) {
				mqtt_printf(MQTT_DEBUG, "malloc client_crt failed!");
				goto err;
			}
	
			mbedtls_x509_crt_init(client_crt);
	
			client_rsa = (mbedtls_pk_context *) hoagsMalloc( sizeof(mbedtls_pk_context), 1);
			if ( client_rsa == NULL ) {
				mqtt_printf(MQTT_DEBUG, "malloc client_rsa failed!");
				goto err;
			}
	
			mbedtls_pk_init(client_rsa);
	
			if ( mbedtls_x509_crt_parse(client_crt, (const unsigned char *)n->clientCA, strlen(n->clientCA)+1) != 0 ) {
				mqtt_printf(MQTT_DEBUG, "parse client_crt failed!");
				goto err;
			}
	
#if defined(MBEDTLS_VERSION_NUMBER) && (MBEDTLS_VERSION_NUMBER == 0x03000000)
			if (mbedtls_pk_parse_key(client_rsa, (const unsigned char *)n->private_key, strlen(n->private_key) + 1, NULL, 0, NULL, NULL) != 0) {
#else
			if (mbedtls_pk_parse_key(client_rsa, (const unsigned char *)n->private_key, strlen(n->private_key) + 1, NULL, 0) != 0) {
#endif			
				mqtt_printf(MQTT_DEBUG, "parse client_rsa failed!");
				goto err;
			}
	
	

			mbedtls_ssl_conf_own_cert(n->conf, client_crt, client_rsa);
		}
		retVal = mbedtls_ssl_handshake(n->ssl);

		if (retVal < 0) {
			mqtt_printf(MQTT_DEBUG, "ssl handshake failed err:-0x%04X", -retVal);
			goto err;
		} else {
			mqtt_printf(MQTT_DEBUG, "ssl handshake success");
		}
	}
	if (client_rsa) {
		mbedtls_pk_free(client_rsa);
		mbedtls_free(client_rsa);
	}
	if (client_crt) {
		mbedtls_x509_crt_free(client_crt);
		mbedtls_free(client_crt);
	}
	if (root_crt) {
		mbedtls_x509_crt_free(root_crt);
		mbedtls_free(root_crt);
	}
	
	goto exit;

err:
	if (client_rsa) {
		mbedtls_pk_free(client_rsa);
		mbedtls_free(client_rsa);
	}
	if (client_crt) {
		mbedtls_x509_crt_free(client_crt);
		mbedtls_free(client_crt);
	}
	if (root_crt) {
		mbedtls_x509_crt_free(root_crt);
		mbedtls_free(root_crt);
	}
	mbedtls_net_free((mbedtls_net_context *)&n->my_socket);
	mbedtls_ssl_free(n->ssl);
	mbedtls_ssl_config_free(n->conf);
	free(n->ssl);
	free(n->conf);
	retVal = -1;
#endif // #if (MQTT_OVER_SSL)


exit:
	
	return retVal;
}

#endif /* CONFIG_USE_POLARSSL */

#if 0
int NetworkConnectTLS(Network *n, char* addr, int port, SlSockSecureFiles_t* certificates, unsigned char sec_method, unsigned int cipher, char server_verify)
{
	SlSockAddrIn_t sAddr;
	int addrSize;
	int retVal;
	unsigned long ipAddress;

	retVal = sl_NetAppDnsGetHostByName(addr, strlen(addr), &ipAddress, AF_INET);
	if (retVal < 0) {
		return -1;
	}

	sAddr.sin_family = AF_INET;
	sAddr.sin_port = sl_Htons((unsigned short)port);
	sAddr.sin_addr.s_addr = sl_Htonl(ipAddress);

	addrSize = sizeof(SlSockAddrIn_t);

	n->my_socket = sl_Socket(SL_AF_INET, SL_SOCK_STREAM, SL_SEC_SOCKET);
	if (n->my_socket < 0) {
		return -1;
	}

	SlSockSecureMethod method;
	method.secureMethod = sec_method;
	retVal = sl_SetSockOpt(n->my_socket, SL_SOL_SOCKET, SL_SO_SECMETHOD, &method, sizeof(method));
	if (retVal < 0) {
		return retVal;
	}

	SlSockSecureMask mask;
	mask.secureMask = cipher;
	retVal = sl_SetSockOpt(n->my_socket, SL_SOL_SOCKET, SL_SO_SECURE_MASK, &mask, sizeof(mask));
	if (retVal < 0) {
		return retVal;
	}

	if (certificates != NULL) {
		retVal = sl_SetSockOpt(n->my_socket, SL_SOL_SOCKET, SL_SO_SECURE_FILES, certificates->secureFiles, sizeof(SlSockSecureFiles_t));
		if (retVal < 0)
		{
			return retVal;
		}
	}

	retVal = sl_Connect(n->my_socket, (SlSockAddr_t *)&sAddr, addrSize);
	if (retVal < 0) {
		if (server_verify || retVal != -453) {
			sl_Close(n->my_socket);
			return retVal;
		}
	}

	SysTickIntRegister(SysTickIntHandler);
	SysTickPeriodSet(80000);
	SysTickEnable();

	return retVal;
}
#endif
