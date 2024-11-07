#pragma once
#include <base/di/SingletonGetter.h>
#include <bsp-interface/di/interrupt.h>
#include <DmaChannel.h>

namespace bsp
{
    class Dma1Channel5 :
        public bsp::DmaChannel
    {
    private:
        bool _is_open = false;

    public:
        static_function Dma1Channel5 &Instance();

        std::string Name() const override;
        void Open(bsp::IDmaOptions const &options, void *parent) override;

        bool IsOpen() const override
        {
            return _is_open;
        }

        void Close() override
        {
            _is_open = false;
        }
    };
} // namespace bsp
