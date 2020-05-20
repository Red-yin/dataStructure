OUT_DIR = out
COMPILE_DIR = compile/
TARGET = test
SRC_DIR = ./stack 	\
		  ./queue 	\
		  ./tree
LIB_DIR = .
BASE_LIB = libbase
TARGET_STATIC_LIBS = $(BASE_LIB).a
TARGET_SHARE_LIBS = $(BASE_LIB).so
BASE_LIBS_FILES = queueByArray.c queueByLinklist.c stackByArray.c stackByLinklist.c binaryTree.c
CP = cp -r
RM = rm -r
CC = gcc -g
AR = ar rcs

VPATH = ./compile

$(TARGET):$(BASE_LIB)
	cd $(COMPILE_DIR);$(CC) -o $@ test.c -L$(LIB_DIR) -lbase -static
	#cd $(COMPILE_DIR);$(CC) -o $@ test.c -L$(LIB_DIR) -lbase 
	$(CP) $(COMPILE_DIR)$@ $(OUT_DIR)

$(TARGET_SHARE_LIBS):
	cd $(COMPILE_DIR);$(CC) -shared -fPIC -o $@ $(BASE_LIBS_FILES) 

$(TARGET_STATIC_LIBS):$(patsubst %.c, %.o, $(BASE_LIBS_FILES)) 
	cd $(COMPILE_DIR);$(AR) $@ $^

$(patsubst %.c, %.o, $(BASE_LIBS_FILES)): 
	cd $(COMPILE_DIR);$(foreach f, $(patsubst %.c, %.o, $(BASE_LIBS_FILES)), $(CC) -c -o $(f) $(patsubst %.o, %.c, $(f));)

$(BASE_LIB):init $(TARGET_SHARE_LIBS) $(TARGET_STATIC_LIBS)

init:
	mkdir -p $(COMPILE_DIR)
	mkdir -p $(OUT_DIR)
	#将所有源代码文件拷贝到compile目录
	$(foreach d,$(SRC_DIR),$(CP) $(d)/*.c $(COMPILE_DIR);$(CP) $(d)/*.h $(COMPILE_DIR);)
	$(CP) test.c $(COMPILE_DIR)

clean:
	$(RM) $(COMPILE_DIR) $(OUT_DIR)
