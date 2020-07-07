echo "Doing something"
gcc -o lamb -g -Wall server.c
gcc -o client -g -Wall client.c
rm -rf *.dSYM
echo "Done at compiling"