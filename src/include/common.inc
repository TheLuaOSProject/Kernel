///
///@file common.inc
///@author Amrit Bhogal
///@version 1.0.0 - Amrit Bhogal on 2022-05-26
///

#pragma once

#define function(name)  .global name\
                        .type   name, @function\
                        name
