#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* commandTempalte = "gsettings set org.gnome.desktop.background picture-uri /home/";

void main( int argc, char* argv[] )
{
	FILE* f_log = fopen( "/tmp/.wallparer.log", "w+" );

	if( !f_log )
	{
		printf( "Error on openin log file\n" );
		return;
	}

	system( "echo ${USER} > /tmp/.wallparer-username" );

	FILE* f_user = fopen( "/tmp/.wallparer-username", "r" );

	if( !f_user )
	{
		fprintf( f_log, "could not read username\n" );
		fclose( f_log );
		return;
	}

	char username[256] = {0};

	fscanf( f_user, "%s", username );

	fclose( f_user );

	system( "rm /home/${USER}/.wallparers/pictures/*" );

	system( "cp /home/${USER}/Pictures/Wallpapers/* /home/${USER}/.wallparers/pictures/" );

	system( "ls /home/${USER}/.wallparers/pictures > /home/${USER}/.wallparers/list" );

	FILE* f_list = fopen( "/home/dimitis/.wallparers/list", "r" );

	if( !f_list )
	{
		fprintf( f_log, "Wallparer error: file was not created!\n" );
		fclose( f_log );
		return;
	}

	int count = 0;
	char buffer[1000] = {0};

	while( fgets( buffer, 1000, f_list ) )
	{
		count += 1;

		/*if( strchr( buffer, ' ' ) )
		{
			do{
				char command[1000] = "mv /home/${USER}/.wallparer/pictures/";
				strcat( command, buffer );
				
				strcat( command, " /home/${USER}/.wallparer/pictures/" );

				*strchr( buffer, ' ' ) = '_';

				strcat( command, buffer );

				printf( "%s\n", command );
				//system( command );
			}while( strchr( buffer, ' ' ) );
		}*/
	}

	if( !feof( f_list ) )
	{
		fprintf( f_log, "Wallparer error: cannot read from file!\n" );
		fclose( f_list );
		fclose( f_log );
		return;
	}

	fclose( f_list );

	system( "ls /home/${USER}/.wallparers/pictures > /home/${USER}/.wallparers/list" );

	f_list = fopen( "/home/dimitis/.wallparers/list", "r" );

	if( !f_list )
	{
		fprintf( f_log, "Wallparer error: file was not created!\n" );
		fclose( f_log );
		return;
	}

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
			
			fprintf( f_log, "Wallparers error: can't read from file!\n" );
			fclose( f_log );
			return;
		}
	}

	while( 1 )
	{
		printf( "Choose a wallparer:\n" );
		for( i = 0; i < count; ++i )
		{

			if( strlen( a_list[i] ) > 80 )
			{
				printf( "%d. %s\n", i, a_list[i] );
				continue;
			}
		
			char buffer[80] = {0};

			while( 1 )
			{
				while( strchr(buffer, '\n' ) )
				{
					*strchr(buffer, '\n') = ' ';
				}

				if( i > count || strlen( buffer ) > 80 || strlen( buffer ) + strlen( a_list[i] ) > 80 )
				{
					break;
				}
				
				char t_buffer[5] = {0};
				sprintf( t_buffer, "%d. ", i);
				
				strcat( buffer, t_buffer );
				strcat( buffer, a_list[i] );
				strcat( buffer, "    " );
				
				i += 1;
				continue;
			}

			printf( "\t%s\n", buffer );
		}

		printf( ">> " );

		int inp;

		scanf( "%u", &inp );
		
		if( inp == -1 )
		{
			return;
		}

		if( inp > count || inp < 0 )
		{
			printf( "Wrong choise!" );
		}
		else
		{
			char b_command[1000] = {0};

			strcpy( b_command, commandTempalte );
			strcat( b_command, username );
			strcat( b_command, "/.wallparers/pictures/" );
			strcat( b_command, a_list[inp] );

			//printf( "%s\n", b_command );
			system( b_command );

			break;
		}
	}

	fclose( f_list );
	fclose( f_log );
}
