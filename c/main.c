#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main( int argc, char* argv[] )
{
	system( "gsettings set org.gnome.desktop.background picture-uri /home/${USER}/.wallparers/pictures/wallpaper" );

	FILE* f_log = fopen( "/tmp/.wallparer.log", "w+" );

	if( !f_log )
	{
		printf( "Error on openin log file\n" );
		return;
	}

	system( "ls /home/${USER}/Pictures/Wallpapers > /home/${USER}/.wallparers/list" );
	
	FILE* f_list = fopen( "/home/dimitis/.wallparers/list", "r" );

	if( !f_list )
	{
		fprintf( f_log, "Wallparer error: file was not created!\n" );
		fclose( f_log );
		return;
	}

	int count = 0, max_len = 0;
	char buffer[257] = {0};

	while( fgets( buffer, 257, f_list ) )
	{
		count += 1;

		int t_len = strlen( buffer );
		max_len = t_len > max_len ? t_len : max_len;
	}

	max_len += 1;

	if( !feof( f_list ) )
	{
		fprintf( f_log, "Wallparer error: cannot read from file!\n" );
		fclose( f_list );
		fclose( f_log );
		return;
	}

	rewind( f_list );

	char a_list[count][max_len];

	int i, j;

	for( i = 0; i < count; ++i)
	{
		memset( a_list[i], 0, max_len );
	}
	
	for( i = 0; i < count; ++i )
	{
		if( !fgets( a_list[i], max_len, f_list ) )
		{
			fclose( f_list );
			
			fprintf( f_log, "Wallparers error: can't read from file!\n" );
			fclose( f_log );
			return;
		}

		while( strchr(a_list[i], '\n' ) )
		{
			*strchr(a_list[i], '\n') = 0;
		}
	}

	while( 1 )
	{
		printf( "Choose a wallparer:\n" );
		for( i = 0; i < count; ++i )
		{
			if( strlen( a_list[i] ) > 76 )
			{
				printf( "%d. %s\n", i, a_list[i] );
				continue;
			}
		
			char buffer[77] = {0};

			while( 1 )
			{
				if( i >= count || strlen( buffer ) > 76 || strlen( buffer ) + strlen( a_list[i] ) > 76 )
				{
					i -= 1;
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

			printf( "    %s\n", buffer );
		}

		printf( ">> " );

		int inp;

		scanf( "%d", &inp );
		
		if( inp == -1 )
		{
			return;
		}

		if( inp >= count || inp < 0 )
		{
			printf( "Wrong choise!" );
		}
		else
		{
			char b_command[1000 + max_len];

			memset( b_command, 0, 1000 + max_len );

			strcat( b_command, "cp /home/${USER}/Pictures/Wallpapers/" );

			int last = 0;

			for( i = 0; i < strlen( a_list[inp] ); ++i )
			{
				if( a_list[inp][i] == ' ' )
				{
					strncat( b_command, a_list[inp], i - last );
					strcat( b_command, "\\ " ); 
					last = i + 1;
				}
			}

			strcat( b_command, &a_list[inp][last] );

			strcat( b_command, " /home/${USER}/.wallparers/pictures/wallpaper" );

			//printf( "%s\n", b_command );
			system( b_command );

			break;
		}
	}

	fclose( f_list );
	fclose( f_log );
}
