/**
 * @file    ports.h
 * @author  Amrit Bhogal (@Frityet)
 * @brief   Interface with the ports of the computer
 * @version 1.0
 * @date    2021-11-24
 * 
 * @copyright Copyright Amrit Bhogal(c) 2021
 * 
 */

#ifndef LUAOS_PORTS
#define LUAOS_PORTS

#include <common.h>

/**
 * @brief Gets a byte from the specified port
 * 
 * @param port Port to get from
 * @return u8_t - Byte returned from the port
 */
uint8_t port_in(uint16_t port);

/**
 * @brief Sends a byte to a port
 * 
 * @param port Port to send data to
 * @param data Data to send
 */
void port_out(uint16_t port, uint8_t data);

/**
 * @brief Gets a word from the specified port
 * 
 * @param port Port to get from
 * @return u16_t - Word returned from the port
 */
uint16_t port_inw(uint16_t port);

/**
 * @brief Sends a word to the specified port
 * 
 * @param port Port to send data to
 * @param data Data to send
 */
void port_outw(uint16_t port, uint16_t data);

#endif //LUAOS_PORTS
