#include <bits/stdc++.h>
#include<gmp.h>
using namespace std;
string  pt_str="";
string temp_pt_str="";
string  dec_str="";

void ASCIISentence(string str,string* res)
{
	int l = str.length();
	int convert;
	for (int i = 0; i < l; i++) {
		convert = str[i] - NULL;
		string s = to_string(convert);
		(*res).append(s);
	}
}

void asciiToSentence(string str, int len,string * res)
{
	int num = 0;
	for (int i = 0; i < len; i++) {

		// Append the current digit
		num = num * 10 + (str[i] - '0');

		// If num is within the required range
		if (num >= 32 && num <= 122) {

			// Convert num to char
			char ch = (char)num;
            (*res)+=ch;
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

int main(){
	int check = 0;		                                    //will be 2 if prime, else 1 or 0
	mpz_t prime_p, prime_q, t;			                    //two very large prime numbers
	int bits = 128;
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

    mpz_init_set_str (prime_p, "340282365653906833253643981767154204671", 10);
    mpz_init_set_str (prime_q, "340282366920933627760096148915069386783", 10);

	mpz_t N;
	mpz_inits(N,NULL);
	mpz_mul ( N, prime_p, prime_q);
	mpz_t P, Q,tot_n, e, en_gcd;			                    //totient on n=prime_p*prime_q; which is LCM(prime_p-1, prime_q-1)
	mpz_init(P);
	mpz_init(Q);
	mpz_init(e);
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
	cout << "Public key pair:\n N = " << N << "\n e = "<<e;

    mpz_t gcdex,y,d;
    mpz_inits(gcdex,d,y,NULL);
    mpz_init_set_ui(gcdex,1);
	mpz_gcdext(gcdex,d,y,e,tot_n);
	cout<<"\nSecret key component : \n d = "<<d<<endl;

    string input_str;
    cout<<"\nEnter the string to encrypt: "<<endl;
    getline(cin,input_str);
    ASCIISentence(input_str,&pt_str);
    int st_len=pt_str.length();
    char plain_text[st_len+1];
    strcpy(plain_text, pt_str.c_str());
    cout<<endl;

    //before encryption
    mpz_t str_num;
    mpz_init(str_num);
    mpz_set_str(str_num,plain_text,10);
    cout<<" \nPT before encryption :\n"<<input_str<<endl;
    cout<<endl;

    //generate cipher text
    mpz_t ctext,base,exp, mod,ptext;
    mpz_inits(ctext ,base,exp,mod,ptext,NULL);
    mpz_init_set (exp, e);
    mpz_init_set (mod,N);
    mpz_powm(ctext,  str_num, exp, mod);
    cout<<"Cipher text: \n"<< ctext<<endl;
    cout<<endl;

    //decrypt cipher text
    mpz_init_set (exp,d);
    mpz_powm(ptext,  ctext, exp, mod);
    char *decrypt_text=NULL;
    decrypt_text=mpz_get_str(decrypt_text,10,ptext);
    string temp_str=convertToString(decrypt_text,st_len+1);
    int temp_len=temp_str.length();
    asciiToSentence(temp_str,temp_len,&dec_str);
    cout<<"After Decryption: \n"<<dec_str<<endl;

	return 0;
}
