/* ********************************************************************
 * 
 *      PROGRAMA PARA MANEJAR EL ENCENDIDO DE 3 LEDS
 *                CON LA TARJETA "ESP32-CAM"
 * 
 * ********************************************************************
 *       Diplomado IoT                     octubre/12 - 2021
 * ********************************************************************
 * 
 * Descripción:
 * 
 * 1. Este programa controla el encendido de 3 LEDs cada
 *    1, 3 y 5 segundos, mediante la técnica no-bloqueante
 *    que se encuentra en el programa: 
 *    "Conexión básica por MQTT del NodeMCU"
 *    realizado por Hugo Escalpelo (28-julio-2021), que se
 *    encuentra en el REPOSITORIO (GitHub) de Codigo IoT
 * 
 * 2. Este programa controla el encendido y apagado de
 *    4 leds conectados a la tarjeta ESP32 en los siguientes
 *    pines: 
 * 
 *    Componente      PinESP32CAM       Estados lógicos
 *    ledStatus--------GPIO 33---------On=>LOW, Off=>HIGH
 *    ledFlash---------GPIO 4----------On=>HIGH, Off=>LOW
 *       
 *    ESPCAM32    ->  LEDS
 *    GPIO12----------LED 1 segundos
 *    GPIO13----------LED 3 segundos
 *    GPIO14----------LED 5 segundos
 *    GPIO15----------LED 7 segundos
 * 
 * ******************************************************************/

 /* -----------------------------------------------------------------
  *  
  *  ESTRUCTURA DEL PROGRAMA:
  *  
  *  100 - void setup()
  *  
  *  200 - void loop()
  *        210 - void controlar_tiempos_led()
  *        
  * ---------------------------------------------------------------*/

/**********************************
 *    Declaracion de VARIABLES
 * *******************************/
long timeNow;       // Variables de control de tiempo no bloqueante

/**********************************
 *    Declaracion de pines - LED
 *    y TIEMPOS de encendido
 *    
 *    GPIO12 <- led_1_seg
 *    GPIO13 <- led_3_seg
 *    GPIO14 <- led_5_seg
 *    GPIO15 <- led_7_seg
 * *******************************/
int num_LEDs = 4;                           // Número de LEDs = 4 LEDs
int pin_LED[] = {12, 13, 14, 15};           // Arreglo de pines del ESP32 para conexión de los LEDs
int wait_LED[] = {1000, 3000, 5000, 7000};  // Arreglo "wait" de encendido/apagado para cada LED
long timeLast_LED[4];                       // Arreglo de "timeLast" para cada LED

/* ********************************************************************
 *  
 *                    100 - void setup()
 *                    
 * *******************************************************************/
void setup() {

  Serial.begin (115200);
  
  /* - 1 ----------------------------------------------------
   *               Inicializacion de LED's 
   * ------------------------------------------------------*/
  for ( int i = 0; i < num_LEDs; ++i ) {
    pinMode (pin_LED[i], OUTPUT);     // pines de SALIDA
    digitalWrite (pin_LED[i], LOW);   // Se apagan todos los LEDs
    timeLast_LED[i] =  millis();      // Se actualiza "timeLast" para cada LED
  }

}


/* ********************************************************************
 *  
 *                      200 - void loop()
 *                      
 * *******************************************************************/
void loop() {

  /* -------------------------------------------------- *
   * LLamada a subrutina de manejo de secuencia de LEDs *
   * ---------------------------------------------------*/
  controlar_secuencia_led();

}

/* ********************************************************************
 *  
 *                  210 - controlar_tiempos_led()
 *                      
 * *******************************************************************/
 void controlar_secuencia_led() {
  /* --------------------------------------------------------
   *     Encendido y apagado de LEDs cada "w" segundos 
   * ------------------------------------------------------*/
  for ( int i = 0; i < num_LEDs; ++i ) {
    timeNow = millis();  // Se actualiza el tiempo actual
    if (timeNow - timeLast_LED[i] > wait_LED[i]) { 
      /* -------------------------------------------------------
       *  Se cumplieron los "w" segundos para el LED "i"
       *  Se actualiza la variable "timeLast" del LED "i"
       *          para seguimiento del tiempo
       * ------------------------------------------------------- */
      timeLast_LED[i] = timeNow;

      if (digitalRead(pin_LED[i])) {
        /* ----------------------------------------
         * Si el LED "i" está encendido -> APAGAR
         * ---------------------------------------- */
        digitalWrite(pin_LED[i], LOW);
      } else {
        /* ----------------------------------------
         * Si el LED "i" está apagado -> ENCENDER
         * ---------------------------------------- */
        digitalWrite(pin_LED[i], HIGH);
      }
    }
  }
 }
