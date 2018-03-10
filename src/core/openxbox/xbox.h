#pragma once

#include <assert.h>
#ifndef _WIN32
	#include <libgen.h>
#endif
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "openxbox/cpu.h"
#include "openxbox/dev.h"
#include "openxbox/emulator.h"
#include "openxbox/gdbserver.h"
#include "openxbox/log.h"
#include "openxbox/mem.h"
#include "openxbox/util.h"
#include "openxbox/xbe.h"
#include "openxbox/thread.h"
#include "openxbox/settings.h"

#include "openxbox/hw/i8254.h"
#include "openxbox/hw/smbus.h"
#include "openxbox/hw/pcibus.h"
#include "openxbox/hw/smc.h"
#include "openxbox/hw/mcpx.h"
#include "openxbox/hw/mcpx_ram.h"
#include "openxbox/hw/lpc.h"
#include "openxbox/hw/agp.h"
#include "openxbox/hw/eeprom.h"
#include "openxbox/hw/nvnet.h"
#include "openxbox/hw/tvenc.h"

#include "openxbox/cpu_module.h"

namespace openxbox {

/*!
 * Top-level Xbox machine class
 *
 * This class is the top-level class, will perform initialization and high-level
 * management of the overall emulation flow.
 */
class Xbox : Emulator, IOMapper {
protected:
	// ----- Modules ----------------------------------------------------------
	IOpenXBOXCPUModule * m_cpuModule;

	// ----- Hardware ---------------------------------------------------------
	Cpu             *m_cpu;
	char            *m_ram;
	char            *m_rom;
	MemoryRegion    *m_memRegion;
	
    i8254           *m_i8254;

    SMBus           *m_SMBus;
    SMCDevice       *m_SMC;
    EEPROMDevice    *m_EEPROM;
    TVEncoderDevice *m_TVEncoder;

    PCIBus          *m_PCIBus;
    MCPXRAMDevice   *m_MCPXRAM;
    LPCDevice       *m_LPC;
    NVNetDevice     *m_NVNet;
    AGPDevice       *m_AGPBridge;

    // TODO: move to TV encoder device
    int m_field_pin = 0;

    // ----- Configuration ----------------------------------------------------
    OpenXBOXSettings *m_settings;

	// ----- State ------------------------------------------------------------
	bool m_should_run;

	// ----- Debugger ---------------------------------------------------------
	GdbServer *m_gdb;

public:
	Xbox(IOpenXBOXCPUModule *cpuModule);
	~Xbox();
	int Initialize(OpenXBOXSettings *settings);

	void InitializePreRun();
	void Cleanup();

	int Run();
	int RunCpu();
	void Stop();

    // IOMapper implementation
    void IORead(uint32_t addr, uint32_t *value, uint16_t size);
    void IOWrite(uint32_t addr, uint32_t value, uint16_t size);

    void MMIORead(uint32_t addr, uint32_t *value, uint8_t size);
    void MMIOWrite(uint32_t addr, uint32_t value, uint8_t size);
};

}
