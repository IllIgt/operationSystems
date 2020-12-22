#include <cerrno>
#include <unistd.h>
#include <fcntl.h>
#include <malloc.h>
#include <sys/stat.h>
#include <cstring>


#define MAXLINE 128

#define FILE_MODE ( S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH )
#define PIPE_S2C "../S2C_PIPE"
#define PIPE_C2S "../C2S_PIPE"

const int PIPE_S2C_MODE = O_WRONLY;
const int PIPE_C2S_MODE = O_RDONLY;

int main() {
	printf("[Server] -> * Start Server...\n");
	char str[ MAXLINE ];
	ssize_t n;
	int readfd;
	int writefd;

	strcpy( str, "Ping?\n" );

	unlink( PIPE_S2C );
	unlink( PIPE_C2S );

	if( mkfifo( PIPE_S2C, FILE_MODE ) == EEXIST )
		printf("\n [Server] -> * warning: pipe named %s already exists!\n", PIPE_S2C);

	if( mkfifo( PIPE_C2S, FILE_MODE ) == EEXIST )
		printf("\n [Server] -> * warning: pipe named %s already exists!\n", PIPE_C2S);

	writefd = open( PIPE_S2C, PIPE_S2C_MODE );
	if(writefd != -1){
		printf("[Server] -> * write-only pipe opened...\n");
		sleep( 1 );
		write( writefd, str, strlen( str ) );
		printf("[Server] -> [Client]: %s\n", str);
		readfd = open( PIPE_C2S, PIPE_C2S_MODE );
		printf("[Server] -> * waiting for response...\n");
		sleep( 1 );

		while( ( n = read( readfd, str, MAXLINE ) ) > 0 ) {
			str[ n ] = 0;
			printf("[Server] -> * client responds: %s\n", str);
			break;
		}
		close( readfd );
		close( writefd );
		unlink( PIPE_S2C );
		unlink( PIPE_C2S );
	} else {
		printf("Unable to open pipes...\n");
		return 1;
	}
}

