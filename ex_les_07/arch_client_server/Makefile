# Variabili per rendere il Makefile più leggibile e modificabile
CC = gcc
CFLAGS = -Wall -Wextra -std=c99
BIN_DIR = bin
TARGET_SERVER = $(BIN_DIR)/server
TARGET_CLIENT = $(BIN_DIR)/client
HEADERS = arch_cl_lib.h

# Regola predefinita: assicura che la directory bin esista, poi compila tutto
all: $(BIN_DIR) $(TARGET_SERVER) $(TARGET_CLIENT)

# Regola per creare la directory bin se non esiste
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Regola per compilare il programma server
$(TARGET_SERVER): server.c $(HEADERS) $(BIN_DIR)
	$(CC) $(CFLAGS) server.c -o $(TARGET_SERVER)

# Regola per compilare il programma client
$(TARGET_CLIENT): client.c $(HEADERS) $(BIN_DIR)
	$(CC) $(CFLAGS) client.c -o $(TARGET_CLIENT)

# Regola per pulire i file generati (eseguibili e file oggetto)
clean:
	rm -rf $(BIN_DIR) *.o
