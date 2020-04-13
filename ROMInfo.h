#include <stdint.h>

using sbyte = int8_t;
using sword = int16_t;
using sdword = int32_t;
using sqword = int64_t;

using ubyte = uint8_t;
using uword = uint16_t;
using udword = uint32_t;
using uqword = uint64_t;


// 11-character name with padding, manufacturer code and CGB flag (newest ROMs)
struct GBTitle_11
{
	unsigned char title[11];
	ubyte padding[3];
	ubyte manufacturerCode;
	ubyte CGB_flag;
};

// 15-character name with CGB flag
struct GBTitle_15
{
	unsigned char title[15];
	char CGB_Flag[1];
};

// 16-character name (oldest ROMs)
struct GBTitle_16
{
	unsigned char title[16];
};

union CartTitle
{
	GBTitle_11 title11;
	GBTitle_15 title15;
	GBTitle_16 title16;
};

enum class eROMSize : ubyte
{
	eROMSize_32K = 0x00,  // 0 banks
	eROMSize_64K_4B = 0x01,
	eROMSize_128K_8B = 0x02,
	eROMSize_256K_16B = 0x03,
	eROMSize_512K_32B = 0x04,
	eROMSize_1024K_64B = 0x05,  // 1M
	eROMSize_2048K_128B = 0x06,  // 2M
	eROMSize_4096K_256B = 0x07,  // 4M
	eROMSize_8192K_512B = 0x08,  // 8M
	eROMSize_1152K_72B = 0x52,  // 1.1M
	eROMSize_1280K_80B = 0x53,  // 1.2M
	eROMSize_1536K_96B = 0x54   // 1.5M
};

enum class eRAMSize : ubyte
{
	eRAM_None = 0x00,
	eRAM_2K = 0x01,
	eRAM_8K = 0x02,
	eRAM_32K = 0x03,  // 4 banks of 8K
	eRAM_128b = 0x04,  // 16 banks of 8K
	eRAM_64Kb = 0x05   // 8 banks of 8K
};

enum class eDestCode : ubyte
{
	eDC_Japan = 0x00,
	eDC_Other = 0x01
};

struct stCartridgeInfo
{
	ubyte       padding[0x100];     // 256-bytes
	ubyte       entryAddr[0x04];    // Entry address (normally a NOP and JP 0150h)
	ubyte       logoBitmap[0x30];   // Nintendo logo bitmap
	CartTitle   cartridgeTitle;     // Title (or in other cases, title + manufacturer code + CGB flag)
	ubyte       licenseeCode[2];    // Licensee code (newer location)
	ubyte       sgbFlag;            // SGB flag (0x00 or 0x03)
	ubyte       cartType;           // Cartridge type
	eROMSize    romSize;            // Values denote ROM size (and number of banks)
	eRAMSize    ramSize;            // Values denote RAM size (and bank size/count)
	eDestCode   destinationCode;    // Destination: 0x00 = Japan / 0x01 = not Japan
	ubyte       licenseeCode_Old;   // Old (original) licensee code
	ubyte       maskROM_ver;        // Mask ROM (version)
	sbyte       headerChecksum;     // Checksum of header (0134-014C - from title to mask ROM version) using 'x=0:FOR i=0134h TO 014Ch: x=x-MEM[i]-1: NEXT'
	uword       globalChecksum;     // Global checksum (sum of all bytes --upper byte first-- of whole cartridge, excluding these 2 bytes)
};
