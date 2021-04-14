#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* commandTempalte = "gsettings set org.gnome.desktop.background picture-uri /home/dimitis/.wallparers/pictures/";

void main( int argc, char* argv[] )
{
	/*FILE* file = fopen( "/home/${USER}/.wallparers/conf", "r" );

	if( !file )
	{
		printf( "Wallparer error: conf file!\n" );
		return;
	}*/

	system( "ls /home/${USER}/.wallparers/pictures > /home/${USER}/.wallparers/list" );

	FILE* f_list = fopen( "/home/dimitis/.wallparers/list", "r" );

	if( !f_list )
	{
		printf( "Wallparer error: file was not created!\n" );
		return;
	}

	int count = 0;
	char buffer[1000] = {0};

	while( fgets( buffer, 1000, f_list ) )
	{
		count += 1;
	}

	if( !feof( f_list ) )
	{
		printf( "Wallparer error: cannot read from file!\n" );
		fclose( f_list );
		return;
	}

	rewind( f_list );

	char a_list[count][1000];

	int i, j;

	for( i = 0; i < count; ++i)
	{
		for( j = 0; j < 1000; ++j )
		{
			a_list[i][j] = 0;
		}
	}

	for( i = 0; i < count; ++i )
	{
		if( !fgets( a_list[i], 1000, f_list ) )
		{
			fclose( f_list );
			
			printf( "Wallparers error: can't read from file!\n" );

			return;
		}
	}

	while( 1 )
	{
		printf( "Choose a wallparer:\n" );
		for( i = 0; i < count; ++i )
		{
			printf( "%d. %s\n", i, a_list[i] );
		}

		printf( ">> " );

		unsigned int inp;

		scanf( "%u", &inp );

		if( inp > count )
		{
			printf( "Wrong choise!" );
		}
		else
		{
			char b_command[1000] = {0};

			strcpy( b_command, commandTempalte );
			strcat( b_command, a_list[inp] );

			system ( b_command );

			break;
		}
	}

	fclose( f_list );
}
