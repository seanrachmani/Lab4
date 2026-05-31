#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/*
For this part,
use an array of structs with 
the above menu names 
and pointers to appropriate functions that implement each option,
using the same menu scheme from lab 1.
*/
struct fun_desc {
char *name;
char index;
//field named fun which is a pointer to function that has no parmas and its return value void:
void (*fun)();
};

//You should keep important state variables of your program as global variables, including:
//debug mode off by default:
char debug_mode = 0;
char file_name[128] = "";
int unit_size = 1;
unsigned char mem_buf[10000];
size_t mem_count = 0;
//for 1b: toggle diplay mode
char display_mode = 0; // 0 for hex(default), 1 for decimal



/*
======================================menu functions==========================================
*/

void toggle_debug_mode() {
    if(debug_mode == 0) { 
        debug_mode = 1;
        fprintf(stderr, "Debug flag now on\n");
    }
    else{
        debug_mode = 0;
        fprintf(stderr, "Debug flag now off\n");
    }
    


}

/*
Set File Name queries the user for a file name, 
and stores it in file_name. 
You may assume that the file name is no longer than 100 characters.
 If debug mode is on, the function should also print (to stderr, as are all debug messages):
  "Debug: file name set to 'file_name' " (obviously, replacing 'file_name' with the actual name).
*/

void set_file_name() {
    fprintf(stdout, "Enter File Name\n");
    if(fgets(file_name, sizeof(file_name), stdin) != NULL){
        //getting rid of \n charcter by replacing it in null:
        int len = strlen(file_name);
        if (len > 0 && file_name[len - 1] == '\n') {
            file_name[len - 1] = '\0'; 
        }
        if(debug_mode){
        fprintf(stderr,"Debug: file name set to:%s",file_name);
        }
    }
}

/*
Set Unit Size option sets the size variable. The steps are:
Prompt the user for a number.
If the value is valid (1, 2, or 4), set the size variable accordingly.
If debug mode is on, print "Debug: set size to x", with x the appropriate size.
If not valid, print an error message and leave unit_size unchanged.
*/
void set_unit_size() {
    char buffer[50];
    int temp_size;
    fprintf(stdout, "Enter Unit Size:\n");
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        //lloking for the num in the buffer which is the user input and put it in temp_size
        sscanf(buffer, "%d", &temp_size); 
        //. Size can be either 1, 2 or 4, with 1 as the default.
        if (temp_size == 1 || temp_size == 2 || temp_size == 4) {
            unit_size = temp_size;
            if (debug_mode) {
                fprintf(stderr, "Debug: set size to %d\n", unit_size);
            }
        }
        else {
            fprintf(stderr, "Invalid unit size\n"); // 
        }
    }
}



void load_into_memory() {
    //check if file name is empty
    if (strcmp(file_name, "") == 0) {
        fprintf(stderr, "Error: file name is empty\n");
        return;
    }

    //open file for reading
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: cannot open file\n");
        return;
    }

    //prompt user for location and length
    char buffer[50];
    unsigned int location;
    int length;
    fprintf(stdout, "Please enter <location> <length>\n");
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        //search input: %x for hex location, %d for decimal length, put it in variables
        sscanf(buffer, "%x %d", &location, &length);
        //if debug flag is on, print the file_name, as well as location, and length to stderr.
        if (debug_mode) {
            fprintf(stderr, "Debug: file_name=%s, location=%X, length=%d\n", file_name, location, length);
        }


        /*
        requiremnet: Copy length * unit_size bytes from file_name starting at position location into mem_buf:
        1.location is user input and tell us where to start our copy, like putting the mouse in the right line of the file
        2.mem buf is global to save the info we copy
        unit size is how many bytes each unit, length is how much units,
        so we need length * unit_size bytes (the system calls needs )
        */
        //1.Seek the specified location in the file. seek_set is to start from first byte
        fseek(file, location, SEEK_SET);

        //NOW WE CAN READ FROM RIGHT PLACE:
        //2.Read from file directly into mem_buf using fread
        //fread(where to store, size of each, total numbers of elements, wehre to read from)
        fread(mem_buf, unit_size, length, file);
        
        // Update the global mem_count so we know how many bytes are currently in memory
        mem_count = length * unit_size; 

        fprintf(stdout, "Loaded %d units into memory\n", length);
    }

    //close the file!
    fclose(file);
}


/*
default is hexa aka 0 aka off
display mode == 1 aka decimal aka on 
*/
void toggle_display_mode() {
    if (display_mode == 0) {
        display_mode = 1;
        fprintf(stdout, "Decimal display flag now on, decimal representation\n");
    }
    else {
        display_mode = 0;
        fprintf(stdout, "Decimal display flag now off, hexadecimal representation\n");
    }
}



void memory_display() {
    char buffer[50];
    unsigned int addr; //offset
    int u; // length

    fprintf(stdout, "Enter address and length\n");
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        //offset (resp. addr) in hexadecimal x, u will be given in decimal d
        sscanf(buffer, "%x %d", &addr, &u);

        //taken code from lab instructions(for short choose of print format(1,2,4) )
        static char* hex_formats[] = {"%#hhx\n", "%#hx\n", "No such unit", "%#x\n"};
        static char* dec_formats[] = {"%#hhd\n", "%#hd\n", "No such unit", "%#d\n"};
        //end of taken code

        //output print according to lab example
        if (display_mode == 1) {
            fprintf(stdout, "Decimal\n=======\n");
        } else {
            fprintf(stdout, "Hexadecimal\n===========\n");
        }

        
        unsigned char* ptr;
        if (addr == 0) {
            //Entering a value of 0 for addr is a special case, in which the memory to be displayed starts at the beginning of your mem_bu
            ptr = mem_buf;
        }
        else {
            ///user input
            ptr = (unsigned char*)addr;
        }

        //displays u units of size unit_size starting at a given address addr in memory.
        for (int i = 0; i < u; i++) {
            //taken code from units.c
            //(*int) will be pointer for only 4 bytes, and then another * for the adrees value which is data of the file in this address which in this case is *sometimes* addreses itself 
            //the hex/dec formats array will handle 1/2/4
            int var = *((int*)(ptr));
            //end of taken code

            if (display_mode == 1) {
                printf(dec_formats[unit_size - 1], var);
            } 
            else {
                printf(hex_formats[unit_size - 1], var);
            }
            
            //ptr arithmetic. unsigned char is one bytes so +1 is for one byte but we need to skip the bytes we just printed according to unit size
            ptr += unit_size;
        }
    }
}











void save_into_file() {
    //Check if file name is empty like before
    if (strcmp(file_name, "") == 0) {
        fprintf(stderr, "Error: file name is empty\n");
        return;
    }

    //open file for reading AND writing ("r+")
    FILE *file = fopen(file_name, "r+");
    if (file == NULL) {
        fprintf(stderr, "Error: cannot open file for writing\n");
        return;
    }

    // prompt user for addresses and length
    char buffer[100];
    unsigned int source_address; //(source virtual memory address, in hexadecimal) where to start the copy from
    unsigned int target_location; //target file offset, in hexadecimal) for file name saved. in this file we put other info
    int length;//(number of units, in decimal).
    
    fprintf(stdout, "Please enter <source-address> <target-location> <length>\n");
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        // %x for hex addresses, %d for decimal length
        sscanf(buffer, "%x %x %d", &source_address, &target_location, &length);
        
        //check where we are copying from (just like in memory_display aka special case)
        unsigned char* ptr;
        if (source_address == 0) {
            ptr = mem_buf;
        } 
        else {
            ptr = (unsigned char*)source_address;
        }

        //If <target-location> is greater than the size of <file_name> you should print an error message and not copy anything.
        //GO TO THE END TO SEE THE LENTH
        fseek(file, 0, SEEK_END);
        long file_size = ftell(file); //ftell is the distance from the start in bytes which is file size
        
        if (target_location > file_size) {
            fprintf(stderr, "Error: target location is strictly greater than file size\n");
            fclose(file);
            return; 
        }




        //we copy from hexeditplus virtual memory(sorce) to file offset(traget with saved file name)
        //seek the specified target location in the file
        fseek(file, target_location, SEEK_SET);

        //write to file directly from our pointer using fwrite
        fwrite(ptr, unit_size, length, file);
        
        fprintf(stdout, "Saved %d units into file\n", length);
    }
    fclose(file);
}











void memory_modify() {
    printf("Not implemented yet\n");
}

void quit() {
    if (debug_mode) {
        fprintf(stderr, "quitting\n");
    }
    exit(0);
}

/*
======================================menu functions==========================================
*/


struct fun_desc menu1[] = { 
    { "Toggle <D>ebug Mode", 'D', toggle_debug_mode }, 
    { "Set <F>ile Name", 'F', set_file_name }, 
    { "Set <U>nit Size", 'U', set_unit_size }, 
    { "<L>oad Into Memory", 'L', load_into_memory }, 
    { "<T>oggle Display Mode", 'T', toggle_display_mode }, 
    { "<M>emory Display", 'M', memory_display }, 
    { "<S>ave Into File", 'S', save_into_file }, 
    { "Memory Modif<y>", 'y', memory_modify }, 
    { "<Q>uit", 'Q', quit }, 
    { NULL, 0, NULL } 
};

void menu(){
    while(feof(stdin)==0){//we have more 
        //When the debug mode is on, you should print the value of the variables: unit_size, file_name, and mem_count, every time just before the menu is printed:
        if(debug_mode){
            fprintf(stderr, "Unit size: %d\n", unit_size);
            fprintf(stderr, "File name: %s\n", file_name);
            fprintf(stderr, "Mem count: %zu\n", mem_count);
        }
        fprintf(stdout,"Choose action:\n");
        int idx=0;
        while(menu1[idx].fun!=NULL){
            printf("%s\n",menu1[idx].name);
            idx++;
        }
        //code taken from tutorialsPoint:
        char buffer[50]; //array of chars
        fgets(buffer, sizeof(buffer), stdin);
        //end of taken code
        int isError = 1;
        for(int i=0;menu1[i].fun!=NULL;i++){
            if(buffer[0]==menu1[i].index){
            //call the function
                menu1[i].fun();
                isError = 0;
            }
        }
        if(isError==1){
            printf("function not supported\n");
        }   
    }      
    exit(0);
}


int main(int argc, char **argv){
  menu();
}

