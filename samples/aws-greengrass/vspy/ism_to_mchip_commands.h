/*
 * Contains definitions pertaining to commands issued by ISM Chip to instruct the
 * main chip to perform certain tasks
 */

#ifndef ISM_TO_MCHIP_COMMANDS_H_
#define ISM_TO_MCHIP_COMMANDS_H_

#define ISM_CMD_CTRL_LED_COLOR (0x01)

typedef struct _sfifoISMChipLEDControl
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t reserved[5];
} sfifoISMChipLEDControl;

#endif /* ISM_TO_MCHIP_COMMANDS_H_ */
