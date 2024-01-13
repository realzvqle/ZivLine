BUILD_DIR := build
SRC_DIR := src
RES_DIR := resources

EXE := $(BUILD_DIR)/zivline.exe
RES_OBJ := $(BUILD_DIR)/res.o

CC := gcc
RC := windres

CFLAGS := -O1 -s
LDFLAGS := -ldbghelp

SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))

all: $(EXE)
$(EXE): $(RES_OBJ) $(OBJ_FILES)
	$(CC) $(OBJ_FILES) $(RES_OBJ) $(LDFLAGS) -o $(EXE)
	$(EXE)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Compiling $< into $@"
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compilied $@"


$(RES_OBJ): $(RES_DIR)/res.rc
	$(RC) $(RES_DIR)/res.rc -O coff -o $(RES_OBJ)





