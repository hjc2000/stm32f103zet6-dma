#include "Dma1Channel5.h"
#include "DmaOptions.h"
#include "LinkDma.h"

std::string bsp::Dma1Channel5::Name() const
{
    return "dma1_channel5";
}

void bsp::Dma1Channel5::Open(bsp::IDmaOptions const &options, void *parent)
{
    if (_is_open)
    {
        throw std::runtime_error{"已经打开，要先关闭才能再次打开"};
    }

    _is_open = true;

    __HAL_RCC_DMA1_CLK_ENABLE();
    _dma_handle.Instance = DMA1_Channel5;
    _dma_handle.Init = static_cast<bsp::DmaOptions const &>(options);
    HAL_DMA_Init(&_dma_handle);

    // DMA1_Channel5 只能用来进行串口接收
    bsp::LinkDmaToUartRx(_dma_handle, *static_cast<UART_HandleTypeDef *>(parent));
}
