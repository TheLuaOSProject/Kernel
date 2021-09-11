//
// Created by Frityet on 2021-09-10.
//

#include "display.h"

uint16_t    get_cursor_offset(void);

void        set_cursor_offset(uint16_t offset);

uint16_t    printchar(char      chr, 
                      uint16_t  col, 
                      uint16_t  row,
                      char      attr);

uint16_t    get_offset(uint16_t col, uint16_t row);

uint16_t    get_row_offset(uint16_t offset);

uint16_t    get_col_offset(uint16_t offset);

void clear_screen(void)
{
    
}

void kernel_print(string_t msg)
{
    
}

void kernel_print_at(string_t msg, uint16_t col, uint16_t row)
{
    
}



uint16_t get_offset(uint16_t col, uint16_t row)
{
    return (2 * row * MAX_COLUMNS + col);
}

uint16_t get_col_offset(uint16_t offset)
{
    return (offset - (get_row_offset(offset) * 2 * MAX_COLUMNS)) / 2;
}

uint16_t get_row_offset(uint16_t offset)
{
    return (offset / (2 * MAX_COLUMNS));
}