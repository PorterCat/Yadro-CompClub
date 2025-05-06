# Решение тестового задания YADRO

Требуется написать прототип системы, которая следит за работой компьютерного клуба, обрабатывает события и подсчитывает выручку за день и время занятости каждого стола.

[Текст задания](https://drive.yadro.com/s/WMbk94mKSwetA7s).

## Сборка
Для сборки используется `CMake`.

Чтобы собрать можно выполнить скрипт:

### Linux
```sh
./build.sh
```

### Windows
```sh
./build.bat 
```

ИЛИ

```sh
mkdir -p build
cd build

cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake --build .
```

## Запуск
```sh
./build/compclub <input.txt>
```

## Тесты
- Исходные данные хранятся в директории `./tests` 
- Ожидаемые результаты в директории `./tests/pending` 

### Запуск
Для запуска потребуется интерпретатор Python
```sh
python3 run_test.py ./build/compclub 
```