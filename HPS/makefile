# Makefile para compilação nativa no DE1-SoC
# Versão simplificada - mantém estilo original

help:
	@echo "Comandos:"
	@echo "  run     - executa (compila tudo, executa e limpa)"
	@echo "  compile - apenas compila"
	@echo "  clean   - limpa arquivos compilados"

run:
	@echo "--- Montando lib.s ---"
	@as lib.s -o lib.o
	@echo "--- Compilando mouse_utils.c ---"
	@gcc -c mouse_utils.c -o mouse_utils.o -std=c99
	@echo "--- Compilando e Ligando main.c ---"
	@gcc main.c mouse_utils.o lib.o -z noexecstack -std=c99 -lm -o exe
	@echo "--- Executando (requer sudo para mouse) ---"
	@sudo ./exe
	@echo "--- Limpando arquivos temporários ---"
	@rm -f exe lib.o mouse_utils.o

compile:
	@echo "--- Montando lib.s ---"
	@as lib.s -o lib.o
	@echo "--- Compilando mouse_utils.c ---"
	@gcc -c mouse_utils.c -o mouse_utils.o -std=c99
	@echo "--- Compilando e Ligando main.c ---"
	@gcc main.c mouse_utils.o lib.o -z noexecstack -std=c99 -lm -o exe
	@echo ">>> Executavel 'exe' criado. Execute com: sudo ./exe"

clean:
	@echo "--- Limpando ---"
	@rm -f exe *.o

.PHONY: help run compile clean
