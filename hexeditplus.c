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



/*
======================================menu functions==========================================
*/

void toggle_debug_mode() {
    if(debug_mode == 0) { 
        debug_mode = 1
        fprintf(stderr, "Debug flag now on\n");
    }
    else{
        debug_mode = 1;
        fprintf(stderr, "Debug flag now off\n");
    }
    


}

void set_file_name() {

}

void set_unit_size() {

}

void load_into_memory() {
    printf("Not implemented yet\n");
}

void toggle_display_mode() {
    printf("Not implemented yet\n");
}

void memory_display() {
    printf("Not implemented yet\n");
}

void save_into_file() {
    printf("Not implemented yet\n");
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
      }
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
          menu[i].fun();
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

