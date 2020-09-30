
ifeq ($(CC), )
	CC = gcc -Werror
endif

OUT_DIR = out
TARGET = test
SRC_DIR = ./stack 	\
		  ./queue 	\
		  ./tree
LIB_DIR = .
BASE_LIB = libbase
TARGET_STATIC_LIBS = $(BASE_LIB).a
TARGET_SHARE_LIBS = $(BASE_LIB).so
BASE_LIBS_FILES := $(foreach f, $(SRC_DIR), $(wildcard $(f)/*.c))
OBJECT_FILES = $(patsubst %.c, %.o, $(BASE_LIBS_FILES))
HEAD_FILES := $(foreach f, $(SRC_DIR), $(wildcard $(f)/*.h))
HEAD_DIR = ./include
CP = cp -r
RM = rm -rf
AR = ar rcs

INCLUDE = $(HEAD_DIR)

VPATH = ./compile

$(TARGET):$(BASE_LIB)
	$(CC) -o $@ test.c -L$(LIB_DIR) -lbase -static -I$(INCLUDE)
	#$(CC) -o $@ test.c -L$(LIB_DIR) -lbase 

$(TARGET_SHARE_LIBS):$(OBJECT_FILES)
	$(CC) -shared -fPIC -o $@ $^ -I$(INCLUDE)

$(TARGET_STATIC_LIBS):$(OBJECT_FILES)
	$(AR) $@ $^ -I$(INCLUDE)

$(OBJECT_FILES):
	$(foreach f, $(patsubst %.c, %.o, $(BASE_LIBS_FILES)), $(CC) -c -o $(f) $(patsubst %.o, %.c, $(f)) -I$(INCLUDE);)

$(BASE_LIB):init $(TARGET_SHARE_LIBS) $(TARGET_STATIC_LIBS)

init:
	$(CP) $(HEAD_FILES) $(HEAD_DIR)
	echo $(BASE_LIBS_FILES)
	mkdir -p $(OUT_DIR)
	#$(foreach d,$(SRC_DIR),$(CP) $(d)/*.c $(COMPILE_DIR);$(CP) $(d)/*.h $(COMPILE_DIR);)

clean:
	$(RM) $(OUT_DIR) $(OBJECT_FILES)
