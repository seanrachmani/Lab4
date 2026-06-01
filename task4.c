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
    return count_digits(argv[1]);
}