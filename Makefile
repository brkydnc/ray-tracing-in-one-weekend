CC = gcc
LDFLAGS = -lm 
OBJFILES = main.o vec3.o color.o ray.o hit.o util.o camera.o
TARGET = main
RENDER_OUTPUT = output.ppm

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CLFAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) $(RENDER_OUTPUT)

render: $(RENDER_OUTPUT)
	./$(TARGET) >> $(RENDER_OUTPUT)

$(RENDER_OUTPUT):
	touch $(RENDER_OUTPUT)
