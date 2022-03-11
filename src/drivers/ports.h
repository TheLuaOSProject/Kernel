//
// Created by Frityet on 2022-02-08.
//

#ifndef LUAOS_PORTS_
#define LUAOS_PORTS_

#include <luaos_types.h>

/**
 * @brief Gets a byte from the specified port
 * 
 * @param port Port to get from
 * @return u8_t - Byte returned from the port
 */
extern byte_t PORT_IN(word_t port);

/**
 * @brief Sends a byte to a port
 * 
 * @param port Port to send data to
 * @param data Data to send
 */
extern void PORT_OUT(word_t port, byte_t data);

/**
 * @brief Gets a word from the specified port
 * 
 * @param port Port to get from
 * @return u16_t - Word returned from the port
 */
extern word_t PORT_WORD_IN(byte_t port);

/**
 * @brief Sends a word to the specified port
 * 
 * @param port Port to send data to
 * @param data Data to send
 */
extern void PORT_WORD_OUT(word_t port, word_t data);

#endif //LUAOS_PORTS_
