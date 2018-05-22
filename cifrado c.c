#include<stdio.h>
 
int main()
{
    char frase[100], c;
    int i, n;
    
    printf("Dame una frase: ");
    gets(frase);
    printf("Cuantos espacios quieres desplazar: ");
    scanf("%d", &n);
    
    for(i = 0; frase[i] != '\0'; ++i){
        c = frase[i];
        
        if(c >= 'a' && c <= 'z'){
            c = c + n;
            
            if(c > 'z'){
                c = c - 'z' + 'a' - 1;
            }
            
            frase[i] = c;
        }
        else if(c >= 'A' && c <= 'Z'){
            c = c + n;
            
            if(c > 'Z'){
                c = c - 'Z' + 'A' - 1;
            }
            
            frase[i] = c;
        }
    }
    
    printf("La frase encriptada es: %s", frase);
    
    return 0;
}
