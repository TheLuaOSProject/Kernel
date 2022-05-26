#pragma once

#define function(name)  .global name\
                        .type   name, @function\
                        name
