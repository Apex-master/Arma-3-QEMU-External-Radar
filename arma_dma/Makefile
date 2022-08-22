CXX=g++
CXXFLAGS=-I./memflow_lib/memflow-win32-ffi/ -I./memflow_lib/memflow-ffi/ -L./memflow_lib/target/release -Wno-multichar
LIBS=-lm -Wl,--no-as-needed -ldl -lpthread -l:libmemflow_win32_ffi.a

OUTDIR=./build
OBJDIR=$(OUTDIR)/obj

$(shell mkdir -p $(OBJDIR))
$(shell cp memflow_lib/memflow-qemu-procfs/target/release/libmemflow_qemu_procfs.so $(OUTDIR))

%.o: %.cpp
	$(CXX) -c -o $(OBJDIR)/$@ $< $(CXXFLAGS)

arma_dma: arma_dma.o memory.o sio_socket.o sio_packet.o sio_client.o sio_client_impl.o
	$(CXX) -o $(OUTDIR)/$@ $(OBJDIR)/arma_dma.o $(OBJDIR)/memory.o $(OBJDIR)/sio_socket.o $(OBJDIR)/sio_packet.o $(OBJDIR)/sio_client.o $(OBJDIR)/sio_client_impl.o $(CXXFLAGS) $(LIBS)

.PHONY: all
all: arma_dma

.DEFAULT_GOAL := all

clean:
	rm -rf $(OUTDIR)
