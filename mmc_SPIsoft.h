#ifndef MMC_SPI_H
#define	MMC_SPI_H

#define CMD0            0
#define CMD1            1
#define READ_MMC        17
#define WRITE_MMC       24
#define SET_BLOCKLEN    16
#define CMD_08          8
#define CMD_77          77
#define CMD_69          69

void command_mmc(char, char, char, char, char);
void mmc_init(void);
void Read_point_mmc(unsigned long dir);
void savePosBufferSd(unsigned int);
void Read_image_mmc(long int, char, char, char, char, char);
void Write_image_mmc(long int);
void Clean_block_mmc(unsigned long dir, unsigned long cant_char);
void Write_page(unsigned long dir, char clean);
void Read_page(unsigned long dir);
void wakeUpSD(void);

#endif	/* MMC_SPI_H */


//#define CMD0            0x40
//#define CRC_CMD0        0x95
//
//#define CMD1            0x41
//#define CRC_CMD1        0xF9
//
//#define READ_MMC        0x51
//#define CRC_READ        0xFF
//
//#define WRITE_MMC       0x58
//#define CRC_WRITE       0xFF
//#define SET_BLOCKLEN    0x50
//#define CMD_08          0x48
//#define CRC_CMD08       0x87
//
//#define CMD_77          77
//#define CMD_69          69
