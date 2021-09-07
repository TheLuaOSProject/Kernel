#ifndef LUAOS_PORTS
#define LUAOS_PORTS

#include "../types.h"

/**
 * @brief Gets a byte from the specified port
 * 
 * @param port Port to get from
 * @return u8_t - Byte returned from the port
 */
u8_t port_in(u16_t port);

/**
 * @brief Sends a byte to a port
 * 
 * @param port Port to send data to
 * @param data Data to send
 */
void port_out(u16_t port, u8_t data);

/**
 * @brief Gets a word from the specified port
 * 
 * @param port Port to get from
 * @return u16_t - Word returned from the port
 */
u16_t wport_in(u16_t port);

/**
 * @brief Writes a word to the specified port
 * 
 * @param port Port to send data to
 * @param data Data to send
 */
void wport_out(u16_t port, u16_t data);

#endif //LUAOS_PORTS