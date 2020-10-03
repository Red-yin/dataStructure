
ifeq ($(CC), )
	CC = gcc -Werror
endif

OUT_DIR = out
TARGET = test
SRC_DIR = ./stack 	\
		  ./queue 	\
		  ./tree
LIB_DIR = .
BASE_LIB = libdataStructure
TARGET_STATIC_LIBS = $(BASE_LIB).a
TARGET_SHARE_LIBS = $(BASE_LIB).so
BASE_LIBS_FILES := $(foreach f, $(SRC_DIR), $(wildcard $(f)/*.c))
OBJECT_FILES = $(patsubst %.c, %.o, $(BASE_LIBS_FILES))
HEAD_FILES := $(foreach f, $(SRC_DIR), $(wildcard $(f)/*.h))
LOCAL_HEAD_DIR = ./include/local
HEAD_DIR = ./include
CP = cp -r
RM = rm -rf
AR = ar rcs

INCLUDE = -I$(HEAD_DIR)
INCLUDE += -I$(LOCAL_HEAD_DIR)

VPATH = ./compile

$(TARGET):$(BASE_LIB)
	#$(CC) -o $@ test.c -L$(LIB_DIR) -lbase -static -I$(INCLUDE)
	$(CC) -o $@ test.c -L$(LIB_DIR) -ldataStructure $(INCLUDE) -lpthread

$(TARGET_SHARE_LIBS):$(OBJECT_FILES)
	$(CC) -shared -o $@ $^

$(TARGET_STATIC_LIBS):$(OBJECT_FILES)
	$(AR) $@ $^

$(OBJECT_FILES):
	#只有在将.c文件编译成.o文件时，include目录才会被用到
	#在将.c文件编译.o文件的时候，都加上-fPIC，这样才能编译出动态库来，在链接打包生成库文件时这个参数是无效甚至非法的
	$(foreach f, $(patsubst %.c, %.o, $(BASE_LIBS_FILES)), $(CC) -c -o $(f) $(patsubst %.o, %.c, $(f)) -fPIC $(INCLUDE);)

$(BASE_LIB):init $(TARGET_SHARE_LIBS) $(TARGET_STATIC_LIBS) end

end:
	$(CP) $(TARGET_SHARE_LIBS) $(OUT_DIR)
	$(CP) $(TARGET_STATIC_LIBS) $(OUT_DIR)

init:
	echo $(INCLUDE)
	mkdir -p $(OUT_DIR)
	mkdir -p $(LOCAL_HEAD_DIR)
	$(CP) $(HEAD_FILES) $(LOCAL_HEAD_DIR)
	echo $(BASE_LIBS_FILES)
	#$(foreach d,$(SRC_DIR),$(CP) $(d)/*.c $(COMPILE_DIR);$(CP) $(d)/*.h $(COMPILE_DIR);)

clean:
	$(RM) $(OUT_DIR) $(OBJECT_FILES) $(LOCAL_HEAD_DIR) $(TARGET) $(TARGET_SHARE_LIBS) $(TARGET_STATIC_LIBS)
