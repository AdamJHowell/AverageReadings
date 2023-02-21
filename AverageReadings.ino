#define LED_BUILTIN 2									// The GPIO that the onboard LED is attached to.
unsigned long lastTelemetryPollTime = 0;			// The last time sensors were polled.
unsigned long telemetryPollInterval = 10000;		// How long to wait between sensor polling.
float settingArray[] = { 21.12, 21.12, 21.12 }; // An array to hold the 3 most recent values.
const unsigned int arraySize = 3;


/**
 * @brief readTelemetry() will manipulate the settingArray[] like a FIFO queue, by popping the tail value off, and adding a new value to the head.
 */
void readTelemetry()
{
	settingArray[2] = settingArray[1];
	settingArray[1] = settingArray[0];
	settingArray[0] = random( 99.9 );
} // End of readTelemetry() function.


/**
 * @brief averageArray() return the mathematical mean of all values in the array.
 */
float averageArray()
{
	if( arraySize < 1 )
		return 0.0;
	float tempValue = 0;
	for( size_t i = 0; i < arraySize; i++ )
		tempValue += settingArray[i];
	return tempValue / arraySize;
} // End of the averageArray() function.


void printTelemetry()
{
	Serial.printf( "Average: %f", averageArray() );
} // End of printTelemetry() function.


/**
 * @brief setup() is run once at device boot.
 */
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


/**
 * @brief loop() is run repeatedly after setup() has completed.
 */
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
