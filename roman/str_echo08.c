#include	"unp.h"
#include <string.h>


int converttonum(char* roman_num){
     //Roman to arabic convert from www.daniweb.com
    int len = strlen(roman_num);
    int number = 0;
    int counter = 0;
    int b4sum = 0;
    int sum = 0;
    for (counter = len; counter >= 0; counter--){
    if (roman_num[counter] == 'M' || roman_num[counter] == 'm')
        number = 1000;
    else if (roman_num[counter] == 'D' || roman_num[counter] == 'd')
        number = 500;
    else if (roman_num[counter] == 'C' || roman_num[counter] == 'c')
        number = 100;
    else if (roman_num[counter] == 'L' || roman_num[counter] == 'l')
        number = 50;
    else if (roman_num[counter] == 'X' || roman_num[counter] == 'x')
        number = 10;
    else if (roman_num[counter] == 'V' || roman_num[counter] == 'v')
        number = 5;
    else if (roman_num[counter] == 'I' || roman_num[counter] == 'i')
        number = 1;
    else
        number = 0;
    if (b4sum > number)
        sum = b4sum - number;
    else
        sum = sum + number;
    b4sum = number;
    }
    return sum;
}

int get_int_len (int value){
                int l=1;
                while(value>9){ l++; value/=10; }
                return l;
            }

void str_echo(int sockfd)
{
	
	
    //include content-type and content-length (every single character starting from <html>
    
	for ( ; ; ) {
	char		arg1[MAXLINE+1];
	int        arg2;
	ssize_t		n;
	char		line[MAXLINE];
	char		totalline[MAXLINE];
	totalline[0] = '\0';
	char getrequest[MAXLINE];
	char httpversion[MAXLINE];
	int length = 39;
	    
		if ( (n = Readline(sockfd, line, MAXLINE)) == 0)
			return;		/* connection closed by other end */
        printf("%s\n", line);
        if (sscanf(line, "%s%s%s", getrequest, arg1, httpversion) == 3){
            fprintf(stderr, "Just to check: %s\n", getrequest);
            if(!strcmp(getrequest, "GET")){
                arg2 = converttonum(&arg1[1]); //&arg1[1] gets rid of the slash
                           
                length = length + get_int_len(arg2);

                snprintf(totalline, sizeof(line), "%s%s\n", httpversion, " 200 OK");
                snprintf(line, sizeof(line), "%s%d\n", "Content-Length:", length);
                strcat(totalline,line);
                snprintf(line, sizeof(line), "%s\n", "Vary: Accept-Encoding");
                strcat(totalline,line);
                snprintf(line, sizeof(line), "%s\n", "Content-Type: text/html");
                strcat(totalline,line);
                snprintf(line, sizeof(line), "%s\n", "");
                strcat(totalline,line);
                snprintf(line, sizeof(line), "%s\n", "<html>");
                strcat(totalline,line);
                snprintf(line, sizeof(line), "%s\n", "<body>");
                strcat(totalline,line);
                snprintf(line, sizeof(line), "%s%d%s\n", "<h1>",arg2,"</h1>");
                strcat(totalline,line);
                snprintf(line, sizeof(line), "%s\n", "</body>");
                strcat(totalline,line);
                snprintf(line, sizeof(line), "%s\n", "</html>");
                strcat(totalline,line);
                }
		}else{
		    
			//snprintf(totalline, sizeof(line), "input error - too many/few arguments\n");
        }
		n = strlen(totalline);
		fprintf(stderr, "%s", totalline);
		fprintf(stderr, "%s\n\n\n", " ");
		Writen(sockfd, totalline, n);
	}
}
