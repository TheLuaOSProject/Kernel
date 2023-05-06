/**
 * Copyright (C) 2023 Amrit Bhogal
 *
 * This file is part of LuaOS.
 *
 * LuaOS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * LuaOS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LuaOS.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file ipc.h
 */

#include "common.h"
#include "lock.h"

#include "luck/memory/manager.h"

NONNULL_BEGIN

struct Message {
    struct Message *nullable next, *nullable previous;
    size_t length;
    byte data[];
};

struct Channel {
    struct Message *nullable read, *nullable write;
    size_t byte_count, byte_max;
    size_t message_count, message_max;
    Lock    lock;
};

static inline struct Channel channel_create(size_t byte_max, size_t message_max)
{
    return (struct Channel) {
        .byte_max = byte_max,
        .message_max = message_max,
    };
}

static inline void channel_destroy(struct Channel *nonnull channel)
{
    struct Message *nullable msg = channel->read;
    while (msg != nullptr) {
        struct Message *next = msg->next;
        kfree((struct Message *)msg, sizeof(struct Message) + msg->length);
        msg = next;
    }
}

/**
 * @brief Creates a new message
 * 
 * Creates a new message if @c head is a @c nullptr else creates the head of a new message list.
 *
 * @param head Current head or will be the new head.
 * @param length Length of the data.
 * @param data Contents of this message.
 *
 * @retval nullptr If memory could not be allocated for a new @c message else it returns a pointer to the new message.
 */
struct Message *nullable message_create(struct Message *nonnull *nullable head, size_t length, const byte data[static nonnull length]);

/**
 * @brief Adds a new message to the given channel.
 *
 * @param channel Channel to add the message to.
 * @param message Message to add to the channel.
 *
 * @retval int 
 *              - 0 If the message was added.
 *              - -1 If @c channel can't accomodate the size of @c message.
 */
int channel_send(struct Channel *nonnull channel, struct Message *message);

/**
 * @brief Recieves a message from the given channel.
 *
 * @param channel The channel to read from.
 *
 * @retval Message The message that was read from @c channel.
 */
struct Message *nullable channel_receive(struct Channel *nonnull channel);

NONNULL_END
