#ifndef LCDMANAGER_H
#define LCDMANAGER_H

#include <stdint.h>

#ifdef __cplusplus
 extern "C" {
#endif

void LCDManager_SendFrameBufferBlockWithPosition(uint8_t* pixels, uint16_t x, uint16_t y, uint16_t w, uint16_t h);
uint32_t LCDManager_IsTransmittingData(void);
void LCDManager_TransferComplete();

#ifdef __cplusplus
}
#endif

#endif //LCDMANAGER_H
