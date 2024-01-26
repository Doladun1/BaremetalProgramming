#include "i2c0.h"
#include <MKL25Z4.h>
#include <stdint.h>
#include <stdbool.h>
static void i2c0_do_start();
static void i2c0_do_stop();
static void i2c0_config_tx_mode();
static void i2c0_config_rx_mode();
static void i2c0_do_repeat_start();
static _Bool i2c0_last_transfer_is_complete();
static void i2c0_put_byte(uint8_t data);
static uint8_t i2c0_get_byte();
static _Bool i2c0_is_busy();
static void wait_for_transmission_complete();
static _Bool i2c0_ack_not_received();
static void i2c0_nak_after_byte();

void initialize_i2c0()
{
    //clock gating
    SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;
    SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;

    PORTE->PCR [24] = (PORTE->PCR[24] & ~(PORT_PCR_MUX_MASK)) | PORT_PCR_MUX(5);
    PORTE->PCR [25] = (PORTE->PCR[25] & ~(PORT_PCR_MUX_MASK)) | PORT_PCR_MUX(5);
    I2C0->F = I2C_F_ICR(15) | I2C_F_MULT(0);//mult determines mult of divider
    //ICR determines sda hold, scl hold(start), scl hold(stop)
    //must match device being used(acceleramator)

    I2C0->C1 |= I2C_C1_IICEN_MASK;
}

uint8_t i2c0_read_byte(uint8_t device, uint8_t reg)
{
    while(i2c0_is_busy());//gaurantees idle
    i2c0_config_tx_mode();
    i2c0_do_start();//start bit
    i2c0_put_byte(device);//since its write we need a 0 at lsb
    //transmit device
    wait_for_transmission_complete();
    //should instead be in interrupt or some non blocking method
    //should check for ACK, if not sends to stop bit(goto END)
    if (i2c0_ack_not_received())
    {goto END;}

    i2c0_put_byte(reg); //transmit register
    wait_for_transmission_complete();
    //should check for ack
    if (i2c0_ack_not_received())
    {goto END;}

    i2c0_do_repeat_start();//do restart
    i2c0_put_byte(device|0x01);//1 for read
    wait_for_transmission_complete();
    //should check for ack
    if (i2c0_ack_not_received())
    {goto END;}

    i2c0_config_rx_mode();//change to receive mode
    i2c0_get_byte(); //read data
    //I2C0-> C1 |= I2C_C1_TXAK_MASK;
    i2c0_nak_after_byte();
    wait_for_transmission_complete();

    // //should check for ACK
    // if (i2c0_ack_not_received())
    // {goto END}
    i2c0_config_tx_mode();
    i2c0_do_stop();//stop bit
    return i2c0_get_byte();
END:i2c0_config_tx_mode();
    i2c0_do_stop();//stop bit
    return false;

}

uint8_t i2c0_write_byte(uint8_t device, uint8_t reg,uint8_t data)
{
    while(i2c0_is_busy());//gaurantees idle
    i2c0_config_tx_mode();
    i2c0_do_start();//start bit
    i2c0_put_byte(device);//since its write we need a 0 at lsb
    wait_for_transmission_complete();
    if (i2c0_ack_not_received())
    {goto END;}
    i2c0_put_byte(reg); //transmit register
    wait_for_transmission_complete();
    if (i2c0_ack_not_received())
    {goto END;}
    i2c0_put_byte(data);//transmit data
    wait_for_transmission_complete();
    if (i2c0_ack_not_received())
    {goto END;}
    i2c0_do_stop();
END:i2c0_do_stop();//stop bit
    return false;
}

static void wait_for_transmission_complete()
{
    while(!i2c0_last_transfer_is_complete());//wait for entire transmit to complete
    I2C0->S |= I2C_S_IICIF_MASK;//clear interrupt so flag can be detected
}

static _Bool i2c0_is_busy()
{
    return I2C0->S & I2C_S_BUSY_MASK;
}

static _Bool i2c0_ack_not_received()
{
    return I2C0->S & I2C_S_RXAK_MASK;
}

static void i2c0_do_start()
{
    I2C0->C1 |= I2C_C1_MST_MASK;//switching to master is start bit
}

static void i2c0_do_repeat_start()
{
    I2C0->C1 |= I2C_C1_RSTA_MASK;//enable repeat start
}

static void i2c0_do_stop()
{
    I2C0->C1 &= ~I2C_C1_MST_MASK;//switching to slave is stop bit
}

static void i2c0_config_tx_mode()
{
    I2C0->C1 |= I2C_C1_TX_MASK;//setting TX bit changes mode to transmit
}

static void i2c0_config_rx_mode()
{
    I2C0->C1 &= ~I2C_C1_TX_MASK;//clearing RX bit changes mode to Receive
}

static _Bool i2c0_last_transfer_is_complete()
{
    return I2C0->S & I2C_S_IICIF_MASK;//notifies when transfer is complete
}

static void i2c0_put_byte(uint8_t data)
{
    I2C0->D=data;
}

static uint8_t i2c0_get_byte()
{
   return I2C0->D;
}

static void i2c0_nak_after_byte()
{
    I2C0-> C1 |= I2C_C1_TXAK_MASK;
}
