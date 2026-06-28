
#include "i2c_application.h"
#include "at32f435_437_board.h"
#define I2C_TIMEOUT                      0xFFFFFFF

//#define I2Cx_CLKCTRL                   0xB170FFFF   //10K
//#define I2Cx_CLKCTRL                   0xC0E06969   //50K
#define I2Cx_CLKCTRL                     0x80504C4E   //100K
//#define I2Cx_CLKCTRL                   0x30F03C6B   //200K

#define I2Cx_ADDRESS                     0xA0

#define I2Cx_PORT                        I2C2
#define I2Cx_CLK                         CRM_I2C2_PERIPH_CLOCK
#define I2Cx_DMA                         DMA1
#define I2Cx_DMA_CLK                     CRM_DMA1_PERIPH_CLOCK

#define I2Cx_SCL_GPIO_CLK                CRM_GPIOB_PERIPH_CLOCK
#define I2Cx_SCL_GPIO_PIN                GPIO_PINS_10
#define I2Cx_SCL_GPIO_PinsSource         GPIO_PINS_SOURCE10
#define I2Cx_SCL_GPIO_PORT               GPIOB
#define I2Cx_SCL_GPIO_MUX                GPIO_MUX_4

#define I2Cx_SDA_GPIO_CLK                CRM_GPIOB_PERIPH_CLOCK
#define I2Cx_SDA_GPIO_PIN                GPIO_PINS_11
#define I2Cx_SDA_GPIO_PinsSource         GPIO_PINS_SOURCE11
#define I2Cx_SDA_GPIO_PORT               GPIOB
#define I2Cx_SDA_GPIO_MUX                GPIO_MUX_4

void ic2_init(void);
uint8_t lm75_read(void);
extern i2c_handle_type hi2cx;
extern uint8_t eep_write_buf[16];
extern uint8_t eep_read_buf[16];
extern uint8_t lm75_buf[8];
void eep_write(uint16_t men_address, uint8_t *pdata,uint8_t size);
void eep_read(uint16_t men_address, uint8_t *pdata,uint8_t size);