#include <stdio.h>
#include<unistd.h>

int main() {
//    char *filename = "/Users/cg/data/code/wheel/c/notepad/README.md";
    char *filename = "README.md";
    if (access(filename, F_OK) == 0) {
        puts("Exists");
    } else {
        puts("Dose not exist");
    }

    return 0;
}
