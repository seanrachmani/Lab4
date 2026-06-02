int count_digits(char* str) {
    int count = 0;
    
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] >= '0' && str[i] <= '9') {
            count++;
        }
        i++;
    }
    return count;
}


int main(int argc, char **argv) {
    //prevent segfault while input without string
    if(argc < 2){
        return -1;
    }
    return count_digits(argv[1]);
}