## Part 1

### 1.1. Сети и маски
 
1.

   ![2](https://i.imgur.com/Z0KuSXu.png)

   Адрес сети 192.167.38.54/13 - `192.160.0.0`

2.

   ![3](https://i.imgur.com/4lN6VLo.png)

   Маска `255.255.255.0`:

   Префиксная запись: `/24`, Двоинчая: `11111111.11111111.11111111.00000000`

   ![4](https://i.imgur.com/SgNA2A7.png)

   Маска `/15`:

   Обычная запись: `255.254.0.0`, Двоичная запись: `11111111.11111110.00000000.00000000`

   ![5](https://i.imgur.com/sKGqSgD.png)
 
   Маска `11111111.11111111.11111111.11110000`:

   Обычная запись: `255.255.255.240`, Префиксная запись: `/28`

3.
   
   ![6](https://i.imgur.com/twp8V0i.png)

   Маска `/8`:
   
   Адрес сети: `12.0.0.0`
   Минимальный хост: `12.0.0.1`
   Максимальный хост: `12.255.255.254`


   Маска `11111111.11111111.00000000.00000000`:

   Адрес сети: `12.167.0.0`
   Минимальный хост: `12.167.0.1`
   Максимальный хост: `12.167.255.254`


   Маска `255.255.254.0`:

   Адрес сети: `12.167.38.0`
   Минимальный хост: `12.167.38.1`
   Максимальный хост: `12.167.39.254`


   Маска `/4`:

   Адрес сети: `0.0.0.0` (так как `/4` охватывает диапазон `0.0.0.0 — 15.255.255.255`).
   Минимальный хост: `0.0.0.1`
   Максимальный хост: `15.255.255.254`

### 1.2. localhost

   `194.34.23.100` — нельзя (это внешний IP)
   `127.0.0.2` — можно
   `127.1.0.1` — можно
   `128.0.0.1` — нельзя (не входит в диапазон 127.0.0.0/8)

### 1.3. Диапазоны и сегменты сетей

1.
   Частные IP-адреса:
      `10.0.0.45`
      `192.168.4.2`
      `172.20.250.4`
      `172.16.255.255` 
      `10.10.10.10` 

   Публичные IP-адреса:
      `134.43.0.2`
      `172.0.2.1`
      `192.172.0.1`
      `172.68.0.2`
      `192.169.168.1`
 
2.
   Диапазон адресов: `10.10.0.1` — `10.10.63.254`

   `10.0.0.1` — нельзя (не входит в диапазон)
   `10.10.0.2` — можно
   `10.10.10.10` — можно
   `10.10.100.1` — нельзя (выходит за пределы диапазона)
   `10.10.1.255` — можно

## Part 2

 ![1](https://i.imgur.com/RxjY03g.png)

 ip a

 ![2](https://i.imgur.com/Gu6UAT2.png)

 настройка `etc/netplan/00-installer-config.yaml` для каждой машины

 ![3](https://i.imgur.com/j8Y7Rsr.png)

 netplan apply

 ![4](https://i.imgur.com/kBp9J9v.png)

 Добавление статического маршрута вручную

 ![5](https://i.imgur.com/DjTPWvc.png)

 прописал маршрут в `etc/netplan/00-installer-config.yaml`

 ![6](https://i.imgur.com/stwDu79.png)

 `netplan apply + ip r + ping`
 
## Part 3
### 3.1. Скорость соединения

 `8 Mbps = 1 MB/s`

 `100 MB/s = 800 000 Kbps`

 `1 Gbps = 1 000 Mbps`

 ![1](https://i.imgur.com/Y8WHnPV.png)

 скорость соединения между ws1 и ws2.

## Part 4
### Part 4.1 Утилита iptables
 ![1](https://i.imgur.com/YinRmY7.png)

 ws1 strategy

 ![2](https://i.imgur.com/VjPjVJm.png)

 ws2 strategy

 Если сначала стоит запрещающее правило, то оно имеет приоритет перед последующим разрешающим.

### Part 4.2 Утилита nmap

 ![1](https://i.imgur.com/L2fw3Ap.png)

 ping + nmap

## Part 5

### Part 5.1 Настройка адресов машин

![1](https://i.imgur.com/GLsB4Op.png)

ws11

![1](https://i.imgur.com/8AqvCSr.png)

ws21

![1](https://i.imgur.com/WKVbZNa.png)

ws22

![2](https://i.imgur.com/r4QC3Xo.png)

настройка r1 и r2

`sudo netplan apply` для сохранения настроек

![3](https://i.imgur.com/aRf9Wz4.png)

`ip -4 a` для ws

![4](https://i.imgur.com/tBrKZsO.png)

`ip -4 a` для r

![5](https://i.imgur.com/KZYlrg5.png)

ping ws22 c ws21

![6](https://i.imgur.com/fkMj3LU.png)

ping r1 c ws11

### 5.2. Включение переадресации IP-адресов

![6](https://i.imgur.com/yQdNA7o.png)

`sysctl -w net.ipv4.ip_forward=1` на роутерах

![7](https://i.imgur.com/Zj8mPvj.png)

`net.ipv4.ip_forward = 1` в `/etc/sysctl.conf`

### 5.3. Установка маршрута по умолчанию

![1](https://i.imgur.com/sP5NIE2.png)

netplan configs for ws11 + ip r

![1](https://i.imgur.com/0H5bgus.png)

netplan configs for ws21 + ip r

![1](https://i.imgur.com/sCzW7gZ.png)

netplan configs for ws22 + ip r

![2](https://i.imgur.com/8LpekaX.png)

### 5.4. Добавление статических маршрутов

![1](https://i.imgur.com/pzSjGjh.png)

netplan + `ip r`:

![2](https://i.imgur.com/ojKlyCR.png)

Для адреса 10.10.0.0/18 был выбран маршрут, отличный от 0.0.0.0/0, поскольку он является адресом сети и доступен без шлюза.

![3](https://i.imgur.com/wziEKFF.png)

Для определения промежуточных маршрутизаторов traceroute отправляет целевому узлу серию ICMP-пакетов (по умолчанию 3 пакета), с каждым шагом увеличивая значение поля TTL («время жизни») на 1. Это поле обычно указывает максимальное количество маршрутизаторов, которое может быть пройдено пакетом. Первая серия пакетов отправляется с TTL, равным 1, и поэтому первый же маршрутизатор возвращает обратно ICMP-сообщение «time exceeded in transit», указывающее на невозможность доставки данных. Traceroute фиксирует адрес маршрутизатора, а также время между отправкой пакета и получением ответа (эти сведения выводятся на монитор компьютера). Затем traceroute повторяет отправку серии пакетов, но уже с TTL, равным 2, что заставляет первый маршрутизатор уменьшить TTL пакетов на единицу и направить их ко второму маршрутизатору. Второй маршрутизатор, получив пакеты с TTL=1, так же возвращает «time exceeded in transit».

Процесс повторяется до тех пор, пока пакет не достигнет целевого узла. При получении ответа от этого узла процесс трассировки считается завершённым.

На оконечном хосте IP-датаграмма с TTL = 1 не отбрасывается и не вызывает ICMP-сообщения типа срок истёк, а должна быть отдана приложению. Достижение пункта назначения определяется следующим образом: отсылаемые traceroute датаграммы содержат UDP-пакет с заведомо неиспользуемым номером порта на адресуемом хосте. Номер порта будет равен 33434 + (максимальное количество транзитных участков до узла) — 1. В пункте назначения UDP-модуль, получая подобные датаграммы, возвращает ICMP-сообщения об ошибке «порт недоступен». Таким образом, чтобы узнать о завершении работы, программе traceroute достаточно обнаружить, что поступило ICMP-сообщение об ошибке этого типа

### 5.6. Использование протокола ICMP при маршрутизации

![1](https://i.imgur.com/FIPbaiA.png)

пинг несуществующего ip

## Part 6

![1](https://i.imgur.com/qE4jzlO.png)

`/etc/dhcp/dhcpd.conf`

![2](https://i.imgur.com/vQxhXRJ.png)

`resolv.conf`

![3](https://i.imgur.com/nJDFvU2.png)

`reboot + ip a` на ws21

![4](https://i.imgur.com/RaWXoNl.png)

ping ws22 с ws21 и наоборот

![5](https://i.imgur.com/IRaSUTp.png)

ws11 mac address

![6](https://i.imgur.com/MJAE5Pn.png)

r1 dhcp settings

![7](https://i.imgur.com/p2r80kd.png)

ws11 ip address

![8](https://i.imgur.com/NC2Nbzn.png)

Команда sudo dhclient -r enp0s3 освобождает текущий адрес интерфейса enp0s3. Команда sudo dhclient enp0s3 задает новый адрес указанному интерфейсу.

## Part 7

![1](https://i.imgur.com/GERAhLl.png)

`/etc/apache2/ports.conf` ws22, r1

![2](https://i.imgur.com/rYag7Gm.png)

`system apache2 start`

![3](https://i.imgur.com/9fcwSHn.png)

add firewall on r2

![4](https://i.imgur.com/06kRXlA.png)

update firewall

![5](https://i.imgur.com/iupXFWq.png)

проверка SNAT

![6](https://i.imgur.com/unTJXut.png)

проверка DNAT

## Part 8

![1](https://i.imgur.com/DupFTqc.png)

apache2 ports ws22

![2](https://i.imgur.com/5bRh1gO.png)

`ssh -L 8080:localhost:80 leezy@10.20.0.20 -N`

![3](https://i.imgur.com/5bRh1gO.png)

`ssh -L 9090:localhost:80 leezy@10.20.0.20 -N`


