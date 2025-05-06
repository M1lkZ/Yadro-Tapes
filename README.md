# Tape sorter

### Сборка

```cmake -B build -S . -DBUILD_TESTS=ON```

```cmake --build build```

### Тестирование

``` cmake --build build --target tests```

### Запуск 

```build/tape_sort input.txt output.txt config.txt```

Конфигурационный файл должен иметь следующую структуру
```
read_delay=2
write_delay=4
shift_delay=1
memory_limit=3
```

Где `memory_limit` - сколько элементов мы можем держать в памяти. 
Все задержки указаны в миллисекундах.
