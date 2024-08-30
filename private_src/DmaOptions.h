#pragma once
#include <bsp-interface/di/dma.h>
#include <hal.h>

namespace bsp
{
    /// @brief DMA 选项
    class DmaOptions :
        public bsp::IDmaOptions
    {
    private:
        DMA_InitTypeDef _init_type_def;
        std::string _request;

    public:
        DmaOptions();

        operator DMA_InitTypeDef() const;

        /// @brief DMA 拷贝数据的方向。
        /// @return
        IDmaOptions_Direction Direction() const override;
        void SetDirection(IDmaOptions_Direction value) override;

        /// @brief DMA 拷贝数据的过程中，是否自动递增外设数据指针。
        /// @return 返回 true 表示递增，返回 false 表示不递增。
        bool PeripheralIncrement() const override;
        void SetPeripheralIncrement(bool value) override;

        /// @brief DMA 拷贝数据的过程中，是否自动递增内存数据指针。
        /// @return 返回 true 表示递增，返回 false 表示不递增。
        bool MemoryIncrement() const override;
        void SetMemoryIncrement(bool value) override;

        /// @brief 外设数据对齐的字节数
        /// @return
        int PeripheralDataAlignment() const override;
        void SetPeripheralDataAlignment(int value) override;

        /// @brief 内存数据对齐的字节数。
        /// @return
        int MemoryDataAlignment() const override;
        void SetMemoryDataAlignment(int value) override;

        /// @brief DMA 优先级。
        /// @return
        IDmaOptions_Priority Priority() const override;
        void SetPriority(IDmaOptions_Priority value) override;

        /// @brief DMA 的用途。
        /// @return
        std::string Request() const override
        {
            // f103 的 DMA 通道与具体的外设绑死，所以无法自定义 DMA 的用途，所以本参数无用。
            return _request;
        }

        /// @brief DMA 的用途。
        /// @param value
        void SetRequest(std::string value) override
        {
            // f103 的 DMA 通道与具体的外设绑死，所以无法自定义 DMA 的用途，所以本参数无用。
            _request = value;
        }
    };
} // namespace bsp
