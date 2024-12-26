## Part 3

![hostname edit](https://i.imgur.com/w5uhZpN.png)

 с помощью `vim` изменил `/etc/hostname` на user-1

![edit time zone](https://i.imgur.com/Xo4kWHU.png)

 с помощью команды `timedatectl list-timezones` нашел свою таймзону и с помощью команды sudo timedatectl set-timezone Europe/Moscow установил таймзону в которой я нахожусь, потом для проверки таймзоны прописал timedatectl

![net interface](https://i.imgur.com/50sK6fj.png)

 с помощью команды `ls /sys/class/net` вывел список сетевых интерфейсов. Интерфейс io показывает что я работаю с виртуальной машины

![ip adress](https://i.imgur.com/RGm6mhO.jpeg)

 с помощью команды `ip addres` получил ip адресс в том числе от DHCP-сервера. DHCP - это сетевой протокол который назначает автоматически ip адресс, служит для настройки машин подключаемых к сети (принцип работы dhcp в 4 шагах: мы даем запрос на айпи -> сервера предоставляют возможность выбора обратно пользователю -> пользователь выбирает сервер и зарпашивает у него разрешение на предоставление ip адресса -> сервер выдает разрешение пользователю)

![curl ifconfig](https://i.imgur.com/o2J3ZCx.png)

![ip route](https://i.imgur.com/QWwgyel.png)

 с помощью команды `curl ifconfig.me` я вывел на экран внешний ip адресс, и с помощью команды `ip route | grep default` вывел на экран внутренний ip адресс 

![ip settings](https://i.imgur.com/IfO6C7X.png)

 с помощью команды `sudo vim /etc/netplan/01-netcfg.yaml` изменил файл `/etc/netplan/01-netcfg.yaml` и прописал конфигурацию для моего сетевого интерфейса enp0s3, затем сохранил изменения командой `sudo netplan apply` и проверил настройки командой `ip a`

![ping server 1.1.1.1](https://i.imgur.com/8zL2vFF.png)

![ping server ya.ru](https://i.imgur.com/tb7nIF3.png)

 пропинговал сервер 1.1.1.1 и ya.ru с помощью команды `ping -c 4 1.1.1.1` рещультаты на скрине
