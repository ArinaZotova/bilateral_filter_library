# Bilateral Filter Library

Курсовая работа по дисциплине **«Объектно-ориентированное программирование»**.

Проект реализует собственную библиотеку билатерального фильтра на C++17 и консольное приложение для демонстрации работы алгоритма.

В данной реализации рассматриваются изображения в градациях серого.

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
```

## Сборка

```bash
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

## Использование

```bash
bilateral_filter_app <input_image> <output_image> <diameter> <sigma_color> <sigma_space>
```

Пример:

```bash
bilateral_filter_app input.png output.png 10 100 10
```

## Описание параметров

- `input_image` - путь к исходному изображению;
- `output_image` - путь для сохранения результата;
- `diameter` - диаметр окна фильтрации;
- `sigma_color` - яркостная дисперсия;
- `sigma_space` - пространственная дисперсия.

## Основные функции библиотеки

```cpp
double gaussian(double x, double sigma);

double colorDistance(int color1, int color2);

void bilateralFilterCustom(const cv::Mat& src,
                           cv::Mat& dst,
                           int d,
                           double sigmaColor,
                           double sigmaSpace);
```

## Принцип работы

Для каждого пикселя рассматривается окрестность заданного диаметра. Вес соседнего пикселя вычисляется как произведение двух гауссовых функций:

1. пространственной - зависит от расстояния между пикселями;
2. яркостной - зависит от различия интенсивностей.

Итоговое значение пикселя вычисляется как нормированное взвешенное среднее.
