# Ellu-OS

Ellu-OS - это операционная система с открытым исходным кодом, предназначенная для обучения, экспериментов и низкоуровневой разработки систем.

## Локальный запуск

Установка зависимостей
```bash
sudo <apt/dnf> update
sudo <apt/dnf> install wget git unzip nasm qemu-system-i386
```

Клонируйте проект
```bash
cd ~
git clone https://github.com/voncov/Ellu-OS/
```

Создайте необходимые папки
```bash
mkdir -p ~/opt/cross && cd ~/opt/cross
```

Скачайте и распакуйте инструменты
```bash
wget https://github.com/lordmilko/i686-elf-tools/releases/download/15.2.0/i686-elf-tools-linux.zip
unzip i686-elf-tools-linux.zip
```

Добавьте компилятор в переменную PATH
```bash
echo 'export PATH=$HOME/opt/cross/bin:$PATH' >> ~/.bashrc
source ~/.bashrc
```


## Проверьте i686-elf-gcc

```bash
i686-elf-gcc -v
```
* *Если вы столкнулись с ошибкой, проверьте правильность установки компилятора, выполнив действия, описанные здесь.*


Перейдите в директорию проекта
```bash
cd ~/Ellu-OS
```

Запустите систему
```bash
make clean && make run
```
## Лицензия

[MIT](https://choosealicense.com/licenses/mit/)


## Авторы

- [@voncov](https://github.com/voncov/)
