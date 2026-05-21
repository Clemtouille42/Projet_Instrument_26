#include "code.h"

uint8_t I2C_Scan(I2C_HandleTypeDef *hi2c) {
    HAL_StatusTypeDef res;

    for (uint8_t i = 1; i < 128; i++) {
        // Test de l'adresse
        res = HAL_I2C_IsDeviceReady(hi2c, (uint16_t)(i << 1), 3, 10);

        if (res == HAL_OK) {
            return i; // Retourne l'adresse trouvée
        }
    }
    return 0; // Aucun périphérique trouvé
}
