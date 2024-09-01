#include "DmaChannel.h"

void bsp::DmaChannel::LinkDmaToUartTx(UART_HandleTypeDef &uart)
{
    uart.hdmatx = &_dma_handle;
    _dma_handle.Parent = &uart;
}

void bsp::DmaChannel::LinkDmaToUartRx(UART_HandleTypeDef &uart)
{
    uart.hdmarx = &_dma_handle;
    _dma_handle.Parent = &uart;
}
