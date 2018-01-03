CC             = gcc
VPATH          = src test
INCLUDEDIR     = include 

TARGET_CORE    = test_big_float 
TARGET_RAND    = test_rand

SRC_CORE       = bf_util.c bf_add.c bf_cmp.c bf_sub.c bf_mul.c bf_div.c 
SRC_CORE_TOOLS = bf_sqrt.c bf_io.c bf_exp.c bf_ln.c bf_if.c
SRC_CORE_TEST  = test_big_float.c
SRC_RAND       = bf_rand.c
SRC_RAND_TEST  = test_rand.c

CACHE_FILES    = _big_float.c _big_float.o _big_float.cpython-36m-x86_64-linux-gnu.so tags

all: $(TARGET_CORE) $(TARGET_RAND)

$(TARGET_CORE): $(SRC_CORE_TEST) $(SRC_CORE) $(SRC_CORE_TOOLS)
	$(CC) -I $(INCLUDEDIR) -o $@ $^

$(TARGET_RAND):	$(SRC_RAND_TEST) $(SRC_RAND) $(SRC_CORE) $(SRC_CORE_TOOLS)
	$(CC) -I $(INCLUDEDIR) -o $@ $^

.PHONY: clean

clean:
	rm -f $(TARGET_CORE) $(TARGET_RAND) $(CACHE_FILES) 
	rm -r __pycache__

