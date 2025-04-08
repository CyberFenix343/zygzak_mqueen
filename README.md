# Zygzak McQueen - Robot w języku Arduino

## Opis projektu

Projekt "Zygzak McQueen" to robot sterowany za pomocą mikrokontrolera Arduino, który wykorzystuje serwomechanizm, czujniki odległości, wyświetlacz LCD oraz silniki do poruszania się. Robot może poruszać się autonomicznie lub być sterowany manualnie za pomocą komend wysyłanych przez port szeregowy.

## Funkcjonalności

- **Autonomiczna jazda**: Robot unika przeszkód dzięki czujnikowi odległości (IR sensor).
- **Sterowanie manualne**: Możliwość sterowania robotem za pomocą komend z klawiatury (serial monitor).
- **Pomiar temperatury, światła i poziomu wody**: Robot monitoruje temperaturę, poziom światła oraz odczyt z potencjometru i wyświetla te dane na wyświetlaczu LCD.
- **Zmiana prędkości**: Prędkość robota może być zwiększana lub zmniejszana za pomocą komend.

## Wymagania

- Arduino IDE
- Biblioteka Servo
- Biblioteka hd44780
- Biblioteka DistanceSensor

## Połączenia sprzętowe

- **Wyświetlacz LCD**: Podłączony do I2C (adres: `0x20`)
- **Czujnik odległości (IR)**: Podłączony do pinów `IR_TRIG` (7) i `IR_ECHO` (8)
- **Serwomechanizm**: Podłączony do pinu `3`
- **Silniki**: Silniki podłączone do pinów `RIGHT_ENGINE` (9) i `LEFT_ENGINE` (10), z fazami do pinów `LEFT_PHASE` (2) i `RIGHT_PHASE` (3)

## Instrukcja obsługi

1. **Tryb autonomiczny**:
   - Włącz tryb autonomiczny, wysyłając komendę `q` przez serial monitor.
   - Robot będzie unikał przeszkód na swojej drodze.
   
2. **Tryb manualny**:
   - Włącz tryb manualny, wysyłając komendę `q` przez serial monitor.
   - Sterowanie robotem odbywa się za pomocą następujących komend:
     - `w` – jazda do przodu
     - `s` – jazda do tyłu
     - `a` – skręt w lewo
     - `d` – skręt w prawo
     - `t` – zatrzymanie
     - `+` – zwiększenie prędkości
     - `-` – zmniejszenie prędkości
     - `r` – włącz/wyłącz ruch
     - `m` – przełącz tryb (manualny/autonomiczny)

## Instalacja

1. Sklonuj repozytorium.
2. Otwórz projekt w Arduino IDE.
3. Wgraj kod na swoje urządzenie (np. Arduino Uno).
4. Monitoruj wyświetlacz LCD oraz komunikaty w serial monitorze.

## Uwagi

Projekt wykorzystuje bibliotekę `hd44780` do obsługi wyświetlacza LCD i `Servo` do kontrolowania serwomechanizmu. Biblioteka `DistanceSensor` jest używana do obsługi czujnika odległości.
