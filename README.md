# Bilateral Filter Library

Курсовая работа по дисциплине **«Объектно-ориентированное программирование»**.

Проект реализует собственную библиотеку билатерального фильтра на C++17 и консольное приложение для демонстрации работы алгоритма.

## Возможности

- собственная реализация билатерального фильтра;
- обработка черно-белых изображений;
- использование OpenCV для чтения, записи и хранения изображений;
- сборка через CMake;
- кроссплатформенность.

## Требования

- C++17;
- CMake 3.16 или выше;
- OpenCV.

## Структура проекта

```text
bilateral_filter_library/
├── CMakeLists.txt
├── README.md
├── .gitignore
├── include/
│   └── bilateral_filter/
│       └── bilateral_filter.hpp
├── src/
│   └── bilateral_filter.cpp
├── apps/
│   └── bilateral_filter_cli.cpp
└── examples/
    └── run_example.txt
