# Ellu-OS
[(🇷🇺) Ru README](https://github.com/voncov/Ellu-OS/blob/main/README-RU.md)

Ellu-OS is an open-source operating system designed for learning, experimentation, and low-level system development.

## Run Locally

Install dependencies
```bash
sudo <apt/dnf> update
sudo <apt/dnf> install wget git unzip nasm qemu-system-i386
```

Clone the project
```bash
cd ~
git clone https://github.com/voncov/Ellu-OS/
```

Create the necessary folders
```bash
mkdir -p ~/opt/cross && cd ~/opt/cross
```

Download and unpack the tools
```bash
wget https://github.com/lordmilko/i686-elf-tools/releases/download/15.2.0/x86_64-elf-tools-linux.zip
unzip x86_64-elf-tools-linux.zip
```

Add the compiler to PATH
```bash
echo 'export PATH=$HOME/opt/cross/bin:$PATH' >> ~/.bashrc
source ~/.bashrc
```


## Check i686-elf-gcc

```bash
i686-elf-gcc -v
```
* *If you encounter an error, check that you have installed the compiler correctly by following the steps shown here.*


Go to the project directory
```bash
cd ~/Ellu-OS
```

Start the system
```bash
make clean && make run
```
## License

[MIT](https://choosealicense.com/licenses/mit/)


## Authors

- [@voncov](https://github.com/voncov/)
