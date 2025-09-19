# Compilador e Option flags
CXX = g++
CXXFLAGS = -Wall -std=c++17 -O2

TARGET = programa

# Diretórios
SRC_DIR = .
ALG_DIR = algoritmos

# Arquivos fonte
SRCS = $(SRC_DIR)/main.cpp \
       $(SRC_DIR)/avaliador.cpp \
       $(ALG_DIR)/bubbleSort.cpp \
       $(ALG_DIR)/insertionSort.cpp \
       $(ALG_DIR)/buscaBinaria.cpp \
       $(ALG_DIR)/buscaSequencial.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# make: criar o "programa", isto é, compilar, mas não executar
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# make clean: remover o "programa"
clean:
	rm -f $(OBJS) $(TARGET)

# make run: executar o "programa"
run: all
	./$(TARGET)