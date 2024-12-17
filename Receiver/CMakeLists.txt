# Название подпроекта
project(Receiver)

# Добавляем исполняемый файл из Receiver.cpp
add_executable(Receiver Receiver.cpp)

# Подключение библиотеки Windows
target_link_libraries(Receiver PRIVATE kernel32)
