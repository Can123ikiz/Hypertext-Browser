#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include <windows.h>

/*Write a basic hypertext browser that supports colored text */

int main(int argc, char *argv[]) {
	
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    FILE * file;
    file = fopen("link_1.htx", "r");  // "link_1.htx" dosyas� okumak i�in a��ld�.
    char character;
    int red_flag = 0;   
	int blue_flag = 0; 
	char previous_char = 0;
	char comment_flag = 0;
    					
    if((file = fopen("link_1.htx", "r"))== NULL){
		printf("Empty file...");
		return;
	} 
	while(EOF != (character = fgetc(file))){
    	if( character == '[' && red_flag == 1){	
			while(character!= ']'){
				character = fgetc(file);
			}
			character = fgetc(file);
			if(character == '\n')
				printf("\n");
			else if (character == ' ')
				printf(" ");
			red_flag = 0;
			
		} if( character == '[' && blue_flag == 1){
			
			while(character != ']'){
				character = fgetc(file);
			}
			character = fgetc(file);
			if(character == '\n')
				printf("\n");
			else if(character ==' ')
				printf(" ");
			
			blue_flag = 0;
		} 
		
    	if(character == '['){
    		character = fgetc(file);
    			if(red_flag == 0 && (character == 'r')){
						red_flag = 1;
						while(character != ']'){
							character = fgetc(file);
						}						
	
					}
				else if(blue_flag == 0 && (character == 'b')){
						blue_flag = 1;
						while(character != ']'){
						character = fgetc(file);
						}
					}
				
			character = fgetc(file);
	}
	
	if(character != '[' && red_flag == 1){  // [red] ... [end_red] aras�ndaki yaz�lar� k�rm�z� yazd�r�l�r.
		SetConsoleTextAttribute(hConsole,FOREGROUND_RED); // Yaz�lar� k�rm�z� yazd�rmay� sa�layan kod par�as�.
		printf("%c", character);
	}
	
	else if(character != '[' && blue_flag == 1){ // [blue] ... [end_blue] aras�ndaki yaz�lar� mavi yazd�r�l�r.
		SetConsoleTextAttribute(hConsole,FOREGROUND_BLUE); // Yaz�lar� mavi yazd�rmay� sa�layan kod par�as�.
		printf("%c", character);
	}
	
	else if(character == '/' && comment_flag == 0){
        previous_char = '/';
    }
    else if(character == '*' && previous_char == '/' ){ //Comment a��ld�.
        comment_flag = 1;
        previous_char = 0;
    }
    else if(character == '*' && comment_flag==1){
        previous_char = '*';
    }
    else if(character == '/' && previous_char == '*' && comment_flag == 1){ //Comment kapand�.
        comment_flag = 0;
        previous_char = 0;
    }else if(comment_flag == 1){
        previous_char = 0;
	}
	else if(character != '*' && comment_flag == 0 && previous_char == '/'){
		previous_char = 0;

	}	
}
	SetConsoleTextAttribute(hConsole,FOREGROUND_INTENSITY);  // Bir �zelli�i olmayan yaz�lar gri yazd�r�l�r.

	if(comment_flag == 1){ //Comment kapanmad�ysa hata mesaj�.
		printf("\n Comment Error \n");
	}	
	fclose(file);
    getchar();
    return (EXIT_SUCCESS);
	return 0;
}
