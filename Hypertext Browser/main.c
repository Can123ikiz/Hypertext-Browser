#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int document_name_length; //Global variable.
char *document_name;      //Global variable.

//Ge�ersiz dosya ismi girildi�inde kullan�c�dan girilen di�er karakterleri enter'a kadar ge�er. 
void getInnecesaryCharacters(FILE* fp, char actual_char)
{
    if(actual_char=='\n')
        return;
    
    while(EOF!=(actual_char=fgetc(fp)) && actual_char!='\n')
        continue;
}
 
int get_command_of_read_file(FILE* fp){  // console'dan dosya adi alinir ve kontroller yapilir.
	
	document_name_length=25; //Standart length, can change.
    
    //Allocating the requested memory.
    document_name = realloc(NULL, sizeof(*document_name)*document_name_length);

    char character_of_input='\n';
    
    while(EOF!=(character_of_input=fgetc(fp)) &&  //Dosya isminin sonu de�ilse bo�luklar� ge�er.
            (character_of_input==' ' || character_of_input=='\t' ))
        continue;
    
    if(character_of_input=='\n')  // Enter okundu�unda dosya isminin bitti�i d���n�l�r.
       return -1; //Program end code.
   	    
    int index=0; 
    document_name[index++]=character_of_input; //�lk harf okundu ve document_name array'ine kaydedildi.    
    
    while(EOF!=(character_of_input=fgetc(fp)) && character_of_input != '.' && character_of_input != '\n') //Noktaya kadar olan k�sm�n kontrol�.
    {
        
        document_name[index++]=character_of_input;
        if(index==document_name_length) //Dosya ismi i�in bellekte yer artt�r�l�yor.
        {
            document_name =  realloc(document_name, sizeof(*document_name)*(document_name_length+=16));
            if(!document_name_length)
            {
                printf("An error ocurred, restarting the program...\n\n");
                return -1;
            }
        }
    }
    //Dosyan�n uzant�s�na kadar olan k�s�m okundu. O k�s�mdan sonra '.htx' gelmek zorunda. Di�er durumlar wrong commend olur. Kullan�c�dan tekrar istenir.
    if (character_of_input!= '.'){
    	getInnecesaryCharacters(fp, character_of_input);
    	return 0;
	}
	else  // nokta okunduysa
	{
		document_name[index++]=character_of_input;
		if((character_of_input=fgetc(fp))!='h')
        {
            getInnecesaryCharacters(fp, character_of_input); 
            return 0; //Wrong command code.
        }
            
        else
        {
        	document_name[index++]=character_of_input;
        	if((character_of_input=fgetc(fp))!='t')
            {
                getInnecesaryCharacters(fp, character_of_input); 
                return 0; //Wrong command code.
            }
            else
			{
            	document_name[index++]=character_of_input;
            	if((character_of_input=fgetc(fp))!='x'){
            		getInnecesaryCharacters(fp, character_of_input); 
                	return 0; //Wrong command code.
				}
				else
				{
					document_name[index++]=character_of_input;
					if((character_of_input=fgetc(fp))!='\n'){
            		getInnecesaryCharacters(fp, character_of_input); 
                	return 0; //Wrong command code.
				}
			}
		}
	}
    document_name_length=index;  //document_name in geni�li�i belirlendi.
    document_name[index++]='\0';
    return 1; //Correct query code.
    }
}

void openLinks(){  // Linklerin a��lmas� i�in olusturulmus bir method.
	
	printf("\n Press 1 to open the link: " );
	int choice;	
	scanf("%d", &choice);
	if(choice==1){
		system("start main1"); // A��lmas� istenilen dosya -> "main1"   
	}	
	else{
		printf("There is no link.");
	}					
}

int main(int argc, char** argv) 
{
    printf("c:\\> ");
    int query_code=get_command_of_read_file(stdin);
    
    if(query_code == -1){   
    	printf("Empty name of file.\n");
	}
	 while(query_code != -1)
    {
		if(query_code == 0){   // wrong command line
			printf("Unrecognized command, please retype a command.\n\n");
			printf("c:\\> ");
			query_code=get_command_of_read_file(stdin);
    	
		}else{
            query_code = -1; 
        }
    }
         
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    FILE * file;
    file = fopen(document_name, "r");  // file okuma yap�lmak i�in a��ld�.
    char character;
    int red_flag = 0;   
	int blue_flag = 0; 
	int comment_flag = 0;
	char previous_char = 0;
    					
    if((file = fopen(document_name, "r"))== NULL){   // Dosya bos ise...
		printf("Empty file...");
		return;
	} 
	while(EOF != (character = fgetc(file))){   // Dosya sonuna okuma yapilir.
    	if( character == '[' && red_flag == 1){	 // [end_red durumu icin if bloguna girilir.
			while(character!= ']'){
				character = fgetc(file);
			}
			character = fgetc(file);  // ] i�aretten sonra gelen karakteri al�r.
			if(character == '\n')
				printf("\n"); 
			else if (character == ' ')
				printf(" ");
			red_flag = 0; // flag resetlenir.
			
		} if( character == '[' && blue_flag == 1){  // [end_blue durumu i�in if bloguna girilir.
			while(character != ']'){ 
				character = fgetc(file);
			}
			character = fgetc(file); // ] i�aretten sonra gelen karakteri al�r.
			if(character == '\n')
				printf("\n");
			else if (character == ' ')
				printf(" ");
			blue_flag = 0; // flag resetlenir.
		} 
		
    	if(character == '['){
    		character = fgetc(file);
    			if(red_flag == 0 && (character == 'r')){
				// Parantez a��ld�ktan sonra 'r' geldiyse bunun red oldu�unu anla��l�r. ( r ile ba�layan bir renk gelmeyece�ini varsay�n�z.)
						red_flag = 1; // flaglar set edilir.
						while(character != ']'){ //[red tagi kapat�lana kadar d�ner.
							character = fgetc(file);
						}						
	
					}
				else if(blue_flag == 0 && (character == 'b')){
				// Parantez a��ld�ktan sonra 'b' geldiyse bunun red oldu�unu anla��l�r. ( b ile ba�layan bir renk gelmeyece�ini varsay�n�z.)
						blue_flag = 1; // flagler set edilir. 
						while(character != ']'){ //[blue tagi kapat�lana kadar d�ner.
						character = fgetc(file);
						}
					}
				else { 	// linki a�ma ...
					while(character != '|'){  // [label_comes_here|file_name] label_comes_here k�sm� ekrana yazd�r�l�r. 
						SetConsoleTextAttribute(hConsole,FOREGROUND_GREEN ); // Linklerin rengi console'da ye�il olarak g�r�n�r.
						printf("%c", character);
						character = fgetc(file);
					}	
				}
			character = fgetc(file);  // Bir sonraki karakter okunur.
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
		
	} // end of while...
	
	SetConsoleTextAttribute(hConsole,FOREGROUND_INTENSITY);  // Bir �zelli�i olmayan yaz�lar gri yazd�r�l�r.

	if(comment_flag == 1){ //Comment flag a��k kald�ysa hata mesaj�.
		printf("\n Comment Error \n");
	}else{
		openLinks();  // Link a�ma fonskiyonu �a��r�l�r.
	}

	getchar();    // Console'un kapanmas�n� engeller.
	fclose(file); // Dosya kapat�l�r.
    free(document_name); 
    return (EXIT_SUCCESS);

} // end of main...

		

