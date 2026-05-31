void memory_display() {
    static char* hex_formats[] = {"%#hhx\n", "%#hx\n", "No such unit", "%#x\n"};
    static char* dec_formats[] = {"%#hhd\n", "%#hd\n", "No such unit", "%#d\n"};
    
    int val = 0x5555;
    printf("Decimal:\n");
    printf(dec_formats[unit_size - 1], val); 
    printf("Hexadecimal:\n");
    printf(hex_formats[unit_size - 1], val);
}
