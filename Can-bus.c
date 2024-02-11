#include "stm32f4xx_hal.h"

// CAN handle
CAN_HandleTypeDef hcan;

// Message data
uint8_t tx_data[8] = {1, 2, 3, 4, 5, 6, 7, 8}; // Replace with your data

// Initialize CAN peripheral
void MX_CAN_Init(void) {
  hcan.Instance = CAN1; // Change to your specific CAN peripheral

  hcan.Init.Prescaler = 16; // Adjust based on desired baud rate
  hcan.Init.Mode = CAN_MODE_NORMAL;
  hcan.Init.Type = CAN_TYPE_STANDARD;
  hcan.Init.SJW = CAN_SJW_1TQ;
  hcan.Init.BS1 = CAN_BS1_6TQ;
  hcan.Init.BS2 = CAN_BS2_5TQ;
  hcan.Init.TTCM = DISABLE;
  hcan.Init.ABOM = DISABLE;
  hcan.Init.AWUM = DISABLE;
  hcan.Init.NART = DISABLE;
  hcan.Init.RFLM = DISABLE;
  hcan.Init.TXFIFOQueueMode = DISABLE;

  HAL_CAN_Init(&hcan);
}

// Transmit a CAN message
void send_can_message(uint32_t id) {
  CAN_TxHeaderTypeDef tx_header;

  tx_header.StdId = id; // Set your desired CAN ID
  tx_header.TransmitMode = CAN_MODE_NORMAL;
  tx_header.DLC = 8; // Data length

  if (HAL_CAN_Transmit(&hcan, &tx_header, tx_data, 100) != HAL_OK) { // 100ms timeout
    // Error handling
  }
}

// Example usage
int main(void) {
  MX_CAN_Init();

  while (1) {
    send_can_message(0x123); // Replace with your message ID
    HAL_Delay(1000); // Delay between messages
  }
}
