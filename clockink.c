#include <Arduino.h>

#include <Adafruit_GFX.h> 
#include <Fonts/FreeSerifBoldItalic24pt7b.h>
#include <Wire.h>
#include <Adafruit_LPS2X.h>
#include <Adafruit_LC709203F.h>
#include <SensirionI2CScd4x.h>
#include <GxEPD2_BW.h>
#include <RV-3028-C7.h>


#define VERBOSITY 3		/* 0 -> no message, 1 -> general messages, 2 -> Otii Arc messages, 3 -> low level messages */
#include "logger.h"
#include "display.h"
#include "status.h"
#include "resources/font/72x116/array.h"


//#define INIT_RV3028	/* uncomment to run the 1st time (init the RV_3028-C7) to produce an interrupt every minut */ 


/* === Peripherials === */

/* display e-ink Waveshare 7.5" v2 */
GxEPD2_BW<GxEPD2_750_T7, GxEPD2_750_T7::HEIGHT> display(GxEPD2_750_T7(/*CS*/8, /*DC*/18, /*RST*/17, /*BUSY*/16));
/* CO2 sensor SCD40 */
SensirionI2CScd4x scd40;
/* pressure sensor LSP22 */
Adafruit_LPS22 lps;
/* RV3028 RTC Breakout */
RV3028 rtc;
/* LC709203 battery charger */
Adafruit_LC709203F batt;

/* intern status (hour, date, temp., ) */
t_status st;

/* enable and disable I2C */
inline void enableI2C() {digitalWrite(I2C_POWER, HIGH);}
inline void disableI2C() {digitalWrite(I2C_POWER, LOW);}


void setup() {
	/* init I2C */
	pinMode(I2C_POWER, OUTPUT);
	enableI2C();

	/* init serials */
	logInit(115200, SERIAL_8N1, 38, 39);
	Wire.begin(115200);
	delay(100);
	logInfo("Start !");

	/* init display */
	display.init(115200); // enable diagnostic output on Serial
	display.hibernate();
	
	/* init SCD40 */
	//scd40.begin(Wire);

	/* init LPS22 */
	//lps.init(Wire);

	/* init RTC */
	//rtc.init(Wire);
	//getDateHour(rtc, status)
	
	/* init battery */
	//batt.init(Wire);


	/*TODO: 
	- demander à avoir une interruption de RTC toutes les minutes
	- passer en mode sleep
	*/

	
	// debug
	displayHour(0x2245);
	helloWorld("Hello World!");
	

/*
	// stop potentially previously started measurement
	error = scd4x.stopPeriodicMeasurement();
	if (error) {
		logDebug("Error trying to execute stopPeriodicMeasurement(): ");
		errorToString(error, errorMessage, 256);
		logDebug(errorMessage);
	}

	// Start Measurement
	//error = scd4x.startPeriodicMeasurement();
	if (error) {
		logDebug("Error trying to execute startPeriodicMeasurement(): ");
		errorToString(error, errorMessage, 256);
		logDebug(errorMessage);
	}


	logDebug("Waiting for first measurement... (5 sec)");
*/
}

void loop() {

	uint16_t error;
	char errorMessage[256];
	char msg[256];


	logOtii("end delay 10s - print toto");


// static int toto = 0;
// toto++;
// sprintf(msg, "toto = %d", toto);
// display.init(115200);
// helloWorld(msg);
// display.hibernate();

	logOtii("start loop");
	delay(10000);


/*
	// Read Measurement
	uint16_t co2;
	float temperature;
	float humidity;
	digitalWrite(I2C_POWER, LOW);
	logDebug("start measures SCD");
 error = scd4x.startPeriodicMeasurement();
 delay(5000);
	error = scd4x.readMeasurement(co2, temperature, humidity);
	logDebug("end measure SCD");
	if (error) {
		logDebug("Error trying to execute readMeasurement(): ");
		errorToString(error, errorMessage, 256);
		logDebug(errorMessage);
	} else if (co2 == 0) {
		logDebug("Invalid sample detected, skipping.");
	} else {
		sprintf(msg,"Co2=%d  T°=%.1f°C  H=%.1f%\n 17h40", co2, temperature, humidity);
		logDebug("begin print e-ink");
		helloWorld(msg);
		logDebug("end deisplay");

		logDebug(msg);
	}
	digitalWrite(I2C_POWER, HIGH);
*/
}


void helloWorld(char *msg)
{

	display.setRotation(0);
	display.setFont(&FreeSerifBoldItalic24pt7b);
	display.setTextColor(GxEPD_BLACK);
	int16_t tbx, tby; uint16_t tbw, tbh;
	display.getTextBounds(msg, 0, 0, &tbx, &tby, &tbw, &tbh);
	// center the bounding box by transposition of the origin:
	uint16_t x = ((display.width() - tbw) / 2) - tbx;
	uint16_t y = ((display.height() - tbh) / 2) - tby;
	display.setFullWindow();
	display.firstPage();
	do
	{
		display.fillScreen(GxEPD_WHITE);
		display.setCursor(x, y);
		display.print(msg);
	}
	while (display.nextPage());

 display.hibernate();
}



