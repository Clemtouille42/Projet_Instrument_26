#ifndef CODE_H
#define CODE_H

#include "main.h"

// On retire le paramètre UART pour éviter l'erreur de type
uint8_t I2C_Scan(I2C_HandleTypeDef *hi2c);

#endif /* CODE_H */
