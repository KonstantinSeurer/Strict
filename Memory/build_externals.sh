 
arch=$(uname -i)

if [[ $arch == x86_64 ]]; then
	gcc -c externals.c -o x86_64/linux/externals.o
else
	echo "Unsupported architecture!"
fi
