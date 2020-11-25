we have added sockets to the best of our knowledge
we have created a server socket alice and client socket bob
please run the server_alice.cpp first and in another terminal run client_bob.cpp next
use following commands
1. in terminal 1->
	g++ server_alice.cpp -o alice -lgmp -lgmpxx
	./alice
2. in terminal 2->
	g++ client_bob.cpp -o bob -lgmp -lgmpxx
	./bob
please note that we have used gmp and pbc libraries
so the program requires them to be already downloaded and setup