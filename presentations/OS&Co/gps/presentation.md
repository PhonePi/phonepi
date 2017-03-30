% Разработка драйвера GPS модуля для Linux
% Азат Абдуллин
% 21 марта 2017

## Постановка задачи

SIM808 --- четырехдиапазонный модуль GSM/GPRS с функцией спутниковой GPS навигации

![sim](sim808.jpg)

## Постановка задачи

Для SIM808 будет реализован драйвер составного устройства для ОС Arch Linux. На снове драйвера составного устройства будет реализовано 3 интерфейсных драйвера:

* драйвер GSM
* драйвер GPRS
* **драйвер GPS**

## Интерфейсный драйвер GPS

Задачи:

* представление GPS модуля SIM808 как отдельного устройства в системе
* реализация необходимых возможностей GPS устройств на основе драйвера составного устройства

## Предполагаемая иерархия

![sim](hierarhy.png)

## GPS в Linux

GPS модуль в Linux:

* представляется как символьное устройство
* обмен данными в виде строковых сообщений
* общение по одному из протоколов навигационных устройств

Наиболее распространенный протокол - NMEA 0183

## Протокол NMEA 0183

NMEA 0183 --- текстовый потокол обмена данными между навигационным оборудованием
![nmea](nmeamsg.png)

## Информация от драйвера составного устройства

* время в UTC формате
* координаты (широта, долгота, высота над уровнем моря)
* время до определения местоположения (в сек)
* количество видимых спутников
* скорость движения
* направление движения

Соответствует минимальному рекомендованному надобу данных NMEA

## GPSD

Gpsd --- сервис-демон, который следит за одним или несколькими GPS-приемниками и предоставляет доступ к ним прикладному ПО

* все данные от GPS доступны по запросу на TCP 2947
* возможность настройки формата вывода
* поддерживает NMEA-устройства