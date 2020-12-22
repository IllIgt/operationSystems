#include <unistd.h>
#include <fcntl.h>
#include <malloc.h>
#include <cstring>

#define MAXLINE 128
#define PIPE_S2C "../S2C_PIPE"
#define PIPE_C2S "../C2S_PIPE"

const int PIPE_S2C_MODE = O_RDONLY;
const int PIPE_C2S_MODE = O_WRONLY;

int main() {

	char str[ MAXLINE ];
	ssize_t n;
	int readfd;
	int writefd;

	while ( true ) {

		readfd = open( PIPE_S2C, PIPE_S2C_MODE );
		if ( readfd!= -1 ) {

			printf("[Client] -> * read-only pipe opened...\n");
			sleep( 1 );

			while( ( n = read( readfd, str, MAXLINE ) ) > 0) {
				str[ n ] = 0;
				printf("[Client] -> * server says: %s\n", str);
				break;
			}

			strcpy( str, "Pong!\n" );
			writefd = open( PIPE_C2S, PIPE_C2S_MODE );
			sleep( 1 );
			printf("[Client] -> * write-only pipe opened...\n");
			sleep( 1 );
			printf("[Client] -> [Server]: %s \n", str);
			write( writefd, str, strlen( str ) );
			close( readfd );
			close( writefd );
			break;
		}
		sleep( 1 );
	}

	return 1;
}