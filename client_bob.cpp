// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
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
void asciiToSentence(string str, int len,string& res)
{
	int num = 0;
	for (int i = 0; i < len; i++) {

		// Append the current digit
		num = num * 10 + (str[i] - '0');

		// If num is within the required range
		if (num >= 32 && num <= 122) {

			// Convert num to char
			char ch = (char)num;
            (res)+=ch;
			//cout << ch;

			// Reset num to 0
			num = 0;
		}
	}
}

string convertToString(char* a, int size)
{
    int i;
    string s = "";
    for (i = 0; i < size; i++) {
        s = s + a[i];
    }
    return s;
}

void createkeys(mpz_t &N, mpz_t &e,mpz_t &d)
{
	int check = 0;		                                    //will be 2 if prime, else 1 or 0
	mpz_t prime_p, prime_q, t;			                    //two very large prime numbers
	int bits = 1024;
	mpz_init(prime_p);
	mpz_init(prime_q);
	mpz_init(t);
	gmp_randstate_t state;
	gmp_randinit_default(state);

	/*while(check!=2 && check!=1){
		mpz_init_set_ui(t, time(0));
		gmp_randseed(state, t);
		mpz_rrandomb(prime_p, state, bits);
		check = mpz_probab_prime_p(prime_p, 50);
	}
	check = 0;
	while(check!=2 && check!=1){
		mpz_init_set_ui(t, time(0));
		gmp_randseed(state, t);
		mpz_rrandomb(prime_q, state, bits);
		check = mpz_probab_prime_p(prime_q, 50);
		if(mpz_cmp(prime_p, prime_q)==0){
			check = 0;
		}
	}*/

    mpz_init_set_str (prime_p, "117020014223499698734185311344030498185016241236864284616156804843820087374890033948149772889562488715934732731488769406930567363351407508732947932514694249103785234597995664513489299315183792018245421624438716014079232307637004165104277209305291692932214802297282685245630046728533815201593708216886839104489", 10);
    mpz_init_set_str (prime_q, "174929609124129658756875521978488361694943813639866222904748795334096034744229059200246435859198306477078175575710761959678096020532668319415119710643889348262444900429797962932280533830638487349799911081407199215518064607001242356595870650136993159547882002253727152943433268058563996876593095903127096723611", 10);

    // mpz_init_set_str (prime_p, "7", 10);
    // mpz_init_set_str (prime_q, "5", 10);

	
	mpz_mul ( N, prime_p, prime_q);
	mpz_t P, Q,tot_n, en_gcd;			                    //totient on n=prime_p*prime_q; which is LCM(prime_p-1, prime_q-1)
	mpz_init(P);
	mpz_init(Q);
	mpz_init(tot_n);
	mpz_init(en_gcd);

	mpz_sub_ui(P, prime_p, 1);
	mpz_sub_ui(Q, prime_q, 1);
	mpz_lcm(tot_n, P, Q);
	mpz_init_set_ui(t, time(0));
	gmp_randseed(state, t);
	mpz_urandomm(e, state, tot_n);
	mpz_gcd(en_gcd, e, tot_n);

	//calculate e
	while(mpz_cmp_ui(en_gcd, 1)!=0){
		mpz_init_set_ui(t, time(0));
		gmp_randseed(state, t);
		mpz_urandomm(e, state, tot_n);
		mpz_gcd(en_gcd, e, tot_n);
	}
	//cout << "Public key pair:\n N = " << N << "\n e = "<<e;

    mpz_t gcdex,y;
    mpz_inits(gcdex,y,NULL);
    mpz_init_set_ui(gcdex,1);
	mpz_gcdext(gcdex,d,y,e,tot_n);
	//cout<<"\nSecret key component : \n d = "<<d<<endl;
}




int main(int argc, char const *argv[]) 
{ 
	int sock = 0, valread; 
	struct sockaddr_in serv_addr; 

	char buffer[1024] = {0}; 
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{ 
		printf("\n Socket creation error \n"); 
		return -1; 
	} 

	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(PORT); 
	
	// Convert IPv4 and IPv6 addresses from text to binary form 
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
	{ 
		printf("\nInvalid address/ Address not supported \n"); 
		return -1; 
	} 

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
	{ 
		printf("\nConnection Failed \n"); 
		return -1; 
	} 
			
	string a= "Hello Alice by Bob"; 
	char *hello = &a[0];
	send(sock , hello , strlen(hello) , 0 ); 
	printf("Hello message sent\n"); 
	valread = read( sock , buffer, 1024); 
	printf("%s\n",buffer );
	
     
	cout<<"connection establish"<<endl;

	mpz_t N,e,d;
	mpz_inits(N,NULL);
	mpz_inits(d,NULL);
	mpz_inits(e,NULL);


	 createkeys(N,e,d);
	cout<<endl;
	cout << "Public key pair:\nN = " << N << "\n\ne = "<<e<<endl;
	cout<<"\nSecret key component : \nd = "<<d<<endl;

	char * nchar = mpz_get_str(NULL,10,N);
	char * echar = mpz_get_str(NULL,10,e);

	send(sock , nchar , strlen(nchar) , 0 ); 
	printf("\nval N  sent\n"); 
	valread = read( sock , buffer, 1024); 
	printf("%s\n",buffer );
	this_thread::sleep_for(chrono::seconds(1)); 		
	send(sock , echar , strlen(echar), 0 ); 
	printf("val e  sent\n"); 
	valread = read( sock , buffer, 1024); 
	printf("%s\n",buffer );
	char *st;
	
	valread = read( sock , buffer, 1024); 
	st = buffer;
		string len = buffer;
		int st_len = atoi(st);

	




    mpz_t ctext;
    mpz_init(ctext);
	char * charctext;
	//  to flush buffer i put the time gap to flush buffer  other  wise they
	// are concatenated with each other 
	 this_thread::sleep_for(chrono::seconds(1)); 

	valread = read( sock , buffer, 1024); 
	charctext = buffer;

	string removelen=charctext;

	if(removelen.find(len)==0)
	{
		removelen.erase (0,len.size()); 
		charctext = &removelen[0];
	}

	
    mpz_set_str(ctext,charctext,10);
	cout<< "\nCipher text: \n"<<ctext<<endl;
    mpz_t exp, mod,ptext;
    mpz_inits(exp,mod,ptext,NULL);
    mpz_init_set (mod,N);
	mpz_init_set (exp,d);

    mpz_powm(ptext,  ctext, exp, mod);
	cout<<"\nPT before encryption :\n"<< ptext<<endl;

	string  dec_str="";

    char *decrypt_text=NULL;
    decrypt_text=mpz_get_str(decrypt_text,10,ptext);
    string temp_str=convertToString(decrypt_text,st_len+1);
    int temp_len=temp_str.length();
    asciiToSentence(temp_str,temp_len,dec_str);
    cout<<"\nAfter Decryption: \n"<<dec_str<<endl;


	cout<<"---------------------"<<endl;


	return 0; 
} 
