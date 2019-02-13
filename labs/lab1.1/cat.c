#include <stdio.h>	
#include <unistd.h>	
#include <fcntl.h>

int main(int argc, char **argv){
	int	i;
    int file;
    int ch;

	for (i = 1; i < argc; i++){ //for every paramater we look for a valid file
		file = open(argv[i], O_RDONLY);
		if (file < 0){
            perror(argv[i]); 
            continue; 
        }
		while (read(file, &ch, 1) == 1){
            write( STDOUT_FILENO, &ch, 1);//print to the terminal
        }
		close(file);
	}
    return 0;
}
