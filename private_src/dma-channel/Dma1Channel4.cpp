#include "Dma1Channel4.h"
#include "DmaOptions.h"

bsp::Dma1Channel4 &bsp::Dma1Channel4::Instance()
{
    class Getter :
        public base::SingletonGetter<Dma1Channel4>
    {
    public:
        std::unique_ptr<Dma1Channel4> Create() override
        {
            return std::unique_ptr<Dma1Channel4>{new Dma1Channel4{}};
        }

        void Lock() override
        {
            DI_DisableGlobalInterrupt();
        }

        void Unlock() override
        {
            DI_EnableGlobalInterrupt();
        }
    };

    Getter g;
    return g.Instance();
}

std::string bsp::Dma1Channel4::Name() const
{
    return "dma1_channel4";
}

void bsp::Dma1Channel4::Open(bsp::IDmaOptions const &options, void *parent)
{
    if (_is_open)
    {
        throw std::runtime_error{"已经打开，要先关闭才能再次打开"};
    }

    _is_open = true;

    __HAL_RCC_DMA1_CLK_ENABLE();
    _dma_handle.Instance = DMA1_Channel4;
    _dma_handle.Init = static_cast<bsp::DmaOptions const &>(options);
    HAL_DMA_Init(&_dma_handle);

    // DMA1_Channel4 只能用来进行串口发送
    LinkDmaToUartTx(*static_cast<UART_HandleTypeDef *>(parent));
}
