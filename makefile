CC := g++
CFLAGS := -std=c++11 -Wall -Wextra -pedantic

SRCS := LoadBalancer.cpp main.cpp Webserver.cpp
OBJS := $(SRCS:.cpp=.o)
TARGET := loadbalancer

all: $(TARGET)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(OBJS) $(TARGET)
