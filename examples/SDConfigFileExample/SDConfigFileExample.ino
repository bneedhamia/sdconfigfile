#include <SD.h>
#include <SDConfigFile.h>

/*
 * Example use of the SDConfigFile library.
 * This sketch reads the configuration file from the SD card,
 * then prints the configuration and prints a hello message
 * at a rate given in the configuration file.
 *
 * This example app is placed in the public domain by its author,
 * Bradford Needham (@bneedhamia, https://www.needhamia.com )
 */
 
/*
 * Hardware: An Arduino Uno
 * plus an SD card shield, for example the
 * Sparkfun MicroSD Shield:
 *   https://www.sparkfun.com/products/12761
 *
 * Make sure that pinSelectSD (below) is correct
 * for the SD card you're using.
 */

/*
 * To operate:
 * 1) format your SD card.
 * 2) copy the examples/SDConfigFileExample/example.cfg file
 *    to the SD card.
 * 3) Download and run this Sketch
 * 4) Open the Serial Monitor at 9600 baud.
 * See that the Serial Monitor shows the settings
 * and the greeting, and the hello message is printed
 * with the timing given in the configuration file.
 *
 * Change the example.cfg file contents and see how the
 * hello message and timing change - without downloading
 * a new version of this sketch.
 */

const int pinSelectSD = 8; // SD shield Chip Select pin.

// The filename of the configuration file on the SD card
const char CONFIG_FILE[] = "example.cfg";

/*
 * Settings we read from the configuration file.
 *   didReadConfig = true if the configuration-reading succeeded;
 *     false otherwise.
 *     Used to prevent odd behaviors if the configuration file
 *     is corrupt or missing.
 *   hello = the "hello world" string, allocated via malloc().
 *   doDelay = if true, delay waitMs in loop().
 *     if false, don't delay.
 *   waitMs = time (milliseconds) to wait after printing hello.
 */
boolean didReadConfig;
char *hello;
boolean doDelay;
int waitMs;

boolean readConfiguration();

void setup() {
  Serial.begin(9600);

  pinMode(pinSelectSD, OUTPUT);

  didReadConfig = false;
  hello = 0;
  doDelay = false;
  waitMs = 0;
  
  
  // Setup the SD card 
  Serial.println("Calling SD.begin()...");
  if (!SD.begin(pinSelectSD)) {
    Serial.println("SD.begin() failed. Check: ");
    Serial.println("  card insertion,");
    Serial.println("  SD shield I/O pins and chip select,");
    Serial.println("  card formatting.");
    return;
  }
  Serial.println("...succeeded.");

  // Read our configuration from the SD card file.
  didReadConfig = readConfiguration();
}

void loop() {

  /*
   * If we didn't read the configuration, do nothing.
   */
   
  if (!didReadConfig) {
    return;
  }

  /*
   * print the hello message,
   * then wait the configured time.
   */
  if (hello) {

    Serial.println(hello);
    if (doDelay) {
      delay(waitMs);
    }

  }
  
}

/*
 * Read our settings from our SD configuration file.
 * Returns true if successful, false if it failed.
 */
boolean readConfiguration() {
  /*
   * Length of the longest line expected in the config file.
   * The larger this number, the more memory is used
   * to read the file.
   * You probably won't need to change this number.
   */
  const uint8_t CONFIG_LINE_LENGTH = 127;
  
  // The open configuration file.
  SDConfigFile cfg;
  
  // Open the configuration file.
  if (!cfg.begin(CONFIG_FILE, CONFIG_LINE_LENGTH)) {
    Serial.print("Failed to open configuration file: ");
    Serial.println(CONFIG_FILE);
    return false;
  }
  
  // Read each setting from the file.
  while (cfg.readNextSetting()) {
    
    // Put a nameIs() block here for each setting you have.
    
    // doDelay
    if (cfg.nameIs("doDelay")) {
      
      doDelay = cfg.getBooleanValue();
      Serial.print("Read doDelay: ");
      if (doDelay) {
        Serial.println("true");
      } else {
        Serial.println("false");
      }
    
    // waitMs integer
    } else if (cfg.nameIs("waitMs")) {
      
      waitMs = cfg.getIntValue();
      Serial.print("Read waitMs: ");
      Serial.println(waitMs);

    // hello string (char *)
    } else if (cfg.nameIs("hello")) {
      
      // Dynamically allocate a copy of the string.
      hello = cfg.copyValue();
      Serial.print("Read hello: ");
      Serial.println(hello);

    } else {
      // report unrecognized names.
      Serial.print("Unknown name in config: ");
      Serial.println(cfg.getName());
    }
  }
  
  // clean up
  cfg.end();
  
  return true;
}

