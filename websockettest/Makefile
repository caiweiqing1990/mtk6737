SRC_FILE = cJSON.c  cJSON.h  http_request.c websocket_client.c  websocket_common.c  websocket_common.h
websocket_client:$(SRC_FILE)
	gcc -o websocket_client websocket_client.c cJSON.c websocket_common.c http_request.c -lm -lpthread
