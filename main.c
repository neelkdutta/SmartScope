/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "string.h"
#include <stdlib.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim7;
TIM_HandleTypeDef htim17;

/* USER CODE BEGIN PV */

//NEED PUBLIC VARIABLES FOR 1. LSTHOURS 2. LSTMINUTES 3. RAMOTORTICKS 4. DECMOTORTICKS
static int lst_hours = 0;
static int lst_minutes = 0;
static int currentDECticks = 0;
static int currentRAticks = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
static void MX_TIM17_Init(void);
static void MX_TIM7_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


void HAL_GPIO_EXTI_Callback(uint16_t pin) {
	if(pin == GPIO_PIN_14){
		currentDECticks++;
	}

	else if(pin == GPIO_PIN_0){
		currentRAticks++;
	}
}

char read_char() {

	while(1){
  			//row 1
  			HAL_GPIO_WritePin (GPIOC, GPIO_PIN_8, GPIO_PIN_SET);  //Pull the R1 high
  			HAL_GPIO_WritePin (GPIOF, GPIO_PIN_5, GPIO_PIN_RESET);  // Pull the R2 low
  			HAL_GPIO_WritePin (GPIOF, GPIO_PIN_3, GPIO_PIN_RESET);  // Pull the R3 low
  			HAL_GPIO_WritePin (GPIOC, GPIO_PIN_12, GPIO_PIN_RESET);  // Pull the R4 low

  			if (HAL_GPIO_ReadPin (GPIOD, GPIO_PIN_2)){   // if the Col 1 is high
  				while(HAL_GPIO_ReadPin (GPIOD, GPIO_PIN_2)){
  					HAL_Delay(5); //experimental delay of 5 ms, to unbounce
  				}
  				return '1';
  			}
  			if (HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_11)){   // if the Col 2 is high
  				while(HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_11)){
  					HAL_Delay(5); //experimental delay of 5 ms, to unbounce
  				}
  				return '2';
  			}
  			if (HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_10)){   // if the Col 3 is high
  				while(HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_10)){
  					HAL_Delay(5); //experimental delay of 5 ms, to unbounce
  				}
  				return '3';
  			}
  			if (HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_9)){   // if the Col 4 is high
  				while(HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_9)){
  					HAL_Delay(5); //experimental delay of 5 ms, to unbounce
  				}
  				return '-';
  			}

  			//row 2
  			HAL_GPIO_WritePin (GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);  //Pull the R1 low
  			HAL_GPIO_WritePin (GPIOF, GPIO_PIN_5, GPIO_PIN_SET);  // Pull the R2 high
  			HAL_GPIO_WritePin (GPIOF, GPIO_PIN_3, GPIO_PIN_RESET);  // Pull the R3 low
  			HAL_GPIO_WritePin (GPIOC, GPIO_PIN_12, GPIO_PIN_RESET);  // Pull the R4 low

  			if (HAL_GPIO_ReadPin (GPIOD, GPIO_PIN_2)){   // if the Col 1 is high
  				while(HAL_GPIO_ReadPin (GPIOD, GPIO_PIN_2)){
  					HAL_Delay(5); //experimental delay of 5 ms, to unbounce
  				}
  				return '4';
  			}
  			if (HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_11)){   // if the Col 2 is high
  				while(HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_11)){
  					HAL_Delay(5); //experimental delay of 5 ms, to unbounce
  				}
  				return '5';
  			}
  			if (HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_10)){   // if the Col 3 is high
  				while(HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_10)){
  					HAL_Delay(5); //experimental delay of 5 ms, to unbounce
  				}
  				return '6';
  			}
  			if (HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_9)){   // if the Col 4 is high
  				while(HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_9)){
  					HAL_Delay(5); //experimental delay of 5 ms, to unbounce
  				}
  				return '+';
  			}

  			//row 3
  			HAL_GPIO_WritePin (GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);  //Pull the R1 low
  			HAL_GPIO_WritePin (GPIOF, GPIO_PIN_5, GPIO_PIN_RESET);  // Pull the R2 low
  			HAL_GPIO_WritePin (GPIOF, GPIO_PIN_3, GPIO_PIN_SET);  // Pull the R3 high
  			HAL_GPIO_WritePin (GPIOC, GPIO_PIN_12, GPIO_PIN_RESET);  // Pull the R4 low

  			if (HAL_GPIO_ReadPin (GPIOD, GPIO_PIN_2)){   // if the Col 1 is high
  				while(HAL_GPIO_ReadPin (GPIOD, GPIO_PIN_2)){
  					HAL_Delay(5); //experimental delay of 5 ms, to unbounce
  				}
  				return '7';
  			}
  			if (HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_11)){   // if the Col 2 is high
  				while(HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_11)){
  					HAL_Delay(5); //experimental delay of 5 ms, to unbounce
  				}
  				return '8';
  			}
  			if (HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_10)){   // if the Col 3 is high
  				while(HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_10)){
  					HAL_Delay(5); //experimental delay of 5 ms, to unbounce
  				}
  				return '9';
  			}
  			if (HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_9)){   // if the Col 4 is high
  				while(HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_9)){
  					HAL_Delay(5); //experimental delay of 5 ms, to unbounce
  				}
  				return 'C';
  			}

  			//row4
  			HAL_GPIO_WritePin (GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);  //Pull the R1 low
  			HAL_GPIO_WritePin (GPIOF, GPIO_PIN_5, GPIO_PIN_RESET);  // Pull the R2 low
  			HAL_GPIO_WritePin (GPIOF, GPIO_PIN_3, GPIO_PIN_RESET);  // Pull the R3 low
  			HAL_GPIO_WritePin (GPIOC, GPIO_PIN_12, GPIO_PIN_SET);  // Pull the R4 high

  			if (HAL_GPIO_ReadPin (GPIOD, GPIO_PIN_2)){   // if the Col 1 is high
  				while(HAL_GPIO_ReadPin (GPIOD, GPIO_PIN_2)){
  					HAL_Delay(5); //experimental delay of 5 ms, to unbounce
  				}
  				return '*';
  			}
  			if (HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_11)){   // if the Col 2 is high
  				while(HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_11)){
  					HAL_Delay(5); //experimental delay of 5 ms, to unbounce
  				}
  				return '0';
  			}
  			if (HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_10)){   // if the Col 3 is high
  				while(HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_10)){
  					HAL_Delay(5); //experimental delay of 5 ms, to unbounce
  				}
  				return '#';
  			}
  			if (HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_9)){   // if the Col 4 is high
  				while(HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_9)){
  					HAL_Delay(5); //experimental delay of 5 ms, to unbounce
  				}
  				return 'D';
  			}
  		}
}

//writes from keypad to display
char write_keypadchar(){
	HAL_GPIO_WritePin (GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);

	char toreturn = read_char();
	uint8_t buf[10] = {toreturn};
	HAL_SPI_Transmit(&hspi1, buf, 1, HAL_MAX_DELAY);

	HAL_GPIO_WritePin (GPIOA, GPIO_PIN_6, GPIO_PIN_SET);// deselect display

	return toreturn;
}

//writes predetermined char to screen
void write_char(char towrite){
	HAL_GPIO_WritePin (GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);

	HAL_Delay(5);
	uint8_t buf1[10] = {towrite};
	HAL_SPI_Transmit(&hspi1, buf1, 1, HAL_MAX_DELAY);

	HAL_GPIO_WritePin (GPIOA, GPIO_PIN_6, GPIO_PIN_SET);// deselect display

}

//reads LST in the format hhmm
char* get_LST(){
  HAL_GPIO_WritePin (GPIOA, GPIO_PIN_6, GPIO_PIN_RESET); //select the display

	//clear the screen
	uint8_t buf1[10] = {0xFE, 0x51};
	HAL_SPI_Transmit(&hspi1, buf1, 2, HAL_MAX_DELAY);

	//write RA:
	write_char('L');
	write_char('S');
	write_char('T');
  write_char(':');
  write_char(' ');
  static char toreturn[4] = "";
  for(int i = 0; i < 4; i++){
	if(i == 2){
		write_char('h');
		write_char(' ');
	}
    char toappend = write_keypadchar();
	strncat(toreturn, &toappend, 1);
  }
  write_char('m');

  HAL_GPIO_WritePin (GPIOA, GPIO_PIN_6, GPIO_PIN_SET); //deselect the display
  HAL_Delay(1000);
  return toreturn;
}


//gets RA and Dec from keypad
//RA: hhmm
//Dec: <+/->ddmm  (A is -, B is +)
char* get_coords(){
	HAL_GPIO_WritePin (GPIOA, GPIO_PIN_6, GPIO_PIN_RESET); //select the display

	//clear the screen
	uint8_t buf1[10] = {0xFE, 0x51};
	HAL_SPI_Transmit(&hspi1, buf1, 2, HAL_MAX_DELAY);

	//write RA:
	write_char('R');
	write_char('A');
	write_char(':');
	write_char(' ');

	static char ra_dec[10];
	//read 4 inputs
	for(int i = 0; i < 4; i++){
		if(i == 2){
			write_char('h');
			write_char(' ');
		}
		char toappend = write_keypadchar();
		strncat(ra_dec, &toappend, 1);
	}
	write_char('m');
	HAL_Delay(1000);
  //clear screen
	HAL_GPIO_WritePin (GPIOA, GPIO_PIN_6, GPIO_PIN_RESET); //select the display

  	//uint8_t buf2[10] = {0xFE, 0x51};
	//HAL_SPI_Transmit(&hspi1, buf2, 2, HAL_MAX_DELAY);

	 //set cursor below and write DEC:
	 HAL_Delay(5);
	 uint8_t buf3[10] = {0xFE, 0x45, 0x14};
	 HAL_SPI_Transmit(&hspi1, buf3, 3, HAL_MAX_DELAY);


	write_char('D');
	write_char('E');
	write_char('C');
	write_char(':');
	write_char(' ');

	for(int i = 0; i < 5; i++){
		if(i == 3){
			write_char('d');
			write_char(' ');
		}
		char toappend = write_keypadchar();
		strncat(ra_dec, &toappend, 1);
	}
	write_char('m');
	HAL_GPIO_WritePin (GPIOA, GPIO_PIN_6, GPIO_PIN_SET); //deselect display
	HAL_Delay(2000);
	return ra_dec;
}

int getLSThours(char * str){
  char convert[2];
  strncpy(convert, str, 2);
  return atoi(convert);
}

int getLSTminutes(char * str){
  char convert[2];
  strncpy(convert, str + 2, 2);
  return atoi(convert);
}

int getRAhours(char * str){
  char convert[2];
  strncpy(convert, str, 2);
  return (atoi(convert));
}

int getRAminutes(char * str){
  char convert[2];
  strncpy(convert, str + 2, 2);
  return (atoi(convert));
}

//returns as an offset from +90
int getDECdegrees(char * str){
  char convert[3];
  strncpy(convert, str + 4, 3);
  return atoi(convert);
}

int getDECminutes(char * str){
  char convert[2];
  strncpy(convert, str + 7, 2);

  return (atoi(convert));
}

//assuming starting at ha = 0
int getTotalTicksHA(int RAhours, int RAminutes){


  //logic for HA = LST - RA
  int HAhours = 0;
  int HAminutes = 0;
  if(lst_hours - RAhours <= 0){
    HAhours = 24 + lst_hours - RAhours;
    if(lst_minutes - RAminutes < 0){
      HAminutes = 60 + lst_minutes - RAminutes;
      HAhours--;
    }
    else{
      if(lst_hours == RAhours){ //edge case
        HAhours = 0;
      }
      HAminutes = lst_minutes - RAminutes;
    }
  }
  else{ //lsthours - rahours > 0
    HAhours = lst_hours - RAhours;
    if(lst_minutes - RAminutes < 0){
      HAminutes = 60 + lst_minutes - RAminutes;
      HAhours--;
    }
    else{
      HAminutes = lst_minutes - RAminutes;
    }
  }

  //HOPEFULLY
  //0 <= HAhours < 24
  //0 <= HAminutes < 60

  //actual ticks
  int ticksfor1 = 2740;
  int toreturn = 0;
  if(HAhours < 12){ //clockwise
    toreturn = ticksfor1 * HAhours;
    toreturn += ticksfor1 / 60 * HAminutes;
  }
  else{ //counter-clockwise
    toreturn = ticksfor1 * (24 - HAhours);
    toreturn -= ticksfor1 / 60 * HAminutes;
  }
  return toreturn;
}

//assuming starting at dec = 0
int getTotalTicksDEC(int DECdegrees, int DECminutes){
  int ticksfor90 = 27990; //NEED TO CHANGE
  int toreturn = 0; 
  if(DECdegrees > 0){
    toreturn = ticksfor90 / 90 * DECdegrees + ticksfor90 / 90 / 60 * DECminutes;
  }else{
    DECdegrees *= -1;
    toreturn = ticksfor90 / 90 * DECdegrees + ticksfor90 / 90 / 60 * DECminutes;
  }
  return toreturn;
}

void goToFromReset(int RAhours, int RAminutes, int DECdegrees, int DECminutes){
  int raTickGoal = getTotalTicksHA(RAhours, RAminutes);
  int decTickGoal = getTotalTicksDEC(DECdegrees, DECminutes);

  //configure CW/CCW
  HAL_GPIO_WritePin (GPIOF, GPIO_PIN_8, GPIO_PIN_SET);
  HAL_GPIO_WritePin (GPIOF, GPIO_PIN_7, GPIO_PIN_SET);

  HAL_GPIO_WritePin (GPIOF, GPIO_PIN_9, GPIO_PIN_SET);
  HAL_GPIO_WritePin (GPIOG, GPIO_PIN_1, GPIO_PIN_SET);

  int HAhours = 0;
    int HAminutes = 0;
    if(lst_hours - RAhours <= 0){
      HAhours = 24 + lst_hours - RAhours;
      if(lst_minutes - RAminutes < 0){
        HAminutes = 60 + lst_minutes - RAminutes;
        HAhours--;
      }
      else{
        if(lst_hours == RAhours){ //edge case
          HAhours = 0;
        }
        HAminutes = lst_minutes - RAminutes;
      }
    }
    else{ //lsthours - rahours > 0
      HAhours = lst_hours - RAhours;
      if(lst_minutes - RAminutes < 0){
        HAminutes = 60 + lst_minutes - RAminutes;
        HAhours--;
      }
      else{
        HAminutes = lst_minutes - RAminutes;
      }
    }

  //MAY HAVE TO SWAP
  if(HAhours < 12){ //CW
    HAL_GPIO_WritePin (GPIOF, GPIO_PIN_8, GPIO_PIN_RESET);
  }
  else{ //CCW
    HAL_GPIO_WritePin (GPIOF, GPIO_PIN_7, GPIO_PIN_RESET);
  }

  if(DECdegrees > 0){ //up/CW from the left
    HAL_GPIO_WritePin (GPIOF, GPIO_PIN_9, GPIO_PIN_RESET);
  }
  else{ //down/CCW from the left
    HAL_GPIO_WritePin (GPIOG, GPIO_PIN_1, GPIO_PIN_RESET);
  }

  currentRAticks = 0;
  currentDECticks = 0;

  while(currentRAticks <= raTickGoal && currentDECticks <= decTickGoal){
    //in progress message?
  }
  if(currentRAticks >= raTickGoal){
	  //turn off motor 1
	HAL_GPIO_WritePin (GPIOF, GPIO_PIN_8, GPIO_PIN_SET);
	HAL_GPIO_WritePin (GPIOF, GPIO_PIN_7, GPIO_PIN_SET);
  }

  if(currentDECticks >= decTickGoal){
	  //turn off motor 2
	    HAL_GPIO_WritePin (GPIOF, GPIO_PIN_9, GPIO_PIN_SET);
	    HAL_GPIO_WritePin (GPIOG, GPIO_PIN_1, GPIO_PIN_SET);
  }

  while(currentRAticks <= raTickGoal || currentDECticks <= decTickGoal){
      //in progress message?
    }

  if(currentRAticks >= raTickGoal){
  	  //turn off motor 1
  	HAL_GPIO_WritePin (GPIOF, GPIO_PIN_8, GPIO_PIN_SET);
  	HAL_GPIO_WritePin (GPIOF, GPIO_PIN_7, GPIO_PIN_SET);
  }

    if(currentDECticks >= decTickGoal){
  	  //turn off motor 2
  	    HAL_GPIO_WritePin (GPIOF, GPIO_PIN_9, GPIO_PIN_SET);
  	    HAL_GPIO_WritePin (GPIOG, GPIO_PIN_1, GPIO_PIN_SET);
    }


  //turn off all motors
  HAL_GPIO_WritePin (GPIOF, GPIO_PIN_8, GPIO_PIN_SET);
  HAL_GPIO_WritePin (GPIOF, GPIO_PIN_7, GPIO_PIN_SET);
  HAL_GPIO_WritePin (GPIOF, GPIO_PIN_9, GPIO_PIN_SET);
  HAL_GPIO_WritePin (GPIOG, GPIO_PIN_1, GPIO_PIN_SET);




  //no longer at position, go back to main control logic
  
  //RESET GLOBAL VARS

}

//returns the character currently pressed, otherwise 'x'
char single_poll(){
  HAL_Delay(50);
  HAL_GPIO_WritePin (GPIOC, GPIO_PIN_8, GPIO_PIN_SET);  //Pull the R1 high
  HAL_GPIO_WritePin (GPIOF, GPIO_PIN_5, GPIO_PIN_RESET);  // Pull the R2 low
  HAL_GPIO_WritePin (GPIOF, GPIO_PIN_3, GPIO_PIN_RESET);  // Pull the R3 low
  HAL_GPIO_WritePin (GPIOC, GPIO_PIN_12, GPIO_PIN_RESET);  // Pull the R4 low

  if (HAL_GPIO_ReadPin (GPIOD, GPIO_PIN_2)){   // if the Col 1 is high
    while(HAL_GPIO_ReadPin (GPIOD, GPIO_PIN_2)){
      HAL_Delay(5); //experimental delay of 5 ms, to unbounce
    }
    return '1';
  }
  if (HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_11)){   // if the Col 2 is high
    while(HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_11)){
      HAL_Delay(5); //experimental delay of 5 ms, to unbounce
    }
    return '2';
  }
  if (HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_10)){   // if the Col 3 is high
    while(HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_10)){
      HAL_Delay(5); //experimental delay of 5 ms, to unbounce
    }
    return '3';
  }
  if (HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_9)){   // if the Col 4 is high
    while(HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_9)){
      HAL_Delay(5); //experimental delay of 5 ms, to unbounce
    }
    return '-';
  }

  //row 2
  HAL_GPIO_WritePin (GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);  //Pull the R1 low
  HAL_GPIO_WritePin (GPIOF, GPIO_PIN_5, GPIO_PIN_SET);  // Pull the R2 high
  HAL_GPIO_WritePin (GPIOF, GPIO_PIN_3, GPIO_PIN_RESET);  // Pull the R3 low
  HAL_GPIO_WritePin (GPIOC, GPIO_PIN_12, GPIO_PIN_RESET);  // Pull the R4 low

  if (HAL_GPIO_ReadPin (GPIOD, GPIO_PIN_2)){   // if the Col 1 is high
    while(HAL_GPIO_ReadPin (GPIOD, GPIO_PIN_2)){
      HAL_Delay(5); //experimental delay of 5 ms, to unbounce
    }
    return '4';
  }
  if (HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_11)){   // if the Col 2 is high
    while(HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_11)){
      HAL_Delay(5); //experimental delay of 5 ms, to unbounce
    }
    return '5';
  }
  if (HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_10)){   // if the Col 3 is high
    while(HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_10)){
      HAL_Delay(5); //experimental delay of 5 ms, to unbounce
    }
    return '6';
  }
  if (HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_9)){   // if the Col 4 is high
    while(HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_9)){
      HAL_Delay(5); //experimental delay of 5 ms, to unbounce
    }
    return '+';
  }

  //row 3
  HAL_GPIO_WritePin (GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);  //Pull the R1 low
  HAL_GPIO_WritePin (GPIOF, GPIO_PIN_5, GPIO_PIN_RESET);  // Pull the R2 low
  HAL_GPIO_WritePin (GPIOF, GPIO_PIN_3, GPIO_PIN_SET);  // Pull the R3 high
  HAL_GPIO_WritePin (GPIOC, GPIO_PIN_12, GPIO_PIN_RESET);  // Pull the R4 low

  if (HAL_GPIO_ReadPin (GPIOD, GPIO_PIN_2)){   // if the Col 1 is high
    while(HAL_GPIO_ReadPin (GPIOD, GPIO_PIN_2)){
      HAL_Delay(5); //experimental delay of 5 ms, to unbounce
    }
    return '7';
  }
  if (HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_11)){   // if the Col 2 is high
    while(HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_11)){
      HAL_Delay(5); //experimental delay of 5 ms, to unbounce
    }
    return '8';
  }
  if (HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_10)){   // if the Col 3 is high
    while(HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_10)){
      HAL_Delay(5); //experimental delay of 5 ms, to unbounce
    }
    return '9';
  }
  if (HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_9)){   // if the Col 4 is high
    while(HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_9)){
      HAL_Delay(5); //experimental delay of 5 ms, to unbounce
    }
    return 'C';
  }

  //row4
  HAL_GPIO_WritePin (GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);  //Pull the R1 low
  HAL_GPIO_WritePin (GPIOF, GPIO_PIN_5, GPIO_PIN_RESET);  // Pull the R2 low
  HAL_GPIO_WritePin (GPIOF, GPIO_PIN_3, GPIO_PIN_RESET);  // Pull the R3 low
  HAL_GPIO_WritePin (GPIOC, GPIO_PIN_12, GPIO_PIN_SET);  // Pull the R4 high

  if (HAL_GPIO_ReadPin (GPIOD, GPIO_PIN_2)){   // if the Col 1 is high
    while(HAL_GPIO_ReadPin (GPIOD, GPIO_PIN_2)){
      HAL_Delay(5); //experimental delay of 5 ms, to unbounce
    }
    return '*';
  }
  if (HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_11)){   // if the Col 2 is high
    while(HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_11)){
      HAL_Delay(5); //experimental delay of 5 ms, to unbounce
    }
    return '0';
  }
  if (HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_10)){   // if the Col 3 is high
    while(HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_10)){
      HAL_Delay(5); //experimental delay of 5 ms, to unbounce
    }
    return '#';
  }
  if (HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_9)){   // if the Col 4 is high
    while(HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_9)){
      HAL_Delay(5); //experimental delay of 5 ms, to unbounce
    }
    return 'D';
  }
  return 'x';
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_TIM17_Init();
  MX_TIM7_Init();
  /* USER CODE BEGIN 2 */

  //reads one char from keypad


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  //set motors to idle
  HAL_GPIO_WritePin (GPIOF, GPIO_PIN_8, GPIO_PIN_SET);
  HAL_GPIO_WritePin (GPIOF, GPIO_PIN_7, GPIO_PIN_SET);

  HAL_GPIO_WritePin (GPIOF, GPIO_PIN_9, GPIO_PIN_SET);
  HAL_GPIO_WritePin (GPIOG, GPIO_PIN_1, GPIO_PIN_SET);


  HAL_GPIO_WritePin (GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
  HAL_Delay(3000); //to allow board to stabalize? idk but it fixed some problems

  //clear the screen
  HAL_GPIO_WritePin (GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
  uint8_t buf1[10] = {0xFE, 0x51};
  HAL_SPI_Transmit(&hspi1, buf1, 2, HAL_MAX_DELAY);
  HAL_Delay(5);

  //set blinking cursor on
  uint8_t buf2[10] = {0xFE, 0x4B};
  HAL_SPI_Transmit(&hspi1, buf2, 2, HAL_MAX_DELAY);
  HAL_Delay(5);

  HAL_GPIO_WritePin (GPIOA, GPIO_PIN_6, GPIO_PIN_SET);



  //get LST from keypad
  char * lst_str = get_LST();
  lst_hours = getLSThours(lst_str);
  lst_minutes = getLSTminutes(lst_str); //need to set up a way to increment lst via timer interrupt

  HAL_TIM_Base_Start_IT(&htim17);//start lst timer
  while (1){ //past initialization, after LST has been set
	  char* radec_str;
	  radec_str[0] = '\0';
	  radec_str = get_coords();

	  int ra_hours = getRAhours(radec_str);
	  int ra_minutes = getRAminutes(radec_str);
	  int dec_degrees = getDECdegrees(radec_str);
	  int dec_minutes = getDECminutes(radec_str) / 10; //idk why

	  goToFromReset(ra_hours, ra_minutes, dec_degrees, dec_minutes);

	  while(1){ //inner while, inside only when looking at an object

		   // start 1 min timer interrupt
		  HAL_TIM_Base_Start_IT(&htim7); // start 10 sec timer interrupt

      //check for abcd pressed down
      char captured = single_poll();
      if(captured == 'x'){ // nothing was pressed
        HAL_GPIO_WritePin (GPIOF, GPIO_PIN_8, GPIO_PIN_SET);
        HAL_GPIO_WritePin (GPIOF, GPIO_PIN_7, GPIO_PIN_SET);
        HAL_GPIO_WritePin (GPIOF, GPIO_PIN_9, GPIO_PIN_SET);
        HAL_GPIO_WritePin (GPIOG, GPIO_PIN_1, GPIO_PIN_SET);

      }
      if(captured == '*'){
          break; //should prompt to enter new coordinates
      }
      if(captured != 'x'){ //smth was actually pressed
        if(captured == '-'){
  
          HAL_GPIO_WritePin (GPIOF, GPIO_PIN_8, GPIO_PIN_RESET);
          HAL_Delay(5);
        }
        else if(captured == '+'){
         
          HAL_GPIO_WritePin (GPIOF, GPIO_PIN_7, GPIO_PIN_RESET);
          HAL_Delay(5);
        }
        else if(captured == 'C'){
          
          HAL_GPIO_WritePin (GPIOF, GPIO_PIN_9, GPIO_PIN_RESET);
          HAL_Delay(5);
        }
        else if(captured == 'D'){
          
          HAL_GPIO_WritePin (GPIOG, GPIO_PIN_1, GPIO_PIN_RESET);
          HAL_Delay(5);
        }
      }//end if not x


	  }//end inner while
	  HAL_TIM_Base_Stop_IT(&htim7); // stop 10 sec interrrupt - for auto increment - stop after done w curr location



    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi1.Init.CLKPhase = SPI_PHASE_2EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM7 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM7_Init(void)
{

  /* USER CODE BEGIN TIM7_Init 0 */

  /* USER CODE END TIM7_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM7_Init 1 */

  /* USER CODE END TIM7_Init 1 */
  htim7.Instance = TIM7;
  htim7.Init.Prescaler = 4000-1;
  htim7.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim7.Init.Period = 10000-1;
  htim7.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim7) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim7, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM7_Init 2 */

  /* USER CODE END TIM7_Init 2 */

}

/**
  * @brief TIM17 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM17_Init(void)
{

  /* USER CODE BEGIN TIM17_Init 0 */

  /* USER CODE END TIM17_Init 0 */

  /* USER CODE BEGIN TIM17_Init 1 */

  /* USER CODE END TIM17_Init 1 */
  htim17.Instance = TIM17;
  htim17.Init.Prescaler = 4000-1;
  htim17.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim17.Init.Period = 60000-1;
  htim17.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim17.Init.RepetitionCounter = 0;
  htim17.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim17) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM17_Init 2 */

  /* USER CODE END TIM17_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  HAL_PWREx_EnableVddIO2();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_3|GPIO_PIN_5|GPIO_PIN_7|GPIO_PIN_8
                          |GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, GPIO_PIN_1, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8|GPIO_PIN_12, GPIO_PIN_RESET);

  /*Configure GPIO pins : PE2 PE3 */
  GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF13_SAI1;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PF0 PF1 PF2 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF4_I2C2;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pins : PF3 PF5 PF7 PF8
                           PF9 */
  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_5|GPIO_PIN_7|GPIO_PIN_8
                          |GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pins : PC0 PC1 PC2 PC3
                           PC4 PC5 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG_ADC_CONTROL;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PA1 PA3 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG_ADC_CONTROL;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PA6 */
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PB1 */
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG_ADC_CONTROL;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB2 PB6 */
  GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PG1 */
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : PE7 PE8 PE9 PE10
                           PE11 PE12 PE13 */
  GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF1_TIM1;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PE14 PE0 */
  GPIO_InitStruct.Pin = GPIO_PIN_14|GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : PE15 */
  GPIO_InitStruct.Pin = GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF3_TIM1_COMP1;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : PB10 */
  GPIO_InitStruct.Pin = GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB12 PB13 PB15 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF13_SAI2;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PB14 */
  GPIO_InitStruct.Pin = GPIO_PIN_14;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF14_TIM15;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PD8 PD9 */
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : PD14 PD15 */
  GPIO_InitStruct.Pin = GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF2_TIM4;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : PG7 PG8 */
  GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF8_LPUART1;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pin : PC6 */
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF13_SAI2;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PC7 */
  GPIO_InitStruct.Pin = GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PC8 PC12 */
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PC9 PC10 PC11 */
  GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA8 PA10 */
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF10_OTG_FS;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PA9 */
  GPIO_InitStruct.Pin = GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PD0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF9_CAN1;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : PD2 */
  GPIO_InitStruct.Pin = GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : PD3 PD4 PD5 PD6 */
  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : PB3 PB4 PB5 */
  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF6_SPI3;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB8 PB9 */
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if(htim == &htim7) {
		//turn ra motor clockwise MIGHT HAVE TO SWITCH
		//HAL_GPIO_WritePin (GPIOF, GPIO_PIN_8, GPIO_PIN_SET);
		//turn off motors
		  HAL_GPIO_WritePin (GPIOF, GPIO_PIN_8, GPIO_PIN_SET);
		  HAL_GPIO_WritePin (GPIOF, GPIO_PIN_7, GPIO_PIN_SET);
		  HAL_GPIO_WritePin (GPIOF, GPIO_PIN_9, GPIO_PIN_SET);
		  HAL_GPIO_WritePin (GPIOG, GPIO_PIN_1, GPIO_PIN_SET);

		currentRAticks = 0;
		HAL_GPIO_WritePin (GPIOF, GPIO_PIN_8, GPIO_PIN_RESET);
		while(currentRAticks < 8){

		}
		HAL_GPIO_WritePin (GPIOF, GPIO_PIN_8, GPIO_PIN_SET); //turn motor off

	}


	if(htim == &htim17) {
		if(lst_minutes < 59){
			lst_minutes++;
		}
		else{
			lst_minutes = 0;
			if(lst_hours < 23){
				lst_hours++;
			}
			else{
				lst_hours = 0;
			}
		}
	}
}


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
