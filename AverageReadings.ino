#define LED_BUILTIN 2                             // The GPIO that the onboard LED is attached to.
unsigned long lastTelemetryPollTime = 0;	    // The last time sensors were polled.
unsigned long telemetryPollInterval = 10000;  // How long to wait between sensor polling.
float settingArray[] = { 0, 0, 0 };           // An array to hold the 3 most recent values.


/**
 * @brief readTelemetry() will manipulate the settingArray[] like a FIFO queue, by popping the head value off, and adding a new value to the tail.
 */
void readTelemetry()
{
  settingArray[0] = settingArray[1];
  settingArray[1] = settingArray[2];
  settingArray[2] = random( 99.9 );
} // End of readTelemetry() function.


void printTelemetry()
{
  float tempC = ( settingArray[0] + settingArray[1] + settingArray[2] ) / 3.0;
  Serial.printf( "Average: %d", tempC );
} // End of printTelemetry() function.


void setup() 
{
 	// This delay gives me time to open the serial console after flashing.
	delay( 500 );

	pinMode( LED_BUILTIN, OUTPUT );
	digitalWrite( LED_BUILTIN, HIGH );

	Serial.begin( 115200 );
	if( !Serial )
		delay( 1000 );
	Serial.setDebugOutput( true );
	Serial.println();

	Serial.println( "setup() is running." );
	Serial.printf( "Source file: %s\n", __FILE__ );
} // End of setup() function.


void loop() 
{
	unsigned long time = millis();
	if( lastTelemetryPollTime == 0 || ( ( time > telemetryPollInterval ) && ( time - telemetryPollInterval ) > lastTelemetryPollTime ) )
	{
		readTelemetry();
		printTelemetry();
		lastTelemetryPollTime = millis();
	}
} // End of loop() function.
