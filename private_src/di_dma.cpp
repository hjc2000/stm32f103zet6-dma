#include "Dma1Channel4.h"
#include "Dma1Channel5.h"
#include "DmaOptions.h"
#include <base/container/Dictionary.h>
#include <base/di/SingletonGetter.h>
#include <bsp-interface/di/dma.h>
#include <bsp-interface/di/interrupt.h>
#include <map>

std::shared_ptr<bsp::IDmaOptions> DICreate_DmaOptions()
{
    return std::shared_ptr<bsp::IDmaOptions>{new bsp::DmaOptions{}};
}

base::IDictionary<std::string, bsp::IDmaChannel *> const &DI_DmaChannelCollection()
{
    class Initializer
    {
    private:
        Initializer()
        {
            Add(&bsp::Dma1Channel4::Instance());
            Add(&bsp::Dma1Channel5::Instance());
        }

        void Add(bsp::IDmaChannel *o)
        {
            _collection.Add(o->Name(), o);
        }

    public:
        base::Dictionary<std::string, bsp::IDmaChannel *> _collection;

        static_function Initializer &Instance()
        {
            class Getter :
                public base::SingletonGetter<Initializer>
            {
            public:
                std::unique_ptr<Initializer> Create() override
                {
                    return std::unique_ptr<Initializer>{new Initializer{}};
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
    };

    return Initializer::Instance()._collection;
}
