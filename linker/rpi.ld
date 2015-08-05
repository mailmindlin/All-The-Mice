ENTRY(_start)
 
SECTIONS
{
    /* Starts at LOADER_ADDR. */
    . = 0x8000; /*turns out to be 32kb*/
    __start = .;
    __init_start = .;
    .init :
    {
    	*(.init)
    }
    __init_end=.;
    __text_start = .;
    .text :
    {
        KEEP(*(.text.boot))
        *(.text)
    }
    . = ALIGN(4096); /* align to page size */
    __text_end = .;
 
    __rodata_start = .;
    .rodata :
    {
        *(.rodata)
    }
    . = ALIGN(4096); /* align to page size */
    __rodata_end = .;
 
    __data_start = .;
    .data :
    {
        *(.data)
    }
    . = ALIGN(4096); /* align to page size */
    __data_end = .;
 
    __bss_start = .;
    .bss :
    {
        bss = .;
        *(.bss)
    }
    . = ALIGN(4096); /* align to page size */
    __bss_end = .;
    __exidx_start = .;
    .ARM.exidx   : { *(.ARM.exidx* .gnu.linkonce.armexidx.*) }
    __exidx_end = .;
    _HEAP_START = .;
    .heap :
    {
        . = 268435455;/*(1024^2 * 256) - 1; 256 mb*/
    }
    _HEAP_END = .;
    __end = .;
}