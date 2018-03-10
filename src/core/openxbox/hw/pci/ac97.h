#pragma once

#include <cstdint>

#include "../defs.h"
#include "pci.h"

namespace openxbox {

class AC97Device : public PCIDevice {
public:
    // constructor
	AC97Device();

    // PCI Device functions
    void Init();
    void Reset();

    uint32_t IORead(int barIndex, uint32_t port, unsigned size);
    void IOWrite(int barIndex, uint32_t port, uint32_t value, unsigned size);
    uint32_t MMIORead(int barIndex, uint32_t addr, unsigned size);
    void MMIOWrite(int barIndex, uint32_t addr, uint32_t value, unsigned size);
};

}