# 设置目标
TARGET = server
# 设置编译器
CXX = g++
DEPS = ./inc/
# 获取inc下的所有.cpp文件
SRCS = $(wildcard src/*.cpp)
# 通过cpp文件获得与之同名的*.o类型的文件
OBJS = $(patsubst src/%.cpp, obj/%.o, $(SRCS))  
# 设置变量，连接的时候所需要的东西
CFLAGS = -lpthread `mysql_config --cflags --libs`

all: clean $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $^ -o $@ $(CFLAGS)

obj/%.o: src/%.cpp
	$(CXX) -c $< -o $@ -I$(DEPS)

.PHONY: clean
clean:
	$(RM) obj/*.o $(TARGET)

# $< 第一个依赖文件的名称。
# $@ 目标的完整名称。
# $^ 所有的依赖文件，以空格分开，不包含重复的依赖文件。
# $(RM) 表示rm -f