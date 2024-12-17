# Название подпроекта
project(Sender)

# Добавляем исполняемый файл из Sender.cpp
add_executable(Sender Sender.cpp)

# Подключение библиотеки Windows (необходимо для использования API Windows)
target_link_libraries(Sender PRIVATE kernel32)
