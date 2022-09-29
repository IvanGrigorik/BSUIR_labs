#include <sys/io.h>
#include <stdint.h>
#include <stdio.h>

const uint32_t PCI_ENABLE_BIT = 0x80000000;
const uint32_t PCI_CONFIG_ADDRESS = 0xCF8;
const uint32_t PCI_CONFIG_DATA = 0xCFC;

uint32_t r_pci_32(uint8_t bus, uint8_t device, uint8_t func, uint8_t pci_reg) {
    // unsigned long flags;
    // local_irq_save(flags)

    outl(PCI_ENABLE_BIT | (bus << 16) | (device << 11) | (func << 8) | (pci_reg << 2), PCI_CONFIG_ADDRESS);
    uint32_t ret = inl(PCI_CONFIG_DATA);

    // local_irq_restore(flags);
    return ret;
}

int main() {

    iopl(3);

    uint8_t bus, device, func;
    uint32_t data;

    for (bus = 0; bus != 0xFF; bus++) {
        for (device = 0; device < 32; device++) {
            for (func = 0; func < 8; func++) {

                data = r_pci_32(bus, device, func, 0);
                if (data != 0xFFFFFFFF) {
                    uint32_t vendorID = data % 0x10000;
                    uint32_t deviceID = (data - vendorID) / 0x10000;
                    printf("bus %d, device 0x%04x, func %d: vendor=0x%04x\n", bus, deviceID, func, vendorID);
                }
            }
        }
    }
}