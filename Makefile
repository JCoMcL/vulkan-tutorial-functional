SRC = main.cpp
VULKAN_SDK_PATH = /usr
CFLAGS = -std=c++1z -I$(VULKAN_SDK_PATH)/include
LDFLAGS = -L$(VULKAN_SDK_PATH)/lib `pkg-config --static --libs glfw3` -lvulkan

vktest: $(SRC)
	g++ $(CFLAGS) -o $@ $< $(LDFLAGS)

.PHONY: test clean

test: vktest
	./$<

clean:
	rm -f vktest


