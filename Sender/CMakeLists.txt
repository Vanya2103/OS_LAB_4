# �������� ����������
project(Sender)

# ��������� ����������� ���� �� Sender.cpp
add_executable(Sender Sender.cpp)

# ����������� ���������� Windows (���������� ��� ������������� API Windows)
target_link_libraries(Sender PRIVATE kernel32)
