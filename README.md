## Part 1

![Ubuntu version](https://i.imgur.com/TOvvEAo.png)

 версия ubuntu

## Part 2

![Add new member](https://i.imgur.com/9AM3WHy.png)

![new member group](https://i.imgur.com/KlYDjwK.png)

 `sudo useradd -m -G adm new_leezy` добавили нового юзера в групу `adm`
- `-m` - создаёт домашнюю директорию для нового пользователя.
- `-G adm` - добавляет пользователя в группу adm.


## Part 3

![hostname edit](https://i.imgur.com/w5uhZpN.png)

 с помощью `vim` изменил `/etc/hostname` на `user-1`

![edit time zone](https://i.imgur.com/Xo4kWHU.png)

 с помощью команды `timedatectl list-timezones` нашел свою таймзону и с помощью команды `sudo timedatectl set-timezone Europe/Moscow` установил таймзону в которой я нахожусь, потом для проверки таймзоны прописал timedatectl

![net interface](https://i.imgur.com/50sK6fj.png)

 с помощью команды `ls /sys/class/net` вывел список сетевых интерфейсов. Интерфейс `io` показывает что я работаю с виртуальной машины

![ip adress](https://i.imgur.com/RGm6mhO.jpeg)

 с помощью команды `ip addres` получил ip адресс в том числе от DHCP-сервера. DHCP - это сетевой протокол который назначает автоматически ip адресс, служит для настройки машин подключаемых к сети (принцип работы dhcp в 4 шагах: мы даем запрос на айпи -> сервера предоставляют возможность выбора обратно пользователю -> пользователь выбирает сервер и зарпашивает у него разрешение на предоставление ip адресса -> сервер выдает разрешение пользователю)

![curl ifconfig](https://i.imgur.com/o2J3ZCx.png)

![ip route](https://i.imgur.com/QWwgyel.png)

 с помощью команды `curl ifconfig.me` я вывел на экран внешний ip адресс, и с помощью команды `ip route | grep default` вывел на экран внутренний ip адресс 

![ip settings](https://i.imgur.com/IfO6C7X.png)

 с помощью команды `sudo vim /etc/netplan/01-netcfg.yaml` изменил файл `/etc/netplan/01-netcfg.yaml` и прописал конфигурацию для моего сетевого интерфейса enp0s3, затем сохранил изменения командой `sudo netplan apply` и проверил настройки командой `ip a`

![ping server 1.1.1.1](https://i.imgur.com/8zL2vFF.png)

![ping server ya.ru](https://i.imgur.com/tb7nIF3.png)

 пропинговал сервер 1.1.1.1 и ya.ru с помощью команды `ping -c 4 1.1.1.1` и `ping -c 4 ya.ru` результаты на скрине

## Part 4

![apt upgrade](https://i.imgur.com/w2ytl9F.png)

 обновил системные пакеты командой `sudo apt upgrade` (при выполнении команды была ошибка, дополнительно ввел `sudo apt-get update`)

## Part 5

![new user sudo](https://i.imgur.com/2Cyt0JP.png)

 добавил нового пользователя в группу `sudo` командой `sudo usermod -aG sudo new_leezy`

![hostname edit](https://i.imgur.com/PAgWaMG.png)

 командой `sudo -u new_leezy sudo vim /etc/hostname` изменил hostname через нового пользователя

команда `sudo` служит для того чтобы запускать команды от имени суперпользователя, для запуска команд с `sudo` необходимо знать пароль от пользователя

## Part 6

![time](https://i.imgur.com/3wDbFX6.png)

## Part 7

![vim](https://i.imgur.com/zgCjGog.png)

 для сохранения ввел команду `:wq`

![nano](https://i.imgur.com/IBMmp2e.png)

 для сохранения нажал `ctrl + o` потом `ENTER` потом `ctrl + x`

![joe](https://i.imgur.com/fMEUK5M.png)

 для сохранения нажал `ctrl + k` потом `x`


![vim no save](https://i.imgur.com/VwUf9TZ.png)

 `:q!` для выхода без сохранения

![nano no save](https://i.imgur.com/mzui4lC.png)

 `ctrl + x` потом `N` для выхода

![joe no save](https://i.imgur.com/VGJCKto.png)

 `ctrl + c` потом `Y` для выхода

![cat all](https://i.imgur.com/0cxsg0c.png)

 вывод всех файлов

![vim grep](https://i.imgur.com/tSerczy.png)

 нажал `esc` и ввел команду `/leezy` для поиска слова

![vim grep](https://i.imgur.com/Au670XZ.png)

 ввел команду `:%s/leezy/sewer/g` для замены слова

![nano](https://i.imgur.com/a8olsvg.png)

 `ctrl + \` для поиска слова 

![nano](https://i.imgur.com/h0uFSQ3.png)

 `ctrl + \` для поиска слова и потом вводим новое слово и нажимаем `ENTER` потом `Y

![joe](https://i.imgur.com/KPMhxB4.png)

 `ctrl + k` потом `F` для поиска слова

![joe](https://i.imgur.com/XE43THA.png)

 `ctrl + k` потом `F` для поиска слова, потом вводим новое слово и нажимаем `Y` для сохранения

## Part 8

![sshd](https://i.imgur.com/yJUPR4n.png)

 установка sshd

![sshd](https://i.imgur.com/ock31jY.png)

 добавление в автостарт

![sshd](https://i.imgur.com/NTlX9iS.png)

 настройка на порт 2022 с помощью `sudo vim /etc/ssh/sshd_config` и `sudo systemctl restart ssh` для сохранения изменений

![sshd](https://i.imgur.com/km6E75u.png)

 `ps aux | grep sshd` показывает наличие процесса `sshd`
- `a` - показывает процессы всех пользователей
- `u` - выводит информацию о пользователе, который запустил процесс
- `x` - показывает процессы, не привязанные к терминалу

![sshd](https://i.imgur.com/jr7XBkp.png)

 Объяснение `netstat -tan`:
- `-t` - отображает только TCP-соединения
- `-a` - показывает все соединения и прослушиваемые порты
- `-n` - отображает адреса и номера портов в числовом форма
- `tcp` - тип протокола
- `0` - количество принятых данных
- `0` - количество отправленных данных
- `0.0.0.0:2022` - адрес и порт, на котором служба слушает
- `0.0.0.0:` - означает, что служба доступна для всех IP-адресов
- `LISTEN` - статус сокета

