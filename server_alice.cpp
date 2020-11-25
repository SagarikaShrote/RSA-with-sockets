// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include<gmp.h>
#include <bits/stdc++.h>
#include <thread> 
#include <chrono> 
using namespace std;

#define PORT 8080 

void ASCIISentence(string str,string & res)
{
	int l = str.length();
	int convert;
	for (int i = 0; i < l; i++) {
		convert = str[i] - NULL;
		string s = to_string(convert);
		(res).append(s);
	}
}

int main(int argc, char const *argv[]) 
{ 
	int server_fd, new_socket, valread; 
	struct sockaddr_in address; 
	int opt = 1; 
	int addrlen = sizeof(address); 
	char buffer[1024] = {0}; 

	
	// Creating socket file descriptor 
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
	{ 
		perror("socket failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	// Forcefully attaching socket to the port 8080 
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
												&opt, sizeof(opt))) 
	{ 
		perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	} 
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons( PORT ); 
	
	// Forcefully attaching socket to the port 8080 
	if (bind(server_fd, (struct sockaddr *)&address, 
								sizeof(address))<0) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	if (listen(server_fd, 3) < 0) 
	{ 
		perror("listen"); 
		exit(EXIT_FAILURE); 
	} 
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
					(socklen_t*)&addrlen))<0) 
	{ 
		perror("accept"); 
		exit(EXIT_FAILURE); 
	} 
	char *hello = "Hello Bob by Alice"; 
	
		valread = read( new_socket , buffer, 1024); 
		printf("%s\n",buffer ); 
		send(new_socket , hello , strlen(hello) , 0 ); 
		printf("Hello message sent\n"); 
	
		cout<<"connection establish"<<endl;
		this_thread::sleep_for(chrono::seconds(3));
	char * nchar ,*echar;
	mpz_t N,e;
	    mpz_inits(N ,e,NULL);
	valread = read( new_socket , buffer, 1024); 
	nchar = buffer;
	mpz_set_str(N,nchar,10);
	cout<< "n is received from Bob"<<endl;
	//cout<< "\nthis n"<<nchar<<endl;
	char *nrecev = "n is received by Alice"; 
		send(new_socket , nrecev , strlen(nrecev) , 0 ); 
 
	

	
	valread = read( new_socket , buffer, 1024); 
	echar = buffer;	
	string remove = buffer;
	remove = remove.substr(0, remove.length() - 1);
	echar = &remove[0];
		//cout<< "\nthis e "<<echar<<endl;
			cout<< "e is received from Bob"<<endl;

		char * ereceive = "e is received by Alice"; 
		send(new_socket , ereceive , strlen(ereceive) , 0 ); 


	mpz_set_str(e,echar,10);

	cout<<"\nN->\n"<<N<<endl;
	cout<<"\ne->\n"<<e<<endl;
	string  pt_str="";	
    string input_str;
    cout<<"\nEnter the string to encrypt: "<<endl;
    getline(cin,input_str);
	cout<<"length of input string: "<<input_str.length()<<endl;
    ASCIISentence(input_str,pt_str);
    int st_len=pt_str.length();
    char plain_text[st_len+1];
    strcpy(plain_text, pt_str.c_str());


    //before encryption
    mpz_t str_num;
    mpz_init(str_num);
    mpz_set_str(str_num,plain_text,10);
    cout<<" \nPT before encryption :\n"<<str_num<<endl;

    //generate cipher text
    mpz_t ctext,base,exp, mod,ptext;
    mpz_inits(ctext ,base,exp,mod,ptext,NULL);
    mpz_init_set (exp, e);
    mpz_init_set (mod,N);
    mpz_powm(ctext, str_num, exp, mod);
    
		string st =  to_string(st_len);
		char * charstrlen =&st[0];
		send(new_socket , charstrlen , strlen(charstrlen), 0 ); 
		cout<< "length of PT-->"<<charstrlen<<endl;
    	cout<<endl;
	// to fush the buffer 
	 this_thread::sleep_for(chrono::seconds(1)); 

	char * charctext =  mpz_get_str(NULL,10,ctext);
	cout<<"Cipher text: \n"<< charctext<<endl;
		send(new_socket , charctext , strlen(charctext) , 0 ); 
	
    cout<<endl;

	return 0; 
} 
