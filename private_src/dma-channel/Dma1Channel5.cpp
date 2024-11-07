#include "Dma1Channel5.h"
#include "DmaOptions.h"

bsp::Dma1Channel5 &bsp::Dma1Channel5::Instance()
{
    class Getter :
        public base::SingletonGetter<Dma1Channel5>
    {
    public:
        std::unique_ptr<Dma1Channel5> Create() override
        {
            return std::unique_ptr<Dma1Channel5>{new Dma1Channel5{}};
        }

        void Lock() override
        {
            DI_InterruptSwitch().DisableGlobalInterrupt();
        }

        void Unlock() override
        {
            DI_InterruptSwitch().EnableGlobalInterrupt();
        }
    };

    Getter g;
    return g.Instance();
}

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
    LinkDmaToUartRx(*static_cast<UART_HandleTypeDef *>(parent));
}
