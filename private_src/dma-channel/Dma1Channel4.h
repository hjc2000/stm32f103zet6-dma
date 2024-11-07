#pragma once
#include <base/define.h>
#include <base/di/SingletonGetter.h>
#include <bsp-interface/di/interrupt.h>
#include <DmaChannel.h>

namespace bsp
{
    class Dma1Channel4 :
        public bsp::DmaChannel
    {
    private:
        bool _is_open = false;

    public:
        static_function Dma1Channel4 &Instance();

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
